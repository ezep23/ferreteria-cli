
#include <iostream>
using namespace std;

#include "../Utils.h"
#include "VentasManager.h"

VentasManager::VentasManager(){

}

void VentasManager::cargarVenta(){
    int idT=0;
    float total=0;

    idT = _ventaManager.cargar();

    if (idT == 0) {
        cout << "NO SE PUDO CONTINUAR";
        return;
    }

    total = _detalleManager.cargar(idT);

    int pos = _ventaManager.buscarPosicion(idT);

    Transaccion reg = _ventaManager.traerRegistro(pos);
    reg.setMontoTotal(total);

    if(_ventaManager.guardar(pos, reg)){
        cout << "VENTA COMPLETADA CON EXITO!" << endl;
    }
}

void VentasManager::mostrarVentas(){
    int cantidadVentas = _ventaManager.obtenerNumeroRegistros();
    int cantidadDetalles = _detalleManager.obtenerNumeroRegistros();

    for (int i = 0; i < cantidadVentas; i++) {

        Transaccion ventaActual = _ventaManager.traerRegistro(i);

        if (ventaActual.getEstado()) {
            _ventaManager.mostrarVentaCompleta(ventaActual);

            for (int j = 0; j < cantidadDetalles; j++) {


                DetalleTransaccion detalleActual = _detalleManager.traerRegistro(j);

                if (ventaActual.getIdTransaccion() == detalleActual.getIdTransaccion()) {
                    _detalleManager.mostrarDetalleCompleto(detalleActual);
                }

            }
        }
    }
}

void VentasManager::mostrarVenta(){
    int id;

    cout << "Ingrese el ID de la venta: ";
    id = pedirEnteroValido();

    if(id < 1){
        cout << "ESE ID NO ES POSIBLE";
        return;
    }

    _ventaManager.mostrar(id);
    _detalleManager.mostrar(id);
}

void VentasManager::modificarVenta(){
}

void VentasManager::mostrarOrdenadasUltimaVenta(){
    _ventaManager.mostrarOrdenadasPrimeraVenta();
}
void VentasManager::mostrarOrdenadasPrimeraVenta(){
    _ventaManager.mostrarOrdenadasUltimaVenta();
}

void VentasManager::eliminarVenta(){
    int id;

    cout << "ATENCIÓN SE ELIMINARA LA VENTA COMO SUS DETALLES" << endl;
    cout << "Ingrese el ID de la transacción (0 - Para salir): ";
    id = pedirEnteroValido();

    if(id <= 0){
        return;
    }

    /// NI ME ACUERDO COMO FUNCIONABA ESTO
    _detalleManager.eliminar();
    _ventaManager.eliminar();
}



