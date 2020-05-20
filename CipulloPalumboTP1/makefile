# Makefile para el Trabajo Practico I de Estructuras de Datos y Algoritmos I

# Macros.
PROG1 = programa1
PROG2 = programa2
LISTAS = gdclist.c
ALGORITMOS = algoritmos.c
PERSONA = persona.c
FLAGS = -Wall -Wextra -Werror -std=c99 -g


# Destino simbólico que actualiza todos los ejecutables con una sola llamada.
all : $(PROG1) $(PROG2)

# Ejecutable del programa 1.
$(PROG1) : $(PROG1).c
	gcc $(FLAGS) -o $@ $^

# Archivo objeto de la implementacion de listas generales.
$(LISTAS:.c=.o) : $(LISTAS) $(LISTAS.c=.h)
	gcc $(FLAGS) -c $(LISTAS)

# Archivo objeto de la implementacion de los algoritmos de ordenación.
$(ALGORITMOS:.c=.o) : $(ALGORITMOS) $(ALGORITMOS:.c=.h) $(LISTAS:.c=.h)
	gcc $(FLAGS) -c $(ALGORITMOS)

# Archivo objeto de la implementación de funciones con la estructura Persona.
$(PERSONA:.c=.o) : $(PERSONA) $(PERSONA:.c=.h)
	gcc $(FLAGS) -c $(PERSONA)

# Ejecutable de programa 2.
$(PROG2) : $(PROG2).c $(LISTAS:.c=.o) $(ALGORITMOS:.c=.o) $(PERSONA:.c=.o)
	gcc $(FLAGS) -o $@ $^

# Destino simbólico que borra todos los archivos con extensión .o cuando se invoca.
clean: 
	rm *.o

.PHONY : all
.PHONY : clean