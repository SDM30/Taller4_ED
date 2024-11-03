
#include "sistema.h"
#include <chrono>

int main(int argc, char *argv[]) {
    
    Sistema control;

    if ( (argc < 3) || (argc > 3) ) {
        std::cout << "Uso: " << argv[0] << " <Archivo_Personas> <Archivo_Prueba_Seis_Grados>" << std::endl;
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    control.cargarPersonas(argv[1], true);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Tiempo de ejecucion de carga: " << duration.count() << " microsegundos" << std::endl

    auto start_seis_grados = std::chrono::high_resolution_clock::now();
    control.probarSeisGrados(argv[2], true);
    auto end_seis_grados = std::chrono::high_resolution_clock::now();
    auto duration_seis_grados = std::chrono::duration_cast<std::chrono::microseconds>(end_seis_grados - start_seis_grados);
    std::cout << "Tiempo de ejecucion de seis grados: " << duration_seis_grados.count() << " microsegundos" << std::endl;

    return 0;
}
