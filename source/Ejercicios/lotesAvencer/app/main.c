#include "imports.h"

/**
Se debe pasar por argumento
1) la fecha actual en formato: DDMMAAAA,
2) n meses a considerar


ELIJO UNA LISTA YA QUE ES UN ARCHIVO ORDENADO, SECUENCIAL
**/

int main(int argc, char *argv[])
{
    iniciarProceso(argv[1] , atoi(argv[2]));

    return 0;
}
