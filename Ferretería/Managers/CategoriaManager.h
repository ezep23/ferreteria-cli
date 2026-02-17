#pragma once
#include <string>
#include "../Archivos/CategoriaArchivo.h"


class CategoriaManager{
  public:
    CategoriaManager();

    void cargar();
    void mostrar();
    void eliminar();
    void actualizar();

    bool existeCategoria(int id);

    void crearBackup();
    void cargarBackup();

  protected:
    void mostrarLista(const Categoria &reg);
  private:
    CategoriaArchivo _repo;
};
