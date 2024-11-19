#pragma once
#include <iterator>
#include <list>

template <typename T>
class GameList {
private:
    std::list<T*> _elements; // Contenedor de objetos (punteros)

public:
    // M�todos para a�adir elementos
    void push_back(T* elem) {
        auto it = _elements.insert(_elements.end(), elem);
        elem->setListAnchor(anchor(it, this));
    }

    void push_front(T* elem) {
        auto it = _elements.insert(_elements.begin(), elem);
        elem->setListAnchor(anchor(it, this));
    }

    // M�todo para eliminar elementos
    void remove(typename std::list<T*>::iterator it) {
        _elements.erase(it);
    }

    // Iteradores para recorrer los elementos
    auto begin() { return _elements.begin(); }
    auto end() { return _elements.end(); }

    // Verifica si la lista est� vac�a
    bool empty() const { return _elements.empty(); }

    // Clase anchor
    class anchor {
        typename std::list<T*>::iterator _it; // Iterador al nodo en la lista
        GameList<T>* _list;                  // Referencia a la lista

    public:
        // Constructor por defecto: indica que el objeto no est� anclado
        anchor() : _list(nullptr) {}

        // Configura el ancla a un nodo espec�fico
        anchor(typename std::list<T*>::iterator it, GameList<T>* list)
            : _it(it), _list(list) {}

        // Mueve el ancla
        anchor(anchor&& other) noexcept : _it(other._it), _list(other._list) {
            other._list = nullptr;
        }

        // Elimina el nodo de la lista al destruir el objeto
        ~anchor() {
            if (_list) _list->remove(_it);
        }

        // Sobrecargamos =
        anchor& operator=(anchor&& other) noexcept {
            if (this != &other) {
                if (_list) _list->remove(_it);
                _it = other._it;
                _list = other._list;
                other._list = nullptr;
            }
            return *this;
        }
    };
};