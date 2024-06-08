#include "lotePrueba.h"
#include "../impuestosVencidos.h"
#define SRC_PATH "../source/Ejercicios/impuestosVencidos/files/impuestosVencidos.dat"
#include <winsock2.h>
#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void crearLoteImpVencidos()
{
    tImpuesto impuestos[] = {
    ///   patente,   nroCuota,   titular,    dni,      vto,      importe
        {"AA999BB",      1,     "Porsche", 34234432, 20200312,  42332.32},
        {"943NB32",      1,     "Pagani",  30232232, 20190521,  42332.32},
        {"AA999BB",      2,     "Porsche", 34234432, 20200312,  42332.32},
        {"943NB32",      2,     "Pagani",  30232232, 20200312,  42332.32},
        {"AA999BB",      6,     "Porsche", 34234432, 20200312,  42332.32},
        {"AA999BB",      1,     "Porsche", 34234432, 20200312,  42332.32},
        {"AA999BB",      1,     "Ferrari", 40654324, 20200312,  42332.32},
        {"943NB32",      1,     "Bugatti", 23533200, 20200312,  42332.32},
        {"GG753LC",      1,     "Bugatti", 23533200, 20200312,  42332.32},
        {"FFP213A",      10,     "Ferrari", 40654324, 20200312,  42332.32},
        {"AA999BB",      10,     "Porsche", 34234432, 20200312,  42332.32},
        {"943NB32",      0,     "Pagani",  30232232, 20190521,  42332.32},
        {"AA999BB",      22,     "Porsche", 34234432, 20200312,  42332.32},
        {"943NB32",      22,     "Pagani",  30232232, 20200312,  42332.32},
        {"AA999BB",      61,     "Porsche", 34234432, 20200312,  42332.32},
        {"AA999BB",      11,     "Porsche", 34234432, 20200312,  42332.32},
        {"AA999BB",      7,     "Ferrari", 40654324, 20200312,  42332.32},
        {"943NB32",      -1,     "Bugatti", 23533200, 20200312,  42332.32},
        {"GG753LC",      -456456546,     "Bugatti", 23533200, 20200312,  42332.32},
        {"FFP213A",      4734347348,     "Ferrari", 40654324, 20200312,  42332.32},
        {"AA999BB",      1,     "Porsche", 0000000000000, 20200312,  42332.32},
        {"943NB32",      1,     "Pagani",  435464565656, 20190521,  42332.32},
        {"AA999BB",      2,     "Porsche", -21321123, 20200312,  42332.32},
        {"943NB32",      2,     "Pagani",  1, 20200312,  42332.32},
        {"AA999BB",      6,     "Porsche", 3423, 20200312,  42332.32},
        {"AA999BB",      1,     "Porsche", 34234, 20200312,  42332.32},
        {"AA999BB",      1,     "Ferrari", 406543, 20200312,  42332.32},
        {"943NB32",      1,     "Bugatti", 2353320, 20200312,  42332.32},
        {"GG753LC",      1,     "Bugatti", 23533200, 20203312,  42332.32},
        {"FFP213A",      1,     "Ferrari", 40654324, 202003121,  42332.32},
        {"AA999BB",      1,     "Porsche", 34234432, 26756454,  42332.32},
        {"943NB32",      1,     "Pagani",  30232232, 3,  42332.32},
        {"AA999BB",      2,     "Porsche", 34234432, 2020,  42332.32},
        {"943NB32",      2,     "Pagani",  30232232, 202003,  42332.32},
        {"AA999BB",      6,     "Porsche", 34234432, -20200312,  42332.32},
        {"AA999BB",      1,     "Porsche", 34234432, 2020312,  42332.32},
        {"AA999BB",      1,     "Ferrari", 406543245, 20200312,  42332.32},
        {"02K",      1,     "Lamborhini", 3533200, 20200312,  42332.32},
        {"H H J T",      1,     "Rolls Royce", 23533200, 20200312,  42332.32},
        {"XM23",      6,     "Koegnigsegg", 40654324, 20200312,  42332.32}
    };
    FILE *pfLote = fopen(SRC_PATH, "wb");
    byte i;

    if(!pfLote)
        return;

    for(i = 0; i < (sizeof(impuestos) / sizeof(tImpuesto)); i++)
        fwrite(impuestos + i, sizeof(tImpuesto), 1, pfLote);

    fclose(pfLote);
}
