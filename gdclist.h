#ifndef __GDCLIST_H__
#define __GDCLIST_H__

#include <stddef.h>


typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
  struct _GNodo *ant;
} GNodo;

typedef GNodo *GList;

typedef struct {
  char *nombre;
  int edad;
  char *lugarDeNacimiento; //pais o capital
} Persona;


typedef void (*FuncionVisitante) (void *dato);

typedef void (*Destruir) (void *dato);


// Devuelve una lista vacía.
GList gdclist_crear();

// Destruccion de la lista.
void gdclist_destruir(GList lista);

// Destruccion de la lista donde el dato es una persona.
void GList_destruir_persona(GList lista, Destruir destruir_persona);

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

// Dada una lista no vacía y dos posiciones, intercambia los nodos en posicion1 y posicion2 entre si.
GList gdclist_intercambiar(GList lista, int posicion1, int posicion2);

void gdclist_recorrer(GList lista, FuncionVisitante visit);

#endif /* __GDCLIST_H */