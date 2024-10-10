#pragma once
#include "Coche.h"
#include <iostream>
#include <fstream>

using namespace std;
class ListaCoches
{
private:
	int tam = cont + 10;
	Coche** coche;
	int cont;
public:
	ListaCoches();
	ListaCoches(int tam, Coche** coche, int cont);
	bool leerModelos();
	int buscarCoche(int codigo) const;
	Coche** getCoche() const;
	int getCont() const;
	void mostrarCoches();
	void agregarCoche2();
	void agregarCoche(const Coche& nuevoCoche);
	void ordenarCoches(int totalCoches)const;
	~ListaCoches();
};

