#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "strutil.h"
#include "funcioneshash.h"
#include "hash.h"
#include "lista.h"
#include "cmk.h"
#include "data.h"
#include "heap.h"
#include "topk.h"
#include "procesardatos.h"
#define INICIO_TAG 1
#define CANT_F_HASH 4
#define N 400000

void destruir_cmk(cmk_t* cm){
    free(cm->f1);
    free(cm->f2);
    free(cm->f3);
    free(cm->f4);
    free(cm);    
}

bool inicializar_vectores(cmk_t* cm, int n){
    int TAM = N/CANT_F_HASH;
    cm->f1= malloc(sizeof(int)*TAM);
    if(!cm->f1){
        free(cm);
        return false;
    }
    
    cm->f2= malloc(sizeof(int)*TAM);
    if(!cm->f2){
        free(cm->f1);
        free(cm);
        return false;
    }

    cm->f3= malloc(sizeof(int)*TAM);
    if(!cm->f3){
        free(cm->f1);
        free(cm->f2);
        free(cm);
        return false;
    }

    cm->f4= malloc(sizeof(int)*TAM);
    if(!cm->f4){
        free(cm->f1);
        free(cm->f2);
        free(cm->f3);
        free(cm);
        return false;
    }

    for(int i=0; i<TAM; i++){
        cm->f1[i] = 0;
        cm->f2[i] = 0;
        cm->f3[i] = 0;
        cm->f4[i] = 0;
    }
    return true;
}

cmk_t* cmk_crear(int n){
    cmk_t* cm = malloc(sizeof(cmk_t));
    if(!cm) return NULL;
    
    if( !inicializar_vectores(cm, n) ) return NULL;
    
    cm->n = n;
    return cm;
}

void cmk_agregar(cmk_t* cm, char* tag){
    size_t AMORTIZACION = N/CANT_F_HASH;
    size_t p1,p2,p3,p4;

    p1 = hashing1(tag) % AMORTIZACION;
    p2 = hashing2(tag) % AMORTIZACION;
    p3 = hashing3(tag) % AMORTIZACION;
    p4 = hashing4(tag) % AMORTIZACION;

    cm->f1[p1] += 1;
    cm->f1[p2] += 1;
    cm->f1[p3] += 1;
    cm->f1[p4] += 1;
}

size_t cmk_obtener(cmk_t* cm, char* tag){
    size_t TAM = N/CANT_F_HASH;
    size_t p1,p2,p3,p4;
    size_t r[4];

    p1 = hashing1(tag) % TAM;
    p2 = hashing2(tag) % TAM;
    p3 = hashing3(tag) % TAM;
    p4 = hashing4(tag) % TAM;

    r[0] = cm->f1[p1];
    r[1] = cm->f1[p2];
    r[2] = cm->f1[p3];
    r[3] = cm->f1[p4];

    return min_del_array(r);
}


void vaciar_hash(hash_t* h){
    if (!h) return;
    hash_iter_t *it = hash_iter_crear(h);
    if(it) return;
    while(!hash_iter_al_final(it)){
        const char* clave = hash_iter_ver_actual(it);
        char* tag = hash_borrar(h,clave);
        free(tag);
        hash_iter_avanzar(it);
    }
    hash_iter_destruir(it);
}

int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int tam_tt = 0;
    cmk_t* cm = cmk_crear(n);
    hash_t* visitados = hash_crear(free);

    //sentinela
    bool __ok = true; 
    
    size_t capacidad = 0;
	char *linea = NULL;
    int cont = 0;  
    int i = 1;

    while(__ok){
        __ok = getline( &linea, &capacidad, stdin ) > 0;
        //imprime topk      
        if(cont == n || !__ok){
              fprintf(stdout,"--- %d\n",i++);
              datos_t* tt = crear_data(visitados, cm, &tam_tt);
              top_k(tt, k, tam_tt);
              hash_destruir(visitados);
              visitados = hash_crear(free);
              destruir_datos(tt);
              cont = 0;
              tam_tt=0;
        }
        //procesa
        if(__ok){
              char** s = procesar_linea(linea, capacidad);
            for(int j =INICIO_TAG; s[j]; j++){
                char* tag = s[j];
                cmk_agregar(cm,tag);
                if(!hash_pertenece(visitados,tag)){
                    char* copytag= copiarCadena(tag);
                    hash_guardar(visitados,tag,copytag);
                }
            }
            free_strv(s);
            cont ++;
        }        
    }
    if (visitados) hash_destruir(visitados);
    free(linea);
    destruir_cmk(cm);
    return 0;

}
