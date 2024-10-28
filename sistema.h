#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Grafo.h" 

class Sistema {
    private:
        static Grafo<std::string> gPersonas;
    
    public:
        Grafo<std::string> getPersonas();
        void cargarPersonas(std::string nombre_archivo, bool verbose);
        bool seisGrados(std::string p1, std::string p2, bool verbose);
        void probarSeisGrados(std::string nombre_archivo, bool verbose);
        void liberarMatriz(int** matriz, int tam);
};

#endif