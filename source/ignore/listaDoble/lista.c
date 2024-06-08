#include "lista.h"

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo)( (  !( (nodo) = (tNodo *) malloc(tamNodo) )  ||      \
                                                                !( (info) = malloc(tamInfo) )               )?   \
                                                                    free(nodo), SIN_MEM : OK                     )

#define MINIMO(x, y)( ((x) < (y))? (x) : (y) )

void crearLista(tLista *pl)
{
    *pl = NULL;
}

int listaVacia(const tLista *pl)
{
    return *pl == NULL;
}

int insertarAlInicioConDup(tLista *pl, const void *info, unsigned tamInfo, Comparar cmp)
{
    tNodo *nue;



    if(!RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, tamInfo))
        return SIN_MEM;

    memcpy(nue->info, info, (nue->tamInfo = tamInfo));
    nue->sig = *pl;
    *pl = nue;

    return OK;
}

int insertarAlInicioSinDup(tLista *pl, const void *info, unsigned tamInfo, Comparar cmp)
{
    tLista *ini = pl;
    tNodo *nue;
    int res;

    while(*pl && (res = cmp(info, (*pl)->info)))
        pl = &((*pl)->sig);

    if(!res)
        return CLA_DUP;

    if(!RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, tamInfo))
        return SIN_MEM;

    memcpy(nue->info, info, (nue->tamInfo = tamInfo));
    nue->sig = *ini;
    *ini = nue;

    return OK;
}

int insertarAlInicioAcumulando(tLista *pl, const void *info, unsigned tamInfo, Comparar cmp, Acumular acm)
{
    tLista *ini = pl;
    tNodo *nue;
    int res;

    while(*pl && (res = cmp(info, (*pl)->info)))
        pl = &((*pl)->sig);

    if(!res)
    {
        if(acm)
            acm(&((*pl)->info), &((*pl)->tamInfo), info, tamInfo);

        return CLA_DUP;
    }

    if(!RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, tamInfo))
        return SIN_MEM;

    memcpy(nue->info, info, (nue->tamInfo = tamInfo));
    nue->sig = *ini;
    *ini = nue;

    return OK;
}

int insertarAlFinalConDup(tLista *pl, const void *info, unsigned tamInfo, Comparar cmp, Acumular acm)
{
    tNodo *nue;

    while(*pl)
        pl = &((*pl)->sig);

    if(!RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, tamInfo))
        return SIN_MEM;

    memcpy(nue->info, info, (nue->tamInfo = tamInfo));
    nue->sig = NULL;
    *pl = nue;

    return OK;
}

int insertarAlFinalSinDup(tLista *pl, const void *info, unsigned tamInfo, Comparar cmp)
{
    tNodo *nue;
    int res;

    while(*pl && (res = cmp((*pl)->info, info)))
        pl = &((*pl)->sig);

    if(!res)
        return CLA_DUP;

    if(!RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, tamInfo))
        return SIN_MEM;

    memcpy(nue->info, info, (nue->tamInfo = tamInfo));
    nue->sig = NULL;
    *pl = nue;

    return OK;
}

int insertarAlFinalAcumulando(tLista *pl, const void *info, unsigned tamInfo, Comparar cmp, Acumular acm)
{
    tNodo *nue;
    int res;

    while(*pl && (res = cmp((*pl)->info, info)))
        pl = &((*pl)->sig);

    if(!res)
    {
        if(acm)
            acm(&((*pl)->info), &((*pl)->tamInfo), info, tamInfo);

        return CLA_DUP;
    }

    if(!RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, tamInfo))
        return SIN_MEM;

    memcpy(nue->info, info, (nue->tamInfo = tamInfo));
    nue->sig = NULL;
    *pl = nue;

    return OK;
}

int buscarInfoPorClave(tLista *pl, void *info, unsigned cantBytes, Comparar cmp)
{
    while(*pl && cmp((*pl)->info, info))
        pl = &((*pl)->sig);

    if(!(*pl))
        return NO_EXISTE;

    memcpy(info, (*pl)->info, MINIMO(cantBytes, (*pl)->tamInfo));

    return OK;
}

int buscarInfoPorClaveOrdenada(tLista *pl, void *info, unsigned cantBytes, Comparar cmp)
{
    int res;

    while(*pl && ((res = cmp((*pl)->info, info)) > 0) )
        pl = &((*pl)->sig);

    if(!(*pl) || (res < 0))
        return NO_EXISTE;

    memcpy(info, (*pl)->info, MINIMO(cantBytes, (*pl)->tamInfo));

    return OK;
}

tLista *buscarSubLista(tLista *pl, const void *info, Comparar cmp)
{
    while(*pl && cmp((*pl)->info, info))
        pl = &((*pl)->sig);

    if(!(*pl))
        return NULL;

/// casos posibles
///      a) no hay elementos
///           => retorno NULL
///      b) hay elementos, pero no encuentro la sublista a partir de la instancia buscada
///           => retorno NULL
///      c) encuentro la sublista
///           => retorno la misma, o sea, *pl


    return pl;
}

int filtrarLista(tLista *pl, const void *info, Comparar cmp)
{
    tNodo *elim;
    int res;



    while(*pl && (res = cmp((*pl)->info, info)))
    {
        if(!res)
        {
            elim = *pl;
            *pl = elim->sig;
            free(elim->info);
            free(elim);

            return FILTRADO;
        }

        pl = &((*pl)->sig);
    }

    return OK;
}

int map(tLista *pl, Accionar task, void *recurso)
{
    while(*pl)
    {
        task((*pl)->info, recurso);
        pl = &((*pl)->sig);
    }

    return OK;
}

int eliminarNUltimos(tLista *pl, unsigned cant)
{
    tLista *ini = pl;
    tNodo *elim;
    unsigned cont = 0;

    while(*pl)
    {
        cont++;
        pl = &((*pl)->sig);
    }

    if(cont >= cant)
    {
        cant = cont - cant;
        while(cant--)
            ini = &((*ini)->sig);

        while(*ini)
        {
            elim = *ini;
            *ini = elim->sig;
            free(elim->info);
            free(elim);

            ini = &((*pl)->sig);
        }
    }

    return OK;
}


/// eliminar las claves que no tienen duplicados y las que están duplicadas acción


int eliminarNoDupAccDup(tLista *pl, Comparar cmp, Accionar task, void *recurso)
{
    tLista *ref = pl,
            *ini = pl;
    int res;
    char dup;
    tNodo *elim;

    if(!(*pl))
        return LISTA_VACIA;

    while(*ref)
    {
        res = 1;
        dup = 0;
        pl = ini;
        while(*pl && res)
        {
            if(pl != ref && !(res = cmp((*ref)->info, (*pl)->info)))
            {
                task((*ref)->info, recurso);
                dup = 1;
            }
            else
                pl = &((*pl)->sig);
        }
        if(!dup)
        {
            elim = *ref;
            *ref = elim->sig;
            free(elim->info);
            free(elim);
        }
        else
            ref = &((*pl)->sig);
    }

    return OK;
}
