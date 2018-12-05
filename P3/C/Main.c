#include <stdio.h>
#include <glib.h>
//#include <stdbool.h>
//#include "Etc.h"
#include "Tabulation.h"
#include "Memoization.h"
GHashTable * map = NULL;

int main(void) {
    int array[] = {5,6,8,7,9,55,10};
    int size = sizeof(array)/sizeof(array[0]);
  	printf("[tabulation] Minimum number of multiplications is %d \n", Tabulation(array, size));

  	initMemoization(array, size);
  	printf("[memoization] Minimum number of multiplications is %d \n", MatrixChainOrder(1, size-1));
    g_hash_table_foreach(map, (GHFunc)iterator, "%s -> %d\n");
    clean();

    return 0;
}
