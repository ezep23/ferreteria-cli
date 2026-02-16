#pragma once
#include "VentaManager.h"
#include "DetalleVentaManager.h"

class VentasManager{
  public:
    VentasManager();

    void cargarVenta();
    void mostrarVentas();
    void mostrarVenta();
    void modificarVenta();
    void eliminarVenta();

    void mostrarOrdenadasUltimaVenta();
    void mostrarOrdenadasPrimeraVenta();

  private:
    VentaManager _ventaManager;
    DetalleVentaManager _detalleManager;
};
