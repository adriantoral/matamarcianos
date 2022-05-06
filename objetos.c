/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 05-05-2022 */

#include <string.h>
#include <stdlib.h>
#include "objetos.h"
#include "misil.h"
#include "personaje.h"
#include "enemigo.h"
#include "tipos.h"

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

t_objeto CrearObjetoConDatos(char *cadena)
{
	// Declaración de variables para cada tipo de dato
	int posX = 0,
		posY = 0,
		enemigo_vida = 0,
		enemigo_puntuacion = 0,
		nEnemigo_movimientos = 0,
		misil_danio = 0,
		personaje_vida = 0,
		personaje_puntuacion = 0,
		nParametros = 0;

	// Reserva de copia de cadena de entrada
	// copiar cadena, para poder usar strtok
	// la cadena debe empezar por la palabra "objeto" y acabar por "]". Si no, es un error
	// consumir final de objeto "]" (sustituir por '\0')
	char *cadena_cpy = NULL,
		 *cadena_aux = (char *)malloc(strlen(cadena) + 1),
		 *cadena_aux_p = NULL,
		 *datos_metadatos = NULL, // arg1=val1
		 **parametros = NULL, // ["arg1=val1", "arg2=val2"]
		 sprite = ' ';

	e_tipoObjeto tipo = VACIO;
	e_direccion misil_direccion = PARADO;
	t_movimiento *enemigo_movimientos = NULL;

	strcpy(cadena_aux, cadena); // objeto[posX=6,posY=9,sprite=A,tipo=personaje,vida=5,puntuacion=0,movimientos=x=1,y=1,x=2,y=2,x=3,y=3,x=4,y=4]

	// Si el primer token es la palabra “objeto”
	// iterar iniciando cada una de las variables posibles. Se acaba cuando "token" o "valor"
	// son null
	if (!strcmp(strtok(cadena_aux, "["), "objeto")) // posX=6,posY=9,sprite=A,tipo=personaje,vida=5,puntuacion=0,movimientos=x=1,y=1,x=2,y=2,x=3,y=3,x=4,y=4]
	{
		cadena_aux_p = strtok(NULL, "]"); // posX=6,posY=9,sprite=A,tipo=personaje,vida=5,puntuacion=0,movimientos=x=1,y=1,x=2,y=2,x=3,y=3,x=4,y=4
		cadena_cpy = (char *)realloc(cadena_cpy, strlen(cadena_aux_p) + 1); // posX=6,posY=9,sprite=A,tipo=personaje,vida=5,puntuacion=0,movimientos=x=1,y=1,x=2,y=2,x=3,y=3,x=4,y=4 (copia)
		strcpy(cadena_cpy, cadena_aux_p);

		datos_metadatos = strtok(cadena_cpy, ",");
		if (datos_metadatos)
		{
			parametros = (char **)realloc(parametros, sizeof(char *));
			parametros[nParametros++] = datos_metadatos;
		}

		while ((datos_metadatos = strtok(NULL, ",")))
		{
			if (datos_metadatos)
			{
				parametros = (char **)realloc(parametros, sizeof(char *) * (nParametros + 1));
				parametros[nParametros++] = datos_metadatos;
			}
		}

		for (int i=0; i<nParametros; i++)
		{
			char *datos = (char *)malloc(strlen(parametros[i]) + 1),
				 *dato = NULL,
				 *metadato = NULL;

			strcpy(datos, parametros[i]);

			dato = strtok(datos, "=");
			metadato = strtok(NULL, "=");

			// Leer el token (posX, posY, vida,puntuación,
			// tipo,direccion,danio,sprite,movimientos)
			// si token no es NULL
			// si no es un array movimientos (son especiales)
			// leer valor asignado
			// inicializar la variable adecuada en función del token leído (vida, posX, etc..)
			// si es un array movimientos
			// leer los cuatro movimientos y almacenarlos
			if (dato)
			{
				if (!strcmp(dato, "movimientos"))
				{
					dato = metadato;
					metadato = strtok(NULL, "=");
				}

				// Datos generales
				if		(!strcmp(dato, "posX")) posX = strtol(metadato, NULL, 10);
				else if (!strcmp(dato, "posY")) posY = strtol(metadato, NULL, 10);
				else if (!strcmp(dato, "sprite")) sprite = metadato[0];
				else if (!strcmp(dato, "tipo"))  tipo = dameTipo(metadato);

				// Datos del enemigo
				else if (!strcmp(dato, "vida") && tipo == ENEMIGO) enemigo_vida = strtol(metadato, NULL, 10);
				else if (!strcmp(dato, "puntuacion") && tipo == ENEMIGO) enemigo_puntuacion = strtol(metadato, NULL, 10);
				else if (!strcmp(dato, "x") && tipo == ENEMIGO)
				{
					// Si encuentra una x, reserva memoria para el movimiento del enemigo y guarda su valor
					// Si encuentra y, aumenta en uno en numero de movimientos y guarda su valor
					enemigo_movimientos = (t_movimiento *)realloc(enemigo_movimientos, sizeof(t_movimiento) * (nEnemigo_movimientos + 1));
					enemigo_movimientos[nEnemigo_movimientos].x = strtol(metadato, NULL, 10);
				}
				else if (!strcmp(dato, "y") && tipo == ENEMIGO)	enemigo_movimientos[nEnemigo_movimientos++].y = strtol(metadato, NULL, 10);

				// Datos del misil
				else if (!strcmp(dato, "direccion")) misil_direccion = dameDireccion(metadato);
				else if (!strcmp(dato, "danio")) misil_danio = strtol(metadato, NULL, 10);

				// Datos del personaje
				else if (!strcmp(dato, "vida") && tipo == PERSONAJE) personaje_vida = strtol(metadato, NULL, 10);
				else if (!strcmp(dato, "puntuacion") && tipo == PERSONAJE) personaje_puntuacion = strtol(metadato, NULL, 10);
			}

			free(datos);
		}
	}

	// Liberar datos
	free(parametros);
	free(cadena_aux);
	free(cadena_cpy);

	// Una vez leidas todas las variables de la cadena
	// Crear un objeto, iniciar posición, tipo, sprite, de objeto
	// en función del tipo del objeto, crear un objeto con sus datos de personaje,misil ó enemigo
	// usar crear[Personaje/Misil/Enemigo] con datos
	t_objeto objeto = CrearObjeto(tipo, posX, posY);
	objeto.esta_activo = 1;
	objeto.sprite = sprite;

	switch (tipo)
	{
		case ENEMIGO:
			objeto.enemigo = CrearEnemigoConDatos(enemigo_vida, enemigo_puntuacion, enemigo_movimientos);
			objeto.enemigo.tamanio_movimientos = nEnemigo_movimientos;
			break;

		case MISIL:
			objeto.misil = CrearMisilConDatos(misil_danio, misil_direccion);
			break;

		case PERSONAJE:
			objeto.personaje = CrearPersonajePrincipalConDatos(personaje_vida, personaje_puntuacion);
			break;

		case VACIO:
			break;
	}

	// Devolver el objeto
	return objeto;
}

e_tipoObjeto dameTipo(char *strTipo)
{
	e_tipoObjeto tipo;

	// Comparar la cadena “strTipo” con las palabras "misil","enemigo","personaje"
	// Devolver el tipo asociado
	// Si no es ninguno, devolver "4" (error)
	if (!strcmp(strTipo, "misil")) tipo = MISIL;
	else if (!strcmp(strTipo, "enemigo")) tipo = ENEMIGO;
	else if (!strcmp(strTipo, "personaje")) tipo = PERSONAJE;
	else tipo = VACIO;

	return tipo;
}

e_direccion dameDireccion(char *strDir)
{
	e_direccion direccion;

	// Comparar la cadena “strDir” con las palabras "ascendente","descendente"
	// Devolver el tipo ”direccion_e” asociado
	// Si no es ninguno, devolver "2" (error)
	if (!strcmp(strDir, "ascendente")) direccion = ASCENDENTE;
	else if (!strcmp(strDir, "descendente")) direccion = DESCENDENTE;
	else direccion = PARADO;

	return direccion;
}
