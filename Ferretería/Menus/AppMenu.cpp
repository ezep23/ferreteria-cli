#include <iostream>
using namespace std;

#include "AppMenu.h"

AppMenu::AppMenu(){
  _cantidadOpciones = 10;
}

void AppMenu::mostrarOpciones(){
    cout << endl;
  cout << "--- MENU PRINCIPAL ---" << endl;
  cout << endl;
  cout << " 1 - VENTAS " << endl;
  cout << " 2 - COMPRAS " << endl;
  cout << " 3 - ALMACEN" << endl;
  cout << " 4 - INFORMES" << endl;
  cout << endl;
  cout << " 5 - CLIENTES" << endl;
  cout << " 6 - EMPLEADOS" << endl;
  cout << " 7 - PROVEEDORES" << endl;
  cout << endl;
  cout << " 8 - CATEGORIAS" <<endl;
  cout << " 9 - EMPRESAS" << endl;
  cout << " 10 - BACKUPS" << endl;
  cout << endl;
  cout << "----------------------" << endl;
  cout << endl;
  cout << " 0 - SALIR" << endl;
  cout << endl;
  cout << "----------------------"<<endl;
}

void AppMenu::ejecutarOpcion(int opcion){
  switch(opcion){
  case 1:
    _ventaMenu.mostrar();
  break;
  case 2:
    _compraMenu.mostrar();
    break;
  case 3:
    _almacenMenu.mostrar();
    break;
  case 4:
    _informeMenu.mostrar();
    break;
  case 5:
    _clienteMenu.mostrar();
    break;
  case 6:
    _empleadoMenu.mostrar();
    break;
  case 7:
    _proveedorMenu.mostrar();
    break;
  case 8:
    _categoriaMenu.mostrar();
    break;
  case 9:
    _empresaMenu.mostrar();
    break;
  case 10:
    _backupMenu.mostrar();
    break;
  }
}
