#ifndef __GDCLIST_H__
#define __GDCLIST_H__

#include <stddef.h>

typedef int (*FuncionDeComparacion) (void * dato1, void * dato2); // devuelve 1 en caso de que sean iguales o 0 si no lo son


typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
  struct _GNodo *ant;
} GNodo;

typedef GNodo * GList;

// Devuelve una lista vacía.
GList gdclist_crear();

// Destruccion de la lista.
void gdclist_destruir(GList lista);

// Determina si la lista es vacía.
int gdclist_vacia(GList lista);

DNodo * cdlist_agregar_inicio(DNodo * lista, int dato);

DNodo * cdlist_agregar_final(DNodo * lista, int dato);

#endif /* __GDCLIST_H */