#include "dev.h"
#include "../../strValidators/strValidators.h"

#define MAX_TAM_REC 11

#define LIMITE_INF 1
#define LIMITE_SUP 999
#define VAL 1
#define NO_VAL 0

bool verificar_mat(const char *dimMat1, const char *dimMat2)
{
    int filas1,
        filas2,
        colum1,
        colum2;

    sscanf(dimMat1, "[%d][%d]", &filas1, &colum1);
    if(validadorRangoMatriz(filas1, colum1) != VAL)
        return false;

    sscanf(dimMat2, "[%d][%d]", &filas2, &colum2);
    if(validadorRangoMatriz(filas2, colum2) != VAL)
        return false;

    if((filas1 != filas2) || (colum1 != colum2))
        return false;

    return true;
}

byte cargar_mat(tArbolBinBusq *MatrizDispersa, FILE *pfMat)
{
    byte cod = VAL;

    return cod;
}

bool validadorRangoMatriz(unsigned fila, unsigned columna)
{
    if(((fila < LIMITE_INF) || (fila > LIMITE_SUP)) ||
       ((columna < LIMITE_INF) || (columna > LIMITE_SUP)))
        return false;

    return true;
}

byte parsearElementoMatriz(const char *linea, tElementoMatriz *elem)
{
    byte cod = VAL;

    sscanf(linea, "[%d][%d] %d", &(elem->fila), &(elem->columna), &(elem->valor));

    if(validadorRangoMatriz(elem->fila, elem->columna) != VAL)
        cod = NO_VAL;

    return cod;
}
