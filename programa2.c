# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <assert.h> 
# include "gdclist.h"
# include "algoritmos.h"

#define MAX_STR_SIZE 70
#define POSITION 0

// static void imprimir_persona(void * dato) {
//   printf("%s - %d - %s\n", (char*)(((Persona*)dato)->nombre), ((Persona*) dato)->edad, (char*)(((Persona*)dato)->lugarDeNacimiento));
// }

GList leerPersonas(char *file) {
  FILE *fp_personas;
  fp_personas = fopen(file, "r"); // Abre el archivo pasado como parametro.
  GList listaPersonas = gdclist_crear();
  char edad[4];
  while (! feof(fp_personas)) {
    Persona *persona = malloc(sizeof(Persona));
    persona->nombre = malloc(sizeof(char)*MAX_STR_SIZE);
    persona->lugarDeNacimiento = malloc(sizeof(char)*MAX_STR_SIZE);
    fscanf(fp_personas, "%[^,], %[^,], %[^\n]\n", persona->nombre, edad, persona->lugarDeNacimiento);
    persona->edad = atoi(edad);
    listaPersonas = gdclist_agregar_final(listaPersonas, (void*) persona);
    // printf("%s - %d - %s\n", persona->nombre, persona->edad, persona->lugarDeNacimiento);
  }
  return listaPersonas;
}

void correrAlgoritmo(char* archivo, GList lista, AlgoritmoSorting ordenar, FuncionComparadora comparar) {
  FILE* archivoPtr = fopen(archivo, "w");
  int longitud = gdclist_longitud(lista);
  char algoritmo[MAX_STR_SIZE], funcComp[MAX_STR_SIZE], junk[MAX_STR_SIZE];
  clock_t inicioSort, finalSort;
  inicioSort = clock();
  lista = ordenar(lista, comparar);
  finalSort = clock();
  double tiempoEjecucion = (double)(finalSort - inicioSort) / CLOCKS_PER_SEC;
  sscanf(archivo, "%[^_]_%[^_]_%[^_]_%[^.].txt", algoritmo, junk, junk, funcComp);
  fprintf(archivoPtr, "%s Sort ordenando %s (de manera ascendente)\nTiempo de ejecución: %fs\n\nLista ordenada:\n", algoritmo, funcComp, tiempoEjecucion);
  GNodo* temp = lista;
  Persona* persona;
  for (int i = 0; i < longitud; i++) {
    persona = (Persona*) temp->dato;
    fprintf(archivoPtr, "%s, %d, %s\n", persona->nombre, persona->edad, persona->lugarDeNacimiento);
    temp = temp->sig;
  }
  fclose(archivoPtr);
}


int main(int argc, char **argv) {
  // assert(argc == 2);
//   /* 
//   argc == 3
//   argv[0] es el nombre del ejecutable
//   argv[1] es el nombre del archivo de salida de programa1, es decir, el que contiene las personas (datos de prueba)
//   argv[2] es el nombre del archivo donde se volcaran los resulados de la aplicacion de los algoritmos
//   */
  GList listaPersonas = leerPersonas(argv[1]);

  correrAlgoritmo("Selection_Sort_comp_edades.txt", listaPersonas, selectionSort, compEdades);
  // correrAlgoritmo("Selection_Sort_comp_nombres.txt", listaPersonas, selectionSort, compNombres);
  // correrAlgoritmo("Insertion_Sort_comp_edades.txt", listaPersonas, insertionSort, compEdades);
  // correrAlgoritmo("Insertion_Sort_comp_nombres.txt", listaPersonas, insertionSort, compNombres);
  // correrAlgoritmo("Merge_Sort_comp_edades.txt", listaPersonas, mergeSort, compEdades);
  // correrAlgoritmo("Merge_Sort_comp_nombres.txt", listaPersonas, mergeSort, compNombres);
  // gdclist_recorrer(listaPersonas, imprimir_persona);
  // puts("Edades BEFORE SORT");
// 
  // gdclist_recorrer(listaPersonas, imprimir_edad);   puts("");
  // printf("lo tira antes de la función\n");

  // Persona *persona = malloc(sizeof(Persona));
  // persona->edad = -42;
  // gdclist_recorrer(listaPersonas, imprimir_edad);   puts("");
  // listaPersonas = insertionSort(listaPersonas, compEdades);
  // listaPersonas = gdclist_intercambiar(listaPersonas, 0, 0);
  // listaPersonas = gdclist_insertar(listaPersonas, (void*) persona, 10);

  // puts("Edades AFTER SORT");
  // gdclist_recorrer(listaPersonas, imprimir_edad);   puts("");
  // printf("lo tira después de la función\n");



  
  gdclist_destruir(listaPersonas, destruir_persona);
  // printf("lo tira después de destruir la lista\n");









  return 0;
}