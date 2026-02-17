#include <iostream>
using namespace std;

#include "BackupManager.h"

BackupManager::BackupManager(){

}

void BackupManager::crearBackupGeneral(){
    _almacenManager.crearBackup();
    _categoriaManager.crearBackup();
    _clienteManager.crearBackup();
    _compraManager.crearBackup();
    _detalleVentaManager.crearBackup();
    _detalleCompraManager.crearBackup();
    _ventaManager.crearBackup();
    _empleadoManager.crearBackup();
    _empresaManager.crearBackup();
    _proveedorManager.crearBackup();
}

void BackupManager::cargarBackupGeneral(){
    _almacenManager.cargarBackup();
    _categoriaManager.cargarBackup();
    _clienteManager.cargarBackup();
    _compraManager.cargarBackup();
    _detalleVentaManager.cargarBackup();
    _detalleCompraManager.cargarBackup();
    _ventaManager.cargarBackup();
    _empleadoManager.cargarBackup();
    _empresaManager.cargarBackup();
    _proveedorManager.cargarBackup();
}

void BackupManager::crearBackupProductos(){
    _almacenManager.crearBackup();
}
void BackupManager::crearBackupCategorias(){
    _categoriaManager.crearBackup();
}
void BackupManager::crearBackupClientes(){
    _clienteManager.crearBackup();
}
void BackupManager::crearBackupCompras(){
    _compraManager.crearBackup();
}
void BackupManager::crearBackupDetallesCompras(){
    _detalleCompraManager.crearBackup();
}
void BackupManager::crearBackupDetallesVentas(){
    _detalleVentaManager.crearBackup();
}
void BackupManager::crearBackupVentas(){
    _ventaManager.crearBackup();
}
void BackupManager::crearBackupEmpleado(){
    _empleadoManager.crearBackup();
}
void BackupManager::crearBackupEmpresa(){
    _empresaManager.crearBackup();
}
void BackupManager::crearBackupProveedor(){
    _proveedorManager.crearBackup();
}

void BackupManager::cargarBackupProductos(){
    _almacenManager.cargarBackup();
}
void BackupManager::cargarBackupCategorias(){
    _categoriaManager.cargarBackup();
}
void BackupManager::cargarBackupClientes(){
    _clienteManager.cargarBackup();
}
void BackupManager::cargarBackupCompras(){
    _compraManager.cargarBackup();
}
void BackupManager::cargarBackupDetallesCompras(){
    _detalleCompraManager.cargarBackup();
}
void BackupManager::cargarBackupDetallesVentas(){
    _detalleVentaManager.cargarBackup();
}
void BackupManager::cargarBackupVentas(){
    _ventaManager.cargarBackup();
}
void BackupManager::cargarBackupEmpleado(){
    _empleadoManager.cargarBackup();
}
void BackupManager::cargarBackupEmpresa(){
    _empresaManager.cargarBackup();
}
void BackupManager::cargarBackupProveedor(){
    _proveedorManager.cargarBackup();
}
