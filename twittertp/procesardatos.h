#include <stddef.h>
#include "strutil.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define CANT_F_HASH 4

//Devuelve el minimo del array que guarda los valores devueltos por las funciones de hash
size_t min_del_array(size_t* values);

//Devuelve el largo en digitos del numero pasado por parametro
int len_int(int numero);

//Devuelve el entero pasado por parametro convertido a char
char* to_string(int value);

//Rellena la palabra en caso de tener un largo menor a 15, para que pueda usarse en el radix sort
char* rellenar_palabra_con_15c(char* cadena);

//Devuelve un array de chars* donde cada posicion es ocupada por los elementos separados por coma de la entrada del programa
char** procesar_linea(char* linea, size_t cap);

//Devuelve una copia de la cadena pasada por parametro
char* copiarCadena(char* cad);
