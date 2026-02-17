#pragma once
#include "../Archivos/DetalleVentaArchivo.h"
#include "AlmacenManager.h"

class DetalleVentaManager
{
  public:
    DetalleVentaManager();

    int obtenerNumeroRegistros();
    int buscarPosicion(int id);
    DetalleTransaccion traerRegistro(int pos);

    float cargar(int id);

    void mostrar();
    void mostrar(int id);
    void mostrarDetallesTransaccion(int idTransaccion);

    void modificar();
    void eliminar();

    float obtenerMontoCategoria(int idTrans, int idCat);
    int obtenerCantidadCategoria(int idTrans, int idCat);
    int obtenerCantidadProductos(int idCliente);

    void crearBackup();
    void cargarBackup();

    bool validarExisteTransaccion(int idTransaccion);
    bool validarDetallePerteneceTransaccion(int idDetalle, int idTransaccion);

    void mostrarDetalleCompleto(const DetalleTransaccion &reg);
  private:
    DetalleVentaArchivo _repo;
    AlmacenManager _almacenManager;
};
