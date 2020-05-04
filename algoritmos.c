# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include "gdclist.h"
# include "algoritmos.h"


/* Archivo con las implementaciones de los algoritmos de ordenación
sobre listas generales doblemente enlazadas circulares. */


/* Selection Sort ordena una lista detectando el elemento mínimo cada vez que la recorre,
moviéndolo al principio de la lista y repitiendo el proceso con los elementos restantes hasta ordenarla en su totalidad. */
GList selection_sort(GList lista, FuncionComparadora comparar) {
  if (!gdclist_es_vacia(lista)) {
    GNodo *nodoMinimo, *nodoAComparar, *nodoActual = lista;
    int longitud = gdclist_longitud(lista);
    // Se itera (longitud - 1) veces ya que la iteración número (longitud) es trivial (queda un sólo elemento).
    for (int i = 0; i < longitud - 1; i++) {
      nodoMinimo = nodoActual;
      nodoAComparar = nodoActual->sig;
      for (int j = i + 1; j < longitud; j++) { // Compara cada elemento no ordenado con el mínimo, y en caso de ser menor lo establece como nuevo mínimo
        if (comparar(nodoAComparar->dato, nodoMinimo->dato) < 0) {
          nodoMinimo = nodoAComparar;
        }
        nodoAComparar = nodoAComparar->sig;
      }
      lista = gdclist_intercambiar(lista, nodoActual, nodoMinimo); // Intercambia el elem. mínimo con el consecutivo al último ordenado.
      nodoActual = nodoActual->sig;
    }
  }
  return lista;
}

/* Insertion Sort ordena una lista comparando la sublista ordenada al principio de la lista (que comienza siendo unitaria), 
con el elemento inmediato posterior, ubicandolo en el orden correspondiente con respecto a los elementos ya ordenados, aumentando así
la longitud de la sublista ordenada por 1. Repite este proceso hasta ordenar el último elemento. */
GList insertion_sort(GList lista, FuncionComparadora comparar) { 
  if (!gdclist_es_vacia(lista)) {
    GNodo *nodoActual = lista, *nodoAComparar, *ultimoOrdenado;
    int j, longitud = gdclist_longitud(lista);
    for (int i = 1; i < longitud; i++) { // La iteración comienza del segundo elemento pues el primero esta trivialmente ordenado.
      j = i - 1;
      ultimoOrdenado = nodoActual;
      nodoAComparar = nodoActual->sig;
      while (j >= 0) { // Compara el último elemento de la sublista ordenada con su siguiente.
        if (comparar(nodoAComparar->dato, nodoActual->dato) < 0) {
          // Si no están ordenados los intercambia y repite la comparación entre el nuevo elemento y su anterior hasta que esté ordenado.
          lista = gdclist_intercambiar(lista, nodoActual, nodoAComparar);
          j--;
          nodoActual = nodoActual->ant;
          nodoAComparar = nodoAComparar->ant;
        } else j = -1; // Si están ordenados el nuevo nodo pasa a ser el último de la sublista ordenada y avanza al proximo.
      }
      nodoActual = ultimoOrdenado->sig;
    }
  }
  return lista;
}


void agregar_final_existente(GList resultado, GNodo* lista) {
  resultado->sig = lista;
  lista->ant = resultado;
}


// merge fusiona dos listas ordenadas y devuelve el resultado. Se utiliza como función auxiliar para merge_sort.
GList merge(GList listaL, GList listaR, FuncionComparadora comparar) {
  listaL->ant->sig = NULL; // Se apunta el siguiente del último elem. de cada lista a NULL.
  listaR->ant->sig = NULL;
  GList resultado;
  GNodo *ultimo; // Nodo auxiliar que apuntará al último elemento de listaOrdenada.
  if (comparar(listaL->dato, listaR->dato) <= 0) { // Inicializo la lista a devolver según corresponda.
    resultado = listaL;
    listaL = listaL->sig;
  } else {
    resultado = listaR;
    listaR = listaR->sig;
  }
  GList listaOrdenada = resultado; // Lista a devolver.
  // Mientras las dos listas sean no vacías, las fusiona según el orden de los elementos.
  while (!gdclist_es_vacia(listaL) && !gdclist_es_vacia(listaR)) {
    if (comparar(listaL->dato, listaR->dato) <= 0) {
      agregar_final_existente(resultado, listaL);
      listaL = listaL->sig;
    } else {
      agregar_final_existente(resultado, listaR);
      listaR = listaR->sig;
    }
    resultado = resultado->sig;
  }
  // A lo sumo uno de los dos siguiente bucles se ejecutarán dependiendo de la lista de mayor longitud.
  // Se agregan los elementos restantes.
  while (!gdclist_es_vacia(listaL)) {
      agregar_final_existente(resultado, listaL);
      if (listaL->sig == NULL) {
        ultimo = listaL;
        listaL = listaL->sig;
      } else {
        listaL = listaL->sig;
        resultado = resultado->sig;
      }
  }
  while (!gdclist_es_vacia(listaR)) {
      agregar_final_existente(resultado, listaR);
      if (listaR->sig == NULL) {
        ultimo = listaR;
        listaR = listaR->sig;
      } else {
        listaR = listaR->sig;
        resultado = resultado->sig;
      }
  }
  agregar_final_existente(ultimo, listaOrdenada); // Se apunta el último nodo al primero de la lista a devolver.
  return listaOrdenada;
}

/* Merge Sort ordena una lista dividiendo sus elementos en dos mitades, llamándose a sí misma recursivamente 
y luego fusionando las dos sublistas ordenadas resultantes. El caso base del algoritmo sucede cuando la lista es unitaria. */
GList merge_sort(GList lista, FuncionComparadora comparar) {
  GList listaOrdenada;
  int longitud  = gdclist_longitud(lista);
  if (longitud == 1 || gdclist_es_vacia(lista)) // Caso base.
    listaOrdenada = lista;
  else {
    GList izqOrdenado = lista;
    GList derOrdenado;
    GNodo* temp = lista;
    int mitad = (longitud % 2 == 0) ? (longitud / 2) : (longitud / 2 + 1); // mitad indica la posición del primer elemento de la sublista derecha.
    for (int i = 0; i < mitad-1; i++) {
      temp = temp->sig;
    } // Ahora temp apunta al primer nodo de la sublista derecha.
    derOrdenado = temp->sig; // Se guardan las posiciones a reemplazar en izqOrdenado para derOrdenado.
    GNodo *finalLista2 = izqOrdenado->ant;
    temp->sig = izqOrdenado;
    izqOrdenado->ant = temp;
    finalLista2->sig = derOrdenado;
    derOrdenado->ant = finalLista2;
    // Ya quedaron determinadas las dos sublistas, por lo que ahora sucede la recursión.
    izqOrdenado = merge_sort(izqOrdenado, comparar);
    derOrdenado = merge_sort(derOrdenado, comparar);
    listaOrdenada = merge(izqOrdenado, derOrdenado, comparar); // Se fusionan las sublistas ordenadas mediante la función auxiliar merge.
  }
  return listaOrdenada;
}
