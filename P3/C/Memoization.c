#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

char comma = ',';
char * buffer = NULL;
int i_len, j_len;
char i_str[12], j_str[12];
GHashTable * map;
int * matrix;

void iterator(gpointer key, gpointer value, gpointer user_data) {
  printf(user_data, key, GPOINTER_TO_INT(value));
}

int MatrixChainOrder (int i, int j) {
	int k;
	sprintf(i_str, "%d", i); // i_str=(char*) i
  	i_len = strlen(i_str); // i_len=nº de digitos en i

  	sprintf(j_str, "%d", j); // j_str=(char*) j
  	j_len = strlen(j_str); // j_len=nº de digitos en j

  	//* Comienzo creacion key *//
  	buffer = malloc((i_len + 1 + j_len + 1) * sizeof(char)); // Reservacion del espacio
  	if(buffer == NULL) exit(1);
  	snprintf(buffer, sizeof buffer, "%s%c%s", i_str, comma, j_str); // Concatenacion para crear la key
  	char * key = strdup(buffer); // Clonacion del contenido de buffer en key
  	free(buffer);
  	//* --------fin key------- *//

  	int value = GPOINTER_TO_INT(g_hash_table_lookup (map, key)); // value=map.getValue(key)
	if (value < INT_MAX) {
		return value;
	}

	for (k = i; k < j; k++) {
		int q = MatrixChainOrder(i,k) +
        	MatrixChainOrder(k+1,j) +
        	matrix[i-1]*matrix[k]*matrix[j];
    	value = GPOINTER_TO_INT(g_hash_table_lookup (map, key)); // value=map.getValue(key)
		if (q < value){
			g_hash_table_insert (map, key, GINT_TO_POINTER (q)); // map[key]=q
    	}

	}

	return GPOINTER_TO_INT(g_hash_table_lookup (map, key)); //return map[key]

}

void clean() {
	g_hash_table_destroy (map);
}

void initMemoization(int array[], int size) {
	int i, j;
  	matrix=array;
  	map=g_hash_table_new(g_str_hash, g_int_equal);// Creación mapa

	for (i = 1; i < size; i++) {
		sprintf(i_str, "%d", i); // i_str=(char*) i
		i_len = strlen(i_str); // i_len=nº de digitos en i

		for (j = i; j < size; j++  ) {
			sprintf(j_str, "%d", j); // j_str=(char*) j
			j_len = strlen(j_str); // j_len=nº de digitos en j

      		//* Comienzo creacion key *//
			buffer = malloc((i_len + 1 + j_len + 1) * sizeof(char)); // Reservacion del espacio
      		if(buffer == NULL) exit(1);
      		snprintf(buffer, sizeof buffer, "%s%c%s", i_str, comma, j_str); // Concatenacion para crear la key
      		//* -------fin key-------- *//

      	// Cuando i=j ? map[i,j]=0 : map[i,j]=INT_MAX
    	(i == j) ? g_hash_table_insert (map, strdup(buffer), GINT_TO_POINTER (0))
      : g_hash_table_insert (map, strdup(buffer), GINT_TO_POINTER (INT_MAX));

      free(buffer); // Liberacion espacio buffer
		}
	}
}
