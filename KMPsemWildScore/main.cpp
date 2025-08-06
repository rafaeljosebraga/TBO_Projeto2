#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;

long long tempo_total_kmp = 0;
int acessos = 0;

void imprimir(const char *texto, int inicio, int fim, int linhaAtual) {
  cout << "[Linha " << linhaAtual << "]\tPadrao encontrado:\t";
  for (int i = inicio; i <= fim; i++) {
    cout << texto[i];
  }
  cout << endl;
}

// modelando a tabela de prefixo (LPS)
vector<int> lps(const char *pattern, int tamPattern) {

  vector<int> LPS(tamPattern, 0);
  int j = 0;
  int i = 1;

  while (i < tamPattern) {

    if (pattern[i] == pattern[j]) {
      j++;
      LPS[i] = j;
      i++;
    } else {
      if (j != 0) {
        j = LPS[j - 1];
      } else {
        LPS[i] = 0;
        i++;
      }
    }
  }

  return LPS;
}

// buscando o padrão pattern no texto, algoritmo KMP
vector<int> kmp(const char *texto, const char *pattern, int linhaAtual) {
  auto start = high_resolution_clock::now();
  vector<int> achados;
  int tamPattern = strlen(pattern);
  int tamTexto = strlen(texto);

  // modelando a tabela de prefixo (LPS), chama a função lps()
  vector<int> LPS = lps(pattern, tamPattern);
  int i = 0;
  int j = 0;

  for (i = 0; i < tamTexto;) {
    if (pattern[j] == texto[i]) {
      i++;
      j++;
      if (j == tamPattern) {
        achados.push_back(i - j);
        j = LPS[j - 1];
      }
    } else if (j != 0) {
      j = LPS[j - 1];
    } else {
      i++;
    }
  }
  auto end = high_resolution_clock::now();
  auto duration = duration_cast<nanoseconds>(end - start).count();
  tempo_total_kmp += duration;
  return achados;
}

int main() {
  ifstream arquivo("entrada.txt");
  if (!arquivo.is_open()) {
    cerr << "Erro ao abrir o arquivo entrada.txt" << endl;
    return 1;
  }

  const char *pattern = "rep";
  cout << "Padrao: " << pattern << endl;

  string linha;
  int linhaAtual = 1;
  while (getline(arquivo, linha)) {
    vector<int> achados = kmp(linha.c_str(), pattern, linhaAtual);
    if (achados.size() > 0) {
      cout << "Na linha " << linhaAtual << endl;
      for (auto a : achados) {
        cout << "Padrão na posição " << a << endl;
        cout << "Texto: " << linha << endl;
      }
    }
    linhaAtual++;
  }
  tempo_total_kmp = tempo_total_kmp / 1000000;
  cout << "Tempo total de execucao do KMP: " << tempo_total_kmp << " ms"
       << endl;

  arquivo.close();
  return 0;
}
