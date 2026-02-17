#include "Persona.h"
#include <cstring>
using namespace std;

Persona::Persona(){
    setNombre("");
    setApellido("");
    setEmail("");
    setTelefono("");
    setDni("");
}

Persona::Persona(string nombre, string apellido, string telefono, string email, string dni){
    setNombre(nombre);
    setApellido(apellido);
    setTelefono(telefono);
    setEmail(email);
    setDni(dni);
}

void Persona::setNombre(string nombre){
    strncpy(_nombre, nombre.c_str(), 19);
}

void Persona::setApellido(string apellido){
    strncpy(_apellido, apellido.c_str(), 19);
}
void Persona::setTelefono(string telefono){
    strncpy(_telefono, telefono.c_str(), 17);
}
void Persona::setEmail(string email){
    strncpy(_email, email.c_str(), 34);
}
void Persona::setDni(string dni){
    strncpy(_dni, dni.c_str(), 7);
}


string Persona::getNombre() const{
    return string(_nombre);
}
string Persona::getApellido() const{
    return string(_apellido);
}
string Persona::getTelefono() const{
    return string(_telefono);
}
string Persona::getEmail() const{
    return string(_email);
}
string Persona::getDni() const{
    return string(_dni);
}
