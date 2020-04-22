# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <assert.h>
# include <wchar.h>
#include <locale.h>
#include <ctype.h>

#define MAX_STR_SIZE 70

// ESJNAER;JGNAERJN ;AEJ 

typedef struct {
  char *nombre;
  int edad;
  char *lugarDeNacimiento; //pais o capital
} Persona;

int contarLineas(FILE *fp) { // Función que cuenta la cantidad de líneas del archivo que se pasa como argumento.
  int lineas_fp = 0;
  char linea[MAX_STR_SIZE]; // Tamaño de línea elegido acorde a los archivos que estamos usando.
  while (! feof(fp)) { // fgets lee hasta encontrar un "\n", por lo tanto el bucle lee línea a línea y por cada una aumenta el contador. 
    fgets(linea, MAX_STR_SIZE, fp);
    if (! feof(fp)) lineas_fp += 1; 
    // La condición del if será falsa en la última iteración y de esta forma no contará lineas de más, suponiendo que todas las líneas incluyen un "\n" al final. 
  }
  return lineas_fp;
}

char **leerArchivo(char *file, int *len_file){
  FILE *fp_archivo;
  fp_archivo = fopen(file, "r"); // Abre el archivo pasado como parametro.
  *len_file = contarLineas(fp_archivo); // Cuenta la cantidad de líneas del archivo.
  rewind(fp_archivo);

  char **arreglo = malloc(sizeof(char*) * (*len_file));
  char junk[MAX_STR_SIZE];
  int length_string;
  int line = 0;
  while (! feof(fp_archivo)) {
    fgets(junk, MAX_STR_SIZE, fp_archivo);
    length_string = strlen(junk);
    for (int  i = 0; i<length_string; i++) {
      if (junk[i] == '\r' || junk[i] == '\n') junk[i] = '\0'; // si algún caracter no es alfabético, termina el string ahí
    }
    arreglo[line] = malloc(sizeof(char) * (length_string+1));
    strcpy(arreglo[line], junk);
    line++;
  }
  fclose(fp_archivo);
  return arreglo;
}



void escribirPersonas(char **nombres, char **paises, int nPersonas, int len_nombres, int len_paises, char *file) {
  FILE *fp_salida;
  fp_salida = fopen(file, "w");
  
  srand(time(0)); // Establece la seed del random igual al tiempo actual, lo que asegura que la secuencia de números generada sea distinta en cada ejecución del programa.
  Persona *persona = malloc(sizeof(Persona));
  for (int i = 0; i < nPersonas; i++) {
    persona->nombre = nombres[rand() % len_nombres];
    persona->edad = (rand() % 100) + 1;
    persona->lugarDeNacimiento = paises[rand() % len_paises];
    // printf("%s, %d, %s\n", persona->nombre, persona->edad, persona->lugarDeNacimiento);
    fprintf(fp_salida, "%s, %d, %s\n", persona->nombre, persona->edad, persona->lugarDeNacimiento);
  }
  free(persona);
  fclose(fp_salida);
}


int main(int argc, char **argv) {
  /*
  argv[0] es el nombre del ejecutable
  argv[1] es nombres1.txt
  argv[2] es paises.txt
  argv[3] es el nombre del archivo de salida
  argv[4] es un entero que representa la cantidad de personas a generar
*/
  // setlocale(LC_ALL, "es_ES");
  // printf("locale: %s\n", setlocale(LC_ALL, ""));
  assert(argc == 5);
  int len_nombres, len_paises;
  int nPersonas = atoi(argv[4]);
  char **nombres = leerArchivo(argv[1], &len_nombres);
  char **paises = leerArchivo(argv[2], &len_paises);
  escribirPersonas(nombres, paises, nPersonas, len_nombres, len_paises, argv[3]);
  // for (int i =0 ; i<10; i++) printf("%s", nombres[i]);
  for (int i = 0; i < len_nombres; i++) free(nombres[i]);
  for (int i = 0; i < len_paises; i++) free(paises[i]);
  free(nombres);
  free(paises);
  return 0;
}