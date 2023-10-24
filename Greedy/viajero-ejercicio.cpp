#include <iostream>
#include <algorithm>
#include "../Lista/lista.cpp"

using namespace std;

class Destino
{
public:
    double costo;
    double satisfaccion;
    double ratio;

    Destino(double costo, double satisfaccion) : costo(costo), satisfaccion(satisfaccion), ratio(satisfaccion / costo) {}
};

void viaje(Destino **destinos, int cantDestinos, double presupuesto)
{
    // IMPLEMENTAR!!! :)
}

int main()
{
    /*
        Consigna: Problema del Viajero con Presupuesto Limitado

        Supón que eres un viajero que quiere visitar varios destinos turísticos.
        Cada destino tiene un costo y un valor de satisfacción.
        Tienes un presupuesto
        limitado y tu objetivo es maximizar tu satisfacción total sin exceder tu presupuesto.
        El algoritmo voraz debera seleccionar destinos basados en la mejor relación 
        satisfacción-costo hasta que se agote el presupuesto.
    */
    int cantDestinos = 4;
    Destino **destinos = new Destino *[cantDestinos];

    destinos[0] = new Destino(300, 90);  // Por ejemplo, Paris
    destinos[1] = new Destino(500, 150); // Por ejemplo, Nueva York
    destinos[2] = new Destino(200, 50);  // Por ejemplo, Bangkok
    destinos[3] = new Destino(400, 110); // Por ejemplo, Sydney

    double presupuesto = 700;

    viaje(destinos, cantDestinos, presupuesto);
    // SALIDA ESPERADA:
    //     Destino con costo: 400 y satisfaccion: 110
    //     Destino con costo: 200 y satisfaccion: 50
    //     Satisfaccion total: 160
    //     Presupuesto remanente: 100

    // Liberar memoria
    for (int i = 0; i < cantDestinos; delete destinos[i++])
        ;
    delete[] destinos;

    return 0;
}