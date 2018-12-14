#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <stdbool.h>
#include "Etc.h"
#include "Tabulation.h"
#include "Memoization.h"

GHashTable * map = NULL;
bool flagDi = false;
bool flagDo = false;
bool flagF = false;
bool flagT = false;
bool flagMem = false;
bool flagTab = false;

int main(int argc, char * argv[]) {

	char path[500]="";	// dirección del fichero
	int size;	// Num de elementos
	double timer_tabulation;
	double timer_memoization;

	// Se leen los parámetros pasados al programa
	GetParam(argc, argv, &flagDi, &flagDo, &flagF, &flagT, &flagMem, &flagTab, path);
	int min_operaciones_Tab;
	int min_operaciones_Mem;
	if (flagDi) Input();

	if (!flagDi && !flagDo && !flagT) {
		printf("[!] ERROR. --do || --di || -t requerido\n");
		exit(1);
	}
	if ((!flagT || !flagDo) && !flagTab && !flagMem && !flagDi) {
		printf("[!] ERROR. --tab  || --mem requerido\n");
		exit(1);
	}
	if (flagDo || flagT){

		FILE *fichero = fopen(path, "r");	// Se abre el fichero
		if (fichero != NULL) {
			char linea[50000];	// String que contendrá cada línea del fichero

			while (fgets(linea, sizeof linea, fichero ) != NULL) {

				size = getSizeArray(linea);		// Obtenemos el número de elementos

				if (size < 3) {
					printf(" Aviso: Array no válido. Mínimo 3 elementos \n");
					continue;
				}
				printf("Size => %d\n", (size-1));
				int array[size];
				split(linea, array, size);	// Se crea el array con los elementos

				if (flagTab) {
					if (flagT) ComienzaTimer();
					min_operaciones_Tab = Tabulation(array, size);	// Cáculo de la op min
					if (flagT) timer_tabulation = FinTimer();
				}

				if (flagMem) {
					if (flagT) ComienzaTimer();
					initMemoization(array, size);	// Inicio del hashmap de resultados
					min_operaciones_Mem = MatrixChainOrder(1, size-1);	// Cáculo de la op min
					if (flagT) timer_memoization = FinTimer();
					// g_hash_table_foreach(map, (GHFunc)iterator, "%s -> %d\n");
					clean();	// Destrucción del hashmap creado
				}

				if (flagDo) {
					if (flagTab) printf("[Tabulation] Operaciones mínimas => %d\n", min_operaciones_Tab);
					if (flagMem) printf("[Memoization] Operaciones mínimas => %d\n", min_operaciones_Mem);
				}

				if (flagT) {
					if (flagTab) printf("[Tabulation] Tiempo => %fs \n", timer_tabulation);
					if (flagMem) printf("[Memoization] Tiempo => %fs \n", timer_memoization);
					if ((timer_tabulation > 120.0) || (timer_memoization> 120.0)){

						printf("Max time\n");
						return 0;
					}
				}
				if (flagDo || flagT)printf("-------------------------------------------------\n");
			}
			pclose(fichero);

		} else {

			perror(path);
			return (1);

		}
	}
	return 0;
}
