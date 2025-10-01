#include "BNode.h"
#include "Btree.h"
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  BNode bnode(true);
  std::cout << "cero:\n";
  // bnode.print();

  bnode.insert(parseKey("a"));
  std::cout << "uno:\n";
  bnode.print();

  bnode.insert(parseKey("a"));
  bnode.insert(parseKey("b"));
  bnode.insert(parseKey("d"));
  bnode.insert(parseKey("e"));
  std::cout << "dos:\n";
  bnode.print();

  bnode.insert(parseKey("c"));
  bnode.insert(parseKey("100"));

  std::cout << "tres:\n";
  bnode.print();

  std::cout << "el nro 100: " << bnode.exists(parseKey("100"));

  std::cout << "\n\n\n\nnext:\n\n";

  Btree *b = new Btree(4);

  b->insert(parseKey("a"));
  // BNode *node = new BNode(true, nullptr);
  b->insert(parseKey("b"));
  b->insert(parseKey("d"));
  b->insert(parseKey("e"));
  b->insert(parseKey("f"));

  b->print();

  return 0;
}
