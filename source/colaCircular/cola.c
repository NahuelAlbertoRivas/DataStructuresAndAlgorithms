#include "cola.h"

void crearColaCirc(tColaCirc *pc)
{
    *pc = NULL;
}

int colaLlenaCirc(const tColaCirc *pc, unsigned cantBytes)
{
    tNodoColaCirc *aux = (tNodoColaCirc *)malloc(sizeof(tNodoColaCirc));
    void *info = malloc(cantBytes);

    free(aux);
    free(info);

    return aux == NULL || info == NULL;
}

int ponerEnColaCirc(tColaCirc *pc, const void *d, unsigned cantBytes)
{
    tNodoColaCirc *nue;

    if((nue = (tNodoColaCirc *)malloc(sizeof(tNodoColaCirc))) == NULL || (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    if(!(*pc))
        nue->sig = nue;
    else
    {
        nue->sig = (*pc)->sig;
        (*pc)->sig = nue;
    }
    *pc = nue;

    return TODO_BIEN;
}

int verPrimeroColaCirc(const tColaCirc *pc, void *d, unsigned cantBytes)
{
    if(!(*pc))
        return COLA_VACIA;
    memcpy(d, (*pc)->sig->info, MINIMO(cantBytes, (*pc)->sig->tamInfo));
    return TODO_BIEN;
}

int colaVaciaCirc(const tColaCirc *pc)
{
    return *pc == NULL;
}

int sacarDeColaCirc(tColaCirc *pc, void *d, unsigned cantBytes)
{
    tNodoColaCirc *aux;

    if(!(*pc))
        return 0;
    aux = (*pc)->sig;
    memcpy(d, aux->info, MINIMO(cantBytes, aux->tamInfo));
    if(aux == *pc) /// si el elemento a eliminar es el último
        *pc = NULL;
    else /// si no, enlazo el siguiente
        (*pc)->sig = aux->sig;

    free(aux->info);
    free(aux);
    return TODO_BIEN;
}

void vaciarColaCirc(tColaCirc *pc)
{
    while(*pc)
    {
        tNodoColaCirc *aux = (*pc)->sig; /// recupero el primero

        if(*pc == aux) /// me fijo si no es el último elemento
            *pc = NULL; /// si lo es, indico que la cola está vacía
        else /// si no,
            (*pc)->sig = aux->sig;
        free(aux->info);
        free(aux);
    }
}
