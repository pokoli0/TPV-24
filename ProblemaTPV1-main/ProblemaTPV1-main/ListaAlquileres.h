#pragma once
#include "Alquiler.h"
#include "ListaCoches.h"

using namespace std;
class ListaAlquileres
{
private:
	Alquiler* alquiler;
	int cont;
	int tam = cont + 10;
public:
	ListaAlquileres();
	ListaAlquileres(Alquiler* alquiler, int cont, int tam);
	Alquiler* getAlquiler() const;
	bool leerAlquileres(const ListaCoches& listaCoches);
	void ordenarAlquileres(int totalAlquileres);
	void mostrarAlquileres(const ListaCoches& listaCoches);
	void agregarAlquiler();
	void agregarAlquiler2(const Alquiler& nuevoAlquiler);
};

