#ifndef METHOD_H
#define METHOD_H

/**
 * Clase functor (porque define un operator()) que envuelve un método de
 * instancia junto a la instancia con la que se aplica.
 *
 * El constructor recibe un método y el objeto sobre el que se aplica.
 *
 * Es un ejemplo de las cosas más enrevesadas de C++ (plantillas
 * con número de argumentos variables, punteros a métodos, etc.).
 * Obviamente, esto no forma parte del temario de la asignatura.
 */
template<typename T, typename R, typename... Args>
class Method {
	using MType = R(T::*)(Args...);

	MType method;	// Puntero al método
	T* object;	// Puntero al objeto

public:
	Method(MType method, T* object)
	 : method(method)
	 , object(object) {}

	// Llamada al método
	R operator()(Args... args) const {
		(object->*method)(args...);
	}
};

#endif // METHOD_H
