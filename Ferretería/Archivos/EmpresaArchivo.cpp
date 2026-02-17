#include <iostream>
using namespace std;

#include "EmpresaArchivo.h"

EmpresaArchivo::EmpresaArchivo(std::string nombreArchivo): _nombreArchivo(nombreArchivo){

}

bool EmpresaArchivo::guardar(const Empresa &reg){
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "ab");

  if(pFile == nullptr){
    return false;
  }

  result = fwrite(&reg, sizeof(Empresa), 1, pFile);

  fclose(pFile);

  return result;
}

bool EmpresaArchivo::guardar(int pos, const Empresa &registro){
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if(pFile == nullptr){
    return false;
  }

  fseek(pFile, sizeof(Empresa)*pos, SEEK_SET);

  result = fwrite(&registro, sizeof(Empresa), 1, pFile);

  fclose(pFile);

  return result;
}

int EmpresaArchivo::buscarID(int id){
  Empresa reg;
  FILE *pFile;
  int pos = -1;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    return pos;
  }

  while(fread(&reg, sizeof(Empresa), 1, pFile)){
    if(reg.getId() == id){
      pos = ftell(pFile) / sizeof(Empresa) - 1;
      break;
    }
  }

  fclose(pFile);

  return pos;
}

Empresa EmpresaArchivo::leer(int pos){
  Empresa reg;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    reg.setId(-1);
    return reg;
  }

  fseek(pFile, sizeof(Empresa)*pos, SEEK_SET);

  fread(&reg, sizeof(Empresa), 1, pFile);

  fclose(pFile);

  return reg;
}

int EmpresaArchivo::leerTodos(Empresa regs[], int cantidad){
  int result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    return 0;
  }

  result = fread(regs, sizeof(Empresa), cantidad, pFile);

  fclose(pFile);

  return result;
}

int EmpresaArchivo::getCantidadRegistros(){
  int cantidad;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    return 0;
  }

  fseek(pFile, 0, SEEK_END);
  cantidad = ftell(pFile) / sizeof(Empresa);

  fclose(pFile);

  return cantidad;
}

int EmpresaArchivo::getNuevoID(){
    return getCantidadRegistros() + 1;
}

bool EmpresaArchivo::eliminar(int pos){
  Empresa reg = leer(pos);
  if(reg.getId() == -1){
    return false;
  }

  reg.setEstado(false);

  return guardar(pos, reg);
}

void EmpresaArchivo::crearBackup(){
    Empresa obj;
    FILE* p = fopen("./backups/Empresas.bkp", "wb");

    if (p == nullptr){
        cout << "NO SE PUEDE CREAR EL BACKUP DE EMPRESAS";
        return;
    }

    int cantidad = getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        obj = leer(i);
        fwrite(&obj, sizeof obj, 1, p);
    }
    fclose(p);

    system("cls");
    cout << "BACKUP DE EMPRESAS CREADO" << endl;
}

void EmpresaArchivo::cargarBackup(){
    Empresa obj;

    FILE* p = fopen(_nombreArchivo.c_str(), "wb");

    if (p == nullptr){
        cout << "NO SE PUDO ABRIR O NO EXISTE EL ARCHIVO DE EMPRESAS";
        return;
    }
    FILE* pBackup = fopen("./backups/Empresas.bkp", "rb");

    if (pBackup == nullptr){
        cout << "NO SE PUDO ABRIR O NO EXISTE EL ARCHIVO DE BACKUP EMPRESAS";
        return;
    }

    while (fread(&obj, sizeof obj, 1, pBackup) == 1) {
        fwrite(&obj, sizeof(Empresa), 1, p);
    }

    fclose(p);
    fclose(pBackup);
    cout << " # COPIA DE SEGURIDAD EMPRESAS RESTAURADA CON EXITO" << endl;
}
