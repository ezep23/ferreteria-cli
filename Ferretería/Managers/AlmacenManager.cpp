#include <iostream>

#include "AlmacenManager.h"
#include "../Entidades/Producto.h"

#include "../Utils.h"

using namespace std;


AlmacenManager::AlmacenManager(){

}

void AlmacenManager::cargarProducto(){
    int idProv, idProd, idCat, stock;
    float precio;
    string nombre;

    idProd = _repo.getNuevoID();

    do{
        cout << "Ingrese el ID de proveedor (0 - Listar)" << endl;
        cout << "Opcion: ";
        idProv = pedirEnteroValido();
        cout << endl;

        if(idProv == 0){
            cout << "PROVEEDORES: ";
            _proveedorManager.mostrar();
            cout << endl;
        }

    }while(idProv <= 0 || !_proveedorManager.existeProveedor(idProv));

    do{
        cout << "Ingrese el ID de Categoria (0 - Listar)"<< endl;
        cout << "Opcion: ";
        idCat = pedirEnteroValido();

        if(idCat == 0){
            _categoriaManager.mostrar();
        }

        cout << "Ingrese el ID de Categoria" << endl;
        cout << "Opcion: ";
        idCat = pedirEnteroValido();

    }while(idCat <= 0);

    do{
        cout << "Ingrese el nombre del producto: ";
        nombre = cargarCadena();
    }while(!validarCadena(nombre));

    cout << "Ingrese el precio: ";
    precio = pedirFlotanteValido();

    cout << "Ingrese el stock: ";
    stock = pedirEnteroValido();

    if(_repo.guardar(Producto(idProd, idProv, idCat, nombre, precio, stock))){
        cout << "NUEVO PRODUCTO GUARDADO";
        return;
    }else{
        cout << "NO SE PUDO GUARDAR EL PRODUCTO";
        return;
    }

}

void AlmacenManager::listarPorCategoria(){
    int idCategoria;
    _categoriaManager.mostrar();

    cout << "INGRESE LA CATEGORIA QUE DESEE VER: (0 - Para salir)";
    idCategoria = pedirEnteroValido();

    if(idCategoria <= 0){
        return;
    }

    if(_categoriaManager.existeCategoria(idCategoria)){
        mostrarProducto(idCategoria);
        return;
    }

    cout << "NO HAY REGISTROS" << endl;
    return;
}

void AlmacenManager::mostrarProducto(){
  int cantidad = _repo.getCantidadRegistros();
  Producto *vProducto = new Producto[cantidad];

  if(vProducto == nullptr){
    cout << "No se pudo asignar memoria..." << endl;
    exit(-100);
  }

  _repo.leerTodos(vProducto, cantidad);

  cout << "PRODUCTOS: " << endl;

  for(int i=0; i<cantidad; i++){
    if(vProducto[i].getEstado()){
        mostrarLista(vProducto[i]);
    }
  }
    delete [] vProducto;
}

void AlmacenManager::mostrarProducto(int idCategoria){
  int cantidad = _repo.getCantidadRegistros();
  Producto *vProducto = new Producto[cantidad];

  if(vProducto == nullptr){
    cout << "No se pudo asignar memoria..." << endl;
    exit(-100);
  }

  _repo.leerTodos(vProducto, cantidad);

  system("cls");
  cout << "PRODUCTOS DE LA CATEGORIA SELECCIONADO:" << endl;

  for(int i=0; i<cantidad; i++){

    if(vProducto[i].getEstado()){

        if(vProducto[i].getIdCategoria() == idCategoria){
            mostrarLista(vProducto[i]);
        }

    }

  }
    delete [] vProducto;
}

int AlmacenManager::obtenerStock(int id){
  int cantidad = _repo.getCantidadRegistros();
  Producto *vProducto = new Producto[cantidad];

  if(vProducto == nullptr){
    cout << "No se pudo asignar memoria..." << endl;
    exit(-100);
  }

  _repo.leerTodos(vProducto, cantidad);

  for(int i=0; i<cantidad; i++){
    if(vProducto[i].getEstado() && vProducto[i].getId() == id){
        return vProducto[i].getStock();
    }
  }
  delete [] vProducto;
  return 0;

}

bool AlmacenManager::validarID(int id){
  int cantidad = _repo.getCantidadRegistros();
  Producto *vProducto = new Producto[cantidad];

  if(vProducto == nullptr){
    cout << "No se pudo asignar memoria..." << endl;
    return false;
  }

  _repo.leerTodos(vProducto, cantidad);

  for(int i=0; i<cantidad; i++){
    if(vProducto[i].getEstado() && vProducto[i].getId() == id){
        return true;
    }
  }
  delete [] vProducto;
  return false;
}

float AlmacenManager::obtenerPrecio(int id){
    int cantidad = _repo.getCantidadRegistros();
  Producto *vProducto = new Producto[cantidad];

  if(vProducto == nullptr){
    cout << "No se pudo asignar memoria..." << endl;
    exit(-100);
  }

  _repo.leerTodos(vProducto, cantidad);

  for(int i=0; i<cantidad; i++){
    if(vProducto[i].getEstado() && vProducto[i].getId() == id){
        return vProducto[i].getPrecio();
    }
  }
  delete [] vProducto;
  return 0;
}

void AlmacenManager::descontarStock(int id, int cantidad){
  int pos = _repo.buscarID(id);
  Producto reg = _repo.leer(pos);

  if(reg.getEstado()){

    int nuevo = reg.getStock() - cantidad;

    if(nuevo >= 0){
        reg.setStock(nuevo);
        _repo.guardar(pos, reg);
    }

  }else{
    cout << "NO SE PUDO ACTUALIZAR EL STOCK" << endl;
  }
}

void AlmacenManager::rellenarStock(int id, int cantidad){
  int pos = _repo.buscarID(id);
  Producto reg = _repo.leer(pos);

  if(reg.getEstado()){

    int nuevo = reg.getStock() + cantidad;

    if(nuevo >= 0){
        reg.setStock(nuevo);
        _repo.guardar(pos, reg);
    }

  }else{
    cout << "NO SE PUDO ACTUALIZAR EL STOCK" << endl;
  }
}

void AlmacenManager::eliminarProducto(){
  int id, pos;
  cout << "Ingrese el ID del producto: ";
  id = pedirEnteroValido();

  pos = _repo.buscarID(id);
  if(_repo.eliminar(pos)){
    cout << "REGISTRO ELIMINADO" << endl;
    return;
  }

  cout << "NO SE PUDO ELIMINAR EL REGISTRO" << endl;
  return;
}

int AlmacenManager::obtenerCategoriaProducto(int id){
    int cantidad = _repo.getCantidadRegistros();

    for(int i=0; i<cantidad; i++){
        if(_repo.leer(i).getEstado() && _repo.leer(i).getId() == id){
            return _repo.leer(i).getIdCategoria();
        }
  }

  return 0;
}

void AlmacenManager::actualizarProducto(){
  int id, pos, opc;

  cout << "Ingrese el ID del cliente: ";
  id = pedirEnteroValido();

  /// HABRÁ QUE VALIDAR ACÁ?

  pos = _repo.buscarID(id);
  Producto reg = _repo.leer(pos);

  system("cls");
  cout << "Que desea actualizar?" << endl;
  cout << " 1 - NOMBRE" << endl;
  cout << " 2 - PRECIO" << endl;
  cout << " 3 - STOCK" << endl;
  cout << "-------------" << endl;
  cout << " 0 - SALIR" << endl;
  cout << " Opcion: ";
  opc = pedirEnteroValido();

  switch(opc){
    case 0:{
        return;
     }
    case 1:{
        string nombre;

        do{
          cout << "Ingrese el nuevo nombre: ";
          nombre = cargarCadena();
        }while(!validarCadena(nombre));

        reg.setNombre(nombre);
        _repo.guardar(pos, reg);

        cout << "NOMBRE ACTUALIZADO" << endl;
        return;

     }
     case 2:{
        float precio;

        cout << "Ingrese el nuevo precio: ";
        precio = pedirFlotanteValido();

        if(precio > 0){
            reg.setPrecio(precio);
            _repo.guardar(pos, reg);

            cout << "PRECIO ACTUALIZADO" << endl;
            return;
        }

        cout << "NO SE PUDO ACTUALIZAR";
        return;
     }
     case 3:{
        int stock;

        cout << "Ingrese el nuevo stock: ";
        stock = pedirEnteroValido();

        if(stock > 0){
            reg.setStock(stock);
            _repo.guardar(pos, reg);

            cout << "STOCK ACTUALIZADO" << endl;
            return;
        }


        cout << "NO SE PUDO ACTUALIZAR";
        return;
     }
   }
}

void AlmacenManager::numeroProductosProveedor(){
    int cantidad = _repo.getCantidadRegistros();

    Producto *vProducto = new Producto[cantidad];

    if(vProducto == nullptr){
        cout << "No se pudo asignar memoria..." << endl;
        return;
    }

    _repo.leerTodos(vProducto, cantidad);

    int totalIDs = _proveedorManager.obtenerNumeroProximoID();
    int *cantProveedores = new int[totalIDs]();

    if(cantProveedores == nullptr){
        delete[] vProducto;
        return;
    }


    for(int i = 0; i < cantidad; i++){
        if(vProducto[i].getEstado()){
            int idProv = vProducto[i].getIdProveedor();

            if (idProv > 0 && idProv < totalIDs) {
                cantProveedores[idProv - 1]++;
            }
        }
    }

    cout << "--- REPORTE DE PRODUCTOS POR PROVEEDOR ---" << endl;
    for(int j = 0; j < totalIDs - 1; j++){
        if(cantProveedores[j] > 0){
            cout << "PROVEEDOR ID " << (j + 1) << endl;
            cout << "PRODUCTOS ASIGNADOS: " << cantProveedores[j] << endl;
            cout << "-------------------------" << endl;
        }
    }

    delete[] vProducto;
    delete[] cantProveedores;
}

void AlmacenManager::listarBajoStock(){
  int cantidad = _repo.getCantidadRegistros();
  Producto *vProducto = new Producto[cantidad];

  if(vProducto == nullptr){
    cout << "No se pudo asignar memoria..." << endl;
    exit(-100);
  }

  _repo.leerTodos(vProducto, cantidad);

  cout << "PRODUCTOS CON MENOS DE 5 UNIDADES DISPONIBLES: " << endl;
  for(int i=0; i<cantidad; i++){

    if(vProducto[i].getEstado()){

        if(vProducto[i].getStock() <= 5){
            mostrarLista(vProducto[i]);
            cout << endl;
        }

    }

  }

  delete [] vProducto;
  return;
}

void AlmacenManager::mostrarNombresAZ(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay productos registrados." << endl;
        return;
    }

    Producto *vProducto = new Producto[cantidad];
    _repo.leerTodos(vProducto, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vProducto[j].getNombre() < vProducto[j_min].getNombre()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Producto temp = vProducto[i];
            vProducto[i] = vProducto[j_min];
            vProducto[j_min] = temp;
        }
    }

    cout << "PRODUCTOS POR NOMBRE (A-Z): " << endl;
    for (int x = 0; x < cantidad; x++) {
        if (vProducto[x].getEstado()) {
            mostrarLista(vProducto[x]);
        }
    }

    delete[] vProducto;
}
void AlmacenManager::mostrarNombresZA(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay productos registrados." << endl;
        return;
    }

    Producto *vProducto = new Producto[cantidad];
    _repo.leerTodos(vProducto, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vProducto[j].getNombre() < vProducto[j_min].getNombre()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Producto temp = vProducto[i];
            vProducto[i] = vProducto[j_min];
            vProducto[j_min] = temp;
        }
    }

    cout << "PRODUCTOS POR NOMBRE (Z-A): " << endl;
    for (int x = cantidad - 1; x >= 0; x--) {
        if (vProducto[x].getEstado()) {
            mostrarLista(vProducto[x]);
        }
    }

    delete[] vProducto;
}
void AlmacenManager::mostrarPreciosAltoBajo(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay productos registrados." << endl;
        return;
    }

    Producto *vProducto = new Producto[cantidad];
    _repo.leerTodos(vProducto, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vProducto[j].getPrecio() < vProducto[j_min].getPrecio()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Producto temp = vProducto[i];
            vProducto[i] = vProducto[j_min];
            vProducto[j_min] = temp;
        }
    }

    cout << "PRODUCTOS POR PRECIO (MAYOR A MENOR): " << endl;
    for (int x = cantidad - 1; x >= 0; x--) {
        if (vProducto[x].getEstado()) {
            mostrarLista(vProducto[x]);
        }
    }

    delete[] vProducto;
}
void AlmacenManager::mostrarPreciosBajoAlto(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay productos registrados." << endl;
        return;
    }

    Producto *vProducto = new Producto[cantidad];
    _repo.leerTodos(vProducto, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vProducto[j].getPrecio() < vProducto[j_min].getPrecio()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Producto temp = vProducto[i];
            vProducto[i] = vProducto[j_min];
            vProducto[j_min] = temp;
        }
    }

    cout << "PRODUCTOS POR PRECIO (MENOR A MAYOR): " << endl;
    for (int x = 0; x < cantidad; x++) {
        if (vProducto[x].getEstado()) {
            mostrarLista(vProducto[x]);
        }
    }

    delete[] vProducto;
}
void AlmacenManager::mostrarStockAltoBajo(){
     int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay productos registrados." << endl;
        return;
    }

    Producto *vProducto = new Producto[cantidad];
    _repo.leerTodos(vProducto, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vProducto[j].getStock() < vProducto[j_min].getStock()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Producto temp = vProducto[i];
            vProducto[i] = vProducto[j_min];
            vProducto[j_min] = temp;
        }
    }

    cout << "PRODUCTOS POR STOCK (MAYOR A MENOR): " << endl;
    for (int x = cantidad - 1; x >= 0; x--) {
        if (vProducto[x].getEstado()) {
            mostrarLista(vProducto[x]);
        }
    }

    delete[] vProducto;
}
void AlmacenManager::mostrarStockBajoAlto(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay productos registrados." << endl;
        return;
    }

    Producto *vProducto = new Producto[cantidad];
    _repo.leerTodos(vProducto, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vProducto[j].getStock() < vProducto[j_min].getStock()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Producto temp = vProducto[i];
            vProducto[i] = vProducto[j_min];
            vProducto[j_min] = temp;
        }
    }

    cout << "PRODUCTOS POR STOCK (MENOR A MAYOR): " << endl;
    for (int x = 0; x < cantidad; x++) {
        if (vProducto[x].getEstado()) {
            mostrarLista(vProducto[x]);
        }
    }

    delete[] vProducto;
}

void AlmacenManager::mostrarLista(const Producto &reg){
  cout << "----------------------------" <<endl;
  cout << "ID: " << reg.getId() << endl;
  cout << "ID Categoria: " << reg.getIdCategoria() << endl;
  cout << "ID Proveedor: " << reg.getIdProveedor() << endl;
  cout << "Nombre: "<< reg.getNombre() << endl;
  cout << "Precio: " << reg.getPrecio() << endl;
  cout << "Stock: " << reg.getStock() << endl;
  cout << "----------------------------" <<endl;
}

void AlmacenManager::crearBackup(){
    _repo.crearBackup();
}
void AlmacenManager::cargarBackup(){
    _repo.cargarBackup();
}

