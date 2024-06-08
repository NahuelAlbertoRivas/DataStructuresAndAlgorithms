#include "cola.h"

void crearCola(tCola *pc)
{
    *pc = NULL;
}

int colaLlena(const tCola *pc, unsigned cantBytes)
{
    tNodo *aux = (tNodo *)malloc(sizeof(tNodo));
    void *info = malloc(cantBytes);

    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}

int ponerEnCola(tCola *pc, const void *d, unsigned cantBytes)
{
    tNodo *nue;
    /// unsigned nueMio;
    /// unsigned nueMioSig;

    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL || (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    /// nueMio = (nue);
    //nueMioSig=nue->sig;
    if(!(*pc))
    {
        nue->sig = nue;
        ///nueMioSig=nue->sig;
    }
    else
    {
        nue->sig = (*pc)->sig;
        (*pc)->sig = nue;
        /// nueMioSig=nue->sig;
    }
    *pc = nue;
    /// printf("t:%p, p-sig:%p \nnue:%x nue-sig:%x \n", *pc, (*pc)->sig, nueMio, nueMioSig);
    return TODO_BIEN;
}

int verPrimeroCola(const tCola *pc, void *d, unsigned cantBytes)
{
    if(!(*pc))
        return COLA_VACIA;
    memcpy(d, (*pc)->sig->info, MINIMO(cantBytes, (*pc)->sig->tamInfo));
    return TODO_BIEN;
}

int colaVacia(const tCola *pc)
{
    return *pc == NULL;
}

int sacarDeCola(tCola *pc, void *d, unsigned cantBytes)
{
    tNodo *aux;

    if(!(*pc))
        return 0;
    aux = (*pc)->sig;
    memcpy(d, aux->info, MINIMO(cantBytes, aux->tamInfo));
    if(aux == *pc) /// si el elemento a eliminar es el último
        *pc = NULL;
    else /// si no, enlazo el siguiente
        (*pc)->sig = aux->sig;

    /// printf(" tope %p, p->sig: %p \n", *pc, (*pc)->sig);

    free(aux->info);
    free(aux);
    return TODO_BIEN;
}

void vaciarCola(tCola *pc)
{
    while(*pc)
    {
        tNodo *aux = (*pc)->sig; /// recupero el primero

        if(*pc == aux) /// me fijo si no es el último elemento
            *pc = NULL; /// si lo es, indico que la cola está vacía
        else /// si no,
            (*pc)->sig = aux->sig;
        free(aux->info);
        free(aux);
    }
}
