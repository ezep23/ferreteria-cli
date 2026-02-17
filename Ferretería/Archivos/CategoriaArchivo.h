#pragma once
#include <string>
#include "../Entidades/Categoria.h"

class CategoriaArchivo{
  public:
    CategoriaArchivo(std::string nombreArchivo = "Categorias.dat");
    bool guardar(const Categoria &reg);
    bool guardar(int pos, const Categoria &reg);

    int buscarID(int id);
    Categoria leer(int pos);

    bool eliminar(int pos);

    int leerTodos(Categoria regs[], int cantidad);
    int getCantidadRegistros();
    int getNuevoID();

    void crearBackup();
    void cargarBackup();
  private:
    std::string _nombreArchivo;
};
