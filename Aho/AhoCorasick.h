
#ifndef AHOCORASICK_H
#define AHOCORASICK_H

#include "Map.h"
#include "Node.h"
#include <queue>
#include <string>
#include <vector>
using namespace std;

class AhoCorasick {
public:
  ~AhoCorasick() { delete this->raiz; }
  AhoCorasick(vector<string> palavras) {
    // Construir a Trie
    this->raiz = new Node();
    Node *atNode = this->raiz;
    for (const auto &palavra : palavras) {
      for (char c : palavra) {
        if (!atNode->temFilho(c)) {
          Node *novoNode = new Node();
          atNode->setFilho(c, *novoNode);
        }
        atNode = atNode->getFilho(c);
      }
      atNode->alocarPalavra(palavra);
      atNode = this->raiz;
    }
    // Colocar Falhas
    this->raiz->Falha = this->raiz;
    queue<Node *> fila;
    for (auto node : this->raiz->getFilhos()) {
      node->Falha = this->raiz;
      fila.push(node);
    }

    while (!fila.empty()) {

      Node *atual = fila.front();
      fila.pop();
      auto nodes = atual->getFilhos();
      auto chaves = atual->getChavesFilhos();
      for (int i = 0; i < nodes.size(); i++) {
        fila.push(nodes[i]);
        auto falha = atual->Falha;
        while (!falha->temFilho(chaves[i]) && falha != this->raiz) {
          falha = falha->Falha;
        }
        nodes[i]->Falha = falha->getFilho(chaves[i]) ? this->raiz : falha;
        auto saidas = nodes[i]->Falha->obterPalavras();
        for (const auto &saida : saidas) {
          nodes[i]->alocarPalavra(saida);
        }
      }
    }
  };

  void buscar(string texto, vector<int> &encontradas,
              vector<string> &palavrasEncontradas) {
    auto estado = this->raiz;
    for (int i = 0; i < texto.size();) {
      char c = texto[i];
      if (estado->temFilho(c)) {
        estado = estado->getFilho(c);
        i++;
        if (!estado->obterPalavras().empty()) {
          auto palavras = estado->obterPalavras();
          for (const auto &palavra : palavras) {
            encontradas.push_back(i - palavra.size());
            palavrasEncontradas.push_back(palavra);
          }
        }
      } else if (estado == this->raiz) {
        i++;
      } else {
        estado = estado->Falha;
      }
    }
  }

  void inserir(const string &palavra);
  void construirFalhas();
  vector<int> buscar(const string &texto);

private:
  Node *raiz; // Raiz da Trie
  // Definição do nó interno será feita depois
};

#endif // AHOCORASICK_H
