#include <stdio.h>
#include <limits.h> 	//este no sé para cual, pero para parametros creo
#include <glib.h>
//#include <stdbool.h>
//#include "Etc.h"
#include "Tabulation.h"
#include "Memoization.h"
GHashTable * map = NULL;
int main(void) { 
    int array[] = {1, 2, 3, 4, 5, 6, 7}; 
    int size = sizeof(array)/sizeof(array[0]); 
	//printf("Minimum number of multiplications is %d \n", Tabulation(array, size)); 
	map = g_hash_table_new_full (g_direct_hash, g_direct_equal, NULL, NULL);
	initMemoization(array, size);
	
	printf(" MEMOIZATION - Minimum number of multiplications is %d \n", LOOKUPCHAIN (array, 1, size-1));
	
	//clean();
    return 0; 
} 
