#include "Tree.h"

// Constructor
Tree::Tree() { raiz = nullptr; }

// --- Auxiliares ---
int Tree::altura(Node *n) { return (n == nullptr) ? 0 : n->altura; }

int Tree::factorEquilibrio(Node *n) {
  return (n == nullptr) ? 0 : altura(n->izq) - altura(n->der);
}

// Comparación según reglas: num < mayus < minus
int Tree::comparar(Node *a, Node *b) {
  bool aIsNum = !a->isChar;
  bool bIsNum = !b->isChar;

  if (aIsNum && bIsNum)
    return a->valor - b->valor;
  if (aIsNum && b->isChar)
    return -1; // num < char
  if (a->isChar && bIsNum)
    return 1; // char > num

  // Ambos char → mayus < minus (ASCII lo respeta: 'A'=65 < 'a'=97)
  return a->valor - b->valor;
}

// Rotaciones
Node *Tree::rotacionDerecha(Node *y) {
  Node *x = y->izq;
  Node *T2 = x->der;

  x->der = y;
  y->izq = T2;

  y->altura = max(altura(y->izq), altura(y->der)) + 1;
  x->altura = max(altura(x->izq), altura(x->der)) + 1;

  return x;
}

Node *Tree::rotacionIzquierda(Node *x) {
  Node *y = x->der;
  Node *T2 = y->izq;

  y->izq = x;
  x->der = T2;

  x->altura = max(altura(x->izq), altura(x->der)) + 1;
  y->altura = max(altura(y->izq), altura(y->der)) + 1;

  return y;
}

// --- Insertar ---
Node *Tree::insertar(Node *nodo, int valor, bool isChar) {
  if (nodo == nullptr)
    return new Node(valor, isChar);

  Node temp(valor, isChar);
  int cmp = comparar(&temp, nodo);

  if (cmp < 0)
    nodo->izq = insertar(nodo->izq, valor, isChar);
  else if (cmp > 0)
    nodo->der = insertar(nodo->der, valor, isChar);
  else
    return nodo; // no duplicados

  nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));
  int fe = factorEquilibrio(nodo);

  // Casos de balanceo
  if (fe > 1 && comparar(&temp, nodo->izq) < 0)
    return rotacionDerecha(nodo);

  if (fe < -1 && comparar(&temp, nodo->der) > 0)
    return rotacionIzquierda(nodo);

  if (fe > 1 && comparar(&temp, nodo->izq) > 0) {
    nodo->izq = rotacionIzquierda(nodo->izq);
    return rotacionDerecha(nodo);
  }

  if (fe < -1 && comparar(&temp, nodo->der) < 0) {
    nodo->der = rotacionDerecha(nodo->der);
    return rotacionIzquierda(nodo);
  }

  return nodo;
}

// --- Mínimo ---
Node *Tree::minimo(Node *nodo) {
  Node *actual = nodo;
  while (actual->izq != nullptr)
    actual = actual->izq;
  return actual;
}

// --- Eliminar ---
Node *Tree::eliminar(Node *nodo, int valor, bool isChar) {
  if (nodo == nullptr)
    return nodo;

  Node temp(valor, isChar);
  int cmp = comparar(&temp, nodo);

  if (cmp < 0)
    nodo->izq = eliminar(nodo->izq, valor, isChar);
  else if (cmp > 0)
    nodo->der = eliminar(nodo->der, valor, isChar);
  else {
    if (nodo->izq == nullptr || nodo->der == nullptr) {
      Node *temp = nodo->izq ? nodo->izq : nodo->der;
      if (temp == nullptr) {
        temp = nodo;
        nodo = nullptr;
      } else {
        *nodo = *temp;
      }
      delete temp;
    } else {
      Node *temp = minimo(nodo->der);
      nodo->valor = temp->valor;
      nodo->isChar = temp->isChar;
      nodo->der = eliminar(nodo->der, temp->valor, temp->isChar);
    }
  }

  if (nodo == nullptr)
    return nodo;

  nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));
  int fe = factorEquilibrio(nodo);

  if (fe > 1 && factorEquilibrio(nodo->izq) >= 0)
    return rotacionDerecha(nodo);

  if (fe > 1 && factorEquilibrio(nodo->izq) < 0) {
    nodo->izq = rotacionIzquierda(nodo->izq);
    return rotacionDerecha(nodo);
  }

  if (fe < -1 && factorEquilibrio(nodo->der) <= 0)
    return rotacionIzquierda(nodo);

  if (fe < -1 && factorEquilibrio(nodo->der) > 0) {
    nodo->der = rotacionDerecha(nodo->der);
    return rotacionIzquierda(nodo);
  }

  return nodo;
}

// --- Buscar ---
bool Tree::buscar(Node *nodo, int valor, bool isChar) {
  if (nodo == nullptr)
    return false;

  Node temp(valor, isChar);
  int cmp = comparar(&temp, nodo);

  if (cmp == 0)
    return true;
  if (cmp < 0)
    return buscar(nodo->izq, valor, isChar);
  return buscar(nodo->der, valor, isChar);
}

// --- Recorrido Preorden ---
void Tree::preorder(Node *nodo) {
  if (nodo != nullptr) {
    cout << nodo->getValue() << " ";
    preorder(nodo->izq);
    preorder(nodo->der);
  }
}

// --- Imprimir como directorios ---
void Tree::printTree(Node *nodo, string prefix, bool isLeft) {
  if (nodo != nullptr) {
    cout << prefix;

    cout << (isLeft ? "├──" : "└──");

    cout << nodo->getValue() << endl;

    printTree(nodo->izq, prefix + (isLeft ? "│   " : "    "), true);
    printTree(nodo->der, prefix + (isLeft ? "│   " : "    "), false);
  }
}

// --- Métodos públicos ---
void Tree::insertar(int valor) { raiz = insertar(raiz, valor, false); }
void Tree::insertar(char c) { raiz = insertar(raiz, (int)c, true); }

void Tree::eliminar(int valor) { raiz = eliminar(raiz, valor, false); }
void Tree::eliminar(char c) { raiz = eliminar(raiz, (int)c, true); }

bool Tree::buscar(int valor) { return buscar(raiz, valor, false); }
bool Tree::buscar(char c) { return buscar(raiz, (int)c, true); }

void Tree::preorder() {
  preorder(raiz);
  cout << endl;
}

void Tree::printTree() { printTree(raiz, "", false); }
