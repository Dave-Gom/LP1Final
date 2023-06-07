#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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
Punto *jugar(int valor, Matriz *tablero, int automatico);
void imprimeJugadas(Punto puntos[], int longitud);
int evaluaJugadas(Punto jugadas[],int longitud, int valor);
long long int factorial(long long int);
double calcularDistancia(Punto p1, Punto p2);
void generateSubsets(Punto Jugadas[], int cantidadJugadas, Punto *Combinaciones[], int cantComb);
int combinatoria(int n, int k);
Punto **subConjuntos(Punto puntos[], int longitud, int cantidadElementosSubConjunto);
int subConjuntoRepetido(Punto **array, int longitud, Punto* subCon, int dimSubcon);
Archivo *abreArchivoGenerico(char nombreArchivo[], char modo[]);
