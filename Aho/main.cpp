#include "AhoCorasick.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
  // Supondo que você já tenha um vetor de palavras

  vector<string> palavras = {"bola", "minecraft", "roblox",
                             "ela",  "ment",      "ira"};

  // Cronômetro para criação do autômato
  auto start_automato = std::chrono::high_resolution_clock::now();
  AhoCorasick automato(palavras);
  auto end_automato = std::chrono::high_resolution_clock::now();
  auto duracao_automato = std::chrono::duration_cast<std::chrono::nanoseconds>(
                              end_automato - start_automato)
                              .count();

  // Ler o conteúdo do arquivo entrada.txt
  ifstream arquivo("entrada.txt");
  if (!arquivo) {
    cerr << "Erro ao abrir entrada.txt" << endl;
    return 1;
  }
  stringstream buffer;
  buffer << arquivo.rdbuf();
  string texto = buffer.str();

  vector<int> encontradas;
  vector<string> palavrasEncontradas;

  // Cronômetro para busca
  auto start_busca = std::chrono::high_resolution_clock::now();
  automato.buscar(texto, encontradas, palavrasEncontradas);
  auto end_busca = std::chrono::high_resolution_clock::now();
  auto duracao_busca = std::chrono::duration_cast<std::chrono::nanoseconds>(
                           end_busca - start_busca)
                           .count();

  // Exemplo de saída dos resultados
  for (size_t i = 0; i < palavrasEncontradas.size(); ++i) {
    cout << "Encontrado: " << palavrasEncontradas[i] << " na posição "
         << encontradas[i] << endl;
  }

  cout << "Tempo de criação do autômato: " << duracao_automato << " ns" << endl;
  if (duracao_busca > 1000000) {
    cout << "Tempo de busca: " << duracao_busca / 1000000.0 << " ms" << endl;

  } else {
    cout << "Tempo de busca: " << duracao_busca << " ns" << endl;
  }

  return 0;
}
