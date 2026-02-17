#pragma once

#include "AlmacenManager.h"
#include "CategoriaManager.h"
#include "ClienteManager.h"
#include "CompraManager.h"
#include "DetalleCompraManager.h"
#include "VentaManager.h"
#include "DetalleVentaManager.h"
#include "EmpleadoManager.h"
#include "EmpresaManager.h"
#include "ProveedorManager.h"

class BackupManager{
  public:
    BackupManager();

    void crearBackupGeneral();
    void cargarBackupGeneral();

    void crearBackupProductos();
    void crearBackupCategorias();
    void crearBackupClientes();
    void crearBackupCompras();
    void crearBackupDetallesCompras();
    void crearBackupDetallesVentas();
    void crearBackupVentas();
    void crearBackupEmpleado();
    void crearBackupEmpresa();
    void crearBackupProveedor();

    void cargarBackupProductos();
    void cargarBackupCategorias();
    void cargarBackupClientes();
    void cargarBackupCompras();
    void cargarBackupDetallesCompras();
    void cargarBackupDetallesVentas();
    void cargarBackupVentas();
    void cargarBackupEmpleado();
    void cargarBackupEmpresa();
    void cargarBackupProveedor();

  private:
    AlmacenManager _almacenManager;
    CategoriaManager _categoriaManager;
    ClienteManager _clienteManager;
    CompraManager _compraManager;
    DetalleVentaManager _detalleVentaManager;
    DetalleCompraManager _detalleCompraManager;
    VentaManager _ventaManager;
    EmpleadoManager _empleadoManager;
    EmpresaManager _empresaManager;
    ProveedorManager _proveedorManager;
};
