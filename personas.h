#ifndef __PERSONAS_H__
#define __PERSONAS_H__

#include <stddef.h>

/* Archivo de cabecera de la implementación de funciones auxiliares
sobre la estructura Persona. */


typedef struct { // Estructura de una Persona.
  char *nombre;
  int edad;
  char *lugarDeNacimiento; //(pais o ciudad)
} Persona;


// Toma un puntero a void que es una Persona y libera su espacio el memoria.
void destruir_persona(void *dato);

void imprimir_edad(void * dato); // BORRAR

// Función del tipo FuncionComparadora. Compara dos numeros.
int comp_edades(void *persona1, void *persona2);

// Función del tipo FuncionComparadora. Compara dos arreglos de char.
int comp_nombres(void *persona1, void *persona2);


#endif /* __PERSONAS_H__ */