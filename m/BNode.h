#ifndef BNODE_H
#define BNODE_H
#include "Key.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
struct BNode {
  std::vector<Key> key;
  bool isLeaf;
  std::vector<BNode *> child;
  BNode *parent;

  BNode(bool isLeaf_, BNode *p) : isLeaf(isLeaf_), parent(p) {};
  BNode(bool isLeaf_) : isLeaf(isLeaf_) {};
  BNode() : isLeaf(false) {};

  bool insert(Key value) {

    // caso si está vacío
    if (key.size() == 0) {
      key.insert(key.begin(), value);
      return true;
    }
    // si ya existe
    if (std::find(key.begin(), key.end(), value) != key.end())
      return false;

    // cc
    auto pos = std::upper_bound(key.begin(), key.end(), value);
    key.insert(pos, value);
    return true;
  }

  bool exists(Key value) {
    return std::find(key.begin(), key.end(), value) != key.end();
  }

  void print() {
    // si esta vacío
    if (key.size() == 0) {
      std::cout << "[]";
      return;
    }
    std::cout << "[";
    for (int i = 0; i < key.size() - 1; i++) {
      std::cout << key[i] << "|";
    }
    std::cout << key[key.size() - 1] << "]" << std::endl;
  }
};

#endif
