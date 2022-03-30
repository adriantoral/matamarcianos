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

