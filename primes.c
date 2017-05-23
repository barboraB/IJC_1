// primes.c
// Řešení IJC-DU1, příklad a), 27.3.2017
// Autor: Barbora Blašková, FIT
// Přeloženo: gcc 6.3.1
// Obsahuje main, kde vola funkciu Eratosthenes(), aby nasla prvocisla v tu vytvorenom poli.
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bit_array.h"

void Eratosthenes(bit_array_t pole[]);

int main()
{
	unsigned long size = 303000000;
	ba_create(array, size);

	Eratosthenes(array);

	return 0;
}