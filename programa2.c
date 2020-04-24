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
  printf("Holaaa\n");
  FILE *fp_personas;
  fp_personas = fopen(file, "r"); // Abre el archivo pasado como parametro.
  GList listaPersonas = gdclist_crear();
  char edad[4];
  while (! feof(fp_personas)) {
    Persona* persona = malloc(sizeof(Persona));
    // persona->nombre = "Manuel";
    persona->nombre = malloc(sizeof(char)*MAX_STR_SIZE);
    persona->lugarDeNacimiento = malloc(sizeof(char)*MAX_STR_SIZE);
    fscanf(fp_personas, "%[^,], %[^,], %[^\n]\n", persona->nombre, edad, persona->lugarDeNacimiento);
    persona->edad = atoi(edad);
    listaPersonas = gdclist_agregar_final(listaPersonas, (void*) persona);
    // printf("%s - %d - %s\n", persona->nombre, persona->edad, persona->lugarDeNacimiento);
  }
  return listaPersonas;
}


int main(int argc, char **argv) {
  assert(argc == 2);
//   /* 
//   argc == 2
//   argv[0] es el nombre del ejecutable
//   argv[1] es el nombre del archivo de salida de programa1, es decir, el que contiene las personas
//   Tambien puede recibir la cantidad de personas del otro programa para no tener que leer el archivo dos veces.
//   */
  printf("wtf\n");
  GList listaPersonas = leerPersonas(argv[1]);

  gdclist_recorrer(listaPersonas, imprimir_persona, DLIST_RECORRIDO_HACIA_ADELANTE);

  listaPersonas = selectionSort(listaPersonas, compEdades);

  gdclist_recorrer(listaPersonas, imprimir_persona, DLIST_RECORRIDO_HACIA_ADELANTE);

//   gdclist_destruir(listaPersonas);

  return 0;
}