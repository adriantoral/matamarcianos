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
	}while(!error);

	return numero;
}
