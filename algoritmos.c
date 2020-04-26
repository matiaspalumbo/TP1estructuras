# include <string.h>
# include <stdio.h>
# include <math.h>
# include "gdclist.h"
# include "algoritmos.h"



void destruir_persona(void *dato) {
  Persona *persona = (Persona*)dato;
  free(persona->nombre);
  free(persona->lugarDeNacimiento);
  free(persona);
}

// Compara dos numeros, retorna -1 si num1<num2
int compEdades(void* persona1, void* persona2) {
  int edad1 = ((Persona*)persona1)->edad, edad2 = ((Persona*)persona2)->edad;
  int val;
  if (edad1 < edad2) val = -1;
  else if (edad1 > edad2) val = 1;
  else val = 0;
  return val;
}

// Compara dos arreglos de char 
int comparaStrings(void *str1, void *str2) {
  char *s1 = (char*)str1, *s2 = (char*)str2;
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

GList selectionSort(GList lista, FuncionComparadora comparar) {
  if (!gdclist_es_vacia(lista)) {
    int indiceMinimo, longitud = gdclist_longitud(lista);
    for (int i = 0; i < longitud - 1; i++) {
      indiceMinimo = i;
      for (int j = i + 1; j < longitud; j++) {
        if (comparar(gdclist_leer(lista, j), gdclist_leer(lista, indiceMinimo)) < 0) {
          indiceMinimo = j;
        }
      }
      if (gdclist_leer(lista, indiceMinimo) != gdclist_leer(lista, i)) {
        gdclist_intercambiar(&lista, i, indiceMinimo);
      }
    }
  }
  return lista;
}

GList insertionSort(GList lista, FuncionComparadora comparar) { 
  if (!gdclist_es_vacia(lista)) {
    int aux, j, longitud = gdclist_longitud(lista);
    for (int i = 1; i < longitud; i++) {
      aux = i;
      j = aux-1;
      while (0 <= j) {
        if (0 < comparar(gdclist_leer(lista, j), gdclist_leer(lista, aux))) {
          gdclist_intercambiar(lista, j, aux);
          aux--;
          j--;
        } else j = -1;
      }
    }
  }
  return lista;
}


GList mergeSort(GList lista, FuncionComparadora comparar) {
  if (!gdclist_es_vacia(lista)) {
    
  }
  return lista;
}
// MERGE SORT
// function merge(left, right) is
//     var result := empty list

//     while left is not empty and right is not empty do
//         if first(left) ≤ first(right) then
//             append first(left) to result
//             left := rest(left)
//         else
//             append first(right) to result
//             right := rest(right)

//     // Either left or right may have elements left; consume them.
//     // (Only one of the following loops will actually be entered.)
//     while left is not empty do
//         append first(left) to result
//         left := rest(left)
//     while right is not empty do
//         append first(right) to result
//         right := rest(right)
//     return result

// function merge_sort(node head) is
//     // return if empty list
//     if head = nil then
//         return nil
//     var node array[32]; initially all nil
//     var node result
//     var node next
//     var int  i
//     result := head
//     // merge nodes into array
//     while result ≠ nil do
//          next := result.next;
//          result.next := nil
//          for(i = 0; (i < 32) && (array[i] ≠ nil); i += 1) do
//               result := merge(array[i], result)
//               array[i] := nil
//          // do not go past end of array
//          if i = 32 then
//                i -= 1
//          array[i] := result
//          result := next
//     // merge array into single list
//     result := nil
//     for (i = 0; i < 32; i += 1) do
//          result := merge(array[i], result)
//     return result

