/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 04-05-2022 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "objetos.h"
#include "tablero.h"
#include "utils.h"

/////////////////////////////////////////////////
// Programa principal

int main(int argc, char** argv)
{
	int numFilas = 0,
		numColumnas = 0;

	printf("[!] Introduzca el numero de filas del tablero:\n");
	numFilas = leeNumero();
	printf("[!] Introduzca el numero de columnas del tablero:\n");
	numColumnas = leeNumero();

	// Crear un array doble de tamaño "NFILAS"x"NCOLUMNAS" de tipo "objeto_t", llamado "tablero.
	t_objeto **tablero = reservaTablero(numFilas, numColumnas);

	// Iniciar el tablero (llamar a la función indicada)
	iniciaTableroConDatos(tablero, numFilas, numColumnas, argc, argv);

	do
	{
		// Dibujar el tablero (llamar a la función indicada)
		dibujaTablero(tablero, numFilas, numColumnas);

		// Actualiza el tablero
		actualizaTablero(tablero, numFilas, numColumnas);
	}
	while(buscaPersonaje(tablero, numFilas, numColumnas));

	// Terminar
	liberaTablero(tablero, numFilas, numColumnas);
}

