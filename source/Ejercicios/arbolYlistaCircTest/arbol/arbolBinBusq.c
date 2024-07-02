#include "arbolBinBusq.h"

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo)( (   !( (nodo) = (tNodoArbol *) malloc(tamNodo) )      \
                                                              || !( (info) = malloc(tamInfo) )                )?   \
                                                                      free(nodo), SIN_MEM : TODO_OK                )

void crearArbol(tArbolBinBusq *pa)
{
    *pa = NULL;
}

int insertarEnArbol(tArbolBinBusq *pa, const void *info, unsigned tamInfo, Comparar cmp, Acumular acm)
{
    int res;

    if(*pa)
    {
        if((res = cmp(info, (*pa)->info)) < 0)
            return insertarEnArbol(&((*pa)->izq), info, tamInfo, cmp, acm);
        else if(res > 0)
            return insertarEnArbol(&((*pa)->der), info, tamInfo, cmp, acm);
        else
        {
            if(acm)
                if(!acm(&((*pa)->info), &((*pa)->tamInfo), info, tamInfo))
                    return SIN_MEM;
            return CLA_DUP;
        }
    }
    if(!RESERVAR_MEMORIA_NODO(*pa, sizeof(tNodoArbol), (*pa)->info, tamInfo))
        return SIN_MEM;

    (*pa)->izq = NULL;
    (*pa)->der = NULL;
    memcpy((*pa)->info, info, ((*pa)->tamInfo = tamInfo));

    return TODO_OK;
}

void recorrerEnOrdenArbol(tArbolBinBusq *pa, void *recurso, Accionar tarea)
{
    recorrerEnOrdenRecArbol(pa, 0, recurso, tarea);
}

void recorrerEnOrdenRecArbol(tArbolBinBusq *pa, unsigned n, void *recurso, Accionar tarea)
{
    if(!(*pa))
        return;

    recorrerEnOrdenRecArbol(&((*pa)->izq), n + 1, recurso, tarea);
    tarea((*pa)->info, (*pa)->tamInfo, n, recurso);
    recorrerEnOrdenRecArbol(&((*pa)->der), n + 1, recurso, tarea);
}

void recorrerEnPreOrdenArbol(tArbolBinBusq *pa, void *recurso, Accionar tarea)
{
    recorrerEnPreOrdenRecArbol(pa, 0, recurso, tarea);
}

void recorrerEnPreOrdenRecArbol(tArbolBinBusq *pa, unsigned n, void *recurso, Accionar tarea)
{
    if(!(*pa))
        return;

    tarea((*pa)->info, (*pa)->tamInfo, n, recurso);
    recorrerEnPreOrdenRecArbol(&((*pa)->izq), n + 1, recurso, tarea);
    recorrerEnPreOrdenRecArbol(&((*pa)->der), n + 1, recurso, tarea);
}

void recorrerPosOrdenRecArbolOrdenArbol(tArbolBinBusq *pa, void *recurso, Accionar tarea)
{
    recorrerPosOrdenRecArbol(pa, 0, recurso, tarea);
}

void recorrerPosOrdenRecArbol(tArbolBinBusq *pa, unsigned n, void *recurso, Accionar tarea)
{
    if(!(*pa))
        return;

    recorrerPosOrdenRecArbol(&((*pa)->izq), n + 1, recurso, tarea);
    recorrerPosOrdenRecArbol(&((*pa)->der), n + 1, recurso, tarea);
    tarea((*pa)->info, (*pa)->tamInfo, n, recurso);
}

int alturaArbolBinBusq(tArbolBinBusq *pa)
{
    unsigned hi,
             hd;

    if(!(*pa))
        return 0;

    hi = alturaArbolBinBusq(&((*pa)->izq));
    hd = alturaArbolBinBusq(&((*pa)->der));

    return ((hi > hd)? hi : hd) + 1;
}

int leerDesdeArchivoBin(void *info, unsigned tamInfo, unsigned pos, void *pf)
{
    if(!info || !pf)
        return ERROR_PARAMS;

    fseek((FILE *) pf, pos * tamInfo, SEEK_SET);
    return fread(info, tamInfo, 1, (FILE *) pf);
}

int leerDesdeVector(void *info, unsigned tamInfo, unsigned pos, void *vec)
{
    if(!info || !vec)
        return ERROR_PARAMS;

    *((int *) info) = *(((int *) vec) + pos);

    return TODO_OK;
}

int cargarDesdeDatosOrdenados(tArbolBinBusq *pa, int li, int ls, void *fuente, unsigned tamInfo, Leer fCarga)
{
    int m = (li + ls) / 2;
    int res;

    if(li > ls)
        return TODO_OK;

    if(RESERVAR_MEMORIA_NODO(*pa, sizeof(tNodoArbol), (*pa)->info, tamInfo) != TODO_OK)
        return SIN_MEM;

    fCarga((*pa)->info, tamInfo, m, fuente);
    (*pa)->izq = NULL;
    (*pa)->der = NULL;

    if((res = cargarDesdeDatosOrdenados(&((*pa)->izq), li, m - 1, fuente, tamInfo, fCarga)) != TODO_OK)
        return res;
    return cargarDesdeDatosOrdenados(&((*pa)->der), m + 1, ls, fuente, tamInfo, fCarga);
}

int cargarVectorEnArbol(tArbolBinBusq *pa, unsigned tamInfo, unsigned ce, void *vec)
{
    if(*pa || !vec)
        return ERROR_PARAMS;

    return cargarDesdeDatosOrdenados(pa, 0, ce - 1, vec, tamInfo, leerDesdeVector);
}

int cargarArchivoBinEnArbol(tArbolBinBusq *pa, unsigned tamInfo, FILE *pf)
{
    unsigned ce;

    if(*pa || !pf)
        return ERROR_PARAMS;

    fseek(pf, 0, SEEK_END);
    ce = ftell(pf) / tamInfo;

    return cargarDesdeDatosOrdenados(pa, 0, ce - 1, pf, tamInfo, leerDesdeArchivoBin);
}

tNodoArbol **menorNodoClaveArbol(tArbolBinBusq *pa)
{
    while((*pa)->izq)
        pa = &((*pa)->izq);

    return (tNodoArbol **) pa;
}

const void *buscarMenorClaveArbol(tArbolBinBusq *pa, void *buffer, unsigned cantBytes)
{
    if(!(*pa))
        return NULL;

    pa = menorNodoClaveArbol(pa);

    memcpy(buffer, (*pa)->info, MINIMO(cantBytes, (*pa)->tamInfo));

    return (*pa)->info;
}

tNodoArbol **mayorNodoClaveArbol(tArbolBinBusq *pa)
{
    while((*pa)->der)
        pa = &((*pa)->der);

    return (tNodoArbol **) pa;
}

const void *buscarMayorClaveArbol(tArbolBinBusq *pa, void *buffer, unsigned cantBytes)
{
    if(!(*pa))
        return NULL;

    pa = mayorNodoClaveArbol(pa);

    memcpy(buffer, (*pa)->info, MINIMO(cantBytes, (*pa)->tamInfo));

    return (*pa)->info;
}

tNodoArbol *mayorNodoNoClave(tArbolBinBusq *pa, tNodoArbol *mayor, Comparar cmp)
{
    if(!(*pa))
        return mayor;

    if(cmp((*pa)->info, mayor->info) > 0)
        mayor = *pa;

    mayor = mayorNodoNoClave(&((*pa)->izq), mayor, cmp);
    mayor = mayorNodoNoClave(&((*pa)->der), mayor, cmp);

    return mayor;
}

const void *buscarMayorNoClave(tArbolBinBusq *pa, void *buffer, unsigned cantBytes, Comparar cmp)
{
    tNodoArbol *mayor = *pa;

    if(!(*pa))
        return NULL;

    mayor = mayorNodoNoClave(&((*pa)->izq), mayor, cmp);
    mayor = mayorNodoNoClave(&((*pa)->der), mayor, cmp);

    memcpy(buffer, mayor->info, MINIMO(cantBytes, mayor->tamInfo));

    return mayor->info;
}

tNodoArbol *menorNodoNoClaveArbol(tArbolBinBusq *pa, tNodoArbol *menor, Comparar cmp)
{
    if(!(*pa))
        return menor;

    if(cmp((*pa)->info, menor->info) < 0)
        menor = *pa;

    menor = menorNodoNoClaveArbol(&((*pa)->izq), menor, cmp);
    menor = menorNodoNoClaveArbol(&((*pa)->der), menor, cmp);

    return menor;
}

const void *buscarMenorNoClaveArbol(tArbolBinBusq *pa, void *buffer, unsigned cantBytes, Comparar cmp)
{
    tNodoArbol *menor = *pa;

    if(!(*pa))
        return NULL;

    menor = menorNodoNoClaveArbol(&((*pa)->izq), menor, cmp);
    menor = menorNodoNoClaveArbol(&((*pa)->der), menor, cmp);

    memcpy(buffer, menor->info, MINIMO(cantBytes, menor->tamInfo));

    return menor->info;
}

tNodoArbol **buscarNodoClaveArbol(tArbolBinBusq *pa, void *dato, Comparar cmp)
{
    if(!(*pa))
        return NULL;

    if(cmp((*pa)->info, dato))
        if(!buscarNodoClaveArbol(&((*pa)->izq), dato, cmp))
            return buscarNodoClaveArbol(&((*pa)->der), dato, cmp);

    return (tNodoArbol **) pa;
}

const void *buscarElemClaveArbol(tArbolBinBusq *pa, void *dato, unsigned cantBytes, Comparar cmp)
{
    if(!(*pa))
        return NULL;

    if(!(pa = buscarNodoClaveArbol(pa, dato, cmp)))
        return NULL;

    memcpy(dato, (*pa)->info, MINIMO(cantBytes, (*pa)->tamInfo));

    return (*pa)->info;
}

int eliminarRaizArbol(tArbolBinBusq *pa)
{
    tNodoArbol **remp,
               *elim;

    if(!(*pa))
        return SIN_CONTENIDO;

    free((*pa)->info);

    if(!((*pa)->izq) && !((*pa)->der))
    {
        free(*pa);
        *pa = NULL;
        return TODO_OK;
    }

    remp = (alturaArbolBinBusq(&((*pa)->izq)) > alturaArbolBinBusq(&((*pa)->der)))?
                mayorNodoClaveArbol(&((*pa)->izq))
              : menorNodoClaveArbol(&((*pa)->der));

    elim = *remp;

    (*pa)->info = elim->info;
    (*pa)->tamInfo = elim->tamInfo;

    *remp = elim->izq? elim->izq : elim->der;

    free(elim);

    return TODO_OK;
}

void vaciarArbol(tArbolBinBusq *pa)
{
    if(!(*pa))
        return;

    vaciarArbol(&((*pa)->izq));
    vaciarArbol(&((*pa)->der));

    free((*pa)->info);
    free(*pa);
    *pa = NULL;
}

int vaciarArbol2(tArbolBinBusq *pa)
{
    unsigned cont;

    if(!(*pa))
        return 0;

    cont = vaciarArbol2(&((*pa)->izq)) + vaciarArbol2(&((*pa)->der)) + 1;

    free((*pa)->info);
    free(*pa);
    *pa = NULL;

    return cont;
}
