#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <limits.h> 
#include <glib.h>
#include <errno.h>
#include "Memoization.h"
int i, j, k, L, q;
char comma[1] = ",";
char * key = NULL;
char * key2 = NULL;
char * keyinicial = NULL;
int value;
gpointer old_key = NULL;
gpointer old_value = NULL;
int realValue;
char * realKey = NULL;
char * keyString = NULL;
int ilen, jlen;
char i_str[12], j_str[12];
extern GHashTable * map;
int m ;
int contador = 0;

void printKeyValue( gpointer key, gpointer value, gpointer userData ) {
	char* realKey = (char*)key;
	int realValue = GPOINTER_TO_INT( value );
   	printf( "%s => %d\n", realKey, realValue );
}

void mi_strcpy (char* s1, char* s2, int pos){
  	char* ptr = &s1[pos];	// Apunta a al puntero de chars en la posicion
							// pos
  	char* ptr2 = s2;		// Puntero al puntero de chars 
							// donde se guardara la copia
  	while (*ptr2 != '\0') {	// Mientras hayan datos
      	*ptr = *ptr2;		// realiza la copia
      	ptr++;				// Se avanza los punteros
     	ptr2++;	
  	}
  	*ptr = '\0';	// Añadimos el caracter nulo 
}

int MatrixChainOrder (int array[], int i, int j) {

	// HACER KEY
	sprintf(i_str, "%d", i);
	ilen = strlen(i_str);
	sprintf(j_str, "%d", j);
	jlen = strlen(j_str);
	keyString = malloc((ilen + 1 + jlen + 1) * sizeof(char));

	if (keyString == NULL) { 
		fprintf(stderr, " %s\n", strerror(errno));
		exit(1);
	}

	strcpy(keyString, i_str);
	keyString[ilen] = comma[0];
	keyString[ilen + 1 ] = '\0';
	strcat(keyString,j_str);

	/*if (contador == 0) {
		mi_strcpy (key2, keyString, 0);
		contador++;
	}*/
	//printf(" %s key\n",key2);
	key = strdup(keyString);
	free(keyString);
	// FIN HACER KEY

	if ( ! g_hash_table_lookup_extended (map, key, NULL, &old_value)) {
		fprintf(stderr, " [!] ERROR. Fallo al buscar una clave que debe de estar\n");
	}
	realValue = GPOINTER_TO_INT(old_value);
	//printf("%d valor , %s key\n", realValue, key);

	if (realValue < INT_MAX) {
		return realValue;
	}

	m = INT_MAX;
	for (k = i; k < j; k++) {
		q = MatrixChainOrder(array,i,k) + MatrixChainOrder(array,k+1,j) + array[i-1]*array[k]*array[j];	

		if (q < m) {
			m = q;
			g_hash_table_replace (map, key , GINT_TO_POINTER (q));
			
		}
		
	}
	if ( g_hash_table_lookup_extended (map, key, NULL, &old_value)) {
		m = GPOINTER_TO_INT(old_value);
		g_hash_table_foreach( map, printKeyValue, NULL );
	
	}
	
	return m;
	
}

/*void clean() {
	g_hash_table_destroy (map);
}*/

void initMemoization(int array[], int size) { 
	key = malloc(sizeof(*key));

	for (i = 1; i < size; i++) {
		sprintf(i_str, "%d", i);
		ilen = strlen(i_str);
		for (j = i; j < size; j++  ) {
			sprintf(j_str, "%d", j);
			jlen = strlen(j_str);
			keyString = malloc((ilen + 1 + jlen + 1) * sizeof(char));

			if(keyString == NULL) { 
				fprintf(stderr, " %s\n", strerror(errno));
				exit(1);
			}

			strcpy(keyString, i_str);
			keyString[ilen] = comma[0];
			keyString[ilen + 1 ] = '\0';
			strcat(keyString,j_str);
			key = strdup(keyString);
			free(keyString);   
			// FIN HACER KEY
			
			if ( ! g_hash_table_lookup_extended (map, key, &old_key, &old_value)){
            	if (i == j) {
					g_hash_table_insert (map, key, GINT_TO_POINTER (0));
            	} else {
					g_hash_table_insert (map, key, GINT_TO_POINTER (INT_MAX));
				}
        	} 
		}
    }
}
