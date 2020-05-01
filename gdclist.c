#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "gdclist.h"

// Archivo del código fuente de la implementación de listas generales doblemente enlazadas circulares.


GList gdclist_crear() { // Función que devuelve una lista vacia.
  return NULL;
}

void gdclist_destruir(GList lista, Destruir funcion_destructora) {
  /* Función que libera el espacio en memoria que ocupa una lista (la destruye),
  y en caso de ser necesario, el dato que guarda cada nodo. */
  lista->ant->sig = NULL; // Iguala a NULL el siguiente del último elemento de la lista y asi deja de ser circular.
  GNodo *nodoAEliminar; // Variable auxiliar.
  while (lista != NULL) { // El bucle se repite hasta que lista llegue a su último elemento.
    // Por cada iteración, guarda un nodo en la variable auxiliar e iguala lista al siguiente nodo.
    nodoAEliminar = lista;
    lista = lista->sig;
    // En caso de ser necesario libera el espacio en memoria del dato del nodo.
    if (funcion_destructora != NULL) funcion_destructora(nodoAEliminar->dato);
    // Y luego libera la memoria del propio nodo.
    free(nodoAEliminar);
  }
}

int gdclist_es_vacia(GList lista) { // Función que determina si la lista es vacía.
  return lista == NULL;
}

int gdclist_longitud(GList lista) {
  // Función que devuelve la longitud de la lista dada.
  int longitud;
  if (gdclist_es_vacia(lista)) longitud = 0; // Si la lista es vacia, su longitud es 0.
  else {
    longitud = 1; // Caso contrario su longitud es al menos 1.
    GNodo *temp = lista; // Defino un nodo para recorrer la lista.
    while (temp->sig != lista) { // El bucle itera hasta llegar al último elemento de la lista.
      // Por cada iteración aumenta la longitud por 1 y avanza un nodo en la lista.
      longitud++;
      temp = temp->sig;
    }
  }
  return longitud;
}

GList gdclist_agregar_inicio(GList lista, void *dato) {
  // Función que dada una lista y un dato, agrega un nodo al inicio de la lista con ese dato.
  // Le asigno un espacio en memoria al nuevo nodo que se va a agregar a la lista.
  GNodo *nuevoNodo = malloc(sizeof(GNodo)); 
  if (gdclist_es_vacia(lista)) {
    // Si la lista es vacía, 'nuevoNodo' será el único nodo de la lista.
    nuevoNodo->dato = dato;
    nuevoNodo->sig = nuevoNodo;
    nuevoNodo->ant = nuevoNodo;
  } else { // Si la lista no es vacia:
    nuevoNodo->dato = dato;
    nuevoNodo->sig = lista; // El siguiente de 'nuevoNodo' será el inicio de la lista.
    GNodo *nodo = lista->ant; // Defino un nodo auxiliar que apunta al ultimo elemento en la lista.
    lista->ant = nuevoNodo; // El anterior de la lista sera 'nuevoNodo'.
    nodo->sig = nuevoNodo; // El siguiente del úlitmo nodo de la lista será 'nuevoNodo'.
    nuevoNodo->ant = nodo; // El anterior de 'nuevoNodo' será el último elemento de la lista.
  }
  return nuevoNodo; // Retorno 'nuevoNodo', pues pasa a ser el inicio de la lista.
}

GList gdclist_agregar_final(GList lista, void *dato) {
  // Función que dada una lista y un dato, agrega un nodo al inicio de la lista con ese dato.
  if (gdclist_es_vacia(lista)) {
    // Si la lista es vacía le asigno un espacio en memoria a la misma.
    lista = malloc(sizeof(GNodo));
    lista->dato = dato;
    lista->sig = lista;
    lista->ant = lista;
  } else { // Si la lista no es vacia:
    // Le asigno un espacio en memoria al nuevo nodo que se va a agregar a la lista.
    GNodo *nuevoNodo = malloc(sizeof(GNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->sig = lista; // El siguiente de 'nuevoNodo' será el inicio de la lista.
    GNodo *nodo = lista->ant; // ahora 'nodo' apunta al ultimo elemento en la lista.
    lista->ant = nuevoNodo; // El anterior de la lista sera 'nuevoNodo'.
    nodo->sig = nuevoNodo; // El siguiente del úlitmo nodo de la lista será 'nuevoNodo'.
    nuevoNodo->ant = nodo; // El anterior de 'nuevoNodo' será el último elemento de la lista.
  }
  return lista;
}

void* gdclist_leer(GList lista, int pos) {
  // Función que dada una lista y una posición, lee el dato de la lista en la posición indicada.
  assert(0 <= pos && pos < gdclist_longitud(lista)); // Verifico que la posición sea valida.
  GNodo *temp = lista; // Defino un nodo para recorrer la lista.
  for (int i = 0; i != pos; i++) temp = temp->sig; 
  // Ahora 'temp' apunta al nodo en la posicion pos.
  return temp->dato; // Retorno el dato de ese nodo.
}

GList gdclist_intercambiar(GList lista, GNodo *nodo1, GNodo *nodo2) {
  // Función que dada una lista y dos nodos de la misma, intercambia sus datos entre sí.
  assert(!gdclist_es_vacia(lista)); // Verifico que la lista no sea vacía.
  void *aux = nodo1->dato; // Guardo el primer dato en una variable auxiliar.
  nodo1->dato = nodo2->dato; // Luego guardo el segundo dato en el primer nodo.
  nodo2->dato = aux; // Y por último guardo el primer dato en el segundo nodo.
  return lista;
}


// BORRAR
void gdclist_recorrer(GList lista, FuncionVisitante visit) {
  // Función que dada una lista y una función visitante, recorre la lista y aplica visit a cada nodo.
  GNodo *nodo = lista; // Defino un nodo para recorrer la lista.
  for (; nodo->sig != lista; nodo = nodo->sig) 
    visit(nodo->dato); // Llamo la función visitante con cada nodo de la lista.
  visit(nodo->dato); 
}