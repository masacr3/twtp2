#include "strutil.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* funcion que cuenta la cantidad total del array de strings
 * len es la dimension del array
 * buffer la cantidad total de caracteres del array
 */ 
void strvlen ( char** s, size_t* len, size_t* buffer){
	*len = 0;
	*buffer = 0;	
	for(int i=0; s[i]; i++){
		*len += 1;
		*buffer += strlen(s[i]);
	}
}

/* devuelve la cantidad de bytes hasta el separador*/
size_t calcular_bytes(const char* s, char sep){
	size_t cont = 0;
	for(int i=0; s[i] && s[i] != sep; i++) cont++;
	return cont;
}

/* devuelve la cantidad de aparaciones del separador */
size_t contar_separadores(const char* s, char sep){
	size_t cont = 0;
	for(int i=0; s[i]; i++) if( s[i] == sep ) cont++;
	return cont;
}

char *substr(const char *str, size_t n){
	if(!str) return NULL;
	size_t largo = strlen(str);
	char* _substr = malloc(sizeof(char) * ( n >= largo ? largo + 1 : n + 1 ) );
	if(!_substr) return NULL;
	memcpy(_substr, &str[0], n >= largo ? largo : n );
	_substr[ n >= largo ? largo : n] = '\0';
	return _substr;
}

char **split(const char* str, char sep){
	if (!str) return NULL;
	size_t cant_sep = contar_separadores(str,sep);
	char** _split = (char**)malloc(sizeof(char*) * (cant_sep + 2) );
	if (!_split) return NULL;
	_split[ cant_sep + 1 ] = NULL;
	size_t inicio = 0;
	for (int i=0; i <= cant_sep; i++){
		size_t bytes = calcular_bytes(&str[inicio], sep);
		_split[i] = substr(str + inicio, bytes);
		inicio += bytes + 1;
	}
	return _split;
}

char* join (char** strv, char sep){
	if (!strv) return NULL;
	size_t len;
	size_t buffer;
	strvlen(strv, &len, &buffer);
	size_t bytes = buffer + ( sep == '\0' ? 0 : len);
	char* _join = malloc( sizeof(char) * (bytes + 1) );
	if( !_join) return NULL;
	_join[bytes] = '\0';
	if (!len) return _join;
	size_t largo = 0;
	for(int i=0; i<len-1; i++){
		strcpy(&_join[largo],strv[i]);
		largo += strlen(strv[i]);
		if (sep != '\0'){
			_join[largo] = sep;
			largo++;
		}
	}
	strcpy(&_join[largo], strv[len-1]);
	return _join;
}

void free_strv(char *strv[]){
    for (int i = 0; strv[i]; i++) {
        free(strv[i]);
    }
	free(strv);
}
