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

public:
  Btree(int max_keys_value);
  BNode *search(BNode *root, Key k);
  void insert(Key k);
  void remove(Key k);
  void print();
};
#endif
