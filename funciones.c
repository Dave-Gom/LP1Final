#include "header.h"


/**
 * @brief funcion central del juego, despliega el menu y decide que funcion llamar atendiendo a la seleccion del usuario
 * @param nick
 */
void inicia(char nick[])
{
    int opcion;
    printf("\nBienvenido %s\n", nick);
    do
    {

        printf("A continuación, muestra por pantalla el siguiente menú:\n");
        printf("1. Visualizar configuración del tablero.\n");
        printf("2. Configurar parámetros.\n");
        printf("3. Ver estadísticas.\n");
        printf("4. Jugar partida.\n");
        printf("5. Ayuda.\n");
        printf("6. Salir.\n");
        printf("Ingresa el número de la opción deseada: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            visualizarConfiguracion(nick);
            break;
        case 2:
            configurarParametros(nick);
            break;
        case 3:
            verEstadisticas();
            break;
        case 4:
            jugarPartida(nick);
            break;
        case 5:
            mostrarAyuda();
            break;
        case 6:
            printf("Gracias por usar el programa. ¡Hasta luego!\n");
            break;
        default:
            printf("Opción inválida. Por favor, ingresa un número del 1 al 6.\n");
        }

        printf("\n");
    } while (opcion != 6);
}


/**
 * @brief Lee la configuracion de dimension del tablero
 * @param nick
 */
void visualizarConfiguracion(char nick[])
{
    int ancho, alto;
    leeConfiguracion(&ancho, &alto, nick);
    if (ancho == 0 && alto == 0)
    {
        printf("Las dimensiones del tablero son: %d x %d\n", 10, 10);
    }
    else
    {
        printf("Las dimensiones del tablero son: %d x %d\n", ancho, alto);
    }
}

/**
 * @brief Carga los datos del tablero y los guarda en el archivo _configuracion.txt
 * @param nick
 */
void configurarParametros(char nick[])
{
    int ancho, alto;
    char nombreArchivo[100] = "";
    strcat(nombreArchivo, nick);
    strcat(nombreArchivo, "_configuracion.txt");

    Archivo *ptrConfiguracion = abreArchivoGenerico(nombreArchivo, "w");
    if (ptrConfiguracion != NULL)
    {
        do
        {
            printf("Ingrese el valor del ancho (menor o igual a 10): ");
            scanf("%d", &ancho);

            printf("Ingrese el valor del alto (menor o igual a 10): ");
            scanf("%d", &alto);

            if (ancho > 10 || alto > 10)
            {
                printf("Los valores ingresados deben ser menores o iguales 10. Por favor, inténtelo nuevamente.\n");
            }
        } while (ancho > 10 || alto > 10);

        fprintf(ptrConfiguracion->punteroArchivo, "Ancho=%d\n", ancho);
        fprintf(ptrConfiguracion->punteroArchivo, "Alto=%d\n", alto);
    }
    fclose(ptrConfiguracion->punteroArchivo);
    // Agrega aquí el código para configurar los parámetros
}

void verEstadisticas()
{
    printf("Has seleccionado la opción: Ver estadísticas.\n");
    // Agrega aquí el código para ver las estadísticas
}

void jugarPartida(char nick[])
{
    int ancho = 0, alto = 0;
    int turno1 = 0;
    int turno2 = 0;
    int valor;
    int resultado = 0;
    leeConfiguracion(&ancho, &alto, nick);
    Matriz *ptrTablero = inicializaMatriz(alto, ancho);
    iniciaMatriz(ptrTablero);
    imprimeMatrizFormat(*ptrTablero);
    Punto JugadasJugador1[(ancho * alto) / 2];
    Punto JugadasJugador2[(ancho * alto) / 2];

        do
        {
                JugadasJugador1[turno1] = *jugar(1, ptrTablero, 0);
                turno1++;
                imprimeJugadas(JugadasJugador1, turno1);
        } while ((turno1) != 5);
    /*     do
        {
            if((turno1 + turno2) % 2 == 0){

                turno1++;
            }
            else{
                printf("juega jugador 2 0 IA\n");
                turno2++;
            }
        } while ((turno1 + turno2) != 25); */
}

void mostrarAyuda()
{
    printf("Has seleccionado la opción: Ayuda.\n");
    // Agrega aquí el código para mostrar la ayuda
}


/**
 * @brief Abre o crea forzada un archivo dado su nombre y modo
 * @param nombreArchivo
 * @param modo
 * @return *Archivo
 *
 * @author David Gomez
 *
 */
Archivo *abreArchivoGenerico(char nombreArchivo[], char modo[])
{
    Archivo *ptrNuevoArchivo = malloc(sizeof(Archivo)); // inicializa el puntero al archivo en null
    char generico[100];
    if ((ptrNuevoArchivo->punteroArchivo = fopen(nombreArchivo, modo)) == NULL)
    {
        if ((ptrNuevoArchivo->punteroArchivo = fopen(nombreArchivo, "w+")) != NULL)
        {
            return ptrNuevoArchivo; // retorna el puntero al archivo si hubo exito
        }
        else
        {
            printf("No se pudo Abir Ni crear el archivo");
            return NULL;
        }
    }
    else
    {
        return ptrNuevoArchivo; // retorna el puntero al archivo si hubo exito
    }
}

/**
 * @brief lee la configuracion de archivo y la asigna a las variabler ancho y alto
 * @param ancho
 * @param alto
 * @param nick
 *
 * @author David Gomez
 *
 */
void leeConfiguracion(int *ancho, int *alto, char nick[])
{
    int primerValor, segundoValor;
    char anchoChar[20] = "", altoChar[20] = "";
    char nombreArchivo[100] = "";
    strcat(nombreArchivo, nick);
    strcat(nombreArchivo, "_configuracion.txt");
    Archivo *ptrConfiguracion = abreArchivoGenerico(nombreArchivo, "r");
    if (ptrConfiguracion != NULL && !feof(ptrConfiguracion->punteroArchivo))
    {
        fscanf(ptrConfiguracion->punteroArchivo, "%s", anchoChar);
        fscanf(ptrConfiguracion->punteroArchivo, "%s", altoChar);
        sscanf(anchoChar, "Ancho=%d", &primerValor);
        sscanf(altoChar, "Alto=%d", &segundoValor);
    }

    *ancho = primerValor;
    *alto = segundoValor;
    fclose(ptrConfiguracion->punteroArchivo);
}

/**
 * @brief Asigna el valor inicial 0 a todas las posiciones de la matriz
 *
 * @param fila Cantidad de filas de la matriz
 * @param colum Cantidad de columnas de la matriz
 * @param matriz Matriz a ser inicializada
 *
 * @author David Gomez
 */
void iniciaMatriz(Matriz *ptrMatriz)
{
    int i, j;
    for (i = 0; i < ptrMatriz->fila; i++)
    {
        for (j = 0; j < ptrMatriz->columna; j++)
            ptrMatriz->matriz[i][j] = 0;
    }
}




/**
 * @brief Imprimie una matriz formateada en forma de Table
 *
 * @param filas Cantidad de filas
 * @param columnas Cantidad de columnas
 * @param Matriz Matriz a ser impresa
 */
void imprimeMatrizFormat(Matriz matriz)
{
    int i;
    int j;

    printf("\n\nEste es el tablero:\n\n");
    for (i = 0; i < matriz.fila; i++)
    {
        for (j = 0; j < matriz.columna; j++)
        {
            printf("%d ", matriz.matriz[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}


Matriz *inicializaMatriz(int filas, int columnas){
    Matriz *ptrMatriz = malloc(sizeof(Matriz));
    int i;
    ptrMatriz->fila = filas;
    ptrMatriz->columna = columnas;
    ptrMatriz->matriz = malloc(filas * sizeof(int *));
    for ( i = 0; i < filas; i++)
    {
        ptrMatriz->matriz[i] = malloc(columnas * sizeof(int));
    }

    return ptrMatriz;
}

Punto *jugar(int valor, Matriz *tablero, int automatico){
    Punto *nuevoPunto = malloc(sizeof(Punto));
    printf("\nTurno jugador %d\n", valor);
    int x = 0, y = 0;
    if (automatico == 1)
    {
        //valores automaticos
    }
    else{
        do
        {
            printf("Ingrese la fila: ");
            scanf("%d", &x);

            printf("Ingrese la columna: ");
            scanf("%d", &y);

            if (x > tablero->columna || y > tablero->columna)
            {
                printf("Los valores ingresados deben ser menores o iguales 10. Por favor, inténtelo nuevamente.\n");
            }
        } while (x > tablero->columna || y > tablero->columna);
    }

    nuevoPunto->x = x;
    nuevoPunto->y = y;
    tablero->matriz[x][y] = valor;
    imprimeMatrizFormat(*tablero);
    return nuevoPunto;
}


void imprimeJugadas(Punto puntos[], int longitud){
    int i = 0;
    printf("{");
    for (i = 0; i < longitud; i++)
    {
        printf("(%d , %d ) ,", puntos[i].x, puntos[i].y);
    }
    printf("}");
    
}
