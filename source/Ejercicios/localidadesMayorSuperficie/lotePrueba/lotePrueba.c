#include "lotePrueba.h"
#include "../locMayorSup.h"
#define SRC_PATH "../source/Ejercicios/localidadesMayorSuperficie/files/lote.dat"
#include <winsock2.h>
#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void crearLoteLocalidades()
{
    tLocalidad localidades[] = {
    ///  provincia,   localidad,    superficie,       población
        {1,           "Firense",     34234.34,        2020},
        {2,           "3 Arroyos",   10232.32,        2019},
        {7,           "Necochea",    34234.32,        2020},
        {3,           "Avellaneda",  30232.32,        2020},
        {17,          "Bolivares",   34234.32,        2020},
        {1,           "Nordelta",    34234.32,        2020},
        {1,           "Ferrari",     40654.24,        2020},
        {16,          "Washington",  23533.00,        2020},
        {19,          "Bugatti",     23533.00,        2020.6},
        {10,          "Kingston",    40654.24,        2020},
        {23,          "Porsche",     34234.32,        2020},
        {20,          "Pagani",      20232.32,        2019},
        {22,          "Wellin",      34234.32,        2020},
        {22,          "Henzel",      60232.32,        2020},
        {21,          "Roadster",    34234.32,        2020},
        {11,          "SVJ",         34234.32,        2020},
        {7,           "Varisto",     40654.24,        2020},
        {13,          "Hint",        23533.00,        2020},
        {-456456546,  "Huayra",      23533.00,        2020},
        {4734347348,  "Lloris",      40654.24,        2020},
        {5,           "Gumpert", 0000000000, 2020},
        {-1,          "Rover",       435464565656,    2019},
        {12,          "Land",        -21321123,       -202},
        {25,          "Hellcat",     1,               2020},
        {18,          "Richmond",    53423,           20200312},
        {14,          "Agera",       33423.4,         20},
        {1,           "Jacob & Co",     94065.43,        212},
        {16,          "Zanotti",     54322.320,       2312},
        {17,          "Giuseppe",    92353.3200,      3312},
        {1,           "LVHM",        14065.4324,      2121},
        {22,          "La Voiture Noire",     63423.4432,      6454},
        {2,           "Pontiac",     33023.2232,      3},
        {11,          "Maybach",     83423.4432,      202},
        {9,           "Bolide",      53023.2232,      2023},
        {3,           "Panamera",    33423.4432,      0312},
        {4,           "Paulvic",  43423.4432,      0},
        {12,          "Bentley",     4065.43245,      312},
        {10,          "Chiron",      13533.200,       2312},
        {5,           "Rolls Royce", 42353.3200,      22},
        {6,           "Koegnigsegg", 24065.4324,      9999},
        {1,           "Firense",     34234.34,        2020},
        {2,           "3 Arroyos",   30232.32,        2019},
        {7,           "Necochea",    34234.32,        2020},
        {31,          "Avellaneda",  30232.32,        2020},
        {12,          "Bolivares",   34234.32,        2020},
        {1,           "Nordelta",    34234.32,        2020},
        {-1,          "Ferrari",     40654.24,        2020},
        {333,         "Washington",  23533.00,        2020},
        {19,          "Bugatti",     23533.00,        2020},
        {10,          "Kingston",    40654.24,        2020},
        {-23,         "Porsche",     34234.32,        2020},
        {20,          "Pagani",      80232.32,        2019},
        {22,          "Wellin",      34234.32,        2020},
        {22,          "Henzel",      80232.32,        2020},
        {11,          "Giuseppe",    92353.3200,      3312},
        {3,           "Moet",        0,               332}
    };
    FILE *pfLote = fopen(SRC_PATH, "wb");
    byte i;

    if(!pfLote)
        return;

    for(i = 0; i < (sizeof(localidades) / sizeof(tLocalidad)); i++)
        fwrite(localidades + i, sizeof(tLocalidad), 1, pfLote);

    fclose(pfLote);
}
