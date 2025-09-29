#include "src/lista.h"
#include "src/tp1.h"
#include "src/extras_tp1.h"
#include <stdio.h>

void destruir_pokemon_lista(void *pokemon)
{
	if (pokemon == NULL)
		return;

	struct pokemon *pokemon_a_liberar = pokemon;
	free(pokemon_a_liberar->nombre);
	free(pokemon_a_liberar);
}

/*
* Muestra el pokemon enviado por pantalla
*/
bool mostrar_pokemon(struct pokemon *pokemon_seleccionado)
{
	char *tipo_pokemon = malloc(16 * sizeof(char));
	if (tipo_pokemon == NULL)
		return false;

	switch (pokemon_seleccionado->tipo) {
	case TIPO_AGUA:
		strcpy(tipo_pokemon, "Agua");
		break;
	case TIPO_ELEC:
		strcpy(tipo_pokemon, "Electrico");
		break;
	case TIPO_FANT:
		strcpy(tipo_pokemon, "Fantasma");
		break;
	case TIPO_FUEG:
		strcpy(tipo_pokemon, "Fuego");
		break;
	case TIPO_LUCH:
		strcpy(tipo_pokemon, "Lucha");
		break;
	case TIPO_NORM:
		strcpy(tipo_pokemon, "Normal");
		break;
	case TIPO_PLAN:
		strcpy(tipo_pokemon, "Planta");
		break;
	case TIPO_PSI:
		strcpy(tipo_pokemon, "Psiquico");
		break;

	default:
		strcpy(tipo_pokemon, "INVALIDO");
		break;
	}

	printf("------------------------------\n");
	printf("ID: %i\nNombre: %s\nTipo: %s\nAtaque: %i\nDefensa: %i\nVelocidad: %i",
	       pokemon_seleccionado->id, pokemon_seleccionado->nombre,
	       tipo_pokemon, pokemon_seleccionado->ataque,
	       pokemon_seleccionado->defensa, pokemon_seleccionado->velocidad);
	printf("\n------------------------------\n");

	free(tipo_pokemon);
	return true;
}

char *copiar_string(char *string)
{
	if (string == NULL)
		return NULL;

	char *copia = malloc((strlen(string) + 1) * sizeof(char));
	if (copia == NULL)
		return NULL;

	strcpy(copia, string);
	return copia;
}

/* Originalmente esta funcion solo era una linea (su return) pero por errores con valgrind
	*decidi hacer una copia real de cada pokemon en vez de solamente poner un puntero al pokemon original
	*en los nodos, asi tp1_destruir y los destructores de tp_lista hacen su trabajo por separado bien.
	*Tambien es la razon por la que incorporé una funcion que copie un string
*/
bool copia_agrega_pokemon(struct pokemon *el_pokemon, void *una_lista)
{
	struct pokemon *pokemon_lista = malloc(sizeof(struct pokemon));
	if (pokemon_lista == NULL)
		return false;

	*pokemon_lista = *el_pokemon;
	pokemon_lista->nombre = copiar_string(el_pokemon->nombre);

	if (pokemon_lista->nombre == NULL) {
		free(pokemon_lista);
		return false;
	}

	return lista_agregar(una_lista, pokemon_lista);
}

lista_t *array_a_lista(tp1_t *array_pokemons)
{
	if (array_pokemons == NULL)
		return NULL;
	lista_t *nueva_lista = lista_crear();
	if (nueva_lista == NULL)
		return NULL;

	size_t pokemons_agregados = tp1_con_cada_pokemon(
		array_pokemons, copia_agrega_pokemon, nueva_lista);

	if (pokemons_agregados != tp1_cantidad(array_pokemons)) {
		lista_destruir(nueva_lista);
		nueva_lista = NULL;
	}

	return nueva_lista;
}

int main(int argc, char *argumento[])
{
	if (argc < 2) {
		printf("Error: Faltan argumentos!\n");
		return 1;
	}

	tp1_t *pokemons_1 = tp1_leer_archivo(argumento[1]);
	if (pokemons_1 == NULL)
		return 1;

	lista_t *lista_pokemons = array_a_lista(pokemons_1);

	if (lista_pokemons == NULL)
		return 1;
	else
		tp1_destruir(pokemons_1);

	struct pokemon *pokemon_actual = NULL;
	size_t i = 0;
	bool se_encontro = false;
	int argumento_4_id = strtnum(argumento[4]);
	size_t cantidad_elementos = lista_cantidad(lista_pokemons);
	lista_iterador_t *iterar_pokemons =
		lista_iterador_crear(lista_pokemons);
	if (iterar_pokemons == NULL)
		return 1;

	/*---------Manejo de posibilidades---------*/
	if (strcmp(argumento[3], "id") == 0) {
		while (i < cantidad_elementos && se_encontro == false) {
			pokemon_actual =
				lista_iterador_obtener_actual(iterar_pokemons);

			if (argumento_4_id == pokemon_actual->id) {
				mostrar_pokemon(pokemon_actual);
				se_encontro = true;
			}

			lista_iterador_siguiente(iterar_pokemons);
			i++;
		}
	} else if (strcmp(argumento[3], "nombre") == 0) {
		while (i < cantidad_elementos && se_encontro == false) {
			pokemon_actual =
				lista_iterador_obtener_actual(iterar_pokemons);

			if (strcmp(argumento[4], pokemon_actual->nombre) == 0) {
				mostrar_pokemon(pokemon_actual);
				se_encontro = true;
			}

			lista_iterador_siguiente(iterar_pokemons);
			i++;
		}
	}

	lista_iterador_destruir(iterar_pokemons);
	lista_destruir_todo(lista_pokemons, destruir_pokemon_lista);

	return 0;
}
