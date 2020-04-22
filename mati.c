#include <stdio.h>
#include <stdlib.h>
#include "gdclist.h"

static void imprimir_dato(void * dato) {
  printf("%d ", *(int*)dato);
}

int main(int argc, char *argv[]) {
  GList lista = gdclist_crear();
  int x = 25, y = 26, z = 27;
  int a = 1, b = 2, c = 3;

  lista = gdclist_agregar_inicio(lista, &c);
  lista = gdclist_agregar_inicio(lista, &b);
  lista = gdclist_agregar_inicio(lista, &a);
  lista = gdclist_agregar_final(lista, &x);
  lista = gdclist_agregar_final(lista, &y);
  lista = gdclist_agregar_final(lista, &z);

  gdclist_recorrer(lista, imprimir_dato, DLIST_RECORRIDO_HACIA_ADELANTE);
  puts("");

  lista = gdclist_intercambiar(lista, 1, 4);

  gdclist_recorrer(lista, imprimir_dato, DLIST_RECORRIDO_HACIA_ADELANTE);
  puts("");

  gdclist_destruir(lista);

  return 0;
}