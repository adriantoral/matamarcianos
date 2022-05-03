/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 03-05-2022 */

#include "objetos.h"
#include "misil.h"
#include "personaje.h"
#include "enemigo.h"

////////////////////////////////////////////////////////////
// Aniadir la función para crear un objeto de un tipo dado. Inicializa sus valores "tipo",
// "sprite" y "posición" dependiendo del tipo indicado. La posición por defecto es "X=0" "Y=0"
//
// Por defecto, los objetos creados están activos (la variable "activo"=1)

t_objeto CrearObjeto(e_tipoObjeto tipo, int x, int y)
{
	t_objeto objeto;

	objeto.posicion.x = x;
	objeto.posicion.y = y;
	objeto.esta_activo = 1;
	objeto.tipo = tipo;

	if (tipo == ENEMIGO)
	{
		objeto.sprite = 'V';
		objeto.enemigo = CrearEnemigo();
	}
	else if (tipo == MISIL)
	{
		objeto.sprite = '|';
		objeto.misil = CrearMisil();
	}
	else if (tipo == PERSONAJE)
	{
		objeto.sprite = 'A';
		objeto.personaje = CrearPersonajePrincipal();
	}
	else if (tipo == VACIO)
	{
		objeto.sprite = ' ';
		objeto.esta_activo = 0;
	}

	return objeto;
}

