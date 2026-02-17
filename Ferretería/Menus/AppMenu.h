#pragma once

#include "Menu.h"

#include "VentaMenu.h"
#include "CompraMenu.h"
#include "ClienteMenu.h"
#include "EmpleadoMenu.h"
#include "ProveedorMenu.h"
#include "AlmacenMenu.h"
#include "CategoriaMenu.h"
#include "EmpresaMenu.h"
#include "InformeMenu.h"
#include "BackupMenu.h"

class AppMenu: public Menu{
 public:
    AppMenu();
    void mostrarOpciones();
  protected:

    void ejecutarOpcion(int opcion);

    VentaMenu _ventaMenu;
    CompraMenu _compraMenu;
    ClienteMenu _clienteMenu;
    EmpleadoMenu _empleadoMenu;
    ProveedorMenu _proveedorMenu;
    AlmacenMenu _almacenMenu;
    CategoriaMenu _categoriaMenu;
    EmpresaMenu _empresaMenu;
    InformeMenu _informeMenu;
    BackupMenu _backupMenu;
};
