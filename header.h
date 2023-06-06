#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ESTRUCTURAARCHIVOS
{
    FILE *punteroArchivo;
} Archivo; // Para definir un puntero a este dato user "malloc(sizeof(Archivo));"

// Estructura para representar un punto en el plano cartesiano
typedef struct
{
    int x;
    int y;
} Punto;

void inicia(char nick[]);
void visualizarConfiguracion(char nick[]);
void configurarParametros(char nick[]);
void verEstadisticas();
void jugarPartida(char nick[]);
void mostrarAyuda();
void iniciaMatriz(const int fila, const int colum, int matriz[][colum]);
void leeConfiguracion(int *ancho, int *alto, char nick[]);
void iniciaMatriz(const int fila, const int colum, int matriz[][colum]);
int verificarCuadrado(int ancho, int alto, int matriz[alto][ancho], int valor);
void juegaUser(int fila, int columna, int matriz[fila][columna]);
void imprimeMatrizFormat(int filas, int columnas, int Matriz[][columnas]);
double calcularDistancia(Punto p1, Punto p2);
int verificarCuadrado(Punto p1, Punto p2, Punto p3, Punto p4);

Archivo *abreArchivoGenerico(char nombreArchivo[], char modo[]);
