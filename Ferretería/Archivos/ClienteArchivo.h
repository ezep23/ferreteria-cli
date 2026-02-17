#pragma once
#include <string>
#include "../Entidades/Cliente.h"

class ClienteArchivo{
  public:
    ClienteArchivo(std::string nombreArchivo = "Clientes.dat");
    bool guardar(const Cliente &reg);
    bool guardar(int pos, const Cliente &reg);

    int buscarID(int id);
    Cliente leer(int pos);

    bool eliminar(int pos);

    int leerTodos(Cliente regs[], int cantidad);
    int getCantidadRegistros();
    int getNuevoID();

    void crearBackup();
    void cargarBackup();
  private:
    std::string _nombreArchivo;
};
