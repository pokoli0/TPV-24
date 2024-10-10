#pragma once
#include "Date.hpp"
#include <string>
#include <Windows.h>

using namespace std;

class Ejemplar
{
public:
	enum Tipo {
		libro, audiovisual, juego,
	};
	Ejemplar() {};
	Ejemplar(int cod, Tipo tipo, string nom);

	int getCodigo() const {
		return codigo;
	}

	string mostrarTipo() const {
		if (tipo == libro)
		{
			return "Libro";
		}
		else if (tipo == juego)
		{
			return "Juego";
		}
		else if (tipo == audiovisual) {
			return "Audiovisual";
		}
	}

	string getNombre() const {
		return nombre;
	};
	void setCodigo(int cod)  {
		codigo = cod;
	}
	
	void setTipo(char tip)  {
		if (tip == 'L')
		{
			tipo = libro;
		}
		else if (tip == 'J')
		{
			tipo = juego;
		}
		else {
			tipo = audiovisual;
		}
	}

	void setNombre(string nom)  {
		nombre = nom;
	};

	void const presta() { disponible = false; };
	void devuelve() { disponible = true; };

	friend ostream& operator<<(ostream& f, const Ejemplar& c);
	friend istream& operator>>(istream& f, Ejemplar& e);

private:

	int codigo;
	Tipo tipo;
	string nombre;
	bool disponible;

};

