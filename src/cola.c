#include "cola.h"
#include <stdlib.h>
#include <stdbool.h>

struct nodo {
	void *dato;
	struct nodo *siguiente;
};

typedef struct nodo nodo_t;

struct cola {
	nodo_t *primero;
	nodo_t *ultimo;
	size_t cantidad;
};

cola_t *cola_crear()
{
	cola_t *nueva_cola = malloc(sizeof(cola_t));
	if (nueva_cola == NULL)
		return NULL;

	nueva_cola->primero = NULL;
	nueva_cola->ultimo = NULL;
	nueva_cola->cantidad = 0;

	return nueva_cola;
}

bool cola_encolar(cola_t *cola, void *elemento)
{
	if (cola == NULL)
		return false;

	nodo_t *ultimo_nodo = NULL;

	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (nuevo_nodo == NULL)
		return false;

	if (cola->ultimo != NULL) {
		ultimo_nodo = cola->ultimo;
		ultimo_nodo->siguiente = nuevo_nodo;
	}

	if (cola->primero == NULL)
		cola->primero = nuevo_nodo;

	nuevo_nodo->dato = elemento;
	nuevo_nodo->siguiente = NULL;
	cola->cantidad++;
	cola->ultimo = nuevo_nodo;

	return true;
}

void *cola_desencolar(cola_t *cola)
{
	if (cola == NULL || cola->primero == NULL)
		return NULL;

	nodo_t *actual = cola->primero;
	void *dato = actual->dato;
	cola->primero = actual->siguiente;
	free(actual);
	cola->cantidad--;
	return dato;
}

void *cola_ver_primero(cola_t *cola)
{
	if (cola == NULL || cola->primero == NULL)
		return NULL;

	return cola->primero->dato;
}

size_t cola_cantidad(cola_t *cola)
{
	if (cola == NULL || cola->primero == NULL)
		return 0;

	return cola->cantidad;
}

void cola_destruir(cola_t *cola)
{
	if (cola == NULL)
		return;

	while (cola->cantidad != 0 && cola->primero != NULL) {
		cola_desencolar(cola);
	}

	free(cola);
}
