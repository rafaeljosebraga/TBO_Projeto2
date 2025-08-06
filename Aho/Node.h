#ifndef NODE_H
#define NODE_H

#include <unordered_map>

class Node {
public:
  Node();
  ~Node();

  std::unordered_map<char, Node *> children;
  bool isEndOfWord;
};

#endif // NODE_H
