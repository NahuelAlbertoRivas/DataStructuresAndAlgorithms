#ifndef L_TDA
#define L_TDA

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define SIN_MEM 0
#define TODO_OK 1
#define CLA_DUP 2
#define ERR_PARAMS 3
#define ERR_ARCH 4
#define SIN_INICIALIZAR 5
#define ARBOL_VACIO 6

typedef struct sNodoArbol
{
    void *info;
    unsigned tamInfo;
    struct sNodoArbol *izq,
                      *der;
} tNodoArbol;

typedef tNodoArbol *tArbolBinBusq;

typedef int (*Comparar)(const void *, const void *);

typedef void (*Accionar)(void *, unsigned, unsigned, void *);
typedef void (*AccionarSimple)(void *, unsigned, void *);

typedef int (*Acumular)(void **, unsigned *, const void *, unsigned);

typedef void (*Mostrar)(const void *, FILE *);

typedef int (*Leer)(void *, unsigned, unsigned, void *);

void crearArbol(tArbolBinBusq *pa);

int insertarEnArbolBin(tArbolBinBusq *pa, const void *info, unsigned tamInfo, Comparar cmp, Acumular acm);

void recorrerEnOrdenSimpleArbolBinBusq(tArbolBinBusq *pa, void *recurso, AccionarSimple task);
void recorrerEnOrdenArbolBinBusq(tArbolBinBusq *pa, void *recurso, Accionar task);
void recorrerEnPreOrdenSimpleArbolBinBusq(tArbolBinBusq *pa, void *recurso, AccionarSimple task);
void recorrerEnPreOrdenArbolBinBusq(tArbolBinBusq *pa, void *recurso, Accionar task);

int cargarArbolDesdeArchivoBin(tArbolBinBusq *pa, unsigned tamInfo, FILE *pf);

int cargarDesdeDatosOrdenados(tArbolBinBusq *pa, void *fuente, unsigned tamInfo, int li, int ls, Leer fCarga);

int leerDeArchivo(void *info, unsigned tamInfo, unsigned pos, void *fuente);

void grabarEnArchivo(void *info, unsigned tamInfo, void *recurso);

int guardarArbolEnOrdenAchivoBin(tArbolBinBusq *pa, FILE *pf);

unsigned alturaArbol(const tArbolBinBusq *pa);

unsigned contarNodosDelArbol(const tArbolBinBusq *pa);

bool esArbolAVL(const tArbolBinBusq *pa);

void vaciarArbol(tArbolBinBusq *pa);

#endif
