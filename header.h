#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ESTRUCTURAARCHIVOS
{
    FILE *punteroArchivo;
} Archivo; // Para definir un puntero a este dato user "malloc(sizeof(Archivo));"

typedef struct MATRIZ
{
    int fila;
    int columna;
    int **matriz;
} Matriz;
// Estructura para representar un punto en el plano cartesiano
typedef struct PUNTO
{
    int x;
    int y;
} Punto;

typedef struct JUGADAS
{
    Punto *posiciones;
    int cantidadJugadas;
} Jugadas;

void inicia(char nick[]);
void visualizarConfiguracion(char nick[]);
void configurarParametros(char nick[]);
void verEstadisticas();
void jugarPartida(char nick[]);
void mostrarAyuda();
void iniciaMatriz(Matriz *matriz);
void leeConfiguracion(int *ancho, int *alto, char nick[]);
void imprimeMatrizFormat(Matriz matriz);
Matriz *inicializaMatriz(int filas, int columnas);
// Punto *jugar(int valor, int fila, int col, int matriz[][col]);

Archivo *abreArchivoGenerico(char nombreArchivo[], char modo[]);
