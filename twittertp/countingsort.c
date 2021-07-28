#include "data_pu.h"
#include "countingsort.h"

void countingsort_numero(data_t* pp, int n, int max, int min){
    int k = max - min;
    data_t resultado [n+1];
    int cont[k+1];
    int sum[k+1];

    for (int i=0; i < k+1; i++){
        cont[i] = 0;
        sum[i] = 0;
    }

    for(int i=0; i < n; i++ ){
        size_t pos = pp[i].cant - min;
        cont[pos] ++;
    }

    for(int i=0; i < k; i++){
        sum[i+1] = sum[i] + cont[i]; 
    }

    for(int i=0; i < n ; i++ ){
        size_t pos = pp[i].cant - min;
        size_t p = sum[pos];
        resultado[p] = pp[i];
        sum[pos]++;
    }

    for(int i=0; i<n;i++){
        pp[i] = resultado[i];
    }

}
