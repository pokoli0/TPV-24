#include "Coche.h"
#include <iostream>
#include <fstream>
#include <string>

Coche::Coche(): codigo(), precio(), nombre() {}
Coche::Coche(int codigo, int precio, string nombre) : codigo(codigo), precio(precio), nombre(nombre) {}
int Coche::getCodigo() const {
	return codigo;
}
int Coche::getPrecio() const {
	return precio;
}
string Coche::getNombre()const {
	return nombre;
}
istream& operator>>(istream& in, Coche& coche) {
	
	return in >> coche.codigo >> coche.precio;
}
istream& getline(istream& in, Coche& coche) {
	
	 getline(in, coche.nombre);
	 return in;
}