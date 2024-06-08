#include "testUnit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crearArchivoEnteros()
{
    int vec[] = {500, 7, 10, 432, 1000, 0, 2124, 4, 8, 9, 7, -1, 100, 80, 433, 3000, -2, 50000000, 1},
                i;
    FILE *pf = fopen("datos.bin", "wb");
    if(!pf)
        return;

    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
        fwrite(vec + i, sizeof(*vec), 1, pf);

    fclose(pf);
}

int grabarRegistro();

int leerRegistro();
