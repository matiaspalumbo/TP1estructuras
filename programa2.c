# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <assert.h> 
# include <locale.h> 
# include "gdclist.h"
# include "algoritmos.h"

// Constante para la longitud de los strings auxiliares para leer archivos.
#define MAX_STR_SIZE 70


static void imprimir_persona(void * dato) {
  wprintf(L"%s - %d - %s\n", (char*)(((Persona*)dato)->nombre), ((Persona*) dato)->edad, (char*)(((Persona*)dato)->lugarDeNacimiento));
}

GList leerPersonas(char *file) {
  // Recibe el archivo con las Personas y crea una lista con todas ellas.
  FILE *fp_personas;
  fp_personas = fopen(file, "r"); // Abre el archivo pasado como parametro en formato lectura.
  GList listaPersonas = gdclist_crear(); // Crea la lista de Personas.
  char* personaBuff;
  while (! feof(fp_personas)) { // El bucle itera hasta que se llegue al final del archivo.
    // Le asigna un espacio en memoria a la Persona y a sus variable internas.
    Persona *persona = malloc(sizeof(Persona));
    persona->nombre = malloc(sizeof(char)*MAX_STR_SIZE);
    persona->lugarDeNacimiento = malloc(sizeof(char)*MAX_STR_SIZE);
    // Lee una línea del archivo en el formato que esta escrito y lo guarda en las 3 variables internas de la Persona.
    fscanf(fp_personas, "%[^,], %d, %[^\n]\n", personaBuff, &(persona->edad), persona->lugarDeNacimiento);
    int lengthStr = strlen(personaBuff);
    // for (int i = 0; i < lengthStr; i++) {
    //   if (personaBuff[i] < 0) {
    //     personaBuff[i] = 'N';
    //   }
    // }
    strcpy(persona->nombre, personaBuff);
    listaPersonas = gdclist_agregar_final(listaPersonas, (void*) persona);
  }
  return listaPersonas; // Retorna la lista con Personas.
}


GList copiarLista(GList lista) {
  /* Función que dada una lista del tipo GList crea una nueva lista con nuevos nodos
  pero cuyos datos son los mismos. */
  int longitud = gdclist_longitud(lista); // Longitud de la lista.
  GList nuevaLista = gdclist_crear(); // Crea una nueva lista.
  for (int i = 0; i < longitud; i++) { 
    // Por cada iteración agrega un nodo al final de la nueva lista con el dato correspondiente de la lista recibida.
    nuevaLista = gdclist_agregar_final(nuevaLista, lista->dato);
    lista = lista->sig;
  }
  return nuevaLista; // Retorna la nueva lista.
}


void correrAlgoritmo(char *archivo, GList lista, AlgoritmoSorting ordenar, FuncionComparadora comparar) {
  /* Función que dado un algoritmo de ordenación, una función comparadora de datos 
  y una lista, aplica el algoritmo con la función sobre la lista y escribe los 
  resultados en el archivo parasado como argumento. */
  FILE *archivoPtr = fopen(archivo, "w"); // Abre el archivo en formato escritura.
  int longitud = gdclist_longitud(lista); // Calcula la longitud de la lista.

  clock_t inicioSort, finalSort;
  inicioSort = clock(); // Toma el tiempo antes de correr el algoritmo.
  lista = ordenar(lista, comparar); // Corre el algoritmo con la función sobre la lista.
  // gdclist_recorrer(lista, imprimir_persona);
  finalSort = clock(); // Toma el tiempo despues de correr el algoritmo.
  // Calcula el tiempo de ejecución del algoritmo.
  double tiempoEjecucion = (double)(finalSort - inicioSort) / CLOCKS_PER_SEC;
  
  char algoritmo[MAX_STR_SIZE], funcComp[MAX_STR_SIZE], junk[MAX_STR_SIZE], orden[MAX_STR_SIZE];
  sscanf(archivo, "%[^_]_%[^_]_%[^_]_%[^.].txt", algoritmo, junk, funcComp, orden);
  fprintf(archivoPtr, "%s Sort ordenando %s (%s)\nTiempo de ejecución: %fs\n\nLista ordenada:\n", algoritmo, funcComp, orden, tiempoEjecucion);
  
  GNodo *temp = lista; // Defino un nodo para recorrer la lista.
  Persona *persona; // Persona a copiar en el archivo.
  for (int i = 0; i < longitud; i++) {
    /* En cada iteración, el bucle castea el dato de un nodo de la lista a Persona,
    y luego la impime en el archivo en el formato acordado. */
    persona = (Persona*) temp->dato;
    fprintf(archivoPtr, "%s, %d, %s\n", persona->nombre, persona->edad, persona->lugarDeNacimiento);
    temp = temp->sig; // Avanza al siguiente nodo.
  }

  fclose(archivoPtr); // Cierra el archivo.
}


int main(int argc, char **argv) {
  assert(argc == 2);
//   /* 
//   argc == 3
//   argv[0] es el nombre del ejecutable
//   argv[1] es el nombre del archivo de salida de programa1, es decir, el que contiene las personas (datos de prueba)
//   argv[2] es el nombre del archivo donde se volcaran los resulados de la aplicacion de los algoritmos
//   */

  GList listaPersonas = leerPersonas(argv[1]);
  
  // GList copia = copiarLista(listaPersonas);
  // correrAlgoritmo("Selection_Sort_edades_ascendente.txt", copia, selectionSort, compEdades);
  // gdclist_destruir(copia, NULL);
  
  // copia = copiarLista(listaPersonas);
  // correrAlgoritmo("Selection_Sort_nombres_alfabeticamente.txt", copia, selectionSort, compNombres);
  // gdclist_destruir(copia, NULL);

  // copia = copiarLista(listaPersonas);
  // correrAlgoritmo("Insertion_Sort_edades_ascendente.txt", copia, insertionSort, compEdades);
  // gdclist_destruir(copia, NULL);
  
  // copia = copiarLista(listaPersonas);
  // correrAlgoritmo("Insertion_Sort_nombres_alfabeticamente.txt", copia, insertionSort, compNombres);
  // gdclist_destruir(copia, NULL);
  
  // copia = copiarLista(listaPersonas);
  // correrAlgoritmo("Merge_Sort_edades_ascendente.txt", copia, mergeSort, compEdades);
  // gdclist_destruir(copia, NULL);
  
  correrAlgoritmo("Merge_Sort_nombres_alfabeticamente.txt", listaPersonas, mergeSort, compNombres);
  gdclist_destruir(listaPersonas, destruir_persona);



  return 0;
}