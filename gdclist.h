#ifndef __GDCLIST_H__
#define __GDCLIST_H__

#include <stddef.h>

// Archivo de cabecera de la implementación de listas generales doblemente enlazadas circulares.


typedef struct _GNodo { // Estructura de un nodo de una lista general.
  void *dato;
  struct _GNodo *sig;
  struct _GNodo *ant;
} GNodo;

typedef GNodo *GList; // Estructura de una lista general.

/* Declaración de un puntero a una función llamado FuncionVisitante que toma 
como argumneto un puntero a void y retorna void. */
typedef void (*FuncionVisitante) (void *dato);

/* Declaración de un puntero a una función llamado Destruir que toma como 
argumento un puntero a void y retorna void. */
typedef void (*Destruir) (void *dato);


// Devuelve una lista vacía.
GList gdclist_crear();

// Destruye de la lista y en caso de que sea necesario, el dato que guarda cada nodo.
void gdclist_destruir(GList lista, Destruir funcion_destructora);

// Determina si la lista es vacía.
int gdclist_es_vacia(GList lista);

// Devuelve la longitud de una lista.
int gdclist_longitud(GList lista);

// Agrega un elemento al inicio de la lista. 
GList gdclist_agregar_inicio(GList lista, void *dato);

// Agrega un elemento al final de la lista.
GList gdclist_agregar_final(GList lista, void *dato);

// Lee el dato en la posición pos de la lista.
void *gdclist_leer(GList lista, int pos);

// Dada una lista y dos nodos de la lista, intercambia los datos de los nodos nodo1 y nodo2 entre si.
GList gdclist_intercambiar(GList lista, GNodo *nodo1, GNodo *nodo2);

// BORRAR
// Dada una lista y una función visitante, recorre la lista y aplica visit a cada nodo.
void gdclist_recorrer(GList lista, FuncionVisitante visit);

#endif /* __GDCLIST_H */