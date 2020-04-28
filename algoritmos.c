# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "gdclist.h"
# include "algoritmos.h"


void imprimir_edad(void * dato) {
  printf("%d  ", ((Persona*) dato)->edad);
}


void destruir_persona(void *dato) {
  Persona *persona = (Persona*)dato;
  free(persona->nombre);
  free(persona->lugarDeNacimiento);
  free(persona);
}

// Compara dos numeros, retorna -1 si num1<num2
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
  return val;
}

// UNA OPCION DE SELECTION SORT (INC.)
// GList selectionSort(GList lista, FuncionComparadora comparar) {
//   if (!gdclist_es_vacia(lista)) {
//     int longitud = gdclist_longitud(lista);
//     int i = 0, j;
//     int primerElemento = lista;
//     for (GNodo* temp1 = lista; temp1->sig != primerElemento; temp1 = temp1->sig) {
//       void* minimo = i;
//       j = i + 1;
//       for (GNodo* temp2 = temp1->sig; temp2->sig != primerElemento; temp2 = temp2->sig) {
//         if (comparar(temp2->dato, temp1->dato) < 0)
//           minimo = j;
//         j++;
//       }
//       if (minimo != i) {
//         gdclist_intercambiar(lista, i, minimo);
//         primerElemento = 
//       }
//       i++;
//     }
//   }
//   return lista;
// }

// the best (i think) shot at selection sort


// GList selectionSort(GList lista, FuncionComparadora comparar) {
//   if (!gdclist_es_vacia(lista)) {
//     int indiceMinimo, longitud = gdclist_longitud(lista);
//     for (int i = 0; i < longitud - 1; i++) {
//       indiceMinimo = i;
//       for (int j = i + 1; j < longitud; j++) {
//         if (comparar(gdclist_leer(lista, j), gdclist_leer(lista, indiceMinimo)) < 0) {
//           indiceMinimo = j;
//         }
//       }
//       if (gdclist_leer(lista, indiceMinimo) != gdclist_leer(lista, i)) {
//         lista = gdclist_intercambiar(lista, i, indiceMinimo);
//       }
//     }
//   }
//   return lista;
// }


GList selectionSort(GList lista, FuncionComparadora comparar) {
  if (!gdclist_es_vacia(lista)) {
    GNodo *nodoMinimo = lista, *nodoAComparar, *nodoActual = lista;
    int longitud = gdclist_longitud(lista), indiceMinimo;
    for (int i = 0; i < longitud - 1; i++) {
      indiceMinimo = i;
      nodoMinimo = nodoActual;
      nodoAComparar = nodoActual->sig;
      for (int j = i + 1; (j < longitud); j++) {
        if (comparar(nodoAComparar->dato, nodoMinimo->dato) < 0) {
          nodoMinimo = nodoAComparar;
          indiceMinimo = j;
        }
        nodoAComparar = nodoAComparar->sig;
      }
      if (nodoActual != nodoMinimo)
        lista = gdclist_intercambiar(lista, i, indiceMinimo);
      nodoActual = nodoActual->sig;
    }
  }
  return lista;
}


GList insertionSort(GList lista, FuncionComparadora comparar) { 
  if (!gdclist_es_vacia(lista)) {
    GNodo *nodoActual = lista, *nodoAComparar, *ultimoOrdenado;
    int aux, j, longitud = gdclist_longitud(lista);
    for (int i = 1; i < longitud; i++) {
      aux = i;
      j = aux-1;
      ultimoOrdenado = nodoActual;
      nodoAComparar = nodoActual->sig;
      while (0 <= j) {
        if (0 < comparar(nodoActual->dato, nodoAComparar->dato)) {
          lista = gdclist_intercambiar(lista, j, aux);
          aux--;
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
  listaL->ant->sig = NULL;
  listaR->ant->sig = NULL;
  GList resultado = NULL;

  while (!gdclist_es_vacia(listaL) && !gdclist_es_vacia(listaR)) {
    if (comparar(gdclist_leer(listaL, 0), gdclist_leer(listaR, 0)) <= 0) {
      resultado = gdclist_agregar_final(resultado, listaL->dato);
      listaL = listaL->sig;
    } else {
      resultado = gdclist_agregar_final(resultado, listaR->dato);
      listaR = listaR->sig;
    }
  }
  // Only one of the following loops will actually be entered.
  while (!gdclist_es_vacia(listaL)) {
    resultado = gdclist_agregar_final(resultado, listaL->dato);
    listaL = listaL->sig;
  }
  while (!gdclist_es_vacia(listaR)) {
    resultado = gdclist_agregar_final(resultado, listaR->dato);
    listaR = listaR->sig;
  }
  return resultado;
}


GList mergeSort(GList lista, FuncionComparadora comparar) { // Ordena hasta la posicion limite inclusive
  GList listaOrdenada;
  if (gdclist_longitud(lista) == 1 || gdclist_es_vacia(lista))
    listaOrdenada = lista;
  else {
    GList izqOrdenado = gdclist_crear();
    GList derOrdenado = gdclist_crear();
    int mitad = (ceil(((double) gdclist_longitud(lista)) / 2.0));
    GNodo* temp = lista;
    for (int i = 0; i < gdclist_longitud(lista); i++) {
      if (i < mitad)
        izqOrdenado = gdclist_agregar_final(izqOrdenado, temp->dato);
      else
        derOrdenado = gdclist_agregar_final(derOrdenado, temp->dato);
      temp = temp->sig;
    }
    izqOrdenado = mergeSort(izqOrdenado, comparar);
    derOrdenado = mergeSort(derOrdenado, comparar);
    listaOrdenada = merge(izqOrdenado, derOrdenado, comparar);
    }
  return listaOrdenada;
}

