#include "cmk.h"
#include "data.h"
#include <stdlib.h>
#include "hash.h"

datos_t* crear_data(hash_t* h, cmk_t* cm, int* tam){
    if(!h) return NULL;
    hash_iter_t* it = hash_iter_crear(h);
    size_t largo = hash_cantidad(h);
    *tam = (int)largo;
    datos_t* data = malloc(sizeof(datos_t)*(largo+1));
    //como todas las posiciones son positivas, actua como null @masacr3
    data[largo].frecuencia = -1;
    data[largo].tag = NULL;
    for(int i=0; !hash_iter_al_final(it); i++ ){
        const char* clave = hash_iter_ver_actual(it);
        char* tag = hash_obtener(h,clave);
        size_t frecuencia = cmk_obtener(cm,tag);  
        data[i].frecuencia = frecuencia;
        data[i].tag = copiarCadena(tag);
        hash_iter_avanzar(it);
    }
    hash_iter_destruir(it);
    return data;
}

void destruir_datos(datos_t* datos){
    if (!datos) return; 

    for(int i=0; datos[i].tag; i++){
        free(datos[i].tag);
        
    }
    free(datos);
}
