/* Author : Adrian Toral */
/* Codigo : Matamarcianos en c */
/* Fecha  : 24-04-2022 */

#include <stdio.h>
#include "utils.h"

int leeNumero()
{
	int numero = 0,
		error = 0;

	do
	{
		error = scanf("%d", &numero);
		limpiarBuffer;
		if (!error) printf("[!] Numero no valido. Prueba de nuevo\n");
	}
	while(!error);

	return numero;
}

char leeCaracter()
{
	char caracter = '\0';

	caracter = getchar();
	limpiarBuffer;

	return caracter;
}

