#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ESTRUCTURAARCHIVOS
{
    FILE *punteroArchivo;
} Archivo; // Para definir un puntero a este dato user "malloc(sizeof(Archivo));"

void inicia(char nick[]);
void visualizarConfiguracion(char nick[]);
void configurarParametros(char nick[]);
void verEstadisticas();
void jugarPartida();
void mostrarAyuda();

Archivo *abreArchivoGenerico(char nombreArchivo[], char modo[]);
