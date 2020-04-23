# include <string.h>
# include <stdio.h>
# include <math.h>
# include "gdclist.h"


/* 
Retorna un entero menor que, igual a, o mayor que 0 , si el primer argumento es considerado, 
respectivamente, menor que, igual a o mayor que el segundo.
*/
typedef int (*FuncionComparadora) (void *dato1, void *dato2);


// Compara dos numeros, retorna -1 si num1<num2
int compNumeros(void* num1, void* num2) {
  int n1 = *(int*)num1, n2 = *(int*)num2;
  int val;
  if (n1 < n2) val = -1;
  else if (n1 > n2) val = 1;
  else val = 0;
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
    void* datoAComparar = NULL;
    void* minimo = NULL;
    void* nodoPivot = NULL;
    for (int i = 0; i < longitud - 1; i++) {
      // gdclist_recorrer(lista, imprimir_dato, DLIST_RECORRIDO_HACIA_ADELANTE); puts("");
      minimo = gdclist_leer(lista, i);
      nodoPivot = minimo;
      for (int j = i + 1; j < longitud; j++) {
        // printf("longitud: %d\n", longitud);
        // printf("%d\n", j);
        datoAComparar = gdclist_leer(lista, j);
        if (comparar(datoAComparar, minimo) < 0) { // si el elemento a comparar es menor al mínimo, éste se convierte en el nuevo mínimo.
          minimo = datoAComparar;
          indiceMinimo = j;
        }
      }
      if (minimo != nodoPivot) {
        printf("Iteración %d - Índice mínimo %d\n", i, indiceMinimo);
        gdclist_intercambiar(&lista, i, indiceMinimo);
      }
    }
  }
  return lista;
}


GList insertionSort(GList lista, FuncionComparadora compare) { 
  GNodo *inicio = lista->sig;
  GNodo *temp, *temp2;
  for (int i = 1; i < gdclist_longitud(lista); i++) {
    temp = temp2 = inicio;
    for (int j = i-1; 0 <= j; j--) {
      if (0 < compare(temp2->ant->dato, temp->dato)) {
        gdclist_intercambiar(&inicio, i, j);

      }
      temp2 = temp2->ant;
    }


    inicio = inicio->sig;
  }
  return lista;
}

//pseudocode
/*
procedure insertionSort( A : array of items )
   int holePosition
   int valueToInsert
	
   for i = 1 to length(A) inclusive do:
	
      // select value to be inserted 
      valueToInsert = A[i]
      holePosition = i
      
      // locate hole position for the element to be inserted 
		
      while holePosition > 0 and A[holePosition-1] > valueToInsert do:
         A[holePosition] = A[holePosition-1]
         holePosition = holePosition -1
      end while
		
      // insert the number at hole position 
      A[holePosition] = valueToInsert
      
   end for
	
end procedure
*/
