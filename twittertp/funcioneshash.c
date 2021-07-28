#include <stdbool.h>
#include <stdint.h>
#include <string.h>

size_t hashing1(const char* cp){
    unsigned int hash = 5381;
    int c;

    while ((c = *cp++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

size_t hashing2(const char* key){
    uint32_t hash = 0;
    for(int i = 0; key[i]; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    
    return hash < 0 ? hash * -1 : hash;
}

size_t hashing3(const char* s){
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31*hashval;
    
    return hashval;
}

size_t hashing4(const char* cp){
    unsigned long int int_max = 4294967296; // pow(2, 32)
    unsigned long int prime = 16777619;
	unsigned long int val = 2166136261;
	
	for (int i = 0; cp[i]; i++)
	{
	    val = val ^ cp[i];
	    val = (val * prime) % int_max;
	}
	return val;
}
