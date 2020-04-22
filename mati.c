#include <stdio.h>
#include <stdlib.h>
#include "gdclist.h"

static void imprimir_dato(void * dato) {
  printf("%d ", *(int*)dato);
}

int main(int argc, char *argv[]) {
  GList lista = gdclist_crear();
  int x = 0, y = 3, z = 8;
  int a = 4, b = 6, c = 9;

  lista = gdclist_agregar_inicio(lista, &x);
  lista = gdclist_agregar_inicio(lista, &b);
  lista = gdclist_agregar_inicio(lista, &a);
  lista = gdclist_agregar_final(lista, &y);
  lista = gdclist_agregar_final(lista, &z);
  lista = gdclist_agregar_final(lista, &c);

//   GList lista2 = gdclist_intercambiar(lista, 1, 4);

  gdclist_recorrer(lista, imprimir_dato, DLIST_RECORRIDO_HACIA_ADELANTE);
  puts("");

//   gdclist_recorrer(lista2, imprimir_dato, DLIST_RECORRIDO_HACIA_ADELANTE);
//   puts("");

  gdclist_destruir(lista);
//   gdclist_destruir(lista2);

  return 0;
}