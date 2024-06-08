#include "cola.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo) ( (   !( (nodo) = (tNodo *) malloc(tamNodo) )    \
                                                              || !( (info) = malloc(tamInfo) )  )?          \
                                                                        free(nodo), SIN_MEM : TODO_OK       )

#define MINIMO(x, y) ( ( (x) < (y) )? (x) : (y) )

void crearCola(tCola *pc)
{
    pc->pri = pc->ult = NULL;
}

int colaVacia(const tCola *pc)
{
    return pc->pri == NULL;
}

int colaLlena(const tCola *pc, unsigned cantBytes)
{
    tNodo *nue;

    if(RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, cantBytes))
    {
        free(nue->info);
        free(nue);
    }

    return !nue || !(nue->info);
}

int ponerEnCola(tCola *pc, const void *info, unsigned tamInfo)
{
    tNodo *nue;

    if(!RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, tamInfo))
        return SIN_MEM;

    memcpy(nue->info, info, (nue->tamInfo = tamInfo));
    nue->sig = NULL;
    if(pc->ult)
        pc->ult->sig = nue;
    else
        pc->pri = nue;
    pc->ult = nue;

    return TODO_OK;
}

int verPrimero(const tCola *pc, void *buffer, unsigned cantBytes)
{
    if(!(pc->pri))
        return COLA_VACIA;

    memcpy(buffer, pc->pri->info, MINIMO(cantBytes, pc->pri->tamInfo));

    return TODO_OK;
}

int sacarDeCola(tCola *pc, void *buffer, unsigned cantBytes)
{
    tNodo *elim = pc->pri;

    if(!elim)
        return COLA_VACIA;

    pc->pri = elim->sig;
    memcpy(buffer, elim->info, MINIMO(cantBytes, elim->tamInfo));
    if(!(pc->pri))
        pc->ult = NULL;
    free(elim->info);
    free(elim);

    return TODO_OK;
}

void vaciarCola(tCola *pc)
{
    while(pc->pri)
    {
        tNodo *elim = pc->pri;
        pc->pri = elim->sig;
        free(elim->info);
        free(elim);
    }

    pc->ult = NULL;
}
