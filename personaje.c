#include "personaje.h"


////////////////////////////////////////////////////////
// Aniadir función para crear un personaje con valores por defecto (todo a 0).

personaje_t CrearPersonajePrincipal()
{
	personaje_t personaje;

	personaje.vida = 0;
	personaje.puntuacion = 0; 

	return personaje;
}
