#ifndef DEV
#define DEV

typedef struct sNodoArbol
{
    void *info;
    unsigned tamInfo;
    struct sNodoArbol *izq,
                      *der;
    
}tNodoArbol;

typedef tNodoArbol *tArbolBinBusq;

void crearArbol(tArbolBinBusq *pa);

int arbolVacio(tArbolBinBusq *pa);

#endif