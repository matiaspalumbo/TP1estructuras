#ifndef __ALGORITMOS_H__
#define __ALGORITMOS_H__

#include <stddef.h>
#include "gdclist.h"

typedef struct {
  char *nombre;
  int edad;
  char *lugarDeNacimiento; //pais o capital
} Persona;


// Definición del tipo de la función comparadora de dos elementos de una lista.
typedef int (*FuncionComparadora) (void *dato1, void *dato2);

// Compara dos numeros, retorna -1 si num1<num2
int compEdades(void* num1, void* num2);

// Compara dos arreglos de char 
int comparaStrings(void *str1, void *str2);

// Ordena una lista utilizando Selection Sort
GList selectionSort(GList lista, FuncionComparadora comparar);

// Ordena una lista utilizando Insertion Sort
GList insertionSort(GList lista, FuncionComparadora comparar);

// Ordena una lista utilizando Merge Sort
// GList mergeSort(GList lista, FuncionComparadora comparar) {
//   if (!gdclist_es_vacia(lista)) {
    
//   }
//   return lista;
// }




// MERGE SORT pseudocodigo
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





#endif /* __ALGORITMOS_H */