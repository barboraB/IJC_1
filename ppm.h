// ppm.h
// Řešení IJC-DU1, příklad b), 27.3.2017
// Autor: Barbora Blašková, FIT
// Přeloženo: gcc 6.3.1
// Obsahuje funkcie pre prácu s .ppm súborom
#ifndef PPM_H
#define PPM_H

#include <stdlib.h>
#include <stdio.h>


struct ppm {
        unsigned xsize;
        unsigned ysize;
        char data[];    // RGB bajty, celkem 3*xsize*ysize
     };

struct ppm * ppm_read(const char * filename);

int ppm_write(struct ppm *p, const char * filename);

#endif