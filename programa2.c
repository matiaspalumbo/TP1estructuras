# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <assert.h> 
# include "gdclist.h"


typedef int (*FuncionComparadora) (void* dato1, void* dato2);

typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
  struct _GNodo *ant;
} GNodo;

typedef GNodo *GList;

typedef struct {
  char *nombre;
  int edad;
  char *lugarDeNacimiento; //pais o capital
} Persona

gdclist_agregar_final(lista, (void*)personaPTR); 

void leerPersonas(char *file, int *len_file) {
  FILE *fp_personas;
  fp_personas = fopen(file, "r"); // Abre el archivo pasado como parametro.
  // *len_file = contarLineas(fp_personas); // Cuenta la cantidad de líneas del archivo.
  // rewind(fp_personas);

  for (int i = 0; i < *len_file; i++) {
  }
}


int main(int argc, char **argv) {
  /* 
  argc == 2
  argv[0] es el nombre del ejecutable
  argv[1] es el nombre del archivo de salida de programa1, es decir, el que contiene las personas
  Tambien puede recibir la cantidad de personas del otro programa para no tener que leer el archivo dos veces.
  */

  return 0;
}