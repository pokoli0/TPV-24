#pragma once
#include "Date.h"
#include <string>
#include <Windows.h>

using namespace std;

class Ejemplar
{
public:
	enum Tipo {
		libro, audiovisual, juego,
	};
	Ejemplar(int cod, Tipo tipo, string nom);

	int getCodigo() const {
		return codigo;
	}

	 char getTipo() const {
		return tipo;
	}

	string getNombre() const {
		return nombre;
	};

	void const presta() { disponible = false; };
	void devuelve() { disponible = true; };

	friend ostream& operator<<(ostream& f, const Ejemplar& c);
	friend istream& operator>>(istream& f, Ejemplar& e);

private:

	int codigo;
	char tipo;
	string nombre;
	bool disponible;

};

