# include <string.h>
# include <stdio.h>
# include <math.h>
# include "gdclist.h"


/* 
Retorna un entero menor que, igual a, o mayor que 0 , si el primer argumento es considerado, 
respectivamente, menor que, igual a o mayor que el segundo.
*/
typedef int (*FuncionComparadora) (void *dato1, void *dato2);

GList selectionSort(GList lista, FuncionComparadora func) {
    
}

GList insertionSort(GList lista, FuncionComparadora compare) { 
  GNodo *inicio = lista->sig;
  GNodo *temp, *temp2;
  for (int i = 1; i < gdclist_longitud(lista); i++) {
    temp = temp2 = inicio;
    for (int j = i-1; 0 <= j; j--) {
      if (0 < compare(temp2->ant->dato, temp->dato)) {
        gdclist_intercambiar(inicio, i, j);

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
