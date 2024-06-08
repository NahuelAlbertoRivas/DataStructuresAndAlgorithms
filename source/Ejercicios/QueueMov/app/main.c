#include "../dev/dev.h"
#include "../testUnit/testUnit.h"

int main(int argc, char *argv[])
{
    crearArchivoBienFormatMovs(); /// esta fn. genera registros con un formato relativamente correcto, hay otra que crea un lote menos amigable
    procesarMovimientos(argv[1]);

    return 0;
}
