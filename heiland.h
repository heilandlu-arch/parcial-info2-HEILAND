#pragma once

#include <cmath>
#include <cstdio>

class trayectoria {
    int tam;
    double *tiempo;
    double *x;
    double *y;
    double *z; //puntero pq no se el tamaño del archivo 

    public:

    ~trayectoria() {
        delete[]tiempo;
        delete[]x;
        delete[]y;
        delete[]z;
    }

    trayectoria (FILE *f) {
        fseek(f, 0, SEEK_END);//recorro p saber tam
        tam = ftell(f);
        tam = tam /sizeof(double);
        tam = tam/4; 

        //hsta ac tengo tam

        rewind(f); 

        tiempo = new double[tam];
        x = new double[tam];
        y = new double[tam];
        z = new double[tam];

        //hasta ac ya hic vectr ahora cargo 

        for (int i = 0; i < tam; i++) {
            fread(&tiempo[i], sizeof(double), 1, f); 
            fread(&x[i], sizeof(double), 1, f);
            fread(&y[i], sizeof(double), 1, f);
            fread(&z[i], sizeof(double), 1, f);
        } 

    }//carg ahora quiero calcular el tiempo de vuelo de cada archivo 

    //puedo hacer esto pq ya carge datos

    //me pide tiempo de vuelo de cada drone (cada archivo), la funcion para cada drone la llamo en el main

    double tiempovuelo() {
        double tiempovuelo;
        return tiempovuelo = tiempo[tam - 1] - tiempo[0];
    }

     //necesito modulo para saber la distancia recorrida pero d c/u?
     //la consigna me pide la distancia recorrida de cada drone 

     double distanciarecorrida() {
        double distanciarecorrida;
        double sumatoria = 0;
        for (int i = 1; i < tam; i++){
            double dx = x[i] - x[i-1];
            double dy = y[i] - y[i-1];
            double dz = z[i] - z[i-1];
            sumatoria = sumatoria + sqrt(dx*dx + dy*dy + dz*dz);
        }
        distanciarecorrida = sumatoria;
        return distanciarecorrida; 
    }

    //me pide velocidad maxima de cada drone, es lo mis

   double velocidadmaxima() {
   double velocidadmaxima = 0;
    for (int i = 1; i < tam; i++) {
        double dt = tiempo[i] - tiempo[i-1];
        if (dt > 0) {
            double dx = x[i] - x[i-1];
            double dy = y[i] - y[i-1];
            double dz = z[i] - z[i-1];
            double velocidad = sqrt(dx*dx + dy*dy + dz*dz) / dt;
            if (velocidad > velocidadmaxima) {
                velocidadmaxima = velocidad;
            }
        }
    }
    return velocidadmaxima;
}

    //me pide velocidad promedio de cada drone

    double velocidadpromedio(){
        double tiempototal = tiempo[tam - 1] - tiempo[0];
        if (tiempototal <= 0) return 0;
        double velocidadpromedio = distanciarecorrida() / tiempototal;
        return velocidadpromedio;
    }


double distanciaminima(const trayectoria &t2, const trayectoria &t3, double &tiempomin, double &xmin, double &ymin, double &zmin) {
    double mindist = 1e300; // muy grande p compara
    double distancia;

    for (int i = 0; i < tam; i++){
        double valorgrande= 1e300;
        for (int j = 0; j < t2.tam; j++){
            distancia = sqrt((x[i]-t2.x[j])*(x[i]-t2.x[j])+(y[i]-t2.y[j])*(y[i]-t2.y[j]) +(z[i]-t2.z[j])*(z[i]-t2.z[j]));
            if (distancia < valorgrande) valorgrande = distancia;
        }
        for (int k = 0; k < t3.tam; k++){
            distancia = sqrt((x[i]-t3.x[k])*(x[i]-t3.x[k]) +(y[i]-t3.y[k])*(y[i]-t3.y[k])+(z[i]-t3.z[k])*(z[i]-t3.z[k]));
            if (distancia < valorgrande) valorgrande = distancia;
        }

        if (valorgrande < mindist) {
            mindist = valorgrande;
            tiempomin = tiempo[i];
            xmin = x[i];
            ymin = y[i];
            zmin = z[i];
        }
    }
    return mindist;
}
};





