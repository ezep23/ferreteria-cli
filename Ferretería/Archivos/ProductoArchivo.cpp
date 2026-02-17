#include <iostream>
using namespace std;

#include "ProductoArchivo.h"

ProductoArchivo::ProductoArchivo(std::string nombreArchivo): _nombreArchivo(nombreArchivo){

}

bool ProductoArchivo::guardar(const Producto &reg){
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "ab");

  if(pFile == nullptr){
    return false;
  }

  result = fwrite(&reg, sizeof(Producto), 1, pFile);

  fclose(pFile);

  return result;
}

bool ProductoArchivo::guardar(int pos, const Producto &registro){
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if(pFile == nullptr){
    return false;
  }

  fseek(pFile, sizeof(Producto)*pos, SEEK_SET);

  result = fwrite(&registro, sizeof(Producto), 1, pFile);

  fclose(pFile);

  return result;
}

int ProductoArchivo::buscarID(int id){
  Producto reg;
  FILE *pFile;
  int pos = -1;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    return pos;
  }

  while(fread(&reg, sizeof(Producto), 1, pFile)){
    if(reg.getId() == id){
      pos = ftell(pFile) / sizeof(Producto) - 1;
      break;
    }
  }

  fclose(pFile);

  return pos;
}

Producto ProductoArchivo::leer(int pos){
  Producto reg;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    reg.setId(-1);
    return reg;
  }

  fseek(pFile, sizeof(Producto)*pos, SEEK_SET);

  fread(&reg, sizeof(Producto), 1, pFile);

  fclose(pFile);

  return reg;
}

int ProductoArchivo::leerTodos(Producto regs[], int cantidad){
  int result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    return 0;
  }

  result = fread(regs, sizeof(Producto), cantidad, pFile);

  fclose(pFile);

  return result;
}

int ProductoArchivo::getCantidadRegistros(){
  int cantidad;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    return 0;
  }

  fseek(pFile, 0, SEEK_END);
  cantidad = ftell(pFile) / sizeof(Producto);

  fclose(pFile);

  return cantidad;
}

int ProductoArchivo::getNuevoID(){
    return getCantidadRegistros() + 1;
}

bool ProductoArchivo::eliminar(int pos){
  Producto reg = leer(pos);
  if(reg.getId() == -1){
    return false;
  }

  reg.setEstado(false);

  return guardar(pos, reg);
}

void ProductoArchivo::crearBackup(){
    Producto obj;
    FILE* p = fopen("./backups/Productos.bkp", "wb");

    if (p == nullptr){
        cout << "NO SE PUEDE CREAR EL BACKUP DE PRODUCTOS";
        return;
    }

    int cantidad = getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        obj = leer(i);
        fwrite(&obj, sizeof obj, 1, p);
    }
    fclose(p);

    system("cls");
    cout << "BACKUP DE PRODUCTOS CREADO" << endl;
}

void ProductoArchivo::cargarBackup(){
    Producto obj;

    FILE* p = fopen(_nombreArchivo.c_str(), "wb");

    if (p == nullptr){
        cout << "NO SE PUDO ABRIR O NO EXISTE EL ARCHIVO DE PRODUCTOS";
        return;
    }
    FILE* pBackup = fopen("./backups/Productos.bkp", "rb");

    if (pBackup == nullptr){
        cout << "NO SE PUDO ABRIR O NO EXISTE EL ARCHIVO DE BACKUP PRODUCTOS";
        return;
    }

    while (fread(&obj, sizeof obj, 1, pBackup) == 1) {
        fwrite(&obj, sizeof(Producto), 1, p);
    }

    fclose(p);
    fclose(pBackup);
    cout << " # COPIA DE SEGURIDAD PRODUCTOS RESTAURADA CON EXITO" << endl;
}


