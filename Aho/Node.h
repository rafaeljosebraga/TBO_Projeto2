#ifndef NODE_H
#define NODE_H

#include "Hash.h"
#include "Map.h"
#include <cstddef>
#include <optional>

class Node {
public:
  Node();
  ~Node();
  Map<Node *> filhos;
  Node *Falha;
  bool isEndOfWord;
  // definir set()

  bool temFilho(char key) { return this->filhos.contem(key); }

  Node *getFilho(char key) {
    if (this->filhos.contem(key)) {
      return this->filhos.obter(key);
    }
    return nullptr;
  }

  bool setFilho(char key, Node &node) {
    this->filhos.definir(key, &node);
    return true;
  }

  void configurarEstado(bool isEnd) { this->isEndOfWord = isEnd; }
};

#endif // NODE_H
