#ifndef BTREE_H
#define BTREE_H
#include "BNode.h"
#include <bits/stdc++.h>

class Btree {
private:
  BNode *root;
  const int max_keys;
  const int min_keys;

  void splitNode(BNode *node);
  void insertOnLeaf(BNode *node, Key k);

  // Métodos auxiliares para remove
  int indexInParent(BNode* node);
  BNode* predecessorLeaf(BNode* node, int idx);
  bool borrowFromLeft(BNode* node, int posInParent);
  bool borrowFromRight(BNode* node, int posInParent);
  void mergeWithLeft(BNode* node, int posInParent);
  void mergeWithRight(BNode* node, int posInParent);
  void fixUnderflow(BNode* node);

public:
  Btree(int max_keys_value);
  std::pair<BNode*, int> search(BNode *root, Key k);
  void insert(Key k);
  void remove(Key k);
  void print();
};
#endif
