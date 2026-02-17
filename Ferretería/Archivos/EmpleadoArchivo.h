#pragma once
#include <string>
#include "../Entidades/Empleado.h"

class EmpleadoArchivo{
  public:
    EmpleadoArchivo(std::string nombreArchivo = "Empleados.dat");
    bool guardar(const Empleado &reg);
    bool guardar(int pos, const Empleado &reg);

    int buscarID(int id);
    Empleado leer(int pos);

    bool eliminar(int pos);

    int leerTodos(Empleado regs[], int cantidad);
    int getCantidadRegistros();
    int getNuevoID();

    void crearBackup();
    void cargarBackup();
  private:
    std::string _nombreArchivo;
};
