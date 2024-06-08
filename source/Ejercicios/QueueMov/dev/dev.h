#ifndef DEV
#define DEV

#include "../../../colaDinamica/cola.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_APERTURA_ARCH 96348
#define SIN_CONTENIDO 442
#define FIN_PROCESO 4343
#define ERR_PARAMS 46432
#define LECTURA_CORRECTA 345243
#define LECTURA_DEFECTUOSA -53125

typedef struct
{
    char codProd;
    unsigned cantMovimientos;
} regProd;

int procesarMovimientos(const char *path);

int leerMov(FILE *pfMovs, regProd *prodInfo, tCola *movimientos);

int recuperarCodProd(const char *linea, char *codProd);

int recuperarCantMovs(const char *linea, unsigned *cantMovs);

int sacarNyGrabarEnArchivo(tCola *movimientos, FILE *pfReporte, unsigned cant);

#endif
