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

typedef void (*Destruir) (void *dato);


// Devuelve una lista vacía.
GList gdclist_crear();

// Destruccion de la lista.
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

GList gdclist_insertar(GList lista, void* dato, int pos);

GList gdclist_eliminar(GList lista, int pos);

// Dada una lista no vacía y dos posiciones, intercambia los nodos en posicion1 y posicion2 entre si.
GList gdclist_intercambiar(GList lista, GNodo* nodo1, GNodo* nodo2);

void gdclist_recorrer(GList lista, FuncionVisitante visit);

#endif /* __GDCLIST_H */