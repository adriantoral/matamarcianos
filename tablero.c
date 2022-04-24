/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 24-04-2022 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "tablero.h"
#include "enemigo.h"
#include "misil.h"
#include "objetos.h"
#include "personaje.h"
#include "tipos.h"

int buscaPersonaje(objeto_t **tablero, int numFilas, int numColumnas)
{
	for (int i=0; i<numFilas; i++)
		for (int j=0; j<numColumnas; j++)
		{
			objeto_t *objeto = &(tablero[i][j]);
			if (objeto->esta_activo && objeto->tipo == personaje) return 1;
		}

	return 0;
}

void liberaTablero(objeto_t **tablero, int numFilas)
{
	for (int i=0; i<numFilas; i++) free(tablero[i]);
	free(tablero);
}

objeto_t **reservaTablero(int numFilas, int numColumnas)
{
	// Declarar un puntero doble de objeto_t llamado tablero
	objeto_t **tablero = NULL;

	// Iniciar la primera dimensión del puntero doble “tablero” con un array de numFilas de punteros a objeto_t
	tablero = (objeto_t **)malloc(sizeof(objeto_t) * numFilas);

	// Inicializar esa fila del tablero con un array de objeto_t de tamaño “numColumnas"
	for (int i=0; i<numFilas; i++) tablero[i] = (objeto_t *)malloc(sizeof(objeto_t) * numColumnas);

	//devolver el array doble tablero
	return tablero;
}

void actualizaTablero(objeto_t **tablero, int numFilas, int numColumnas)
{
	// Por cada posición del tablero
	// Si es un objeto activo
	// Obtener el tipo del objeto
	// Llamar a su función de movimiento: mueveEnemigo, mueveMisil o muevePersonaje
	for (int i=0; i<numFilas; i++)
		for (int j=0; j<numColumnas; j++)
		{
			objeto_t *objeto = &(tablero[i][j]);

			if (objeto->esta_activo)
			{
				switch (objeto->tipo)
				{
					case enemigo:
						mueveEnemigo(objeto, numFilas, numColumnas);
						break;

					case misil:
						mueveMisil(objeto, numFilas, numColumnas);
						break;

					case personaje:
						muevePersonaje(objeto, numFilas, numColumnas);
						break;

					case empty:
						break;
				}
			}
		}

	// Después de haber movido todos los objetos, actualizar sus posiciones dentro del tablero
	// Por cada objeto activo del tablero (recorrerlo con un for doble)
	// Obtener su nueva posición X,Y almacenada en el objeto
	// Comprobar si debe moverse (las nuevas posiciones son distintas de la posición actual)
	for (int i=0; i<numFilas; i++)
		for (int j=0; j<numColumnas; j++)
		{
			objeto_t *objeto = &(tablero[i][j]);
			objeto_t *objeto_siguiente = &(tablero[objeto->posicion.y][objeto->posicion.x]);

			if (objeto->posicion.x != j || objeto->posicion.y != i)
			{
				// Si se mueve
				// Comprobar si en esa nueva posición ya hay un objeto activo
				// Si es así, significa que hay una colisión, se resolverán de la siguiente manera
				// Si colisiona un Misil con un Enemigo, se desactivan ambos
				// Si colisiona un Misil con el Personaje, se desactivan ambos
				// En otro caso,(no hay objeto activo) se mueve el objeto a la nueva posición
				// Se copia el objeto a la posición X Y del tablero indicada por sus variables de posición
				// Se desactiva el objeto que estaba en la posición original (variable activo del objeto accedido con los contadores del “for” a false)
				if (objeto_siguiente->esta_activo)
				{
					switch (objeto->tipo)
					{
						case enemigo:
						case misil:
						case personaje:
							if ((objeto_siguiente->tipo == misil && objeto->tipo == enemigo) || (objeto_siguiente->tipo == enemigo && objeto->tipo == misil) || (objeto_siguiente->tipo == misil && objeto->tipo == personaje)) objeto->esta_activo = 0;
							break;

						case empty:
							break;
					}
				}

				*objeto_siguiente = *objeto;
				*objeto = CrearObjeto(empty, j, i);
			}
		}
}

void iniciaTablero(objeto_t **tablero, int numFilas, int numColumnas)
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
		}
		while(tablero[yEnemigo][xEnemigo].esta_activo);

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
		}
		while(tablero[yMisil][xMisil].esta_activo);

		pTablero = &(tablero[yMisil][xMisil]);
		*pTablero = CrearObjeto(misil, xMisil, yMisil);
	}

	//El  personaje principal está en la fila más inferior del tablero, en una columna aleatoria
	int xPersonaje = rand() % numColumnas,
		yPersonaje = numFilas - 1;

	pTablero = &(tablero[yPersonaje][xPersonaje]);
	*pTablero = CrearObjeto(personaje, xPersonaje, yPersonaje);
}

void dibujaTablero(objeto_t **tablero, int numFilas, int numColumnas)
{
	// Por cada fila,columna de tablero
	//		Si el objeto está activo
	//			Mostrar su sprite
	//		Si no
	//			Mostrar un espacio en blanco
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
			printf("%c", tablero[i][j].esta_activo ? tablero[i][j].sprite : ' ');
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

