#include "listaDoblemente.h"

void crearLista(tLista *pl)
{
    *pl = NULL;
}

int listaVacia(const tLista *pl)
{
    return (*pl) == NULL;
}

int insertarAlComienzo(tLista *pl, const void *info, unsigned cantBytes)
{
    tNodo *act = *pl,
           *nue;

    if(!(nue = (tNodo *) malloc(sizeof(tNodo))) || !(nue->info = malloc(cantBytes))) /// me fijo si tengo memoria
    {
        free(nue);
        return SIN_MEM;
    }

    if(act) /// encuentro la posición
        while(act->ant)
            act = act->ant;

    memcpy(nue->info, info, (nue->tamInfo = cantBytes)); /// realizo la copia de la info. y asignación de su tamaño

    nue->ant = NULL; /// cableo
    nue->sig = act;
    if(act)
        act->ant = nue;
    *pl = nue;

    return TODO_OK;
}

int insertarAlFinal(tLista *pl, const void *info, unsigned cantBytes)
{
    tNodo *act = *pl,
           *nue;

    if(!(nue = (tNodo*) malloc(sizeof(tNodo))) || !(nue->info = malloc(cantBytes))) /// reservo memoria
    {
        free(nue);
        return SIN_MEM;
    }

    if(act) /// si hay al menos dos nodos encuentro la posición del nuevo
        while(act->sig)
            act = act->sig;

    memcpy(nue->info, info, (nue->tamInfo = cantBytes)); /// copio info

    nue->sig = NULL; /// cableo
    nue->ant = act;
    if(act)
        act->sig = nue;
    *pl = nue;

    return TODO_OK;
}

int mostrarIzqADer(const tLista *pl, Mostrar mostrar, FILE *pf)
{
    tNodo *act = *pl;
    int ce = 0;

    if(!act)
        return LISTA_VACIA;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        mostrar(&(act->info), pf);
        act = act->sig;
        ce++;
    }

    return ce;
}

int mostrarDerAIzq(const tLista *pl, Mostrar mostrar, FILE *pf)
{
    tNodo *act = *pl;
    int ce = 0;

    if(!act)
        return LISTA_VACIA;

    while(act->sig)
        act = act->sig;

    while(act)
    {
        mostrar(&(act->info), pf);
        act = act->ant;
        ce++;
    }

    return ce;
}

int mapLista(tLista *pl, Accion tarea)
{
    tNodo *act = *pl;
    int ce = 0;

    if(!act)
        return LISTA_VACIA;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        tarea(act->info);
        act = act->sig;
        ce++;
    }

    return ce;
}

int mapLista2(tLista *pl, Accion tarea)
{
    tNodo *act = *pl,
           *ant = act->ant;
    int ce = 0;

    while(ant)
    {
        tarea(ant->info);
        ant = ant->ant;
        ce++;
    }
    while(act)
    {
        tarea(act->info);
        act = act->sig;
        ce++;
    }

    return ce;
}

int filterLista(tLista *pl, void *recurso, Comparacion cmp)
{
    tNodo *act = *pl,
           *ant,
           *sig;

    if(!act)
        return LISTA_VACIA;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        if(!cmp(act->info, recurso))
        {
            sig = act->sig;
            ant = act->ant;
            if(ant)
                ant->sig = sig;
            if(sig)
                sig->ant = ant;
            free(act->info);
            free(act);
        }
        act = act->sig;
    }

    return 1;
}

int filterLista2(tLista *pl, void *recurso, Comparacion cmp)
{
    tNodo *actDer = *pl,            /// para recorrer desde el nodo actual hacia derecha
           *actIzq = (*pl)->ant,    /// para recorrer desde el nodo anterior al actual hacia izquierda
            *ant,
            *sig;

    while(actIzq)
    {
        if(!cmp(actIzq->info, recurso))
        {
            sig = actIzq->sig;
            ant = actIzq->ant;
            if(ant)
                ant->sig = sig;
            if(sig)
                sig->ant = ant;
            free(actIzq->info);
            free(actIzq);
        }
        actIzq = actIzq->ant;
    }
    while(actDer)
    {
        if(!cmp(actDer->info, recurso))
        {
            sig = actDer->sig;
            ant = actDer->ant;
            if(ant)
                ant->sig = sig;
            if(sig)
                sig->ant = ant;
            free(actDer->info);
            free(actDer);
        }
        actDer = actDer->sig;
    }

    return TODO_OK;
}

int insertarEnOrden(tLista *pl, const void *info, unsigned cantBytes, Comparacion cmp, Acumular acm)
{
    tNodo *act = *pl,
           *sig,
           *nue;

    if(!act) /// me fijo si hay elementos en la lista así encontrar la posición para agrupar/insertar el nuevo o bien dejar el contexto preparado para la primer inserción
        sig = act;
    else
    {
        while(act->sig && (cmp(act->info, info) < 0))
            act = act->sig;
        while(act->ant && (cmp(act->info, info) > 0))
            act = act->ant;

        if(!cmp(act->info, info))
        {
            if(acm)
                if(!acm(&((act)->info), &((act)->tamInfo), info, cantBytes))
                    return SIN_MEM;
            return CLA_DUP;
        }
        sig = act->sig;
    }
    /// si no es repetido, debo insertar ya que previamente encontramos dónde debe ubicarse (o bien será el primero)
    if(!(nue = (tNodo *) malloc(sizeof(tNodo))) || !(nue->info = malloc(cantBytes)))
    {
        free(nue);
        return SIN_MEM;
    }
    memcpy(nue->info, info, (nue->tamInfo = cantBytes));
    if(act)
        act->sig = nue;
    if(sig)
        sig->ant = nue;
    nue->ant = act;
    nue->sig = sig;

    *pl = nue;

    return TODO_OK;
}

int vaciarLista(tLista *pl)
{
    int ce = 0;
    tNodo *act = *pl,
           *ant,
            *elim;

    if(!act)
        return LISTA_VACIA;

    ant = act->ant;

    while(ant)
    {
        elim = ant;
        ant = ant->ant;
        free(elim->info);
        free(elim);
        ce++;
    }
    while(act)
    {
        elim = act;
        act = act->sig;
        free(elim->info);
        free(elim);
        ce++;
    }
    *pl = NULL;

    return ce;
}
