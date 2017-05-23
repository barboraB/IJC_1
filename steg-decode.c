// steg-decode.c
// Řešení IJC-DU1, příklad b), 27.3.2017
// Autor: Barbora Blašková, FIT
// Přeloženo: gcc 6.3.1
// Nacita obrazok do struktury a vypise tajnu spravu.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "ppm.h"
#include "bit_array.h"
#include "error.h"

int main(int argc, char const *argv[])
{

	if(argc > 2 || argc == 1) error_msg("Zly pocet argumentov.\n");
	
	struct ppm *picture;
	if((picture = ppm_read(argv[1])) == NULL){
		return 1;
	}

	ba_create(indexes, ((picture->xsize)*(picture->ysize)*3));

	unsigned long size = ba_size(indexes);
	double ratio = sqrt(size);

	for (unsigned long i = 2; i < ratio; i++){
		if(!(ba_get_bit(indexes, i))){
			for(unsigned long j = i*i; j < size; j += i){
				ba_set_bit(indexes, j, 1);
			}
		}
	}

	ba_create(bits, ba_size(indexes));
	unsigned int count = 0;
	for (unsigned int i = 2; i < ba_size(indexes); i++){
		if(!(ba_get_bit(indexes, i))){
			ba_set_bit(bits, count, (picture->data[i] & (unsigned char) 1));
			count++;
		}
	}
	char *msg = (char *) (bits+1);
	unsigned int len = strlen(msg);
	if(msg[len] != '\0'){
		free(picture);
		error_msg("Zprava nie je korektne ukoncena.\n");
	}
	ppm_write(picture, "skuska.ppm");
	printf("%s\n", msg);

	free(picture);

	return 0;
}