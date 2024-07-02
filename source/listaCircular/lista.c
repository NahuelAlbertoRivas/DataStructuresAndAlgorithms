#include "lista.h"

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo)( (   !((nodo) = (tNodo *)malloc(tamNodo))    \
                                                              || !((info) = malloc(tamInfo)) )?          \
                                                                     free(nodo), SIN_MEM : OK            )

#define MINIMO(x, y)(((x)<(y))?(x):(y))

void crearListaCirc(tLista *pl)
{
    *pl = NULL;
}

int listaVaciaCirc(const tLista *pl)
{
    return *pl == NULL;
}

int listaLlenaCirc(const tLista *pl, unsigned cantBytes)
{
    tNodo *nue;

    if(RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, cantBytes) == OK)
    {
        free(nue->info);
        free(nue);
    }

    return !nue || !(nue->info);
}

int insertarEnListaCirc(tLista *pc, const void *info, unsigned tamInfo)
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

//void mostrarLSC(const tLista *pl, FILE *pf, Mostrar mst)
//{
//    tNodo *act;
//
//    if(!(*pl))
//        return;
//
//    act = (*pl)->sig;
//
//    while(act != *pl)
//    {
//        mst(act->info, pf);
//        act = act->sig;
//    }
//    mst(act->info, pf);
//}
//
//int mapLSC(const tLista *pl, void *recurso, AccionarSimple tarea)
//{
//    tNodo *act;
//    unsigned cant = 0;
//
//    if(!(*pl))
//        return cant;
//
//    act = (*pl)->sig;
//
//    while(act != *pl)
//    {
//        tarea(act->info, recurso);
//        act = act->sig;
//        cant++;
//    }
//    tarea(act->info, recurso);
//    cant++;
//
//    return cant;
//}

void vaciarListaCirc(tLista *pl)
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

//void vaciarLSC(tLista *pl)
//{
//    tNodo *elim;
//
//    while(*pl)
//    {
//        elim = (*pl)->sig;
//        if(elim == *pl)
//            *pl = NULL;
//        else
//            (*pl)->sig = elim->sig;
//        free(elim->info);
//        free(elim);
//    }
//}
//
//int vaciarLSC2(tLista *pl)
//{
//    tNodo *elim;
//    unsigned cant = 0;
//
//    while(*pl)
//    {
//        elim = (*pl)->sig;
//        if(elim == *pl)
//            *pl = NULL;
//        else
//            (*pl)->sig = elim->sig;
//        free(elim->info);
//        free(elim);
//        cant++;
//    }
//
//    return cant;
//}
