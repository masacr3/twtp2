#ifndef DATA_PU_H
#define DATA_PU_H

struct data;

typedef struct data data_t;

struct data{
    int cant;
    char** lista_nombres;
};

#include "hash.h"
#include "lista.h"
#include "radixsort.h"

data_t* crear_data(hash_t* usuarios, int cant_elem_hash, int* min, int* max);
void destruir_data(data_t* datos,int n);

#endif