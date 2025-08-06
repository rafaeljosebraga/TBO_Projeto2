
#ifndef AHOCORASICK_H
#define AHOCORASICK_H

#include "Map.h"
#include <string>
#include <vector>
using namespace std;

class AhoCorasick {
public:
  AhoCorasick();
  ~AhoCorasick();

  void inserir(const string &palavra);
  void construirFalhas();
  vector<int> buscar(const string &texto);

private:
  // Definição do nó interno será feita depois
};

#endif // AHOCORASICK_H
