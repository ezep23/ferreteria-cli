#pragma once
#include "../Archivos/EmpleadoArchivo.h"


class EmpleadoManager{
  public:
    EmpleadoManager();

    void cargar();
    void mostrar();
    void mostrar(int id);
    void eliminar();
    void actualizar();

    void mostrarNombresAZ();
    void mostrarNombresZA();
    void mostrarApellidosAZ();
    void mostrarApellidosZA();

    bool existeRegistro(int id);
    int obtenerNumeroProximoID();

    void crearBackup();
    void cargarBackup();

  protected:
    void mostrarLista(const Empleado &reg);
  private:
    EmpleadoArchivo _repo;
};
