# Makefile para el Trabajo Practico I de Estructuras de Datos y Algoritmos I

# Macros.
PROG1 = programa1
PROG2 = programa2
LISTAS = gdclist.c
ALGORITMOS = algoritmos.c
PERSONAS = persona.c


# Destino simbólico que actualiza todos los ejecutables con una sola llamada.
all : $(PROG1) $(PROG2)

# Ejecutable del programa 1.
$(PROG1) : $(PROG1).c
	gcc $(CFLAGS) -o $@ $^

# Archivo objeto de la implementacion de listas generales.
$(LISTAS:.c=.o) : $(LISTAS) $(LISTAS.c=.h)
	gcc -c $(LISTAS)

# Archivo objeto de la implementacion de los algoritmos de ordenación.
$(ALGORITMOS:.c=.o) : $(ALGORITMOS) $(ALGORITMOS:.c=.h) $(LISTAS:.c=.h)
	gcc -c $(ALGORITMOS)

# Archivo objeto de la implementación de funciones con la estructura Persona.
$(PERSONAS:.c=.o) : $(PERSONAS) $(PERSONAS:.c=.h)
	gcc -c $(PERSONAS)

# Ejecutable de programa 2.
$(PROG2) : $(PROG2).c $(LISTAS:.c=.o) $(ALGORITMOS:.c=.o) $(PERSONAS:.c=.o)
	gcc $(CFLAGS) -o $@ $^

# Destino simbólico que borra todos los archivos con extensión .o cuando se invoca.
clean: 
	rm *.o