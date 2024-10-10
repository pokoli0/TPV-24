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

void ListaPrestamos::ordenarLista()
{
	Prestamo* a = elems + capacidad;
	sort(elems, a);
}

void ListaPrestamos::mostrarPrestamos()
{
	Date* actual = new Date();
	for (int i = 0; i < capacidad; i++) {
		cout << elems[i].getFecha() <<
			" (en " <<
			elems[i].getFecha().diff(*actual) <<
			" dias) ";
			//elems[i].getEjemplar()->getNombre() << 

		if (elems[i].getFecha().diff(*actual) < 0) {
			cout << " (" <<
			elems[i].getFecha().diff(elems[i].getFechaDevolucion()) <<
			" dias de penalizacion)";
		}

			cout << endl;
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
