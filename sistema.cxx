#include "sistema.h"

// Definición de gPersonas
Grafo<std::string> Sistema::gPersonas;


Grafo<std::string> Sistema::getPersonas() {
    return gPersonas;
}

void Sistema::cargarPersonas(std::string nombre_archivo, bool verbose) {
    
    std::ifstream entrada(nombre_archivo);
    if (!entrada.is_open()){
        printf("El archivo %s no existe o es ilegible\n", nombre_archivo.c_str());
        return;        
    }

    if (entrada.peek() == EOF) {
        std::cout << "El archivo " << nombre_archivo << " no existe o es ilegible"
                << std::endl;
        return;
    }

    //Datos persona
    int numero_personas = 0;
    std::string nombre_p1;
    std::string nombre_p2;

    while (entrada >> numero_personas) {
        for (int i = 0; i < numero_personas; i++) {
            entrada >> nombre_p1;
            entrada >> nombre_p2;

            if (verbose) {
                std::cout << std::endl << nombre_p1 << " " << nombre_p2 << std::endl;
                std::cout << "Ingresando al Grafo" << std::endl;
                if (gPersonas.buscarVertice(nombre_p1) >= 0) 
                    std::cout << nombre_p1 
                            << " ya esta en el grafo"
                            << std::endl;
                if (gPersonas.buscarVertice(nombre_p2) >= 0) 
                    std::cout << nombre_p2 
                            << " ya esta en el grafo"
                            << std::endl;  
            }

            gPersonas.insertarVertice(nombre_p1);
            gPersonas.insertarVertice(nombre_p2);

            gPersonas.insAristaNoDir(nombre_p1, nombre_p2, 1);
        }
    }

    if (verbose) {
        std::cout << std::endl << "Revisar estado del grafo al finalizar lectura" << std::endl;
        std:: cout << "Numero de personas = " << gPersonas.cantVertices() << std::endl;
        std::cout << "Recorrido plano = ";
        gPersonas.plano();
        std::cout << "Recorrido por profundidad (Desde Alice) = ";
        gPersonas.DFS("Alice");
        std::cout << "Recorrido por anchura (Desde Alice) = ";
        gPersonas.BFS("Alice");
    }
}