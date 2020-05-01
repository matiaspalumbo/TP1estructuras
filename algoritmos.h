#ifndef __ALGORITMOS_H__
#define __ALGORITMOS_H__

#include <stddef.h>
#include <wchar.h>
#include "gdclist.h"

/* Archivo de cabecera de la implementación de los algoritmos de ordenación 
Selection Sort, Insertion Sort y Merge Sort sobre listas generales doblemente
enlazadas circulares y algunas funciones auxiliares. */


typedef struct { // Estructura de una Persona.
  wchar_t *nombre;
  int edad;
  wchar_t *lugarDeNacimiento; //(pais o ciudad)
} Persona;


/* Declaración de un puntero a una función llamado FuncionComparadora que toma 
como argumentos dos punteros a void y retorna un int (entero). 
Retorna un entero menor que, igual a, o mayor que 0 , si el primer argumento 
es considerado, respectivamente, menor que, igual a o mayor que el segundo. */
typedef int (*FuncionComparadora) (void *dato1, void *dato2);

/* Declaración de un puntero a una función llamado AlgoritmoSorting que toma como 
argumneto una lista de tipo GList y una FuncionComparadora y retorna una lista de tipo GList. */
typedef GList (*AlgoritmoSorting) (GList lista, FuncionComparadora comparar);

// Toma un puntero a void que es una Persona y libera su espacio el memoria.
void destruir_persona(void *dato);

void imprimir_edad(void * dato); // BORRAR

// Función del tipo FuncionComparadora. Compara dos numeros.
int compEdades(void *persona1, void *persona2);

// Función del tipo FuncionComparadora. Compara dos arreglos de char.
int compNombres(void *persona1, void *persona2);

// Ordena una lista utilizando Selection Sort.
GList selectionSort(GList lista, FuncionComparadora comparar);

// Ordena una lista utilizando Insertion Sort.
GList insertionSort(GList lista, FuncionComparadora comparar);

// Ordena una lista utilizando Merge Sort.
GList mergeSort(GList lista, FuncionComparadora comparar);


#endif /* __ALGORITMOS_H */