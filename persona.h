#ifndef __PERSONA_H__
#define __PERSONA_H__

#include <stddef.h>

/* Archivo de cabecera de la implementación la estructura que representará
 a una persona y sus funciones auxiliares. */


typedef struct { // Estructura de una Persona con nombre, edad y lugar de nacimiento de la misma.
  char *nombre;
  int edad;
  char *lugarDeNacimiento;
} Persona;


// Toma un puntero a void (que es una Persona) y libera su espacio el memoria.
void destruir_persona(void *dato);

void imprimir_edad(void * dato); // BORRAR


// FuncionComparadora que compara las edades de dos personas.
int comp_edades(void *persona1, void *persona2);

// FuncionComparadora que compara los nombres de dos personas.
int comp_nombres(void *persona1, void *persona2);


#endif /* __PERSONA_H__ */