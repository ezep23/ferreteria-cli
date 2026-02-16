#include <iostream>
using namespace std;

#include "EmpleadoMenu.h"

EmpleadoMenu::EmpleadoMenu(){
  _cantidadOpciones = 8;
}

void EmpleadoMenu::mostrarOpciones(){
  cout << "--- MENU EMPLEADOS ---" << endl;
  cout << "1 - CARGAR " << endl;
  cout << "2 - MOSTRAR " << endl;
  cout << "3 - ACTUALIZAR " << endl;
  cout << "4 - ELIMINAR " << endl;
  cout << "----------------------" << endl;
  cout << "5 - MOSTRAR POR NOMBRES A-Z" << endl;
  cout << "6 - MOSTRAR POR NOMBRES Z-A" << endl;
  cout << "7 - MOSTRAR POR APELLIDOS A-Z" << endl;
  cout << "8 - MOSTRAR POR APELLIDOS Z-A" << endl;
  cout << "---------------------------------" << endl;
  cout << "0 - SALIR" << endl;
  cout << "--------------------"<<endl;
}

void EmpleadoMenu::ejecutarOpcion(int opcion){
  switch(opcion){
  case 1:
    _empleadoManager.cargar();
  break;
  case 2:
    _empleadoManager.mostrar();
  break;
  case 3:
    _empleadoManager.actualizar();
  break;
  case 4:
    _empleadoManager.eliminar();
  break;
  case 5:
    _empleadoManager.mostrarNombresAZ();
  break;
  case 6:
    _empleadoManager.mostrarNombresZA();
  break;
  case 7:
    _empleadoManager.mostrarApellidosAZ();
  break;
  case 8:
    _empleadoManager.mostrarApellidosZA();
  break;
  }
}
