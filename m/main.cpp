#include "BNode.h"
#include "Key.h"
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

Key parseKey(const string &input) {
  if (input.empty())
    return Key(0);

  // Verificar si es número
  istringstream iss(input);
  int num;
  if (iss >> num && iss.eof()) {
    return Key(num);
  }

  // Si no es número, tomar el primer carácter
  return Key(input[0]);
}
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

  return 0;
}
