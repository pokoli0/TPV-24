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

		for (int i = 0; !input.eof() && i < n; i++)
		{
			input >> codigo;
			input >> fecha;
			input >> user;

			elems[i].setEjemplar(catalogo.buscaEjemplar(codigo));
			elems[i].setFecha(fecha);
			elems[i].setUsuario(user);
		}
	}

	input.close();

	return encontrado;
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
