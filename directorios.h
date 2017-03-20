// Librerias
#include "colas.h"

// Estructuras
typedef struct
{
  String rutaAbs;
  char nombre[NAME_MAX];
  DIR *dir;
  int cantArchivos;
  struct stat informacion;
  int bytes;
  pthread_t hilo;

} Directorio;

// Funciones
void informacionArchivos(Directorio *directorio, Cola *colaDir);
void creaStr(Directorio *directorio, char *str);
void crearReporte(char *rutaSalida, Cola *cola, char *nombreArchivoSalida);
void *hilosTrabajando(void *colasVoid);
void crearHilos(int n, pthread_t *arregloHilos, multiCola *colas);