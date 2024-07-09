#include "TDA.h"

#define RESERV_MEM_NODO(nodo, tamNodo, info, tamInfo)\
( (   !( (nodo) = (tNodo *) malloc(tamNodo) )   \
   || !( (info) = malloc(tamInfo) )              )? \
            free(nodo), SIN_MEM : TODO_OK       )

#define MINIMO(x, y) ( ( (x) < (y) )? (x) : (y) )

void crearLista(tLista *pl)
{
    *pl = NULL;
}

bool listaVacia(tLista *pl)
{
    return *pl == NULL;
}

const void *verPrimero(tLista *pl, void *buffer, unsigned cantBytes)
{
    if(!(*pl))
        return NULL;

    if(buffer)
        memcpy(buffer, (*pl)->info, MINIMO(cantBytes, (*pl)->tamInfo));

    return (*pl)->info;
}

char insertarEnOrden(tLista *pl, const void *info, unsigned tamInfo, Comparar cmp, Acumular acm)
{
    tNodo *nue;

    while(*pl && cmp((*pl)->info, info) < 0)
            pl = &((*pl)->sig);
    if(*pl && !cmp((*pl)->info, info))
    {
        if(acm)
            acm(&((*pl)->info), &((*pl)->tamInfo), info, tamInfo);
        return CLA_DUP;
    }
    if(!RESERV_MEM_NODO(nue, sizeof(tNodo), nue->info, tamInfo))
        return SIN_MEM;

    memcpy(nue->info, info, (nue->tamInfo = tamInfo));

    nue->sig = *pl;
    *pl = nue;

    return TODO_OK;
}

void vaciarLista(tLista *pl)
{
    tNodo *elim;

    while(*pl)
    {
        elim = *pl;
        *pl = elim->sig;
        free(elim->info);
        free(elim);
    }
}

void mostrarYvaciarN(tLista *pl, unsigned n, FILE *pf, Mostrar mst)
{
    tNodo *elim;

    while(n && *pl)
    {
        elim = *pl;
        *pl = elim->sig;
        if(mst && pf)
            mst(elim->info, pf);
        free(elim->info);
        free(elim);
        n--;
    }
}
