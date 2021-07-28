#include "radixsort.h"
#include <stddef.h>
#define TOPE_CARACTERES 14
#define MAX_CARACTERES 255

void radixsort_palabras(char** usuarios){
    int n = 0;
    for(int i=0; usuarios[i]; i++) n++;
    for(int i=0; i<TOPE_CARACTERES+1; i++){
        countingsort_palabras(usuarios, n, TOPE_CARACTERES-i);
    }
}

void countingsort_palabras(char** listap, int n, int work){
    int k  = MAX_CARACTERES;
    int cont[k+1];
    int sum[k+1];
    char* nuevalista[n+1] ;

    for (int i=0; i < k+1; i++){
        cont[i] = 0;
        sum[i] = 0;
    }

    for(int i=0; i < n; i++ ){
        size_t pos = listap[i][work];
        cont[pos] ++;
    }

    for(int i=0; i < k; i++){
        sum[i+1] = sum[i] + cont[i]; 
    }

    for(int i=0; i < n ; i++ ){
        size_t pos = listap[i][work];
        size_t p = sum[pos];
        nuevalista[p] = listap[i];
        sum[pos]++;
    }
    
    for(int i=0; i<n;i++){
        listap[i] = nuevalista[i];
    }

}