#include "gdclist.h"
#include <stdlib.h>

// cambiar tipo de datos a void*
// agregar funcion intercambiar (nodos)
// analizar utilidad de función recorrer

GList gdclist_crear() {
  return NULL;
}

void gdclist_destruir(GList lista) {
  if (lista != NULL) {
    GNodo *nodo = lista;
    for (; nodo->sig != lista; nodo = nodo->sig);
    nodo->sig = NULL;
  }
  GNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int gdclist_vacia(GList lista) {
  return lista == NULL;
}

GNodo *gdclist_agregar_inicio(GList lista, void *dato) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));  
  if (lista == NULL) {
    nuevoNodo->dato = dato;
    nuevoNodo->sig = lista;
    nuevoNodo->ant = lista;
  } else {
    nuevoNodo->dato = dato;
    nuevoNodo->sig = lista;
    lista->ant = nuevoNodo;
    GNodo *nodo = lista;
    for (; nodo->sig != lista; nodo = nodo->sig);
    /* ahora 'nodo' apunta al ultimo elemento en la lista */
    nodo->sig = nuevoNodo;
    nuevoNodo->ant = nodo;
  }
  return nuevoNodo;
}

GNodo *gdclist_agregar_final(GList lista, void *dato) {
  if (lista == NULL) {
    lista = malloc(sizeof(GNodo));
    lista->dato = dato;
    lista->sig = lista;
    lista->ant = lista;
  } else {
    GNodo *nuevoNodo = malloc(sizeof(GNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->sig = lista;
    lista->ant = nuevoNodo;
    GNodo *nodo = lista;
    for (; nodo->sig != lista; nodo = nodo->sig);
    /* ahora 'nodo' apunta al ultimo elemento en la lista */
    nodo->sig = nuevoNodo;
    nuevoNodo->ant = nodo;
  }
  return lista;
}

GNodo *gdclist_intercambiar(GNodo *lista, int posicion1, int posicion2) {
  GNodo *inicio = lista;
  GNodo *nodoA, *nodoB;
  int menor = (posicion1 < posicion2) ? posicion1 : posicion2;
  int mayor = (posicion1 < posicion2) ? posicion2 : posicion1;
  for (int i = 0; i < mayor; i++) {
    if (i == menor) nodoA = lista;
    if (i == mayor) nodoB = lista;
    lista = lista->sig;
  }
  /* ahora nodoA apunta al nodo en la menor posicion y nodoB al nodo en la posicion mayor */
  
  GNodo *auxA = nodoA;
  nodoA->sig = nodoB->sig;
  nodoA->ant = nodoB->ant;
  (nodoB->sig)->ant = nodoA;
  (nodoB->ant)->sig = nodoA;
  nodoB->sig = auxA->sig;
  nodoB->ant = auxA->ant;
  (auxA->sig)->ant = nodoB;
  (auxA->ant)->sig = nodoB;

  return inicio;
}