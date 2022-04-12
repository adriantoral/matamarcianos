#include "personaje.h"
#include "utils.h"
#include <stdio.h>


////////////////////////////////////////////////////////
// Aniadir función para crear un personaje con valores por defecto (todo a 0).

personaje_t CrearPersonajePrincipal()
{
	personaje_t personaje;

	personaje.vida = 0;
	personaje.puntuacion = 0; 

	return personaje;
}

void muevePersonaje(objeto_t* objeto, int numFilas, int numColumnas)
{
	//Pedir movimiento al usuario:
	int direccion = 0,
		x = objeto->posicion.x,
		y = objeto->posicion.y;
	char caracter_direccion = '\0';

	do
	{
		printf("[!] Mueva al personaje\n\tA) Izquierda\n\tD) Derecha\n\tS) Detener el juego\nOpcion:\n");
		caracter_direccion = leeCaracter();
	}while(caracter_direccion != 'a' && caracter_direccion != 'd' && caracter_direccion != 's');

	// Leer movimiento
	// Si se ha presionado “A”, mover una unidad a la derecha
	// Si se ha presionado “D”: mover una unidad a la izquierda
	// Si se ha presionado “S”: El personaje deja de estar activo
	direccion = caracter_direccion == 'a' ? -1 : caracter_direccion == 'd' ? 1 : 0;
	if (!direccion) objeto->esta_activo = 0;

	// Comprobar coordenadas correctas:
	// Si están fuera del número de Columas válidas del tablero, no se mueve
	if ((x + direccion) < numColumnas && (x + direccion) >= 0) objeto->posicion.x += direccion;
}

