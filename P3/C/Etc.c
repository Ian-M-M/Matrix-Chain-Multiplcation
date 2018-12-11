#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#include "Etc.h"

clock_t t0, t1;
double time_taken = 0;
char path[500]=""; 
int numElementos, i;

void ComienzaTimer() {
	t0 = clock();
}

double FinTimer() {
	t1 = clock();
	time_taken = ((double) (t1 - t0) )/CLOCKS_PER_SEC;
  	return time_taken;
}

void GetParam(int argc, char * argv[], bool * flagDi, bool * flagDo,
	bool * flagF, bool * flagT, bool * flagMem, bool * flagTab, char * p) {
	if (argc < 3){
		printf(" [!] ERROR. Numero de argumentos incorrectos\n");
		exit(1);
	}
	// Estructura necesaria al ser las opciones de
	// mas de un caracter
	static struct option long_options[] = {
		{"di", no_argument, 0,  'i' },
	  	{"do", no_argument, 0,  'o' },
	  	{"f", required_argument,0, 'f' },
	  	{"t", no_argument,	0,	't' },
		{"mem", no_argument,	0,	'm' },
		{"tab", no_argument,	0,	'b' },
	  	{0, 0, 0, 0}
  	};
	int long_index = 0;
	int opt = 0;
	// Activamos flags leyendo los parametros
	// pasados al programa
	while ((opt = getopt_long(argc, argv,"iof:mbt",
        long_options, &long_index )) != -1) {
		switch(opt) {
	  		case 'o':
      			*flagDo = true;	// Debug output
        		break;
      		case 'i':
	      		*flagDi = true;	// Debug input
	      		break;
			case 'f':				// Archivo
	      		*flagF = true;
				strcpy(p,optarg);		// Copiamos la ruta 
				strcpy(path,optarg);	
	      		break;
			case 't':				// Contador del tiempo
	      		*flagT = true;		
	      		break;				
			case 'm':
	      		*flagMem = true;	// Debug input
	      		break;
			case 'b':
	      		*flagTab = true;	// Debug input
	      		break;
			case '?':
	  			printf ("[!] ERROR. Opcion incorrecta `-%c'.\n", optopt);
				exit(1);
		}
	}
	if (!flagF) {
		printf("[!] ERROR. '-f nombreFichero' requerido\n");
		exit(1);
	}
}

void Input(){
	printf("Ruta del fichero => %s\n",path);	
	FILE *fichero = fopen(path, "r");
	if (fichero != NULL) {
		char linea[128];
  		while (fgets(linea, sizeof linea, fichero) != NULL) {
			printf("%s", linea);
  		}
		fclose(fichero);
 	} else {
		perror(path);
		exit(1);
 	}
	printf("-------------------------------------------------\n");
}

void split (char linea [], int * array, int size) {
	numElementos = size;	
	char *token =strtok(linea, ",");
	i = 0;
	while (token != NULL) {
		array[i] = atoi(token);
		token=strtok(NULL, ",");
		i++;
	}
}

int getSizeArray(char linea[]) {
	int size = 0;
	i = 0;
	while(linea[i] != '\0') {
		if (linea[i] == ',') {
			size++;
		}
		i++;
	}
	if (size > 0) size++;
	return size;
}
