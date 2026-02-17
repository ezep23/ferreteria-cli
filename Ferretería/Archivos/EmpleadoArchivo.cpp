#include <iostream>
using namespace std;

#include "EmpleadoArchivo.h"

EmpleadoArchivo::EmpleadoArchivo(std::string nombreArchivo): _nombreArchivo(nombreArchivo){

}

bool EmpleadoArchivo::guardar(const Empleado &reg){
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "ab");

  if(pFile == nullptr){
    return false;
  }

  result = fwrite(&reg, sizeof(Empleado), 1, pFile);

  fclose(pFile);

  return result;
}

bool EmpleadoArchivo::guardar(int pos, const Empleado &registro){
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if(pFile == nullptr){
    return false;
  }

  fseek(pFile, sizeof(Empleado)*pos, SEEK_SET);

  result = fwrite(&registro, sizeof(Empleado), 1, pFile);

  fclose(pFile);

  return result;
}

int EmpleadoArchivo::buscarID(int id){
  Empleado reg;
  FILE *pFile;
  int pos = -1;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    return pos;
  }

  while(fread(&reg, sizeof(Empleado), 1, pFile)){
    if(reg.getId() == id){
      pos = ftell(pFile) / sizeof(Empleado) - 1;
      break;
    }
  }

  fclose(pFile);

  return pos;
}

Empleado EmpleadoArchivo::leer(int pos){
  Empleado reg;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    reg.setId(-1);
    return reg;
  }

  fseek(pFile, sizeof(Empleado)*pos, SEEK_SET);

  fread(&reg, sizeof(Empleado), 1, pFile);

  fclose(pFile);

  return reg;
}

int EmpleadoArchivo::leerTodos(Empleado regs[], int cantidad){
  int result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    return 0;
  }

  result = fread(regs, sizeof(Empleado), cantidad, pFile);

  fclose(pFile);

  return result;
}

int EmpleadoArchivo::getCantidadRegistros(){
  int cantidad;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    return 0;
  }

  fseek(pFile, 0, SEEK_END);
  cantidad = ftell(pFile) / sizeof(Empleado);

  fclose(pFile);

  return cantidad;
}

int EmpleadoArchivo::getNuevoID(){
    return getCantidadRegistros() + 1;
}

bool EmpleadoArchivo::eliminar(int pos){
  Empleado reg = leer(pos);
  if(reg.getId() == -1){
    return false;
  }

  reg.setEstado(false);

  return guardar(pos, reg);
}

void EmpleadoArchivo::crearBackup(){
    Empleado obj;
    FILE* p = fopen("./backups/Empleados.bkp", "wb");

    if (p == nullptr){
        cout << "NO SE PUEDE CREAR EL BACKUP DE EMPLEADOS";
        return;
    }

    int cantidad = getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        obj = leer(i);
        fwrite(&obj, sizeof obj, 1, p);
    }
    fclose(p);

    system("cls");
    cout << "BACKUP DE EMPLEADOS CREADO" << endl;
}

void EmpleadoArchivo::cargarBackup(){
    Empleado obj;

    FILE* p = fopen(_nombreArchivo.c_str(), "wb");

    if (p == nullptr){
        cout << "NO SE PUDO ABRIR O NO EXISTE EL ARCHIVO DE EMPLEADOS";
        return;
    }
    FILE* pBackup = fopen("./backups/Compras.bkp", "rb");

    if (pBackup == nullptr){
        cout << "NO SE PUDO ABRIR O NO EXISTE EL ARCHIVO DE BACKUP EMPLEADOS";
        return;
    }

    while (fread(&obj, sizeof obj, 1, pBackup) == 1) {
        fwrite(&obj, sizeof(Empleado), 1, p);
    }

    fclose(p);
    fclose(pBackup);
    cout << " # COPIA DE SEGURIDAD EMPLEADOS RESTAURADA CON EXITO" << endl;
}
