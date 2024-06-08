#include "pila.h"
#include <stdlib.h>
#include <string.h>

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo) ( (   !((nodo) = (tNodo *) malloc(tamNodo))    \
                                                                || !((info)= malloc(tamInfo))          )?  \
                                                                   free(nodo), SIN_MEM : TODO_OK           )
#define MINIMO(x, y) ((x) <= (y)? (x) : (y))

void crearPila(tPila *pp)
{
    *pp = NULL;
}

int pilaVacia(const tPila *pp)
{
    return *pp == NULL;
}

int pilaLlena(const tPila *pp, unsigned tamInfo)
{
    tNodo *nue;

    if(RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, tamInfo))
    {
        free(nue->info);
        free(nue);
    }

    return !nue || !nue->info;
}

int ponerEnPila(tPila *pp, const void *info, unsigned tamInfo)
{
    tNodo *nue;

    if(!RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, tamInfo))
        return SIN_MEM;

    memcpy(nue->info, info, (nue->tamInfo = tamInfo));
    nue->sig = *pp;
    *pp = nue;

    return TODO_OK;
}

int verTope(const tPila *pp, void *buffer, unsigned cantBytes)
{
    if(!(*pp))
        return PILA_VACIA;

    memcpy(buffer, (*pp)->info, MINIMO(cantBytes, (*pp)->tamInfo));

    return TODO_OK;
}

int sacarDePila(tPila *pp, void *buffer, unsigned cantBytes)
{
    tNodo *elim = *pp;

    if(!elim)
        return SIN_MEM;

    *pp = elim->sig;
    memcpy(buffer, elim->info, MINIMO(cantBytes, elim->tamInfo));
    free(elim->info);
    free(elim);

    return TODO_OK;
}

void vaciarPila(tPila *pp)
{
    while(*pp)
    {
        tNodo *elim = *pp;
        *pp = elim->sig;
        free(elim->info);
        free(elim);
    }
}
