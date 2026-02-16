#include <iostream>
using namespace std;

#include "AlmacenMenu.h"

AlmacenMenu::AlmacenMenu(){
  _cantidadOpciones = 11;
}

void AlmacenMenu::mostrarOpciones(){
  cout << "--------- MENU ALMACEN ----------" << endl;
  cout << "1 - CARGAR PRODUCTO" << endl;
  cout << "2 - MOSTRAR PRODUCTO" << endl;
  cout << "3 - FILTRAR PRODUCTOS POR CATEGORIA" << endl;
  cout << "4 - ACTUALIZAR PRODUCTO" << endl;
  cout << "5 - ELIMINAR PRODUCTO" << endl;
  cout << "---------------------------------" << endl;
  cout << "6 - MOSTRAR POR NOMBRE A-Z" << endl;
  cout << "7 - MOSTRAR POR NOMBRE Z-A" << endl;
  cout << "8 - MOSTRAR DE MENOR A MAYOR STOCK" << endl;
  cout << "9 - MOSTRAR DE MAYOR A MENOR STOCK" << endl;
  cout << "10 - MOSTRAR DE MENOR A MAYOR PRECIO" << endl;
  cout << "11 - MOSTRAR DE MAYOR A MENOR PRECIO" << endl;
  cout << "---------------------------------" << endl;
  cout << "0 - SALIR" << endl;
  cout << "---------------------------------"<<endl;
}

void AlmacenMenu::ejecutarOpcion(int opcion){
  switch(opcion){
  case 1:
    _almacenManager.cargarProducto();
  break;
  case 2:
    _almacenManager.mostrarProducto();
  break;
  case 3:
    _almacenManager.listarPorCategoria();
    break;
  case 4:
    _almacenManager.actualizarProducto();
  break;
  case 5:
    _almacenManager.eliminarProducto();
  break;
  case 6:
    _almacenManager.mostrarNombresAZ();
  break;
  case 7:
    _almacenManager.mostrarNombresZA();
  break;
  case 8:
    _almacenManager.mostrarStockBajoAlto();
  break;
  case 9:
    _almacenManager.mostrarStockAltoBajo();
  break;
  case 10:
    _almacenManager.mostrarPreciosBajoAlto();
  break;
  case 11:
    _almacenManager.mostrarPreciosAltoBajo();
  break;
  }
}
