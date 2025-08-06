#ifndef NODE_H
#define NODE_H

#include "Hash.h"
#include "Map.h"
#include <cstddef>
#include <optional>
using namespace std;

class Node {
public:
  char chave; // caractere que leva a este nó a partir do pai

  Node(char c = '\0') : chave(c), Falha(nullptr) {}
  ~Node() {}

  Map<Node *> filhos;
  Node *Falha;
  vector<string> Palavras; // palavra associada ao nó

  bool temFilho(char key) { return this->filhos.contem(key); }

  Node *getFilho(char key) {
    if (this->filhos.contem(key)) {
      return this->filhos.obter(key);
    }
    return nullptr;
  }

  bool setFilho(char key, Node &node) {
    node.chave = key; // define a chave do filho
    this->filhos.definir(key, &node);
    return true;
  }

  vector<Node *> getFilhos() {
    vector<Node *> filhosList;
    for (size_t i = 0; i < 256; ++i) {
      if (this->filhos.contem(i)) {
        filhosList.push_back(this->filhos.obter(i));
      }
    }
    return filhosList;
  }

  vector<char> getChavesFilhos() {
    vector<char> chaves;
    for (size_t i = 0; i < 256; ++i) {
      if (this->filhos.contem(i)) {
        chaves.push_back(static_cast<char>(i));
      }
    }
    return chaves;
  }

  void alocarPalavra(string palavra) { this->Palavras.push_back(palavra); }
  vector<string> obterPalavras() { return this->Palavras; }
};

#endif // NODE_H
