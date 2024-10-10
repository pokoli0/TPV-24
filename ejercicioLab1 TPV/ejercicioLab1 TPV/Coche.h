#pragma once

#include <iostream>
#include <fstream>
#include "Date.h"
#include <string>
#include <Windows.h>
#include <algorithm>

using namespace std;

class Coche
{
	private: 
		int codigo;
		int precio;
		string modelo;

	public:
		Coche(int c, int p, string s) : codigo(c), precio(p), modelo(s) {}

		int getCodigo() {
			return codigo;
		}

		int getPrecio() {
			return precio;
		}

		string getModelo() const {
			return modelo;
		}

		friend ostream& operator<<(ostream& f, const Coche& c)
		{
			f << "Código: " << c.codigo << ", Precio: " << c.precio << ", Modelo: " << c.modelo;
			return f;
		}

		friend istream& operator>>(istream& f, Coche& c)
		{
			cout << "Introduce el código del coche: ";
			f >> c.codigo;
			cout << "Introduce el precio del coche: ";
			f >> c.precio;
			cout << "Introduce el modelo del coche: ";
			f >> c.modelo;
			return f;
		}
};

