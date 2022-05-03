/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 03-05-2022 */

#ifndef __ENEMIGO_H__
#define __ENEMIGO_H__

#include "tipos.h"

enemigo_t CrearEnemigo();
void mueveEnemigo(objeto_t* objeto, int numFilas, int numColumnas);
enemigo_t CrearEnemigoConDatos(int vida, int puntuacion, movimiento_t *movimientos);

#endif

