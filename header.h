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

typedef struct JUGADOR
{
    char nick[100];
    int partidasJugadas;
    int partidasGanadas;
    int partidasPeridas;
    int partidasEmpatadas;
} Jugador;

typedef struct REGISTRO
{
    char nick[100];
    int puntaje;
} RegistroRanking;

void inicia(char nick[]);
void visualizarConfiguracion(char nick[]);
void configurarParametros(char nick[]);
void verEstadisticas(char nick[]);
void jugarPartida(char nick[]);
void mostrarAyuda();
void iniciaMatriz(Matriz *matriz);
void leeConfiguracion(int *ancho, int *alto, char nick[]);
void imprimeMatrizFormat(Matriz matriz);
Matriz *inicializaMatriz(int filas, int columnas);
Punto *jugar(int valor, Matriz *tablero, int automatico);
void imprimeJugadas(Punto puntos[], int longitud);
int evaluaJugadas(Punto jugadas[], int longitud);
double calcularDistancia(Punto p1, Punto p2);
int combinatoria(int n, int k);
void liberarCombinaciones(Punto **Combinaciones, int cantidadCombinaciones);
void almacenarCombinaciones(Punto jugadas[], int cantJugadas, int indiceActual, Punto combinacion[], int indiceCombinacion, Punto **Combinaciones, int *cantidadCombinaciones);
void liberarCombinaciones(Punto **Combinaciones, int cantidadCombinaciones);
int esCuadrado(Punto *combinacion, int longitudArray);
void ordIntecambio(double arreglo[], int longitud);
char valoresIguales(double arreglo[], int longitud);
Punto *IA(Matriz tablero);
int enteroAleatorio(int limite);
int calcularMinimaCantidad(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada);
int ArribaIz(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada);
int ArribaDer(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada);
int abajoDer(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada);
int AbajoIz(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada);
int DiagonalAbajo(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada);
int DiagonalArriba(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada);
int DiagonalIzq(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada);
int DiagonalDer(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada);
void guardarPartida(char nick[], int resultado, int cantidadJugadas);
Jugador *leeResultados(char NombreArchivo[]);
void guardarResultados(char nombreArchivo[], Jugador jugador);
void guardarEnRanking(char nombre[], int puntaje);
void leerRanking(RegistroRanking ranking[], int dimencion);
void ordIntecambioRegistosRanking(RegistroRanking arreglo[], int longitud);
int evalTablero(Matriz tablero);
int evaluarfila(Matriz tablero, int filaEval);
int evaluarColumna(Matriz tablero, int columnaEval);
Archivo *abreArchivoGenerico(char nombreArchivo[], char modo[]);
