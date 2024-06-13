#include "../sharedFns/dev.h"

#define SRC_PATH "../source/Ejercicios/bookStringsClasifier/app/quijote-es.txt"

int bookStringsClasifier(void *recursos)
{
    int mayorCnt = 0,
        menorCnt = -1;
    tArbolBinBusq palabras;
    char setSeparadores[] = " .,;!¡:    -_|¿?*+{}()\"\'~´`[]/\\ $#%&°<>»�«"; /// sería propio mandarlo por arg a main pero es un proyecto muy grande este

    crearArbolBinBusq(&palabras);

    procesarLibro(SRC_PATH, &palabras, setSeparadores);

    if(!arbolVacio(&palabras))
    {
        recorrerEnOrdenSimpleArbolBinBusq(&palabras, &mayorCnt, buscarMayor);
        recorrerEnOrdenSimpleArbolBinBusq(&palabras, &menorCnt, buscarMenor);

        menu(mayorCnt, menorCnt, &palabras);
    }

    eliminarArbol(&palabras);

    return 0;
}
