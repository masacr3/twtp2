
#ifndef CMK_H
#define CMK_H

struct count_mk;

typedef struct count_mk cmk_t;

struct count_mk{
    int* f1;
    int* f2;
    int* f3;
    int* f4;
    int n;
};

#include <stdlib.h>
#include "lista.h"

#include "data.h"

cmk_t* cmk_crear(int n); 

void destruir_cmk(cmk_t* cm);

void cmk_agregar(cmk_t* cm, char* tag);

size_t cmk_obtener(cmk_t* cm, char* tag);

datos_t* count_min_sketch(cmk_t* cm, int n, bool* seguir, int* tam_datos);

#endif
