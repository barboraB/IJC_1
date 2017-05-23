// eratosthenes.c
// Řešení IJC-DU1, příklad a), 27.3.2017
// Autor: Barbora Blašková, FIT
// Přeloženo: gcc 6.3.1
// Obsahuje funkciu, ktorá nájde v poli bitov prvočíselné indexy. Ak číslo nie je prvočíslo, nastaví ho na 1, ináč ho nechá v 0. Vypíše 10 najväčších prvočisel
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bit_array.h"

void Eratosthenes(bit_array_t pole[]){

	unsigned long size = ba_size(pole);
	double ratio = sqrt(size);
	for (unsigned long i = 2; i < ratio; i++){
		if(!(ba_get_bit(pole, i))){
			for(unsigned long j = i*i; j < size; j += i){
				ba_set_bit(pole, j, 1);
			}
		}
	}

	int count = 0;
	unsigned long primes[10];

	for (unsigned long i = size; i > 0; i--){
		if(!(ba_get_bit(pole,i))){
			primes[count] = i;
			count++;
		}
		if (count == 10) break;
	}

	for (int i = 9; i >= 0; i-- ){
		printf("%lu\n", primes[i]);
	}
	
}