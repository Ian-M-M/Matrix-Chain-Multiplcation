#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <limits.h> 
#include <glib.h>
#include <errno.h>
int i, j, k, L, q;
char comma[1] = ",";
char * key = NULL;
int value;
gpointer old_key = NULL;
gpointer old_value = NULL;
int realValue;
char * realKey = NULL;
char * keyString = NULL;
int ilen, jlen;
char i_str[12], j_str[12];
extern GHashTable * map;


int LOOKUPCHAIN (int array[], int i, int j) {
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
	key = strdup(keyString);
	free(keyString);
	// FIN HACER KEY

	if ( g_hash_table_lookup_extended (map, key, &old_key, &old_value)) {
		printf("hey");
	} 
	realValue = GPOINTER_TO_UINT(old_value);
	printf("%d valor , %s key\n", realValue, key);

	if (realValue < INT_MAX) return realValue;
	
	for (k = i; k < j-1; k++) {

		q = LOOKUPCHAIN(array,i,k) + LOOKUPCHAIN(array,k+1,j) + array[i-1]*array[k]*array[j];	
		if (q < realValue) g_hash_table_insert (map, key, GINT_TO_POINTER (q));
		printf("se ha insertado2 \n");
	
	}
	if ( g_hash_table_lookup_extended (map, key, &old_key, &old_value)) {
		realValue = GPOINTER_TO_INT(old_value);
	}
	return realValue;
}

void clean() {

	g_hash_table_destroy (map);
	map = NULL;
}


void initMemoization(int array[], int size) { 
	
	key = malloc(sizeof(*key));
	for (i = 1; i <= size; i++) {
		sprintf(i_str, "%d", i);
		ilen = strlen(i_str);
		for (j = i; j <= size; j++  ) {
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
			if (g_hash_table_lookup_extended (map, key, &old_key, &old_value)){
            	realValue = GPOINTER_TO_UINT(old_value);
        	} else {
				if (i == j) {
					g_hash_table_insert (map, key, GINT_TO_POINTER (0));
            	} else {
					g_hash_table_insert (map, key, GINT_TO_POINTER (INT_MAX));
				}
				
				if (g_hash_table_lookup_extended (map, key, &old_key, &old_value)) {
						realValue = GPOINTER_TO_UINT(old_value);
						char * realKey = (char*)old_key;
						printf( "%s => %d\n", realKey, realValue);
				}
			} 
		}
    }
}
