#pragma once
#include "../Archivos/ProductoArchivo.h"
#include "ProveedorManager.h"
#include "CategoriaManager.h"
#include "EmpresaManager.h"

class AlmacenManager{
  public:
    AlmacenManager();

    void cargarProducto();
    void mostrarProducto();
    void mostrarProducto(int idCategoria);
    void eliminarProducto();
    void actualizarProducto();

    void listarPorCategoria();
    void listarBajoStock();

    void mostrarNombresAZ();
    void mostrarNombresZA();
    void mostrarPreciosAltoBajo();
    void mostrarPreciosBajoAlto();
    void mostrarStockAltoBajo();
    void mostrarStockBajoAlto();

    int obtenerStock(int id);
    float obtenerPrecio(int id);
    int obtenerCategoriaProducto(int id);

    void numeroProductosProveedor();

    void descontarStock(int id, int cantidad);
    void rellenarStock(int id, int cantidad);

    bool validarID(int id);

    void crearBackup();
    void cargarBackup();

  protected:
    void mostrarLista(const Producto &reg);
  private:
    ProductoArchivo _repo;
    EmpresaManager _empresaManager;
    ProveedorManager _proveedorManager;
    CategoriaManager _categoriaManager;
};
