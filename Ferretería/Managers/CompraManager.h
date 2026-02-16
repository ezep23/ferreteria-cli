#pragma once
#include "../Archivos/CompraArchivo.h"
#include "../Archivos/EmpleadoArchivo.h"
#include "EmpleadoManager.h"

class CompraManager
{
  public:
    CompraManager();

    int cargar();
    bool guardar(int pos, Transaccion reg);

    int buscarPosicion(int id);
    Transaccion traerRegistro(int pos);

    int obtenerNumeroRegistros();
    void comprasPorEmpleado();

    void mostrar();
    void mostrar(int id);

    void mostrarOrdenadasUltimaCompra();
    void mostrarOrdenadasPrimeraCompra();

    void modificar();
    void eliminar();

    void mostrarCompraCompleta(const Transaccion &reg);
  private:
    EmpleadoManager _empleadoManager;
    EmpleadoArchivo _repoEmpleado;
    CompraArchivo _repo;
};
