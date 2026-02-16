#include <iostream>
using namespace std;

#include "ClienteMenu.h"

ClienteMenu::ClienteMenu(){
  _cantidadOpciones = 8;
}

void ClienteMenu::mostrarOpciones(){
  cout << "--- MENU CLIENTES ---" << endl;
  cout << "1 - CARGAR CLIENTE" << endl;
  cout << "2 - MOSTRAR CLIENTES" << endl;
  cout << "3 - ACTUALIZAR CLIENTE " << endl;
  cout << "4 - ELIMINAR CLIENTE " << endl;
  cout << " --------------------" << endl;
  cout << "5 - LISTAR NOMBRES A-Z" << endl;
  cout << "6 - LISTAR NOMBRES Z-A" << endl;
  cout << "7 - LISTAR APELLIDOS A-Z" << endl;
  cout << "8 - LISTAR APELLIDOS Z-A" << endl;
  cout << "---------------------------------" << endl;
  cout << "0 - SALIR" << endl;
  cout << "--------------------"<<endl;
}

void ClienteMenu::ejecutarOpcion(int opcion){
  switch(opcion){
  case 1:
    _clienteManager.cargar();
  break;
  case 2:
    _clienteManager.mostrar();
  break;
  case 3:
    _clienteManager.actualizar();
  break;
  case 4:
    _clienteManager.eliminar();
  break;
  case 5:
    _clienteManager.mostrarNombresAZ();
  break;
  case 6:
    _clienteManager.mostrarNombresZA();
  break;
  case 7:
    _clienteManager.mostrarApellidosAZ();
  break;
  case 8:
    _clienteManager.mostrarApellidosZA();
  break;
  }
}
