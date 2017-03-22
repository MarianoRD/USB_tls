// Librerias
#include "directorios.h"
#include <errno.h>

/*----------------------------------------------------------------------------*/
/*                                Funciones                                   */
/*----------------------------------------------------------------------------*/

/* 
  Cuenta cuantos archivos y sub-directorios posee un directorio y cuantos
  bytes ocupan dichos archivos (sin contar los directorios)
*/
void informacionArchivos(Directorio *directorio, Cola *colaDir) {
  // Variables
  struct dirent *fd;
  struct stat info;
  String str;

  // Revisa que se tengan los permisos necesarios en el directorio
  if(verificarPermisosRX(directorio->rutaAbs) == 1) {
    printf("No se pudo leer/ejecutar en: %s\n", directorio->rutaAbs);
    return;
  };
  // Abre el directorio
  directorio->dir = opendir(directorio->rutaAbs);
  // Cuenta solamente los archivos
  while ((fd = readdir(directorio->dir)) != NULL) {
    // Concateno la ruta absoluta
      strcpy(str, "");
      strcat(str, directorio->rutaAbs);
      strcat(str, "/");
      strcat(str, fd->d_name);
    // Saco el stat
    if(stat(str, &info) == -1) {
      // Errores
      printf("ERROR: %s\n", strerror(errno));
      // Fin errores
      printf("Error stat(), informacionArchivos(), directorios.c\n");
    };
    // No cuenta los archivos ocultos
    if (fd->d_name[0] == '.') {
      continue;
    }
    if (S_ISDIR(info.st_mode)) {
      // Agrego el elemento a la cola
      pthread_mutex_lock(&colaDir->mutex);
      pushCola(colaDir, &str);
      pthread_mutex_unlock(&colaDir->mutex);
    } else {
      (directorio->cantArchivos)++;
      directorio->bytes = directorio->bytes + info.st_size;
    };
  }
  // Cierra el directorio
  closedir(directorio->dir);
}


/*
  Crea el string que va a ser escrito en el reporte.
*/
void creaStr(Directorio *directorio, char *str){
  // Imprime de la información del directorio
  char archivos[ARCHIVOS_MAX];
  char bytes[BYTES_MAX];
  char hilo[BYTES_MAX];
  // Convierte los datos en str
  sprintf(archivos, "%d", directorio->cantArchivos);
  sprintf(bytes, "%u", directorio->bytes);
  sprintf(hilo, "%lu", directorio->hilo);
  // Creo el str
  strcpy(str, "");
  strcat(str, hilo);
  strcat(str, " | ");
  strcat(str, directorio->rutaAbs);
  strcat(str, " | ");
  strcat(str, archivos);
  strcat(str, " | ");
  strcat(str, bytes);
  strcat(str, "\n");

  return;
}

/*
  Crea el reporte del programa
*/
void crearReporte(char *rutaSalida, Cola *cola, char *nombreArchivoSalida) {
  // Inicializa las variables
  String str;
  FILE *archivo;
  // Guarda la ruta inicial de ejecución
  char rutaInicial[PATH_MAX];
  getcwd(rutaInicial, PATH_MAX);
  // Cambia a la carpeta de salida
  chdir(rutaSalida);
  // Verifica si la salida es por STD_OUT o a un archivo
  if (strcmp(nombreArchivoSalida, "") == 0) {
    archivo = stdout;
  } else {
    // Abre el archivo
    archivo = fopen(nombreArchivoSalida, "w");
  };
  // Escribe el archiv
  while(cola->cantNodos > 0) {
    popCola(cola, &str);
    fprintf(archivo, "%s", str);
    strcpy(str, "");
    fflush(archivo);
  }
  // Cierra el archivo
  if (strcmp(nombreArchivoSalida, "") != 0) {
    fclose(archivo);
  };
  // Regresa al directorio inicial
  chdir(rutaInicial);

  return;
}

/*
  Funcion que va a correr cada hilo, para verificar los sub-directorios
*/
void *hilosTrabajando(void *colasVoid) {

  multiCola *colas = (multiCola *) colasVoid;

  // Ciclo de trabajo mientras la cola de directorios no esté vacía
  while(colas->directorios.cantNodos != 0) {
    // Inicializa las variables
      Directorio directorioActual;
      String *strActual = (String *) malloc(sizeof(String));
    // Busca el directorio en la cola correspondiente
      pthread_mutex_lock(&(colas->directorios.mutex));
      if(colas->directorios.cantNodos == 0) {
        pthread_mutex_unlock(&(colas->directorios.mutex));
        break;
      };
      popCola(&(colas->directorios), &(directorioActual.rutaAbs));
      printf("Directorio: %s, \tCola: %d\n", directorioActual.rutaAbs, colas->directorios.cantNodos);
      pthread_mutex_unlock(&(colas->directorios.mutex));
    // Analiza el directorio
      informacionArchivos(&directorioActual, &(colas->directorios));
    // Agrega la información del hilo trabajador
      directorioActual.hilo = pthread_self();
    // Crea el str
      creaStr(&directorioActual, *strActual);
    // Agrega el str a la cola correspondiente
      pthread_mutex_lock(&(colas->strings.mutex));
      pushCola(&(colas->strings), strActual);
      pthread_mutex_unlock(&(colas->strings.mutex));
  };
  // Finaliza el hilo (la cola está vacía)
    pthread_exit(NULL);
    return 0;
};

/*
  Crea hilos
*/
void crearHilos(int n, pthread_t *arregloHilos, multiCola *colas) {
  int i;
  for (i = 0; i < n; i++) {
    pthread_create (&(arregloHilos[i]),NULL, hilosTrabajando, (multiCola *)colas);
    printf("Creado el hilo: %lu\n", arregloHilos[i]);
  }
  return;
};