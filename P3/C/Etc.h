#ifndef _Etc_h
#define _Etc_h
#include <glib.h>
/*
	ComienzaTimer(): Método que comienza a 
	contar el tiempo
*/
void ComienzaTimer();

/*
	FinTimer(): Para de contar el tiempo 
*/
double FinTimer();

/*
	GetParam(): Gestion de los parametros
	pasados al programa
*/
void GetParam(int argc, char * argv[], bool * flagDi, bool * flagDo,
	bool * flagF, bool * flagT, bool * flagMem, bool * flagTab, char * p);

/*
	Input(): Muestra el nombre del fichero
	y su contenido
*/
void Input();

/*
	Split(): Método en el que al pasarle el array, su 
	tamaño y una linea del fichero, modifica el array
	añadiendole los elementos de la linea divididos por
	comas.
*/
void split (char linea[], int * array, int size);

/*
	getSizeArray(): Calcula el numero de dimensiones
	contenidas en linea. Para que al crear el array 
	contenedor éste tenga un tamaño predefinido.
*/
int getSizeArray(char linea[]);

#endif
