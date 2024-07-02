#ifndef LISTA_SIMPLE_CIRCULAR
#define LISTA_SIMPLE_CIRCULAR

#include "../commonData/commonData.h"

typedef struct sNodoLSC
{
    void *info;
    unsigned tamInfo;
    struct sNodoLSC *sig;
} tNodoLSC;

typedef tNodoLSC *tListaCircular;

void crearLSC(tListaCircular *pl);

int insertarLSC(tListaCircular *pl, const void *info, unsigned tamInfo);

int eliminarSiguienteLSC(tListaCircular *pl, void *buffer, unsigned cantBytes);

void mostrarLSC(const tListaCircular *pl, FILE *pf, Mostrar mst);

int mapLSC(const tListaCircular *pl, void *recurso, AccionarSimple tarea);

void vaciarLSC(tListaCircular *pl);

int vaciarLSC2(tListaCircular *pl);

#endif
