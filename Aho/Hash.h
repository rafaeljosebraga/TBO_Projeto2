#pragma once
#include "EstruturasAuxiliares/Arvore.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;
// hash Function
template <typename T> class Hash {
private:
  vector<ArvoreBinaria<T>> tabela;
  int tamanho;
  int count;

  void resize() {
    int oldSize = tamanho;
    tamanho = tamanho * 2; // or next prime number

    auto *oldTable = tabela;
    tabela = new ArvoreBinaria<T>[tamanho];

    count = 0; // reset count; will re-add elements

    // Iterate over old table
    for (int i = 0; i < oldSize; i++) {
      vector<T> elementos;
      oldTable[i].EmOrdem(elementos);
      for (const auto &el : elementos) {
        insert(el); // re-insert into new table (increments count)
      }
    }

    delete[] oldTable;
  }

  int hashFunction(char chave) {
    int hash = chave % tamanho;
    return hash;
  }

public:
  Hash(int tam = 8) : tamanho(tam) {
    tabela.resize(tamanho);
    count = 0;
  }

  void insert(char chave, T valor) {
    int indice = hashFunction(chave);
    tabela[indice].Inserir(valor);
    count++;
  }

  vector<T> search(char chave) {
    int indice = hashFunction(chave);
    vector<T> resultados;
    tabela[indice].EmOrdem(resultados);
    return resultados;
  }

  bool searchSpecific(char chave, T valor) {
    int indice = hashFunction(chave);
    return tabela[indice].Pesquisar(valor);
  }
};
