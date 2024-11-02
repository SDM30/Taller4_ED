#include "sistema.h"

// Definición de gPersonas
Grafo<std::string> Sistema::gPersonas;

void Sistema::cargarPersonas(std::string nombre_archivo, bool verbose) {
    
    std::ifstream entrada(nombre_archivo);
    if (!entrada.is_open()) {
        printf("El archivo %s no existe o es ilegible\n", nombre_archivo.c_str());
        return;        
    }

    if (entrada.peek() == EOF) {
        std::cout << "El archivo " << nombre_archivo << " no tiene contenido o es ilegible"
                  << std::endl;
        return;
    }

    int numero_personas = 0;
    std::string linea;
    std::string nombre_p1, nombre_p2;

    if (entrada >> numero_personas) {
        entrada.ignore();

        for (int i = 0; i < numero_personas; i++) {
            std::getline(entrada, linea);
            std::istringstream stream(linea);

            stream >> nombre_p1;
            if (!(stream >> nombre_p2)) {
                nombre_p2 = "";
            }

            if (!nombre_p1.empty() && gPersonas.buscarVertice(nombre_p1) < 0) {
                gPersonas.insertarVertice(nombre_p1);
            }
            if (!nombre_p2.empty() && gPersonas.buscarVertice(nombre_p2) < 0) {
                gPersonas.insertarVertice(nombre_p2);
            }

            if (!nombre_p2.empty()) {
                gPersonas.insAristaNoDir(nombre_p1, nombre_p2, 1);
            }

            if (verbose) {
                std::cout << "Numero personas = " << i << std::endl;
                std::cout << std::endl << "Ingresando al Grafo: " << nombre_p1;
                if (!nombre_p2.empty()) {
                    std::cout << " - " << nombre_p2;
                }
                std::cout << std::endl;

                if (gPersonas.buscarVertice(nombre_p1) >= 0)
                    std::cout << nombre_p1 << " ya está en el grafo" << std::endl;
                if (!nombre_p2.empty() && gPersonas.buscarVertice(nombre_p2) >= 0)
                    std::cout << nombre_p2 << " ya está en el grafo" << std::endl;
            }
        }
    }

    // Imprimir el estado del grafo al final de la lectura
    if (verbose) {
        std::cout << std::endl << "Estado del grafo al finalizar lectura" << std::endl;
        std::cout << "Numero de personas = " << gPersonas.cantVertices() << std::endl;
        std::cout << "Recorrido plano = ";
        gPersonas.plano();
        std::cout << "Recorrido por profundidad (Desde Primer Vertice) = ";
        gPersonas.DFS(gPersonas.obtenerVertices()[0]);
        std::cout << "Recorrido por anchura (Desde Primer Vertice) = ";
        gPersonas.BFS(gPersonas.obtenerVertices()[0]);
        std::cout << std::endl;
        std::cout << "Matriz de adyacencia = " << std::endl;
        for (int i = 0; i < gPersonas.cantVertices(); i++) {
            for (int j = 0; j < gPersonas.cantVertices(); j++) {
                std::cout << gPersonas.obtenerAristas()[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void Sistema::sumarMatrices(int** matriz1, int** matriz2) {
    // matriz1 almacena el resultado
    const int tam = gPersonas.cantVertices();
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            matriz1[i][j] += matriz2[i][j];
        }
    }
}

void Sistema::calcularMatrizCaminos(bool verbose) {
    const int tam = gPersonas.cantVertices();
    //Original
    int **matriz_a = gPersonas.obtenerAristasCpy();
    //Accumula las potencias
    int **matriz_a_k = gPersonas.obtenerAristasCpy();

    matriz_caminos = gPersonas.obtenerAristasCpy();
    
    for (int i = 0; i < 5; i++) {
        //Sumar a la matriz de caminos
        sumarMatrices(matriz_caminos, matriz_a_k);

        //Multiplicación de matrices
        int** matriz_aux = gPersonas.obtenerAristasCpy();
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

        //Salto de linea para siguente fila de la matriz
        if (verbose) {
            std::cout<<std::endl; 
        }

        liberarMatriz(matriz_a_k, tam);
        matriz_a_k = matriz_aux;
    }
    sumarMatrices(matriz_caminos, matriz_a_k);

    //Inicializar matriz de identidad
    int **matriz_iden = gPersonas.obtenerAristasCpy();
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            matriz_iden[i][j] = 0;
            if (i == j) {
                matriz_iden[i][j] = 1;
            }
        }
    }

    liberarMatriz(matriz_a, tam);
    liberarMatriz(matriz_a_k, tam);

    sumarMatrices(matriz_caminos, matriz_iden);

    //Reemplazar valores > 0 por 1
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            if (matriz_caminos[i][j] > 0) {
                matriz_caminos[i][j] = 1;
            }

            if (verbose) {
                std::cout << matriz_caminos[i][j] << " ";
            }
        }

        if (verbose) {
            std::cout << std::endl;
        }
    }

    liberarMatriz(matriz_iden, tam);
}

bool Sistema::seisGrados(std::string p1, std::string p2) {
    const int tam = gPersonas.cantVertices();

    if (gPersonas.obtenerVertices().empty()) {
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

    if (matriz_caminos[pos_p1][pos_p2] > 0) {
        return true;
    }

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
    calcularMatrizCaminos(true);
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

    //Eliminar extension del archivo
    int pos_punto = nombre_archivo.find_last_of(".");
    std::ofstream salida(nombre_archivo.substr(0,pos_punto) + "_resultado.txt");

    while (entrada >> numero_personas) {
        salida << numero_personas << std::endl;
        if (verbose) std::cout << numero_personas << std::endl;
        for (int i = 0; i < numero_personas; i++) {
            entrada >> nombre_p1;
            entrada >> nombre_p2;
            cumple = (seisGrados(nombre_p1, nombre_p2)) ? "Cumple" : "No Cumple";
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