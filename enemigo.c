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

	for(int i=0; i<MOVIMIENTOS; i++)
	{
		enemigo.movimientos[i].x = 0;
		enemigo.movimientos[i].y = 0;
	}

	return enemigo;
}

