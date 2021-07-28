#define _GNU_SOURCE
#include "calcular_t_usuario.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strutil.h"
#include "hash.h"
#include "lista.h"
#include "stdbool.h"
#define TAG_PERTENECE strcmp(taglista,tag)==0 

hash_t* swap_lista_por_array(hash_t* reverse);

/*  
    Hace un init de los hashes
*/
void inicializa_hashes(hash_t* usuarios, hash_t* tags, char* nombreUsuario);

/*
    agrega los tag al usuario y actualiza su contador
*/
void agregar_tag_y_actualizar_contador(hash_t* usuarios, char* nombreUsuarios, hash_t* lista, char* tag);

/*
    Recibe un hash de usuarios {usuario: cant} 
    #usuario -> string
    #cant -> number
    
    La funcion invierte el hash { cant : [usuario, ..., usuario]}
    #cant -> number
    #[usuario, ..., usuario] -> lista 

    post: Retorna un nuevo hash invertido
*/
hash_t* invertir_hash_clave_value(hash_t* usuarios, hash_t* reverse, int* cant_e);

/*
    Pasa una lista a un array de string copiando el contenido
    de la misma para eliminar referencias
    pre: recibe una lista
    post: devuelve un char** con contenido dinamico
*/
char** to_array_char(lista_t* lista);

/*
    Cambia el value = [lista] por un {char*,..., char*}
    post : devuelve un nuevo hash_t
*/
hash_t* swap_lista_por_array(hash_t* reverse);

//herramientas
char* rellenar_palabra_con_15c(char* cadena);

//(1****)
char* rellenar_palabra_con_15c(char* cadena){
    if(!cadena) return NULL;
    char* usuario = malloc( sizeof(char) * 16);
    if(!usuario) return NULL;
    int i=0;
    for(; cadena[i] && i<15; i++){
        usuario[i] = cadena[i];
    }
    for(; i<15; i++){
        usuario[i] = '\0';
    }
    usuario[15]='\0';

    return usuario;
}

void wrapper_destruir_lista(void* lista){
    lista_destruir(lista, free);
}

void wrapper_destruir_hash(void* hash){
    hash_destruir(hash);
}

void wrapper_destruir_strv(void* strv){
    free_strv(strv);
}


char** procesar_linea(char* linea_actual){
    if(linea_actual[strlen(linea_actual)-1] == '\n') linea_actual[strlen(linea_actual)-1] = '\0';
    char** s = split(linea_actual,',');
    return s;
}

int len_int(int numero){
    int pibote = 10;
    int len = 1;
    while ( pibote < numero ){
        pibote *= 10;
        len ++;
    }
    return len;
}

void mostrar_hash(hash_t* reverse){
    hash_iter_t* it = hash_iter_crear(reverse);
    while (! hash_iter_al_final(it)){
        const char* clave = hash_iter_ver_actual(it);
        char** lista = hash_obtener(reverse, clave);
        printf("%s : ",clave);
        for(int i=0; lista[i]; i++){
            char* usuario = lista[i];
            if ( (i!=0) && (i% 5 == 0)) printf("\n    ");
            printf("%s ", usuario);
        }
        printf("\n\n");
        hash_iter_avanzar(it);
    }
    hash_iter_destruir(it);
}


void inicializa_hashes(hash_t* usuarios, hash_t* tags, char* nombreUsuario){
    if (! hash_pertenece(usuarios, nombreUsuario) ){
        int* cant = malloc(sizeof(int));
        *cant = 0;
        hash_guardar(usuarios,nombreUsuario,cant);
        hash_t* h = hash_crear(NULL);
        hash_guardar(tags, nombreUsuario, h);
    }
}

void agregar_tag_y_actualizar_contador(hash_t* usuarios, char* nombreUsuarios, hash_t* visitados, char* tag){
    hash_guardar(visitados,tag,NULL);
    int* cant = hash_obtener(usuarios, nombreUsuarios);
    *cant += 1;
}

//(1*)
hash_t* invertir_hash_clave_value(hash_t* usuarios, hash_t* reverse, int* cant_e){
    hash_iter_t* it = hash_iter_crear(usuarios);
    while (! hash_iter_al_final(it)){
        const char* clave = hash_iter_ver_actual(it);
        int* cant = hash_obtener(usuarios, clave);
        char* value = malloc(sizeof(char)*strlen(clave)+1);
        strcpy(value, clave);
        char* nuevaClave = malloc(sizeof(char)*len_int(*cant)+1);
        sprintf(nuevaClave, "%d", *cant);
        
        if ( !hash_pertenece(reverse, nuevaClave) ){
            lista_t* lista = lista_crear();
            lista_insertar_ultimo(lista,value);
            hash_guardar(reverse,nuevaClave,lista);
            *cant_e += 1;
        }
        else{
            lista_t* lista = hash_obtener(reverse,nuevaClave);
            lista_insertar_ultimo(lista, value);
        }
        free(nuevaClave);
        hash_iter_avanzar(it);
    } 	
    hash_iter_destruir(it);
    hash_t* hashtag = swap_lista_por_array(reverse);

    return hashtag;
}

void agrego_tags(hash_t* tags, hash_t* usuarios, char* usuario, char** data){
    hash_t* visitados = hash_obtener(tags,usuario);

        for (int i= 1; data[i]; i++){
            char* tag = data[i];
            if (!hash_pertenece(visitados,tag)){ 
                agregar_tag_y_actualizar_contador(usuarios, usuario, visitados, tag);
            }
        }
}

//(1***)
char** to_array_char(lista_t* lista){
    size_t largo = lista_largo(lista);
    char** s = (char**)malloc(sizeof(char*) * (largo + 1));
    lista_iter_t* it = lista_iter_crear(lista);
    s[largo] = NULL;

    for(int i=0; !lista_iter_al_final(it); i++){
        char* cadena = lista_iter_ver_actual(it);
        char* nuevacadena = rellenar_palabra_con_15c(cadena);
        s[i]= nuevacadena;
        lista_iter_avanzar(it);
    }
    lista_iter_destruir(it);
    return s;
}

//(1**)
hash_t* swap_lista_por_array(hash_t* reverse){
    hash_iter_t* it = hash_iter_crear(reverse);
    hash_t* nuevo = hash_crear(NULL); 
    while(!hash_iter_al_final(it)){
        const char* clave = hash_iter_ver_actual(it);
        char* nuevaclave = malloc(sizeof(char)*strlen(clave)+1);
        strcpy(nuevaclave,clave);
        lista_t* lista = hash_obtener(reverse, clave);
        char** nuevalista = to_array_char(lista);
        hash_guardar(nuevo,nuevaclave,nuevalista);
        free(nuevaclave);
        hash_iter_avanzar(it);
    }
    hash_iter_destruir(it);
    return nuevo;
}

/******************************************************
 *             main que resuelve calcular t           *
 * ****************************************************/
hash_t* calcular_t_usuarios(char* archivo, int* cant_e){
    //procesado de archivo
    FILE* twitts = fopen(archivo, "r");
    size_t cap = 0;
	char *linea = NULL;
    
    //hash
    hash_t* usuarios = hash_crear(free);
    hash_t* tags = hash_crear(wrapper_destruir_hash);
    hash_t* reverse = hash_crear(wrapper_destruir_lista);

	while( getline ( &linea, &cap, twitts ) > 0 ){
        char** data = procesar_linea(linea);
        char* usuario = data[0];
        inicializa_hashes(usuarios, tags, usuario);
        agrego_tags(tags, usuarios, usuario, data);
        free_strv(data);
	}
    hash_t* hashtag = invertir_hash_clave_value(usuarios, reverse, cant_e);
    
    hash_destruir(tags);
    hash_destruir(usuarios);
    hash_destruir(reverse);
	free(linea);
    fclose(twitts);

    return hashtag;
}