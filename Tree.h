#ifndef TREE_H
#define TREE_H

#include <algorithm> // max
#include <iostream>
#include <string>

using namespace std;

struct Node {
  int valor;   // puede ser número o char (ASCII)
  bool isChar; // true = es char, false = es int
  Node *izq;
  Node *der;
  int altura;

  Node(int v, bool isC) {
    valor = v;
    isChar = isC;
    izq = der = nullptr;
    altura = 1;
  }

  // Para imprimir correctamente
  string getValue() const {
    if (isChar)
      return string(1, (char)valor);
    return to_string(valor);
  }
};

class Tree {
private:
  Node *raiz;

  // Funciones auxiliares
  int altura(Node *n);
  int factorEquilibrio(Node *n);
  Node *rotacionDerecha(Node *y);
  Node *rotacionIzquierda(Node *x);

  int comparar(Node *a, Node *b);

  Node *insertar(Node *nodo, int valor, bool isChar);
  Node *eliminar(Node *nodo, int valor, bool isChar);
  Node *minimo(Node *nodo);
  bool buscar(Node *nodo, int valor, bool isChar);
  void preorder(Node *nodo);
  void printTree(Node *nodo, string prefix, bool isLeft);

public:
  Tree();
  void insertar(int valor);
  void insertar(char c);
  void eliminar(int valor);
  void eliminar(char c);
  bool buscar(int valor);
  bool buscar(char c);
  void preorder();
  void printTree(); // imprime en estilo directorios
};

#endif
