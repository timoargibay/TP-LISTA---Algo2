#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"

struct nodo {
	void *dato;
	struct nodo *siguiente;
};

typedef struct nodo nodo_t;

struct pila {
	nodo_t *primero;
	size_t cantidad;
};

pila_t *pila_crear()
{
	pila_t *nueva_lista = malloc(sizeof(pila_t));

	if (nueva_lista == NULL)
		return NULL;

	nueva_lista->cantidad = 0;
	nueva_lista->primero = NULL;

	return nueva_lista;
}

bool pila_apilar(pila_t *pila, void *elemento)
{
	if (pila == NULL)
		return false;

	nodo_t *nodo_nuevo = malloc(sizeof(nodo_t));

	if (nodo_nuevo == NULL)
		return false;

	nodo_nuevo->dato = elemento;
	nodo_nuevo->siguiente = NULL;

	if (pila->primero != NULL)
		nodo_nuevo->siguiente = pila->primero;

	pila->primero = nodo_nuevo;
	pila->cantidad++;

	return true;
}

void *pila_desapilar(pila_t *pila)
{
	if (pila == NULL || pila->primero == NULL)
		return NULL;

	nodo_t *actual = pila->primero;
	void *dato = NULL;

	dato = actual->dato;
	pila->primero = actual->siguiente;
	free(actual);
	pila->cantidad--;
	return dato;
}

void *pila_ver_primero(pila_t *pila)
{
	if (pila == NULL || pila->primero == NULL)
		return NULL;

	return pila->primero->dato;
}

size_t pila_cantidad(pila_t *pila)
{
	if (pila == NULL)
		return 0;

	return pila->cantidad;
}

void pila_destruir(pila_t *pila)
{
	if (pila == NULL)
		return;

	while (pila->cantidad != 0 && pila->primero != NULL) {
		pila_desapilar(pila);
	}

	free(pila);
}