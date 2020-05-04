# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <assert.h>

/* Constante para la longitud de los strings auxiliares en la lectura de archivos.
El tamaño fue elegido de acuerdo a los archivos con los que se trabajarán. */
#define MAX_STR_SIZE 70
// Constante que determina la edad máxima de cada persona.
#define MAX_EDAD 100


int contar_lineas(FILE *fp) { // Función que cuenta la cantidad de líneas del archivo que se pasa como argumento.
  int lineas_fp = 0;
  char linea[MAX_STR_SIZE];
  while (! feof(fp)) {
    // Se lee línea a línea y por cada una se aumenta el contador. 
    fgets(linea, MAX_STR_SIZE, fp);
    if (! feof(fp))
      lineas_fp += 1; 
    // La condición del if será falsa en la última iteración y de esta forma no contará lineas de más.
  }
  return lineas_fp;
}

char **leer_archivo(char *file, int *len_file){
  // Recibe una archivo, almacena sus lineas en un arreglo y guarda su longitud en len_file.
  FILE *archivo;
  archivo = fopen(file, "r");
  *len_file = contar_lineas(archivo);
  rewind(archivo);

  // Crea un arreglo de punteros a char de la longitud del archivo para leer cada línea.
  char **arreglo = malloc(sizeof(char*) * (*len_file));
  char junk[MAX_STR_SIZE]; // String auxiliar para leer cada línea.
  int length_string;
  int line = 0; // Contador de líneas.

  while (! feof(archivo)) { // Itera hasta que llegar al final del archivo.
    fgets(junk, MAX_STR_SIZE, archivo);
    length_string = strlen(junk);
    for (int  i = 0; i < length_string; i++) {
      // Ubica el final del string donde termina la línea.
      if (junk[i] == '\r' || junk[i] == '\n') junk[i] = '\0'; 
    }
    // Le asigna un el espacio en memoria correspondiente a la línea leida en el arreglo creado.
    arreglo[line] = malloc(sizeof(char) * (length_string+1));
    strcpy(arreglo[line], junk); // Copia la línea en el arreglo.
    line++;
  }

  fclose(archivo);
  return arreglo; // Retorna el arreglo creado.
}

/* Para evitar pérdidas de aleatoriedad en la elección de nombres debido a límites en RAND_MAX 
en diferentes sistemas operativos, para cada número aleatorio necesario se multiplican dos números
obtenidos de rand() y se devuelve el módulo de ese número con respecto a la cantidad de opciones 
(que será la cantidad de nombres o de lugares). */
int generar_random(long long *prodRand, long *rand1, long *rand2, int upperLimit) {
  *rand1 = rand();
  if ((*rand1) >= (long) upperLimit)
    return (int) (*rand1 % upperLimit);
  else {
    *rand2 = rand();
    *prodRand = *rand1 * *rand2;
    return (int) (*prodRand % upperLimit);
  }
}

void escribir_personas(char **nombres, char **lugares, int nPersonas, int len_nombres, int len_lugares, char *file) {
  /* Función que crea las Personas y las imprime en el archivo de salida. 
  Recibe los arreglos con nombres y lugares, sus longitudes, la cantidad 
  de Personas a crear y el archivo de salida en el cual escribirlas. */
  FILE *fp_salida;
  fp_salida = fopen(file, "w");
  /* Establece la seed del random igual al tiempo actual, lo que asegura que la secuencia 
  de números generada sea distinta en cada ejecución del programa. */
  srand(time(0)); 
  long long prodRand;
  long rand1, rand2;
  char *nombre, *lugarDeNacimiento;
  int edad;
  for (int i = 0; i < nPersonas; i++) {
    /* Por cada iteración calcula 3 números random dentro del rango correspondiente 
    que representan el índice del nombre, la edad, y el índice del pais/ciudad de la 
    Persona a crear, respectivamente, y le asigna el valor a cada variable de la persona. */
    nombre = nombres[generar_random(&prodRand, &rand1, &rand2, len_nombres)];
    edad = generar_random(&prodRand, &rand1, &rand2, MAX_EDAD) + 1;
    lugarDeNacimiento = lugares[generar_random(&prodRand, &rand1, &rand2, len_lugares)];
    // Luego la imprime en el archivo.
    fprintf(fp_salida, "%s, %d, %s\n", nombre, edad, lugarDeNacimiento);
  }
  fclose(fp_salida);
}

void libera_memoria(char **nombres, char **lugares, int len_nombres, int len_lugares) {
  // Libera los espacios de memoria asignados con malloc para los arreglos de nombres y lugares.
  for (int i = 0; i < len_nombres; i++) free(nombres[i]);
  for (int i = 0; i < len_lugares; i++) free(lugares[i]);
  free(nombres);
  free(lugares);
}

int main(int argc, char **argv) {
  /* argc siempre será igual a 5
  argv[0] es el nombre del ejecutable
  argv[1] es el nombre del archivo con nombres
  argv[2] es el nombre del archivo con lugares
  argv[3] es el nombre del archivo de salida
  argv[4] es un número que representa la cantidad de personas a generar */
  assert(argc == 5);

  // Cant. de líneas de los archivos con nombres y lugares respectivamente.
  int len_nombres, len_lugares;
  int nPersonas = atoi(argv[4]); // Cantidad de personas que hay que crear.
  char **nombres = leer_archivo(argv[1], &len_nombres); // Arreglo con todos los nombres posibles.
  char **lugares = leer_archivo(argv[2], &len_lugares); // Arreglo con todos los lugares posibles.
  // Se escriben las personas generadas en el archivo de salida.
  escribir_personas(nombres, lugares, nPersonas, len_nombres, len_lugares, argv[3]);
  // Se libera la memoria asignada.
  libera_memoria(nombres, lugares, len_nombres, len_lugares);
  return 0;
}