
#include "sistema.h"

int main(int argc, char *argv[]) {

    Sistema control;

    if ( (argc < 3) || (argc > 3) ) {
        std::cout << "Uso: " << argv[0] << " <Archivo_Personas> <Archivo_Prueba_Seis_Grados>" << std::endl;
        return 1;
    }

    control.cargarPersonas(argv[1], true);

    return 0;
}