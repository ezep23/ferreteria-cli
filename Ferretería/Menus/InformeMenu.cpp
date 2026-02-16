#include <iostream>
using namespace std;

#include "InformeMenu.h"

InformeMenu::InformeMenu(){
  _cantidadOpciones = 11;
}

void InformeMenu::mostrarOpciones(){
  cout << "--- MENU INFORMES ---------------" << endl;
  cout << "1 - RECAUDACION MENSUAL EN UN ANIO " << endl;
  cout << "2 - RECAUDACION MENSUAL POR CATEGORIA EN UN ANIO" << endl;
  cout << "3 - NUMERO DE PRODUCTOS VENDIDOS MENSUALMENTE POR CATEGORIA" << endl;
  cout << "4 - RECAUDACION ANUAL" << endl;
  cout << "5 - RECAUDACION ANUAL POR CATEGORIA" << endl;
  cout << "6 - NUMERO DE PRODUCTOS VENDIDOS POR CATEGORIA EN UN ANIO" << endl;
  cout << "7 - NUMERO TOTAL DE PRODUCTOS VENDIDOS POR CATEGORIA"<<endl;
  cout << "8 - NUMERO DE PRODUCTOS POR PROVEEDOR" << endl;
  cout << "9 - NUMERO DE VENTAS POR EMPLEADO" << endl;
  cout << "10 - NUMERO DE COMPRAS POR EMPLEADO" << endl;
  cout << "11 - PRODUCTOS BAJO STOCK (MENOS DE 5)"<<endl;
  cout << "---------------------------------" << endl;
  cout << "0 - SALIR" << endl;
  cout << "---------------------------------"<<endl;
}

void InformeMenu::ejecutarOpcion(int opcion){
  switch(opcion){
  case 1:
    _informeManager.recaudacionMensual();
    break;
  case 2:
    _informeManager.recaudacionMensualCategoria();
    break;
  case 3:
    _informeManager.numeroVentasMensualCategoria();
    break;
  case 4:
    _informeManager.recaudacionAnual();
    break;
  case 5:
    _informeManager.recaudacionAnualCategoria();
    break;
  case 6:
    _informeManager.numeroVentasAnualCategoria();
    break;
  case 7:
    _informeManager.numeroProductosVendidosCategoria();
    break;
  case 8:
    _informeManager.numeroProductosProveeedor();
    break;
  case 9:
    _informeManager.ventasPorEmpleado();
    break;
  case 10:
    _informeManager.comprasPorEmpleado();
    break;
  case 11:
    _informeManager.listarBajoStock();
    break;
  }
}
