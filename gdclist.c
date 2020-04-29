#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "gdclist.h"


GList gdclist_crear() {
  return NULL;
}

void gdclist_destruir(GList lista, Destruir funcion_destructora) {
  lista->ant->sig = NULL;
  GNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    funcion_destructora(nodoAEliminar->dato);
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
  if (gdclist_es_vacia(lista)) {
    nuevoNodo->dato = dato;
    nuevoNodo->sig = nuevoNodo;
    nuevoNodo->ant = nuevoNodo;
  } else {
    nuevoNodo->dato = dato;
    nuevoNodo->sig = lista;
    GNodo *nodo = lista->ant; /* ahora 'nodo' apunta al ultimo elemento en la lista */
    lista->ant = nuevoNodo;
    nodo->sig = nuevoNodo;
    nuevoNodo->ant = nodo;
  }
  return nuevoNodo;
}

GList gdclist_agregar_final(GList lista, void *dato) {
  if (gdclist_es_vacia(lista)) {
    lista = malloc(sizeof(GNodo));
    lista->dato = dato;
    lista->sig = lista;
    lista->ant = lista;
  } else {
    GNodo *nuevoNodo = malloc(sizeof(GNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->sig = lista;
    GNodo *nodo = lista->ant; /* ahora 'nodo' apunta al ultimo elemento en la lista */
    lista->ant = nuevoNodo;
    nodo->sig = nuevoNodo;
    nuevoNodo->ant = nodo;
  }
  return lista;
}

void* gdclist_leer(GList lista, int pos) {
  assert(pos >= 0);
  // assert(pos < gdclist_longitud(lista));
  GNodo *temp = lista;
  for (int i = 0; i != pos; i++)
    temp = temp->sig;
  return temp->dato;
}

// GList gdclist_insertar(GList lista, void* dato, int pos) {
//   assert(pos <= gdclist_longitud(lista) && pos >= 0);
//   GNodo* nuevoNodo = malloc(sizeof(GNodo));
//   GNodo* aux;
//   nuevoNodo->dato = dato;
//   if (pos == 0) {
//     nuevoNodo->sig = lista;
//     nuevoNodo->ant = (lista)->ant;
//     aux = (lista)->ant;
//     (lista)->ant = nuevoNodo;
//     aux->sig = nuevoNodo;
//     lista = nuevoNodo;
//   } else {
//     GNodo* temp = lista;
//     for (int i=0; i!=pos-1; i++) {
//       temp = temp->sig;
//     }
//     nuevoNodo->sig = temp->sig;
//     nuevoNodo->ant = temp;
//     aux = temp->sig;
//     temp->sig = nuevoNodo;
//     aux->ant = nuevoNodo;
//   }
//   return lista;
// }

// GList gdclist_eliminar(GList lista, int pos) {
//   int longitud = gdclist_longitud(lista);
//   assert(pos < longitud && pos >= 0);
//   // GNodo* resultado = lista;
//   if (pos == 0) {
//     if (longitud == 1)
//       lista = NULL;
//     (lista)->sig->ant = (lista)->ant;
//     (lista)->ant->sig = (lista)->sig;
//     free(lista);
//     lista = lista->sig;
//   } else {
//     GNodo* temp = lista;
//     for (int i=0; i!=pos-1; i++) {
//       temp = temp->sig;
//     }
//     GNodo* aux = temp->sig;
//     temp->sig = aux->sig;
//     aux->sig->ant = temp;
//     free(aux);
//   }
//   return lista;
// }

// GList gdclist_intercambiar(GList lista, int posicion1, int posicion2) {
//   assert(!gdclist_es_vacia(lista));
//   assert(posicion1 >= 0 && posicion1 < gdclist_longitud(lista));
//   assert(posicion2 >= 0 && posicion2 < gdclist_longitud(lista));
//   if (posicion1 != posicion2) {
//     // int menor = (posicion1 <= posicion2) ? posicion1 : posicion2;
//     // int mayor = (posicion1 <= posicion2) ? posicion2 : posicion1;
//     void* dato1 = gdclist_leer(lista, posicion1);
//     void* dato2 = gdclist_leer(lista, posicion2);
//     lista = gdclist_insertar(lista, dato2, posicion1);
//     lista = gdclist_eliminar(lista, posicion1+1);
//     lista = gdclist_insertar(lista, dato1, posicion2);
//     lista = gdclist_eliminar(lista, posicion2+1);
//   }
//   return lista;
// }


// GList gdclist_intercambiar(GList lista, int posicion1, int posicion2) {
//   assert(!gdclist_es_vacia(lista));
//   assert(posicion1 >= 0 && posicion1 < gdclist_longitud(lista));
//   assert(posicion2 >= 0 && posicion2 < gdclist_longitud(lista));

//   GNodo *nodoA, *nodoB;
//   if (posicion1 != posicion2) {
//     int menor = (posicion1 <= posicion2) ? posicion1 : posicion2;
//     int mayor = (posicion1 <= posicion2) ? posicion2 : posicion1;
//     GNodo *temp = lista;
//     for (int i = 0; i < mayor+1; i++) {
//       if (i == menor) nodoA = temp;
//       if (i == mayor) nodoB = temp;
//       temp = temp->sig;
//     } /* ahora nodoA apunta al nodo en la menor posicion y nodoB al nodo en la posicion mayor */

//     if (menor == 0 && mayor == gdclist_longitud(lista)-1) {
//       nodoA->ant = nodoB->ant;
//       nodoB->ant->sig = nodoA;
//       GNodo *aux = nodoA->sig;
//       nodoA->sig = nodoB;
//       nodoB->sig = aux;
//       aux->ant = nodoB;
//       nodoB->ant = nodoA;
//     } else { 
//       if (menor == mayor - 1) {
//         nodoA->ant->sig = nodoB;
//         nodoB->sig->ant = nodoA;
//         GNodo* nodoAux = nodoA->ant;
//         nodoA->ant = nodoB;
//         nodoA->sig = nodoB->sig;
//         nodoB->sig = nodoA;
//         nodoB->ant = nodoAux;
//       } else {
//         GNodo *auxAsig = nodoA->sig;
//         GNodo *auxAant = nodoA->ant;
//         nodoA->sig = nodoB->sig;
//         nodoA->ant = nodoB->ant;
//         nodoB->sig->ant = nodoA;
//         nodoB->ant->sig = nodoA;
//         nodoB->sig = auxAsig;
//         nodoB->ant = auxAant;
//         auxAsig->ant = nodoB;
//         auxAant->sig = nodoB;
//       }
//     }
//     if (menor == 0) lista = nodoB;
//   }
//   return lista;
// }


GList gdclist_intercambiar(GList lista, GNodo* nodo1, GNodo* nodo2) {
  assert(!gdclist_es_vacia(lista));
  void* aux = nodo1->dato;
  nodo1->dato = nodo2->dato;
  nodo2->dato = aux;
  return lista;
}


void gdclist_recorrer(GList lista, FuncionVisitante visit) {
  GNodo * nodo = lista;
  for (; nodo->sig != lista; nodo = nodo->sig)
    visit(nodo->dato);
  visit(nodo->dato);
}