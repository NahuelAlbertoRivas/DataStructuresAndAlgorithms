#ifndef COMMONDATA
#define COMMONDATA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <winsock2.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>

#define PATH_PROD_OK "../files/prod_ok.dat"
#define PATH_PROD_VENCE "../files/prod_a_vencer.txt"
#define PATH_STOCK "../files/stock.dat"

#define TAM_CODPROD 7
#define TAM_DESC 26

typedef struct
{
    int dd,
        mm,
        aaaa;
} tFecha;

typedef struct
{
    char codProd[TAM_CODPROD],
         descrip[TAM_DESC];
    int nroLote;
    tFecha vto;
    unsigned cantStock;
} tRegStock;

typedef struct
{
    int nro;
    tFecha vto;
    unsigned cantStock;
} tLote;


#endif
