#pragma once
#include <string>
#include "../Entidades/DetalleTransaccion.h"

class DetalleCompraArchivo{
  public:
    DetalleCompraArchivo(std::string nombreArchivo = "DetallesCompras.dat");
    bool guardar(const DetalleTransaccion &registro); // guardar al final
    bool guardar(int pos, const DetalleTransaccion &registro); // guardar x posición (modificar)

    int buscarID(int id);

    bool eliminar(int pos);

    DetalleTransaccion leer(int pos);
    int leerTodos(DetalleTransaccion detalles[], int cantidad);

    int getCantidadRegistros();
    int getNuevoID();


    void crearBackup();
    void cargarBackup();
  private:
    std::string _nombreArchivo;
};
