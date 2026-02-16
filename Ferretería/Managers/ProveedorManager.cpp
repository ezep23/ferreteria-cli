#include <iostream>

#include "ProveedorManager.h"
#include "../Entidades/Proveedor.h"

#include "../Utils.h"

using namespace std;


ProveedorManager::ProveedorManager(){

}

bool ProveedorManager::existeProveedor(int id){
    int pos = _repo.buscarID(id);
    Proveedor reg = _repo.leer(pos);

    if(reg.getEstado()){
        return true;
    }

    return false;
}

void ProveedorManager::cargar(){
  int id;
  int idE;
  string nombre;
  string apellido;
  string tel;
  string email;
  string dni;

  id = _repo.getNuevoID();

  cout << "CARGAR NUEVO PROVEEDOR ----" << endl;
  cout << "ID EMPRESA (0 - Salir)" << endl;
  cout << "Opcion: ";
  cin >> idE;

  if(idE <= 0){
    return;
  }

  bool empresaExiste = _empresaManager.validarEmpresaExiste(idE);

  if(!empresaExiste){
    cout << "NO SE HA ENCONTRADO O NO EXISTE ESA EMPRESA" << endl;
    return;
  }
  cout << "ID PROVEEDOR: " << id << endl;

  cout << "Ingrese DNI: ";
  dni = cargarCadena();

  if(!validarDNI(dni)){
    do{
        cout << "Error, ingrese un dni correcto: ";

        dni = cargarCadena();
        validarDNI(dni);

    }while(validarDNI(dni));
  }

  cout << "Ingrese nombre: ";
  nombre = cargarCadena();

  cout << "Ingrese apellido: ";
  apellido = cargarCadena();

  cout << "Ingrese telefono: ";
  tel = cargarCadena();

  cout << "Ingrese email: ";
  email = cargarCadena();

  if(_repo.guardar(Proveedor(nombre, apellido, tel, email, dni, id, idE))){
    cout << "Se agrego correctamente" << endl;
  }
  else{
    cout << "Error al intentar guardar el personal." << endl;
  }

}

int ProveedorManager::obtenerNumeroProximoID(){
    return _repo.getNuevoID();
}

void ProveedorManager::mostrar(){
  int cantidad = _repo.getCantidadRegistros();
  Proveedor *vProveedor = new Proveedor[cantidad];

  if(vProveedor == nullptr){
    cout << "No se pudo asignar memoria..." << endl;
    exit(-100);
  }

  _repo.leerTodos(vProveedor, cantidad);

  cout << "PROVEEDORES: " << endl;

  for(int i=0; i<cantidad; i++){
    if(vProveedor[i].getEstado()){
        mostrarLista(vProveedor[i]);
    }
  }
    delete [] vProveedor;
}

void ProveedorManager::eliminar(){
  int id, pos;
  cout << "Ingrese el ID del proveedor: ";
  cin >> id;

  pos = _repo.buscarID(id);
  if(_repo.eliminar(pos)){
    cout << "REGISTRO ELIMINADO" << endl;
    return;
  }

  cout << "NO SE PUDO ELIMINAR EL REGISTRO" << endl;
  return;
}

void ProveedorManager::actualizar(){
  int id, pos, opc;
  cout << "Ingrese el ID del proveedor: ";
  cin >> id;

  pos = _repo.buscarID(id);
  Proveedor reg = _repo.leer(pos);

  system("cls");
  cout << "Que desea eliminar?" << endl;
  cout << " 1 - NOMBRE" << endl;
  cout << " 2 - APELLIDO" << endl;
  cout << " 3 - TELEFONO" << endl;
  cout << " 4 - EMAIL" << endl;
  cout << " 5 - DNI" << endl;
  cout << " 6 - ESTADO" << endl;
  cout << " Opcion: ";
  cin >> opc;

  switch(opc){
    case 0:{
        cout << "Error" << endl;
        system("pause");
        return;
     }
    case 1:{
        string nombre;
        nombre = cargarCadena();

        reg.setNombre(nombre);
        _repo.guardar(pos, reg);

        cout << "NOMBRE ACTUALIZADO" << endl;
        return;

     }
    case 2:{
        string apellido;
        apellido = cargarCadena();

        reg.setApellido(apellido);
        _repo.guardar(pos, reg);

        cout << "APELLIDO ACTUALIZADO" << endl;
        return;
     }
     case 3:{
        string tel;
        tel = cargarCadena();

        reg.setTelefono(tel);
        _repo.guardar(pos, reg);

        cout << "TELEFONO ACTUALIZADO" << endl;
        return;
     }
     case 4:{
        string email;
        email = cargarCadena();

        reg.setEmail(email);
        _repo.guardar(pos, reg);

        cout << "EMAIL ACTUALIZADO" << endl;
        return;
     }
     case 5:{
        string dni;
        dni = cargarCadena();

        if(!validarDNI(dni)){
            do{
                cout << "Error, ingrese un dni correcto: ";

                dni = cargarCadena();
                validarDNI(dni);

            }while(validarDNI(dni));
        }

        reg.setDni(dni);
        _repo.guardar(pos, reg);

        cout << "DNI ACTUALIZADO" << endl;
        return;
     }
    case 6:{
        reg.setEstado(!reg.getEstado());
        _repo.guardar(pos, reg);

        system("cls");
        cout << "ESTADO ACTUALIZADO" << endl;
        return;
    }
 }

}

void ProveedorManager::mostrarNombresAZ() {
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay proveedores registrados." << endl;
        return;
    }

    Proveedor *vProveedor = new Proveedor[cantidad];
    _repo.leerTodos(vProveedor, cantidad);

    // ORDENAMIENTO (Selection Sort sin desempate)
    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vProveedor[j].getNombre() < vProveedor[j_min].getNombre()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Proveedor temp = vProveedor[i];
            vProveedor[i] = vProveedor[j_min];
            vProveedor[j_min] = temp;
        }
    }

    cout << "PROVEEDORES POR NOMBRE (A-Z): " << endl;
    for (int x = 0; x < cantidad; x++) {
        if (vProveedor[x].getEstado()) {
            mostrarLista(vProveedor[x]);
        }
    }

    delete[] vProveedor;
}
void ProveedorManager::mostrarNombresZA(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay proveedores registrados." << endl;
        return;
    }

    Proveedor *vProveedor = new Proveedor[cantidad];
    _repo.leerTodos(vProveedor, cantidad);

    // ORDENAMIENTO (Selection Sort sin desempate)
    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vProveedor[j].getNombre() < vProveedor[j_min].getNombre()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Proveedor temp = vProveedor[i];
            vProveedor[i] = vProveedor[j_min];
            vProveedor[j_min] = temp;
        }
    }

    cout << "PROVEEDORES POR NOMBRE (Z-A): " << endl;
    for (int x = cantidad - 1; x >= 0; x--) {
        if (vProveedor[x].getEstado()) {
            mostrarLista(vProveedor[x]);
        }
    }

    delete[] vProveedor;
}
void ProveedorManager::mostrarApellidosAZ(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay proveedores registrados." << endl;
        return;
    }

    Proveedor *vProveedor = new Proveedor[cantidad];
    _repo.leerTodos(vProveedor, cantidad);

    // ORDENAMIENTO (Selection Sort sin desempate)
    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vProveedor[j].getApellido() < vProveedor[j_min].getApellido()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Proveedor temp = vProveedor[i];
            vProveedor[i] = vProveedor[j_min];
            vProveedor[j_min] = temp;
        }
    }

    cout << "PROVEEDORES POR APELLIDO (A-Z): " << endl;
    for (int x = 0; x < cantidad; x++) {
        if (vProveedor[x].getEstado()) {
            mostrarLista(vProveedor[x]);
        }
    }

    delete[] vProveedor;
}
void ProveedorManager::mostrarApellidosZA(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay proveedores registrados." << endl;
        return;
    }

    Proveedor *vProveedor = new Proveedor[cantidad];
    _repo.leerTodos(vProveedor, cantidad);

    // ORDENAMIENTO (Selection Sort sin desempate)
    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vProveedor[j].getApellido() < vProveedor[j_min].getApellido()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Proveedor temp = vProveedor[i];
            vProveedor[i] = vProveedor[j_min];
            vProveedor[j_min] = temp;
        }
    }

    cout << "PROVEEDORES POR APELLIDO (Z-A): " << endl;
    for (int x = cantidad - 1; x >= 0; x--) {
        if (vProveedor[x].getEstado()) {
            mostrarLista(vProveedor[x]);
        }
    }

    delete[] vProveedor;
}


void ProveedorManager::mostrarLista(const Proveedor &reg){
  cout << "ID: " << reg.getId() << endl;
  cout << "ID Empresa: " << reg.getIdEmpresa() << endl;
  cout << "DNI: " << reg.getDni() << endl;
  cout << "Nombre: "<< reg.getNombre() << endl;
  cout << "Apellido: " << reg.getApellido() << endl;
  cout << "Telefono: " << reg.getTelefono() << endl;
  cout << "Email: " << reg.getEmail() << endl;
  cout << "------------" <<endl;
}

