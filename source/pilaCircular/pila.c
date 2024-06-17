#include "pila.h"

void crearPilaCirc(tPilaCirc *p)
{
    *p = NULL;
}

int pilaLlenaCirc(const tPilaCirc *p, unsigned cantBytes)
{
    tNodoPilaCirc *aux = (tNodoPilaCirc *)malloc(sizeof(tNodoPilaCirc));
    void *info = malloc(cantBytes);

    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}

int ponerEnPilaCirc(tPilaCirc *p, const void *d, unsigned cantBytes)
{
    tNodoPilaCirc *nue;

    if((nue = (tNodoPilaCirc *)malloc(sizeof(tNodoPilaCirc))) == NULL ||
    (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    if(*p == NULL)
    {
        nue->sig = nue;
        *p = nue;
    }
    else
    {
        nue->sig = (*p)->sig;
        (*p)->sig = nue;
    }

    return 1;
}

int verTopeCirc(const tPilaCirc *p, void *d, unsigned cantBytes)
{
    if(*p == NULL)
        return 0;
    memcpy(d, (*p)->sig->info, MINIMO(cantBytes, (*p)->sig->tamInfo));
    return 1;
}

int pilaVaciaCirc(const tPilaCirc *p)
{
    return *p == NULL;
}

int sacarDePilaCirc(tPilaCirc *pp, void *d, unsigned cantBytes)
{
    tNodoPilaCirc *aux;

    if(*pp == NULL)
        return 0;
    aux = (*pp)->sig;
    memcpy(d, aux->info, MINIMO(cantBytes, aux->tamInfo));
    if(aux == *pp)
        *pp = NULL;
    else
        (*pp)->sig = aux->sig;

    free(aux->info);
    free(aux);
    return 1;
}

void vaciarPilaCirc(tPilaCirc *p)
{
    while(*p)
    {
        tNodoPilaCirc *aux = (*p)->sig;

        if(*p == aux)
            *p = NULL;
        else
            (*p)->sig = aux->sig;
        free(aux->info);
        free(aux);
    }
}
