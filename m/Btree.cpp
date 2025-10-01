#include "Btree.h"
#include "BNode.h"
#include <algorithm>
Btree::Btree(int max_v) : max_keys(max_v), min_keys((max_v - 1) / 2) {
  root = new BNode();
}

BNode *Btree::search(BNode *root_, Key k) {

  // tamaño cero
  if (root_->key.size() == 0) {
    return nullptr;
  }

  // si está en el nodo actual
  auto pos = std::find(root_->key.begin(), root_->key.end(), k);
  if (pos != root_->key.end()) {
    return root_;

    // si no está en el nodo actual
  } else if (root_->isLeaf) {
    return nullptr;
  } else {
    auto pos = std::upper_bound(root_->key.begin(), root_->key.end(), k);
    int i_child = pos - root_->key.begin();
    return this->search(root_->child[i_child], k);
  }
}

void Btree::insert(Key k) {
  if (root == nullptr) {
    root = new BNode(true, nullptr);
    root->insert(k);
    return;
  }
}

/*
  Btree(int max_keys_value);
  BNode *search(Key k);
  void insert(Key k);
  void remove(Key k);
  void print();
  */
