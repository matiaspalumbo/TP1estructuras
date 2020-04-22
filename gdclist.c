# include "gdclist.h"
# include <stdlib.h>


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
    nuevoNodo->sig = nuevoNodo;
    nuevoNodo->ant = nuevoNodo;
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

  GNodo *aux1A = nodoA->sig;
  GNodo *aux2A = nodoA->ant;
  nodoA->sig = nodoB->sig;
  nodoA->ant = nodoB->ant;
  (nodoB->sig)->ant = nodoA;
  (nodoB->ant)->sig = nodoA;
  nodoB->sig = aux1A;
  nodoB->ant = aux2A;
  aux1A->ant = nodoB;
  aux2A->sig = nodoB;

  return inicio;
}


void gdclist_recorrer_adelante(GList lista, FuncionVisitante visit) {
  GNodo * nodo = lista;
  for (; nodo->sig != lista; nodo = nodo->sig)
    visit(nodo->dato);
  visit(nodo->dato);
}

void gdclist_recorrer_atras(GList lista, FuncionVisitante visit) {
  GNodo * nodo = lista->ant;
  for (; nodo->ant != lista->ant; nodo = nodo->ant)
    visit(nodo->dato);
  visit(nodo->dato);
}

void gdclist_recorrer(GList lista, FuncionVisitante visit, DListOrdenDeRecorrido orden) {
  if (lista != NULL) {
    if (orden) gdclist_recorrer_atras(lista, visit);
    else gdclist_recorrer_adelante(lista, visit);
  }
}