#ifndef ARBOLBINBUSQ
#define ARBOLBINBUSQ

#define ARBOL_VACIO 55235
#define ARBOL_LLENO 54235
#define SIN_MEM -123234
#define CLA_DUP 453321
#define TODO_OK 2321

typedef struct sNodoArbol
{
    void *info;
    unsigned tamInfo;
    struct sNodoArbol *izq,
                      *der;
} tNodoArbol;

typedef tNodoArbol *tArbolBinBusq;

typedef int (*Comparar)(const void *, const void *);

void crearArbol(tArbolBinBusq *pa);

int arbolVacio(const tArbolBinBusq *pa);

int arbolLleno(const tArbolBinBusq *pa, unsigned cantBytes);

int insertarEnArbol(tArbolBinBusq *pa, const void *info, unsigned tamInfo, Comparar cmp);

#endif
