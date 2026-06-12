#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include "heiland.h"

int main () {

    // un archivo por cada drone
    FILE *f1 = fopen ("trajectory_1.dat","rb");
    FILE *f2 = fopen ("trajectory_2.dat","rb");
    FILE *f3 = fopen ("trajectory_3.dat","rb"); // aca ya leo los archivos double

    if (f1 == NULL || f2 == NULL || f3 == NULL) {
        printf ("error al abrir uno de los archivos\n");
        return 1;
    }
 
    // ya lei los archivos de 3 drones, ahora obj
    trayectoria h1(f1);
    trayectoria h2(f2);
    trayectoria h3(f3);

    // llamo a las funciones
    double tiempo1 = h1.tiempovuelo();
    double tiempo2 = h2.tiempovuelo();
    double tiempo3 = h3.tiempovuelo();

    double distancia1 = h1.distanciarecorrida();
    double distancia2 = h2.distanciarecorrida();
    double distancia3 = h3.distanciarecorrida();

    double velocidadmax1 = h1.velocidadmaxima();
    double velocidadmax2 = h2.velocidadmaxima();
    double velocidadmax3 = h3.velocidadmaxima();

    double velocidadprom1 = h1.velocidadpromedio();
    double velocidadprom2 = h2.velocidadpromedio();
    double velocidadprom3 = h3.velocidadpromedio();



    std::cout << "el tiempo de vuelo para el drone 1 es: " << tiempo1 << std::endl;
    std::cout << "el tiempo de vuelo para el drone 2 es: " << tiempo2 << std::endl;
    std::cout << "el tiempo de vuelo para el drone 3 es: " << tiempo3 << std::endl;

    std::cout << "la distancia recorrida para el drone 1 es: " << distancia1 << std::endl;
    std::cout << "la distancia recorrida para el drone 2 es: " << distancia2 << std::endl;
    std::cout << "la distancia recorrida para el drone 3 es: " << distancia3 << std::endl;

    std::cout << "la velocidad maxima de vuelo para el drone 1 es: " << velocidadmax1 << std::endl;
    std::cout << "la velocidad maxima de vuelo para el drone 2 es: " << velocidadmax2 << std::endl;
    std::cout << "la velocidad maxima de vuelo para el drone 3 es: " << velocidadmax3 << std::endl;

    std::cout << "la distancia minima entre los drones es: " << velocidadmax1 << std::endl;


    FILE *out = fopen("resultados.txt","w");
    if (!out) {
        printf("No se pudo crear resultados.txt\n");
        fclose(f1); fclose(f2); fclose(f3);
        return 1;
    }

    fprintf(out, "Tiempo de vuelo (s): %.2f %.2f %.2f\n", tiempo1, tiempo2, tiempo3);
    fprintf(out, "Distancia recorrida (m): %.2f %.2f %.2f\n", distancia1, distancia2, distancia3);
    fprintf(out, "Velocidad maxima (m/s): %.2f %.2f %.2f\n", velocidadmax1, velocidadmax2, velocidadmax3);
    fprintf(out, "Velocidad promedio (m/s): %.2f %.2f %.2f\n", velocidadprom1, velocidadprom2, velocidadprom3);

    printf("se guardaron los resultados.txt\n");

    fclose(out);
    fclose(f1);
    fclose(f2);
    fclose(f3);

    return 0;
}
