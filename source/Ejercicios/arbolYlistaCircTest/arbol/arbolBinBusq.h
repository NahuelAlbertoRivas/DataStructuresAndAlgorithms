#ifndef ARBOLBINBUSQ
#define ARBOLBINBUSQ

#include "../commonData/commonData.h"

typedef struct sNodoArbol
{
    void *info;
    unsigned tamInfo;
    struct sNodoArbol *izq,
                      *der;
} tNodoArbol;

typedef tNodoArbol *tArbolBinBusq;

void crearArbol(tArbolBinBusq *pa);

int insertarEnArbol(tArbolBinBusq *pa, const void *info, unsigned tamInfo, Comparar cmp, Acumular acm);

void recorrerEnOrdenArbol(tArbolBinBusq *pa, void *recurso, Accionar tarea);

void recorrerEnOrdenRecArbol(tArbolBinBusq *pa, unsigned n, void *recurso, Accionar tarea);

void recorrerEnPreOrdenArbol(tArbolBinBusq *pa, void *recurso, Accionar tarea);

void recorrerEnPreOrdenRecArbol(tArbolBinBusq *pa, unsigned n, void *recurso, Accionar tarea);

void recorrerPosOrdenRecArbolOrdenArbol(tArbolBinBusq *pa, void *recurso, Accionar tarea);

void recorrerPosOrdenRecArbol(tArbolBinBusq *pa, unsigned n, void *recurso, Accionar tarea);

int alturaArbolBinBusq(tArbolBinBusq *pa);

int leerDesdeVector(void *info, unsigned tamInfo, unsigned pos, void *vec);

int cargarDesdeDatosOrdenados(tArbolBinBusq *pa, int li, int ls, void *fuente, unsigned tamInfo, Leer fCarga);

int cargarArchivoBinEnArbol(tArbolBinBusq *pa, unsigned tamInfo, FILE *pf);

int cargarVectorEnArbol(tArbolBinBusq *pa, unsigned tamInfo, unsigned ce, void *vec);

const void *buscarMenorClaveArbol(tArbolBinBusq *pa, void *buffer, unsigned cantBytes);

const void *buscarMayorClaveArbol(tArbolBinBusq *pa, void *buffer, unsigned cantBytes);

const void *buscarMayorNoClave(tArbolBinBusq *pa, void *buffer, unsigned cantBytes, Comparar cmp);

const void *buscarMenorNoClaveArbol(tArbolBinBusq *pa, void *buffer, unsigned cantBytes, Comparar cmp);

const void *buscarElemClaveArbol(tArbolBinBusq *pa, void *dato, unsigned cantBytes, Comparar cmp);

void vaciarArbol(tArbolBinBusq *pa);

int vaciarArbol2(tArbolBinBusq *pa);

#endif
