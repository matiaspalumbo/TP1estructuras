#ifndef __GDCLIST_H__
#define __GDCLIST_H__

#include <stddef.h>


typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
  struct _GNodo *ant;
} GNodo;

typedef GNodo *GList;


typedef void (*FuncionVisitante) (void *dato);

typedef enum {
  DLIST_RECORRIDO_HACIA_ADELANTE,
  DLIST_RECORRIDO_HACIA_ATRAS
} DListOrdenDeRecorrido;


// Devuelve una lista vacía.
GList gdclist_crear();

// Destruccion de la lista.
void gdclist_destruir(GList lista);

// Determina si la lista es vacía.
int gdclist_vacia(GList lista);

// Devuelve la longitud de una lista.
int gdclist_longitud(GList lista);

// Agrega un elemento al inicio de la lista. 
GList gdclist_agregar_inicio(GList lista, void *dato);

// Agrega un elemento al final de la lista.
GList gdclist_agregar_final(GList lista, void *dato);

// Dada una lista y dos posiciones, intercambia los nodos en posicion1 y posicion2 entre si.
// Asumimos que las posiciones van de 0 hasta longitud-1 y posicion1 != posicion2.
GList gdclist_intercambiar(GList lista, int posicion1, int posicion2);

void gdclist_recorrer(GList lista, FuncionVisitante visit, DListOrdenDeRecorrido orden);

#endif /* __GDCLIST_H */