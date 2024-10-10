
#include "Alquiler.h"
#include "Coche.h"
#include <iostream>
#include <fstream>
#include <string>
Alquiler::Alquiler() :codigo(), fecha(), dias(), coche() {};
Alquiler::Alquiler(int codigo, Date fecha, int dias, Coche** coche): codigo(codigo), fecha(fecha), dias(dias), coche(coche) {}

int Alquiler::getCodigo()const {
	return codigo;
}
int Alquiler::getDias() const {
	return dias;
}
Date Alquiler::getFecha()const {
	return fecha;
}
void Alquiler::setCoche(Coche** nuevoCoche) {
	coche = nuevoCoche;
}
Coche** Alquiler::getCoche() const {
	return coche;
}
istream& operator>>(istream& in, Alquiler& alquiler	) {
	return in >> alquiler.codigo >> alquiler.fecha >> alquiler.dias;
}
//istream& sort(Alquiler* alquiler, Alquiler* totalAlquileres) { 
//	return sort(alquiler, totalAlquileres);
//}

