#include <iostream>
using namespace std;

#include "CompraArchivo.h"

CompraArchivo::CompraArchivo(std::string nombreArchivo)
  : _nombreArchivo(nombreArchivo)
{
  /// validar
}

bool CompraArchivo::guardar(const Transaccion &registro){
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "ab");

  if(pFile == nullptr){
    return false;
  }

  result = fwrite(&registro, sizeof(Transaccion), 1, pFile);

  fclose(pFile);

  return result;
}

bool CompraArchivo::guardar(int pos, const Transaccion &registro){
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if(pFile == nullptr){
    return false;
  }

  fseek(pFile, sizeof(Transaccion)*pos, SEEK_SET);

  result = fwrite(&registro, sizeof(Transaccion), 1, pFile);

  fclose(pFile);

  return result;
}

Transaccion CompraArchivo::leer(int pos){
  Transaccion registro;
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    registro.setIdTransaccion(-1);
    return registro;
  }

  fseek(pFile, sizeof(Transaccion)*pos, SEEK_SET);

  fread(&registro, sizeof(Transaccion), 1, pFile);

  fclose(pFile);

  return registro;
}



int CompraArchivo::leerTodos(Transaccion compras[], int cantidad){
  int result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr)
  {
    return 0;
  }

  result = fread(compras, sizeof(Transaccion), cantidad, pFile);

  fclose(pFile);

  return result;
}

int CompraArchivo::getCantidadRegistros()
{
  int cantidad;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr)
  {
    return 0;
  }

  fseek(pFile, 0, SEEK_END);
  cantidad = ftell(pFile) / sizeof(Transaccion);

  fclose(pFile);

  return cantidad;
}

int CompraArchivo::getNuevoID(){
  return getCantidadRegistros() + 1;
}


int CompraArchivo::buscarID(int id){
  Transaccion registro;
  FILE *pFile;
  int pos = -1;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr)
  {
    return pos;
  }

  while(fread(&registro, sizeof(Transaccion), 1, pFile)){
    if(registro.getIdTransaccion() == id){
      pos = ftell(pFile) / sizeof(Transaccion) - 1;
      break;
    }
  }

  fclose(pFile);

  return pos;
}

bool CompraArchivo::eliminar(int pos){
  Transaccion registro = leer(pos);
  if(registro.getIdTransaccion() == -1){
    return false;
  }

  registro.setEstado(false);

  return guardar(pos, registro);
}

void CompraArchivo::crearBackup(){
    Transaccion obj;
    FILE* p = fopen("./backups/Compras.bkp", "wb");

    if (p == nullptr){
        cout << "NO SE PUEDE CREAR EL BACKUP DE COMPRAS";
        return;
    }

    int cantidad = getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        obj = leer(i);
        fwrite(&obj, sizeof obj, 1, p);
    }
    fclose(p);

    system("cls");
    cout << "BACKUP COMPRAS CREADO" << endl;
}

void CompraArchivo::cargarBackup(){
    Transaccion obj;

    FILE* p = fopen(_nombreArchivo.c_str(), "wb");

    if (p == nullptr){
        cout << "NO SE PUDO ABRIR O NO EXISTE EL ARCHIVO DE COMPRAS";
        return;
    }
    FILE* pBackup = fopen("./backups/Compras.bkp", "rb");

    if (pBackup == nullptr){
        cout << "NO SE PUDO ABRIR O NO EXISTE EL ARCHIVO DE BACKUP COMPRAS";
        return;
    }

    while (fread(&obj, sizeof obj, 1, pBackup) == 1) {
        fwrite(&obj, sizeof(Transaccion), 1, p);
    }

    fclose(p);
    fclose(pBackup);
    cout << " # COPIA DE SEGURIDAD COMPRAS RESTAURADA CON EXITO" << endl;
}


