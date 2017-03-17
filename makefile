# Makefile para compilar el comando tls.

# Variables
CC = gcc
CFLAGS = -g -Wall -Wextra
OBJS = main.o directorios.o librerias.o colas.o

# Regla all
all: tls

# Creacion del ejecutable

tls: $(OBJS)
	gcc $(CFLAGS) -o tls $(OBJS) -lpthread

# Creación de los Object-Files (.o)
main.o: main.c directorios.o
	gcc $(CFLAGS) -c main.c

directorios.o: directorios.h colas.o
	gcc $(CFLAGS) -c directorios.c

colas.o: colas.h librerias.o
	gcc $(CFLAGS) -c colas.c

librerias.o: librerias.h
	gcc $(CFLAGS) -c librerias.c

# Clean

clean: 
	rm -f tls $(OBJS)