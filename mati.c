# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <assert.h> 
# include <locale.h> 
# include <wchar.h> 
# include "gdclist.h"
# include "algoritmos.h"

#define MAX_STR_SIZE 70
#define MAX_EDAD 0


static void imprimir_persona(void * dato) {
  wprintf(L"%s - %d - %s\n", (char*)(((Persona*)dato)->nombre), ((Persona*) dato)->edad, (char*)(((Persona*)dato)->lugarDeNacimiento));
}

GList leerPersonas(char *file) {
  FILE *fp_personas;
  fp_personas = fopen(file, "r"); // Abre el archivo pasado como parametro.
  GList listaPersonas = gdclist_crear();
  char *edad = malloc(sizeof(wchar_t)*MAX_STR_SIZE);
  while (! feof(fp_personas)) {
    Persona *persona = malloc(sizeof(Persona));
    persona->nombre = malloc(sizeof(wchar_t)*MAX_STR_SIZE);
    persona->lugarDeNacimiento = malloc(sizeof(wchar_t)*MAX_STR_SIZE);
    fwscanf(fp_personas, L"%[^,], %[^,], %[^\n]\n", persona->nombre, edad, persona->lugarDeNacimiento);
    // fscanf(fp_personas, "%[^,], %[^,], %[^\n]\n", persona->nombre, edad, persona->lugarDeNacimiento);
    persona->edad = atoi(edad);
    listaPersonas = gdclist_agregar_final(listaPersonas, (void*) persona);
    // printf("%s - %d - %s\n", persona->nombre, persona->edad, persona->lugarDeNacimiento);
  }
  free(edad);
  return listaPersonas;
}


GList copiarLista(GList lista) {
  int longitud = gdclist_longitud(lista);
  GList nuevaLista = gdclist_crear();
  for (int i = 0; i < longitud; i++) {
    nuevaLista = gdclist_agregar_final(nuevaLista, lista->dato);
    lista = lista->sig;
  }
  return nuevaLista;
}


void correrAlgoritmo(char *archivo, GList lista, AlgoritmoSorting ordenar, FuncionComparadora comparar) {
  FILE *archivoPtr = fopen(archivo, "w");
  int longitud = gdclist_longitud(lista);
  char algoritmo[MAX_STR_SIZE], funcComp[MAX_STR_SIZE], junk[MAX_STR_SIZE], orden[MAX_STR_SIZE];
  clock_t inicioSort, finalSort;
  inicioSort = clock();
  lista = ordenar(lista, comparar);
  finalSort = clock();
  double tiempoEjecucion = (double)(finalSort - inicioSort) / CLOCKS_PER_SEC;
  sscanf(archivo, "%[^_]_%[^_]_%[^_]_%[^_]_%[^.].txt", algoritmo, junk, junk, funcComp, orden);
  fprintf(archivoPtr, "%s Sort ordenando %s (%s)\nTiempo de ejecución: %fs\n\nLista ordenada:\n", algoritmo, funcComp, orden, tiempoEjecucion);
  GNodo* temp = lista;
  Persona* persona;
  for (int i = 0; i < longitud; i++) {
    persona = (Persona*) temp->dato;
    fwprintf(archivoPtr, L"%s, %d, %s\n", persona->nombre, persona->edad, persona->lugarDeNacimiento);
    temp = temp->sig;
  }
  fclose(archivoPtr);
}
// ------
int generarRandom(unsigned long long* prodRand, long* rand1, long* rand2, int upperLimit) {
  *rand1 = rand();
  *rand2 = rand();
  *prodRand = *rand1 * *rand2;
  // printf("random: %llu\n", *prodRand%upperLimit);
  return (int) (*prodRand % upperLimit);
}


void escribirPersonas(char **nombres, char **paises, int nPersonas, int len_nombres, int len_paises, char *file) {
  FILE *fp_salida;
  fp_salida = fopen(file, "w");
  char *nombreBuffer, *lugarBuffer;
  int edadBuffer;
  srand(time(0));
  unsigned long long prodRand;
  long rand1, rand2;
  for (int i = 0; i < nPersonas; i++) {
    nombreBuffer = nombres[generarRandom(&prodRand, &rand1, &rand2, len_nombres)];
    edadBuffer = (generarRandom(&prodRand, &rand1, &rand2, MAX_EDAD)) + 1;
    lugarBuffer = paises[generarRandom(&prodRand, &rand1, &rand2, len_paises)];
    fprintf(fp_salida, "%s, %d, %s\n", nombreBuffer, edadBuffer, lugarBuffer);
  }
  fclose(fp_salida);
}
// --------



int main(int argc, char **argv) {
  assert(argc == 2);
//   /* 
//   argc == 3
//   argv[0] es el nombre del ejecutable
//   argv[1] es el nombre del archivo de salida de programa1, es decir, el que contiene las personas (datos de prueba)
//   argv[2] es el nombre del archivo donde se volcaran los resulados de la aplicacion de los algoritmos
//   */
  // setlocale(LC_ALL, "es_ES");
  // printf("locale: %s\n", setlocale(LC_ALL, ""));
  GList listaPersonas = leerPersonas(argv[1]);
  // printf("done\n");
  // gdclist_recorrer(listaPersonas, imprimir_persona);
  // printf("done 2\n");
  
  // GList copia = copiarLista(listaPersonas);
  // correrAlgoritmo("Selection_Sort_comp_edades_ascendente.txt", copia, selectionSort, compEdades);
  // gdclist_destruir(copia, NULL);
  
  // copia = copiarLista(listaPersonas);
  // correrAlgoritmo("Selection_Sort_comp_nombres_alfabeticamente.txt", copia, selectionSort, compNombres);
  // gdclist_destruir(copia, NULL);

  // wprintf(L"%s\n", ((Persona*)(listaPersonas->dato))->nombre);
  // wprintf(L"%s\n", ((Persona*)(listaPersonas->sig->dato))->nombre);
  // printf("%d\n", wcscoll(((Persona*)(listaPersonas->dato))->nombre, ((Persona*)(listaPersonas->sig->dato))->nombre));
  // for (int i=0; i < strlen((char*)((Persona*)(listaPersonas->dato))->nombre); i ++) {
    // wprintf(L"%c\n", (((Persona*)(listaPersonas->dato))->nombre)[i]);
  // }

  // copia = copiarLista(listaPersonas);
  // correrAlgoritmo("Insertion_Sort_comp_edades_ascendente.txt", copia, insertionSort, compEdades);
  // gdclist_destruir(copia, NULL);
  
  // copia = copiarLista(listaPersonas);
  // correrAlgoritmo("Insertion_Sort_comp_nombres_alfabeticamente.txt", copia, insertionSort, compNombres);
  // gdclist_destruir(copia, NULL);
  
  // copia = copiarLista(listaPersonas);
  // correrAlgoritmo("Merge_Sort_comp_edades_ascendente.txt", copia, mergeSort, compEdades);
  // gdclist_destruir(copia, NULL);
  
  correrAlgoritmo("Merge_Sort_comp_nombres_alfabeticamente.txt", listaPersonas, mergeSort, compNombres);
  gdclist_recorrer(listaPersonas, imprimir_persona);
  gdclist_destruir(listaPersonas, destruir_persona);

// wchar_t *ch = malloc(sizeof(wchar_t));
// *ch = ;
// wprintf("%c\n", *ch);
// printf("%d\n", ch);
  return 0;
}