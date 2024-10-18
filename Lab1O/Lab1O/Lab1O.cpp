// PAULA SIERRA LUQUE
// MARCOS PANTOJA 

#include <iostream>
#include <Windows.h>
#include "Catalogo.h"
#include "ListaPrestamos.h"

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    Catalogo catalogo;
    ListaPrestamos listaPrestamos;

    catalogo.LeeCatalogo("catalogo.txt");
    listaPrestamos.leerPrestamos("prestamos.txt", catalogo);


    cout << "Seleccione opción:" << endl 
    << "a) Mostrar catálogo" << endl
    << "b) Mostrar préstamos" << endl
    << "c) Insertar ejemplar" << endl
    << "d) Prestar ejemplar" << endl
    << "e) Devolver ejemplar" << endl
    << "f) Salir" << std::endl;

    char input;
    cin >> input;

    string nombre;
    int cod, user;
    char tipo;
    Date fecha = Date();

    switch (input) {

    case 'a':
        cout << "Seleccionada: a) Mostrar catálogo" << endl;
        catalogo.mostrarCatalogo();

        break;

    case 'b':
        cout << "Seleccionada: b) Mostrar préstamos" << endl;
        listaPrestamos.mostrarPrestamos();

        break;

    case 'c':
        cout << "Seleccionada: c) Insertar ejemplar" << endl <<
            "Tipo de ejemplar L) Libros / A) Audiovisual / J) Juegos: " << endl;
        cin >> tipo;

        cout << "Inserte el nombre del ejemplar: " << endl;
        cin >> nombre;
        cout << "Nombre: " << nombre << endl;

        catalogo.insertaEjemplar(tipo, nombre);

        break;

    case 'd':
        cout << "Seleccionada: d) Prestar ejemplar" << endl;

        cout << "Inserta el código del ejemplar: " << endl;
        cin >> cod;

        //Ejemplar* e = catalogo.buscarEjemplar(cod, 0, catalogo.getTam());


        cout << "Inserta tu usuario: " << endl;
        cin >> user;

        //Prestamo p = Prestamo(e, fecha, u);

        //listaPrestamos.insertaPrestamo(p);
        //listaPrestamos.ordenarPrestamos();

        break;

    case 'e':
        cout << "Seleccionada: e) Devolver ejemplar" << endl;

        cout << "Inserta el código del ejemplar: " << endl;
        cin >> cod;

        //Ejemplar* e = catalogo.buscarEjemplar(cod, 0, catalogo.getTam());

        cout << "Inserta tu usuario: " << endl;
        cin >> user;

        //Prestamo p = Prestamo(e, fecha, user);
        
        //listaPrestamos.insertaPrestamo(p);

        //listaPrestamos.ordenarPrestamos();

        break;

    case 'f':
        cout << "Seleccionada: f) Salir" << endl;
        exit(0);

        break;

    default:
        cout << "Seleccion no válida" << endl;
        exit(0);
        break;
    }


    return 0;
}


