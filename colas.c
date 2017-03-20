// Librerias
#include "colas.h"

/*----------------------------------------------------------------------------*/
/*                                Funciones                                   */
/*----------------------------------------------------------------------------*/

/*
  Inicializa una cola vacía
*/
void inicializarMultiCola(multiCola *colas) {
  // Inicializa directorios
  (colas->directorios).cantNodos = 0;
  (colas->directorios).primero = (colas->directorios).ultimo = NULL;
  // Inicializa Strings
  (colas->strings).cantNodos = 0;
  (colas->strings).primero = (colas->strings).ultimo = NULL;
}

/*
  Agrega un elemento al final de la cola
*/
void pushCola(Cola *cola, String *str) {
  // Crea el nuevo elemento
    Nodo *temp;
    temp = (Nodo *) malloc(sizeof(Nodo));
    // Inicializo los datos del nodo
    strcpy(temp->str, *str);
    temp->siguiente = NULL;
  // Actualiza los apuntadores de la cola
    if (cola->cantNodos == 0) {
      cola->ultimo = cola->primero = temp;
    } else {
      cola->ultimo->siguiente = temp;
      cola->ultimo = temp;
    };
  // Aumenta la cantidad de elementos en la cola
    cola->cantNodos += 1;

  return;
};

/*
  Saca un elemento de la cola
*/
void popCola(Cola *cola, String *str) {
  // Inicializa variables
    Nodo *temp;
  // Saca el elemento de la cola
    if (cola->cantNodos == 0) {
      printf("No hay elementos en la cola.\n");
      strcpy(*str, "");
    } else {
      // Saca el elemento
      temp = cola->primero;
      cola->primero = cola->primero->siguiente;
      cola->cantNodos -= 1;
      strcpy(*str, temp->str);
      // Libera la memoria
      free(temp);
    }

  return;
}

/*
  Chequea si la cola está vacía y devuelve un booleano
*/
boolean colaVacia(Cola *cola) {
  if (cola->cantNodos == 0) {
    return 1;
  } else {
    return 0;
  };
}