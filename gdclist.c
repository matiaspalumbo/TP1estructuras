#include "gdclist.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


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

int gdclist_es_vacia(GList lista) {
  return lista == NULL;
}

int gdclist_longitud(GList lista) {
  int longitud;
  if (gdclist_es_vacia(lista)) longitud = 0;
  else {
    longitud = 1;
    GNodo* temp = lista;
    while (temp->sig != lista) {
      longitud++;
      temp = temp->sig;
    }
  }
  return longitud;
}

GList gdclist_agregar_inicio(GList lista, void *dato) {
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

GList gdclist_agregar_final(GList lista, void *dato) {
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

GList gdclist_intercambiar(GList lista, int posicion1, int posicion2) {
  assert(!gdclist_es_vacia(lista));
  assert(0 <= posicion1 && posicion1 < gdclist_longitud(lista));
  assert(0 <= posicion2 && posicion2 < gdclist_longitud(lista));
  GNodo *nodoA, *nodoB;
  if (posicion1 != posicion2) {
    int menor = (posicion1 <= posicion2) ? posicion1 : posicion2;
    int mayor = (posicion1 <= posicion2) ? posicion2 : posicion1;
    GNodo *temp = lista;
    for (int i = 0; i < mayor+1; i++) {
      if (i == menor) nodoA = temp;
      if (i == mayor) nodoB = temp;
      temp = temp->sig;
    } /* ahora nodoA apunta al nodo en la menor posicion y nodoB al nodo en la posicion mayor */
    GNodo *auxAsig = nodoA->sig;
    GNodo *auxAant = nodoA->ant;
    nodoA->sig = nodoB->sig;
    nodoA->ant = nodoB->ant;
    nodoB->sig->ant = nodoA;
    nodoB->ant->sig = nodoA;
    nodoB->sig = auxAsig;
    nodoB->ant = auxAant;
    auxAsig->ant = nodoB;
    auxAant->sig = nodoB;
    if (nodoA == lista) lista = nodoB;
    else if (nodoB == lista) lista = nodoA;
  }
  return lista;
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