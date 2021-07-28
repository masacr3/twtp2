#ifndef DATA_H
#define DATA_H

struct datos;

typedef struct datos datos_t;

struct datos
{
    size_t frecuencia;
    char* tag;
};

#include "cmk.h"
#include "hash.h"
#include "procesardatos.h"

//Crea el tipo de dato "datos_t"
datos_t* crear_data(hash_t* h, cmk_t* cm, int* tam);

//Destruye el tipo de dato "datos_t"
void destruir_datos(datos_t* data);

#endif
