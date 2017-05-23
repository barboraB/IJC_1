// error.h
// Řešení IJC-DU1, příklad b), 27.3.2017
// Autor: Barbora Blašková, FIT
// Přeloženo: gcc 6.3.1
// Obsahuje 2 funkcie ktoré vypíšu chybovú hláśku na stderr.
#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void warning_msg(const char *fmt, ...);
void error_msg(const char *fmt, ...);

#endif