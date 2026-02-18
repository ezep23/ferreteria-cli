#include <iostream>
using namespace std;

#include "../utils.h"
#include "../Entidades/DetalleTransaccion.h"

#include "DetalleVentaManager.h"

DetalleVentaManager::DetalleVentaManager(){

}

int DetalleVentaManager::buscarPosicion(int id){
    return _repo.buscarID(id);
}

DetalleTransaccion DetalleVentaManager::traerRegistro(int pos){
    return _repo.leer(pos);
}


int DetalleVentaManager::obtenerNumeroRegistros(){
    return _repo.getCantidadRegistros();
}

float DetalleVentaManager::cargar(int idTrans){
    int opc, id, idTransaccion, idProducto, cantProducto, precioUnitario;
    float total, monto;
    total = 0;

    cout << "CUANTOS PRODUCTOS VA A LLEVAR? -> Opcion: ";
    opc = pedirEnteroValido();

    for(int i=0; i<opc; i++){
        id = _repo.getNuevoID();
        idTransaccion = idTrans;

        cout << "Ingresando detalle de venta numero " << (i + 1) << endl;

        cout << "Ingrese el id de producto: ";
        idProducto = pedirEnteroValido();

        if(!_almacenManager.validarID(idProducto)){
            do{
                cout << "ESE ID NO EXISTE" << endl;
                cout << "Ingrese un id real: ";
                idProducto = pedirEnteroValido();
            }while(!_almacenManager.validarID(idProducto));
        }

        cout << "Ingrese la cantidad de ese producto a llevar: ";
        cantProducto = pedirEnteroValido();

        if( _almacenManager.obtenerStock(idProducto) < cantProducto){

            do{
                cout << "NO HAY CANTIDAD SUFICIENTE EN EL ALMACEN" << endl;
                cout << "Ingrese la cantidad de ese producto a llevar: ";
                cantProducto = pedirEnteroValido();
            }while(_almacenManager.obtenerStock(idProducto) < cantProducto);
        }

        _almacenManager.descontarStock(idProducto, cantProducto);

        precioUnitario = _almacenManager.obtenerPrecio(idProducto);
        monto = cantProducto * precioUnitario;

        cout << "Monto: " << monto;

        _repo.guardar(DetalleTransaccion(id, idTransaccion, idProducto, cantProducto, precioUnitario));
        total += monto;

    }

    return total;
}

void DetalleVentaManager::mostrar(){
  cout << "------ Lista detalles venta ------  "<<endl;;
  int cantidad = _repo.getCantidadRegistros();

  for(int i=0; i<cantidad; i++){
    if(_repo.leer(i).getEstado()){
        mostrarDetalleCompleto(_repo.leer(i));
    }
  }
}

void DetalleVentaManager::mostrar(int id){

    int pos = _repo.buscarID(id);

    if(_repo.leer(pos).getId() == id ){
        cout << "-------------------------------" << endl;
        mostrarDetalleCompleto(_repo.leer(pos));
        cout << "-------------------------------" << endl;
    }else{
        cout << "DETALLE NO ENCONTRADO";
        return;
    }
}

void DetalleVentaManager::mostrarDetallesTransaccion(int idTransaccion){
  cout << "------ Lista detalles ventas con id " << idTransaccion << " ------  "<<endl;
  int cantidad = _repo.getCantidadRegistros();

  for(int i=0; i<cantidad; i++){
    if(_repo.leer(i).getEstado() && _repo.leer(i).getIdTransaccion() == idTransaccion){
        mostrarDetalleCompleto(_repo.leer(i));
    }
  }
}

float DetalleVentaManager::obtenerMontoCategoria(int idTrans, int idCat){
    int cantidad = _repo.getCantidadRegistros();
    float acum = 0;

    for(int i=0; i<cantidad; i++){
        if(_repo.leer(i).getEstado() && _repo.leer(i).getIdTransaccion() == idTrans){

            int idCategoria = _almacenManager.obtenerCategoriaProducto(_repo.leer(i).getIdProducto());
            if(idCategoria != 0){

                if(idCategoria == idCat ){
                    acum += _repo.leer(i).getPrecioUnitario() * _repo.leer(i).getCantidad();
                }

            }
        }
    }
    return acum;
}

int DetalleVentaManager::obtenerCantidadCategoria(int idTrans, int idCat){
    int cantidad = _repo.getCantidadRegistros();
    float acum = 0;

    for(int i=0; i<cantidad; i++){
        if(_repo.leer(i).getEstado() && _repo.leer(i).getIdTransaccion() == idTrans){

            int idCategoria = _almacenManager.obtenerCategoriaProducto(_repo.leer(i).getIdProducto());
            if(idCategoria != 0){

                if(idCategoria == idCat ){
                    acum += _repo.leer(i).getCantidad();
                }

            }
        }
    }
    return acum;
}

void DetalleVentaManager::modificar(){
  int id, idDetalle, pos, opc;

  do{
    cout << "Ingrese el ID de la venta: ";
    id = pedirEnteroValido();
  }while(!validarExisteTransaccion(id));

  cout << "DETALLES DE ESA TRANSACCION" << endl;
  mostrarDetallesTransaccion(id);

  do{
    cout << "Ingrese el ID del detalle a modificar: ";
    idDetalle = pedirEnteroValido();
  }while(!validarDetallePerteneceTransaccion(idDetalle, id));

  system("cls");
  cout << "Que desea modificar?" << endl;
  cout << " 1 - ID PRODUCTO" << endl;
  cout << " 2 - CANTIDAD" << endl;
  cout << " Opcion: ";
  opc = pedirEnteroValido();

  switch(opc){
    case 0:{
        cout << "Error" << endl;
        return;
     }
    case 1:{

        int idProducto;

        do{
            cout << "Ingrese el ID del producto nuevo: ";
            idProducto = pedirEnteroValido();
        }while(!_almacenManager.validarID(idProducto));

        int pos = _repo.buscarID(idProducto);
        DetalleTransaccion detalle = _repo.leer(pos);

        detalle.setIdProducto(idProducto);
        _repo.guardar(pos, detalle);

        cout << "ID DE PRODUCTO ACTUALIZADO CORRECTAMENTE" << endl;
        cout << "NUEVO ID: " << idProducto << endl;
    }
    break;
    case 2:{

        int idProducto;

        do{
            cout << "Ingrese el ID del producto nuevo: ";
            idProducto = pedirEnteroValido();
        }while(!_almacenManager.validarID(idProducto));

        int pos = _repo.buscarID(idProducto);
        DetalleTransaccion detalle = _repo.leer(pos);

        int cantidad;
        int idProd = detalle.getIdProducto();
        int cantidadAnterior = detalle.getCantidad();

        int stockMaximoPermitido = _almacenManager.obtenerStock(idProd) + cantidadAnterior;

        do{
            cout << "Usted llevaba esta cantidad del producto: " << cantidadAnterior << endl;
            cout << "Stock maximo disponible para llevar: " << stockMaximoPermitido << endl;
            cout << "Ingrese la cantidad actualizada que va a llevar: ";
            cantidad = pedirEnteroValido();

            if(cantidad <= 0){
                cout << "Sea serio, por favor." << endl;
                return;
            }

            if (cantidad > stockMaximoPermitido) {
                cout << "ERROR: La cantidad supera el stock disponible." << endl;
            }
        } while(cantidad > stockMaximoPermitido);

        if(cantidad >= cantidadAnterior){
            int descontar = cantidad - cantidadAnterior;
            if (descontar > 0) {
                _almacenManager.descontarStock(idProd, descontar);
            }
        } else {
            int aumentar = cantidadAnterior - cantidad;
            _almacenManager.rellenarStock(idProd, aumentar);
        }


        detalle.setCantidad(cantidad);
        _repo.guardar(pos, detalle);

        cout << "CANTIDAD DE VENTA ACTUALIZADA" << endl;
        break;
     }
  }
}

void DetalleVentaManager::eliminar(){
    int id, pos;
    cout << "Ingrese el ID de la venta: ";
    id = pedirEnteroValido();

    int cantidad = _repo.getCantidadRegistros();

    for(int i=0; i<cantidad; i++){
        if(_repo.leer(i).getEstado() && _repo.leer(i).getIdTransaccion() == id){
            _repo.eliminar(i);
            cout << "REGISTRO " << i << " ELIMINADO" << endl;
        }
  }

  return;
}

void DetalleVentaManager::crearBackup(){
    _repo.crearBackup();
}
void DetalleVentaManager::cargarBackup(){
    _repo.cargarBackup();
}

bool DetalleVentaManager::validarExisteTransaccion(int idTransaccion){
  int cantidad = _repo.getCantidadRegistros();
  bool existeId = false;

  for(int i=0; i<cantidad; i++){
    if(_repo.leer(i).getEstado() && _repo.leer(i).getIdTransaccion() == idTransaccion){
        existeId = true;
        return existeId;
    }
  }

  return existeId;
}

 bool DetalleVentaManager::validarDetallePerteneceTransaccion(int idDetalle, int idTransaccion){
    int cantidad = _repo.getCantidadRegistros();
    bool existeId = false;

    for(int i=0; i<cantidad; i++){
    if(_repo.leer(i).getEstado() && _repo.leer(i).getId() == idDetalle){

        if(_repo.leer(i).getIdTransaccion() == idTransaccion){
            existeId = true;
            return existeId;
        }
    }
  }

  return existeId;
}

void DetalleVentaManager::mostrarDetalleCompleto(const DetalleTransaccion &reg){
    cout << "-----------------------------------" << endl;
    cout << "          DETALLE DE VENTA         " << endl;
    cout << "-----------------------------------" << endl;
    cout << " ID: " << reg.getId() << endl;
    cout << " TRANSACCION ID: " << reg.getIdTransaccion() << endl;
    cout << " ID PRODUCTO: " << reg.getIdProducto() << endl;
    cout << " CANTIDAD: " << reg.getCantidad() << endl;
    cout << " PRECIO UNITARIO: " << reg.getPrecioUnitario() << endl;
    cout << " TOTAL: " << reg.getCantidad() * reg.getPrecioUnitario() << endl;
    cout << "-----------------------------------" << endl;
}
