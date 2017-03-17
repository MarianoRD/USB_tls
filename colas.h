// Librerias
#ifndef LIBRERIAS
  #include "librerias.h"
  #define LIBRERIAS
#endif

// Estructuras

typedef struct {
	String str;
	void *siguiente;
} Nodo;

typedef struct {
	Nodo *primero;
	Nodo *ultimo;
	int cantNodos;
	pthread_mutex_t mutex;
} Cola;

typedef struct {
	Cola directorios;
	Cola strings;
} multiCola;

// Funciones
void inicializarMultiCola(multiCola *colas);
void pushCola(Cola *cola, String *str);
void popCola(Cola *cola, String *str);
boolean colaVacia(Cola *cola);