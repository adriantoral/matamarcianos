/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 03-05-2022 */

#ifndef __MISIL_H__
#define __MISIL_H__

#include "tipos.h"

misil_t CrearMisil();
void mueveMisil(objeto_t* objeto, int numFilas, int numColumnas);
misil_t CrearMisilConDatos(int danio, direccion_e direccion);

#endif

