#pragma once
#include "CompraManager.h"
#include "DetalleCompraManager.h"

class ComprasManager{
  public:
    ComprasManager();

    void cargarCompra();
    void mostrarCompras();
    void mostrarCompra();
    void modificarCompra();
    void eliminarCompra();

    void mostrarOrdenadasUltimaCompra();
    void mostrarOrdenadasPrimeraCompra();

  private:
    CompraManager _compraManager;
    DetalleCompraManager _detalleManager;
};
