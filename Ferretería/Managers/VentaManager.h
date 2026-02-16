#pragma once
#include "../Archivos/VentaArchivo.h"
#include "../Archivos/ClienteArchivo.h"
#include "ClienteManager.h"
#include "EmpleadoManager.h"
#include "DetalleVentaManager.h"

class VentaManager
{
  public:
    VentaManager();

    int cargar();
    bool guardar(int pos, Transaccion reg);

    int buscarPosicion(int id);
    Transaccion traerRegistro(int pos);

    int obtenerNumeroRegistros();

    void recaudacionMensual(int anio);
    void recaudacionMensualCategoria(int anio, int idCat);
    void numeroVentasMensualCategoria(int anio, int idCat);
    void recaudacionAnual();
    void recaudacionAnualCategoria(int idCat);
    void numeroVentasAnualCategoria(int idCat);
    void obtenerNumeroProductosVendidosCategoria(int idCat);
    void ventasPorEmpleado();

    int obtenerNumeroProductosVendidosCliente(int idCliente);

    void mostrar();
    void mostrar(int id);

    void modificar();
    void eliminar();

    void mostrarVentaCompleta(const Transaccion &reg);
  private:
    DetalleVentaManager _detalleManager;
    EmpleadoManager _empleadoManager;
    ClienteManager _clienteManager;
    ClienteArchivo _repoCliente;
    VentaArchivo _repo;
};
