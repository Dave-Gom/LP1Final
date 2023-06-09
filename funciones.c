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
    int resultado = 0;
    int bandera1 = 0, bandera2 = 0;
    leeConfiguracion(&ancho, &alto, nick);
    Matriz *ptrTablero = inicializaMatriz(alto, ancho);
    iniciaMatriz(ptrTablero);
    imprimeMatrizFormat(*ptrTablero);
    Punto JugadasJugador1[(ancho * alto) / 2];
    Punto JugadasJugador2[(ancho * alto) / 2];

    do
    {
        if((turno1 + turno2) % 2 == 0){
            JugadasJugador1[turno1] = *jugar(1, ptrTablero, 0);
            turno1++;
            bandera1= evaluaJugadas(JugadasJugador1, turno1);
            if (bandera1 == 1)
            {
                break;
            }
            
        }
        else{
            JugadasJugador2[turno2] = *jugar(2, ptrTablero, 0);
            turno2++;
            bandera2= evaluaJugadas(JugadasJugador2, turno1);
            if (bandera2 == 1)
            {
                break;
            }
        }
    } while ((turno1) != (ancho*alto)/2 || (turno2) != (ancho*alto)/2);

    if(bandera1 == bandera2){
        printf("\n¡Empate!\n");
    }
    else 
    {
        if (bandera1 == 1){
            printf("\n¡Gano el Jugador 1!\n");
        }

        if(bandera2 == 1){
            printf("\n¡Gano el Jugador 2!\n");
        }
    }
    
    
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

/*!
 * @brief agrega una jugada al tablero
 * @param valor 
 * @param tablero 
 * @param automatico 
 * @return 
 */
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

        if (x > tablero->columna || y > tablero->fila || y < 0 || x<0)
        {
            printf("Los valores ingresados deben ser menores o iguales 10. Por favor, inténtelo nuevamente.\n");
            continue;
        }

        if(tablero->matriz[x][y] != 0){
            printf("Casilla ocupada. Por favor, inténtelo nuevamente.\n");
            continue;
        }

    } while (x > tablero->columna || y > tablero->fila ||  y < 0 || x<0 || tablero->matriz[x][y] != 0);


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


/*!
 * @brief Evalua el array de jugadas
 * @param jugadas 
 * @param longitud 
 * @return 1 si hay un cuadrado, 0 en caso contrario
 */
int evaluaJugadas(Punto jugadas[], int longitud){
    int i;
    int bandera = 0;

    if (longitud >= 4){
        Punto** Combinaciones = malloc(combinatoria(longitud, 4) * sizeof(Punto*)); 
        int cantidadCombinaciones = 0;
        Punto combinacion[4];
        almacenarCombinaciones(jugadas, longitud, 0, combinacion, 0, Combinaciones, &cantidadCombinaciones);

        // Imprimir las combinaciones almacenadas
        for (int i = 0; i < cantidadCombinaciones; i++) {
            bandera = esCuadrado(Combinaciones[i], 4);
            if(bandera == 1){
                break;
            }
        }

        liberarCombinaciones(Combinaciones, cantidadCombinaciones); // liberamos la memoria del array de combinaciones 
    }

    return bandera;

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

void almacenarCombinaciones(Punto jugadas[], int cantJugadas, int indiceActual, Punto combinacion[], int indiceCombinacion, Punto** Combinaciones, int* cantidadCombinaciones) {
    if (indiceCombinacion == 4) {
        // Se han seleccionado 4 jugadas, almacenar la combinación en Combinaciones
        Punto* nuevaCombinacion = malloc(4 * sizeof(Punto));
        for (int i = 0; i < 4; i++) {
            nuevaCombinacion[i] = combinacion[i];
        }
        Combinaciones[*cantidadCombinaciones] = nuevaCombinacion;
        (*cantidadCombinaciones)++;
        return;
    }

    if (indiceActual >= cantJugadas) {
        // No hay más jugadas disponibles, terminar la recursión
        return;
    }

    // No seleccionar el punto actual y pasar al siguiente
    almacenarCombinaciones(jugadas, cantJugadas, indiceActual + 1, combinacion, indiceCombinacion, Combinaciones, cantidadCombinaciones);

    // Seleccionar el punto actual y pasar al siguiente
    combinacion[indiceCombinacion] = jugadas[indiceActual];
    almacenarCombinaciones(jugadas, cantJugadas, indiceActual + 1, combinacion, indiceCombinacion + 1, Combinaciones, cantidadCombinaciones);
}

void liberarCombinaciones(Punto** Combinaciones, int cantidadCombinaciones) {
    for (int i = 0; i < cantidadCombinaciones; i++) {
        free(Combinaciones[i]);
    }
    free(Combinaciones);
}


/*!
 * @brief Verifica si un array de 4 puntos se corresponde o no con los vertices de un Cuadrado
 * @param combinacion Array de Puntos (obligatoriamente de cuatro elementos)
 * @return 1 si es afirmativo 0 si no
 */
int esCuadrado(Punto *combinacion, int longitudArray){
    int i,j;
    double bandera1, bandera2;
    if(longitudArray == 4 ){
        double distancias[6]; // 4C2 = 6
        int index = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 4; j++) {
                distancias[index] = calcularDistancia(combinacion[i], combinacion[j]);
                index++;
            }
        }

        ordIntecambio(distancias, 6); // ordeno el array de menor a mayor

        bandera1 = valoresIguales(distancias, 4) == 's'? distancias[0]: 0; // asignamos el valor 0 porque estamos evaluando distancias, y no puede se que la distancia entre dos puntos que no son el mismo sea 0
        bandera2 = valoresIguales(&distancias[4], 2) == 's'? distancias[4]: 0;

        if(bandera1 != 0 && bandera2 != 0 && bandera1<bandera2){
            return 1;
        }

    }
    return 0;

}


/**
 * @brief Ordenamiento de intercambio. Ordena un array en orden ascendente por el metodo de intercambio de variables
 *
 * @param arreglo Arreglo a ser ordeneado
 * @param longitud Dimension del arreglo
 */
void ordIntecambio(double arreglo[], int longitud)
{
    int i,   // iterador
        j;  // iterador
    double aux; // contenedor temporal del valor

    for (i = 0; i < longitud - 1; i++) // inicia desde la primera posicion del arreglo hasta la posicion longitud -1
    {
        for (j = i + 1; j < longitud; j++) // inicia desde la segunda posicion de arreglo hasta la ultima posicion
        {
            if (arreglo[i] > arreglo[j]) // si el arreglo de la segunda pisicon i > al de posicion j los intercambia
            {
                aux = arreglo[i];
                arreglo[i] = arreglo[j];
                arreglo[j] = aux;
            }
        }
    }
}

/*!
 * @brief Evalua si todos los elementos de un array son iguales
 * @param arreglo 
 * @param longitud 
 * @return 's' si todos son iguales 'n' en caso contrario
 */
char valoresIguales(double arreglo[], int longitud){
    double contenedor;
    int i;
    char bandera = 's';
    for ( i = 0; i < longitud; i++)
    {
        if(i == 0){
            contenedor = arreglo[i];
        }

        if(contenedor != arreglo[i]){
            bandera = 'n';
            break;
        }
    }
    
    return bandera;
}