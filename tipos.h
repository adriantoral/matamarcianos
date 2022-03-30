#ifndef __TIPOS_H__
#define __TIPOS_H__

#define MOVIMIENTOS 4

//////////////////////////////////////////////////////////////////////
// Tipos enumerados.
//////////////////////////////////////////////////////////////////////
// Crear un tipo enumerado direccion_e, que se usará para indicar la dirección de los misiles

// Crear un tipo enumerado tipoObjeto_e, que se usará para indicar el tipo de objeto que 
// se usará en el juego. Hay tres tipos:
// enemigo, misil, personaje

typedef enum tipoObjeto_e
{
	enemigo,
	misil,
	personaje,
	empty
} tipoObjeto_e;

typedef enum direccion_e
{
	ascendente,
	descendente,
	quieto
} direccion_e;

//////////////////////////////////////////////////////////////////////
// Estructuras
//////////////////////////////////////////////////////////////////////

// Estructura "movimiento_t" usada por los enemigos, indica la dirección del siguiente movimiento


typedef struct movimiento_t
{
	int x; // Movimiento en el eje X
	int y; // Movimineto en el eje Y
} movimiento_t;


//////////////////////////////////////////////////////////////////////
// Estructura "enemigo_t" con los datos de los enemigos

typedef struct enemigo_t
{
	int vida; // Vida actual del enemigo (0-99)
	int puntuacion; // Puntuacion recibida por el usuario al matar al enemigo (0-1000)
	movimiento_t movimientos[MOVIMIENTOS]; // Array del movimiento
} enemigo_t;

//////////////////////////////////////////////////////////////////////
// Estructura misil_t con los datos de los misiles, y la dirección (tipo enumerado) a 
// la que se desplaza en cada turno

typedef struct misil_t
{
	int danio; // Danio causado por el misil (0-50)
	direccion_e direccion; // 0 - Ascendente ; 1 - Descendente ; 2 - Quieto
} misil_t;

//////////////////////////////////////////////////////////////////////
// Estructura personaje_t con los datos del personaje principal

typedef struct personaje_t
{
	int vida; // Vida actual del usuario (0-200)
	int puntuacion; // Puntuacion actual del usuario
} personaje_t;


//////////////////////////////////////////////////////////////////////
// Estructura de objeto genérico, puede ser cualquiera de los 3 anteriores. 
// Para ello se usará una variable enumerada "tipo", y tendrá las tres estructuras
// anteriores anidadas. Sólo habrá datos es la estructura indicada por la variable "tipo"

typedef struct objeto_t
{
	int x; // Posicion en el eje X del objecto
	int y; // Posicion en el eje Y del objecto
	int esta_activo; // 0 - Inactivo ; 1 - Activo
	tipoObjeto_e tipo; // 0 - Enemigo ; 1 - Misil ; 2 - Personaje principal ; 3 - Empty
	char sprite; // Sprite del objecto
	union
	{
		enemigo_t enemigo;
		misil_t misil;
		personaje_t personaje;
	};
} objeto_t;

#endif

