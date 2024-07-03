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

int eliminarPrimeroListaDoble(tListaDoble *pl)
{
    tNodoListaDoble *act = *pl,
                    *sig;

    if(!act)
        return LISTA_VACIA;

    while(act->ant)
        act = act->ant;

    sig = act->sig;
    free(act->info);
    free(act);
    if(sig)
    {
        sig->ant = NULL;
        *pl = sig;
    }
    else
        *pl = NULL;

    return TODO_OK;
}

int insertarAlFinalListaDoble(tListaDoble *pl, const void *info, unsigned cantBytes)
{
    tNodoListaDoble *act = *pl,
                    *nue;

    if(act) /// si hay al menos dos nodos encuentro la posición del nuevo
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
    tNodoListaDoble *act = *pl,
                    *ant;

    if(!act)
        return LISTA_VACIA;

    while(act->sig)
        act = act->sig;

    ant = act->ant;
    free(act->info);
    free(act);
    if(ant)
    {
        ant->sig = NULL;
        *pl = ant;
    }
    else
        *pl = NULL;

    return TODO_OK;
}

/// la siguiente fn. es muy parecida al filter, pero elimina una única existencia,
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

int mapListaDoble(tListaDoble *pl, void *recurso, Accion tarea)
{
    tNodoListaDoble *act = *pl;
    int ce = 0;

    if(!act)
        return LISTA_VACIA;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        tarea(act->info, recurso);
        act = act->sig;
        ce++;
    }

    return ce;
}

int mapListaDoble2(tListaDoble *pl, void *recurso, Accion tarea)
{
    tNodoListaDoble *act = *pl,
                    *ant;
    int ce = 0;

    if(!act)
        return ce;

    ant = act->ant;

    while(ant)
    {
        tarea(ant->info, recurso);
        ant = ant->ant;
        ce++;
    }
    while(act)
    {
        tarea(act->info, recurso);
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
                    *ant,
                    *sig,
                    *nue;
    int res;

    if(!act) /// me fijo si hay elementos en la lista así encontrar la posición para agrupar/insertar el nuevo o bien dejar el contexto preparado para la primer inserción
    {
        ant = NULL;
        sig = NULL;
    }
    else
    {
        while(act->sig && (cmp(act->info, info) < 0))
            act = act->sig;
        while(act->ant && (cmp(act->info, info) > 0))
            act = act->ant;

        res = cmp(act->info, info);

        if(!res)
        {
            if(acm)
                if(!acm(&((act)->info), &((act)->tamInfo), info, cantBytes))
                    return SIN_MEM;
            return CLA_DUP;
        }
        else if(res > 0)
        {
            ant = act->ant;
            sig = act;
        }
        else
        {
            ant = act;
            sig = act->sig;
        }
    }
    /// si no es repetido, debo insertar ya que previamente encontramos dónde debe ubicarse (o bien será el primero)

   if(RESERVAR_MEMORIA_NODO(nue, sizeof(tNodoListaDoble), nue->info, cantBytes) != TODO_OK)
        return SIN_MEM;

    memcpy(nue->info, info, (nue->tamInfo = cantBytes));
    if(ant)
        ant->sig = nue;
    if(sig)
        sig->ant = nue;
    nue->ant = ant;
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

int vaciarYmostrarIzqADer(tListaDoble *pl, Mostrar mostrar, FILE *pf)
{
    tNodoListaDoble *act = *pl,
                    *elim;
    int ce = 0;

    if(!act)
        return LISTA_VACIA;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        mostrar(act->info, pf);
        elim = act;
        act = elim->sig;
        free(elim->info);
        free(elim);
        ce++;
    }
    *pl = NULL;

    return ce;
}

tNodoListaDoble *buscarNodoMenorClaveListaDoble(tListaDoble *pl, Comparacion cmp)
{
    tNodoListaDoble *act = *pl,
                    *menor;

    if(!act)
        return NULL;
  
    while(act->ant)
      act = act->ant;
  
    menor = act;
    act = menor->sig;

    while(act)
    {
        if(cmp(act->info, menor->info) < 0)
            menor = act;
        act = act->sig;
    }

    return menor;
}

int ordenarListaDoble(tListaDoble *pl, Comparacion cmp)
{
    tNodoListaDoble *ini = *pl,
                    *menor,
                    *ant,
                    *sig;

    if(!ini)
        return LISTA_VACIA;

    while(ini->ant)
        ini = ini->ant;

    while(ini)
    {
        menor = buscarNodoMenorClaveListaDoble(&ini, cmp);
        if(menor != ini)
        {
            ant = menor->ant;
            sig = menor->sig;
            if(ant)
                ant->sig = sig;
            if(sig)
                sig->ant = ant;
            menor->sig = ini;
            if(ini)
            {
                ant = ini->ant;
                if(ant)
                    ant->sig = menor;
                menor->ant = ant;
                ini->ant = menor;
            }
        }
        ini = menor->sig;
    }

    return TODO_OK;
}
