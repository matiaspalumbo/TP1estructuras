# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <assert.h> 

typedef int (*FuncionComparadora) (void* dato1, void* dato2);

typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
  struct _GNodo *ant;
} GNodo;

typedef GNodo *GList;

typedef struct {
  char *nombre;
  int edad;
  char *lugarDeNacimiento; //pais o capital
} Persona;
