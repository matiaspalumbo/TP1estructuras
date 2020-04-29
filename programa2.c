# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <assert.h> 
# include "gdclist.h"
# include "algoritmos.h"

#define MAX_STR_SIZE 70

static void imprimir_persona(void * dato) {
  printf("%s - %d - %s\n", (char*)(((Persona*)dato)->nombre), ((Persona*) dato)->edad, (char*)(((Persona*)dato)->lugarDeNacimiento));
}

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



  // gdclist_recorrer(listaPersonas, imprimir_persona);
  puts("Edades BEFORE SORT");
  gdclist_recorrer(listaPersonas, imprimir_edad);
  puts("");
  // printf("lo tira antes de la función\n");

  listaPersonas = mergeSort(listaPersonas, compEdades);

  // // listaPersonas = gdclist_intercambiar(listaPersonas, 0, 49);

  puts("Edades AFTER SORT");
  gdclist_recorrer(listaPersonas, imprimir_edad);
  puts("");
  // printf("lo tira después de la función\n");
  gdclist_destruir(listaPersonas, destruir_persona);
  // printf("lo tira después de destruir la lista\n");









  return 0;
}