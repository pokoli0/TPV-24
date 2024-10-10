#include "ListaPrestamos.h"

ListaPrestamos::ListaPrestamos(istream&, const Catalogo&)
{
}

ListaPrestamos::~ListaPrestamos()
{
}

bool ListaPrestamos::leerPrestamos(string fichero, Catalogo& catalogo)
{
	bool encontrado;
	ifstream input;
	input.open(fichero);

	if (!input.is_open())
	{
		encontrado = false;
		cout << "no se encuentra el fichero :(" << endl;
	}
	else {
		encontrado = true;

		int n, codigo, user;
		Date fecha;

		input >> n;
		elems = new Prestamo[n];
		capacidad = n;

		for (int i = 0; !input.eof() && i < n; i++)
		{
			input >> codigo;
			input >> fecha;
			input >> user;

			elems[i].setEjemplar(catalogo.buscaEjemplar(codigo, 0, numElems));
			elems[i].setFecha(fecha);
			elems[i].setUsuario(user);
		}
	}

	input.close();

	return encontrado;
}

void ListaPrestamos::mostrarPrestamos()
{
	// fecha de devolución, título, días hasta la entrega y penalización por retraso
	// 14/08/24 (en -41 días) Atraco en alta fidelidad (82 días de penalización)
	cout << "diaPrestamo";

	Date diaPrestamo;


	for (int i = 0; i < capacidad; i++) {
		diaPrestamo = elems[i].getFecha();
		cout << diaPrestamo;

	}

}

void ListaPrestamos::ordena()
{
}

void ListaPrestamos::insertaPrestamo(const Prestamo&)
{
}

void operator<<(ostream&, const ListaPrestamos&)
{
}
