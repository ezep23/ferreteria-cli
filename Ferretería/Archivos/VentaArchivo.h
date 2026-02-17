#pragma once
#include <string>
#include "../Entidades/Transaccion.h"

class VentaArchivo{
  public:
    VentaArchivo(std::string nombreArchivo = "Ventas.dat");
    bool guardar(const Transaccion &registro); // guardar al final
    bool guardar(int pos, const Transaccion &registro); // guardar x posición (modificar)

    int buscarID(int id);

    bool eliminar(int pos);

    Transaccion leer(int pos);
    int leerTodos(Transaccion ventas[], int cantidad);

    int getCantidadRegistros();
    int getNuevoID();

    void crearBackup();
    void cargarBackup();
  private:
    std::string _nombreArchivo;
};
