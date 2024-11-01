#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "Grafo.h" 

class Sistema {
    private:
        static Grafo<std::string> gPersonas;
        int** matriz_caminos;

    public:
        void cargarPersonas(std::string nombre_archivo, bool verbose);
        void sumarMatrices(int** matriz1, int** matriz2);
        void calcularMatrizCaminos(bool verbose);
        bool seisGrados(std::string p1, std::string p2);
        void probarSeisGrados(std::string nombre_archivo, bool verbose);
        void liberarMatriz(int** matriz, int tam);
};

#endif