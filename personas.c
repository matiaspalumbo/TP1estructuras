# include <string.h>
# include <stdio.h>
# include "personas.h"

/* Archivo del código fuente de la implementación de funciones auxiliares
sobre la estructura Persona. */

int convertir_letra(char c) {
  int val;
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

int comp_nombres(void *persona1, void *persona2) {
  char *s1 = ((Persona*)persona1)->nombre, *s2 = ((Persona*)persona2)->nombre;
  int val = 0, prevChar1 = 0, prevChar2 = 0;
  int char1, char2;
  int i = 0, j = 0;
  while (s1[i] != '\0' && s2[j] != '\0' && val == 0) {
    if (prevChar1 < 0) {
      prevChar1 = 1;
      i++;
    }
    else if (prevChar2 < 0) {
      prevChar2 = 1;
      j++;
    }
    else {
      char1 = convertir_letra(s1[i]);
      char2 = convertir_letra(s2[j]);
      if (char1 < char2) val = -1;
      else if (char1 > char2) val = 1;
      else val = 0;
      prevChar1 = s1[i];
      prevChar2 = s2[j];
      i++;
      j++;
    }
  }
  return val;
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

int comp_edades(void *persona1, void *persona2) {
  int edad1 = ((Persona*)persona1)->edad, edad2 = ((Persona*)persona2)->edad;
  int val;
  if (edad1 < edad2) val = -1;
  else if (edad1 > edad2) val = 1;
  else val = 0;
  return val;
}

