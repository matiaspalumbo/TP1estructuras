# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <assert.h> 
# include "gdclist.h"
# include "algoritmos.h"
# include "persona.h"

// Constante para la longitud de los strings auxiliares en la lectura de archivos.
#define MAX_STR_SIZE 70


GList leer_personas(char *file) {
  // Recibe el archivo con las personas y crea una lista con todas ellas.
  FILE *fp_personas;
  fp_personas = fopen(file, "r");
  GList listaPersonas = gdclist_crear(); // Crea la lista de Personas.
  char nombreBuffer[MAX_STR_SIZE], paisBuffer[MAX_STR_SIZE]; // Buffers
  int len_nombre, len_pais; //  Variables auxiliares para la asignación de memoria
  while (! feof(fp_personas)) { // El bucle itera hasta llegar al final del archivo.
    Persona *persona = malloc(sizeof(Persona)); // Le asigna un espacio en memoria a la Persona.
    // Lee una línea del archivo en el formato que esta escrito y lo guarda en las 3 variables internas de la Persona.
    fscanf(fp_personas, "%[^,], %d, %[^\n]\n", nombreBuffer, &(persona->edad), paisBuffer);
    len_nombre = strlen(nombreBuffer);
    len_pais = strlen(paisBuffer);
    persona->nombre = malloc(sizeof(char) * (len_nombre + 1));
    persona->lugarDeNacimiento = malloc(sizeof(char) * (len_pais+1));
    strcpy(persona->nombre, nombreBuffer);
    strcpy(persona->lugarDeNacimiento, paisBuffer);
    // Agrega la Persona a la lista.
    listaPersonas = gdclist_agregar_final(listaPersonas, (void*) persona);
  }
  return listaPersonas; // Retorna la lista con Personas.
}

GList copiar_lista(GList lista) {
  // Función que, dada una lista, crea una nueva lista con nuevos nodos y mismos datos.
  int longitud = gdclist_longitud(lista);
  GList nuevaLista = gdclist_crear(); // Crea la nueva lista.
  for (int i = 0; i < longitud; i++) { 
    // Por cada iteración agrega un nodo al final de la nueva lista con el dato correspondiente de la lista recibida.
    nuevaLista = gdclist_agregar_final(nuevaLista, lista->dato);
    lista = lista->sig;
  }
  return nuevaLista; // Retorna la nueva lista.
}

void correr_algoritmo(char *archivo, GList lista, AlgoritmoSorting ordenar, FuncionComparadora comparar) {
  /* Función que dado un algoritmo de ordenación, una función comparadora de datos 
  y una lista, aplica el algoritmo con la función sobre la lista y escribe los 
  resultados en el archivo pasado como argumento. */
  FILE *archivoPtr = fopen(archivo, "w");
  int longitud = gdclist_longitud(lista);

  clock_t inicioSort, finalSort;
  inicioSort = clock(); // Almacena el tiempo pasado desde la ejecución del programa hasta antes de correr el algoritmo.
  lista = ordenar(lista, comparar); // Corre el algoritmo con la función sobre la lista.
  finalSort = clock(); // Almacena el tiempo pasado desde la ejecución del programa hasta después de correr el algoritmo.
  /* Calcula el tiempo de ejecución del algoritmo restando finalSort e inicioSort.
  CLOCKS_PER_SEC es un macro definido en time.h con la cantidad de clock ticks por segundo. */
  double tiempoEjecucion = (double)(finalSort - inicioSort) / CLOCKS_PER_SEC;
  char algoritmo[MAX_STR_SIZE], funcComp[MAX_STR_SIZE], junk[MAX_STR_SIZE], orden[MAX_STR_SIZE]; // Buffers
  /* El formato del nombre del archivo especifica el algoritmo utilizado y la función comparadora
  mediante guiones bajo (_), por lo que esto se utiliza para generar un título en el archivo. */
  sscanf(archivo, "%[^_]_%[^_]_%[^_]_%[^.].txt", junk, algoritmo, junk, funcComp);
  fprintf(archivoPtr, "%s Sort ordenando %s \nTiempo de ejecución: %fs\n\nLista ordenada:\n", algoritmo, funcComp, tiempoEjecucion);

  GNodo *temp = lista;
  Persona *persona;
  for (int i = 0; i < longitud; i++) {
    // En cada iteración, se imprime la Persona de un nodo de la lista en el archivo.
    persona = (Persona*) temp->dato;
    fprintf(archivoPtr, "%s, %d, %s\n", persona->nombre, persona->edad, persona->lugarDeNacimiento);
    temp = temp->sig;
  }
  fclose(archivoPtr);
}

/* generar_nombre_archivo efectivamente genera el nombre del archivo en el cual se volcaran los datos
correspondientes al algoritmo y función comparadora especificados en nombres con el formato
"_Algoritmo_Sort_funcComp".
argv1 es el nombre del archivo de entrada con la lista de personas y long_argv1 la longitud del nombre. */
char* generar_nombre_achivo(char* argv1, int long_argv1, char* nombre) {
  // para evitar que se acumulen los nombres de diferentes archivos en llamadas repetidas a la función
  // termino el string en el final del nombre del archivo con la lista de personas (sin el .txt)
  argv1[long_argv1-4] = '\0';
  strcat(argv1, nombre);
  char* extension = ".txt";
  strcat(argv1, extension);
  return argv1;
}

int main(int argc, char **argv) {
//   /* 
//   argc == 2
//   argv[0] es el nombre del ejecutable
//   argv[1] es el nombre del archivo de salida de programa1, es decir, el que contiene las personas (datos de prueba)
//   */
  assert(argc == 2);

  GList listaPersonas = leer_personas(argv[1]); // Se vuelcan las personas del archivo a una lista.

  /* Luego, se corren y los tres algoritmos de ordenación con cada función comparadora
  y se vuelcan sus resultados en un archivo (seis llamadas a correr_algoritmo), 
  en cada caso (salvo el último), copiando la lista desordenada. */

  int long_argv1 = strlen(argv[1]);

  GList copia = copiar_lista(listaPersonas);
  char* nombre = generar_nombre_achivo(argv[1], long_argv1, "_Selection_Sort_edades");
  correr_algoritmo(nombre, copia, selection_sort, comp_edades);
  gdclist_destruir(copia, NULL);
  
  copia = copiar_lista(listaPersonas);
  nombre = generar_nombre_achivo(argv[1], long_argv1, "_Selection_Sort_nombres");
  correr_algoritmo(nombre, copia, selection_sort, comp_nombres);
  gdclist_destruir(copia, NULL);

  copia = copiar_lista(listaPersonas);
  nombre = generar_nombre_achivo(argv[1], long_argv1, "_Insertion_Sort_edades");
  correr_algoritmo(nombre, copia, insertion_sort, comp_edades);
  gdclist_destruir(copia, NULL);
  
  copia = copiar_lista(listaPersonas);
  nombre = generar_nombre_achivo(argv[1], long_argv1, "_Insertion_Sort_nombres");
  correr_algoritmo(nombre, copia, insertion_sort, comp_nombres);
  gdclist_destruir(copia, NULL);
  
  copia = copiar_lista(listaPersonas);
  nombre = generar_nombre_achivo(argv[1], long_argv1, "_Merge_Sort_edades");
  correr_algoritmo(nombre, copia, merge_sort, comp_edades);
  gdclist_destruir(copia, NULL);

  nombre = generar_nombre_achivo(argv[1], long_argv1, "_Merge_Sort_nombres");
  correr_algoritmo(nombre, listaPersonas, merge_sort, comp_nombres);
  gdclist_destruir(listaPersonas, destruir_persona);

  return 0;
}