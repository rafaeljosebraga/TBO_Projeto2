#include <cstring>
#include <iostream>
using namespace std;

const int MAX_M = 1000; // tamanho máximo do padrão
const int SIGMA = 256;  // tamanho do alfabeto (ASCII completo)

int f[MAX_M + 1][SIGMA]; // função de transição (autômato)

void FailureFunction(const string &p) {
  int m = p.length();

  // Inicializa todas as transições com 0
  for (int i = 0; i <= m; i++) {
    for (int c = 0; c < SIGMA; c++) {
      f[i][c] = 0;
    }
  }

  // Primeira transição especial
  f[0][(unsigned char)p[0]] = 1;

  int x = 0; // estado atual na construção

  // Construção do autômato
  for (int i = 1; i < m; i++) {
    for (int c = 0; c < SIGMA; c++) {
      f[i][c] = f[x][c]; // herda transições do estado x
    }

    f[i][(unsigned char)p[i]] = i + 1; // transição correta
    x = f[x][(unsigned char)p[i]];     // avança estado
  }
}

int main() {
  string p = "ababc";

  FailureFunction(p);

  // Exibe a tabela de transição
  cout << "Tabela de transição (f):\n";
  for (int i = 0; i <= p.length(); i++) {
    cout << "Estado " << i << ": ";
    for (char c = 'a'; c <= 'c'; c++) { // só mostrando 'a','b','c' do exemplo
      cout << c << "->" << f[i][c] << " ";
    }
    cout << endl;
  }

  return 0;
}
