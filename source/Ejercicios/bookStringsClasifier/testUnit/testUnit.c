#include "testUnit.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_TAM_LINEAS 2048

void crearLibroPrueba()
{
    FILE *pfLibro;
    char nombreLibro[] = "libro.txt",
                         lineasTexto[][MAX_TAM_LINEAS] =
                         {
                            {""},
                            {""},
                            {""},
                            {""},
                            {""},
                            {""}
                         };
    int i;

    crearArchivoTexto(nombreLibro);

    pfLibro = abrirArchivoTexto(nombreLibro);

    for(i = 0; i < (sizeof(lineasTexto) / MAX_TAM_LINEAS); i++)
    {
        fprintf(pfLibro, "%s", lineasTexto[i]);

    }

    fclose(pfLibro);
}
