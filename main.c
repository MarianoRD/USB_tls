// Librerías
#include "directorios.h"

// Declaración de variables
int opt;
char salida[NAME_MAX];
int n = 1;
char dirInicial[PATH_MAX];
char rutaSalida[PATH_MAX];
String strRaiz;
Directorio raiz;
boolean boolDirInicial = false;
multiCola colas;

// Main
int main(int argc, char* argv[]) {

  // Procesa los posibles flags
    while ((opt = getopt(argc, argv, "hn:d:")) != -1) {
      switch (opt) {
        case 'h':
          // Imprime ayuda
          imprimeAyuda();
          exit(0);
          break;
        case 'n':
          // Cantidad de hilos
          n = atoi(optarg);
          break;
        case 'd':
          // Directorio
          strcpy(dirInicial, optarg);
          boolDirInicial = true;
          break;
        default:
          printf("Uso: ./tls [-h] | [-n i] [-d directorio] [ salida ]\n");
      }
    };

  // Inicializo las colas
    inicializarMultiCola(&colas);
  // Crea el arreglo que va a contener el ID de los hilos
    pthread_t arregloHilos[n];

  // Si hay un documento de salida, guarda la información
    if (argv[optind] != NULL) {
      strcpy(salida, argv[optind]);
    } else {
      strcpy(salida, "");
    };

  // Si hay una 'dirInicial' (-d) cambia el directorio
    if (boolDirInicial) {
      getcwd(rutaSalida, PATH_MAX);
      chdir(dirInicial);
    } else {
      getcwd(dirInicial, PATH_MAX);
    };

  // Verifica que se pueda escribir el reporte en el directorio
    verificarEscritura(rutaSalida);

  // Explora el directorio padre
    strcpy(raiz.rutaAbs, dirInicial);
    informacionArchivos(&raiz, &(colas.directorios));

  // Agrega el directorio raiz a la cola
    creaStr(&raiz, strRaiz);
    pushCola(&(colas.strings), &strRaiz);

  // Crea los hilos
    crearHilos(n, arregloHilos, &colas);

  // Espera a que los hilos finalicen <------------------------------------------
    for (int i = 0; i < n; i++){
        pthread_join(arregloHilos[i], NULL);
    }

  // Imprime toda la información recolectada
    crearReporte(rutaSalida, &(colas.strings), salida);

  // Finaliza el programa
    printf("\nPrograma terminó con éxito\n");
    return 0;

}