#include <iostream>
using namespace std;

#include "VentaMenu.h"

VentaMenu::VentaMenu(){
  _cantidadOpciones = 7;
}

void VentaMenu::mostrarOpciones(){
  cout << "---------- MENU VENTA -----------" << endl;
  cout << "1 - CREAR" << endl;
  cout << "2 - MOSTRAR VENTAS" << endl;
  cout << "3 - MOSTRAR VENTA" << endl;
  cout << "4 - MODIFICAR" << endl;
  cout << "5 - ELIMINAR" << endl;
  cout << "---------------------------------" << endl;
  cout << "6 - MOSTRAR VENTAS ORDENADAS DESDE LA ULTIMA" << endl;
  cout << "7 - MOSTRAR VENTAS ORDENADAS DESDE LA PRIMERA" << endl;
  cout << "---------------------------------" << endl;
  cout << "0 - SALIR" << endl;
  cout << "---------------------------------" << endl;
}

void VentaMenu::ejecutarOpcion(int opcion){
  switch(opcion){
  case 1:
    _ventasManager.cargarVenta();
  break;
  case 2:
    _ventasManager.mostrarVentas();
  break;
  case 3:
    _ventasManager.mostrarVenta();
    break;
  case 4:
    _ventasManager.modificarVenta();
  break;
  case 5:
    _ventasManager.eliminarVenta();
  break;
  case 6:
    _ventasManager.mostrarOrdenadasUltimaVenta();
  break;
  case 7:
    _ventasManager.mostrarOrdenadasPrimeraVenta();;
  break;
  }
}
