#include <iostream>

#include "CategoriaManager.h"
#include "../Entidades/Categoria.h"

#include <string.h>
#include "../Utils.h"

using namespace std;


CategoriaManager::CategoriaManager(){

}

void CategoriaManager::cargar(){
  string nombre;
  int id;

  id = _repo.getNuevoID();

  cout << "NUEVA CATEGORIA" << endl;
  do{
    cout << "Ingrese el nombre: ";
    nombre = cargarCadena();
  }while(!validarCadena(nombre));

  if(_repo.guardar(Categoria(id, nombre))){
    cout << "CATEGORIA GUARDADA" << endl;
  }else{
    cout << "NO SE PUDO GUARDAR LA CATEGORIA" << endl;
  }
}

void CategoriaManager::mostrar(){
  int cantidad = _repo.getCantidadRegistros();
  Categoria *vCategoria = new Categoria[cantidad];

  if(vCategoria == nullptr){
    cout << "No se pudo asignar memoria..." << endl;
    exit(-100);
  }

  _repo.leerTodos(vCategoria, cantidad);

  cout << "CATEGORIAS: " << endl;

  for(int i=0; i<cantidad; i++){
    if(vCategoria[i].getEstado()){
        mostrarLista(vCategoria[i]);
    }
  }
    delete [] vCategoria;
}

void CategoriaManager::eliminar(){
  int id, pos;
  cout << "Ingrese el ID de la categoria: ";
  id = pedirEnteroValido();

  pos = _repo.buscarID(id);
  if(_repo.eliminar(pos)){
    cout << "REGISTRO ELIMINADO" << endl;
    return;
  }

  cout << "NO SE PUDO ELIMINAR EL REGISTRO" << endl;
  return;
}

void CategoriaManager::actualizar(){
  int id, pos, opc;

  cout << "Ingrese el ID de la categoria: ";
  id = pedirEnteroValido();

  pos = _repo.buscarID(id);
  Categoria reg = _repo.leer(pos);

  system("cls");
  cout << "Que desea modificar?" << endl;
  cout << " 1 - NOMBRE" << endl;
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
  }

}

bool CategoriaManager::existeCategoria(int id){
  int cantidad = _repo.getCantidadRegistros();
  Categoria *vCategoria = new Categoria[cantidad];

  if(vCategoria == nullptr){
    cout << "No se pudo asignar memoria..." << endl;
    exit(-100);
  }

  _repo.leerTodos(vCategoria, cantidad);

  for(int i=0; i<cantidad; i++){
    if(vCategoria[i].getEstado()){
        if(vCategoria[i].getId() == id){
            delete [] vCategoria;
            return true;
        }
    }
  }

  cout << "SIN REGISTROS" << endl;
  delete [] vCategoria;
  return false;
}


void CategoriaManager::mostrarLista(const Categoria &reg){
  cout << "ID: " << reg.getId() << endl;
  cout << "Nombre categoria: " << reg.getNombre() << endl;
  cout << "------------" <<endl;
}
