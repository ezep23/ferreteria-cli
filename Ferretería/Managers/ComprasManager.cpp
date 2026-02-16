#include <iostream>
using namespace std;

#include "ComprasManager.h"

ComprasManager::ComprasManager(){

}

void ComprasManager::cargarCompra(){
    int idT=0;
    float total=0;

    idT = _compraManager.cargar();

    if (idT == 0) {
        cout << "NO SE PUDO CONTINUAR";
        return;
    }

    total = _detalleManager.cargar(idT);

    int pos = _compraManager.buscarPosicion(idT);

    Transaccion reg = _compraManager.traerRegistro(pos);
    reg.setMontoTotal(total);

    if(_compraManager.guardar(pos, reg)){
        cout << "COMPRA COMPLETADA CON EXITO!" << endl;
    }
}

void ComprasManager::mostrarCompras(){
    int cantidadCompras = _compraManager.obtenerNumeroRegistros();
    int cantidadDetalles = _detalleManager.obtenerNumeroRegistros();

    for (int i = 0; i < cantidadCompras; i++) {

        Transaccion compraActual = _compraManager.traerRegistro(i);

        if (compraActual.getEstado()) {
            _compraManager.mostrarCompraCompleta(compraActual);

            for (int j = 0; j < cantidadDetalles; j++) {


                DetalleTransaccion detalleActual = _detalleManager.traerRegistro(j);

                if (compraActual.getIdTransaccion() == detalleActual.getIdTransaccion()) {
                    _detalleManager.mostrarDetalleCompleto(detalleActual);
                }

            }
        }
    }
}

void ComprasManager::mostrarCompra(){
    int id;

    cout << "Ingrese el ID de la compra: ";
    cin >> id;

    if(id < 1){
        cout << "ESE ID NO ES POSIBLE";
        return;
    }

    _compraManager.mostrar(id);
    _detalleManager.mostrar(id);
}

void ComprasManager::modificarCompra(){
}

void ComprasManager::mostrarOrdenadasUltimaCompra(){
    _compraManager.mostrarOrdenadasPrimeraCompra();
}
void ComprasManager::mostrarOrdenadasPrimeraCompra(){
    _compraManager.mostrarOrdenadasUltimaCompra();
}

void ComprasManager::eliminarCompra(){
    int id;

    cout << "ATENCIÓN SE ELIMINARA LA COMPRA COMO SUS DETALLES" << endl;
    cout << "Ingrese el ID de la transacción (0 - Para salir): ";
    cin >> id;

    if(id <= 0){
        return;
    }

    /// NI ME ACUERDO COMO FUNCIONABA ESTO
    _detalleManager.eliminar();
    _compraManager.eliminar();


}

