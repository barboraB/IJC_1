// bit_array.h
// Řešení IJC-DU1, příklad a), 27.3.2017
// Autor: Barbora Blašková, FIT
// Přeloženo: gcc 6.3.1
// Modul definuje makrá a inline funkcie pre prácu s bitovým poľom.

#ifndef BIT_ARRAY
#define BIT_ARRAY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "error.h"


typedef unsigned long bit_array_t;



//Nastavi pozadovany bit na indexe pozadovanou hodnotou. Makro maskuje hodnotu na prislusnom indexe v poli. Nekontroluje medze pola.
#define BA_SET_BIT(jmeno_pole, index, vyraz)\
	if((vyraz)==0){\
		jmeno_pole[((index) / (sizeof(jmeno_pole[0])*8))] = jmeno_pole[((index) / (sizeof(jmeno_pole[0])*8))] & (~(((long) 1) << ((index)%(sizeof(jmeno_pole[0])*8))));\
	} else {\
		jmeno_pole[((index) / (sizeof(jmeno_pole[0])*8))] = jmeno_pole[((index) / (sizeof(jmeno_pole[0])*8))] | (((long) 1) << ((index)%(sizeof(jmeno_pole[0])*8)));\
	}

//Vrati hodnotu bitu na pozadovanom indexe. Makro maskuje hodnotu na prislusnom indexe v poli aby zistil hodnotu bitu. Nekontroluje medze pola
#define BA_GET_BIT(jmeno_pole, index)\
	((jmeno_pole[((index)/(sizeof(jmeno_pole[0])*8))] & ((long) 1 << ((index)%(sizeof(jmeno_pole[0])*8)))) == 0 ? 0 : 1)

//Vytvori pole s nazvom jmeno_pole a velkostou. Ulozi velkost pola (pocet bitov v nom) do 0teho prvku tohoto pola a vynuluje cele pole.
#define ba_create(jmeno_pole, velkost)\
	bit_array_t jmeno_pole[((velkost)%(sizeof(long)*8) == 0) ? (((velkost) / (sizeof(long)*8))+1) : (((velkost) / ((sizeof(long)) * 8)) + 2)];\
	memset((jmeno_pole), 0, sizeof((jmeno_pole)));\
	jmeno_pole[0]=(velkost)


#ifdef USE_INLINE
	static inline bit_array_t ba_size(bit_array_t *jmeno_pole){
		return jmeno_pole[0];
	}

	static inline int ba_get_bit(bit_array_t *jmeno_pole, unsigned long index){
		return (((ba_size(jmeno_pole)-1) <index)) ? -1 : BA_GET_BIT(jmeno_pole, index+(sizeof(unsigned long)*8));
	}

	static inline void ba_set_bit(bit_array_t *jmeno_pole, unsigned long index, int vyraz){
		if(((ba_size(jmeno_pole)-1) < index)) {
				error_msg("Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)ba_size(jmeno_pole));
			}else{
				BA_SET_BIT(jmeno_pole, index+(sizeof(unsigned long)*8), vyraz)
			}
	}
#else
	//Vrati velkost bitoveho pola (pocet pozadovanych bitov v poli)
	#define ba_size(jmeno_pole)\
		jmeno_pole[0]

	//Vola makro BA_SET_BIT, aby nastavil prislusny bit na hodnotu. Na zaciatku skontroluje ci nie je index mimo alokovanej casti.
	#define ba_set_bit(jmeno_pole, index, vyraz)\
		if(((ba_size(jmeno_pole)-1) < (bit_array_t)(index))) {\
				error_msg("Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)ba_size(jmeno_pole));\
			}else{\
				BA_SET_BIT(jmeno_pole, index+(sizeof(unsigned long)*8), vyraz)\
			}

	//Vola makro BA_GET_BIT, ak je index mimo alokovaneho pola, vracia hodnotu -1	
	#define ba_get_bit(jmeno_pole, index)\
			(((ba_size(jmeno_pole)-1) < (bit_array_t)(index))) ? -1 : BA_GET_BIT(jmeno_pole, index+(sizeof(unsigned long)*8))	

#endif
#endif


