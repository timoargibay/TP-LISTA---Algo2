#include "pa2m.h"
#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"

void prueba_crear_lista()
{
	lista_t *prueba = lista_crear();
	if (prueba != NULL)
		free(prueba);

	pa2m_afirmar(prueba != NULL, "Se crea una lista correctamente!");
}

void prueba_lista_vacia()
{
	lista_t *prueba = lista_crear();

	bool esta_vacia = lista_vacia(prueba);

	pa2m_afirmar(esta_vacia == true, "Se detecto que la lista esta vacia!");

	if (prueba != NULL)
		free(prueba);
}

void prueba_lista_vacia_null()
{
	bool esta_vacia = lista_vacia(NULL);
	pa2m_afirmar(esta_vacia == true,
		     "Si se pasa lista NULL, devuelve true");
}

void prueba_lista_crear_devuelve_lista_vacia()
{
	lista_t *nueva_lista = lista_crear();
	if (nueva_lista != NULL)
		lista_destruir(nueva_lista);

	pa2m_afirmar(nueva_lista != NULL,
		     "Crear una lista devuelve una lista vacia");
}

void prueba_lista_insertar_en_pos0()
{
	lista_t *nueva_lista = lista_crear();
	if (nueva_lista == NULL)
		return;

	char *mensaje_secreto = "Man I love C";
	bool se_inserto = lista_insertar(nueva_lista, mensaje_secreto, 0);

	pa2m_afirmar(se_inserto == false && lista_cantidad(nueva_lista) == 0,
		     "NO se insertó en la posicion 0 con lista_insertar");
	lista_destruir(nueva_lista);
}

void prueba_crear_iterador()
{
	lista_t *nueva_lista = lista_crear();
	if (nueva_lista == NULL)
		return;

	int mi_numero_favorito = 8;
	int mi_segundo_numero_favorito = 4;
	lista_agregar(nueva_lista, &mi_numero_favorito);
	lista_agregar(nueva_lista, &mi_segundo_numero_favorito);

	lista_iterador_t *nuevo_iterador = lista_iterador_crear(nueva_lista);
	if (nuevo_iterador == NULL) {
		lista_destruir(nueva_lista);
		printf("\n Esta prueba salio mal \n");
		return;
	}

	pa2m_afirmar(nuevo_iterador != NULL,
		     "Se creó un iterador correctamente");
	lista_destruir(nueva_lista);
	lista_iterador_destruir(nuevo_iterador);
}

void prueba_crear_iterador_lista_null()
{
	lista_iterador_t *nuevo_iterador = lista_iterador_crear(NULL);
	pa2m_afirmar(nuevo_iterador == NULL,
		     "Si se pasa lista NULL, iterador es NULL");
}

void prueba_iterador_obtener_0()
{
	lista_t *nueva_lista = lista_crear();
	if (nueva_lista == NULL) {
		printf("\nNo pude crear bien la lista\n");
		return;
	}

	int mi_numero_favorito = 8;
	int mi_segundo_numero_favorito = 4;
	lista_iterador_t *nuevo_iterador = NULL;

	if (lista_agregar(nueva_lista, &mi_numero_favorito) &&
	    lista_agregar(nueva_lista, &mi_segundo_numero_favorito)) {
		nuevo_iterador = lista_iterador_crear(nueva_lista);
	}

	if (nuevo_iterador == NULL) {
		printf("\nNo se creó bien el iterador\n");
		lista_destruir(nueva_lista);
		return;
	}

	int *dato_0 = lista_iterador_obtener_actual(nuevo_iterador);
	pa2m_afirmar((*dato_0) == mi_numero_favorito,
		     "Se obtuvo el elemento 0 correctamente");

	lista_destruir(nueva_lista);
	lista_iterador_destruir(nuevo_iterador);
}

void prueba_recibir_5_elementos()
{
	int n1, n2, n3, n4, n5;
	n1 = 1;
	n2 = n1 + 1;
	n3 = n2 + 1;
	n4 = n3 + 1;
	n5 = n4 + 1;

	lista_t *lista = lista_crear();
	if (lista == NULL) {
		printf("\nError armando lista\n");
		return;
	}

	lista_agregar(lista, &n1);
	lista_agregar(lista, &n2);
	lista_agregar(lista, &n3);
	lista_agregar(lista, &n4);
	lista_agregar(lista, &n5);

	lista_iterador_t *iterador = lista_iterador_crear(lista);
	int *dato1 = lista_iterador_obtener_actual(iterador);
	lista_iterador_siguiente(iterador);
	int *dato2 = lista_iterador_obtener_actual(iterador);
	lista_iterador_siguiente(iterador);
	int *dato3 = lista_iterador_obtener_actual(iterador);
	lista_iterador_siguiente(iterador);
	int *dato4 = lista_iterador_obtener_actual(iterador);
	lista_iterador_siguiente(iterador);
	int *dato5 = lista_iterador_obtener_actual(iterador);
	lista_iterador_siguiente(iterador);

	bool afirmacion = ((*dato1) == n1) && (*dato2) == n2 &&
			  (*dato3) == n3 && (*dato4) == n4 && (*dato5) == n5;
	pa2m_afirmar(afirmacion, "Iterador devuelve los 5 elementos en orden");

	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

void prueba_pila_crear()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "Se creo una pila correctamente!");
	pila_destruir(pila);
}

void prueba_pila_apilar()
{
	pila_t *pila = pila_crear();
	int n1, n2, n3, n4, n5;
	n1 = 1;
	n2 = n1 + 1;
	n3 = n2 + 1;
	n4 = n3 + 1;
	n5 = n4 + 1;

	pila_apilar(pila, &n1);
	pila_apilar(pila, &n2);
	pila_apilar(pila, &n3);
	pila_apilar(pila, &n4);
	pila_apilar(pila, &n5);

	size_t cantidad_5 = pila_cantidad(pila);

	int *dato5 = pila_desapilar(pila);
	int *dato4 = pila_desapilar(pila);
	int *dato3 = pila_desapilar(pila);
	int *dato2 = pila_desapilar(pila);
	int *dato1 = pila_desapilar(pila);

	bool afirmacion = (cantidad_5 == 5) && ((*dato1) == n1) &&
			  ((*dato2) == n2) && ((*dato3) == n3) &&
			  ((*dato4) == n4) && ((*dato5) == n5);

	pa2m_afirmar(afirmacion, "Se apilan y desapilan bien los elementos");
	pila_destruir(pila);
}

void prueba_cola_crear()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "Se creó la cola correctamente");
	cola_destruir(cola);
}

void prueba_cola_encolar()
{
	cola_t *cola = cola_crear();
	int n1, n2, n3, n4, n5;
	n1 = 1;
	n2 = n1 + 1;
	n3 = n2 + 1;
	n4 = n3 + 1;
	n5 = n4 + 1;

	cola_encolar(cola, &n1);
	cola_encolar(cola, &n2);
	cola_encolar(cola, &n3);
	cola_encolar(cola, &n4);
	cola_encolar(cola, &n5);

	size_t cantidad_5 = cola_cantidad(cola);

	int *dato1 = cola_desencolar(cola);
	int *dato2 = cola_desencolar(cola);
	int *dato3 = cola_desencolar(cola);
	int *dato4 = cola_desencolar(cola);
	int *dato5 = cola_desencolar(cola);

	bool afirmacion = (cantidad_5 == 5) && ((*dato1) == n1) &&
			  ((*dato2) == n2) && ((*dato3) == n3) &&
			  ((*dato4) == n4) && ((*dato5) == n5);

	pa2m_afirmar(afirmacion, "Se encolan y desencolan bien los elementos");
	cola_destruir(cola);
}

int main()
{
	pa2m_nuevo_grupo("======== Pruebas a funciones de lista_t ========");
	prueba_crear_lista();
	prueba_lista_vacia();
	prueba_lista_vacia_null();
	prueba_lista_crear_devuelve_lista_vacia();
	prueba_lista_insertar_en_pos0();

	pa2m_nuevo_grupo("======== Pruebas a funciones de iterador =======");
	prueba_crear_iterador();
	prueba_crear_iterador_lista_null();
	prueba_iterador_obtener_0();
	prueba_recibir_5_elementos();

	pa2m_nuevo_grupo("=======Pruebas Pila=======");
	prueba_pila_crear();
	prueba_pila_apilar();

	pa2m_nuevo_grupo("=======Pruebas Cola=======");
	prueba_cola_crear();
	prueba_cola_encolar();

	return pa2m_mostrar_reporte();
}
