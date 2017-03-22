// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>

// Macros
#define PATH_MAX 4096    // Cantidad de caracteres (max) de una ruta absoluta.
#define NAME_MAX 255    // Cantidad de caracteres (max) de un nombre de archivo.
#define STR_MAX 6000
#define ARCHIVOS_MAX 21
#define BYTES_MAX 21

// Typedefs
typedef char String[STR_MAX];

// Funciones
void imprimeAyuda();
void verificarEscritura(char *str);
int verificarPermisosRX(char *str);