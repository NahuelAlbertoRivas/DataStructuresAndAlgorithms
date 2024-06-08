#include "../dev/dev.h"
#include "../testUnit/testUnit.h"

int main(int argc, char *argv[])
{
    crearArchivoEnteros();
    procesarArchivo(argv[1], DESC);
    return 0;
}
