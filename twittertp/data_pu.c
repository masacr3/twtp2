#include "data_pu.h"

data_t* crear_data(hash_t* usuarios, int cant_elem_hash, int* min, int* max){
    data_t* datos = malloc(sizeof(data_t)*(cant_elem_hash));
    
    if(!datos){
        printf("error");
        return NULL;
    }
    
    hash_iter_t* it = hash_iter_crear(usuarios);
    for(int i=0; !hash_iter_al_final(it); i++){
        const char* clave = hash_iter_ver_actual(it);
        int cant_tag = atoi(clave);
        if (cant_tag < *min ) *min = cant_tag;
        if (cant_tag > *max ) *max = cant_tag;
        datos[i].cant = cant_tag;
        datos[i].lista_nombres = hash_obtener(usuarios, clave);
        //aplico radix
        radixsort_palabras(datos[i].lista_nombres);
        
        hash_iter_avanzar(it);
    }
    hash_iter_destruir(it);
    return datos;
}

void destruir_data(data_t* datos, int n){
    for(int i=0; i<n; i++){
        char** strv = datos[i].lista_nombres;
        for(int j=0; strv[j]; j++) free(strv[j]);
        free(strv);
    }
    free(datos);
}
