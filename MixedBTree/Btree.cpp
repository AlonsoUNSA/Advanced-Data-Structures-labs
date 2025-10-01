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

  // encontrar la llave del medio
  int midIndex = node->key.size() / 2;
  Key midKey = node->key[midIndex];

  // nuevo nodo (derecha)
  BNode *newNode = new BNode(node->isLeaf, node->parent);
  newNode->key.resize(node->key.size() - midIndex - 1);
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

std::pair<BNode*, int> Btree::search(BNode *root_, Key k) {

  // tamaño cero
  if (root_->key.size() == 0) {
    return {nullptr, -1};
  }

  // si está en el nodo actual
  auto pos = std::find(root_->key.begin(), root_->key.end(), k);
  if (pos != root_->key.end()) {
    int idx = pos - root_->key.begin();
    return {root_, idx};

    // si no está en el nodo actual
  } else if (root_->isLeaf) {
    return {nullptr, -1};
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

// Métodos auxiliares para remove

int Btree::indexInParent(BNode* node) {
    if (!node->parent) return -1;
    for (int i = 0; i < node->parent->child.size(); ++i) {
        if (node->parent->child[i] == node) return i;
    }
    return -1;
}

BNode* Btree::predecessorLeaf(BNode* node, int idx) {
    BNode* cur = node->child[idx];
    while (!cur->isLeaf) {
        cur = cur->child.back();
    }
    return cur;
}

bool Btree::borrowFromLeft(BNode* node, int posInParent) {
    BNode* parent = node->parent;
    BNode* left = parent->child[posInParent - 1];
    if ((int)left->key.size() > min_keys) {
        // Mover clave del padre al nodo
        node->key.insert(node->key.begin(), parent->key[posInParent - 1]);
        // Mover clave del hermano izquierdo al padre
        parent->key[posInParent - 1] = left->key.back();
        left->key.pop_back();
        if (!left->isLeaf) {
            BNode* moved = left->child.back();
            left->child.pop_back();
            node->child.insert(node->child.begin(), moved);
            moved->parent = node;
        }
        return true;
    }
    return false;
}

bool Btree::borrowFromRight(BNode* node, int posInParent) {
    BNode* parent = node->parent;
    BNode* right = parent->child[posInParent + 1];
    if ((int)right->key.size() > min_keys) {
        node->key.push_back(parent->key[posInParent]);
        parent->key[posInParent] = right->key.front();
        right->key.erase(right->key.begin());
        if (!right->isLeaf) {
            BNode* moved = right->child.front();
            right->child.erase(right->child.begin());
            node->child.push_back(moved);
            moved->parent = node;
        }
        return true;
    }
    return false;
}

void Btree::mergeWithLeft(BNode* node, int posInParent) {
    BNode* parent = node->parent;
    BNode* left = parent->child[posInParent - 1];
    left->key.push_back(parent->key[posInParent - 1]);
    for (auto& k : node->key) left->key.push_back(k);
    if (!node->isLeaf) {
        for (auto c : node->child) {
            left->child.push_back(c);
            c->parent = left;
        }
    }
    parent->key.erase(parent->key.begin() + (posInParent - 1));
    parent->child.erase(parent->child.begin() + posInParent);
    node->child.clear();
    delete node;
    fixUnderflow(parent);
}

void Btree::mergeWithRight(BNode* node, int posInParent) {
    BNode* parent = node->parent;
    BNode* right = parent->child[posInParent + 1];
    node->key.push_back(parent->key[posInParent]);
    for (auto& k : right->key) node->key.push_back(k);
    if (!right->isLeaf) {
        for (auto c : right->child) {
            node->child.push_back(c);
            c->parent = node;
        }
    }
    parent->key.erase(parent->key.begin() + posInParent);
    parent->child.erase(parent->child.begin() + (posInParent + 1));
    right->child.clear();
    delete right;
    fixUnderflow(parent);
}

void Btree::fixUnderflow(BNode* node) {
    if (node == root) {
        if (node->key.empty() && !node->isLeaf) {
            BNode* tmp = root;
            root = root->child[0];
            root->parent = nullptr;
            tmp->child.clear();
            delete tmp;
        }
        return;
    }
    if ((int)node->key.size() >= min_keys) return;
    BNode* parent = node->parent;
    int pos = indexInParent(node);
    if (pos - 1 >= 0) {
        if (borrowFromLeft(node, pos)) return;
    }
    if (pos + 1 < (int)parent->child.size()) {
        if (borrowFromRight(node, pos)) return;
    }
    if (pos - 1 >= 0) {
        mergeWithLeft(node, pos);
    } else {
        mergeWithRight(node, pos);
    }
}

void Btree::remove(Key k) {
    if (!root) {
        std::cout << "El árbol está vacío\n";
        return;
    }
    auto p = search(root, k);
    if (!p.first) {
        std::cout << "Clave no encontrada\n";
        return;
    }
    BNode* node = p.first;
    int idx = p.second;
    if (node->isLeaf) {
        node->key.erase(node->key.begin() + idx);
        fixUnderflow(node);
    } else {
        BNode* predLeaf = predecessorLeaf(node, idx);
        Key predKey = predLeaf->key.back();
        node->key[idx] = predKey;
        predLeaf->key.pop_back();
        fixUnderflow(predLeaf);
    }
}
