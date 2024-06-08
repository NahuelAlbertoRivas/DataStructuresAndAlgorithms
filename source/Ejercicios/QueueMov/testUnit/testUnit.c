#include "testUnit.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM_LINEA 201

void crearArchivoBienFormatMovs()
{
    FILE *pfMovs = fopen("../files/movimientosStock.txt", "wt");
    char movements[][MAX_TAM_LINEA] =
    {
        {"a    e      x7        45"},
        {"a s x2 945656   "},
        {"a s x2 10"},
        {"b e x1 54"},
        {" b  s   x90            5"},
        {"  C e x1 20"},
        {"c s x8       29"},
        {"d s x5 50"},
        {"e S x3 5345135415354353453453445155434353645"},
        {"e s x8 10"},
        {"E S X9 30"},
        {"f s x5 40"},
        {"f e x2 20"},
        {"f s x3 50"},
        {"  g   s   x1    15    "},
        {"h s x3 1"},
        {"h s x2 2"},
        {"h s x1 3"},
        {"i e x7 2"},
        {"i e x3 1"},
        {"i e x6 1"},
        {"i e x1 5"},
        {"i     e    x3     10"},
        {"i|e|x4|10"},
        {"i                    e x7 10"},
        {"                                               i e x2 10"},
        {"fin"}
    };
    int i;

    if(!pfMovs)
        return;

    for(i = 0; strcmpi(movements[i], "fin"); i++)
        fprintf(pfMovs, "%s\n", movements[i]);

    fclose(pfMovs);
}

/// en la versión presente todavía no se desarrolló lógica complementaria sobre qué decidir particularmente
/// ante los casos planteados dentro de este segundo lote, sin embargo, los registros no llegan a provocar
/// que el programa crashee
void crearArchivoMalFormatMovs()
{
    FILE *pfMovs = fopen("../files/movimientosStock.txt", "wt");
    char movements[][MAX_TAM_LINEA] =
    {
        {"    A    e      x7        45          ..--.-..fsdgfsdg"},
        {"65464645654a      s gdsfg 43h34h534hu5h4.........945656°°||||"},
        {"a s   x2  10"},
        {"bex154"},
        {" b  s   x90                               5"},
        {"C     e   x1  20"},
        {"c s   x8  29"},
        {"d|etc|50"},
        {"estacionamiento ?????  5345135415354353453453445155434353645"},
        {"e salida departamento x8  cantidad movimientos -->>>>10<<<---"},
        {"E 30"},
        {"\n\\m\\j\\l\\o\\b' ' "" "   " "},
        {"juju"},
        {"\0\0\0\0"},
        {"57345476534547563464565"},
        {"-+{+{{+4{23+24234"},
        {"                                               "},
        {"f s x5 40"},
        {"f e x2 20"},
        {"f s x3 50"},
        {"código producto: g\ntipo de movimiento: salida\tdepto.: N/A\0cantidad de movis->+- 15"},
        {"{""}  {"                  "}"},
        {"fin"}
    };
    int i;

    if(!pfMovs)
        return;

    for(i = 0; strcmpi(movements[i], "fin"); i++)
        fprintf(pfMovs, "%s\n", movements[i]);

    fclose(pfMovs);
}
