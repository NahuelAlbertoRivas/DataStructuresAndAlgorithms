#ifndef DEV_SUMA_MATRICES
#define DEV_SUMA_MATRICES

#include "../../arbolBinBusq/arbol.h"
#include <stdbool.h>
#include <winsock2.h>
#include <windows.h>
#include <unistd.h>

typedef struct
{
    int fila,
        columna,
        valor;
} tElementoMatriz;

bool verificar_mat(const char *dimMat1, const char *dimMat2);
byte cargar_mat(tArbolBinBusq *MatrizDispersa, FILE *pfMat);
bool validadorRangoMatriz(unsigned fila, unsigned columna);

#endif
