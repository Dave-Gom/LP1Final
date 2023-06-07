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
    int arr[] = {1, 2, 3, 4, 5, 6}; // Reemplaza 'a', 'b', 'c', 'd', 'e', 'f' por los valores reales
    // int n = sizeof(arr) / sizeof(arr[0]);

    int n = 4; // Número de elementos en el arreglo

    // Crear el arreglo de puntos array
    Punto **array = malloc(n * sizeof(Punto *));
    for (int i = 0; i < n; i++) {
        array[i] = malloc(4 * sizeof(Punto));
    }

    // Rellenar el arreglo array con datos de prueba
    // Conjunto 1
    array[0][0].x = 1;
    array[0][0].y = 1;

    array[0][1].x = 2;
    array[0][1].y = 2;

    array[0][2].x = 3;
    array[0][2].y = 3;

    array[0][3].x = 4;
    array[0][3].y = 4;

    // Conjunto 2
    array[1][0].x = 5;
    array[1][0].y = 5;

    array[1][1].x = 6;
    array[1][1].y = 6;

    array[1][2].x = 7;
    array[1][2].y = 7;

    array[1][3].x = 8;
    array[1][3].y = 8;

    // Conjunto 3 (Repetido)
    array[2][0].x = 1;
    array[2][0].y = 1;

    array[2][1].x = 2;
    array[2][1].y = 2;

    array[2][2].x = 3;
    array[2][2].y = 3;

    array[2][3].x = 4;
    array[2][3].y = 4;

    // Conjunto 4
    array[3][0].x = 9;
    array[3][0].y = 9;

    array[3][1].x = 10;
    array[3][1].y = 10;

    array[3][2].x = 11;
    array[3][2].y = 11;

    array[3][3].x = 12;
    array[3][3].y = 12;

    // Rellenar el arreglo subCon con el subconjunto a buscar
    Punto subCon[4];
    subCon[0].x = 1;
    subCon[0].y = 1;

    subCon[1].x = 2;
    subCon[1].y = 2;

    subCon[2].x = 3;
    subCon[2].y = 3;

    subCon[3].x = 4;
    subCon[3].y = 4;

    int res = subConjuntoRepetido(array, n, subCon, 4);
    printf("El subconjunto está repetido: %d\n", res );
    // do
    // {
    //         JugadasJugador1[turno1] = *jugar(1, ptrTablero, 0);
    //         turno1++;
    //         imprimeJugadas(JugadasJugador1, turno1);
    //         evaluaJugadas(JugadasJugador1, turno1, 1);

    // } while ((turno1) != 5);
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

int evaluaJugadas(Punto jugadas[], int longitud, int valor){
    int i;
    if (longitud < 4)
    {
        return 0;
    }
    else{
        double cantidadCombinaciones = (factorial(longitud)) / ((factorial(longitud - 4) * factorial(4)));
        printf("\nla cantidad de combinaciones es: %f\n", cantidadCombinaciones);
        Punto **Combinaciones = malloc(cantidadCombinaciones * sizeof(Punto*));


        for ( i = 0; i < cantidadCombinaciones; i++) {
        printf("Combinacion %d: ", i + 1);
        for (int j = 0; j < 4; j++) {
            printf("(%d, %d) ", Combinaciones[i][j].x, Combinaciones[i][j].y);
        }
        printf("\n");
    }
        return 1;
    }
}

long long int factorial(long long int valor){
    printf("\nvalor: %lld", valor);
    long long int f = 0;
    if (valor == 0)
    {

        return 1;
    }
    else{
        f = valor * factorial(valor - 1);
        printf("\nf: %lld", f);
        return f;
    }
}

double calcularDistancia(Punto p1, Punto p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}



int combinatoria(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    } else {
        return combinatoria(n - 1, k - 1) + combinatoria(n - 1, k);
    }
}

Punto **subConjuntos(Punto puntos[], int longitud, int cantidadElementosSubConjunto){

    int i,j,k,l, encontrado;
    int cantComb = combinatoria(longitud, cantidadElementosSubConjunto);
    Punto **array = malloc(cantComb*sizeof(Punto *));
    Punto conjuntoAux[cantidadElementosSubConjunto];
    for (i = 0; i < cantComb; i++)
    {
        if(i == 0){
            for ( j = 0; j < cantidadElementosSubConjunto; j++)
            {
                array[i][j].x = puntos[j].x;
                array[i][j].y = puntos[j].y;
            }
        }
        else{
            while (array[i] == NULL)
            {
                for ( j = 0; j < i; j++)
                {
                    for ( k = 0; k < cantidadElementosSubConjunto; k++)
                    {
                        conjuntoAux[k].x = array[j]->x;
                        conjuntoAux[k].y = array[j]->y;
                    }
                    
                    for ( k = 0; k < cantidadElementosSubConjunto; k++)
                    {
                        for ( l = cantidadElementosSubConjunto; l < longitud; l++)
                        {
                            conjuntoAux[i].x = puntos[l].x;
                            conjuntoAux[i].y = puntos[l].y;
                            encontrado = subConjuntoRepetido(array, cantComb, conjuntoAux, cantidadElementosSubConjunto);
                            if(encontrado == 1){
                                break;
                            }
                        }

                    }
                    if(encontrado == 1){
                        break;
                    }
                }
                if(encontrado == 1){
                    for ( j = 0; j < cantidadElementosSubConjunto; j++)
                    {
                        array[i][j].x = conjuntoAux[j].x;
                        array[i][j].y = conjuntoAux[j].y;
                    }
                }

            }
        }
    }

    return array;
}


int subConjuntoRepetido(Punto **array, int longitud, Punto* subCon, int dimSubcon){
    int i, k, j;
    int existe[dimSubcon];
    int existeCon = 1;

    printf("Subconjunto: {");
    for (i = 0; i < dimSubcon; i++)
    {
        if(i != 0){
            printf(",");
        }
        existe[i] = 0;
        printf("(%d,%d)", subCon[i].x, subCon[i].y);
        
    }
    printf("}");

    for (i = 0; i < longitud; i++)
    {
        for (j = 0; j < dimSubcon; j++)
        {
            for ( k = 0; k < dimSubcon; k++)
            {
                if (subCon[k].x == array[i][j].x && subCon[k].y == array[i][j].y)
                {
                    existe[k] = 1;
                    break;
                }
            }
        }
        

        for ( j = 0; j < dimSubcon; j++)
        {
            if(existe[j] != 1){
                existeCon = 0;
                break;
            }
        }

        if(existeCon == 0){
            break;
        }
        
    }

    return existeCon;
}