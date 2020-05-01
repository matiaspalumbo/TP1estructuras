# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "gdclist.h"
# include "algoritmos.h"

/* Archivo del código fuente de la implementación de los algoritmos de ordenación
sobre listas generales doblemente enlazadas circulares y algunas funciones auxiliares. */


void imprimir_edad(void *dato) { // BORRAR
  printf("%d  ", ((Persona*) dato)->edad);
}

void destruir_persona(void *dato) {
  Persona *persona = (Persona*)dato;
  free(persona->nombre);
  free(persona->lugarDeNacimiento);
  free(persona);
}

int compEdades(void *persona1, void *persona2) {
  int edad1 = ((Persona*)persona1)->edad, edad2 = ((Persona*)persona2)->edad;
  int val;
  if (edad1 < edad2) val = -1;
  else if (edad1 > edad2) val = 1;
  else val = 0;
  return val;
}

// Compara dos arreglos de char 
int compNombres(void *persona1, void *persona2) {
  char *s1 = ((Persona*)persona1)->nombre, *s2 = ((Persona*)persona2)->nombre;
  int val = 0;
  int len = (strlen(s1) < strlen(s2)) ? strlen(s1) : strlen(s2);
  for (int i = 0; (i < len) && (val == 0); i++) {
    if (s1[i] < s2[i]) val = -1;
    else if (s1[i] > s2[i]) val = 1;
    else val = 0;
  }
  if (val == 0) val = compEdades(persona1, persona2);
  return val;
}

GList selectionSort(GList lista, FuncionComparadora comparar) {
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

GList insertionSort(GList lista, FuncionComparadora comparar) { 
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

GList mergeSort(GList lista, FuncionComparadora comparar) {
  GList listaOrdenada;
  int longitud  = gdclist_longitud(lista);
  if (longitud == 1 || gdclist_es_vacia(lista))
    listaOrdenada = lista;
  else {
    GList izqOrdenado = lista;
    GNodo *temp = lista;
    int mitad = ceil((double) gdclist_longitud(lista) / 2.0);
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
    izqOrdenado = mergeSort(izqOrdenado, comparar);
    // printf("ListaR: "); gdclist_recorrer(derOrdenado, imprimir_edad); puts("");
    derOrdenado = mergeSort(derOrdenado, comparar);
    listaOrdenada = merge(izqOrdenado, derOrdenado, comparar);
  }
  return listaOrdenada;
}
