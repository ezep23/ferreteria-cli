#include <iostream>

#include "EmpleadoManager.h"
#include "../Entidades/Empleado.h"

#include "../Utils.h"

using namespace std;

EmpleadoManager::EmpleadoManager(){

}

void EmpleadoManager::cargar(){
  int id;
  string nombre;
  string apellido;
  string tel;
  string email;
  string dni;

  id = _repo.getNuevoID();

  cout << "Cargar Nuevo Personal ----" << endl;
  cout << "ID: " << id << endl;

  do{
    cout << "Ingrese DNI: ";
    dni = cargarCadena();
  }while(!validarDNI(dni));

  do{
    cout << "Ingrese nombre: ";
    nombre = cargarCadena();
  }while(!validarCadena(nombre));

  do{
    cout << "Ingrese apellido: ";
    apellido = cargarCadena();
  }while(!validarCadena(apellido));

  do{
    cout << "Ingrese telefono: ";
    telefono = cargarCadena();
  }while(!validarCadena(telefono));

  do{
    cout << "Ingrese email: ";
    email = cargarCadena();
  }while(!validarCadena(email));

  if(_repo.guardar(Empleado(nombre, apellido, tel, email, dni, id))){
    cout << "Se agrego correctamente" << endl;
  }
  else{
    cout << "Error al intentar guardar el personal." << endl;
  }

}

void EmpleadoManager::mostrar(){
  int cantidad = _repo.getCantidadRegistros();
  Empleado *vEmpleado = new Empleado[cantidad];

  if(vEmpleado == nullptr){
    cout << "No se pudo asignar memoria..." << endl;
    exit(-100);
  }

  _repo.leerTodos(vEmpleado, cantidad);

  cout << "EMPLEADOS: " << endl;

  for(int i=0; i<cantidad; i++){
    if(vEmpleado[i].getEstado()){
        mostrarLista(vEmpleado[i]);
    }
  }
    delete [] vEmpleado;
}

void EmpleadoManager::eliminar(){
  int id, pos;
  cout << "Ingrese el ID del empleado: ";
  id = pedirEnteroValido();

  pos = _repo.buscarID(id);
  if(_repo.eliminar(pos)){
    cout << "REGISTRO ELIMINADO" << endl;
    return;
  }

  cout << "NO SE PUDO ELIMINAR EL REGISTRO" << endl;
  return;
}

void EmpleadoManager::actualizar(){
  int id, pos, opc;
  cout << "Ingrese el ID del empleado: ";
  id = pedirEnteroValido();

  pos = _repo.buscarID(id);
  Empleado reg = _repo.leer(pos);

  system("cls");
  cout << "Que desea eliminar?" << endl;
  cout << " 1 - NOMBRE" << endl;
  cout << " 2 - APELLIDO" << endl;
  cout << " 3 - TELEFONO" << endl;
  cout << " 4 - EMAIL" << endl;
  cout << " 5 - DNI" << endl;
  cout << " 6 - ESTADO" << endl;
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
            cout << "Ingrese el nuevo nombre: "
            nombre = cargarCadena();
        } while (!validarCadena(nombre));

        reg.setNombre(nombre);
        _repo.guardar(pos, reg);

        cout << "NOMBRE ACTUALIZADO" << endl;
        return;

     }
    case 2:{
        string apellido;

        do{
            cout << "Ingrese el nuevo apellido: "
            apellido = cargarCadena();
        } while (!validarCadena(apellido));

        reg.setApellido(apellido);
        _repo.guardar(pos, reg);

        cout << "APELLIDO ACTUALIZADO" << endl;
        return;
     }
     case 3:{
        string tel;

        do{
            cout << "Ingrese el nuevo telefono: "
            tel = cargarCadena();
        } while (!validarCadena(tel));

        reg.setTelefono(tel);
        _repo.guardar(pos, reg);

        cout << "TELEFONO ACTUALIZADO" << endl;
        return;
     }
     case 4:{
        string email;

        do{
            cout << "Ingrese el nuevo email: "
            email = cargarCadena();
        } while (!validarCadena(email));

        reg.setEmail(email);
        _repo.guardar(pos, reg);

        cout << "EMAIL ACTUALIZADO" << endl;
        return;
     }
     case 5:{
        string dni;

        do{
            cout << "Ingrese el nuevo DNI: ";
            dni = cargarCadena)();
        }while(!validarDNI(dni));

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

bool EmpleadoManager::existeRegistro(int id){
   int pos = _repo.buscarID(id);

   if(pos){

        if(_repo.leer(pos).getEstado()){
            return true;
        }

        return false;
   }

   return false;
}

void EmpleadoManager::mostrar(int id){
    int pos = _repo.buscarID(id);
    cout << "Empleado asignado: " << _repo.leer(pos).getNombre() << " - " << _repo.leer(pos).getDni() << endl;
}

int EmpleadoManager::obtenerNumeroProximoID(){
    return _repo.getNuevoID();
}

void EmpleadoManager::mostrarNombresAZ() {
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay empleados registrados." << endl;
        return;
    }

    Empleado *vEmpleado = new Empleado[cantidad];
    _repo.leerTodos(vEmpleado, cantidad);

    // ORDENAMIENTO (Selection Sort sin desempate)
    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vEmpleado[j].getNombre() < vEmpleado[j_min].getNombre()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Empleado temp = vEmpleado[i];
            vEmpleado[i] = vEmpleado[j_min];
            vEmpleado[j_min] = temp;
        }
    }

    cout << "EMPLEADOS POR NOMBRE (A-Z): " << endl;
    for (int x = 0; x < cantidad; x++) {
        if (vEmpleado[x].getEstado()) {
            mostrarLista(vEmpleado[x]);
        }
    }

    delete[] vEmpleado;
}
void EmpleadoManager::mostrarNombresZA(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay empleados registrados." << endl;
        return;
    }

    Empleado *vEmpleado = new Empleado[cantidad];
    _repo.leerTodos(vEmpleado, cantidad);

    // ORDENAMIENTO (Selection Sort sin desempate)
    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vEmpleado[j].getNombre() < vEmpleado[j_min].getNombre()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Empleado temp = vEmpleado[i];
            vEmpleado[i] = vEmpleado[j_min];
            vEmpleado[j_min] = temp;
        }
    }

    cout << "EMPLEADOS POR NOMBRE (Z-A): " << endl;
    for (int x = cantidad - 1; x >= 0; x--) {
        if (vEmpleado[x].getEstado()) {
            mostrarLista(vEmpleado[x]);
        }
    }

    delete[] vEmpleado;
}
void EmpleadoManager::mostrarApellidosAZ(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay empleados registrados." << endl;
        return;
    }

    Empleado *vEmpleado = new Empleado[cantidad];
    _repo.leerTodos(vEmpleado, cantidad);

    // ORDENAMIENTO (Selection Sort sin desempate)
    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vEmpleado[j].getApellido() < vEmpleado[j_min].getApellido()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Empleado temp = vEmpleado[i];
            vEmpleado[i] = vEmpleado[j_min];
            vEmpleado[j_min] = temp;
        }
    }

    cout << "EMPLEADOS POR APELLIDO (A-Z): " << endl;
    for (int x = 0; x < cantidad; x++) {
        if (vEmpleado[x].getEstado()) {
            mostrarLista(vEmpleado[x]);
        }
    }

    delete[] vEmpleado;
}
void EmpleadoManager::mostrarApellidosZA(){
    int cantidad = _repo.getCantidadRegistros();

    if (cantidad <= 0) {
        cout << "No hay empleados registrados." << endl;
        return;
    }

    Empleado *vEmpleado = new Empleado[cantidad];
    _repo.leerTodos(vEmpleado, cantidad);

    // ORDENAMIENTO (Selection Sort sin desempate)
    for (int i = 0; i < cantidad - 1; i++) {
        int j_min = i;

        for (int j = i + 1; j < cantidad; j++) {
            if (vEmpleado[j].getApellido() < vEmpleado[j_min].getApellido()) {
                j_min = j;
            }
        }

        if (j_min != i) {
            Empleado temp = vEmpleado[i];
            vEmpleado[i] = vEmpleado[j_min];
            vEmpleado[j_min] = temp;
        }
    }

    cout << "EMPLEADOS POR APELLIDO (Z-A): " << endl;
    for (int x = cantidad - 1; x >= 0; x--) {
        if (vEmpleado[x].getEstado()) {
            mostrarLista(vEmpleado[x]);
        }
    }

    delete[] vEmpleado;
}

void EmpleadoManager::mostrarLista(const Empleado &reg){
  cout << "ID: " << reg.getId() << endl;
  cout << "DNI: " << reg.getDni() << endl;
  cout << "Nombre: "<< reg.getNombre() << endl;
  cout << "Apellido: " << reg.getApellido() << endl;
  cout << "Telefono: " << reg.getTelefono() << endl;
  cout << "Email: " << reg.getEmail() << endl;
  cout << "------------" <<endl;
}

