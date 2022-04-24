/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 24-04-2022 */

#include "enemigo.h"

////////////////////////////
// Aniadir función para crear un enemigo con valores por defecto (todo a 0).

enemigo_t CrearEnemigo()
{
	enemigo_t enemigo;

	enemigo.vida = 0;
	enemigo.puntuacion = 0;
	enemigo.indice_movimiento = 0;
	enemigo.tamanio_movimientos = MOVIMIENTOS;

	int X[] = {1, 0, -1, 0},
		Y[] = {0, 1, 0, -1};

	for(int i=0; i<MOVIMIENTOS; i++)
	{
		enemigo.movimientos[i].x = X[i];
		enemigo.movimientos[i].y = Y[i];
	}

	return enemigo;
}

void mueveEnemigo(objeto_t* objeto, int numFilas, int numColumnas)
{
	// Obtener el índice del movimiento que se va a realizar, que está almacenado en la
	// Sumar a la posición del objeto la cantidad de movimiento en X Y indicada por el array
	int x = objeto->posicion.x + objeto->enemigo.movimientos[objeto->enemigo.indice_movimiento].x;
	int y = objeto->posicion.y + objeto->enemigo.movimientos[objeto->enemigo.indice_movimiento].y;

	// Comprobar si la nueva posición está dentro del tablero. Para ello, usar
	// Si alguna de las coordenadas no están dentro del tablero, el enemigo no se mueve en esa coordenada
	if (x < numColumnas && x >= 0) objeto->posicion.x = x;

	if (y < numFilas && y >= 0) objeto->posicion.y = y;

	// Actualizar índice de movimiento:
	// Sumar una unidad en el índice de movimiento
	// Si es mayor o igual que el tamaño del array de movimientos, vuelve a 0
	objeto->enemigo.indice_movimiento = ++objeto->enemigo.indice_movimiento >= objeto->enemigo.tamanio_movimientos ? 0 : objeto->enemigo.indice_movimiento;
}

