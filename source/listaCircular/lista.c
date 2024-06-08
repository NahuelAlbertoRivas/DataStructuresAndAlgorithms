#include "lista.h"

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo)( (   !((nodo) = (tNodo *)malloc(tamNodo))    \
                                                              || !((info) = malloc(tamInfo)) )?          \
                                                                     free(nodo), SIN_MEM : OK            )

#define MINIMO(x, y)(((x)<(y))?(x):(y))

void crearLista(tLista *pl)
{
    *pl = NULL;
}

int listaVacia(const tLista *pl)
{
    return *pl == NULL;
}

int listaLlena(const tLista *pl, unsigned cantBytes)
{
    tNodo *nue;

    if(RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, cantBytes) == OK)
    {
        free(nue->info);
        free(nue);
    }

    return !nue || !(nue->info);
}

int insertarEnPila(tLista *pp, const void *info, unsigned tamInfo)
{
    tNodo *nue;

    if(RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, tamInfo) != OK)
        return SIN_MEM;

    memcpy(nue->info, info, (nue->tamInfo = tamInfo));

    if(*pp)
    {
        nue->sig = (*pp)->sig;
        (*pp)->sig = nue;
    }
    else
    {
        *pp = nue;
        nue->sig = *pp;
    }

    return OK;
}

int insertarEnCola(tLista *pc, const void *info, unsigned tamInfo)
{
    tNodo *nue;

    if(!RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, tamInfo))
        return SIN_MEM;

    memcpy(nue->info, info, (nue->tamInfo = tamInfo));

    if(*pc)
    {
        nue->sig = (*pc)->sig;
        (*pc)->sig = nue;
    }
    else
        nue->sig = nue;

    *pc = nue;

    return OK;
}

int verSiguiente(const tLista *pl, void *buffer, unsigned cantBytes)
{
    if(!(*pl))
        return LISTA_VACIA;

    memcpy(buffer, (*pl)->sig, MINIMO(cantBytes, (*pl)->sig->tamInfo));

    return OK;
}

int eliminarSiguiente(tLista *pl, void *buffer, unsigned cantBytes)
{
    tNodo *elim;

    if(!(*pl))
        return LISTA_VACIA;

    elim = (*pl)->sig;
    memcpy(buffer, elim->info, MINIMO(cantBytes, elim->tamInfo));
    if((*pl) == elim)
        *pl = NULL;
    free(elim->info);
    free(elim);

    return OK;
}

void vaciarLista(tLista *pl)
{
    while(*pl)
    {
        tNodo *elim = (*pl)->sig;
        (*pl)->sig = elim->sig;
        if((*pl) == elim)
            *pl = NULL;
        free(elim->info);
        free(elim);
    }
}
