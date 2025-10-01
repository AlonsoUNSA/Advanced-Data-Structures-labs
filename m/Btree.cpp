#include "Btree.h"
#include "BNode.h"
#include <algorithm>
#include <queue>
#include <vector>
Btree::Btree(int max_v) : max_keys(max_v), min_keys((max_v - 1) / 2) {
  root = new BNode(true, nullptr);
}

void Btree::insertOnLeaf(BNode *node, Key k) { node->insert(k); }

void Btree::splitNode(BNode *node) {
  // [node|mid|newNode]
  std::cout << "splitting node";

  // encontrar la llave del medio
  int midIndex = node->key.size() / 2;
  Key midKey = node->key[midIndex];

  // nuevo nodo (derecha)
  BNode *newNode = new BNode(node->isLeaf, node->parent);
  std::copy(node->key.begin() + midIndex + 1, node->key.end(),
            newNode->key.begin());

  if (!node->isLeaf) {
    for (int i = midIndex + 1; i < node->child.size(); i++) {
      newNode->child.push_back(node->child[i]);
      newNode->child.back()->parent = newNode;
    }
    node->child.resize(midIndex + 1);
  }
  node->key.resize(midIndex);

  // si es raiz
  if (node->parent == nullptr) {
    BNode *newRoot = new BNode(false);
    newRoot->key.push_back(midKey);
    newRoot->child.push_back(node);
    newRoot->child.push_back(newNode);
    node->parent = newRoot;
    newNode->parent = newRoot;
    this->root = newRoot;
  } else {
    BNode *p = node->parent;

    auto it = std::upper_bound(p->key.begin(), p->key.end(), midKey);
    int i = it - p->key.begin();

    p->key.insert(it, midKey);
    p->child.insert(p->child.begin() + i + 1, newNode);

    if ((int)p->key.size() > max_keys) {
      splitNode(p);
    }
  }
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
    // root->key.push_back(k);
    return;
  }
  std::vector<Key> &curr_keys = root->key;

  BNode *curr_node = root;

  // si el BNode está vacío?
  while (!curr_node->isLeaf) {
    if (curr_node->exists(k))
      return;
    auto it = std::upper_bound(curr_node->key.begin(), curr_node->key.end(), k);
    int i = it - curr_node->key.begin();
    curr_node = curr_node->child[i];
  }

  insertOnLeaf(curr_node, k);
  if (curr_node->key.size() > max_keys) {
    splitNode(curr_node);
  }
}

void Btree::print() {
  if (!root)
    return;
  std::queue<BNode *> q;

  q.push(root);
  while (!q.empty()) {
    int nivelSize = q.size();
    for (int i = 0; i < nivelSize; i++) {
      BNode *node = q.front();
      q.pop();

      // imprimir claves;
      node->print();
      std::cout << "  ";

      // encolar hijos si no es hoja
      if (!node->isLeaf) {
        for (BNode *c : node->child) {
          q.push(c);
        }
      }
    }
    std::cout << "\n";
  }
}

/*
  Btree(int max_keys_value);
  BNode *search(Key k);
  void insert(Key k);
  void remove(Key k);
  void print();
  */
