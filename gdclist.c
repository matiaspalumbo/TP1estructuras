#include "gdclist.h"
#include <stdlib.h>

// cambiar tipo de datos a void*
// agregar funcion intercambiar (nodos)
// analizar utilidad de función recorrer


GList glist_crear() {
  return NULL;
}

void glist_destruir(GList lista) {
  GNodo *ultimo = lista->ant;
  ultimo->sig = NULL;
  GNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int glist_vacia(GList lista) {
  return lista == NULL;
}

GList glist_agregar_final(GList lista, void * dato) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  GNodo *ultimo = lista->ant;
  if (lista != NULL)
    GNodo *ultimo = lista->ant;
  if (lista == NULL)
    lista = nuevoNodo;

  return lista;
}

GList glist_agregar_inicio(GList lista, void * dato) {
  GNodo * nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void glist_recorrer(GList lista, FuncionVisitante visit) {
  for (GNodo * nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}