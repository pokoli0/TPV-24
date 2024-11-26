/**
 * Lista de objetos con eliminaci�n eficiente.
 *
 * @file gameList.h
 * @author Rub�n Rubio
 * @date TPV1 2024
 */

#ifndef GAME_LIST_H
#define GAME_LIST_H
#include "checkML.h"

#include <cassert>
#include <compare>

 /**
  * Lista de objetos que guardan una referencia opaca a su posici�n en la lista
  * para borrarse eficientemente. Los m�todos de inserci�n de la lista fijan esa
  * referencia, para lo que la clase @c T debe proporcionar un m�todo
  * @c setListAnchor que reciba por movimiento un objeto de tipo @c GameList::anchor.
  *
  * @tparam T Tipo de los objetos almacenados (sin puntero, aunque los objetos
  * se almacenan como punteros).
  */
template<typename T>
class GameList
{
	/// Nodo de la lista doblemente enlazada
	struct Node
	{
		Node* prev, * next;
		T* elem;      ///< Elemento
		int refCount; ///< Contador de referencias (iteradores) al objeto

		Node(Node* base, T* elem = nullptr)
			: elem(elem)
			, refCount(1)
		{
			linkAfter(base);
		}

		Node()
			: prev(this)
			, next(this)
			, elem(reinterpret_cast<T*>(1))
			, refCount(1)
		{
			// Constructor para el nodo fantasma
		}

		~Node()
		{
			unlink();
		}

		/// Si el nodo es fantasma
		bool isGhost() const
		{
			return elem == reinterpret_cast<T*>(1);
		}

		/// Desconecta el nodo de la lista
		void unlink()
		{
			prev->next = next;
			next->prev = prev;
		}

		/// Conecta el nodo tras el nodo dado
		void linkAfter(Node* node)
		{
			next = node->next;
			prev = node;
			next->prev = this;
			node->next = this;
		}

		/// Elimina el elemento de la lista (aunque puede que no
		/// se elimine inmediatamente porque haya iteradores sobre �l)
		void destroy()
		{
			elem = nullptr;
			unref();
		}

		/// A�ade una referencia al nodo
		void addref()
		{
			++refCount;
		}

		/// Retira una referencia al nodo y lo elimina si no es referenciado
		void unref()
		{
			if (--refCount == 0)
				delete this;
		}
	};

	/// Nodo fantasma que da acceso a la lista
	mutable Node ghostNode;

	/// Puntero a uno de los atributo (next o prev) de Node
	/// (para implementar iteradores en ambos sentidos)
	using Pivot = Node * (Node::*);

public:
	/// Referencia que permite borrar elementos de la lista
	class anchor {
		Node* pointer;

		/// Construye un ancla
		explicit anchor(Node* pointer) : pointer(pointer) {}
		friend GameList;
	public:
		/// Ancla que no apunta a nada
		anchor() : pointer(nullptr) {}

		/// No se puede copiar
		anchor(const anchor& other) = delete;
		anchor& operator=(const anchor& other) = delete;

		/// Se puede mover un ancla
		anchor(anchor&& other)
			: pointer(other.pointer)
		{
			other.pointer = nullptr;
		}

		anchor& operator=(anchor&& other)
		{
			this->~anchor();
			pointer = other.pointer;
			other.pointer = nullptr;
			return *this;
		}

		/// Desenlaza el objeto de la lista
		void unlink() {
			delete pointer;
			pointer = nullptr;
		}

		/// Inserta un objeto despu�s de este nodo
		void insert_after(T* value)
		{
			// Comprobamos en depuraci�n que no se insertan valores nulos
			assert(value != nullptr);
			assert(pointer != nullptr);
			value->setListAnchor(anchor(new Node(pointer, value)));
		}

		/// Inserta un objeto antes de este nodo
		void insert_before(T* value)
		{
			// Comprobamos en depuraci�n que no se insertan valores nulos
			assert(value != nullptr);
			assert(pointer != nullptr);
			value->setListAnchor(anchor(new Node(pointer->prev, value)));
		}

		/// El destructor del ancla elimina el nodo enlazado
		~anchor() { if (pointer) pointer->destroy(); }
	};

	/// Crea una lista inicialmente vac�a
	GameList() = default;

	/// La lista no es propietaria siquiera de sus nodos, as� que no
	/// tiene nada que destruir

	/// �La lista es vac�a?
	bool empty() const
	{
		return ghostNode->next == ghostNode->prev;
	}

	/// Impide copiar la lista
	GameList(const GameList& other) = delete;
	GameList& operator=(const GameList& other) = delete;

	/// Permite mover la lista
	GameList(GameList&& other)
		: ghostNode(other.ghostNode)
	{
		// Ajusta los enlaces porque el nodo fantasma ha
		// cambiado de direcci�n de memoria
		ghostNode.prev.next = &ghostNode;
		ghostNode.next.prev = &ghostNode;
	}

	/// A�ade un nuevo objeto al principio de la lista y fija su iterador
	void push_front(T* value)
	{
		// Comprobamos en depuraci�n que no se insertan valores nulos
		assert(value != nullptr);
		value->setListAnchor(anchor(new Node(&ghostNode, value)));
	}

	/// A�ade un nuevo objeto al final de la lista y fija su iterador
	void push_back(T* value)
	{
		// Comprobamos en depuraci�n que no se insertan valores nulos
		assert(value != nullptr);
		value->setListAnchor(anchor(new Node(ghostNode.prev, value)));
	}

	/// Iterador constante sobre los objetos de la lista
	template <Pivot pivot, typename RT>
	class iterator
	{
		// El constructor es privado, pero no para GameList
		friend GameList;

		/// El nodo de la lista al que apunta el iterador
		Node* node;

		iterator(Node* node)
			: node(node)
		{
			node->addref();
			skip();
		}

		void
			skip()
		{
			// Se salta los nodos con elemento nulo, es decir,
			// con elemento que ha sido borrado
			while (node->elem == nullptr && !node->isGhost())
				node = node->*pivot;
		}

	public:
		/// Se elimina la referencia al nodo cuando se destruye el iterador
		~iterator()
		{
			node->unref();
		}

		/// Accede al elemento apuntado por el iterador
		RT operator*() const
		{
			return node->elem;
		}

		/// Itera al siguiente elemento de la lista
		iterator& operator++()
		{
			Node* prev = node;
			node = node->*pivot;
			// A�ade una referencia al nodo al que llegamos
			node->addref();
			// Elimina una referencia al nodo del que nos vamos
			prev->unref();
			// Salta los nodos pendientes de eliminaci�n
			skip();

			return *this;
		}

		auto operator<=>(const iterator& other) const = default;
	};

	/// Iterador constante al inicio de la lista
	auto begin() const
	{
		return iterator<&Node::next, const T*>(ghostNode.next);
	}

	/// Iterador constante al final de la lista
	auto end() const
	{
		return iterator<&Node::next, const T*>(&ghostNode);
	}

	/// Iterador constante al principio de la lista en sentido inverso
	auto rbegin() const
	{
		return iterator<&Node::prev, const T*>(ghostNode.prev);
	}

	/// Iterador constante al final de la lista en sentido inverso
	auto rend() const
	{
		return iterator<&Node::prev, const T*>(&ghostNode);
	}

	/// Iterador al inicio de la lista
	auto begin()
	{
		return iterator<&Node::next, T*>(ghostNode.next);
	}

	/// Iterador al final de la lista
	auto end()
	{
		return iterator<&Node::next, T*>(&ghostNode);
	}

	/// Iterador al principio de la lista en sentido inverso
	auto rbegin()
	{
		return iterator<&Node::prev, T*>(ghostNode.prev);
	}

	/// Iterador al final de la lista en sentido inverso
	auto rend()
	{
		return iterator<&Node::prev, T*>(&ghostNode);
	}
};

#endif // GAME_LIST
