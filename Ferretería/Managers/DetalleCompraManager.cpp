#include <iostream>
using namespace std;

#include "../utils.h" //

#include "../Entidades/DetalleTransaccion.h"

#include "DetalleCompraManager.h"

DetalleCompraManager::DetalleCompraManager(){

}

int DetalleCompraManager::buscarPosicion(int id){
    return _repo.buscarID(id);
}

DetalleTransaccion DetalleCompraManager::traerRegistro(int pos){
    return _repo.leer(pos);
}


int DetalleCompraManager::obtenerNumeroRegistros(){
    return _repo.getCantidadRegistros();
}

float DetalleCompraManager::cargar(int idTrans){
    int opc, id, idTransaccion, idProducto, cantProducto, precioUnitario;
    float total, monto;
    total = 0;

    cout << "CUANTOS PRODUCTOS VA A COMPRAR? -> Opcion: ";
    opc = pedirEnteroValido();

    for(int i=0; i<opc; i++){
        id = _repo.getNuevoID();
        idTransaccion = idTrans;

        cout << "Ingresando detalle de compra numero " << (i + 1) << endl;

        cout << "Ingrese el id de producto: ";
        idProducto = pedirEnteroValido();

        if(!_almacenManager.validarID(idProducto)){
            do{
                cout << "ESE ID NO EXISTE" << endl;
                cout << "Ingrese un id real: ";
                idProducto = pedirEnteroValido();
            }while(!_almacenManager.validarID(idProducto));
        }

        cout << "Ingrese la cantidad de ese producto a stockear: ";
        cantProducto = pedirEnteroValido();

        if( cantProducto <= 0){

            do{
                cout << "NO PUEDE COMPRAR ESA CANTIDAD" << endl;
                cout << "Ingrese la cantidad de ese producto a stockear: ";
                cantProducto = pedirEnteroValido();
            }while(cantProducto <= 0);
        }

        _almacenManager.rellenarStock(idProducto, cantProducto);

        precioUnitario = _almacenManager.obtenerPrecio(idProducto);
        monto = cantProducto * precioUnitario;

        cout << "Monto: " << monto;

        _repo.guardar(DetalleTransaccion(id, idTransaccion, idProducto, cantProducto, precioUnitario));
        total += monto;

    }

    return total;
}

void DetalleCompraManager::mostrar(){
  cout << "------ Lista detalles compras ------  "<<endl;;
  int cantidad = _repo.getCantidadRegistros();

  for(int i=0; i<cantidad; i++){
    if(_repo.leer(i).getEstado()){
        mostrarDetalleCompleto(_repo.leer(i));
    }
  }
}

void DetalleCompraManager::mostrar(int id){

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

/* void DetalleVentaManager::modificar(){
  int id, pos, opc;
  cout << "Ingrese el ID de la venta: ";
  cin >> id;

  pos = _repo.buscarID(id);

  if(pos == -1){
    cout << "ESE REGISTRO NO EXISTE" << endl;
    return;
  }

  Transaccion reg = _repo.leer(pos);

  system("cls");
  cout << "Que desea modificar?" << endl;
  cout << " 1 - ID CLIENTE" << endl;
  cout << " 2 - FECHA" << endl;
  cout << " 3 - HORA" << endl;
  cout << " 4 - TIPO DE FACTURA" << endl;
  cout << " Opcion: ";
  cin >> opc;

  switch(opc){
    case 0:{
        cout << "Error" << endl;
        return;
     }
    case 1:{

        if(reg.getEstado()){

            int posCliente = _repoCliente.buscarID(reg.getIdPersona());
            Cliente cli = _repoCliente.leer(posCliente);
            cout << " ID CLIENTE: " << cli.getId() << endl;
            cout << " NOMBRE Y APELLIDO: " << cli.getNombre() << " " << cli.getApellido() << endl;

            int opc;

            cout << " Ingrese el ID del cliente (0 - salir)" << endl;
            cin >> opc;

            if(opc <= 0){
                return;
            }

            if(opc > 0 ){

                posCliente = _repoCliente.buscarID(opc);
                Cliente cli = _repoCliente.leer(posCliente);

                if(cli.getEstado()){
                    reg.setIdPersona(opc);

                    if(_repo.guardar(pos, reg)){
                        cout << "SE GUARDO EL REGISTRO" << endl;
                        return;
                    }

                    cout << "NO SE PUDO GUARDAR EL REGISTRO" << endl;
                    return;
                }

                cout << "NO SE ENCONTRÓ ESE CLIENTE" << endl;
                return;
            }

            cout << "NO SE PUDO MODIFICAR LA VENTA" << endl;
            return;
        }

        cout << "NO EXISTE ESE CLIENTE" << endl;
        return;
    }
    case 2:{

        int dia, mes, anio;
        Fecha fecha;
        do{
            system("cls");
            cout << "Ingrese el dia de hoy: ";
            cin >> dia;

            cout << "Ingrese el mes actual: ";
            cin >> mes;

            cout << "Ingrese el anio actual: ";
            cin >> anio;
        }while(!fecha.validarFecha(dia, mes, anio));

        reg.setFechaEmision(fecha);

        if(_repo.guardar(pos, reg)){
            cout << "FECHA ACTUALIZADA CORRECTAMENTE";
        }

     }
    case 3:{

     }
     case 4:{

        cout << "TIPO DE FACTURA ACTUAL: " << reg.getTipoFactura() <<endl;
        system("cls");

        cout << "---- NUEVO TIPO DE FACTURA ---- "<< endl;
        cout << " 0 - SALIR " << endl;
        cout << " 1 - TIPO 'A' " << endl;
        cout << " 2 - TIPO 'B' " << endl;
        int opc;
        cout << "Opcion: ";
        cin >> opc;

        if(opc == 0){
            return;
        }

        if(opc == 1){
            reg.setTipoFactura('A');
            _repo.guardar(pos, reg);
            cout << "TIPO DE FACTURA MODIFICADO" << endl;
            return;
        }

        if(opc == 2){
            reg.setTipoFactura('B');
            _repo.guardar(pos, reg);
            cout << "TIPO DE FACTURA MODIFICADO" << endl;
            return;
        }

        cout << "ERROR" << endl;
        return;

     }
 }
}
*/

void DetalleCompraManager::eliminar(){
    int id, pos;
    cout << "Ingrese el ID de la compra: ";
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

void DetalleCompraManager::mostrarDetalleCompleto(const DetalleTransaccion &reg){
    cout << "-----------------------------------" << endl;
    cout << " ID: " << reg.getId() << endl;
    cout << " TRANSACCION ID: " << reg.getIdTransaccion() << endl;
    cout << " ID PRODUCTO: " << reg.getIdProducto() << endl;
    cout << " CANTIDAD: " << reg.getCantidad() << endl;
    cout << " PRECIO UNITARIO: " << reg.getPrecioUnitario() << endl;
    cout << " TOTAL: " << reg.getCantidad() * reg.getPrecioUnitario() << endl;
    cout << "-----------------------------------" << endl;
}
