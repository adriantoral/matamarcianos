/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 04-05-2022 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "tablero.h"
#include "enemigo.h"
#include "misil.h"
#include "objetos.h"
#include "personaje.h"
#include "tipos.h"

void iniciaTableroConDatos(t_objeto **tablero, int numFilas, int numColumnas, int numObjetos, char **datos)
{
	// Inicializar el tablero con objetos "no activos"
	// por cada número de cadenas del array datos
	// iniciar un objeto con datos (llamar a la función “crearObjetoConDatos” pasándole una cadena
	// del array “datos”)
	// colocarlo en la posición del tablero indicada por su “posX/Y”
	// antes de colocarlo, comprobar si las posiciones están dentro del tablero
	// si no están, se avisa al usuario

	t_objeto *pTablero = NULL;

	for (int i=0; i<numFilas; i++)
		for (int j=0; j<numColumnas; j++)
		{
			pTablero = &(tablero[i][j]);
			*pTablero = CrearObjeto(VACIO, j, i);
		}

	for (int i=1; i<numObjetos; i++)
	{
		t_objeto objeto = CrearObjetoConDatos(datos[i]);
		tablero[objeto.posicion.y][objeto.posicion.x] = objeto;
	}
}

int buscaPersonaje(t_objeto **tablero, int numFilas, int numColumnas)
{
	for (int i=0; i<numFilas; i++)
		for (int j=0; j<numColumnas; j++)
		{
			t_objeto *objeto = &(tablero[i][j]);
			if (objeto->esta_activo && objeto->tipo == PERSONAJE) return 1;
		}

	return 0;
}

void liberaTablero(t_objeto **tablero, int numFilas, int numColumnas)
{
	for (int i=0; i<numFilas; i++)
	{
		for (int j=0; j<numColumnas; j++)
			if (tablero[i][j].tipo == ENEMIGO)
				free(tablero[i][j].enemigo.movimientos);

		free(tablero[i]);
	}
	free(tablero);
}

t_objeto **reservaTablero(int numFilas, int numColumnas)
{
	// Declarar un puntero doble de objeto_t llamado tablero
	t_objeto **tablero = NULL;

	// Iniciar la primera dimensión del puntero doble “tablero” con un array de numFilas de punteros a objeto_t
	tablero = (t_objeto **)malloc(sizeof(t_objeto *) * numFilas);

	// Inicializar esa fila del tablero con un array de objeto_t de tamaño “numColumnas"
	for (int i=0; i<numFilas; i++) tablero[i] = (t_objeto *)malloc(sizeof(t_objeto) * numColumnas);

	//devolver el array doble tablero
	return tablero;
}

void actualizaTablero(t_objeto **tablero, int numFilas, int numColumnas)
{
	// Por cada posición del tablero
	// Si es un objeto activo
	// Obtener el tipo del objeto
	// Llamar a su función de movimiento: mueveEnemigo, mueveMisil o muevePersonaje
	for (int i=0; i<numFilas; i++)
		for (int j=0; j<numColumnas; j++)
		{
			t_objeto *objeto = &(tablero[i][j]);

			if (objeto->esta_activo)
			{
				switch (objeto->tipo)
				{
					case ENEMIGO:
						mueveEnemigo(objeto, numFilas, numColumnas);
						break;

					case MISIL:
						mueveMisil(objeto, numFilas, numColumnas);
						break;

					case PERSONAJE:
						muevePersonaje(objeto, numFilas, numColumnas);
						break;

					case VACIO:
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
			t_objeto *objeto = &(tablero[i][j]);
			t_objeto *objeto_siguiente = &(tablero[objeto->posicion.y][objeto->posicion.x]);

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
					if ((objeto_siguiente->tipo == MISIL && objeto->tipo == ENEMIGO) || (objeto_siguiente->tipo == ENEMIGO && objeto->tipo == MISIL) || (objeto_siguiente->tipo == MISIL && objeto->tipo == PERSONAJE) || (objeto_siguiente->tipo == ENEMIGO && objeto->tipo == ENEMIGO))
					{
						if (objeto_siguiente->tipo == ENEMIGO) free(objeto_siguiente->enemigo.movimientos);
						objeto->esta_activo = 0;
					}
				}

				*objeto_siguiente = *objeto;
				*objeto = CrearObjeto(VACIO, j, i);
			}
		}
}

void iniciaTablero(t_objeto **tablero, int numFilas, int numColumnas)
{
	// Iniciar el random
	srand(getpid());

	// Variables AUX
	t_objeto *pTablero = NULL;

	int nEnemigos = (rand() % 3) + 1, // 1-3
		nMisiles  = (rand() % 4) + 2; // 2-5

	/* Debug de numero de enemigos y misiles */
	/* printf("Enemigos : %d\nMisiles : %d\n", nEnemigos, nMisiles); */

	// Inicializar el tablero con objetos "no activos"
	for (int i=0; i<numFilas; i++)
		for (int j=0; j<numColumnas; j++)
		{
			pTablero = &(tablero[i][j]);
			*pTablero = CrearObjeto(VACIO, j, i);
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
		*pTablero = CrearObjeto(ENEMIGO, xEnemigo, yEnemigo);
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
			xMisil = rand() % numColumnas;
			yMisil = rand() % numFilas;
		}
		while(tablero[yMisil][xMisil].esta_activo);

		pTablero = &(tablero[yMisil][xMisil]);
		*pTablero = CrearObjeto(MISIL, xMisil, yMisil);
	}

	//El  personaje principal está en la fila más inferior del tablero, en una columna aleatoria
	int xPersonaje = rand() % numColumnas,
		yPersonaje = numFilas - 1;

	pTablero = &(tablero[yPersonaje][xPersonaje]);
	*pTablero = CrearObjeto(PERSONAJE, xPersonaje, yPersonaje);
}

void dibujaTablero(t_objeto **tablero, int numFilas, int numColumnas)
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

