# Makefile para el Trabajo Practico I de Estructuras de Datos y Algoritmos I

NOMBRES = nombres1.txt
PAISES = paises.txt
PERSONAS = personas.txt
NUM = 1000 # numero de personas que se piden crear
FINAL = resultado.txt # archivo con el resultado final de programa2
LISTAS = gdclist.c


# ejecutable de programa 1
programa1 : programa1.c $(NOMBRES) $(PAISES)
	gcc -Wall -Werror -Wextra -o $@ programa1.c

# ejecuta programa1 con los correspondientes argumentos del main
$(PERSONAS) : programa1 $(NOMBRES) $(PAISES)
	programa1 $(NOMBRES) $(PAISES) $@ $(NUM)

# archivo objeto de la implementacion de listas generales
gdclist.o : gdclist.c gdclist.h
	gcc -c gdclist.c

# archivo objeto de la implementacion de los algoritmos de ordenación
algoritmos.o : algoritmos.c algoritmos.h gdclist.h
	gcc -c algoritmos.c

# ejecutable de programa2
programa2 : programa2.c $(PERSONAS) gdclist.o algoritmos.o
	gcc -Wall -Werror -Wextra -o $@ programa2.c gdclist.o algoritmos.o 
	
# ejecuta programa2 con los correspondientes argumnetos del main
# $(FINAL) : programa2 $(PERSONAS)
# 	./programa2 $(PERSONAS) $@

clean: 
	rm *.o