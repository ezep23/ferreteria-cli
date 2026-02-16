#pragma once
#include "VentaManager.h"
#include "AlmacenManager.h"
#include "CategoriaManager.h"
#include "CompraManager.h"
#include "DetalleVentaManager.h"
#include "ClienteManager.h"

class InformeManager{
  public:
    InformeManager();

    void recaudacionMensual();
    void recaudacionMensualCategoria();
    void numeroVentasMensualCategoria();
    void recaudacionAnual();
    void recaudacionAnualCategoria();
    void numeroVentasAnualCategoria();
    void numeroProductosVendidosCategoria();
    void numeroProductosProveeedor();
    void ventasPorEmpleado();
    void comprasPorEmpleado();
    void listarBajoStock();

  private:
    DetalleVentaManager _detalleManager;
    ClienteManager _clienteManager;
    VentaManager _ventaManager;
    CompraManager _compraManager;
    AlmacenManager _almacenManager;
    CategoriaManager _categoriaManager;
};
