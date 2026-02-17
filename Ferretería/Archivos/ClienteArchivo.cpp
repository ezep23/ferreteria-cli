#include <iostream>
using namespace std;

#include "ClienteArchivo.h"

ClienteArchivo::ClienteArchivo(std::string nombreArchivo): _nombreArchivo(nombreArchivo){

}

bool ClienteArchivo::guardar(const Cliente &reg){
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "ab");

  if(pFile == nullptr){
    return false;
  }

  result = fwrite(&reg, sizeof(Cliente), 1, pFile);

  fclose(pFile);

  return result;
}

bool ClienteArchivo::guardar(int pos, const Cliente &registro){
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if(pFile == nullptr){
    return false;
  }

  fseek(pFile, sizeof(Cliente)*pos, SEEK_SET);

  result = fwrite(&registro, sizeof(Cliente), 1, pFile);

  fclose(pFile);

  return result;
}

int ClienteArchivo::buscarID(int id){
  Cliente reg;
  FILE *pFile;
  int pos = -1;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    return pos;
  }

  while(fread(&reg, sizeof(Cliente), 1, pFile)){
    if(reg.getId() == id){
      pos = ftell(pFile) / sizeof(Cliente) - 1;
      break;
    }
  }

  fclose(pFile);

  return pos;
}

Cliente ClienteArchivo::leer(int pos){
  Cliente reg;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    reg.setId(-1);
    return reg;
  }

  fseek(pFile, sizeof(Cliente)*pos, SEEK_SET);

  fread(&reg, sizeof(Cliente), 1, pFile);

  fclose(pFile);

  return reg;
}

int ClienteArchivo::leerTodos(Cliente regs[], int cantidad){
  int result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    return 0;
  }

  result = fread(regs, sizeof(Cliente), cantidad, pFile);

  fclose(pFile);

  return result;
}

int ClienteArchivo::getCantidadRegistros(){
  int cantidad;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    return 0;
  }

  fseek(pFile, 0, SEEK_END);
  cantidad = ftell(pFile) / sizeof(Cliente);

  fclose(pFile);

  return cantidad;
}

int ClienteArchivo::getNuevoID(){
    return getCantidadRegistros() + 1;
}

bool ClienteArchivo::eliminar(int pos){
  Cliente reg = leer(pos);
  if(reg.getId() == -1){
    return false;
  }

  reg.setEstado(false);

  return guardar(pos, reg);
}

void ClienteArchivo::crearBackup(){
    Cliente obj;
    FILE* p = fopen("./backups/Clientes.bkp", "wb");

    if (p == nullptr){
        cout << "NO SE PUEDE CREAR EL BACKUP DE CLIENTES";
        return;
    }

    int cantidad = getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        obj = leer(i);
        fwrite(&obj, sizeof obj, 1, p);
    }
    fclose(p);

    system("cls");
    cout << "BACKUP CLIENTES CREADO" << endl;
}

void ClienteArchivo::cargarBackup(){
    Cliente obj;

    FILE* p = fopen(_nombreArchivo.c_str(), "wb");

    if (p == nullptr){
        cout << "NO SE PUDO ABRIR O NO EXISTE EL ARCHIVO DE CLIENTES";
        return;
    }
    FILE* pBackup = fopen("./backups/Clientes.bkp", "rb");

    if (pBackup == nullptr){
        cout << "NO SE PUDO ABRIR O NO EXISTE EL ARCHIVO DE BACKUP CLIENTES";
        return;
    }

    while (fread(&obj, sizeof obj, 1, pBackup) == 1) {
        fwrite(&obj, sizeof(Cliente), 1, p);
    }

    fclose(p);
    fclose(pBackup);
    cout << " # COPIA DE SEGURIDAD CLIENTES RESTAURADA CON EXITO" << endl;
}
