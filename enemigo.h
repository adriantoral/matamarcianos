/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 03-05-2022 */

#ifndef __ENEMIGO_H__
#define __ENEMIGO_H__

#include "tipos.h"

t_enemigo CrearEnemigo();
void mueveEnemigo(t_objeto* objeto, int numFilas, int numColumnas);
t_enemigo CrearEnemigoConDatos(int vida, int puntuacion, t_movimiento *movimientos);

#endif

