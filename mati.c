#include <stdio.h>
#include <stdlib.h>
#include "gdclist.h"
#include "algoritmos.h"

static void imprimir_dato(void * dato) {
  printf("%d ", *(int*)dato);
}


int main(int argc, char *argv[]) {
  GList lista = gdclist_crear();
  int a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5;

  lista = gdclist_agregar_inicio(lista, &a1);
  lista = gdclist_agregar_inicio(lista, &a2);
  lista = gdclist_agregar_inicio(lista, &a3);
  lista = gdclist_agregar_inicio(lista, &a4);
  lista = gdclist_agregar_final(lista, &a5);

  gdclist_recorrer(lista, imprimir_dato);
  puts("");

  // lista = selectionSort(lista, comparaNumeros);
  lista = gdclist_intercambiar(lista, 1, 4);
  // lista = insertionSort(lista, comparaNumeros);
  // printf("Lista ordenada.\n");

  gdclist_recorrer(lista, imprimir_dato);
  puts("");

  gdclist_destruir(lista);

  return 0;
}