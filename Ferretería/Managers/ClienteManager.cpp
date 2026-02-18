#include <iostream>
#include <string.h>

#include "ClienteManager.h"
#include "../Entidades/Cliente.h"

#include "../Utils.h"

using namespace std;



ClienteManager::ClienteManager(){

}

void ClienteManager::cargar(){
  int id;
  string nombre;
  string apellido;
  string dni;

  id = _repo.getNuevoID();

  cout << "Cargar Nuevo Personal ----" << endl;
  cout << "ID: " << id << endl;

  do{
    cout << "Ingrese DNI: ";
    dni = cargarCadena();
  } while(!validarDNI(dni));

  do{
    cout << "Ingrese nombre: ";
    nombre = cargarCadena();
  }while(!validarCadena(nombre));

  do{
    cout << "Ingrese apellido: ";
    apellido = cargarCadena();
  }while(!validarCadena(apellido));


  if(_repo.guardar(Cliente(id, nombre, apellido, dni))){
    cout << "Se agrego correctamente" << endl;
  }
  else{
    cout << "Error al intentar guardar el personal." << endl;
  }

}

void ClienteManager::mostrar(){
  int cantidad = _repo.getCantidadRegistros();
  Cliente *vCliente = new Cliente[cantidad];

  if(vCliente == nullptr){
    cout << "No se pudo asignar memoria..." << endl;
    exit(-100);
  }

  _repo.leerTodos(vCliente, cantidad);

  cout << "CLIENTES: " << endl;

  for(int i=0; i<cantidad; i++){
    if(vCliente[i].getEstado()){
        mostrarLista(vCliente[i]);
    }
  }
    delete [] vCliente;
}

void ClienteManager::eliminar(){
  int id, pos;
  cout << "Ingrese el ID del cliente: ";
  id = pedirEnteroValido();

  pos = _repo.buscarID(id);
  if(_repo.eliminar(pos)){
    cout << "REGISTRO ELIMINADO" << endl;
    return;
  }

  cout << "NO SE PUDO ELIMINAR EL REGISTRO" << endl;
  return;
}

void ClienteManager::actualizar(){
  int id, pos, opc;
  cout << "Ingrese el ID del cliente: ";
  id = pedirEnteroValido();

  pos = _repo.buscarID(id);
  Cliente reg = _repo.leer(pos);

  system("cls");
  cout << "Que desea actualizar?" << endl;
  cout << " 1 - NOMBRE" << endl;
  cout << " 2 - APELLIDO" << endl;
  cout << " 3 - DNI" << endl;
  cout << " Opcion: ";
  opc = pedirEnteroValido();

  switch(opc){
    case 0:{
        cout << "Error" << endl;
        system("pause");
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
        string apellido;

        do{
          cout << "Ingrese el nuevo apellido: ";
          apellido = cargarCadena();
        }while(!validarCadena(apellido));

        reg.setApellido(apellido);
        _repo.guardar(pos, reg);

        cout << "APELLIDO ACTUALIZADO" << endl;
        return;
     }
     case 3:{
        string dni;

        do{
          cout << "Ingrese el nuevo DNI: ";
          dni = cargarCadena();
        }while(!validarDNI(dni));

        reg.setDni(dni);
        _repo.guardar(pos, reg);

        cout << "DNI ACTUALIZADO" << endl;
        return;
     }
 }

}

bool ClienteManager::existeRegistro(int id){
   int pos = _repo.buscarID(id);

   if(pos >= 0){
        return _repo.leer(pos).getEstado();
   }
   return false;
}

void ClienteManager::mostrarNombresAZ() {
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    Cliente *vCliente = new Cliente[cantidad];
    _repo.leerTodos(vCliente, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vCliente[j].getNombre() < vCliente[j_min].getNombre()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Cliente temp = vCliente[i];
            vCliente[i] = vCliente[j_min];
            vCliente[j_min] = temp;
        }
    }

    cout << "CLIENTES POR NOMBRE (A-Z): " << endl;
    for (int x = 0; x < cantidad; x++) {
        if (vCliente[x].getEstado()) {
            mostrarLista(vCliente[x]);
        }
    }

    delete[] vCliente;
}
void ClienteManager::mostrarNombresZA(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    Cliente *vCliente = new Cliente[cantidad];
    _repo.leerTodos(vCliente, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vCliente[j].getNombre() < vCliente[j_min].getNombre()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Cliente temp = vCliente[i];
            vCliente[i] = vCliente[j_min];
            vCliente[j_min] = temp;
        }
    }

    cout << "CLIENTES POR NOMBRE (Z-A): " << endl;
    for (int x = cantidad - 1; x >= 0; x--) {
        if (vCliente[x].getEstado()) {
            mostrarLista(vCliente[x]);
        }
    }

    delete[] vCliente;
}
void ClienteManager::mostrarApellidosAZ(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    Cliente *vCliente = new Cliente[cantidad];
    _repo.leerTodos(vCliente, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vCliente[j].getApellido() < vCliente[j_min].getApellido()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Cliente temp = vCliente[i];
            vCliente[i] = vCliente[j_min];
            vCliente[j_min] = temp;
        }
    }

    cout << "CLIENTES POR APELLIDO (A-Z): " << endl;
    for (int x = 0; x < cantidad; x++) {
        if (vCliente[x].getEstado()) {
            mostrarLista(vCliente[x]);
        }
    }

    delete[] vCliente;
}
void ClienteManager::mostrarApellidosZA(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    Cliente *vCliente = new Cliente[cantidad];
    _repo.leerTodos(vCliente, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vCliente[j].getApellido() < vCliente[j_min].getApellido()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Cliente temp = vCliente[i];
            vCliente[i] = vCliente[j_min];
            vCliente[j_min] = temp;
        }
    }

    cout << "CLIENTES POR APELLIDO (Z-A): " << endl;
    for (int x = cantidad - 1; x >= 0; x--) {
        if (vCliente[x].getEstado()) {
            mostrarLista(vCliente[x]);
        }
    }

    delete[] vCliente;
}

void ClienteManager::mostrar(int id){
    int pos = _repo.buscarID(id);
    cout << "Cliente asignado: " << _repo.leer(pos).getNombre() << " " << _repo.leer(pos).getApellido() << " - " << _repo.leer(pos).getDni() << endl;
}

void ClienteManager::crearBackup(){
    _repo.crearBackup();
}
void ClienteManager::cargarBackup(){
    _repo.cargarBackup();
}

void ClienteManager::mostrarLista(const Cliente &reg){
  cout << "----------------------------" <<endl;
  cout << "ID: " << reg.getId() << endl;
  cout << "DNI: " << reg.getDni() << endl;
  cout << "Nombre: "<< reg.getNombre() << endl;
  cout << "Apellido " << reg.getApellido() << endl;
  cout << "----------------------------" <<endl;
}

