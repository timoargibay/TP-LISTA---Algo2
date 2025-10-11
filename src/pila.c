#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"
#include "lista.h"

struct pila {
	lista_t *lista;
};

pila_t *pila_crear()
{
	pila_t *pila = malloc(sizeof(pila_t));

	if (pila == NULL)
		return NULL;

	pila->lista = lista_crear();

	if (pila->lista == NULL) {
		free(pila);
		return NULL;
	}

	return pila;
}

bool pila_apilar(pila_t *pila, void *elemento)
{
	if (pila == NULL || pila->lista == NULL)
		return false;

	//Manejo caso especial porque
	//lista insertar no admite insertar en lista vacia

	if (lista_cantidad(pila->lista) == 0)
		return lista_agregar(pila->lista, elemento);

	return lista_insertar(pila->lista, elemento, 0);
}

void *pila_desapilar(pila_t *pila)
{
	if (pila == NULL || pila->lista == NULL)
		return false;

	return lista_eliminar_elemento(pila->lista, 0);
}

void *pila_ver_primero(pila_t *pila)
{
	if (pila == NULL || pila->lista == NULL)
		return NULL;

	return lista_buscar_elemento(pila->lista, 0);
}

size_t pila_cantidad(pila_t *pila)
{
	if (pila == NULL || pila->lista == NULL)
		return 0;

	return lista_cantidad(pila->lista);
}

void pila_destruir(pila_t *pila)
{
	if (pila == NULL || pila->lista == NULL)
		return;

	while (lista_cantidad(pila->lista) != 0) {
		pila_desapilar(pila);
	}

	lista_destruir(pila->lista);
	free(pila);
}
