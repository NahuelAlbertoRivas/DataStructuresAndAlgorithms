#include "dev.h"
#include <stdlib.h>

void crearArbol(tArbolBinBusq *pa)
{
    *pa = NULL;
}

int arbolVacio(tArbolBinBusq *pa)
{
    return *pa == NULL;
}

int arbolLleno(tArbolBinBusq *pa)
{
    return 1;
}

void vaciarArbol(tArbolBinBusq *pa)
{
    if(!(*pa))
        return;
    vaciarArbol(&((*pa)->izq));
    vaciarArbol(&((*pa)->der));
    free((*pa)->info);
    free(*pa);
}