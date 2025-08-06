#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;

long long tempo_total_kmp = 0;
long long tempo_total_lps = 0;
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

vector<string> quebraString(const string &str, char delimitador) {
  vector<string> partes;
  size_t pos = 0;
  size_t found;

  while (pos < str.length()) {
    size_t found = pos;
    while (found < str.length() && str[found] != delimitador) {
      found++;
    }
    if (found != pos) { // Evita partes vazias
      partes.push_back(str.substr(pos, found - pos));
    }
    pos = found + 1;
  }
  if (pos < str.length()) {
    partes.push_back(str.substr(pos));
  }

  return partes;
}

bool match(char p, char t) { return p == '*' || p == t; }
// buscando o padrão pattern no texto, algoritmo KMP
vector<int> kmp(const char *texto, const char *pattern, int linhaAtual,
                vector<int> LPS) {
  auto start = high_resolution_clock::now();
  vector<int> achados;
  int tamPattern = strlen(pattern);
  int tamTexto = strlen(texto);

  // modelando a tabela de prefixo (LPS), chama a função lps()
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
  // Exemplo de uso do vector partes (remova ou adapte conforme necessário)
  // for (const auto& parte : partes) {
  //   // processar parte se necessário
  // }

  auto end = high_resolution_clock::now();
  auto duration = duration_cast<nanoseconds>(end - start).count();
  tempo_total_kmp += duration;
  return achados;
}

void KMPkrauss(const char *pattern, const vector<string> &partes) {
  ifstream arquivo("entrada.txt");
  if (!arquivo.is_open()) {
    cerr << "Erro ao abrir o arquivo entrada.txt" << endl;
    return;
  }
  // Calcula todos os LPSs antes do processamento
  vector<vector<int>> lps_partes;
  for (const auto &parte : partes) {
    lps_partes.push_back(lps(parte.c_str(), parte.length()));
  }
  string linha;
  int linhaAtual = 1;
  while (getline(arquivo, linha)) {
    int tamTexto = linha.length();
    vector<int> achados_maiores;
    bool prefixo_asterisco = (pattern[0] == '*');
    for (int i = 0; i < tamTexto; ++i) {
      bool achou_todas = true;
      int pos = i;
      for (size_t idx = 0; idx < partes.size(); ++idx) {
        const auto &parte = partes[idx];
        const auto &lps_atual = lps_partes[idx];
        vector<int> achados =
            kmp(linha.c_str() + pos, parte.c_str(), linhaAtual, lps_atual);
        if (achados.empty() ||
            (!prefixo_asterisco && idx == 0 && achados[0] != 0)) {
          achou_todas = false;
          break;
        }
        pos += achados[0] + parte.length();
      }
      if (achou_todas) {
        achados_maiores.push_back(i);
      }
    }
    if (!achados_maiores.empty()) {
      cout << "Na linha " << linhaAtual << endl;
      for (auto a : achados_maiores) {
        cout << "Padrão na posição " << a << endl;
        size_t barra = 0;
        while (barra < linha.size() && linha[barra] != '/')
          barra++;
        if (barra < linha.size()) {
          cout << "Texto: " << linha.substr(0, barra) << endl;
        } else {
          cout << "Texto: " << linha << endl;
        }
      }
    }
    linhaAtual++;
  }
  arquivo.close();
}

int main() {
  const char *pattern = "b*la";
  cout << "Padrao: " << pattern << endl;
  vector<string> brokenPattern = quebraString(pattern, '*');
  for (const auto &part : brokenPattern) {
    cout << "Parte do padrão: " << part << endl;
  }

  // Tempo para criar LPSs
  auto start_lps = high_resolution_clock::now();
  vector<vector<int>> lps_partes;
  for (const auto &parte : brokenPattern) {
    lps_partes.push_back(lps(parte.c_str(), parte.length()));
  }
  auto end_lps = high_resolution_clock::now();
  tempo_total_lps += duration_cast<nanoseconds>(end_lps - start_lps).count();

  // Chama KMPkrauss para processar o arquivo inteiro
  KMPkrauss(pattern, brokenPattern);

  cout << "Tempo total de execucao do KMP: " << (tempo_total_kmp / 1000000)
       << " ms" << endl;
  cout << "Tempo total para criacao das LPS: " << (tempo_total_lps) << " ns"
       << endl;

  return 0;
}
