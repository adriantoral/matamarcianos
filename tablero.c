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
		nMisiles = (rand() % 4) + 2; // 2-5

	/* Generar objetos vacios */
	/* for (int i=0; i<numFilas; i++) */
	/* 	for (int j=0; j<numColumnas; j++) */
	/* 		tablero[i][j] = CrearObjeto(empty); */	

	// Inicializar el tablero con objetos "no activos"
	for (int i=0; i<numFilas; i++)
		for (int j=0; j<numColumnas; j++)
		{
			pTablero = &(tablero[i][j]);
			pTablero->x = j; 
			pTablero->y = i;
			pTablero->esta_activo = 0;
			pTablero->sprite = ' ';
		}

	// Numero de enemigos entre 1 y 3
	// Aniadir Enemigos
		// La posición está en la mitad superior del tablero (Y<=(numFilas/2))
	for (int i=1; i<= nEnemigos; i++)
	{
		int x = rand() % numColumnas,
			y = rand() % (numFilas / 2);

		pTablero = &(tablero[y][x]);
		*pTablero = CrearObjeto(enemigo);
		pTablero->x = x;
		pTablero->y = y;
	}

	// Numero de misiles entre 2 y 5
	// Aniadir misiles
		// Cualquier posición del tablero
	for (int i=1; i<= nMisiles; i++)
	{
		int x = rand() % numColumnas,
			y = rand() % numFilas;

		pTablero = &(tablero[y][x]);
		*pTablero = CrearObjeto(misil);
		pTablero->x = x;
		pTablero->y = y;
	}

	//El  personaje principal está en la fila más inferior del tablero, en una columna aleatoria
	int x = rand() % numColumnas,
		y = numFilas - 1;

	pTablero = &(tablero[y][x]);
	*pTablero = CrearObjeto(personaje);
	pTablero->x = x;
	pTablero->y = y;
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


