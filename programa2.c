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
  /* Función que, dada una lista, crea una nueva lista con nuevos nodos y mismos datos. */
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
  // Buffers
  char algoritmo[MAX_STR_SIZE], funcComp[MAX_STR_SIZE], junk[MAX_STR_SIZE], orden[MAX_STR_SIZE];
  /* El formato del nombre del archivo especifica el algoritmo utilizado y la función comparadora
  mediante guiones bajo (_), por lo que esto se utiliza para generar un título en el archivo. */
  sscanf(archivo, "%[^_]_%[^_]_%[^_]_%[^.].txt", algoritmo, junk, funcComp, orden);
  fprintf(archivoPtr, "%s Sort ordenando %s (%s)\nTiempo de ejecución: %fs\n\nLista ordenada:\n", algoritmo, funcComp, orden, tiempoEjecucion);
  
  GNodo *temp = lista;
  Persona *persona;
  for (int i = 0; i < longitud; i++) {
    /* En cada iteración, se imprime la Persona de un nodo de la lista en el archivo. */
    persona = (Persona*) temp->dato;
    fprintf(archivoPtr, "%s, %d, %s\n", persona->nombre, persona->edad, persona->lugarDeNacimiento);
    temp = temp->sig;
  }
  fclose(archivoPtr);
}


int main(int argc, char **argv) {
  assert(argc == 2);
//   /* 
//   argc == 3
//   argv[0] es el nombre del ejecutable
//   argv[1] es el nombre del archivo de salida de programa1, es decir, el que contiene las personas (datos de prueba)
//   argv[2] es el nombre del archivo donde se volcaran los resulados de la aplicacion de los algoritmos
//   */

  GList listaPersonas = leer_personas(argv[1]); // Se vuelvan las personas del archivo a una lista
  

  /* Luego, se corren y los tres algoritmos de ordenación con cada función comparadora
  y se vuelcan sus resultados en un archivo (seis llamadas a correr_algoritmo), 
  en cada caso (salvo el último), copiando la lista desordenada. */
  GList copia = copiar_lista(listaPersonas);
  correr_algoritmo("Selection_Sort_edades_ascendente.txt", copia, selection_sort, comp_edades);
  gdclist_destruir(copia, NULL);
  
  copia = copiar_lista(listaPersonas);
  correr_algoritmo("Selection_Sort_nombres_alfabeticamente.txt", copia, selection_sort, comp_nombres);
  gdclist_destruir(copia, NULL);

  copia = copiar_lista(listaPersonas);
  correr_algoritmo("Insertion_Sort_edades_ascendente.txt", copia, insertion_sort, comp_edades);
  gdclist_destruir(copia, NULL);
  
  copia = copiar_lista(listaPersonas);
  correr_algoritmo("Insertion_Sort_nombres_alfabeticamente.txt", copia, insertion_sort, comp_nombres);
  gdclist_destruir(copia, NULL);
  
  copia = copiar_lista(listaPersonas);
  correr_algoritmo("Merge_Sort_edades_ascendente.txt", copia, merge_sort, comp_edades);
  gdclist_destruir(copia, NULL);
  
  correr_algoritmo("Merge_Sort_nombres_alfabeticamente.txt", listaPersonas, merge_sort, comp_nombres);
  gdclist_destruir(listaPersonas, destruir_persona);



  return 0;
}