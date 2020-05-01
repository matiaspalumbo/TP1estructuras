# Makefile para el Trabajo Practico I de Estructuras de Datos y Algoritmos I

PROG1 = programa1
PROG2 = programa2
LISTAS = gdclist.c
ALGORITMOS = algoritmos.c


all : $(PROG1) $(PROG2)

# ejecutable de programa 1
$(PROG1) : $(PROG1).c
	$(CC) $(CFLAGS) -o $@ $^

# archivo objeto de la implementacion de listas generales
$(LISTAS:.c=.o) : $(LISTAS) $(LISTAS.c=.h)
	$(CC) -c $(LISTAS)

# archivo objeto de la implementacion de los algoritmos de ordenación
$(ALGORITMOS:.c=.o) : $(ALGORITMOS) $(ALGORITMOS:.c=.h) $(LISTAS:.c=.h)
	$(CC) -c $(ALGORITMOS)

# ejecutable de programa2
$(PROG2) : $(PROG2).c $(LISTAS:.c=.o) $(ALGORITMOS:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm *.o