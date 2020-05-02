# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <wchar.h>
# include "gdclist.h"
# include "algoritmos.h"

/* Archivo del código fuente de la implementación de los algoritmos de ordenación
sobre listas generales doblemente enlazadas circulares y algunas funciones auxiliares. */


enum Letra{
  espacio = -1,
  a = 0,
  b = 1,
  c = 2,
  d = 3,
  e = 4,
  f = 5,
  g = 6,
  h = 7,
  i = 8,
  j = 9,
  k = 10,
  l = 11,
  m = 12,
  n = 13,
  enie = 14,
  o = 15,
  p = 16,
  q = 17,
  r = 18,
  s = 19,
  t = 20,
  u = 21,
  v = 22,
  w = 23,
  x = 24,
  y = 25,
  z = 26,
};

enum Letra convertirLetra(char c) {
  enum Letra val;
  if (c >= 65 && c <= 78)
    val = c - 65;
  else if (c >= 78 && c <= 90)
    val = c - 64;
  else if (c == 32)
    val = -1;
  else if (c < 0)
    val = 14;
  else val = 99;
  return val;
}

int compNombres(void *persona1, void *persona2) {
  char *s1 = ((Persona*)persona1)->nombre, *s2 = ((Persona*)persona2)->nombre;
  int val = 0, prevChar1 = 0, prevChar2 = 0;
  // int len = (strlen(s1) < strlen(s2)) ? strlen(s1) : strlen(s2);
  enum Letra char1, char2;
  int i = 0, j = 0;
  while (s1[i] != '\0' && s2[j] != '\0' && val == 0) {
    if (prevChar1 < 0) {
      // printf("prevChar1: %d - char1 anterior: %d\n", prevChar1, char1);
      prevChar1 = 1;
      i++;
    }
    else if (prevChar2 < 0) {
      // printf("prevChar2: %d - char2 anterior: %d\n", prevChar2, char2);
      prevChar2 = 1;
      j++;
    }
    else {
      char1 = convertirLetra(s1[i]);
      char2 = convertirLetra(s2[j]);
      // printf("s1[i]: %d char1: %d --- s2[j]: %d char2: %d  ---- %d\n", s1[i], char1, s2[j], char2, char1 < char2);
      if (char1 < char2) val = -1;
      else if (char1 > char2) val = 1;
      else val = 0;
      prevChar1 = s1[i];
      prevChar2 = s2[j];
      i++;
      j++;
    }
  }
  // printf("Resultado: %s < %s === %d\n", s1, s2, val);
  // puts("---------");
  // if (val == 0) val = compEdades(persona1, persona2);
  return val;
  // return wcscmp(s1, s2);
}




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

// // Compara dos arreglos de char 
// int compNombres(void *persona1, void *persona2) {
//   wchar_t *s1 = ((Persona*)persona1)->nombre, *s2 = ((Persona*)persona2)->nombre;
//   int val = 0, prevChar = 0;
//   int len = (strlen(s1) < strlen(s2)) ? strlen(s1) : strlen(s2);
//   for (int i = 0; i < len; i++) printf("%d - %d\n", s1[i], s2[i]);
//   for (int i = 0; (i < len) && (val == 0); i++) {
//     if (s1[i] < s2[i]) val = -1;
//     else if (s1[i] > s2[i]) val = 1;
//     else val = 0;
//   }
//   if (val == 0) val = compEdades(persona1, persona2);
//   return val;
//   return wcscmp(s1, s2);
// }

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
    izqOrdenado = mergeSort(izqOrdenado, comparar);
    // printf("ListaR: "); gdclist_recorrer(derOrdenado, imprimir_edad); puts("");
    derOrdenado = mergeSort(derOrdenado, comparar);
    listaOrdenada = merge(izqOrdenado, derOrdenado, comparar);
  }
  return listaOrdenada;
}
