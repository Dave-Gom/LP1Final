#include "header.h"

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
    leeConfiguracion(&ancho, &alto, nick);
    int turno = 0;
    int valor;
    int resultado = 0;
    printf("\n Tablero de %dx%d", alto, ancho);
    printf("\n Tablero de %dx%d", alto, ancho);
    int tablero[alto][ancho];
    iniciaMatriz(alto, ancho, tablero);
    imprimeMatrizFormat(alto, ancho, tablero);
    do
    {
        if (turno % 2 == 0)
        {
            printf("Juega user");
            juegaUser(alto, ancho, tablero);
            valor = 1;
            turno++;
        }
        else
        {
            printf("Juega IA");
            valor = 2;
            turno++;
        }

        imprimeMatrizFormat(alto, ancho, tablero);

        // Verificar cuadrado después de actualizar el turno en la matriz
        resultado = verificarCuadrado(ancho, alto, tablero, valor);
        if (resultado == 1)
        {
            printf("\n SI: %d", resultado);
        }
        else
        {
            printf("\n NO: %d", resultado);
        }

    } while (resultado == 0);
}

void mostrarAyuda()
{
    printf("Has seleccionado la opción: Ayuda.\n");
    // Agrega aquí el código para mostrar la ayuda
}

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
void iniciaMatriz(const int fila, const int colum, int matriz[][colum])
{
    int i, j;
    for (i = 0; i < fila; i++)
    {
        for (j = 0; j < colum; j++)
            matriz[i][j] = 0;
    }
}

int verificarCuadrado(int ancho, int alto, int matriz[alto][ancho], int valor)
{
    int contador = 0;

    for (int i = 0; i < alto; i++)
    {
        for (int j = 0; j < ancho; j++)
        {
            if (matriz[i][j] == valor)
            {
                // Verificar si se encuentra el valor en las cuatro esquinas del cuadrado
                if (i > 0 && j > 0 && matriz[i - 1][j - 1] == valor && matriz[i - 1][j] == valor && matriz[i][j - 1] == valor)
                {
                    contador++;
                }
                if (i > 0 && j < ancho - 1 && matriz[i - 1][j + 1] == valor && matriz[i - 1][j] == valor && matriz[i][j + 1] == valor)
                {
                    contador++;
                }
                if (i < alto - 1 && j > 0 && matriz[i + 1][j - 1] == valor && matriz[i + 1][j] == valor && matriz[i][j - 1] == valor)
                {
                    contador++;
                }
                if (i < alto - 1 && j < ancho - 1 && matriz[i + 1][j + 1] == valor && matriz[i + 1][j] == valor && matriz[i][j + 1] == valor)
                {
                    contador++;
                }
            }
        }
    }

    if (contador >= 4)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void juegaUser(int fila, int columna, int matriz[fila][columna])
{
    int i, j;

    do
    {
        printf("Ingrese la fila (0-%d): ", fila - 1);
        scanf("%d", &i);
        printf("Ingrese la columna (0-%d): ", columna - 1);
        scanf("%d", &j);

        if (i < 0 || i >= fila || j < 0 || j >= columna)
        {
            printf("Posición inválida. Intente nuevamente.\n");
        }
        else
        {
            if (matriz[i][j] != 0)
            {
                printf("Posición ocupada. Intente nuevamente.\n");
            }
        }
    } while (i < 0 || i >= fila || j < 0 || j >= columna || matriz[i][j] != 0);

    matriz[i][j] = 1;
}

/**
 * @brief Imprimie una matriz formateada en forma de Table
 *
 * @param filas Cantidad de filas
 * @param columnas Cantidad de columnas
 * @param Matriz Matriz a ser impresa
 */
void imprimeMatrizFormat(int filas, int columnas, int Matriz[][columnas])
{
    int i;
    int j;

    printf("\n\nEste es el tablero:\n\n");
    for (i = 0; i < filas; i++)
    {
        for (j = 0; j < columnas; j++)
        {
            printf("%d ", Matriz[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

// Función para calcular la distancia entre dos puntos
double calcularDistancia(Punto p1, Punto p2)
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

// Función para verificar si los puntos forman un cuadrado
int verificarCuadrado(Punto p1, Punto p2, Punto p3, Punto p4)
{
    double d12 = calcularDistancia(p1, p2);
    double d13 = calcularDistancia(p1, p3);
    double d14 = calcularDistancia(p1, p4);
    double d23 = calcularDistancia(p2, p3);
    double d24 = calcularDistancia(p2, p4);
    double d34 = calcularDistancia(p3, p4);

    // Verificar si hay dos distancias iguales y una distancia mayor que las otras dos
    if ((d12 == d34 && d13 == d24 && d14 > d12 && d14 > d13) ||
        (d13 == d24 && d12 == d34 && d14 > d13 && d14 > d12) ||
        (d14 == d23 && d12 == d34 && d13 > d14 && d13 > d12))
    {

        // Verificar los ángulos formados por los segmentos entre los puntos
        double angulo = fabs(atan2(p2.y - p1.y, p2.x - p1.x) - atan2(p4.y - p1.y, p4.x - p1.x));
        if (fabs(angulo - M_PI / 2) < 1e-6)
        {
            return 1; // Los puntos forman un cuadrado
        }
    }

    return 0; // Los puntos no forman un cuadrado
}