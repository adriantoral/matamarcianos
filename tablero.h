#ifndef __TABLERO_H__
#define __TABLERO_H__

#define NFILAS 20
#define NCOLUMNAS 10

#include "tipos.h"

void iniciaTablero(objeto_t tablero[NFILAS][NCOLUMNAS], int numFilas, int numColumnas);
void dibujaTablero(objeto_t tablero[NFILAS][NCOLUMNAS], int numFilas, int numColumnas);

#endif

