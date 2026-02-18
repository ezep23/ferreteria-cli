#include <iostream>
using namespace std;

#include "Hora.h"

Hora::Hora(){
 setHora(0);
 setMinutos(0);
}

Hora::Hora(int h, int m){
 setHora(h);
 setMinutos(m);
}

void Hora::setHora(int h){
    _hora = h;
}
void Hora::setMinutos(int m){
    _minutos = m;
}

int Hora::getHora(){
    return _hora;
}
int Hora::getMinutos(){
    return _minutos;
}

bool Hora::validarHora(int hora, int minutos){

    if (hora < 0 || hora > 23){

        cout << "HORA MAL INGRESADA" << endl;
        return false;
    }

    if (minutos < 0 || minutos > 59 ){
        cout << "MINUTOS MAL INGRESADOS" << endl;
        return false;
    }

    return true;
}

