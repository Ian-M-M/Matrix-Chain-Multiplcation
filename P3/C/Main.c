#include <stdio.h>
#include <limits.h> 	
#include <glib.h>
//#include <stdbool.h>
//#include "Etc.h"
#include "Tabulation.h"
#include "Memoization.h"
GHashTable * map = NULL;
int main(void) { 
    int array[] = {10,20,30}; 
    int size = sizeof(array)/sizeof(array[0]); 
	//printf("Minimum number of multiplications is %d \n", Tabulation(array, size)); 
	map = g_hash_table_new_full (g_str_hash, g_int_equal, g_free, g_free);
	initMemoization(array, size);
	
	printf("Minimum number of multiplications is %d \n", MatrixChainOrder(array, 1, size-1));
	
	//clean();
    return 0; 
} 
