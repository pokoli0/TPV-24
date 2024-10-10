#pragma once
#include <iostream>
#include <string>

using namespace std;
class Coche
{
private:
	int codigo;
	int precio;
	string nombre;
public:
	Coche();
	Coche(int codigo, int precio, string nombre);
	int getCodigo() const;
	int getPrecio() const;
	string getNombre()const;
	friend istream& operator>>(istream& in, Coche& coche);
	friend istream& getline(istream& in, Coche& coche);
};

