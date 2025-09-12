#include "Tree.h"

/*
int main() {
  Tree t;

  // Insertar enteros
  t.insertar(10);
  t.insertar(5);
  t.insertar(20);

  // Insertar caracteres
  t.insertar('A');
  t.insertar('z');
  t.insertar('M');

  cout << "Preorden: ";
  t.preorder();

  cout << "\nÁrbol en forma de directorios:\n";
  t.printTree();

  cout << "\nBuscar 10: " << (t.buscar(10) ? "Sí" : "No") << endl;
  cout << "Buscar 'M': " << (t.buscar('M') ? "Sí" : "No") << endl;

  cout << "\nEliminar 10 y 'A'\n";
  t.eliminar(10);
  t.eliminar('A');

  t.printTree();

  return 0;
}*/

#include <iostream>
#include <limits>

void mostrarMenu() {
  std::cout << "Welcome to the AVL tree implementation\n";
  std::cout << "things to do:\n";
  std::cout << std::endl;
  std::cout << "you currently have a empty tree";
  std::cout << std::endl;
  std::cout << "1. Añadir valores al arbol.";
  std::cout << std::endl;
  std::cout << "2. Show tree.";
  std::cout << std::endl;
  std::cout << "3. Find a value.";
  std::cout << std::endl;
  std::cout << "4. Delete a value";
  std::cout << std::endl;
  std::cout << "5. Show Pre-order.";
  std::cout << std::endl;
  std::cout << "6. Exit";
  std::cout << std::endl;
}

int main() {
  // Menu
  Tree t;
  int option = 0;

  do {
    mostrarMenu();
    std::cin >> option;

    // Validar la entrada
    while (std::cin.fail() || option < 0 || option > 6) {
      std::cin.clear(); // Limpiar el estado de error
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n'); // Ignorar la entrada incorrecta
      std::cout << "Opción no válida. Por favor, selecciona nuevamente: ";
      std::cin >> option;
    }

    switch (option) {
    case 1:
      int value;
      std::cout << "\n\n\nvalor a añadir: ";
      std::cin >> value;
      std::cout << "\n\n Es char?: ";
      bool isChar;
      std::cin >> isChar;
      if (isChar)
        t.insertar((char)value);
      else
        t.insertar(value);
      break;
    case 2:
      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << std::endl;
      t.printTree();
      std::cout << "Presiona Enter para volver al menú...";
      std::cin.ignore(); // Ignorar el salto de línea anterior
      std::cin.get();
      break;

    case 3:
      int v_find;
      std::cout << "\n\n\nvalor a buscar: ";
      std::cin >> v_find;
      std::cout << "\n\n Es char?: ";
      bool v_find_isChar;
      std::cin >> v_find_isChar;
      if (v_find_isChar)
        cout << "\nestá en el arbol? " << (char)v_find << ": "
             << (t.buscar((char)v_find) ? "Sí" : "No") << endl;
      else
        cout << "\nestá en el arbol? " << v_find << ": "
             << (t.buscar(v_find) ? "Sí" : "No") << endl;
      break;

    case 4:
      int value_del;
      std::cout << "\n\n\nvalor a añadir: ";
      std::cin >> value_del;
      std::cout << "\n\n Es char?: ";
      bool isChar_del;
      std::cin >> isChar_del;
      if (isChar_del)
        t.eliminar((char)value_del);
      else
        t.eliminar(value_del);
      break;

    case 5:
      std::cout << "\n\n\nMostrando Preorden: ";
      t.preorder();
      std::cout << "Presiona Enter para volver al menú...";
      std::cin.ignore(); // Ignorar el salto de línea anterior
      std::cin.get();
      break;
    }

  } while (option != 6);

  return 0;
}
