// Librerias
#include "librerias.h"

/*----------------------------------------------------------------------------*/
/*                                Funciones                                   */
/*----------------------------------------------------------------------------*/

/*
    Imprime la información de uso del programa tls
*/
void imprimeAyuda() {
    printf("\n\nAyuda para tls:\n");
    
    // Sección Nombre
    printf("\nNOMBRE:\n");
    printf("\t\ttls v-0.0.1-a\n");
    // Sección uso
    printf("\nUSO:\n");
    printf("\t\t ./tls [-h] | [-n i] [-d directorio] [ salida ] \n");
    // Sección Descripción
    printf("\nDESCRIPCIÓN:\n");
    printf("\t\t Muestra la cantidad de archivos y los bytes que estos ocupan"
            "en un directorio, incluidos sus sub-directorios.\n");
    // Seccion de Opciones
    printf("\nOPCIONES:\n");
    printf("\t -h \t Imprime la ayuda del programa. \n");
    printf("\t -n \t Selecciona la cantidad de hilos, que van a ejecutar el "
            "programa (por defecto n = 1).\n");
    printf("\t -d \t Cambia el directorio de ejecución del programa por el "
            "directorio pasado.\n");
    printf("\t[ salida ] \t Cambia la salida a un archivo con el nombre pasado "
            "que se guarda en '/tmp'.\n");
    // Sección Ejemplo
    printf("\nEJEMPLOS:\n");
    printf("\t\t./tls -h\n");
    printf("\t\t./tls salida\n");
    printf("\t\t./tls -n 4 salida\n");
    printf("\t\t./tls -d /tmp -n 8 salida\n");
    printf("\t\t./tls\n");
    // Sección Autor
    printf("AUTORES:\n");
    printf("\t\t Gonzalez, Pablo - 13-10575\n");
    printf("\t\t Rodríguez, Mariano - 12-10892\n");
    printf("\n");


};

/*
    Verifica que se tengan los permisos de escritura en la ruta dada.
*/
void verificarEscritura(char *str) {
    if(access(str, W_OK) == 0) {
        return;
    } else {
        return;
        printf("No se puede crear el reporte en el directorio escogido.\n");
        printf("El programa terminará.\n");
        exit(-1);
    }
}

/*
    Verifica que se tengan los permisos de lectura y ejecución en la ruta
    dada en el string.
*/
int verificarPermisosRX(char *str) {
    if((access(str, R_OK) == 0) && (access(str, X_OK) == 0)) {
        return 0;
    } else {
        return 1;
    }
}