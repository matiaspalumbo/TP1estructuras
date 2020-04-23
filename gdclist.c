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

void* gdclist_leer(GList lista, int pos) {
  assert(pos >= 0);
  // assert(pos < gdclist_longitud(lista));
  GNodo* temp = lista;
  for (int i = 0; i != pos; i++)
    temp = temp->sig;
  return temp->dato;
}


// void gdclist_eliminar(GList* lista, int pos) {
//   assert(pos >= 0);
//   assert(pos <gdclist_longitud(*lista));

//   if (pos == 0) {
//     free(*lista);
//     // printf("ant %d\n", *(int*)((*lista)->ant->dato));
//     // printf("actual %d\n", *(int*)((*lista)->sig->dato));
//     // printf("sig %d\n", *(int*)((*lista)->dato));
//     // GNodo* aux1 = (*lista)->ant;
//     // GNodo* aux2 = (*lista)->sig;
//     // *lista = aux2;
//     // (*lista)->ant = aux1;
//     // printf("ant %d\n", *(int*)((*lista)->ant->dato));
//     // printf("actual %d\n", *(int*)((*lista)->sig->dato));
//     // printf("sig %d\n", *(int*)((*lista)->dato));
//   } else {
//     GNodo* temp = *lista;
//     for (int i=0; i!=pos-1; i++) {
//       temp = temp->sig;
//     } // temp = list[pos-1]
//     GNodo *aux = temp->sig->sig;
//     free(temp->sig);
//     temp->sig = aux;
//     aux->ant = temp;
//     printf("%d\n", *(int*)(temp->dato));
//     printf("%d\n", *(int*)(temp->sig->dato));
//   }
// }




// GList gdclist_intercambiar(GList* lista, int posicion1, int posicion2) {
//   assert(!gdclist_es_vacia(*lista));
//   assert(posicion1 >= 0 && posicion1 < gdclist_longitud(*lista));
//   assert(posicion2 >= 0 && posicion2 < gdclist_longitud(*lista));
//   GNodo *nodoA, *nodoB;
//   if (posicion1 != posicion2) {
//     int menor = (posicion1 <= posicion2) ? posicion1 : posicion2;
//     int mayor = (posicion1 <= posicion2) ? posicion2 : posicion1;
//     GNodo* temp = *lista;
//     for (int i = 0; i < mayor+1; i++) {
//       if (i == menor) nodoA = temp;
//       if (i == mayor) nodoB = temp;
//       temp = temp->sig;
//     } /* ahora nodoA apunta al nodo en la menor posicion y nodoB al nodo en la posicion mayor */
//     // printf("nodoA %d\n", *(int*)(nodoA->dato));
//     // printf("nodoB %d\n", *(int*)(nodoB->dato));
//     if (menor == 0 && mayor == gdclist_longitud(*lista)-1) {
//       nodoA->ant = nodoB->ant;
//       nodoB->ant->sig = nodoA;
//       GNodo* aux = nodoA->sig;
//       nodoA->sig = nodoB;
//       nodoB->sig = aux;
//       *lista = nodoB;
//       // nodoA->sig->ant = nodoB;
//       // GNodo* nodoAux = nodoB->ant;
//       // nodoB->ant = nodoA;
//       // nodoB->sig = nodoA->sig;
//       // nodoA->sig = nodoB;
//       // nodoA->ant = nodoAux;
//     printf("nodoA %d\n", *(int*)(nodoA->dato));
//     printf("nodoB %d\n", *(int*)(nodoB->dato));
//     printf("nodoAant %d\n", *(int*)(nodoA->ant->dato));
//     printf("nodoAsig %d\n", *(int*)(nodoA->sig->dato));
//     printf("nodoBant %d\n", *(int*)(nodoB->ant->dato));
//     printf("nodoBsig %d\n", *(int*)(nodoB->sig->dato));
//     }
//     if (menor == mayor - 1) {
//       nodoA->ant->sig = nodoB;
//       nodoB->sig->ant = nodoA;
//       GNodo* nodoAux = nodoA->ant;
//       nodoA->ant = nodoB;
//       nodoA->sig = nodoB->sig;
//       nodoB->sig = nodoA;
//       nodoB->ant = nodoAux;
//     } else {
//     GNodo *auxAsig = nodoA->sig;
//     GNodo *auxAant = nodoA->ant;
//     // printf("nodoAsig %d\n", *(int*)(auxAsig->dato));
//     // printf("nodoAant %d\n", *(int*)(auxAant->dato));
//     nodoA->sig = nodoB->sig;
//     nodoA->ant = nodoB->ant;
//     // printf("nodoA->sig %d\n", *(int*)(nodoA->sig->dato));
//     // printf("nodoA->ant %d\n", *(int*)(nodoA->ant->dato));
//     nodoB->sig->ant = nodoA;
//     nodoB->ant->sig = nodoA;
//     nodoB->sig = auxAsig;
//     nodoB->ant = auxAant;
//     auxAsig->ant = nodoB;
//     auxAant->sig = nodoB;
//     }
//     if (menor == 0) *lista = nodoB;
//   }
//   printf("lista %d - %d\n", *(int *)((*lista)->ant->dato), *(int *)((*lista)->dato));
//   return *lista;
// }

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