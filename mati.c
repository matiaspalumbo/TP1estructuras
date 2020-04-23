#include <stdio.h>
#include <stdlib.h>
#include "gdclist.h"
#include "algoritmos.c" // TO CHANGE

static void imprimir_dato(void * dato) {
  printf("%d ", *(int*)dato);
}


int main(int argc, char *argv[]) {
  GList lista = gdclist_crear();
  int a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 =5;

  lista = gdclist_agregar_inicio(lista, &a1);
  lista = gdclist_agregar_inicio(lista, &a2);
  lista = gdclist_agregar_inicio(lista, &a3);
  lista = gdclist_agregar_inicio(lista, &a4);
  lista = gdclist_agregar_inicio(lista, &a5);

  gdclist_recorrer(lista, imprimir_dato, DLIST_RECORRIDO_HACIA_ADELANTE);
  puts("");

  // for (int i = 0; i < gdclist_longitud(lista); i++) printf("tercer elemento: %d\n", *(int*)gdclist_leer(lista, i));
  // lista = selectionSort(lista, compNumeros);
  lista = gdclist_intercambiar(&lista, 0, 4);

  gdclist_recorrer(lista, imprimir_dato, DLIST_RECORRIDO_HACIA_ADELANTE);
  puts("");

  gdclist_destruir(lista);

  return 0;
}