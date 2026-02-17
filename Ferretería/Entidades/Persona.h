#pragma once
#include <string>

class Persona{
protected:
   char _nombre[20];
   char _apellido[20];
   char _telefono[18];
   char _email[35];
   char _dni[8];
public:

    Persona();
    Persona(std::string nombre, std::string apellido, std::string telefono, std::string email, std::string dni);

    void setNombre(std::string nombre);
    void setApellido(std::string apellido);
    void setTelefono(std::string telefono);
    void setEmail(std::string email);
    void setDni(std::string dni);

    std::string getNombre() const;
    std::string getApellido() const;
    std::string getTelefono() const;
    std::string getEmail() const;
    std::string getDni() const;
};
