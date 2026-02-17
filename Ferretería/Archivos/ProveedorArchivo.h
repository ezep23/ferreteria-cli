#pragma once
#include <string>
#include "../Entidades/Proveedor.h"

class ProveedorArchivo{
  public:
    ProveedorArchivo(std::string nombreArchivo = "Proveedores.dat");
    bool guardar(const Proveedor &reg);
    bool guardar(int pos, const Proveedor &reg);

    int buscarID(int id);
    Proveedor leer(int pos);

    bool eliminar(int pos);

    int leerTodos(Proveedor regs[], int cantidad);
    int getCantidadRegistros();
    int getNuevoID();

    void crearBackup();
    void cargarBackup();
  private:
    std::string _nombreArchivo;
};
