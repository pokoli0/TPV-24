// Jaime Vicente Arroyo
// Javier Tirado Ríos
// G22

#include <iostream>
#include <fstream>
#include "Date.h"
#include <string>
#include <Windows.h>
#include <algorithm>
#include "ListaCoches.h"

using namespace std;

//struct Coche
//{
//	int matricula;
//	int precio;
//	string nombre;
//};


//Coche* ListaCoches;
//
//int numCoches;

//struct Alquiler 
//{
//	int matricula;
//	Date fecha;
//	int dias;
//	Coche* coche;
//};
//
//Alquiler* ListaAlquileres;
//
//int numAlquileres;

//bool leerModelos() 
//{
//	ifstream entrada("coches.txt");
//
//	if (entrada.is_open()) 
//	{
//		entrada >> numCoches;
//
//		ListaCoches = new Coche[numCoches + 10];
//
//		for (int i = 0; i < numCoches; i++)
//		{
//			entrada >> ListaCoches[i].matricula >> ListaCoches[i].precio; 
//			getline(entrada, ListaCoches[i].nombre);
//		}
//	}
//
//	return entrada.is_open();
//}

//int buscarCoche(Coche listaCoches[], const int codigo)
//{
//	int i = 0;
//
//	while (i < numCoches && codigo != listaCoches[i].matricula)
//	{
//		i++;
//	}
//
//	if (i == numCoches)
//	{
//		i = -1;
//	}
//
//	return i;
//}
//
//bool leerAlquileres() 
//{
//	ifstream entrada("rent.txt"); 
//	
//	if (entrada.is_open())
//	{
//		entrada >> numAlquileres;
//
//		ListaAlquileres = new Alquiler[numAlquileres + 10];
//
//		for (int i = 0; i < numAlquileres; i++)
//		{
//			entrada >> ListaAlquileres[i].matricula >> ListaAlquileres[i].fecha >> ListaAlquileres[i].dias;
//
//			if (buscarCoche(ListaCoches, ListaAlquileres[i].matricula) != -1)
//			{
//				ListaAlquileres[i].coche = &ListaCoches[buscarCoche(ListaCoches, ListaAlquileres[i].matricula)];
//			}
//			else 
//			{
//				ListaAlquileres[i].coche = nullptr;
//			}
//		}
//	} 
//
//	return entrada.is_open();
//}
//
//bool operator<(const Alquiler& izdo, const Alquiler& dcho) {
//	
//	return izdo.fecha < dcho.fecha;
//}
//
//void ordenarAlquileres(Alquiler* listaInicio, Alquiler* listaFin)
//{
//	sort(listaInicio, listaFin);
//}
//
//
//void mostrarAlquileres(Alquiler listaAlquileres[])
//{
//	for (int i = 0; i < numAlquileres; i++) 
//	{
//		if (listaAlquileres[i].coche == nullptr) {
//			cout << listaAlquileres[i].fecha << " ERROR: Modelo inexistente" << endl;
//		}
//		else {
//			cout << listaAlquileres[i].fecha << listaAlquileres[i].coche->nombre << " "
//				<< listaAlquileres[i].dias << " día(s) " << "por "
//				<< listaAlquileres[i].coche->precio * listaAlquileres[i].dias << endl;
//		}
//	}
//}

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	/*leerModelos();
	leerAlquileres();
	ordenarAlquileres(ListaAlquileres, ListaAlquileres + numAlquileres);
	mostrarAlquileres(ListaAlquileres);

	delete[] ListaCoches;
	ListaCoches = nullptr;

	delete[] ListaAlquileres;
	ListaAlquileres = nullptr;*/

	ListaCoches lC;
	lC.leerModelos();
}
