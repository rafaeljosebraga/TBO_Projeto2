#ifndef TRIE_H
#define TRIE_H

#include "Hash.h"
#include "Node.h"
#include <string>

class Trie {
public:
  Trie();
  ~Trie();

  void insert(const std::string &word);
  bool search(const std::string &word) const;
  bool startsWith(const std::string &prefix) const;

private:
  struct TrieNode {
    Hash<TrieNode *> children;
    bool isEndOfWord;
    TrieNode();
    ~TrieNode();
  };
  TrieNode *root;
};

#endif // TRIE_H
