// ppm.c
// Řešení IJC-DU1, příklad b), 27.3.2017
// Autor: Barbora Blašková, FIT
// Přeloženo: gcc 6.3.1
// Obsahuje funkcie pre prácu s .ppm súborom
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "ppm.h"
#include "error.h"

/*
 * Nacita obrazok formatu .ppm do struktury. Format musi splnovat dopredu iste podmienky, inac funkcia vrati NULL
 * @param filename	nazov obrazku
 * @return ukazatel na strukturu v ktorej su ulozene vsetky data ak sa vsetko podarilo, inac NULL
 */

struct ppm * ppm_read(const char * filename){
	FILE *ppm;
	ppm = fopen(filename, "rb");
	if (ppm == NULL){
		error_msg("Nepodarilo sa otvorit subor %s\n", filename);
	}
	int c;
	if((c = fgetc(ppm)) != 'P') {
		warning_msg("Zly format obrazku\n");
		return NULL;
	}
	if((c = fgetc(ppm)) != '6'){
		warning_msg("Zly format obrazku\n");
		return NULL;
	}

	while(isspace(c = getc(ppm))){
		if(c == '\n') break;
		continue;
	}
	unsigned xsize;
	unsigned ysize;
	if(fscanf(ppm ,"%u %u", &xsize, &ysize) != 2){
		warning_msg("Zly format obrazku\n");
		return NULL;
	}

	while(isspace(c = fgetc(ppm))){
		if(c == '\n') break;
		continue;
	}

	if((c = fgetc(ppm)) != '2'){
		warning_msg("Zly format obrazku\n");
		return NULL;
	}
	if((c = fgetc(ppm)) != '5'){
		warning_msg("Zly format obrazku\n");
		return NULL;
	}
	if((c = fgetc(ppm)) != '5'){
		warning_msg("Zly format obrazku\n");
		return NULL;
	}
	if((c = fgetc(ppm)) != '\n'){
		warning_msg("Zly format obrazku\n");
		return NULL;
	}


	if(xsize > 1000 || ysize > 1000) {
		fclose(ppm);
		error_msg("Velkost obrazku je prilis velka\n");
	}
	struct ppm *picture = malloc(sizeof(struct ppm) + (xsize*ysize*3));
	picture->xsize = xsize;
	picture->ysize = ysize;

	for(unsigned i = 0; i < picture->xsize*picture->ysize*3; i++){
		c = fgetc(ppm);
		if(c == EOF) break;
		picture->data[i] = c;
	}

	fclose(ppm);
	return picture;

}
/*
 * Zapise do suboru data zo struktury 
   @param p 	struktura
   @param filename	nazov suboru pre zapis
   @return	0 ak sa vsetko podarilo, -1 ak nastala chyba
 */
int ppm_write(struct ppm *p, const char * filename){
	if (p == NULL || filename == NULL){
		warning_msg("Zle parametre funkcie.\n");
		return -1;
	}
	FILE *f;
	f = fopen(filename, "wb");
	if(fputs("P6 \n", f) == EOF){
		warning_msg("Napodarilo sa zapisat do suboru");
		return -1;
	}	
	fprintf(f, "%u %u\n", p->xsize, p->ysize);
	fprintf(f, "255\n");

	for(unsigned i = 0; i < p->xsize*p->ysize*3; i++){
		fputc(p->data[i], f);
	}
	fclose(f);
	return 0;
}