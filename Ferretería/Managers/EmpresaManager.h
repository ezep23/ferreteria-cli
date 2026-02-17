#pragma once
#include "../Archivos/EmpresaArchivo.h"


class EmpresaManager{
  public:
    EmpresaManager();

    void cargar();
    void mostrar();
    void eliminar();
    void actualizar();

    void mostrarNombreComercialAZ();
    void mostrarNombreComercialZA();

    int retornarIDsNombresOrdenadosAZ();
    int retornarIDsNombresOrdenadosZA();

    int obtenerCantidadRegistros();
    void mostrarNombreEmpresa(int id);
    bool validarEmpresaExiste(int id);

    void crearBackup();
    void cargarBackup();

  protected:
    void mostrarLista(const Empresa &reg);
  private:
    EmpresaArchivo _repo;
};
