# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <assert.h>


#define MAX_STR_SIZE 70  // Constante para la longitud de los strings auxiliares para leer archivos.
#define MAX_EDAD 100 // Constante que determina la edad máxima de cada persona


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
  // Recibe una archivo y un puntero a int para guardar su longitud en líneas.
  FILE *archivo;
  archivo = fopen(file, "r"); // Abre el archivo pasado como parametro.
  *len_file = contarLineas(archivo); // Cuenta la cantidad de líneas del archivo.
  rewind(archivo); // Vuelve al inicio del arhcivo.

  // Crea un arreglo de punteros a char de la longitud del archivo para leer cada línea.
  char **arreglo = malloc(sizeof(char*) * (*len_file));
  char junk[MAX_STR_SIZE]; // String auxiliar para leer cada línea.
  int length_string;
  int line = 0; // Contador de las líneas.

  while (! feof(archivo)) { // El bucle itera hasta que se llegue al final del archivo.
    fgets(junk, MAX_STR_SIZE, archivo); // Lee una línea.
    length_string = strlen(junk); // Calcula su longitud en cantidad de caracteres.
    for (int  i = 0; i < length_string; i++) {
      // Si algún caracter no es alfabético, ubica el final del string en esa posición.
      if (junk[i] == '\r' || junk[i] == '\n') junk[i] = '\0'; 
    }
    // Le asigna un el espacio en memoria correspondiente a la línea leida en el arreglo creado.
    arreglo[line] = malloc(sizeof(char) * (length_string+1));
    strcpy(arreglo[line], junk); // Copia la línea en el arreglo.
    line++; // Pasa a la proxima línea.
  }

  fclose(archivo); // Cierra el archivo.
  return arreglo; // Retorna el arreglo con todas las líneas del archivo.
}


int generarRandom(unsigned long long* prodRand, long* rand1, long* rand2, int upperLimit) {
  *rand1 = rand();
  *rand2 = rand();
  *prodRand = *rand1 * *rand2;
  // printf("random: %llu\n", *prodRand%upperLimit);
  return (int) (*prodRand % upperLimit);
}


void escribirPersonas(char **nombres, char **paises, int nPersonas, int len_nombres, int len_paises, char *file) {
  /* Función que crea las Personas y las imprime en el archivo de salida. 
  Recibe los arreglos con nombres y paises/ciudades, sus longitudes, la cantidad 
  de Personas a crear y el archivo de salida en el cual escribirlas. */
  FILE *fp_salida;
  fp_salida = fopen(file, "w"); // Abre el archivo en el cual escribir las Personas que crea.
  /* Establece la seed del random igual al tiempo actual, lo que asegura que la secuencia 
  de números generada sea distinta en cada ejecución del programa. */
  srand(time(0)); 
  unsigned long long prodRand;
  long rand1, rand2;
  
  char *nombre, *lugarDeNacimiento;
  int edad;
  for (int i = 0; i < nPersonas; i++) {
    /* Por cada iteración calcula 3 números random dentro del rango correspondiente 
    que representan el índice del nombre, la edad, y el índice del pais/ciudad de la 
    Persona a crear, respectivamente, y le asigna el valor a cada variable de la Persona. */
    nombre = nombres[generarRandom(&prodRand, &rand1, &rand2, len_nombres)];
    edad = generarRandom(&prodRand, &rand1, &rand2, MAX_EDAD) + 1;
    lugarDeNacimiento = paises[generarRandom(&prodRand, &rand1, &rand2, len_paises)];
    // Luego la imprime en el archivo en el formato acordado.
    fprintf(fp_salida, "%s, %d, %s\n", nombre, edad, lugarDeNacimiento);
  }
  fclose(fp_salida); // Cierra el archivo.
}


int main(int argc, char **argv) {
  /*
  argc == 5
  argv[0] es el nombre del ejecutable
  argv[1] es nombres1.txt
  argv[2] es paises.txt
  argv[3] es el nombre del archivo de salida
  argv[4] es un entero que representa la cantidad de personas a generar
*/
  assert(argc == 5);

  // Longitudes de los archivos con nombres y paises respectivamente (en cantidad de líneas).
  int len_nombres, len_paises;
  int nPersonas = atoi(argv[4]); // Cantidad de Personas que hay que crear.
  // Arreglo con todos los nombres para crear las Personas.
  char **nombres = leerArchivo(argv[1], &len_nombres);
  // Arreglo con todos los paises y ciudades para crear las Personas.
  char **paises = leerArchivo(argv[2], &len_paises);


  escribirPersonas(nombres, paises, nPersonas, len_nombres, len_paises, argv[3]);

  // Libera los espacios de memoria asignados con malloc.
  for (int i = 0; i < len_nombres; i++) free(nombres[i]);
  for (int i = 0; i < len_paises; i++) free(paises[i]);
  free(nombres);
  free(paises);
  return 0;
}