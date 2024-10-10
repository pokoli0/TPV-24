#pragma once
#include "Date.h"
#include "Coche.h"
#include <iostream>

using namespace std;
class Alquiler
{
private:
	int codigo;
	Date fecha;
	int dias;
	Coche** coche;
public:
	Alquiler();
	Alquiler(int codigo, Date fecha, int dias, Coche** coche);
	int getCodigo() const;
	int getDias() const;
	Date getFecha() const;
	void setCoche(Coche** nuevoCoche);
	Coche** getCoche() const;
	friend istream& operator>>(istream& in, Alquiler& alquiler);
	/*friend istream& sort(Alquiler* alquiler, Alquiler* totalAlquileres);*/
	
};

