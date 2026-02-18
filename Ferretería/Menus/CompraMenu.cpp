#include <iostream>
using namespace std;

#include "CompraMenu.h"

CompraMenu::CompraMenu(){
  _cantidadOpciones = 7;
}

void CompraMenu::mostrarOpciones(){
  cout << "---------- MENU COMPRA ----------" << endl;
  cout << "1 - CREAR" << endl;
  cout << "2 - MOSTRAR COMPRAS " << endl;
  cout << "3 - MOSTRAR COMPRA " << endl;
  cout << "4 - MODIFICAR " << endl;
  cout << "5 - ELIMINAR" << endl;
  cout << "---------------------------------" << endl;
  cout << "6 - MOSTRAR VENTAS ORDENADAS DESDE LA ULTIMA" << endl;
  cout << "7 - MOSTRAR VENTAS ORDENADAS DESDE LA PRIMERA" << endl;
  cout << "---------------------------------" << endl;
  cout << "0 - SALIR" << endl;
  cout << "---------------------------------" << endl;
}

void CompraMenu::ejecutarOpcion(int opcion){
  switch(opcion){
  case 1:
    _comprasManager.cargarCompra();
  break;
  case 2:
    _comprasManager.mostrarCompras();
  break;
  case 3:
    _comprasManager.mostrarCompra();
    break;
  case 4:
    _comprasManager.modificarCompra();
  break;
  case 5:
    _comprasManager.eliminarCompra();
  break;
  case 6:
    _comprasManager.mostrarOrdenadasUltimaCompra();
  break;
  case 7:
    _comprasManager.mostrarOrdenadasPrimeraCompra();
  break;
  }
}
