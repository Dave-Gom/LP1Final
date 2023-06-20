#include "header.h"

/**
 * @brief funcion central del juego, despliega el menu y decide que funcion llamar atendiendo a la seleccion del usuario
 * @param nick
 *
 * @author David Gomez
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
            verEstadisticas(nick);
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
 *
 * @author David Gomez
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
 *
 * @author David Gomez
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

/**
 * @brief Despliega las estadisticas del jugador y el ranking de mejores puntajes
 *
 * @param nick
 *
 * @author David Gomez
 */
void verEstadisticas(char nick[])
{
    printf("\nEstadisticas\n\nJugador: %s\n", nick);
    RegistroRanking rankingActual[5];
    char nombreArchivo[100] = "";
    int i;
    double relacion1 = 0, relacion2 = 0, relacion3 = 0;
    strcat(nombreArchivo, nick);
    strcat(nombreArchivo, "_resultados.txt");
    Jugador *datosJugador = leeResultados(nombreArchivo);

    leerRanking(rankingActual, 5);

    if (datosJugador->partidasJugadas != 0)
    {
        relacion1 = ((double)datosJugador->partidasGanadas / datosJugador->partidasJugadas);
        relacion2 = ((double)datosJugador->partidasEmpatadas / datosJugador->partidasJugadas);
        relacion3 = ((double)datosJugador->partidasPeridas / datosJugador->partidasJugadas);
    }

    printf("\nPartidas ganadas: %d%%\n", (int)(relacion1 * 100));
    printf("Partidas empatadas: %d%%\n", (int)(relacion2 * 100));
    printf("Partidas perdidas: %d%%\n", (int)(relacion3 * 100));

    printf("\nRanking Mejores puntajes\n\n");
    for (i = 0; i < 5; i++)
    {
        if (strcmp(rankingActual[i].nick, "") != 0 && rankingActual[i].puntaje != 0)
        {
            printf("#%d %s\t%d pts.\n", i + 1, rankingActual[i].nick, rankingActual[i].puntaje);
        }
        else
        {
            printf("#%d %s\n", i + 1, "Sin datos");
        }
    }
}

/**
 * @brief Inicia el juego
 * @param nick Nickname del jugador
 *
 * @author David Gomez
 */
void jugarPartida(char nick[])
{
    int ancho = 5, alto = 5; //
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
        if ((turno1 + turno2) % 2 == 0)
        {
            JugadasJugador1[turno1] = *jugar(1, ptrTablero, 0);
            turno1++;
            bandera1 = evaluaJugadas(JugadasJugador1, turno1);
            if (bandera1 == 1)
            {
                break;
            }
        }
        else
        {
            JugadasJugador2[turno2] = *jugar(2, ptrTablero, 1);
            turno2++;
            bandera2 = evaluaJugadas(JugadasJugador2, turno1);
            if (bandera2 == 1)
            {
                break;
            }
        }
    } while (evalTablero(*ptrTablero) == 0);

    if (bandera1 == bandera2 && bandera1 == 0 && bandera2 == 0)
    {
        printf("\n¡Empate!\n");
        guardarPartida(nick, 0, turno1);
    }
    else
    {
        if (bandera1 == 1)
        {
            printf("\n¡Gano el Jugador 1!\n");
            guardarPartida(nick, 1, turno1);
            guardarEnRanking(nick, turno1);
        }

        if (bandera2 == 1)
        {
            printf("\n¡Gano el Jugador 2!\n");
            guardarPartida(nick, 2, turno2);
        }
    }
}

/**
 * @brief Despliega el texto de instrucciones del programa y recomendaciones de juego
 *
 *
 * @author David Gomez
 */
void mostrarAyuda()
{

    printf("\n\n¡Bienvenido al juego interactivo de formar cuadrados!\n\n");
    printf("Aquí encontrarás todas las instrucciones necesarias para disfrutar de esta emocionante experiencia y algunos consejos para tener éxito en tus partidas.\n\n");
    printf("El objetivo del juego es determinar cuadrados a partir de sus vértices y ganar la partida antes que tu oponente, para esta compilacion, la computadora.\n\n");
    printf("Al comenzar, se te pedirá que ingreses tu nick o nombre de usuario para identificarte. Luego, se desplegará un menú con diferentes opciones:\n\n");
    printf("\t1. Visualizar configuración del tablero: Esta opción te permitirá conocer la información sobre el tamaño actual del tablero, es decir, el número de casillas que conforman el tablero en filas y columnas.\n");
    printf("\t2. Configurar parámetros: Aquí podrás ajustar la configuración del tablero, cambiando su tamaño para las partidas posteriores. Recuerda que el tamaño máximo del tablero es de 10x10 casillas.\n");
    printf("\t3. Ver estadísticas: En esta sección podrás consultar tus estadísticas como jugador. Se mostrará el porcentaje de partidas ganadas, perdidas y empatadas, así como la cantidad total de jugadas realizadas. Además, podrás ver el puntaje de los 5 mejores jugadores hasta el momento.\n");
    printf("\t4. Jugar partida: ¡Es hora de poner a prueba tus habilidades! Al seleccionar esta opción, se desplegará el tablero de juego en pantalla. El tablero consta de una cuadrícula de casillas, representadas por filas y columnas, donde podrás colocar tus fichas para formar cuadrados. El juego se desarrollará por turnos, comenzando por ti y luego la computadora o el otro jugador. \n\tCada turno consistirá en elegir una casilla disponible para colocar una ficha. Recuerda que las fichas se representan con el valor 1 para tus movimientos y el valor 2 para los movimientos del oponente. Para formar un cuadrado, deberás seleccionar cuatro casillas consecutivas que representan los vértices del cuadrado en cualquier dirección: horizontal, vertical o diagonal. \n\tPuedes formar cuadrados de cualquier tamaño y en cualquier posición dentro del tablero. ¡La creatividad y la estrategia son clave!\n");
    printf("\tTips para ganar el juego:\n");
    printf("\t\ta) Observa el tablero: Antes de realizar tu movimiento, analiza el estado actual del tablero. Identifica posibles combinaciones de casillas que podrían formar un cuadrado en tu próximo turno y también considera las jugadas del oponente.\n");
    printf("\t\tb) Bloquea al oponente: Si notas que el oponente está cerca de formar un cuadrado, intenta bloquear sus movimientos colocando tus fichas estratégicamente en las casillas que necesita para completar su cuadrado. Esto puede darle una ventaja a tu juego.\n");
    printf("\t\tc) Diversifica tus movimientos: No te limites a una sola dirección o estrategia. Explora diferentes posibilidades y coloca tus fichas en diversas partes del tablero. Esto puede dificultar la tarea del oponente para predecir tus movimientos y evitar que formes cuadrados.\n");
    printf("\t\td) Piensa a futuro: Considera no solo el movimiento actual, sino también las posibles jugadas futuras. Intenta anticiparte a los movimientos del oponente y planifica tu estrategia en consecuencia. Visualiza cómo podrías formar cuadrados en los próximos turnos y actúa en consecuencia.\n");
    printf("\t\te) Mantén el control del centro: El centro del tablero es una posición estratégica, ya que te brinda más oportunidades para formar cuadrados en diferentes direcciones. Intenta mantener el control de estas casillas y dificulta el acceso del oponente a ellas.\n\n");
    printf("Recuerda que la práctica y la experiencia son clave para mejorar tu desempeño en el juego. ¡Diviértete, experimenta con diferentes estrategias y disfruta de la emoción de formar cuadrados ganadores!\n\n");
    printf("\t5. Ayuda: Aquí encontrarás información adicional sobre el funcionamiento del juego y las reglas básicas. Podrás consultar detalles sobre cómo determinar cuadrados a partir de los vértices y cómo se lleva a cabo la partida. Además, si tienes alguna duda específica, estaremos encantados de ayudarte.\n");
    printf("\t6. Salir: Si deseas finalizar el juego, selecciona esta opción para salir del programa.\n\n");
    printf("Recuerda que el juego continuará hasta que uno de los jugadores haya conseguido formar un cuadrado o hasta que el tablero se llene sin que ninguno lo haya logrado. Después de cada partida, los resultados se guardarán en el archivo \"resultados.txt\" para que puedas consultar tus estadísticas en futuras partidas.\n\n");
    printf("¡Diviértete jugando y que tengas mucho éxito en tus estrategias para formar cuadrados!\n");
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
    int primerValor = 0, segundoValor = 0;
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
    if (primerValor == 0)
    {
        primerValor = 10;
    }
    if (segundoValor == 0) // en caso de que no se encentre configurado el tablero, la dimension por defecto es 10x10
    {
        segundoValor = 10;
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
 *
 * @author David Gomez
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

/**
 * @brief inicializa la matriz del tablero
 * @param filas
 * @param columnas
 * @return
 */
Matriz *inicializaMatriz(int filas, int columnas)
{
    Matriz *ptrMatriz = malloc(sizeof(Matriz));
    int i;
    ptrMatriz->fila = filas;
    ptrMatriz->columna = columnas;
    ptrMatriz->matriz = malloc(filas * sizeof(int *));
    for (i = 0; i < filas; i++)
    {
        ptrMatriz->matriz[i] = malloc(columnas * sizeof(int));
    }

    return ptrMatriz;
}

/**
 * @brief agrega una jugada al tablero
 * @param valor
 * @param tablero
 * @param automatico
 * @return
 *
 * @author David Gomez
 */
Punto *jugar(int valor, Matriz *tablero, int automatico)
{
    Punto *nuevoPunto = malloc(sizeof(Punto));
    printf("\nTurno jugador %d\n", valor);
    int x = 0, y = 0;

    if (automatico == 0)
    {
        do
        {
            printf("fila: %d columna: %d\n", tablero->fila, tablero->columna);

            printf("Ingrese la fila: ");
            scanf("%d", &y);

            printf("Ingrese la columna: ");
            scanf("%d", &x);

            if (x >= tablero->columna || y >= tablero->fila || y < 0 || x < 0)
            {
                printf("Los valores para la fila deben estar en [0 , %d].\nLos valores de la columna deben estar en [0,%d]\n", tablero->fila - 1, tablero->columna - 1);
                printf("Fila %d, Columna: %d\n", tablero->fila, tablero->columna);
                printf("Fila %d, Columna: %d\n", y, x);
                continue;
            }

            if (tablero->matriz[y][x] != 0)
            {
                printf("Casilla ocupada. Por favor, inténtelo nuevamente.\n");
                continue;
            }

            break; // Si se llega a este punto, los valores son válidos, se sale del bucle

        } while (1);

        nuevoPunto->x = x;
        nuevoPunto->y = y;
    }
    else
    {
        do
        {
            nuevoPunto = IA(*tablero);
        } while (tablero->matriz[nuevoPunto->y][nuevoPunto->x] != 0);

        printf("Jugador 2: (%d,%d)", nuevoPunto->x, nuevoPunto->y);
    }

    tablero->matriz[nuevoPunto->y][nuevoPunto->x] = valor;
    imprimeMatrizFormat(*tablero);
    return nuevoPunto;
}

/**
 * @brief Imprime un array de puntos
 * @param puntos
 * @param longitud
 *
 * @author David Gomez
 */
void imprimeJugadas(Punto puntos[], int longitud)
{
    int i = 0;
    printf("{");
    for (i = 0; i < longitud; i++)
    {
        printf("(%d , %d ) ,", puntos[i].x, puntos[i].y);
    }
    printf("}");
}

/**
 * @brief Evalua el array de jugadas
 * @param jugadas
 * @param longitud
 * @return 1 si hay un cuadrado, 0 en caso contrario
 *
 * @author David Gomez
 */
int evaluaJugadas(Punto jugadas[], int longitud)
{
    int i;
    int bandera = 0;

    if (longitud >= 4)
    {
        Punto **Combinaciones = malloc(combinatoria(longitud, 4) * sizeof(Punto *));
        int cantidadCombinaciones = 0;
        Punto combinacion[4];
        almacenarCombinaciones(jugadas, longitud, 0, combinacion, 0, Combinaciones, &cantidadCombinaciones);

        // Imprimir las combinaciones almacenadas
        for (int i = 0; i < cantidadCombinaciones; i++)
        {
            bandera = esCuadrado(Combinaciones[i], 4);
            if (bandera == 1)
            {
                break;
            }
        }

        liberarCombinaciones(Combinaciones, cantidadCombinaciones); // liberamos la memoria del array de combinaciones
    }

    return bandera;
}

/**
 * @brief Calcula la distancia entre dos puntos
 * @param p1
 * @param p2
 * @return
 *
 * @author David Gomez
 */
double calcularDistancia(Punto p1, Punto p2)
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

/**
 * @brief Calcula la convinatoria de dos numeros
 * @param n
 * @param k
 * @return
 *
 * @author David Gomez
 */
int combinatoria(int n, int k)
{
    if (k == 0 || k == n)
    {
        return 1;
    }
    else
    {
        return combinatoria(n - 1, k - 1) + combinatoria(n - 1, k);
    }
}

/**
 * @brief Almacena de forma recursiva todas las convinaciones posibles de 4 elementos de puntos del array jugadas en la matriz
 *
 * @param jugadas array de puntos
 * @param cantJugadas dimension del array de puntos
 * @param indiceActual posicion de inicio
 * @param combinacion array combinacion actual
 * @param indiceCombinacion indice actual array combinacion actual
 * @param Combinaciones Array de combinacions
 * @param cantidadCombinaciones dimension del array de combinaciones
 *
 * @author David Gomez
 */
void almacenarCombinaciones(Punto jugadas[], int cantJugadas, int indiceActual, Punto combinacion[], int indiceCombinacion, Punto **Combinaciones, int *cantidadCombinaciones)
{
    if (indiceCombinacion == 4)
    {
        // Se han seleccionado 4 jugadas, almacenar la combinación en Combinaciones
        Punto *nuevaCombinacion = malloc(4 * sizeof(Punto));
        for (int i = 0; i < 4; i++)
        {
            nuevaCombinacion[i] = combinacion[i];
        }
        Combinaciones[*cantidadCombinaciones] = nuevaCombinacion;
        (*cantidadCombinaciones)++;
        return;
    }

    if (indiceActual >= cantJugadas)
    {
        // No hay más jugadas disponibles, terminar la recursión
        return;
    }

    // No seleccionar el punto actual y pasar al siguiente
    almacenarCombinaciones(jugadas, cantJugadas, indiceActual + 1, combinacion, indiceCombinacion, Combinaciones, cantidadCombinaciones);

    // Seleccionar el punto actual y pasar al siguiente
    combinacion[indiceCombinacion] = jugadas[indiceActual];
    almacenarCombinaciones(jugadas, cantJugadas, indiceActual + 1, combinacion, indiceCombinacion + 1, Combinaciones, cantidadCombinaciones);
}

/**
 * @brief libera la memoria del array de combinaciones
 * @param Combinaciones
 * @param cantidadCombinaciones
 *
 * @author David Gomez
 */
void liberarCombinaciones(Punto **Combinaciones, int cantidadCombinaciones)
{
    for (int i = 0; i < cantidadCombinaciones; i++)
    {
        free(Combinaciones[i]);
    }
    free(Combinaciones);
}

/**
 * @brief Verifica si un array de 4 puntos se corresponde o no con los vertices de un Cuadrado
 * @param combinacion Array de Puntos (obligatoriamente de cuatro elementos)
 * @return 1 si es afirmativo 0 si no
 *
 * @author David Gomez
 */
int esCuadrado(Punto *combinacion, int longitudArray)
{
    int i, j;
    double bandera1, bandera2;
    if (longitudArray == 4)
    {
        double distancias[6]; // 4C2 = 6
        int index = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = i + 1; j < 4; j++)
            {
                distancias[index] = calcularDistancia(combinacion[i], combinacion[j]);
                index++;
            }
        }

        ordIntecambio(distancias, 6); // ordeno el array de menor a mayor

        bandera1 = valoresIguales(distancias, 4) == 's' ? distancias[0] : 0; // asignamos el valor 0 porque estamos evaluando distancias, y no puede se que la distancia entre dos puntos que no son el mismo sea 0
        bandera2 = valoresIguales(&distancias[4], 2) == 's' ? distancias[4] : 0;

        if (bandera1 != 0 && bandera2 != 0 && bandera1 < bandera2)
        {
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
 *
 * @author David Gomez
 */
void ordIntecambio(double arreglo[], int longitud)
{
    int i,      // iterador
        j;      // iterador
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
 *
 * @author David Gomez
 */
char valoresIguales(double arreglo[], int longitud)
{
    double contenedor;
    int i;
    char bandera = 's';
    for (i = 0; i < longitud; i++)
    {
        if (i == 0)
        {
            contenedor = arreglo[i];
        }

        if (contenedor != arreglo[i])
        {
            bandera = 'n';
            break;
        }
    }

    return bandera;
}

/**
 * @brief Asigna en x e y las cordenadas de la mejor jugada posible de la IA
 * @param tablero
 *
 * @author David Gomez
 */
Punto *IA(Matriz tablero)
{
    Punto *Jugada = malloc(sizeof(Punto));
    Punto current, puntoAux, puntoContenedor, puntoContenedor2;
    int i, j, contador = 0, k, l;
    int distancia = 0;
    int cantidadJugadas = 4;
    int jugadasPorDistancia;

    for (i = 0; i < tablero.fila; i++)
    {
        for (j = 0; j < tablero.columna; j++)
        {
            if (tablero.matriz[i][j] == 2)
            {
                contador++;

                if (contador == 1)
                { // almacenamos la ubicacion del primer elemento en caso de que sea unico
                    puntoContenedor2.x = j;
                    puntoContenedor2.y = i;
                }

                puntoAux.x = j;
                puntoAux.y = i;
                for (k = 0; k < tablero.columna; k++)
                {
                    for (l = 0; l < tablero.fila; l++)
                    {

                        if (tablero.matriz[i][k] == 2 && k != j)
                        { // si encontramos otro valor dos en la misma fila
                            distancia = abs(j - k);
                            if (distancia != 0)
                            {
                                jugadasPorDistancia = calcularMinimaCantidad(distancia, tablero, puntoAux, 2, &puntoContenedor);

                                if (jugadasPorDistancia < cantidadJugadas)
                                {
                                    cantidadJugadas = jugadasPorDistancia;
                                    Jugada->x = puntoContenedor.x;
                                    Jugada->y = puntoContenedor.y;
                                }
                            }
                        }

                        if (tablero.matriz[l][j] == 2 && l != i)
                        { // si encontramos otro valor dos en la misma columna
                            if (l != i)
                            { // Verifica que no sea el mismo punto
                                distancia = abs(l - i);
                                if (distancia != 0)
                                {
                                    jugadasPorDistancia = calcularMinimaCantidad(distancia, tablero, puntoAux, 2, &puntoContenedor);

                                    if (jugadasPorDistancia < cantidadJugadas)
                                    {
                                        cantidadJugadas = jugadasPorDistancia;
                                        Jugada->x = puntoContenedor.x;
                                        Jugada->y = puntoContenedor.y;
                                    }
                                }
                            }
                        }

                        if (tablero.matriz[l][k] == 2 && (l != i) && abs(i - l) == abs(k - j))
                        { // verifica si se encuentra otro valor 2 en una posición diagonalmente opuesta al punto actual
                            distancia = abs(l - i);
                            if (distancia != 0)
                            {
                                jugadasPorDistancia = calcularMinimaCantidad(distancia, tablero, puntoAux, 2, &puntoContenedor);

                                if (jugadasPorDistancia < cantidadJugadas)
                                {
                                    cantidadJugadas = jugadasPorDistancia;
                                    Jugada->x = puntoContenedor.x;
                                    Jugada->y = puntoContenedor.y;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (contador == 0) // si aun no hay ningun numero 2
    {
        do
        {
            i = enteroAleatorio(tablero.fila);
            j = enteroAleatorio(tablero.columna);
        } while (tablero.matriz[i][j] == 2);

        Jugada->x = j;
        Jugada->y = i;
        return Jugada;
    }

    if (contador == 1 || cantidadJugadas >= 3 || cantidadJugadas == 0) // si solamente hay una jugada, o todas sonel peor caso en el que la cantidad de jugadas para realizar un cuadrado es de 3
    {
        int filaLlena = evaluarfila(tablero, puntoContenedor2.y);
        int colLlena = evaluarColumna(tablero, puntoContenedor2.x);

        if (filaLlena == 0 && colLlena == 0)
        {
            int eleccion = enteroAleatorio(2);
            if (eleccion == 0)
            { // Elegir un número en la misma fila que la jugada
                Jugada->y = puntoContenedor2.y;

                do
                {
                    Jugada->x = enteroAleatorio(tablero.columna);
                    printf("Esto\n");

                } while (Jugada->x == puntoContenedor2.x || tablero.matriz[puntoContenedor2.y][Jugada->x] != 0);
            }
            else
            { // Elegir un número en la misma columna que la jugada
                Jugada->x = puntoContenedor2.x;

                do
                {
                    Jugada->y = enteroAleatorio(tablero.fila);
                    printf("Noo Esto\n");

                } while (Jugada->y == puntoContenedor2.y || tablero.matriz[Jugada->y][puntoContenedor2.x] != 0);
            }
        }

        if (filaLlena == 0 && colLlena == 1)
        {
            Jugada->y = puntoContenedor2.y;

            do
            {
                Jugada->x = enteroAleatorio(tablero.columna);
                printf("Esto\n");

            } while (Jugada->x == puntoContenedor2.x || tablero.matriz[puntoContenedor2.y][Jugada->x] != 0);
        }

        if (filaLlena == 1 && colLlena == 0)
        {
            Jugada->x = puntoContenedor2.x;

            do
            {
                Jugada->y = enteroAleatorio(tablero.fila);
                printf("Noo Esto\n");

            } while (Jugada->y == puntoContenedor2.y || tablero.matriz[Jugada->y][puntoContenedor2.x] != 0);
        }

        if (filaLlena == 1 && colLlena == 1)
        {
            do
            {
                i = enteroAleatorio(tablero.fila);
                j = enteroAleatorio(tablero.columna);
            } while (tablero.matriz[i][j] != 0);

            Jugada->x = j;
            Jugada->y = i;
        }
    }

    return Jugada;
}

/**
 * @brief Retrona un valor entero aleatorio menor al limite
 * @param limite
 * @return int
 *
 * @author David Gomez
 */
int enteroAleatorio(int limite) // devuelve un numero entero positivo, negativo o cero aleatorio
{
    int valor2 = (rand() % limite);
    return valor2;
}

/**
 * @brief evalua la minima cantidad e jugadas para formar un cuadrado
 * @param lado distancie entre el punto evaluado y otro punto
 * @param tablero estado actual del tablero
 * @param ubicacion punto a ser evaluado
 * @param valorAeval valor a verificar en el tablero en la posicion dada
 * @param jugada puntero a punto en el cual se almacenara la nueva jugada
 * @return int
 */
int calcularMinimaCantidad(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada)
{
    Punto punto;
    int maxJugadas = 3;
    int jugadas = 3; // seteamos en tres porque ya sabemos que el punto actual es igual al valor a evaluar

    jugadas = ArribaIz(lado, tablero, ubicacion, valorAeval, &punto);
    if (jugadas < maxJugadas)
    {
        maxJugadas = jugadas;
        jugada->x = punto.x;
        jugada->y = punto.y;
    }

    jugadas = ArribaDer(lado, tablero, ubicacion, valorAeval, &punto);
    if (jugadas < maxJugadas)
    {
        maxJugadas = jugadas;
        jugada->x = punto.x;
        jugada->y = punto.y;
    }

    jugadas = abajoDer(lado, tablero, ubicacion, valorAeval, &punto);

    if (jugadas < maxJugadas)
    {
        maxJugadas = jugadas;
        jugada->x = punto.x;
        jugada->y = punto.y;
    }

    jugadas = AbajoIz(lado, tablero, ubicacion, valorAeval, &punto);

    if (jugadas < maxJugadas)
    {
        maxJugadas = jugadas;
        jugada->x = punto.x;
        jugada->y = punto.y;
    }

    if (lado % 2 == 0)
    {

        jugadas = DiagonalAbajo(lado, tablero, ubicacion, valorAeval, &punto);

        if (jugadas < maxJugadas)
        {
            maxJugadas = jugadas;
            jugada->x = punto.x;
            jugada->y = punto.y;
        }

        jugadas = DiagonalArriba(lado, tablero, ubicacion, valorAeval, &punto);
        if (jugadas < maxJugadas)
        {
            maxJugadas = jugadas;
            jugada->x = punto.x;
            jugada->y = punto.y;
        }

        jugadas = DiagonalDer(lado, tablero, ubicacion, valorAeval, &punto);
        if (jugadas < maxJugadas)
        {
            maxJugadas = jugadas;
            jugada->x = punto.x;
            jugada->y = punto.y;
        }

        jugadas = DiagonalIzq(lado, tablero, ubicacion, valorAeval, &punto);

        if (jugadas < maxJugadas)
        {
            maxJugadas = jugadas;
            jugada->x = punto.x;
            jugada->y = punto.y;
        }
    }

    return maxJugadas;
}

/**
 * @brief Verifica la cantidad de jugadas necesarias para formar un cuadrado en direccion hacia arriba a la izq
 * @param lado lado del cuadrado
 * @param tablero tablero actual
 * @param ubicacion punto a evaluar
 * @param valorAeval valor a verificar
 * @param jugada puntero en el que almacenar una de las jugadas
 * @return int
 *
 * @author David Gomez
 */
int ArribaIz(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada)
{
    int cantiJugadas = 3;
    if (ubicacion.x - lado >= 0 && ubicacion.y - lado >= 0)
    {
        if (tablero.matriz[ubicacion.y - lado][ubicacion.x] == valorAeval)
        { // arriba mismo
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y - lado][ubicacion.x] == 0)
            {
                jugada->x = ubicacion.x;
                jugada->y = ubicacion.y - lado;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y - lado][ubicacion.x - lado] == valorAeval)
        { // diagonal superior izq
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y - lado][ubicacion.x - lado] == 0)
            {
                jugada->x = ubicacion.x - lado;
                jugada->y = ubicacion.y - lado;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y][ubicacion.x - lado] == valorAeval)
        { // a la izquierda
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y][ubicacion.x - lado] == 0)
            {
                jugada->x = ubicacion.x - lado;
                jugada->y = ubicacion.y;
            }
            else
            {
                return 100;
            }
        }

        return cantiJugadas;
    }

    return 100;
}

/**
 * @brief Verifica la cantidad de jugadas necesarias para formar un cuadrado en direccion hacia arriba a la derecha
 * @param lado lado del cuadrado
 * @param tablero tablero actual
 * @param ubicacion punto a evaluar
 * @param valorAeval valor a verificar
 * @param jugada puntero en el que almacenar una de las jugadas
 * @return int
 *
 * @author David Gomez
 */
int ArribaDer(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada)
{
    int cantiJugadas = 3;

    if (ubicacion.x + lado < tablero.columna && ubicacion.y - lado >= 0)
    {
        if (tablero.matriz[ubicacion.y - lado][ubicacion.x] == valorAeval) // arriba mismo
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y - lado][ubicacion.x] == 0)
            {
                jugada->x = ubicacion.x;
                jugada->y = ubicacion.y - lado;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y - lado][ubicacion.x + lado] == valorAeval) // diagonal sup der
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y - lado][ubicacion.x + lado] == 0)
            {
                jugada->x = ubicacion.x + lado;
                jugada->y = ubicacion.y - lado;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y][ubicacion.x + lado] == valorAeval) // a la derecha
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y][ubicacion.x + lado] == 0)
            {
                jugada->x = ubicacion.x + lado;
                jugada->y = ubicacion.y;
            }
            else
            {
                return 100;
            }
        }
        return cantiJugadas;
    }
    else
    {
        return 100;
    }
}

/**
 * @brief Verifica la cantidad de jugadas necesarias para formar un cuadrado en direccion hacia abajo a la izq
 * @param lado lado del cuadrado
 * @param tablero tablero actual
 * @param ubicacion punto a evaluar
 * @param valorAeval valor a verificar
 * @param jugada puntero en el que almacenar una de las jugadas
 * @return int
 *
 * @author David Gomez
 */
int abajoDer(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada)
{
    int cantiJugadas = 3;
    if (ubicacion.x + lado < tablero.columna && ubicacion.y + lado < tablero.fila)
    {
        if (tablero.matriz[ubicacion.y + lado][ubicacion.x] == valorAeval) // abajo mismo
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y + lado][ubicacion.x] == 0)
            {
                jugada->x = ubicacion.x;
                jugada->y = ubicacion.y + lado;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y + lado][ubicacion.x + lado] == valorAeval) // diagonal inferior derecha
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y + lado][ubicacion.x + lado] == 0)
            {
                jugada->x = ubicacion.x + lado;
                jugada->y = ubicacion.y + lado;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y][ubicacion.x + lado] == valorAeval) // a la derecha
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y][ubicacion.x + lado] == 0)
            {
                jugada->x = ubicacion.x + lado;
                jugada->y = ubicacion.y;
            }
            else
            {
                return 100;
            }
        }

        return cantiJugadas;
    }
    else
    {
        return 100;
    }
}

/**
 * @brief Verifica la cantidad de jugadas necesarias para formar un cuadrado en direccion hacia abajo a la izq
 * @param lado lado del cuadrado
 * @param tablero tablero actual
 * @param ubicacion punto a evaluar
 * @param valorAeval valor a verificar
 * @param jugada puntero en el que almacenar una de las jugadas
 * @return int
 *
 * @author David Gomez
 */
int AbajoIz(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada)
{
    int cantiJugadas = 3;
    if (ubicacion.x - lado >= 0 && ubicacion.y + lado < tablero.fila)
    {
        if (tablero.matriz[ubicacion.y + lado][ubicacion.x] == valorAeval) // abajo mismo
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y + lado][ubicacion.x] == 0)
            {
                jugada->x = ubicacion.x;
                jugada->y = ubicacion.y + lado;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y + lado][ubicacion.x - lado] == valorAeval) // diagonal inferior izq
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y + lado][ubicacion.x - lado] == 0)
            {
                jugada->x = ubicacion.x - lado;
                jugada->y = ubicacion.y + lado;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y][ubicacion.x - lado] == valorAeval) // a la izq
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y][ubicacion.x - lado] == 0)
            {
                jugada->x = ubicacion.x - lado;
                jugada->y = ubicacion.y;
            }
            else
            {
                return 100;
            }
        }

        return cantiJugadas;
    }

    return 100;
}

/**
 * @brief Verifica la cantidad de jugadas necesarias para formar un cuadrado en direccion hacia diagonarl hacia abajo
 * @param lado lado del cuadrado
 * @param tablero tablero actual
 * @param ubicacion punto a evaluar
 * @param valorAeval valor a verificar
 * @param jugada puntero en el que almacenar una de las jugadas
 * @return int
 *
 * @author David Gomez
 */
int DiagonalAbajo(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada)
{

    int cantiJugadas = 3;

    if (ubicacion.y + lado < tablero.fila && ubicacion.x + lado / 2 < tablero.columna && ubicacion.x - lado / 2 >= 0) // si se encuentra dentro de los limites de la matriz
    {

        if (tablero.matriz[ubicacion.y + lado][ubicacion.x] == valorAeval) // abajo mismo
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y + lado][ubicacion.x] == 0)
            {
                jugada->x = ubicacion.x;
                jugada->y = ubicacion.y - lado;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y + lado / 2][ubicacion.x + lado / 2] == valorAeval) // diagonal inferior derecha
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y + lado / 2][ubicacion.x + lado / 2] == 0)
            {
                jugada->x = ubicacion.x + lado / 2;
                jugada->y = ubicacion.y + lado / 2;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y + lado / 2][ubicacion.x - lado / 2] == valorAeval) //  diagonal inferior izquierda
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y + lado / 2][ubicacion.x - lado / 2] == 0)
            {
                jugada->x = ubicacion.x - lado / 2;
                jugada->y = ubicacion.y + lado / 2;
            }
            else
            {
                return 100;
            }
        }

        return cantiJugadas;
    }
    else
    {
        return 100;
    }
}

/**
 * @brief Verifica la cantidad de jugadas necesarias para formar un cuadrado en direccion hacia diagonarl hacia arriba
 * @param lado lado del cuadrado
 * @param tablero tablero actual
 * @param ubicacion punto a evaluar
 * @param valorAeval valor a verificar
 * @param jugada puntero en el que almacenar una de las jugadas
 * @return int
 *
 * @author David Gomez
 */
int DiagonalArriba(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada)
{
    int cantiJugadas = 3;
    if (ubicacion.y - lado >= 0 && ubicacion.x + lado / 2 < tablero.columna && ubicacion.x - lado / 2 >= 0) // si se encuentra dentro de los limites del array
    {

        if (tablero.matriz[ubicacion.y - lado][ubicacion.x] == valorAeval) // arriba mismo
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y - lado][ubicacion.x] == 0)
            {
                jugada->x = ubicacion.x;
                jugada->y = ubicacion.y - lado;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y - lado / 2][ubicacion.x + lado / 2] == valorAeval) // diagonal sup der
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y - lado / 2][ubicacion.x + lado / 2] == 0)
            {
                jugada->x = ubicacion.x + lado / 2;
                jugada->y = ubicacion.y - lado / 2;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y - lado / 2][ubicacion.x - lado / 2] == valorAeval) // diagonal sup izq
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y - lado / 2][ubicacion.x - lado / 2] == 0)
            {
                jugada->x = ubicacion.x + lado / 2;
                jugada->y = ubicacion.y;
            }
            else
            {
                return 100;
            }
        }

        return cantiJugadas;
    }
    else
    {
        return 100;
    }
}

/**
 * @brief Verifica la cantidad de jugadas necesarias para formar un cuadrado en direccion hacia diagonarl hacia la izquierda
 * @param lado lado del cuadrado
 * @param tablero tablero actual
 * @param ubicacion punto a evaluar
 * @param valorAeval valor a verificar
 * @param jugada puntero en el que almacenar una de las jugadas
 * @return int
 *
 * @author David Gomez
 */
int DiagonalIzq(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada)
{
    int cantiJugadas = 3;
    if (ubicacion.x - lado >= 0 && ubicacion.y + lado / 2 < tablero.columna && ubicacion.y - lado / 2 >= 0) // si se encuentra dentro de los limites del array
    {

        if (tablero.matriz[ubicacion.y][ubicacion.x - lado] == valorAeval) // a la izq
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y][ubicacion.x - lado] == 0)
            {
                jugada->x = ubicacion.x - lado;
                jugada->y = ubicacion.y;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y - lado / 2][ubicacion.x - lado / 2] == valorAeval) // a la diagonal sup izq
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y - lado / 2][ubicacion.x - lado / 2] == 0)
            {
                jugada->x = ubicacion.x - lado / 2;
                jugada->y = ubicacion.y - lado / 2;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y + lado / 2][ubicacion.x - lado / 2] == valorAeval) // diagonal inferior izq
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y + lado / 2][ubicacion.x - lado / 2] == 0)
            {
                jugada->x = ubicacion.x - lado / 2;
                jugada->y = ubicacion.y + lado / 2;
            }
            else
            {
                return 100;
            }
        }

        return cantiJugadas;
    }
    else
    {
        return 100;
    }
}

/**
 * @brief Verifica la cantidad de jugadas necesarias para formar un cuadrado en direccion hacia diagonarl hacia la derecha
 * @param lado lado del cuadrado
 * @param tablero tablero actual
 * @param ubicacion punto a evaluar
 * @param valorAeval valor a verificar
 * @param jugada puntero en el que almacenar una de las jugadas
 * @return int
 *
 * @author David Gomez
 */
int DiagonalDer(int lado, Matriz tablero, Punto ubicacion, int valorAeval, Punto *jugada)
{
    int cantiJugadas = 3;
    if (ubicacion.x + lado < tablero.columna && ubicacion.y + lado / 2 < tablero.fila && ubicacion.y - lado / 2 >= 0) // si se encuentra dentro de los limites de la matriz
    {

        if (tablero.matriz[ubicacion.y][ubicacion.x + lado] == valorAeval) // a la derecha
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y][ubicacion.x + lado] == 0)
            {
                jugada->x = ubicacion.x + lado;
                jugada->y = ubicacion.y;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y - lado / 2][ubicacion.x + lado / 2] == valorAeval) // diagonal sup derecha
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y - lado / 2][ubicacion.x + lado / 2] == 0)
            {
                jugada->x = ubicacion.x + lado / 2;
                jugada->y = ubicacion.y - lado / 2;
            }
            else
            {
                return 100;
            }
        }

        if (tablero.matriz[ubicacion.y + lado / 2][ubicacion.x + lado / 2] == valorAeval) // diagonal inf derecha
        {
            cantiJugadas--;
        }
        else
        {
            if (tablero.matriz[ubicacion.y + lado / 2][ubicacion.x + lado / 2] == 0)
            {
                jugada->x = ubicacion.x + lado / 2;
                jugada->y = ubicacion.y + lado / 2;
            }
            else
            {
                return 100;
            }
        }

        return cantiJugadas;
    }
    else
    {
        return 100;
    }
}

/**
 * @brief Guarda la parti actual en el registro de resultados del jugados, agrega al ranking de ser necesario
 * @param nick
 * @param resultado
 * @param cantidadJugadas
 *
 * @author David Gomez
 */
void guardarPartida(char nick[], int resultado, int cantidadJugadas)
{
    int partidasJugadas;
    int partidasGanadas;
    int partidasPeridas;
    int partidasEmpatadas;
    char nombreArchivo[100] = "";
    strcat(nombreArchivo, nick);
    strcat(nombreArchivo, "_resultados.txt");
    Jugador *datosJugador = leeResultados(nombreArchivo);

    switch (resultado)
    {
    case 0:
        datosJugador->partidasEmpatadas++;
        break;
    case 1:
        datosJugador->partidasGanadas++;
        break;
    case 2:
        datosJugador->partidasPeridas++;
        break;
    }

    guardarResultados(nombreArchivo, *datosJugador);
}

/**
 * @brief Lee los resultados del jugador del archivo dado
 * @param nombreArchivo
 * @return *Jugador
 *
 * @author David Gomez
 */
Jugador *leeResultados(char nombreArchivo[])
{
    Archivo *configuracion = abreArchivoGenerico(nombreArchivo, "r");
    char ganadas[100] = "";
    char perdidas[100] = "";
    char empatadas[100] = "";
    int g = 0, e = 0, p = 0;
    Jugador *datosJugador = malloc(sizeof(Jugador));
    if (configuracion != NULL && !feof(configuracion->punteroArchivo))
    {
        fscanf(configuracion->punteroArchivo, "%s", ganadas);
        fscanf(configuracion->punteroArchivo, "%s", perdidas);
        fscanf(configuracion->punteroArchivo, "%s", empatadas);
        sscanf(ganadas, "Ganadas=%d", &g);
        sscanf(perdidas, "Perdidas=%d", &p);
        sscanf(empatadas, "Empatadas=%d", &e);
    }
    datosJugador->partidasGanadas = g;
    datosJugador->partidasPeridas = e;
    datosJugador->partidasEmpatadas = p;
    datosJugador->partidasJugadas = datosJugador->partidasEmpatadas + datosJugador->partidasGanadas + datosJugador->partidasPeridas;
    fclose(configuracion->punteroArchivo);
    free(configuracion);

    return datosJugador;
}

/**
 * @brief Guarda los resultados del jugador en el archivo
 *
 * @param nombreArchivo
 * @param jugador
 *
 * @author David Gomez
 */
void guardarResultados(char nombreArchivo[], Jugador jugador)
{
    Archivo *configuracion = abreArchivoGenerico(nombreArchivo, "w");
    if (configuracion != NULL)
    {
        fprintf(configuracion->punteroArchivo, "Ganadas=%d\n", jugador.partidasGanadas);
        fprintf(configuracion->punteroArchivo, "Perdidas=%d\n", jugador.partidasPeridas);
        fprintf(configuracion->punteroArchivo, "Empatadas=%d\n", jugador.partidasEmpatadas);
    }
    fclose(configuracion->punteroArchivo);
    free(configuracion);
}

/**
 * @brief lee la informacin almacenada en el archivo Ranking
 *
 * @param ranking
 * @param dimension
 *
 * @author David Gomez
 */
void leerRanking(RegistroRanking ranking[], int dimension)
{
    Archivo *archivoRanking = abreArchivoGenerico("ranking.txt", "rb");
    RegistroRanking registroAux = {"", 0};
    int indice = 0;
    while (indice < dimension && !feof(archivoRanking->punteroArchivo))
    {
        strcpy(ranking[indice].nick, "");
        ranking[indice].puntaje = 0;

        fseek(archivoRanking->punteroArchivo, indice * sizeof(RegistroRanking), SEEK_SET); // establece el apuntador a la posicion del numero de cuenta del nuevo Registro
        fread(&registroAux, sizeof(RegistroRanking), 1, archivoRanking->punteroArchivo);
        strcpy(ranking[indice].nick, registroAux.nick);
        ranking[indice].puntaje = registroAux.puntaje;
        indice++;
        strcpy(registroAux.nick, "");
        registroAux.puntaje = 0;
    }
    fclose(archivoRanking->punteroArchivo);
    free(archivoRanking);
}

/**
 * @brief Guarda en el ranking los puntos del jugados
 *
 * @attention La cantidad de puntos es inversamente proporcional a la cantidad de jugadas del jugador, los puntos se asignan entre 0 y 1000 puntos
 * @param nombre
 * @param jugadas
 *
 * @author David Gomez
 */
void guardarEnRanking(char nombre[], int jugadas)
{
    int puntaje = 1000 * ((double)4 / jugadas);
    RegistroRanking rankingActual[6];
    leerRanking(rankingActual, 5);

    strcpy(rankingActual[5].nick, nombre);
    rankingActual[5].puntaje = puntaje;
    ordIntecambioRegistosRanking(rankingActual, 6);

    Archivo *archivoRanking = abreArchivoGenerico("ranking.txt", "rb+"); // guardamos el ranking en un archivo binario para que este no se pueda modificar
    int indice = 0;

    while (indice < 5 && !feof(archivoRanking->punteroArchivo))
    {
        fseek(archivoRanking->punteroArchivo, indice * sizeof(RegistroRanking), SEEK_SET);
        fwrite(&(rankingActual[indice]), sizeof(RegistroRanking), 1, archivoRanking->punteroArchivo);
        rewind(archivoRanking->punteroArchivo);
        indice++;
    }

    fclose(archivoRanking->punteroArchivo);
    free(archivoRanking);
}

/**
 * @brief Ordenamiento de intercambio. Ordena un array en orden ascendente por el metodo de intercambio de variables
 *
 * @param arreglo Arreglo a ser ordeneado
 * @param longitud Dimension del arreglo
 *
 * @author David Gomez
 */
void ordIntecambioRegistosRanking(RegistroRanking arreglo[], int longitud)
{
    int i, // iterador
        j; // iterador

    RegistroRanking aux; // contenedor temporal del valor

    for (i = 0; i < longitud - 1; i++) // inicia desde la primera posicion del arreglo hasta la posicion longitud -1
    {
        for (j = i + 1; j < longitud; j++) // inicia desde la segunda posicion de arreglo hasta la ultima posicion
        {
            if (arreglo[i].puntaje < arreglo[j].puntaje) // si el arreglo de la segunda pisicon i > al de posicion j los intercambia
            {
                aux.puntaje = arreglo[i].puntaje;
                strcpy(aux.nick, arreglo[i].nick);
                arreglo[i].puntaje = arreglo[j].puntaje;
                strcpy(arreglo[i].nick, arreglo[j].nick);
                arreglo[j].puntaje = aux.puntaje;
                strcpy(arreglo[j].nick, aux.nick);
            }
        }
    }
}

/**
 * @brief Evalue si el tablero esta lleno o no
 * @param tablero
 * @return 1 si esta lleno cero si no
 *
 * @author David Gomez
 */
int evalTablero(Matriz tablero)
{
    int i, j;
    for (i = 0; i < tablero.fila; i++)
    {
        for (j = 0; j < tablero.columna; j++)
        {
            if (tablero.matriz[i][j] == 0)
            {
                return 0;
            }
        }
    }

    return 1;
}

/**
 * @brief Evalua si una fila del tablero esta llena
 * @param tablero
 * @param filaEval
 * @return 1 si esta llena cero si no
 *
 * @author David Gomez
 */
int evaluarfila(Matriz tablero, int filaEval)
{
    int i;
    for (i = 0; i < tablero.columna; i++)
    {
        if (tablero.matriz[filaEval][i] == 0)
        {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Evalua si una columna del tablero esta llena
 * @param tablero
 * @param filaEval
 * @return 1 si esta llena cero si no
 *
 * @author David Gomez
 */
int evaluarColumna(Matriz tablero, int culumnaEval)
{
    int i;
    for (i = 0; i < tablero.fila; i++)
    {
        if (tablero.matriz[i][culumnaEval] == 0)
        {
            return 0;
        }
    }
    return 1;
}