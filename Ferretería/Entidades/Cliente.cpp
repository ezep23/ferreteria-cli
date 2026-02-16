#include "Cliente.h"
#include <cstring>
using namespace std;

Cliente::Cliente(){
    setId(0);
    setNombre("");
    setApellido("");
    setDni("");
    setEstado(false);
}

Cliente::Cliente(int id, string nombre, string apellido, string dni){
    setId(id);
    setNombre(nombre);
    setApellido(apellido);
    setDni(dni);
    setEstado(true);
}

void Cliente::setId(int id){
    _id = id;
}

void Cliente::setEstado(bool est){
    _estado = est;
}

void Cliente::setNombre(string nombre){
    strncpy(_nombre, nombre.c_str(), 19);
}

void Cliente::setApellido(string apellido){
    strncpy(_apellido, apellido.c_str(), 19);
}

void Cliente::setDni(string dni){
    strncpy(_dni, dni.c_str(), 7);
}

string Cliente::getNombre() const{
    return string(_nombre);
}

string Cliente::getApellido() const{
    return string(_apellido);
}

string Cliente::getDni() const{
    return string(_dni);
}
int Cliente::getId() const{
    return _id;
}
bool Cliente::getEstado() const{
    return _estado;
}
