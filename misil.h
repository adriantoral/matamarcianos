/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 03-05-2022 */

#ifndef __MISIL_H__
#define __MISIL_H__

#include "tipos.h"

t_misil CrearMisil();
void mueveMisil(t_objeto* objeto, int numFilas, int numColumnas);
t_misil CrearMisilConDatos(int danio, e_direccion direccion);

#endif

