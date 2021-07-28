#include "procesardatos.h"

size_t min_del_array(size_t* values){
    size_t pibote = values[0];
    for(int i=0; i<CANT_F_HASH ; i++){
        if (pibote < values[i]) pibote = values[i];    
    }
    return pibote;
}

int len_int(int numero){
    int pibote = 10;
    int len = 1;
    while ( pibote <= numero ){ 
        pibote *= 10;
        len ++;
    }
    return len;
}

char* to_string(int value){
    char *nuevaClave = malloc(sizeof(char)*(len_int(value)+1));
    if(!nuevaClave) return NULL;
    sprintf(nuevaClave, "%d", value);
    return nuevaClave;
}

char* rellenar_palabra_con_15c(char* cadena){
    if(!cadena) return NULL;
    
    char* usuario = malloc( sizeof(char) * 16);
    if(!usuario) return NULL;
    
    int i=0;
    for(; cadena[i] && i<15; i++) usuario[i] = cadena[i];
    
    for(; i<15; i++) usuario[i] = '\0';
    
    usuario[15]='\0';

    return usuario;
}

char** procesar_linea(char* linea, size_t cap){

    size_t len = strlen(linea);
    if(linea[len -1] == '\n') linea[len-1] = '\0';

    char** s = split(linea,',');
    if (!s) return NULL;

    return s;
}

char* copiarCadena(char* cad){
    size_t len = strlen(cad);
    char* nuevo = malloc(sizeof(char)*len+1);
    if (!nuevo) return NULL;

    strcpy(nuevo, cad);
    return nuevo;
}



