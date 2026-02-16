#include <iostream>
using namespace std;

#include "ProveedorMenu.h"

ProveedorMenu::ProveedorMenu(){
  _cantidadOpciones = 8;
}

void ProveedorMenu::mostrarOpciones(){
  cout << "--- MENU PROVEEDORES ---" << endl;
  cout << "1 - CARGAR" << endl;
  cout << "2 - MOSTRAR" << endl;
  cout << "3 - ACTUALIZAR" << endl;
  cout << "4 - ELIMINAR" << endl;
  cout << "------------------------" << endl;
  cout << "5 - LISTAR POR NOMBRES A-Z" << endl;
  cout << "6 - LISTAR POR NOMBRES Z-A" << endl;
  cout << "7 - LISTAR POR APELLIDOS A-Z" << endl;
  cout << "8 - LISTAR POR APELLIDOS Z-A" << endl;
  cout << "---------------------------------" << endl;
  cout << "0 - SALIR" << endl;
  cout << "--------------------"<<endl;
}

void ProveedorMenu::ejecutarOpcion(int opcion){
  switch(opcion){
  case 1:
    _proveedorManager.cargar();
  break;
  case 2:
    _proveedorManager.mostrar();
  break;
  case 3:
    _proveedorManager.actualizar();
  break;
  case 4:
    _proveedorManager.eliminar();
  break;
  case 5:
    _proveedorManager.mostrarNombresAZ();
  break;
  case 6:
    _proveedorManager.mostrarNombresZA();
  break;
  case 7:
    _proveedorManager.mostrarApellidosAZ();
  break;
  case 8:
    _proveedorManager.mostrarApellidosZA();
  break;
  }
}
