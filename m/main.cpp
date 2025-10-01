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

  Btree *b = new Btree(3);

  b->insert(parseKey("4"));
  b->insert(parseKey("28"));
  b->insert(parseKey("22"));
  b->insert(parseKey("19"));
  b->insert(parseKey("2"));
  b->insert(parseKey("20"));
  b->insert(parseKey("9"));
  b->insert(parseKey("23"));
  b->insert(parseKey("29"));
  b->insert(parseKey("25"));
  b->insert(parseKey("30"));
  b->insert(parseKey("3"));
  b->insert(parseKey("31"));
  b->insert(parseKey("16"));
  b->insert(parseKey("100"));
  b->insert(parseKey("7"));
  b->insert(parseKey("1"));

  b->print();

  return 0;
}
