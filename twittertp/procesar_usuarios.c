#include <stdio.h>
#include <stdlib.h>
#include "data_pu.h"
#include "radixsort.h"
#include "countingsort.h"
#include "hash.h"
#include "lista.h"
#include "calcular_t_usuario.h"

void print_usuarios(data_t* usuarios, int n){
    for(int i=0; i<n; i++){
        fprintf(stdout,"%d:",usuarios[i].cant);
        char** lista_usuarios = usuarios[i].lista_nombres;
        for(int j=0; lista_usuarios[j]; j++){
            fprintf(stdout," %s", lista_usuarios[j]);
            if(lista_usuarios[j+1]){
                fprintf(stdout,",");
            }
        }
        printf("\n");
    }
}

void procesar_usuarios(char* archivo){
    int cant = 0;
    hash_t* usuarios_formateados = calcular_t_usuarios(archivo, &cant);
    int max = 0;
    int min = 0;
    data_t* usuarios = crear_data(usuarios_formateados,cant,&min,&max); //aplica radix a la lista de nombres
    countingsort_numero(usuarios,cant, max, min);
    print_usuarios(usuarios, cant);
    //elimina estructuras
    hash_destruir(usuarios_formateados);
    destruir_data(usuarios, cant);
}

int main(int argc, char* argv[]){
    char* archivo = argv[1];
    procesar_usuarios(archivo);
    return 0;
}

