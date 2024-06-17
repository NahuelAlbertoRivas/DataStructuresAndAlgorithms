#include "listaDoblemente.h"

#define SIN_MEM 0

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo)( (   !( (nodo) = (tNodoListaDoble *) malloc(tamNodo) )    \
                                                              || !( (info) = malloc(tamInfo) )                     )? \
                                                                    free(nodo), SIN_MEM : TODO_OK                     )

tNodoListaDoble *buscarNodoMenorClaveListaDoble(tListaDoble *pl, Comparacion cmp);

void crearListaDoble(tListaDoble *pl)
{
    *pl = NULL;
}

int listaVaciaDoble(const tListaDoble *pl)
{
    return (*pl) == NULL;
}

int insertarAlComienzoListaDoble(tListaDoble *pl, const void *info, unsigned cantBytes)
{
    tNodoListaDoble *act = *pl,
                    *nue;

    if(RESERVAR_MEMORIA_NODO(nue, sizeof(tNodoListaDoble), nue->info, cantBytes) != TODO_OK) /// me fijo si tengo memoria
        return SIN_MEM;

    if(act) /// encuentro la posici�n
        while(act->ant)
            act = act->ant;

    memcpy(nue->info, info, (nue->tamInfo = cantBytes)); /// realizo la copia de la info. y asignaci�n de su tama�o

    nue->ant = NULL; /// cableo
    nue->sig = act;
    if(act)
        act->ant = nue;
    *pl = nue;

    return TODO_OK;
}

int eliminarPrimeroListaDoble(tListaDoble *pl)
{
    tNodoListaDoble *act = *pl;

    if(!act)
        return LISTA_VACIA;

    while(act->ant)
        act = act->ant;

    free(act->info);
    free(act);
    act = NULL;

    return TODO_OK;
}

int insertarAlFinalListaDoble(tListaDoble *pl, const void *info, unsigned cantBytes)
{
    tNodoListaDoble *act = *pl,
                    *nue;

    if(act) /// si hay al menos dos nodos encuentro la posici�n del nuevo
        while(act->sig)
            act = act->sig;

    if(RESERVAR_MEMORIA_NODO(nue, sizeof(tNodoListaDoble), nue->info, cantBytes) != TODO_OK)
        return SIN_MEM;

    memcpy(nue->info, info, (nue->tamInfo = cantBytes)); /// copio info

    nue->sig = NULL; /// cableo
    nue->ant = act;
    if(act)
        act->sig = nue;
    *pl = nue;

    return TODO_OK;
}

int eliminarUltimoListaDoble(tListaDoble *pl)
{
    tNodoListaDoble *act = *pl;

    if(!act)
        return LISTA_VACIA;

    while(act->sig)
        act = act->sig;

    free(act->info);
    free(act);
    act = NULL;

    return TODO_OK;
}

/// la siguiente fn. es muy parecida al filter, pero elimina una �nica existencia,
/// la primera encontrada considerando desde el inicio de la lista
int eliminarPorClaveListaDoble(tListaDoble *pl, void *dato, unsigned cantBytes, Comparacion cmp)
{
    tNodoListaDoble *act = *pl,
                    *ant,
                    *sig;

    if(!act)
        return LISTA_VACIA;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        if(!cmp(act->info, dato))
        {
            ant = act->ant;
            sig = act->sig;
            if(ant)
                ant->sig = sig;
            if(sig)
                sig->ant = act->ant;
            free(act->info);
            free(act);
            act = NULL;
            ant?
                (*pl = ant)
              : (*pl = sig);
            return TODO_OK;
        }
        else
            act = act->sig;
    }

    return SIN_COINCIDENCIAS;
}

int mostrarIzqADer(const tListaDoble *pl, Mostrar mostrar, FILE *pf)
{
    tNodoListaDoble *act = *pl;
    int ce = 0;

    if(!act)
        return LISTA_VACIA;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        mostrar(act->info, pf);
        act = act->sig;
        ce++;
    }

    return ce;
}

int mostrarDerAIzq(const tListaDoble *pl, Mostrar mostrar, FILE *pf)
{
    tNodoListaDoble *act = *pl;
    int ce = 0;

    if(!act)
        return LISTA_VACIA;

    while(act->sig)
        act = act->sig;

    while(act)
    {
        mostrar(act->info, pf);
        act = act->ant;
        ce++;
    }

    return ce;
}

tNodoListaDoble *buscarNodoMenorClaveListaDoble(tListaDoble *pl, Comparacion cmp)
{
    tNodoListaDoble *act = *pl,
                    *ant,
                    *menor;

    if(!act)
        return NULL;

    menor = act;
    act = act->sig;
    ant = act->ant;

    while(ant)
    {
        if(cmp(ant->info, menor->info) < 0)
            menor = ant;
        else
            ant = ant->ant;
    }
    while(act)
    {
        if(cmp(act->info, menor) < 0)
            menor = act;
        else
            act = act->sig;
    }

    return menor;
}

int ordenarListaDoble(tListaDoble *pl, Comparacion cmp)
{
    tNodoListaDoble *menor,
                    *ant,
                    *sig;

    if(!(*pl))
        return LISTA_VACIA;

    while(*pl)
    {
        menor = buscarNodoMenorClaveListaDoble(pl, cmp);
        ant = menor->ant;
        sig = menor->sig;
        if(ant)
            ant->sig = sig;
        if(sig)
            sig->ant = ant;
        *pl = menor;
        pl = &((*pl)->sig);
    }

    return TODO_OK;
}

int mapListaDoble(tListaDoble *pl, Accion tarea)
{
    tNodoListaDoble *act = *pl;
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

int mapListaDoble2(tListaDoble *pl, Accion tarea)
{
    tNodoListaDoble *act = *pl,
                    *ant;
    int ce = 0;

    if(!act)
        return ce;

    ant = act->ant;

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

int filterListaDoble(tListaDoble *pl, void *recurso, Comparacion cmp)
{
    tNodoListaDoble *act = *pl,
                    *ant,
                    *sig,
                    *elim;

    unsigned cantElim = 0;

    if(!act)
        return cantElim;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        if(!cmp(act->info, recurso))
        {
            elim = act;
            act = elim->sig;
            sig = elim->sig;
            ant = elim->ant;
            if(ant)
                ant->sig = sig;
            if(sig)
                sig->ant = ant;
            free(elim->info);
            free(elim);
            elim = NULL;
            cantElim++;
        }
        else
            act = act->sig;
    }

    if(cantElim)
        ant?
            (*pl = ant)
          : (*pl = sig);

    return cantElim;
}

int filterListaDoble2(tListaDoble *pl, void *recurso, Comparacion cmp)
{
    tNodoListaDoble *actDer = *pl,        /// para recorrer desde el nodo actual hacia derecha
                    *actIzq,              /// para recorrer desde el nodo anterior al actual hacia izquierda
                    *ant,
                    *sig,
                    *elim;
    unsigned cantElim = 0;

    if(!actDer)
         return cantElim;

    actIzq = actDer->ant;

    while(actIzq)
    {
        if(!cmp(actIzq->info, recurso))
        {
            elim = actIzq;
            actIzq = actIzq->ant;
            sig = elim->sig;
            ant = elim->ant;
            if(ant)
                ant->sig = sig;
            if(sig)
                sig->ant = ant;
            free(elim->info);
            free(elim);
            elim = NULL;
            cantElim++;
        }
        else
            actIzq = actIzq->ant;
    }
    if(cantElim)
        ant?
            (*pl = ant)
          : (*pl = sig);
    while(actDer)
    {
        if(!cmp(actDer->info, recurso))
        {
            elim = actDer;
            actDer = elim->sig;
            sig = elim->sig;
            ant = elim->ant;
            if(ant)
                ant->sig = sig;
            if(sig)
                sig->ant = ant;
            free(elim->info);
            free(elim);
            elim = NULL;
            cantElim++;
        }
        else
            actDer = actDer->sig;
    }

    if(cantElim)
        ant?
            (*pl = ant)
          : sig?
                (*pl = sig)
              : (*pl = *pl);

    return cantElim;
}

int insertarEnOrdenListaDoble(tListaDoble *pl, const void *info, unsigned cantBytes, Comparacion cmp, Acumular acm)
{
    tNodoListaDoble *act = *pl,
                    *sig,
                    *nue;

    if(!act) /// me fijo si hay elementos en la lista as� encontrar la posici�n para agrupar/insertar el nuevo o bien dejar el contexto preparado para la primer inserci�n
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
    /// si no es repetido, debo insertar ya que previamente encontramos d�nde debe ubicarse (o bien ser� el primero)

   if(RESERVAR_MEMORIA_NODO(nue, sizeof(tNodoListaDoble), nue->info, cantBytes) != TODO_OK)
        return SIN_MEM;

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

int vaciarListaDoble(tListaDoble *pl)
{
    int ce = 0;
    tNodoListaDoble *act = *pl,
                    *ant,
                    *elim;

    if(!act)
        return LISTA_VACIA;

    ant = act->ant;

    while(ant)
    {
        elim = ant;
        ant = elim->ant;
        free(elim->info);
        free(elim);
        ce++;
    }
    while(act)
    {
        elim = act;
        act = elim->sig;
        free(elim->info);
        free(elim);
        ce++;
    }
    *pl = NULL;

    return ce;
}
