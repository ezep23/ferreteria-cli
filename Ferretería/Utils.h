#pragma once
#include <string>

std::string cargarCadena();

bool validarDNI(std::string dni);
bool validarCadena(std::string cadena);
bool validarCadenaEspacios(std::string cadena);
bool validarTelefonoString(std::string cadena);
bool validarEmailString(std::string cadena);
bool validarNumero(std::string cadena);
int pedirEnteroValido();
float pedirFlotanteValido();
