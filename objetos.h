/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 03-05-2022 */

#ifndef __OBJETOS_H__
#define __OBJETOS_H__

#include "tipos.h"

t_objeto CrearObjeto(e_tipoObjeto tipo, int x=0, int y=0);
e_tipoObjeto dameTipo(char *strTipo);
e_direccion dameDireccion(char *strDir);
t_objeto CrearObjetoConDatos(char *cadena);

#endif

