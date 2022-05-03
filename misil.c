/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 03-05-2022 */

#include "misil.h"

////////////////////////////////////////////////////////
// Aniadir la función para crear un misil con valores por defecto (todo a 0, dirección ascendente).

misil_t CrearMisil()
{
	misil_t misil;

	misil.danio = 0;
	misil.direccion = ascendente;

	return misil;
}

misil_t CrearMisilConDatos(int danio, direccion_e direccion)
{
	misil_t misil = CrearMisil();
	
	// Inicializar una estructura de tipo misil _t con los
	// datos de danio y puntuacion suministrados
	misil.danio = danio;
	misil.direccion = direccion;

	return misil;
}

void mueveMisil(objeto_t* objeto, int numFilas, int numColumnas)
{
	// Si la dirección del misil es ascendente:
	// Sumar 1 a la coordenada Y de su posición
	// Si no
	// Restar 1 a la coordenada Y de su posición
	int y = objeto->misil.direccion == ascendente ? objeto->posicion.y + 1 : objeto->posicion.y - 1;

	// Comprobar coordenadas nuevas
	// Si está fuera del número de Filas válidas del tablero, se desactiva
	if (y < numFilas && y >= 0) objeto->posicion.y = y;
	else objeto->esta_activo = 0;
}

