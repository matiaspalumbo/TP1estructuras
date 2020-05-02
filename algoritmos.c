# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "gdclist.h"
# include "algoritmos.h"

/* Archivo del código fuente de la implementación de los algoritmos de ordenación
sobre listas generales doblemente enlazadas circulares y algunas funciones auxiliares. */


GList selection_sort(GList lista, FuncionComparadora comparar) {
  if (!gdclist_es_vacia(lista)) {
    GNodo *nodoMinimo, *nodoAComparar, *nodoActual = lista;
    int longitud = gdclist_longitud(lista);
    for (int i = 0; i < longitud - 1; i++) {
      nodoMinimo = nodoActual;
      nodoAComparar = nodoActual->sig;
      for (int j = i + 1; j < longitud; j++) {
        if (comparar(nodoAComparar->dato, nodoMinimo->dato) < 0) {
          nodoMinimo = nodoAComparar;
        }
        nodoAComparar = nodoAComparar->sig;
      }
      if (nodoActual != nodoMinimo)
        lista = gdclist_intercambiar(lista, nodoActual, nodoMinimo);
      nodoActual = nodoActual->sig;
    }
  }
  return lista;
}

GList insertion_sort(GList lista, FuncionComparadora comparar) { 
  if (!gdclist_es_vacia(lista)) {
    GNodo *nodoActual = lista, *nodoAComparar, *ultimoOrdenado;
    int j, longitud = gdclist_longitud(lista);
    for (int i = 1; i < longitud; i++) {
      j = i - 1;
      ultimoOrdenado = nodoActual;
      nodoAComparar = nodoActual->sig;
      while (j >= 0) {
        if (comparar(nodoAComparar->dato, nodoActual->dato) < 0) {
          lista = gdclist_intercambiar(lista, nodoActual, nodoAComparar);
          j--;
          nodoActual = nodoActual->ant;
          nodoAComparar = nodoAComparar->ant;
        } else j = -1;
      }
      nodoActual = ultimoOrdenado->sig;
    }
  }
  return lista;
}

GList merge(GList listaL, GList listaR, FuncionComparadora comparar) {
  // printf("Listas a mergear - L: "); gdclist_recorrer(listaL, imprimir_edad); printf("R: "); gdclist_recorrer(listaR, imprimir_edad); puts("");
  listaL->ant->sig = NULL;
  listaR->ant->sig = NULL;
  GList resultado;
  GNodo *ultimo;
  if (comparar(listaL->dato, listaR->dato) <= 0) {
    resultado = listaL;
    listaL = listaL->sig;
  } else {
    resultado = listaR;
    listaR = listaR->sig;
  }
  GList listaOrdenada = resultado;
  while (!gdclist_es_vacia(listaL) && !gdclist_es_vacia(listaR)) {
    // printf("ola - ");
    if (comparar(listaL->dato, listaR->dato) <= 0) {
      resultado->sig = listaL;
      listaL->ant = resultado;
      listaL = listaL->sig;
    } else {
      resultado->sig = listaR;
      listaR->ant = resultado;
      listaR = listaR->sig;
    }
    resultado = resultado->sig;
  }
  while (!gdclist_es_vacia(listaL)) {
    // printf("L - ");
      resultado->sig = listaL;
      listaL->ant = resultado;
      if (listaL->sig == NULL) {
        ultimo = listaL;
        listaL = listaL->sig;
      } else {
        listaL = listaL->sig;
        resultado = resultado->sig;
      }
  }
  while (!gdclist_es_vacia(listaR)) {
    // printf("R - ");
    // gdclist_recorrer(listaR, imprimir_edad); puts("");
      resultado->sig = listaR;
      listaR->ant = resultado;
      if (listaR->sig == NULL) {
        ultimo = listaR;
        listaR = listaR->sig;
      } else {
        listaR = listaR->sig;
        resultado = resultado->sig;
      }
  }
  ultimo->sig = listaOrdenada;
  listaOrdenada->ant = ultimo;
  // printf("Resultado: "); gdclist_recorrer(listaOrdenada, imprimir_edad); puts("");
  // printf("ultimo: %d\n", ((Persona*) ultimo->dato)->edad);
  return listaOrdenada;
}

GList merge_sort(GList lista, FuncionComparadora comparar) {
  GList listaOrdenada;
  int longitud  = gdclist_longitud(lista);
  if (longitud == 1 || gdclist_es_vacia(lista))
    listaOrdenada = lista;
  else {
    GList izqOrdenado = lista;
    GNodo* temp = lista;
    int mitad = (longitud % 2 == 0) ? (longitud / 2) : (longitud / 2 + 1);
    // int mitad = ceil((double) gdclist_longitud(lista) / 2.0);
    for (int i = 0; i < mitad-1; i++) {
      temp = temp->sig;
    }
    GList derOrdenado = temp->sig; // guardo las posiciones a reemplazar en izqOrdenado para derOrdenado
    GNodo *finalLista2 = izqOrdenado->ant;
    temp->sig = izqOrdenado;
    izqOrdenado->ant = temp;
    finalLista2->sig = derOrdenado;
    derOrdenado->ant = finalLista2;
    // printf("ListaL: "); gdclist_recorrer(izqOrdenado, imprimir_edad); puts("");
    izqOrdenado = merge_sort(izqOrdenado, comparar);
    // printf("ListaR: "); gdclist_recorrer(derOrdenado, imprimir_edad); puts("");
    derOrdenado = merge_sort(derOrdenado, comparar);
    listaOrdenada = merge(izqOrdenado, derOrdenado, comparar);
  }
  return listaOrdenada;
}
