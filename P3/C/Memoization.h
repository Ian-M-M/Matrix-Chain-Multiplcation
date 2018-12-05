#ifndef _Memoization_h
#define _Memoization_h
void printKeyValue( gpointer key, gpointer value, gpointer userData ) ;
void mi_strcpy (char* s1, char* s2, int pos);
int LOOKUPCHAIN(int array[], int i, int j);
void clean();
void initMemoization(int array[], int size);
#endif
