#include "ListaCoches.h"
#include "Coche.h"
#include <iostream>
#include <fstream>
#include <algorithm>
ListaCoches::ListaCoches() : tam(), coche(), cont() {}
ListaCoches::ListaCoches(int tam, Coche** coche, int cont) : tam(tam), coche(coche), cont(cont) {}

//int ListaCoches::getTam() const{
//	return tam;
//}
ListaCoches::~ListaCoches() {
	for (int i = 0; i < cont;i++) {
		delete coche[i];
	}
	delete[]coche;
}
int ListaCoches::getCont()const {
	return cont;
}
Coche** ListaCoches::getCoche() const {
	return coche;
}
bool ListaCoches::leerModelos()
{
	ifstream entrada;
	entrada.open("coches.txt");
	if (!entrada.is_open()) {
		return false;
	}
	else
	{
		entrada >> tam;
		tam += 10;
		coche = new Coche*[tam];
		for (int i = 0; !entrada.eof() && i < tam; i++)
		{
			coche[i] = new Coche;
			entrada >> *coche[i];
			getline(entrada, *coche[i]);
			cont++;
		}

		return true;
	}
	
}
int ListaCoches::buscarCoche(int codigo) const {
	int left = 0;
	int right = cont -1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (coche[mid]->getCodigo() == codigo)
			return mid;
		else if (coche[mid]->getCodigo() < codigo)
			left = mid + 1;
		else right = mid - 1;
	}
	return -1;
	
}
bool comparar(const Coche* izdo, const Coche* dcho) {
	// Definición del orden
	return izdo->getCodigo() < dcho->getCodigo();
}
void ListaCoches::ordenarCoches(int totalCoches) const{
	sort(coche, coche + totalCoches,comparar);
}

void ListaCoches::mostrarCoches() {
	if (cont == 0) {
		cout << "No hay coches disponibles en la lista." << endl;
	}

	cout << "Lista de Coches:" << endl;
	for (int i = 0; i < cont; i++) {
		cout << "Codigo: " << coche[i]->getCodigo() << endl;
		cout << "Nombre: " << coche[i]->getNombre() << endl;
		cout << "Precio: " << coche[i]->getPrecio() << endl;
		//esto es para espaciar los coches entre si 
		cout << "-------------------------" << endl;
	}


}
void ListaCoches::agregarCoche2(){
	Coche* nuevoCoche = new Coche;
	
	cout << "Ingrese datos del coche: ";
	cin >> *nuevoCoche;
	getline(cin, *nuevoCoche);
	agregarCoche(*nuevoCoche);
	ordenarCoches(cont);
	delete[]coche;
}
void ListaCoches::agregarCoche(const Coche& nuevoCoche) {
	if (cont < tam) {
		coche[cont] = new Coche;
		*coche[cont] = nuevoCoche;
		cont++;
		cout << "Coche agregado exitosamente." << endl;
	}
	else {
		cout << "La lista de coches esta llena. No se puede agregar mas coches." << endl;
	}

}




