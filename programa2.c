# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <assert.h> 

typedef int (*FuncionComparadora) (void* dato1, void* dato2);

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


GList glist_crear() {
  return NULL;
}

void glist_destruir(GList lista) {
  GNodo *nodoAEliminar = lista;
  GNodo *ultimo = lista->ant;
  while (nodoAEliminar != ultimo) {
  	free(nodoAEliminar);
    nodoAEliminar = nodoAEliminar->sig;
  }
  free(ultimo);
  free(lista);
}

int glist_vacia(GList lista) {
  return lista == NULL;
}

GList glist_agregar_final(GList lista, void* dato) {
	GNodo* nuevoNodo = malloc(sizeof(GNodo));
	nuevoNodo->dato = dato;
	nuevoNodo->sig = lista;
  GNodo *aux = lista->ant;
	if (lista != NULL)
		lista->ant = nuevoNodo;
	if (lista == NULL)
		lista = nuevoNodo;
	lista->primero = nuevoNodo;
	return lista;
}

GList glist_agregar_inicio(GList lista, int dato) {
	GNodo* nuevoNodo = malloc(sizeof(GNodo));
	nuevoNodo->dato = dato;
	if (glist_vacia(lista)) {
		nuevoNodo->sig = nuevoNodo;
		lista->primero = nuevoNodo;
		lista->ultimo = nuevoNodo;
	} else {
		nuevoNodo->sig = lista->primero;
		lista->primero = nuevoNodo;
		lista->ultimo->sig = nuevoNodo;
	}
	return lista;
}


void glist_recorrer(GList lista, FuncionVisitante visit) {
	GNodo* temp = lista->primero;
	while (temp != lista->ultimo) {
		visit(temp->dato);
		temp = temp->sig;
	}
	visit(lista->ultimo->dato);
}


