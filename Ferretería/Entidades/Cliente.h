#pragma once
#include <string>

class Cliente {
 private:
    int _id;
    char _nombre[20];
    char _apellido[20];
    char _dni[8];
    bool _estado;
 public:

    Cliente();
    Cliente(int id, std::string nom, std::string apellido, std::string dni);

    void setNombre(std::string nombre);
    void setApellido(std::string apellido);
    void setDni(std::string dni);
    void setId(int);
    void setEstado(bool);

    std::string getNombre() const;
    std::string getApellido() const;
    std::string getDni() const;
    int getId() const;
    bool getEstado() const;

};
