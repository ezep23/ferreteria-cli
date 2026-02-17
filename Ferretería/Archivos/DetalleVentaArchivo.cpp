#include <iostream>
using namespace std;

#include "DetalleVentaArchivo.h"

DetalleVentaArchivo::DetalleVentaArchivo(std::string nombreArchivo)
  : _nombreArchivo(nombreArchivo)
{
  /// validar
}

bool DetalleVentaArchivo::guardar(const DetalleTransaccion &registro){
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "ab");

  if(pFile == nullptr){
    return false;
  }

  result = fwrite(&registro, sizeof(DetalleTransaccion), 1, pFile);

  fclose(pFile);

  return result;
}

bool DetalleVentaArchivo::guardar(int pos, const DetalleTransaccion &registro){
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if(pFile == nullptr){
    return false;
  }

  fseek(pFile, sizeof(DetalleTransaccion)*pos, SEEK_SET);

  result = fwrite(&registro, sizeof(DetalleTransaccion), 1, pFile);

  fclose(pFile);

  return result;
}

DetalleTransaccion DetalleVentaArchivo::leer(int pos){
  DetalleTransaccion registro;
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr){
    registro.setId(-1);
    return registro;
  }

  fseek(pFile, sizeof(DetalleTransaccion)*pos, SEEK_SET);

  fread(&registro, sizeof(DetalleTransaccion), 1, pFile);

  fclose(pFile);

  return registro;
}



int DetalleVentaArchivo::leerTodos(DetalleTransaccion ventas[], int cantidad){
  int result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr)
  {
    return 0;
  }

  result = fread(ventas, sizeof(DetalleTransaccion), cantidad, pFile);

  fclose(pFile);

  return result;
}

int DetalleVentaArchivo::getCantidadRegistros()
{
  int cantidad;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr)
  {
    return 0;
  }

  fseek(pFile, 0, SEEK_END);
  cantidad = ftell(pFile) / sizeof(DetalleTransaccion);

  fclose(pFile);

  return cantidad;
}

int DetalleVentaArchivo::getNuevoID(){
  return getCantidadRegistros() + 1;
}


int DetalleVentaArchivo::buscarID(int id){
  DetalleTransaccion registro;
  FILE *pFile;
  int pos = -1;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if(pFile == nullptr)
  {
    return pos;
  }

  while(fread(&registro, sizeof(DetalleTransaccion), 1, pFile)){
    if(registro.getId() == id){
      pos = ftell(pFile) / sizeof(DetalleTransaccion) - 1;
      break;
    }
  }

  fclose(pFile);

  return pos;
}

bool DetalleVentaArchivo::eliminar(int pos){
  DetalleTransaccion registro = leer(pos);
  if(registro.getId() == -1){
    return false;
  }

  registro.setEstado(false);

  return guardar(pos, registro);
}

void DetalleVentaArchivo::crearBackup(){
    DetalleTransaccion obj;
    FILE* p = fopen("./backups/DetallesVentas.bkp", "wb");

    if (p == nullptr){
        cout << "NO SE PUEDE CREAR EL BACKUP DE DETALLES DE VENTAS";
        return;
    }

    int cantidad = getCantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        obj = leer(i);
        fwrite(&obj, sizeof obj, 1, p);
    }
    fclose(p);

    system("cls");
    cout << "BACKUP DETALLES DE VENTAS CREADO" << endl;
}

void DetalleVentaArchivo::cargarBackup(){
    DetalleTransaccion obj;

    FILE* p = fopen(_nombreArchivo.c_str(), "wb");

    if (p == nullptr){
        cout << "NO SE PUDO ABRIR O NO EXISTE EL ARCHIVO DE DETALLES DE VENTAS";
        return;
    }
    FILE* pBackup = fopen("./backups/DetallesVentas.bkp", "rb");

    if (pBackup == nullptr){
        cout << "NO SE PUDO ABRIR O NO EXISTE EL ARCHIVO DE BACKUP DE DETALLES DE VENTAS";
        return;
    }

    while (fread(&obj, sizeof obj, 1, pBackup) == 1) {
        fwrite(&obj, sizeof(DetalleTransaccion), 1, p);
    }

    fclose(p);
    fclose(pBackup);
    cout << " # COPIA DE SEGURIDAD DE DETALLES DE VENTAS RESTAURADA CON EXITO" << endl;
}
