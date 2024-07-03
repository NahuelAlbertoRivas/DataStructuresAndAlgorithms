#include "TDA.h"

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo) \
( (   !( (nodo) = (tNodoArbol *) malloc(tamNodo))   \
   || !( (info) = malloc(tamInfo) ) )?              \
      free(nodo), SIN_MEM : TODO_OK                 )

#define ABS(x)( ((x) < 0)? -(x) : (x) )

void crearArbol(tArbolBinBusq *pa)
{
    *pa = NULL;
}

int insertarEnArbolBin(tArbolBinBusq *pa, const void *info, unsigned tamInfo, Comparar cmp, Acumular acm)
{
    int res;

    if(*pa)
    {
        if((res = cmp((*pa)->info, info)) > 0)
            return insertarEnArbolBin(&((*pa)->izq), info, tamInfo, cmp, acm);
        else if(res < 0)
            return insertarEnArbolBin(&((*pa)->der), info, tamInfo, cmp, acm);
        else
        {
            if(acm)
                acm(&((*pa)->info), &((*pa)->tamInfo), info, tamInfo);
            return CLA_DUP;
        }
    }
    if(RESERVAR_MEMORIA_NODO(*pa, sizeof(tNodoArbol), (*pa)->info, tamInfo) != TODO_OK)
        return SIN_MEM;

    memcpy((*pa)->info, info, ((*pa)->tamInfo = tamInfo));

    (*pa)->izq = NULL;
    (*pa)->der = NULL;

    return TODO_OK;
}

void recorrerEnOrdenSimpleArbolBinBusq(tArbolBinBusq *pa, void *recurso, AccionarSimple task)
{
    if(!(*pa))
        return;

    recorrerEnOrdenSimpleArbolBinBusq(&((*pa)->izq), recurso, task);
    task((*pa)->info, (*pa)->tamInfo, recurso);
    recorrerEnOrdenSimpleArbolBinBusq(&((*pa)->der), recurso, task);
}

void recorrerEnOrdenRecArbolBinBusq(tArbolBinBusq *pa, unsigned n, void *recurso, Accionar task)
{
    if(!(*pa))
        return;

   recorrerEnOrdenRecArbolBinBusq(&((*pa)->izq), n + 1, recurso, task);
   task((*pa)->info, (*pa)->tamInfo, n, recurso);
   recorrerEnOrdenRecArbolBinBusq(&((*pa)->der), n + 1, recurso, task);
}

void recorrerEnOrdenArbolBinBusq(tArbolBinBusq *pa, void *recurso, Accionar task)
{
    recorrerEnOrdenRecArbolBinBusq(pa, 0, recurso, task);
}

void recorrerEnPreOrdenSimpleArbolBinBusq(tArbolBinBusq *pa, void *recurso, AccionarSimple task)
{
    if(!(*pa))
        return;

    task((*pa)->info, (*pa)->tamInfo, recurso);
    recorrerEnPreOrdenSimpleArbolBinBusq(&((*pa)->izq), recurso, task);
    recorrerEnPreOrdenSimpleArbolBinBusq(&((*pa)->der), recurso, task);
}

void recorrerEnPreOrdenRecArbolBinBusq(tArbolBinBusq *pa, unsigned n, void *recurso, Accionar task)
{
    if(!(*pa))
        return;

    task((*pa)->info, (*pa)->tamInfo, n, recurso);
    recorrerEnPreOrdenRecArbolBinBusq(&((*pa)->izq), n + 1, recurso, task);
    recorrerEnPreOrdenRecArbolBinBusq(&((*pa)->der), n + 1, recurso, task);
}

void recorrerEnPreOrdenArbolBinBusq(tArbolBinBusq *pa, void *recurso, Accionar task)
{
    recorrerEnPreOrdenRecArbolBinBusq(pa, 0, recurso, task);
}

int leerDeArchivo(void *info, unsigned tamInfo, unsigned pos, void *fuente)
{
    FILE *pf;

    if(!info || !fuente)
        return ERR_PARAMS;

    pf = (FILE *) fuente;

    fseek(pf, pos * tamInfo, SEEK_SET);
    fread(info, tamInfo, 1, pf);
    fflush(pf);

    return TODO_OK;
}

int cargarArbolDesdeArchivoBin(tArbolBinBusq *pa, unsigned tamInfo, FILE *pf)
{
    unsigned tamLote;

    if(!pf)
        return ERR_PARAMS;

    if(*pa)
        return SIN_INICIALIZAR;

    fseek(pf, 0L, SEEK_END);
    tamLote = ftell(pf) / tamInfo;

    return cargarDesdeDatosOrdenados(pa, pf, tamInfo, 0, tamLote - 1, leerDeArchivo);
}

int cargarDesdeDatosOrdenados(tArbolBinBusq *pa, void *fuente, unsigned tamInfo, int li, int ls, Leer fCarga)
{
    int res,
        m = (li + ls)/2;

    if(li > ls)
        return TODO_OK;

    if(RESERVAR_MEMORIA_NODO(*pa, sizeof(tNodoArbol), (*pa)->info, tamInfo) != TODO_OK)
        return SIN_MEM;

    (*pa)->izq = NULL;
    (*pa)->der = NULL;
    (*pa)->tamInfo = tamInfo;

    fCarga((*pa)->info, tamInfo, m, fuente);

    if((res = cargarDesdeDatosOrdenados(&((*pa)->izq), fuente, tamInfo, li, m - 1, fCarga)) != TODO_OK)
        return res;
    return cargarDesdeDatosOrdenados(&((*pa)->der), fuente, tamInfo, m + 1, ls, fCarga);
}

void grabarEnArchivo(void *info, unsigned tamInfo, void *recurso)
{
    FILE *pf;

    if(!info || !recurso)
        return;

    pf = (FILE *) recurso;
    fwrite(info, tamInfo, 1, pf);
    fflush(pf);
}

int guardarArbolEnOrdenAchivoBin(tArbolBinBusq *pa, FILE *pf)
{
    if(!(*pa))
        return ARBOL_VACIO;

    if(!pf)
        return ERR_ARCH;

    fseek(pf, 0L, SEEK_SET);

    recorrerEnOrdenSimpleArbolBinBusq(pa, pf, grabarEnArchivo);

    return TODO_OK;
}

unsigned alturaArbol(const tArbolBinBusq *pa)
{
    unsigned hi,
             hd;

    if(!(*pa))
        return 0;

    hi = alturaArbol(&((*pa)->izq));
    hd = alturaArbol(&((*pa)->der));

    return ((hi > hd)? hi : hd) + 1;
}

bool esArbolAVL(const tArbolBinBusq *pa)
{
    unsigned hi,
             hd;

    if(!(*pa))
        return true;

    hi = alturaArbol(&((*pa)->izq));
    hd = alturaArbol(&((*pa)->der));

    if(ABS((int) hi - (int) hd) > 1)
        return false;

    return esArbolAVL(&((*pa)->izq)) && esArbolAVL(&((*pa)->der));
}

unsigned contarNodosDelArbol(const tArbolBinBusq *pa)
{

    if(!(*pa))
        return 0;

    return contarNodosDelArbol(&((*pa)->izq)) + contarNodosDelArbol(&((*pa)->der)) + 1;
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
