gcc_condiciones = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g

valgrind_condiciones = --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes

pruebas_compilar: pruebas_alumno.c src_compilar tp1_compilar
	gcc $(gcc_condiciones) pruebas_alumno.c archivos_objeto/lista.o archivos_objeto/pila.o archivos_objeto/cola.o -o pruebas_alumno

src_compilar: src/lista.c src/pila.c src/cola.c
	gcc $(gcc_condiciones) -c src/lista.c -o archivos_objeto/lista.o
	gcc $(gcc_condiciones) -c src/cola.c -o archivos_objeto/cola.o
	gcc $(gcc_condiciones) -c src/pila.c -o archivos_objeto/pila.o

tp1_compilar: src/tp1.c src/extras_tp1.c
	gcc $(gcc_condiciones) -c src/extras_tp1.c -o archivos_objeto/extras_tp1.o
	gcc $(gcc_condiciones) -c src/tp1.c -o archivos_objeto/tp1.o

main_compilar: main.c src_compilar tp1_compilar
	gcc $(gcc_condiciones) main.c archivos_objeto/lista.o archivos_objeto/tp1.o archivos_objeto/extras_tp1.o -o main

format:
	clang-format -i -style=file pruebas_alumno.c
	clang-format -i -style=file src/lista.c src/pila.c src/cola.c src/extras_tp1.c src/tp1.c
	clang-format -i -style=file src/lista.h src/pila.h src/cola.h src/extras_tp1.h src/tp1.h
	clang-format -i -style=file main.c

preparar_entrega: main_compilar format
	rm -f main
	rm -f pruebas_alumno
	rm -f archivos_objeto/*.o

valgrind_pruebas: pruebas_compilar
	valgrind $(valgrind_condiciones) ./pruebas_alumno

valgrind_main: main_compilar
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes ./main ejemplo_main_valgrind.txt buscar nombre Pikachu
