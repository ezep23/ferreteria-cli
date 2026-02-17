#include <iostream>
using namespace std;

#include "BackupMenu.h"

BackupMenu::BackupMenu(){
  _cantidadOpciones = 22;
}

void BackupMenu::mostrarOpciones(){
  cout << "-------------- MENU BACKUPS ---------------------" << endl;
  cout << "1 - CREAR BACKUP GENERAL" << endl;
  cout << "2 - CARGAR BACKUP GENERAL" << endl;
  cout << "------------- CREAR BACKUPS INDIVIDUALES --------" << endl;
  cout << "3 - CREAR BACKUP PRODUCTOS" << endl;
  cout << "4 - CREAR BACKUP EMPLEADOS" << endl;
  cout << "5 - CREAR BACKUP CLIENTES" << endl;
  cout << "6 - CREAR BACKUP COMPRAS" << endl;
  cout << "7 - CREAR BACKUP DETALLES DE COMPRAS" << endl;
  cout << "8 - CREAR BACKUP VENTAS" << endl;
  cout << "9 - CREAR BACKUP DETALLES DE VENTAS" << endl;
  cout << "10 - CREAR BACKUP PROVEEDORES" << endl;
  cout << "11 - CREAR BACKUP EMPRESAS" << endl;
  cout << "12 - CREAR BACKUP CATEGORIAS" << endl;
  cout << "--------- CARGAR BACKUPS INDIVIDUALES --------" << endl;
  cout << "13 - CARGAR BACKUP PRODUCTOS" << endl;
  cout << "14 - CARGAR BACKUP EMPLEADOS" << endl;
  cout << "15 - CARGAR BACKUP CLIENTES" << endl;
  cout << "16 - CARGAR BACKUP COMPRAS" << endl;
  cout << "17 - CARGAR BACKUP DETALLES DE COMPRAS" << endl;
  cout << "18 - CARGAR BACKUP VENTAS" << endl;
  cout << "19 - CARGAR BACKUP DETALLES DE VENTAS" << endl;
  cout << "20 - CARGAR BACKUP PROVEEDORES" << endl;
  cout << "21 - CARGAR BACKUP EMPRESAS" << endl;
  cout << "22 - CARGAR BACKUP CATEGORIAS" << endl;
  cout << "---------------------------------------------" << endl;
  cout << "0 - SALIR" << endl;
  cout << "---------------------------------------------" << endl;
}

void BackupMenu::ejecutarOpcion(int opcion){
  switch(opcion){
  case 1:
    _backupManager.crearBackupGeneral();
  break;
  case 2:
    _backupManager.cargarBackupGeneral();
  break;
  case 3:
    _backupManager.crearBackupProductos();
    break;
  case 4:
    _backupManager.crearBackupEmpleado();
    break;
  case 5:
    _backupManager.crearBackupClientes();
    break;
  case 6:
    _backupManager.crearBackupCompras();
    break;
  case 7:
    _backupManager.crearBackupDetallesCompras();
    break;
  case 8:
    _backupManager.crearBackupVentas();
    break;
  case 9:
    _backupManager.crearBackupDetallesVentas();
    break;
  case 10:
    _backupManager.crearBackupProveedor();
    break;
  case 11:
    _backupManager.crearBackupEmpresa();
    break;
  case 12:
    _backupManager.crearBackupCategorias();
    break;
   case 13:
    _backupManager.cargarBackupProductos();
    break;
  case 14:
    _backupManager.cargarBackupEmpleado();
    break;
  case 15:
    _backupManager.cargarBackupClientes();
    break;
  case 16:
    _backupManager.cargarBackupCompras();
    break;
  case 17:
    _backupManager.cargarBackupDetallesCompras();
    break;
  case 18:
    _backupManager.cargarBackupVentas();
    break;
  case 19:
    _backupManager.cargarBackupDetallesVentas();
    break;
  case 20:
    _backupManager.cargarBackupProveedor();
    break;
  case 21:
    _backupManager.cargarBackupEmpresa();
    break;
  case 22:
    _backupManager.cargarBackupCategorias();
    break;
  }
}
