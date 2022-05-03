/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 03-05-2022 */

#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__

#include "tipos.h"

personaje_t CrearPersonajePrincipal();
void muevePersonaje(objeto_t* objeto, int numFilas, int numColumnas);
personaje_t CrearPersonajePrincipalConDatos(int vida, int puntuacion);

#endif

