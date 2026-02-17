#include <iostream>
#include <cctype>
#include <limits>
#include "utils.h"

std::string cargarCadena()
{
  std::string texto;

  if(std::cin.peek() == '\n')
  {
    std::cin.ignore();
  }

  std::getline(std::cin, texto);

  return texto;
}

bool validarDNI(std::string dni) {

    if (dni.length() > 8 || dni.length() == 0) {
        return false;
    }

    std::string numerosValidos = "0123456789";

    for (int i = 0; i < dni.length(); i++) {

        char caracterDni = dni[i];
        bool coincidencia = false;

        if (i == 0 && caracterDni == '0') {
            return false;
        }

        for (int j = 0; j < 10; j++) {
            if (caracterDni == numerosValidos[j]) {
                coincidencia = true;
                break;
            }
        }

        if (coincidencia == false) {
            return false;
        }
    }

    return true;
}

bool validarNumero(std::string cadena){
    if (cadena.empty()) return false;

    for (int i = 0; i < cadena.size(); i++) {
        if (!isdigit(cadena[i])) {
            return false;
        }
    }
    return true;
}


bool validarCadena(std::string cadena){
    if (cadena.empty()){
        return false;
    }

    for (int i = 0; i < cadena.size(); i++) {
        char c = cadena[i];
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    return true;
}

bool validarCadenaEspacios(std::string cadena){
    if (cadena.empty()){
        return false;
    }

    for (int i = 0; i < cadena.size(); i++) {
        char c = cadena[i];
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

int pedirEnteroValido(){
    int numero;

    while (true) {
        if (std::cin >> numero) {
            return numero;
        } else {
            // Si falla (porque ingresaron letras, por ejemplo):
            std::cout << "Error: Entrada invalida. Solo se aceptan numeros enteros." << std::endl;

            // 1. Limpiamos el estado de error de cin
            std::cin.clear();

            // 2. Descartamos lo que sea que haya escrito el usuario hasta el salto de linea
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Intentalo de nuevo: ";
        }
    }
}

float pedirFlotanteValido() {
    float numero;

    while (true) {
        if (std::cin >> numero) {
            return numero;
        } else {
            // Si falla (ingresaron letras o símbolos inválidos):
            std::cout << "Error: Entrada invalida. Solo se aceptan numeros (usa el punto '.' para decimales)." << std::endl;

            std::cin.clear(); // Limpiamos el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Barremos la basura del teclado

            std::cout << "Intentalo de nuevo: ";
        }
    }
}
