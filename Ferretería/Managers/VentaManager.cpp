#include <iostream>
using namespace std;

#include "../utils.h"

#include "../Entidades/Cliente.h"
#include "../Entidades/Transaccion.h"

#include "VentaManager.h"

VentaManager::VentaManager(){

}

int VentaManager::obtenerNumeroRegistros(){
    return _repo.getCantidadRegistros();
}

bool VentaManager::guardar(int pos, Transaccion reg){
    if(_repo.guardar(pos, reg)){
        return true;
    }
}

int VentaManager::cargar() {
    int id, idCliente, idEmpleado;
    id = _repo.getNuevoID();

    cout << "--- NUEVA VENTA #" << id << " ----" << endl;

    do {
        cout << "Ingrese el ID de Cliente ('0' - para crear)" << endl;
        cout << "Opcion: ";
        idCliente = pedirEnteroValido();

        if (idCliente == 0) {
            return 0;
        }

        if ( !_clienteManager.existeRegistro(idCliente)) {
            cout << ">>> Error: El cliente no existe. Intente nuevamente." << endl;
        }

    } while (!_clienteManager.existeRegistro(idCliente));

    _clienteManager.mostrar(idCliente);
    system("pause");

    do{

       cout << "Ingrese el ID del empleado ('O' - Para listar) " << endl;
       cout << "ID: ";
       idEmpleado = pedirEnteroValido();

       if(idEmpleado == 0){
            cout << "EMPLEADOS" << endl;
            _empleadoManager.mostrar();

            cout << "Ingrese el ID del empleado: ";
            idEmpleado = pedirEnteroValido();
        }

        if ( !_empleadoManager.existeRegistro(idEmpleado)) {
            cout << ">>> Error: El empleado no existe. Intente nuevamente." << endl;
        }

    } while ( !_empleadoManager.existeRegistro(idEmpleado));

    _empleadoManager.mostrar(idEmpleado);
    system("pause");

    int d, m, a;
    Fecha fecha;
    do {
        system("cls");
        cout << "--- FECHA DE LA VENTA ---" << endl;
        cout << "Dia: "; cin >> d;
        cout << "Mes: "; cin >> m;
        cout << "Anio: "; cin >> a;
    } while (!fecha.validarFecha(d, m, a));

    fecha.setDia(d); fecha.setMes(m); fecha.setAnio(a);


    int h, minu;
    Hora hora;
    do {
        system("cls");
        cout << "--- HORA DE LA VENTA ---" << endl;
        cout << "Hora: "; cin >> h;
        cout << "Minutos: "; cin >> minu;
    } while (!hora.validarHora(h, minu));

    hora.setHora(h); hora.setMinutos(minu);

    char opcFactu;
    do {
        system("cls");
        cout << "--- TIPO DE FACTURA ---" << endl;
        cout << " 'A' - Responsable Inscripto (Empresa) " << endl;
        cout << " 'B' - Consumidor Final (Particular) " << endl;
        cout << "Opcion: ";
        cin >> opcFactu;
        opcFactu = toupper(opcFactu);
    } while (opcFactu != 'A' && opcFactu != 'B');
    cin.ignore();

    Transaccion nuevaVenta(id, idCliente, idEmpleado, 0, hora, fecha, opcFactu);

    if (_repo.guardar(nuevaVenta)) {
        return id;
    } else {
        cout << "Error critico al guardar la cabecera de la venta." << endl;
        return 0;
    }
}

void VentaManager::mostrar(){
  cout << "------ Lista de ventas ------  "<<endl;;
  int cantidad = _repo.getCantidadRegistros();

  for(int i=0; i<cantidad; i++){
    if(_repo.leer(i).getEstado()){
        mostrarVentaCompleta(_repo.leer(i));
    }
  }
}

int VentaManager::buscarPosicion(int id){
    return _repo.buscarID(id);
}

Transaccion VentaManager::traerRegistro(int pos){
    return _repo.leer(pos);
}


void VentaManager::mostrar(int id){

    int pos = _repo.buscarID(id);

    if(_repo.leer(pos).getEstado()){
        cout << "-------------------------------" << endl;
        mostrarVentaCompleta(_repo.leer(pos));
        cout << "-------------------------------" << endl;
    }else{
        cout << "VENTA NO ENCONTRADA";
        return;
    }
}

void VentaManager::modificar(){
  int id, pos, opc;
  cout << "Ingrese el ID de la venta: ";
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
  cout << " 4 - TIPO DE FACTURA" << endl;
  cout << " Opcion: ";
  opc = pedirEnteroValido();

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
            cout << " NOMBRE Y APELLIDO: " << cli.getNombre() << " - " << cli.getDni() << endl;

            int opc;

            cout << " Ingrese el ID del cliente (0 - salir)" << endl;
            opc = pedirEnteroValido();

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
        opc = pedirEnteroValido();

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

void VentaManager::eliminar(){
    int id, pos;
    Transaccion venta;
    char respuesta;

    cout << "---- Eliminar venta ----"<<endl;
    cout << "Ingrese ID de la venta: ";
    id = pedirEnteroValido();

    pos = _repo.buscarID(id);

    if(pos != -1){
        venta = _repo.leer(pos);

        if(venta.getEstado() == false){
            cout << "ESTA VENTA YA HA SIDO ELIMINADA" << endl;
            return;
        }

        cout << "Tarea a eliminar: "<<endl;
        mostrarVentaCompleta(venta);

        cout << "Esta segudro de que lo quiere eliminar ? (S/N):";
        cin >> respuesta;

        if(respuesta == 'S' || respuesta == 's'){

            if(_repo.eliminar(pos)){
                cout << "La tarea fue eliminada con exito!" << endl;
            }else{
                cout << "Ocurrio un error al intentar actualizar la tarea." <<endl;
            }
        }

    }else{
        cout << "La tarea no existe en el archivo" << endl;
    }
}

void VentaManager::recaudacionMensual(int anio){
    int cantidad = _repo.getCantidadRegistros();
    Transaccion *vVentas = new Transaccion[cantidad];

    if(vVentas == nullptr){
        cout << "No se pudo asignar memoria..." << endl;
        exit(-100);
    }

    _repo.leerTodos(vVentas, cantidad);

    float recaudacionPorMes[12] = {0};
    for(int i=0; i < cantidad; i++){

        if(vVentas[i].getEstado() && vVentas[i].getFechaTransaccion().getAnio() == anio){

            int mes = vVentas[i].getFechaTransaccion().getMes();

            if(mes >= 1 && mes <= 12){
                recaudacionPorMes[mes - 1] += vVentas[i].getMontoTotal();
            }
        }
    }

    for(int i=0; i < 12; i++){
        cout << "RECAUDACION MES: " << (i + 1) << endl;
        cout << "TOTAL: " << recaudacionPorMes[i] << endl;
    }

    delete [] vVentas;
}

void VentaManager::recaudacionMensualCategoria(int anio, int idCat){
    int cantidad = _repo.getCantidadRegistros();
    Transaccion *vVentas = new Transaccion[cantidad];

    if(vVentas == nullptr){
        cout << "No se pudo asignar memoria..." << endl;
        exit(-100);
    }

    _repo.leerTodos(vVentas, cantidad);

    float recaudacionPorMes[12] = {0};
    for(int i=0; i < cantidad; i++){

        if(vVentas[i].getEstado() && vVentas[i].getFechaTransaccion().getAnio() == anio){

            int mes = vVentas[i].getFechaTransaccion().getMes();

            if(mes >= 1 && mes <= 12){
                recaudacionPorMes[mes - 1] += _detalleManager.obtenerMontoCategoria(vVentas[i].getIdTransaccion(), idCat);
            }
        }
    }

    for(int i=0; i < 12; i++){
        cout << "RECAUDACION MES: " << (i + 1) << endl;
        cout << "TOTAL: " << recaudacionPorMes[i] << endl;
    }

    delete [] vVentas;
}


void VentaManager::recaudacionAnual(){
    int cantidad = _repo.getCantidadRegistros();
    Transaccion *vVentas = new Transaccion[cantidad];

    if(vVentas == nullptr){
        cout << "Error de memoria." << endl;
        exit(-100);
    }

    _repo.leerTodos(vVentas, cantidad);

    /// BURBUJA DESCENDENTE
    Transaccion aux;
    for(int i = 0; i < cantidad - 1; i++){
        for(int j = 0; j < cantidad - i - 1; j++){
            // swap
            if(vVentas[j].getFechaTransaccion().getAnio() < vVentas[j+1].getFechaTransaccion().getAnio()){
                aux = vVentas[j];
                vVentas[j] = vVentas[j+1];
                vVentas[j+1] = aux;
            }
        }
    }

    /// RECORRO ARREGLO AGRUPANDO POR AÑO
    int i = 0;
    while(i < cantidad){

        int anioActual = vVentas[i].getFechaTransaccion().getAnio();
        float recaudacionAnio = 0;

        while(i < cantidad && vVentas[i].getFechaTransaccion().getAnio() == anioActual){

            if(vVentas[i].getEstado()){
                recaudacionAnio += vVentas[i].getMontoTotal();
            }

            i++;
        }

        cout << "AÑO: " << anioActual << endl;
        cout << "TOTAL RECAUDADO: " << recaudacionAnio << endl;
        cout << "-------------------------" << endl;
    }

    delete [] vVentas;
}

void VentaManager::recaudacionAnualCategoria(int idCat){
    int cantidad = _repo.getCantidadRegistros();
    Transaccion *vVentas = new Transaccion[cantidad];

    if(vVentas == nullptr){
        cout << "Error de memoria." << endl;
        exit(-100);
    }

    _repo.leerTodos(vVentas, cantidad);

    Transaccion aux;
    for(int i = 0; i < cantidad - 1; i++){
        for(int j = 0; j < cantidad - i - 1; j++){
            if(vVentas[j].getFechaTransaccion().getAnio() < vVentas[j+1].getFechaTransaccion().getAnio()){
                aux = vVentas[j];
                vVentas[j] = vVentas[j+1];
                vVentas[j+1] = aux;
            }
        }
    }

    int i = 0;
    while(i < cantidad){

        int anioActual = vVentas[i].getFechaTransaccion().getAnio();
        float recaudacionAnio = 0;

        while(i < cantidad && vVentas[i].getFechaTransaccion().getAnio() == anioActual){

            if(vVentas[i].getEstado() ){
                recaudacionAnio += _detalleManager.obtenerMontoCategoria(vVentas[i].getIdTransaccion(), idCat);
            }

            i++;
        }

        cout << "AÑO: " << anioActual << endl;
        cout << "TOTAL RECAUDADO: " << recaudacionAnio << endl;
        cout << "-------------------------" << endl;
    }

    delete [] vVentas;
}

void VentaManager::numeroVentasMensualCategoria(int anio, int idCat){
    int cantidad = _repo.getCantidadRegistros();
    Transaccion *vVentas = new Transaccion[cantidad];

    if(vVentas == nullptr){
        cout << "No se pudo asignar memoria..." << endl;
        exit(-100);
    }

    _repo.leerTodos(vVentas, cantidad);

    float ventasPorMes[12] = {0};
    for(int i=0; i < cantidad; i++){

        if(vVentas[i].getEstado() && vVentas[i].getFechaTransaccion().getAnio() == anio){

            int mes = vVentas[i].getFechaTransaccion().getMes();

            if(mes >= 1 && mes <= 12){
                ventasPorMes[mes - 1] += _detalleManager.obtenerCantidadCategoria(vVentas[i].getIdTransaccion(), idCat);
            }
        }
    }

    for(int i=0; i < 12; i++){
        cout << "VENTA MES: " << (i + 1) << endl;
        cout << "PRODUCTOS VENDIDOS: " << ventasPorMes[i] << endl;
    }

    delete [] vVentas;
}

void VentaManager::numeroVentasAnualCategoria(int idCat){
    int cantidad = _repo.getCantidadRegistros();
    Transaccion *vVentas = new Transaccion[cantidad];

    if(vVentas == nullptr){
        cout << "Error de memoria." << endl;
        exit(-100);
    }

    _repo.leerTodos(vVentas, cantidad);

    Transaccion aux;
    for(int i = 0; i < cantidad - 1; i++){
        for(int j = 0; j < cantidad - i - 1; j++){
            if(vVentas[j].getFechaTransaccion().getAnio() < vVentas[j+1].getFechaTransaccion().getAnio()){
                aux = vVentas[j];
                vVentas[j] = vVentas[j+1];
                vVentas[j+1] = aux;
            }
        }
    }

    int i = 0;
    while(i < cantidad){

        int anioActual = vVentas[i].getFechaTransaccion().getAnio();
        int productosVendidos = 0;

        while(i < cantidad && vVentas[i].getFechaTransaccion().getAnio() == anioActual){

            if(vVentas[i].getEstado() ){
                productosVendidos += _detalleManager.obtenerCantidadCategoria(vVentas[i].getIdTransaccion(), idCat);
            }

            i++;
        }

        cout << "AÑO: " << anioActual << endl;
        cout << "CANTIDAD DE PRODUCTOS VENDIDOS: " << productosVendidos << endl;
        cout << "-------------------------" << endl;
    }

    delete [] vVentas;
}

void VentaManager::obtenerNumeroProductosVendidosCategoria(int idCat){
    int cantidad = _repo.getCantidadRegistros();
    Transaccion *vVentas = new Transaccion[cantidad];

    if(vVentas == nullptr){
        cout << "Error de memoria." << endl;
        exit(-100);
    }

    _repo.leerTodos(vVentas, cantidad);

    int productosVendidos = 0;
    for(int i = 0; i < cantidad; i++){
        if(vVentas[i].getEstado()){
            productosVendidos += _detalleManager.obtenerCantidadCategoria(vVentas[i].getIdTransaccion(), idCat);
        }
    }

   cout << "-----------------------------------" << endl;
   cout << " Total productos vendidos: " << productosVendidos << endl;
   cout << "-----------------------------------" << endl;

    delete [] vVentas;
}

void VentaManager::ventasPorEmpleado(){
    int cantidad = _repo.getCantidadRegistros();
    Transaccion *vVentas = new Transaccion[cantidad];

    if(vVentas == nullptr){
        cout << "Error de memoria." << endl;
        exit(-100);
    }

    _repo.leerTodos(vVentas, cantidad);

    int totalIDs = _empleadoManager.obtenerNumeroProximoID();
    int *cantEmpleados = new int[totalIDs]();

    if(cantEmpleados == nullptr){
        delete[] vVentas;
        return;
    }


    for(int i = 0; i < cantidad; i++){
        if(vVentas[i].getEstado()){
            int idEmpleado = vVentas[i].getIdEmpleado();

            if (idEmpleado > 0 && idEmpleado <= totalIDs) {
                cantEmpleados[idEmpleado - 1]++;
            }
        }
    }

    cout << "--- REPORTE DE VENTAS POR EMPLEADO ---" << endl;
    for(int j = 0; j < totalIDs; j++){
        if(cantEmpleados[j] >= 0){
            cout << "EMPLEADO ID " << (j + 1) << endl;
            cout << "VENTAS ASIGNADOS: " << cantEmpleados[j] << endl;
            cout << "-------------------------" << endl;
        }
    }

    delete[] vVentas;
    delete[] cantEmpleados;
}

void VentaManager::mostrarOrdenadasUltimaVenta(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay ventas registradas." << endl;
        return;
    }

    Transaccion *vVenta = new Transaccion[cantidad];
    _repo.leerTodos(vVenta, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_max = i;

        for (int j = i + 1; j < cantidad; j++) {

            Fecha f_j = vVenta[j].getFechaTransaccion();
            Fecha f_max = vVenta[j_max].getFechaTransaccion();

            long fechaJ_num = f_j.getAnio() * 10000 + f_j.getMes() * 100 + f_j.getDia();
            long fechaMax_num = f_max.getAnio() * 10000 + f_max.getMes() * 100 + f_max.getDia();

            if (fechaJ_num > fechaMax_num) {
                j_max = j;
            }

            else if (fechaJ_num == fechaMax_num) {

                Hora h_j = vVenta[j].getHoraTransaccion();
                Hora h_max = vVenta[j_max].getHoraTransaccion();

                long horaJ_num = h_j.getHora() * 100 + h_j.getMinutos();
                long horaMax_num = h_max.getHora() * 100 + h_max.getMinutos();

                if (horaJ_num > horaMax_num) {
                    j_max = j;
                }
            }
        }

        if (j_max != i) {
            Transaccion temp = vVenta[i];
            vVenta[i] = vVenta[j_max];
            vVenta[j_max] = temp;
        }
    }

    cout << "VENTAS DESDE LA ÚLTIMA TRANSACCIÓN: " << endl;
    for (int x = 0; x < cantidad; x++) {
        if (vVenta[x].getEstado()) {
            mostrarVentaCompleta(vVenta[x]);
        }
    }

    delete[] vVenta;
}
void VentaManager::mostrarOrdenadasPrimeraVenta(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay ventas registradas." << endl;
        return;
    }

    Transaccion *vVenta = new Transaccion[cantidad];
    _repo.leerTodos(vVenta, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {


            Fecha f_j = vVenta[j].getFechaTransaccion();
            Fecha f_min = vVenta[j_min].getFechaTransaccion();

            /// SE SUMAN LAS ANIOS, MESES Y DIAS PARA FORMAR UN NUMERO
            long fechaJ_num = f_j.getAnio() * 10000 + f_j.getMes() * 100 + f_j.getDia();
            long fechaMin_num = f_min.getAnio() * 10000 + f_min.getMes() * 100 + f_min.getDia();

            if (fechaJ_num < fechaMin_num) {
                j_min = j;
            } else if (fechaJ_num == fechaMin_num) { /// SI LAS FECHAS SON IGUAL DESEMPATE POR D

                Hora h_j = vVenta[j].getHoraTransaccion();
                Hora h_min = vVenta[j_min].getHoraTransaccion();

                long horaJ_num = h_j.getHora() * 100 + h_j.getMinutos();
                long horaMin_num = h_min.getHora() * 100 + h_min.getMinutos();

                if (horaJ_num < horaMin_num) {
                    j_min = j;
                }
            }
        }

        if (j_min != i) {
            Transaccion temp = vVenta[i];
            vVenta[i] = vVenta[j_min];
            vVenta[j_min] = temp;
        }
    }

    cout << "VENTAS DESDE LA PRIMERA TRANSACCION: " << endl;
    for (int x = 0; x < cantidad; x++) {
        if (vVenta[x].getEstado()) {
            mostrarVentaCompleta(vVenta[x]);
        }
    }

    delete[] vVenta;
}

void VentaManager::crearBackup(){
    _repo.crearBackup();
}
void VentaManager::cargarBackup(){
    _repo.cargarBackup();
}

void VentaManager::mostrarVentaCompleta(const Transaccion &reg){
    cout << "-----------------------------------" << endl;
    cout << "         CABECERA DE VENTA         " << endl;
    cout << "-----------------------------------" << endl;
    cout << " ID: " << reg.getIdTransaccion() << endl;
    cout << " ID Cliente: " << reg.getIdPersona() << endl;
    cout << " ID Empleado " << reg.getIdEmpleado() << endl;
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
