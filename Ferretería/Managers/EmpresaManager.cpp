#include <iostream>

#include "EmpresaManager.h"
#include "../Entidades/Empresa.h"

#include "../Utils.h"

using namespace std;


EmpresaManager::EmpresaManager(){

}

void EmpresaManager::cargar(){
  string razonSocial, nombreComercial;
  int id;

  id = _repo.getNuevoID();

  cout << "NUEVA EMPRESA" << endl;

  do{
    cout << "Ingrese la razon social: ";
    razonSocial = cargarCadena();
  } while (!validarCadenaEspacios(razonSocial));

  do{
    cout << "Ingrese el nombre comercial: ";
    nombreComercial = cargarCadena();
  } while (!validarCadenaEspacios(nombreComercial));

  if(_repo.guardar(Empresa(id, razonSocial, nombreComercial))){
    cout << "EMPRESA GUARDADA" << endl;
  }else{
    cout << "NO SE PUDO GUARDAR LA EMPRESA" << endl;
  }
}

void EmpresaManager::mostrar(){
  int cantidad = _repo.getCantidadRegistros();
  Empresa *vEmpresa = new Empresa[cantidad];

  if(vEmpresa == nullptr){
    cout << "No se pudo asignar memoria..." << endl;
    exit(-100);
  }

  _repo.leerTodos(vEmpresa, cantidad);

  cout << "EMPRESAS: " << endl;

  for(int i=0; i<cantidad; i++){
    if(vEmpresa[i].getEstado()){
        mostrarLista(vEmpresa[i]);
    }
  }
    delete [] vEmpresa;
}

void EmpresaManager::eliminar(){
  int id, pos;
  cout << "Ingrese el ID de la empresa: ";
  id = pedirEnteroValido();

  pos = _repo.buscarID(id);
  if(_repo.eliminar(pos)){
    cout << "REGISTRO ELIMINADO" << endl;
    return;
  }

  cout << "NO SE PUDO ELIMINAR EL REGISTRO" << endl;
  return;
}

void EmpresaManager::actualizar(){
  int id, pos, opc;

  cout << "Ingrese el ID de la empresa: ";
  id = pedirEnteroValido();

  pos = _repo.buscarID(id);
  Empresa reg = _repo.leer(pos);

  system("cls");
  cout << "Que desea modificar?" << endl;
  cout << " 1 - RAZON SOCIAL" << endl;
  cout << " 2 - NOMBRE COMERCIAL " << endl;
  cout << " 0 - SALIR" << endl;
  cout << " Opcion: ";
  opc = pedirEnteroValido();

  switch(opc){
    case 0:{
        return;
     }
    case 1:{
        string razonSocial;

        do{
            cout << "Ingrese la nueva razon social: ";
            razonSocial = cargarCadena();

        }while(!validarCadenaEspacios(razonSocial));

        reg.setRazonSocial(razonSocial);
        _repo.guardar(pos, reg);

        cout << "RAZON SOCIAL ACTUALIZADA" << endl;
        return;

     }
    case 2:{
        string nombreComercial;

        do{
            cout << "Ingrese el nuevo nombre comercial: ";
            nombreComercial = cargarCadena();
        }while(!validarCadenaEspacios(nombreComercial));

        reg.setNombreComercial(nombreComercial);
        _repo.guardar(pos, reg);

        cout << "NOMBRE COMERCIAL ACTUALIZADO" << endl;
        return;

    }
  }

}

bool EmpresaManager::validarEmpresaExiste(int idE){
    int pos = _repo.buscarID(idE);
    Empresa reg = _repo.leer(pos);

    if(reg.getEstado()){
        return true;
    }

    return false;
}

void EmpresaManager::mostrarNombreComercialAZ() {
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay empresas registrados." << endl;
        return;
    }

    Empresa *vEmpresa = new Empresa[cantidad];
    _repo.leerTodos(vEmpresa, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vEmpresa[j].getNombreComercial() < vEmpresa[j_min].getNombreComercial()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Empresa temp = vEmpresa[i];
            vEmpresa[i] = vEmpresa[j_min];
            vEmpresa[j_min] = temp;
        }
    }

    cout << "EMPRESAS (A-Z): " << endl;
    for (int x = 0; x < cantidad; x++) {
        if (vEmpresa[x].getEstado()) {
            mostrarLista(vEmpresa[x]);
        }
    }

    delete[] vEmpresa;
}
void EmpresaManager::mostrarNombreComercialZA(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay empresas registrados." << endl;
        return;
    }

    Empresa *vEmpresa = new Empresa[cantidad];
    _repo.leerTodos(vEmpresa, cantidad);

    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vEmpresa[j].getNombreComercial() < vEmpresa[j_min].getNombreComercial()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Empresa temp = vEmpresa[i];
            vEmpresa[i] = vEmpresa[j_min];
            vEmpresa[j_min] = temp;
        }
    }

    cout << "EMPRESAS (Z-A): " << endl;
    for (int x = cantidad - 1; x >= 0; x--) {
        if (vEmpresa[x].getEstado()) {
            mostrarLista(vEmpresa[x]);
        }
    }

    delete[] vEmpresa;
}

void EmpresaManager::mostrarNombreEmpresa(int id){
    int pos = _repo.buscarID(id);
    cout << "ID: " << _repo.leer(pos).getId() <<  " - " <<  "NOMBRE: " << _repo.leer(pos).getNombreComercial() << endl;
}

void EmpresaManager::crearBackup(){
    _repo.crearBackup();
}
void EmpresaManager::cargarBackup(){
    _repo.cargarBackup();
}

int EmpresaManager::obtenerCantidadRegistros(){
    return _repo.getCantidadRegistros();
}

void EmpresaManager::mostrarLista(const Empresa &reg){
  cout << "----------------------------" <<endl;
  cout << "ID: " << reg.getId() << endl;
  cout << "Razon social: " << reg.getRazonSocial() << endl;
  cout << "Nombre comercial: " << reg.getNombreComercial() << endl;
  cout << "----------------------------" <<endl;
}
