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
        std::cout << std::endl;
    }
}

void mostrarMatrizAdyacencia(Grafo<std::string>& grafo) {
    std::cout << "Matriz de Adyacencia:" << std::endl;
    int numVer = grafo.cantVertices();
    if (numVer == 0) {
        std::cout << "La matriz está vacía." << std::endl;
        return;
    }
    for (int i = 0; i < numVer; ++i) {
        for (int j = 0; j < numVer; ++j) {
            std::cout << grafo.getAristas()[i][j] << " "; // Asegúrate de que 'aristas' sea accesible.
        }
        std::cout << std::endl;
    }
}

bool Sistema::seisGrados(std::string p1, std::string p2, bool verbose) {
    const int tam = gPersonas.cantVertices();
    //Asegurarse que el grafo no este vacio

    //mostrarMatrizAdyacencia(gPersonas);

    if (gPersonas.getVertices().empty()) {
        std::cout << "No se han cargado personas, no es posible realizar la operacion" << std::endl;
        return false;
    }
    
    int pos_p1 = gPersonas.buscarVertice(p1);
    if (pos_p1 == -1) {
        std::cout << p1 << " no ha sido cargado en el sistema" << std::endl;
        return false;
    }

    int pos_p2 = gPersonas.buscarVertice(p2);
    if (pos_p2 == -1) {
        std::cout << p2 << " no ha sido cargado en el sistema" << std::endl;
        return false;
    }
    //Original
    int **matriz_a = gPersonas.getAristasCpy();
    //Accumula las potencias
    int **matriz_a_k = gPersonas.getAristasCpy();

    for (int potencia = 0; potencia < 6; potencia ++) {


        if (matriz_a_k[pos_p1][pos_p2] > 0) {
            liberarMatriz(matriz_a, tam);
            liberarMatriz(matriz_a_k, tam);
            return true;
        } else {
            //Multiplicación de matrices
            int** matriz_aux = gPersonas.getAristasCpy();
            for (int i = 0; i < tam; i++) {
                for (int j = 0; j < tam; j++) {
                    matriz_aux[i][j] = 0;

                    for (int k = 0; k < tam; k++) {
                        matriz_aux[i][j] += matriz_a_k[i][k] * matriz_a[k][j];
                    }

                    //Mostrar resultado de multiplicacion
                    if (verbose) {
                       std::cout << std::setw(5) << std::left << matriz_aux[i][j];
                    }
                }

                //Salto de linea para siguente fila de la matriz
                if (verbose) {
                    std::cout<<std::endl; 
                }
            }

            liberarMatriz(matriz_a_k, tam);
            matriz_a_k = matriz_aux;
        }

        if (verbose) {
            std::cout << std:: endl << std::endl;
        }
    }

    liberarMatriz(matriz_a, tam);
    liberarMatriz(matriz_a_k, tam);
    return false;
}

void Sistema::liberarMatriz(int** matriz, int tam) {
    if (matriz != NULL) {
        for (int i = 0; i < tam; i++) {
            delete[] matriz[i];
        }
        delete[] matriz;
    }
}

void Sistema::probarSeisGrados(std::string nombre_archivo, bool verbose) {
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
    std::string cumple;
    std::ofstream salida(nombre_archivo + "_resultado");

    while (entrada >> numero_personas) {
        salida << numero_personas << std::endl;
        if (verbose) std::cout << numero_personas << std::endl;
        for (int i = 0; i < numero_personas; i++) {
            entrada >> nombre_p1;
            entrada >> nombre_p2;
            cumple = (seisGrados(nombre_p1, nombre_p2, false)) ? "Cumple" : "No Cumple";
            salida << std::setw(10) << std::left << nombre_p1
                   << std::setw(10) << nombre_p2
                   << std::setw(10) << cumple << std::endl;
            if (verbose) {
                std::cout << std::setw(10) << std::left << nombre_p1
                          << std::setw(10) << nombre_p2
                          << std::setw(10) << cumple << std::endl;
            }
        }
    }
}