#include "heap.h"
#include "cmk.h"
#include <string.h>
#define COMPARAR_TAG strcmp( data1->tag, data2->tag) * (-1)

int cmp_heap(const void* a, const void* b){
    const datos_t* data1 = a;
    const datos_t* data2 = b;

    if (data1->frecuencia < data2->frecuencia) return -1;
    if (data1->frecuencia > data2->frecuencia) return 1;

    return COMPARAR_TAG; 
}

void top_k(datos_t* d, int k, int tam_datos){
    if (!d) return ;
    size_t tam = tam_datos;
    void* arr[tam];
    for(int i=0; i<tam; i++) arr[i] = d+i;
    
    heap_t* h = heap_crear_arr(arr,tam,cmp_heap);
    int imprimir = 0;
    while (!heap_esta_vacio(h) && imprimir++ < k){
        datos_t* tt = heap_desencolar(h);
        size_t frecuencia = tt->frecuencia;
        char* tag = tt->tag;
        fprintf(stdout,"%ld %s\n",frecuencia,tag);
    }
    heap_destruir(h, NULL);
}
