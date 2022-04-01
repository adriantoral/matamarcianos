#include "tablero.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "enemigo.h"
#include "misil.h"
#include "objetos.h"
#include "personaje.h"
#include "tipos.h"

void iniciaTablero(objeto_t tablero[NFILAS][NCOLUMNAS], int numFilas, int numColumnas)
{
	// Iniciar el random
	srand(getpid());

	// Variables AUX
	objeto_t *pTablero = NULL;

	int nEnemigos = (rand() % 3) + 1, // 1-3
		nMisiles  = (rand() % 4) + 2; // 2-5

	/* Debug de numero de enemigos y misiles */
	/* printf("Enemigos : %d\nMisiles : %d\n", nEnemigos, nMisiles); */

	// Inicializar el tablero con objetos "no activos"
	for (int i=0; i<numFilas; i++)
		for (int j=0; j<numColumnas; j++)
		{
			pTablero = &(tablero[i][j]);
			*pTablero = CrearObjeto(empty, j, i);
			pTablero->esta_activo = 0;
		}

	// Numero de enemigos entre 1 y 3
	// Aniadir Enemigos
	// La posición está en la mitad superior del tablero (Y<=(numFilas/2))
	for (int i=1; i<=nEnemigos; i++)
	{
		int xEnemigo = 0,
			yEnemigo = 0;

		do
		{
			xEnemigo = rand() % numColumnas;
			yEnemigo = rand() % (numFilas / 2);
		}while(tablero[yEnemigo][xEnemigo].esta_activo);

		pTablero = &(tablero[yEnemigo][xEnemigo]);
		*pTablero = CrearObjeto(enemigo, xEnemigo, yEnemigo);
	}

	// Numero de misiles entre 2 y 5
	// Aniadir misiles
	// Cualquier posición del tablero
	for (int i=1; i<=nMisiles; i++)
	{
		int xMisil = 0,
			yMisil = 0;

		do
		{
			xMisil = rand() % numColumnas,
				   yMisil = rand() % numFilas;
		}while(tablero[yMisil][xMisil].esta_activo);

		pTablero = &(tablero[yMisil][xMisil]);
		*pTablero = CrearObjeto(misil, xMisil, yMisil);
	}

	//El  personaje principal está en la fila más inferior del tablero, en una columna aleatoria
	int xPersonaje = rand() % numColumnas,
		yPersonaje = numFilas - 1;

	pTablero = &(tablero[yPersonaje][xPersonaje]);
	*pTablero = CrearObjeto(personaje, xPersonaje, yPersonaje);
}

void dibujaTablero(objeto_t tablero[NFILAS][NCOLUMNAS], int numFilas, int numColumnas)
{
	// Por cada fila,columna de tablero
	// Si el objeto está activo
	// Mostrar su sprite
	// Si no
	// Mostrar un espacio en blanco
	for (int i=0; i<numFilas; i++)
	{
		if (i == numFilas - numFilas) 
		{
			printf(" ");
			for (int i=0; i<numColumnas; i++) printf("-");
			printf("\n");
		}

		for (int j=0; j<numColumnas; j++)
		{
			if (j == numColumnas - numColumnas) printf("[");
			printf("%c", tablero[i][j].sprite);
			if (j == numColumnas - 1) printf("]");
		}

		printf("\n");

		if (i == numFilas - 1)
		{
			printf(" ");
			for (int i=0; i<numColumnas; i++) printf("-");
			printf("\n");
		}
	}
}

