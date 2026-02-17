#pragma once
#include "../Archivos/DetalleCompraArchivo.h"
#include "AlmacenManager.h"

class DetalleCompraManager
{
  public:
    DetalleCompraManager();

    int obtenerNumeroRegistros();
    int buscarPosicion(int id);
    DetalleTransaccion traerRegistro(int pos);

    float cargar(int id);

    void mostrar();
    void mostrar(int id);

    void modificar();
    void eliminar();

    void crearBackup();
    void cargarBackup();

    void mostrarDetalleCompleto(const DetalleTransaccion &reg);
  private:
    DetalleCompraArchivo _repo;
    AlmacenManager _almacenManager;
};
