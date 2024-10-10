#pragma once

#include <iostream>
#include <fstream>
#include "Date.h"
#include <string>
#include <Windows.h>
#include <algorithm>
#include "Coche.h"

using namespace std;

class Alquiler
{
	private:
		Date fecha;
		int dias;
		Coche* coche;

	public:
		Alquiler(Coche* c, Date f, int d) : coche(c), fecha(f), dias(d) {}

		Coche* getCoche() {
			return coche;
		}

		Date getFecha() {
			return fecha;
		}

		int getDias() const {
			return dias;
		}

		int getCoste() {
			return (dias * coche->getPrecio());
		}

		// Sobrecarga del operador '<' para comparar alquileres por fecha.
		bool operator<(const Alquiler& otro) const {
			return fecha < otro.fecha;
		}

		// Método para leer un alquiler desde un flujo de entrada.
		void leeAlquiler(const ListaCoches&) {
			input >> coche >> dias ;
		}

		// Función amiga para imprimir un alquiler en un flujo de salida.
		friend ostream& operator<<(ostream& output, const Alquiler& a) {
			output << "Fecha: " << a.fecha << ", Días: " << a.dias << ", Coste: " << a.getCoste();
			return output;
		}
};

