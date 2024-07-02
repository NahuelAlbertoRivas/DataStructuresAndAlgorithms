#include "lista.h"

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo) (  (   !( (nodo) = (tNodoLSC *) malloc(tamNodo) )     \
                                                                || !( (info) = malloc(tamInfo) )              )?  \
                                                                       free(nodo), SIN_MEM : TODO_OK              )


void crearLSC(tListaCircular *pl)
{
    *pl = NULL;
}

int insertarLSC(tListaCircular *pl, const void *info, unsigned tamInfo)
{
    tNodoLSC *nue;

    if(RESERVAR_MEMORIA_NODO(nue, sizeof(tNodoLSC), nue->info, tamInfo) != TODO_OK)
        return SIN_MEM;

    memcpy(nue->info, info, tamInfo);

    if(*pl)
    {
        nue->sig = (*pl)->sig;
        (*pl)->sig = nue;
    }
    else
        nue->sig = nue;

    *pl = nue;

    return TODO_OK;
}

int eliminarSiguienteLSC(tListaCircular *pl, void *buffer, unsigned cantBytes)
{
    tNodoLSC *elim;

    if(!(*pl))
        return LISTA_VACIA;

    elim = (*pl)->sig;
    if(elim == *pl)
        *pl = NULL;
    else
        (*pl)->sig = elim->sig;

    if(buffer)
        memcpy(buffer, elim->info, MINIMO(cantBytes, elim->tamInfo));

    free(elim->info);
    free(elim);

    return TODO_OK;
}

void mostrarLSC(const tListaCircular *pl, FILE *pf, Mostrar mst)
{
    tNodoLSC *act;

    if(!(*pl))
        return;

    act = (*pl)->sig;

    while(act != *pl)
    {
        mst(act->info, pf);
        act = act->sig;
    }
    mst(act->info, pf);
}

int mapLSC(const tListaCircular *pl, void *recurso, AccionarSimple tarea)
{
    tNodoLSC *act;
    unsigned cant = 0;

    if(!(*pl))
        return cant;

    act = (*pl)->sig;

    while(act != *pl)
    {
        tarea(act->info, recurso);
        act = act->sig;
        cant++;
    }
    tarea(act->info, recurso);
    cant++;

    return cant;
}

void vaciarLSC(tListaCircular *pl)
{
    tNodoLSC *elim;

    while(*pl)
    {
        elim = (*pl)->sig;
        if(elim == *pl)
            *pl = NULL;
        else
            (*pl)->sig = elim->sig;
        free(elim->info);
        free(elim);
    }
}

int vaciarLSC2(tListaCircular *pl)
{
    tNodoLSC *elim;
    unsigned cant = 0;

    while(*pl)
    {
        elim = (*pl)->sig;
        if(elim == *pl)
            *pl = NULL;
        else
            (*pl)->sig = elim->sig;
        free(elim->info);
        free(elim);
        cant++;
    }

    return cant;
}
