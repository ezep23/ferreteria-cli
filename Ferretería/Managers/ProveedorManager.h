#pragma once
#include "../Archivos/ProveedorArchivo.h"
#include "EmpresaManager.h"


class ProveedorManager{
  public:
    ProveedorManager();

    void cargar();
    void mostrar();
    void eliminar();
    void actualizar();

    void mostrarNombresAZ();
    void mostrarNombresZA();
    void mostrarApellidosAZ();
    void mostrarApellidosZA();
    void mostrarNombreComercialAZ();
    void mostrarNombreComercialZA();

    bool existeProveedor(int id);
    int obtenerNumeroProximoID();

    void crearBackup();
    void cargarBackup();

    void mostrar(int idEmpresa);
  protected:
    void mostrarLista(const Proveedor &reg);
  private:
    ProveedorArchivo _repo;
    EmpresaManager _empresaManager;
};
