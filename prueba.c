#include <math.h>

// Estructura para representar un punto en el plano cartesiano
typedef struct
{
    int x;
    int y;
} Punto;

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
