#include <iostream>
using namespace std;

#include "../utils.h"

#include "../Entidades/Empleado.h"
#include "../Entidades/Transaccion.h"

#include "CompraManager.h"

CompraManager::CompraManager(){

}

int CompraManager::obtenerNumeroRegistros(){
    return _repo.getCantidadRegistros();
}

bool CompraManager::guardar(int pos, Transaccion reg){
    if(_repo.guardar(pos, reg)){
        return true;
    }
}

int CompraManager::cargar() {
    int id, idEmpleado;

    id = _repo.getNuevoID();

    cout << "--- NUEVA VENTA #" << id << " ----" << endl;

    do {
        cout << "Ingrese el ID de Empleado ('0' - para salir): ";
        idEmpleado = pedirEnteroValido();

        if (idEmpleado == 0) {
            return 0;
        }

        if ( !_empleadoManager.existeRegistro(idEmpleado) ) {
            cout << ">>> Error: El cliente no existe. Intente nuevamente." << endl;
        }

    } while ( !_empleadoManager.existeRegistro(idEmpleado));

    _empleadoManager.mostrar(idEmpleado);
    system("pause");

    int d, m, a;
    Fecha fecha;
    do {
        system("cls");
        cout << "--- FECHA DE LA COMPRA ---" << endl;
        cout << "Dia: "; cin >> d;
        cout << "Mes: "; cin >> m;
        cout << "Anio: "; cin >> a;
    } while (!fecha.validarFecha(d, m, a));

    fecha.setDia(d); fecha.setMes(m); fecha.setAnio(a);


    int h, minu;
    Hora hora;
    do {
        system("cls");
        cout << "--- HORA DE LA COMPRA ---" << endl;
        cout << "Hora: "; cin >> h;
        cout << "Minutos: "; cin >> minu;
    } while (!hora.validarHora(h, minu));

    hora.setHora(h); hora.setMinutos(minu);

    Transaccion nuevaCompra(id, 0, idEmpleado, 0, hora, fecha, 'A');

    if (_repo.guardar(nuevaCompra)) {
        return id;
    } else {
        cout << "Error critico al guardar la cabecera de la compra." << endl;
        return 0;
    }
}

void CompraManager::mostrar(){
  cout << "------ Lista de compras ------  "<<endl;;
  int cantidad = _repo.getCantidadRegistros();

  for(int i=0; i<cantidad; i++){
    if(_repo.leer(i).getEstado()){
        mostrarCompraCompleta(_repo.leer(i));
    }
  }
}

int CompraManager::buscarPosicion(int id){
    return _repo.buscarID(id);
}

Transaccion CompraManager::traerRegistro(int pos){
    return _repo.leer(pos);
}


void CompraManager::mostrar(int id){

    int pos = _repo.buscarID(id);

    if(_repo.leer(pos).getEstado()){
        cout << "-------------------------------" << endl;
        mostrarCompraCompleta(_repo.leer(pos));
        cout << "-------------------------------" << endl;
    }else{
        cout << "COMPRA NO ENCONTRADA";
        return;
    }
}

void CompraManager::modificar(){
  int id, pos, opc;

  cout << "Ingrese el ID de la compra: ";
  id = pedirEnteroValido();

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
  cout << " Opcion: ";
  opc = pedirEnteroValido();

  switch(opc){
    case 0:{
        cout << "Error" << endl;
        return;
     }
    case 1:{

        if(reg.getEstado()){

            int posEmpleado = _repoEmpleado.buscarID(reg.getIdPersona());
            Empleado cli = _repoEmpleado.leer(posEmpleado);
            cout << " ID CLIENTE: " << cli.getId() << endl;
            cout << " NOMBRE Y APELLIDO: " << cli.getNombre() << " " << cli.getApellido() << endl;

            int opc;

            cout << " Ingrese el ID del cliente (0 - salir)" << endl;
            opc = pedirEnteroValido();

            if(opc <= 0){
                return;
            }

            if(opc > 0 ){

                posEmpleado = _repoEmpleado.buscarID(opc);
                Empleado cli = _repoEmpleado.leer(posEmpleado);

                if(cli.getEstado()){
                    reg.setIdPersona(opc);

                    if(_repo.guardar(pos, reg)){
                        cout << "SE GUARDO EL REGISTRO" << endl;
                        return;
                    }

                    cout << "NO SE PUDO GUARDAR EL REGISTRO" << endl;
                    return;
                }

                cout << "NO SE ENCONTRÓ ESE EMPLEADO" << endl;
                return;
            }

            cout << "NO SE PUDO MODIFICAR LA COMPRA" << endl;
            return;
        }

        cout << "NO EXISTE ESE EMPLEADO" << endl;
        return;

    }
    break;
    case 2:{

        int dia, mes, anio;
        Fecha fecha;

        do{
            system("cls");
            cout << "Ingrese el dia de hoy: ";
            dia = pedirEnteroValido();

            cout << "Ingrese el mes actual: ";
            mes = pedirEnteroValido();

            cout << "Ingrese el anio actual: ";
            anio = pedirEnteroValido();
        }while(!fecha.validarFecha(dia, mes, anio));

        reg.setFechaEmision(fecha);

        if(_repo.guardar(pos, reg)){
            cout << "FECHA ACTUALIZADA CORRECTAMENTE";
        }

        break;
     }
    case 3:{
        int h, minu;
        Hora hora;

        do{
            system("cls");
            cout << "Ingrese la hora actual: ";
            h = pedirEnteroValido();

            cout << "Ingrese los minutos actuales: ";
            minu = pedirEnteroValido();

        } while(!hora.validarHora(h, minu));

        reg.setHoraEmision(hora);

        if(_repo.guardar(pos, reg)){
            cout << "FECHA ACTUALIZADA CORRECTAMENTE";
        }

        break;
    }
 }
}

void CompraManager::eliminar(){
    int id, pos;
    Transaccion compra;
    char respuesta;

    cout << "---- Eliminar compra ----"<<endl;
    cout << "Ingrese ID de la compra: ";
    id = pedirEnteroValido();

    pos = _repo.buscarID(id);

    if(pos != -1){
        compra = _repo.leer(pos);

        if(compra.getEstado() == false){
            cout << "ESTA COMPRA YA HA SIDO ELIMINADA" << endl;
            return;
        }

        cout << "Compra a eliminar: "<<endl;
        mostrarCompraCompleta(compra);

        cout << "Esta seguro de que lo quiere eliminar ? (S/N):";
        cin >> respuesta;

        if(respuesta == 'S' || respuesta == 's'){

            if(_repo.eliminar(pos)){
                cout << "La compra fue eliminada con exito!" << endl;
            }else{
                cout << "Ocurrio un error al intentar actualizar la compra." <<endl;
            }
        }

    }else{
        cout << "La compra no existe en el archivo" << endl;
    }
}

void CompraManager::comprasPorEmpleado(){
    int cantidad = _repo.getCantidadRegistros();
    Transaccion *vCompras = new Transaccion[cantidad];

    if(vCompras == nullptr){
        cout << "Error de memoria." << endl;
        exit(-100);
    }

    _repo.leerTodos(vCompras, cantidad);

    int totalIDs = _empleadoManager.obtenerNumeroProximoID();
    int *cantEmpleados = new int[totalIDs]();

    if(cantEmpleados == nullptr){
        delete[] vCompras;
        return;
    }


    for(int i = 0; i < cantidad; i++){
        if(vCompras[i].getEstado()){
            int idEmpleado = vCompras[i].getIdEmpleado();

            if (idEmpleado > 0 && idEmpleado <= totalIDs) {
                cantEmpleados[idEmpleado - 1]++;
            }
        }
    }

    cout << "--- REPORTE DE COMPRAS POR EMPLEADO ---" << endl;
    for(int j = 0; j < totalIDs; j++){
        if(cantEmpleados[j] >= 0){
            cout << "EMPLEADO ID " << (j + 1) << endl;
            cout << "COMPRASS ASIGNADAS: " << cantEmpleados[j] << endl;
            cout << "-------------------------" << endl;
        }
    }

    delete[] vCompras;
    delete[] cantEmpleados;
}

void CompraManager::mostrarOrdenadasPrimeraCompra(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay compras registradas." << endl;
        return;
    }

    Transaccion *vCompra = new Transaccion[cantidad];
    _repo.leerTodos(vCompra, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_max = i;

        for (int j = i + 1; j < cantidad; j++) {

            Fecha f_j = vCompra[j].getFechaTransaccion();
            Fecha f_max = vCompra[j_max].getFechaTransaccion();

            long fechaJ_num = f_j.getAnio() * 10000 + f_j.getMes() * 100 + f_j.getDia();
            long fechaMax_num = f_max.getAnio() * 10000 + f_max.getMes() * 100 + f_max.getDia();

            if (fechaJ_num > fechaMax_num) {
                j_max = j;
            }
            else if (fechaJ_num == fechaMax_num) {

                Hora h_j = vCompra[j].getHoraTransaccion();
                Hora h_max = vCompra[j_max].getHoraTransaccion();

                long horaJ_num = h_j.getHora() * 100 + h_j.getMinutos();
                long horaMax_num = h_max.getHora() * 100 + h_max.getMinutos();

                if (horaJ_num > horaMax_num) {
                    j_max = j;
                }
            }
        }

        if (j_max != i) {
            Transaccion temp = vCompra[i];
            vCompra[i] = vCompra[j_max];
            vCompra[j_max] = temp;
        }
    }

    cout << "COMPRAS DESDE LA ÚLTIMA TRANSACCIÓN: " << endl;
    for (int x = 0; x < cantidad; x++) {
        if (vCompra[x].getEstado()) {
            mostrarCompraCompleta(vCompra[x]);
        }
    }

    delete[] vCompra;
}

void CompraManager::mostrarOrdenadasUltimaCompra(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay compras registradas." << endl;
        return;
    }

    Transaccion *vCompra = new Transaccion[cantidad];
    _repo.leerTodos(vCompra, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {

            Fecha f_j = vCompra[j].getFechaTransaccion();
            Fecha f_min = vCompra[j_min].getFechaTransaccion();

            long fechaJ_num = f_j.getAnio() * 10000 + f_j.getMes() * 100 + f_j.getDia();
            long fechaMin_num = f_min.getAnio() * 10000 + f_min.getMes() * 100 + f_min.getDia();

            if (fechaJ_num < fechaMin_num) {
                j_min = j;
            } else if (fechaJ_num == fechaMin_num) {

                Hora h_j = vCompra[j].getHoraTransaccion();
                Hora h_min = vCompra[j_min].getHoraTransaccion();

                long horaJ_num = h_j.getHora() * 100 + h_j.getMinutos();
                long horaMin_num = h_min.getHora() * 100 + h_min.getMinutos();

                if (horaJ_num < horaMin_num) {
                    j_min = j;
                }
            }
        }

        // swap
        if (j_min != i) {
            Transaccion temp = vCompra[i];
            vCompra[i] = vCompra[j_min];
            vCompra[j_min] = temp;
        }
    }

    cout << "COMPRAS DESDE LA PRIMERA TRANSACCION: " << endl;
    for (int x = 0; x < cantidad; x++) {
        if (vCompra[x].getEstado()) {
            mostrarCompraCompleta(vCompra[x]);
        }
    }

    delete[] vCompra;
}

void CompraManager::crearBackup(){
    _repo.crearBackup();
}
void CompraManager::cargarBackup(){
    _repo.cargarBackup();
}

void CompraManager::mostrarCompraCompleta(const Transaccion &reg){
    cout << "-----------------------------------" << endl;
    cout << "         CABECERA DE COMPRA        " << endl;
    cout << "-----------------------------------" << endl;
    cout << " ID: " << reg.getIdTransaccion() << endl;
    cout << " ID Empleado: " << reg.getIdEmpleado() << endl;
    cout << " Monto total: " << reg.getMontoTotal() << endl;


    Fecha f = reg.getFechaTransaccion();
    cout << " Fecha: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio();

    cout << " - ";

    cout << "Hora: ";
    Hora h = reg.getHoraTransaccion();

    if(h.getHora() < 10){
        cout << "0";
    }
    cout << h.getHora() << ":";

    if(h.getMinutos() < 10){
        cout << "0";
    }
    cout << h.getMinutos()<< endl;


    cout << " Tipo factura: " << reg.getTipoFactura() << endl;
    cout << "-----------------------------------" << endl;
}
