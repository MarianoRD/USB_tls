// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include <signal.h> // No necesario
#include <sys/types.h> // No necesario
//#include <sys/wait.h> // No necesario
//#include <pwd.h> // No necesario
//#include <grp.h> // No necesario
//#include <time.h> // No necesario
//#include <langinfo.h> // No necesario
//#include <elf.h> // No necesario
//#include <libgen.h> // No necesario

// Macros
#define PATH_MAX 4096    // Cantidad de caracteres (max) de una ruta absoluta.
#define NAME_MAX 255    // Cantidad de caracteres (max) de un nombre de archivo.
#define STR_MAX 6000
#define ARCHIVOS_MAX 21
#define BYTES_MAX 21

// Typedefs
typedef enum {false, true} boolean;
typedef char String[STR_MAX];

// Funciones
void imprimeAyuda();
void verificarEscritura(char *str);
int verificarPermisosRX(char *str);