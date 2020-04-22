#ifndef __GDCLIST_H__
#define __GDCLIST_H__

#include <stddef.h>


typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
  struct _GNodo *ant;
} GNodo;

typedef GNodo *GList;

// Devuelve una lista vacía.
GList gdclist_crear();

// Destruccion de la lista.
void gdclist_destruir(GList lista);

// Determina si la lista es vacía.
int gdclist_vacia(GList lista);

// Agrega un elemento al inicio de la lista. 
GNodo *gdclist_agregar_inicio(GNodo *lista, void *dato);

// Agrega un elemento al final de la lista.
GNodo *gdclist_agregar_final(GNodo *lista, void *dato);

// Dada una lista y dos posiciones, intercambia los nodos en posicion1 y posicion2 entre si.
// Asumimos que las posiciones van de 0 hasta longitud-1 y posicion1 != posicion2.
GNodo *gdclist_intercambiar(GNodo *lista, int posicion1, int posicion2);

#endif /* __GDCLIST_H */