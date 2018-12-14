## PROGRAMACIÓN III INFORME DE LA RÁCTICA 3 (PROGRAMACIÓN DINÁMICA)

1. **Nombre de los participantes:**

- Marcos Jesús Santana Pérez
- Chetani Mesa Guzmán
- Ían Marrero Martín

2. **Descripción del problema a resolver:**

El problema consiste en calcular la cantidad mínima de operaciones necesarias para multiplicar una serie de matrices, para esto seguimos como criterio el tamaño de las matrices, por tanto ignoraremos el resultado y nos centraremos en cuantas operaciones van a realizarse.

3. **Lenguajes de programación elegidos:**

- Java v1.8.0_191
- Python v2.7
- C

4. **Enlace a la página web de *geeksforgeek* que describe el problema:**

   [https://www.geeksforgeeks.org/matrix-chain-multiplication-dp-8/](https://www.geeksforgeeks.org/matrix-chain-multiplication-dp-8/)

5. **Estrategia implementada: **

   Memoization.

6. **Nombre de los ficheros que contienen el algoritmo implementado**

   Java:

   - P3/Java/src/P3_entrega_3/Memoization.java

   Python:

   - P3/Python/Memoization.java

   C:

   - P3/C/Memoization.java

7. **Copia de pantalla del fragmento de código que implementa el algoritmo** 

   Python:

   ```python
   def MatrixChainOrder(i, j):
   
       key = str(i) + "," + str(j)
   
       if mem[key] < inf: return mem[key]
       else:
           for k in range(i, j):
   
               q = MatrixChainOrder(i, k) + MatrixChainOrder(k + 1, j) + mat[i - 1] * mat[k] * mat[j]
   
               if q < mem[key]: mem[key] = q
   
       return mem[key]
   ```

   Java:

   ```java
     public long MatrixChainOrder(int i, int j){
   
       String key = i + "," + j;
   
       if(mem.get(key) < inf) return mem.get(key);
   
       else{
         
         for (int k = i; k < j ; k++) {
   
           long q = q = MatrixChainOrder(i, k) + MatrixChainOrder(k + 1, j) + matrix[i - 1] * matrix[k] * matrix[j];
   
           if (q < mem.get(key)) mem.put(key,q);
   
         }
       }
       return mem.get(key);
     }
   ```

   C:

   ```c
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
   
   ```

8. **Formato del fichero de entrada del programa**

   El fichero contendrá cada elemento de un conjunto separado por una coma. Cada conjunto de elementos se pondrá en una línea nueva.
   **Formato:**

   ```
   n1,n2.n3,n4
   n1,n2,n3,n4,n5
   ```

   En la entrega adjuntamos una serie de ficheros para probar el código.

9. **Copia de pantalla que muestre el uso del programa desde consola activando la opción que muestra el tiempo consumido en la ejecución del programa**

   En la entrega hemos adjuntado una serie de ficheros que contienen la salida que se obtiene al usar los ficheros llamados tanto en **Contenido-Unico/todos.txt** y **Contenido-Random/todos.txt**.

   A continuación pantallazo de la salida al usar el archivo /ficheros/Contenido-Random/500.txt

   Java:

   ![]()

   Python:

   ![]()

   C:

   ![]()



## Información adicional

### Ejecución:

##### Java:

Para compilar el archivo ejecutamos:

```
javac -sourcepath src -d build src/**/*.java
```

Para ejecutar el archivo compilado ejecutamos:

```sh
java -cp .:build:**/*.class P3_entrega_3.Main (opciones)
```

##### Python

Para ejecutar Python simplemente ejecutamos:

```
python main.py (opciones)
```

##### C

Para compilar el archivo ejecutamos:

```sh
gcc *.c -o nombre_del_programa
```

Y para ejecutarlo ejecutamos:

```
./nombre_del_programa (opciones)
```

El formato de los parámetros se especifica a continuación.

### Parámetros admitidos:

- **-f file**: Indica al programa el input del que se van a obtener los conjuntos de elementos. 

- **-t:** Muestra el tiempo que tarda en resolverse el problema.
- **-do (--do en C):** Muestra el resultado al resolver el problema.
- **-di (--di en C):** Muestra el nombre del archivo y el contenido del mismo.
- **-mem (--mem en C):** Indica que el problema se va a resolver mediante memoization.
- **-tab (--tab en C):** Indica que el problema se va a resolver mediante tabulation.

> **Nota**: Si se utiliza -t o -do ha de indicarse -mem, -tab o ambas.
