#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "objetos.h"
#include "tablero.h"


/////////////////////////////////////////////////
// Programa principal

int main(int argc, char** argv)
{
	// Crear un array doble de tamaño "NFILAS"x"NCOLUMNAS" de tipo "objeto_t", llamado "tablero.
	objeto_t tablero[NFILAS][NCOLUMNAS];

	// Iniciar el tablero (llamar a la función indicada)
	iniciaTablero(tablero, NFILAS, NCOLUMNAS);

	// Dibujar el tablero (llamar a la función indicada
	dibujaTablero(tablero, NFILAS, NCOLUMNAS);
	
	// Terminar
}

