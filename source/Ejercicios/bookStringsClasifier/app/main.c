#include "../sharedFns/dev.h"

#define SRC_PATH "../source/Ejercicios/bookStringsClasifier/app/quijote-es.txt"

int bookStringsClasifier(void *recursos)
{
    setlocale(LC_ALL, "Spanish");
    int mayorCnt = 0,
        menorCnt = -1;
    tArbolBinBusq palabras;

    crearArbolBinBusq(&palabras);

    procesarLibro(SRC_PATH, &palabras);

    if(!arbolVacio(&palabras))
    {
        recorrerEnOrdenSimpleArbolBinBusq(&palabras, &mayorCnt, buscarMayor);
        recorrerEnOrdenSimpleArbolBinBusq(&palabras, &menorCnt, buscarMenor);

        menu(mayorCnt, menorCnt, &palabras);
    }

    eliminarArbol(&palabras);

    return 0;
}
