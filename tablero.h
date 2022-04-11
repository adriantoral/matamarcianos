#ifndef __TABLERO_H__
#define __TABLERO_H__

#define NFILAS 20
#define NCOLUMNAS 10

#include "tipos.h"

void iniciaTablero(objeto_t **tablero, int numFilas, int numColumnas);
void dibujaTablero(objeto_t **tablero, int numFilas, int numColumnas);
objeto_t **reservaTablero(int numFilas, int numColumnas);
void liberaTablero(objeto_t **tablero, int numFilas);

#endif

