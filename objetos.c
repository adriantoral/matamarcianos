#include "objetos.h"
#include "misil.h"
#include "personaje.h"
#include "enemigo.h"

////////////////////////////////////////////////////////////
// Aniadir la función para crear un objeto de un tipo dado. Inicializa sus valores "tipo",
// "sprite" y "posición" dependiendo del tipo indicado. La posición por defecto es "X=0" "Y=0"
//
// Por defecto, los objetos creados están activos (la variable "activo"=1) 

objeto_t CrearObjeto(tipoObjeto_e tipo)
{
	objeto_t objeto;

	objeto.posicion.x = 0;
	objeto.posicion.y = 0;
	objeto.esta_activo = 1;
	objeto.tipo = tipo;

	if (tipo == enemigo) 
	{
		objeto.sprite = 'V';
		objeto.enemigo = CrearEnemigo();
	}
	else if (tipo == misil) 
	{
		objeto.sprite = '|';
		objeto.misil = CrearMisil();
	}
	else if (tipo == personaje)
	{
		objeto.sprite = 'A';
		objeto.personaje = CrearPersonajePrincipal();
	}
	else if (tipo == empty)
	{
		objeto.sprite = ' ';
	}

	return objeto;
}
