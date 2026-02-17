#pragma once
#include "../Archivos/ClienteArchivo.h"

class ClienteManager{
  public:
    ClienteManager();

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
    void mostrarClientesMasCompras();

    void crearBackup();
    void cargarBackup();

  protected:
    void mostrarLista(const Cliente &reg);
  private:
    ClienteArchivo _repo;
};
