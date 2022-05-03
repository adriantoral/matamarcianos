/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 03-05-2022 */

#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__

#include "tipos.h"

t_personaje CrearPersonajePrincipal();
void muevePersonaje(t_objeto* objeto, int numFilas, int numColumnas);
t_personaje CrearPersonajePrincipalConDatos(int vida, int puntuacion);

#endif

