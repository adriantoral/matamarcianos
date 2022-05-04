/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 04-05-2022 */

#ifndef __TABLERO_H__
#define __TABLERO_H__

#define NFILAS 20
#define NCOLUMNAS 10

#include "tipos.h"

void iniciaTablero(t_objeto **tablero, int numFilas, int numColumnas);
void iniciaTableroConDatos(t_objeto **tablero, int numFilas, int numColumnas, int numObjetos, char **datos);
void dibujaTablero(t_objeto **tablero, int numFilas, int numColumnas);
t_objeto **reservaTablero(int numFilas, int numColumnas);
void liberaTablero(t_objeto **tablero, int numFilas, int numColumnas);
void actualizaTablero(t_objeto **tablero, int numFilas, int numColumnas);
int buscaPersonaje(t_objeto **tablero, int numFilas, int numColumnas); // Devuleve 1 si encuentra al personaje 0 sino

#endif

