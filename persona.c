# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include "persona.h"

/* Archivo del código fuente de la implementación de las funciones auxiliares
sobre la estructura Persona. */


void destruir_persona(void *dato) {
  Persona *persona = (Persona*)dato;
  free(persona->nombre);
  free(persona->lugarDeNacimiento);
  free(persona);
}

/* Función auxiliar de comparar_nombres, definida para asegurar el orden alfabético en los strings.
Considerando el alfabeto español ordenado con números del 0 al 26 (siendo el espacio igual a -1),
cada caracter del string a comparar se transforma en el número correspondiente mediante esta función.
Se consideran sólo letras mayúculas sin tilde ya que este es el criterio seguido en los nombres de personas. */
int convertir_letra(char c) {
  int val;
  if (c >= 65 && c <= 78) // si el caracter es anterior a la Ñ
    val = c - 65;
  else if (c >= 78 && c <= 90) // si el caracter es posterior a la Ñ
    val = c - 64;
  else if (c == 32) // si el caracter es un espacio
    val = -1;
  else if (c < 0)
    val = 14;
  else val = 99;
  return val;
}

/* Compara los nombres de dos personas alfabéticamente. Si hay una letra Ñ presente en un nombre,
al almacenarla en el string la memoria ocupada por el char 'Ñ' desborda la provista por el char 
destinado a su almacenamiento, por lo que aparece un número negativo al acceder a ese caracter, y además, 
ocupa dos char en el string, ambos negativos. Por esta razón (y por el hecho de que esto sucede sólo con ese caracter),
en convertir_letra se asume que si el código del char a convertir es negativo se trata de una Ñ. Para evitar conflictos
con los dos espacios de char ocupados por cada letra Ñ, si el char anterior al char que se compara es negativo, se omite.*/
int comp_nombres(void *persona1, void *persona2) {
  char *s1 = ((Persona*)persona1)->nombre, *s2 = ((Persona*)persona2)->nombre; // Strings a comparar.
  int val = 0, prevChar1 = 0, prevChar2 = 0;
  int char1, char2; // Variables utilizadas en la comparación.
  int i = 0, j = 0; // índices de s1 y s2, respectivamente.
  while (s1[i] != '\0' && s2[j] != '\0' && val == 0) { // El bucle itera hasta que los strings dejen de ser iguales o alguno termine.
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


// Compara las edades de dos personas.
int comp_edades(void *persona1, void *persona2) {
  int edad1 = ((Persona*)persona1)->edad, edad2 = ((Persona*)persona2)->edad;
  int val;
  if (edad1 < edad2) val = -1;
  else if (edad1 > edad2) val = 1;
  else val = 0;
  return val;
}

