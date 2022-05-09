/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 04-05-2022 */

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

typedef enum e_tipoObjeto
{
	ENEMIGO,
	MISIL,
	PERSONAJE,
	VACIO
} e_tipoObjeto;

typedef enum e_direccion
{
	ASCENDENTE,
	DESCENDENTE,
	PARADO
} e_direccion;

//////////////////////////////////////////////////////////////////////
// Estructuras
//////////////////////////////////////////////////////////////////////

// Estructura "movimiento_t" usada por los enemigos, indica la dirección del siguiente movimiento


typedef struct t_intVector2D
{
	int x; // Movimiento en el eje X
	int y; // Movimineto en el eje Y
} t_intVector2D, t_movimiento, t_posicion;


//////////////////////////////////////////////////////////////////////
// Estructura "enemigo_t" con los datos de los enemigos

typedef struct t_enemigo
{
	int vida; // Vida actual del enemigo (0-99)
	int puntuacion; // Puntuacion recibida por el usuario al matar al enemigo (0-1000)
	/* t_movimiento movimientos[MOVIMIENTOS]; // Array del movimiento (intVector2D_t [i]array{}) */
	t_movimiento *movimientos; // Array del movimiento (intVector2D_t [i]array{}) (version 3)
	int indice_movimiento; // Indice del array movimientos
	int tamanio_movimientos; // Tamanio del array movimientos
} t_enemigo;

//////////////////////////////////////////////////////////////////////
// Estructura misil_t con los datos de los misiles, y la dirección (tipo enumerado) a
// la que se desplaza en cada turno

typedef struct t_misil
{
	int danio; // Danio causado por el misil (0-50)
	e_direccion direccion; // 0 - Ascendente ; 1 - Descendente ; 2 - Parado
} t_misil;

//////////////////////////////////////////////////////////////////////
// Estructura personaje_t con los datos del personaje principal

typedef struct t_personaje
{
	int vida; // Vida actual del usuario (0-200)
	int puntuacion; // Puntuacion actual del usuario
} t_personaje;


//////////////////////////////////////////////////////////////////////
// Estructura de objeto genérico, puede ser cualquiera de los 3 anteriores.
// Para ello se usará una variable enumerada "tipo", y tendrá las tres estructuras
// anteriores anidadas. Sólo habrá datos es la estructura indicada por la variable "tipo"

typedef struct t_objeto
{
	t_posicion posicion; // Posicion del obecto X e Y (intVector2D_t)
	int esta_activo; // 0 - Inactivo ; 1 - Activo
	e_tipoObjeto tipo; // 0 - Enemigo ; 1 - Misil ; 2 - Personaje principal ; 3 - Vacio
	char sprite; // Sprite del objecto
	union
	{
		t_enemigo enemigo;
		t_misil misil;
		t_personaje personaje;
	};
} t_objeto;

#endif

