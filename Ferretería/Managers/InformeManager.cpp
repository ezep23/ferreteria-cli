#include <iostream>
using namespace std;

#include "InformeManager.h"

InformeManager::InformeManager(){

}

void InformeManager::recaudacionMensual(){
    int anio;

    cout << "Ingrese el anio: ";
    cin >> anio;

    _ventaManager.recaudacionMensual(anio);
}

void InformeManager::recaudacionMensualCategoria(){
    int anio, idCat;

    cout << "Ingrese el anio: ";
    cin >> anio;

    do{
        cout << "Ingrese la categoria (0 - Para mostrar categorias)" << endl;
        cout << "Opcion: ";
        cin >> idCat;

        if(idCat == 0){
            _categoriaManager.mostrar();
        }


    }while(idCat <= 0 && !_categoriaManager.existeCategoria(idCat));

    _ventaManager.recaudacionMensualCategoria(anio, idCat);
}

void InformeManager::recaudacionAnual(){

    _ventaManager.recaudacionAnual();
}

void InformeManager::recaudacionAnualCategoria(){
    int anio, idCat;

    cout << "Ingrese el anio: ";
    cin >> anio;

    do{
        cout << "Ingrese la categoria (0 - Para mostrar categorias)" << endl;
        cout << "Opcion: ";
        cin >> idCat;

        if(idCat == 0){
            _categoriaManager.mostrar();
        }


    }while(idCat <= 0 && !_categoriaManager.existeCategoria(idCat));

    _ventaManager.numeroVentasMensualCategoria(anio, idCat);
}

void InformeManager::numeroVentasAnualCategoria(){
    int idCat;

    do{
        cout << "Ingrese la categoria (0 - Para mostrar categorias)" << endl;
        cout << "Opcion: ";
        cin >> idCat;

        if(idCat == 0){
            _categoriaManager.mostrar();
        }


    }while(idCat <= 0 && !_categoriaManager.existeCategoria(idCat));

    _ventaManager.numeroVentasAnualCategoria(idCat);
}

void InformeManager::numeroVentasMensualCategoria(){
    int anio, idCat;

    cout << "Ingrese el anio: ";
    cin >> anio;

    do{
        cout << "Ingrese la categoria (0 - Para mostrar categorias)" << endl;
        cout << "Opcion: ";
        cin >> idCat;

        if(idCat == 0){
            _categoriaManager.mostrar();
        }


    }while(idCat <= 0 && !_categoriaManager.existeCategoria(idCat));

    _ventaManager.numeroVentasMensualCategoria(anio, idCat);
}

void InformeManager::numeroProductosVendidosCategoria(){
    int idCat;

    do{
        cout << "Ingrese la categoria (0 - Para mostrar categorias)" << endl;
        cout << "Opcion: ";
        cin >> idCat;

        if(idCat == 0){
            _categoriaManager.mostrar();
        }


    }while(idCat <= 0 && !_categoriaManager.existeCategoria(idCat));

    _ventaManager.obtenerNumeroProductosVendidosCategoria(idCat);
}

void InformeManager::numeroProductosProveeedor(){
    _almacenManager.numeroProductosProveedor();
}

void InformeManager::ventasPorEmpleado(){
    _ventaManager.ventasPorEmpleado();
}

void InformeManager::comprasPorEmpleado(){
    _compraManager.comprasPorEmpleado();
}

void InformeManager::listarBajoStock(){
    _almacenManager.listarBajoStock();
}
