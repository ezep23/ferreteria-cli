#pragma once
#include <string>
#include "../Entidades/Producto.h"

class ProductoArchivo{
  public:
    ProductoArchivo(std::string nombreArchivo = "Productos.dat");
    bool guardar(const Producto &reg);
    bool guardar(int pos, const Producto &reg);

    int buscarID(int id);
    Producto leer(int pos);

    bool eliminar(int pos);

    int leerTodos(Producto regs[], int cantidad);
    int getCantidadRegistros();
    int getNuevoID();

    void crearBackup();
    void cargarBackup();
  private:
    std::string _nombreArchivo;
};
