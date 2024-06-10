#include "lista.h"

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo)( (   !( (nodo) = (tNodo *) malloc(tamNodo) )    \
                                                              || !( (info) = malloc(tamInfo) )          )?  \
                                                                     free(nodo), SIN_MEM : TODO_OK          )

void crearLista(tLista *p)
{
    *p = NULL;
}

int listaVacia(const tLista *p)
{
    return *p == NULL;
}


int listaLlena(const tLista *p, unsigned cantBytes)
{
    tNodo *aux = (tNodo *)malloc(sizeof(tNodo));
    void *info = malloc(cantBytes);

    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}


int vaciarLista(tLista *p)
{
    int cant = 0;
    while(*p)
    {
        tNodo *aux = *p;

        cant++;
        *p = aux->sig;
        free(aux->info);
        free(aux);
    }
    return cant;
}


int vaciarListaYMostrar(tLista *p, void (*mostrar)(const void *, FILE *), FILE *fp)
{
    int cant = 0;
    while(*p)
    {
        tNodo *aux = *p;

        cant++;
        *p = aux->sig;
        if(mostrar && fp)
            mostrar(aux->info, fp);
        free(aux->info);
        free(aux);
    }
    return cant;
}


int ponerAlComienzo(tLista *p, const void *d, unsigned cantBytes)
{
    tNodo *nue;

    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL || (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = *p;
    *p = nue;
    return 1;
}


int sacarPrimeroLista(tLista *p, void *d, unsigned cantBytes)
{
    tNodo *aux = *p;

    if(aux == NULL)
        return 0;
    *p = aux->sig;
    memcpy(d, aux->info, minimo(cantBytes, aux->tamInfo));
    free(aux->info);
    free(aux);
    return 1;
}


int verPrimeroLista(const tLista *p, void *d, unsigned cantBytes)
{
    if(*p == NULL)
        return 0;
    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));
    return 1;
}


int ponerAlFinal(tLista *p, const void *d, unsigned cantBytes)
{
    tNodo *nue;

    while(*p)
        p = &(*p)->sig;
    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL || (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = NULL;
    *p = nue;
    return 1;
}


int sacarUltimoLista(tLista *p, void *d, unsigned cantBytes)
{
    if(*p == NULL)
        return 0;
    while((*p)->sig)
        p = &(*p)->sig;
    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));
    free((*p)->info);
    free(*p);
    *p = NULL;
    return 1;
}


int verUltimoLista(const tLista *p, void *d, unsigned cantBytes)
{
    if(*p == NULL)
        return 0;
    while((*p)->sig)
        p = &(*p)->sig;
    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));
    return 1;
}


int mostrarLista(const tLista *p, void (*mostrar)(const void *, FILE *), FILE *fp)
{
    int cant = 0;

    while(*p)
    {
        mostrar((*p)->info, fp);
        p = &(*p)->sig;
        cant++;
    }
    return cant;
}


int mostrarListaAlReves(const tLista *p, void (*mostrar)(const void *, FILE *), FILE *fp)
{
    if(*p)
    {
        int n = mostrarListaAlReves(&(*p)->sig, mostrar, fp);

        mostrar((*p)->info, fp);
        return n + 1;
    }
    return 0;
}


int mostrarListaAlRevesYVaciar(tLista *p, void (*mostrar)(const void *, FILE *), FILE *fp)
{
    if(*p)
    {
        int n = mostrarListaAlReves(&(*p)->sig, mostrar, fp);

        mostrar((*p)->info, fp);
        free((*p)->info);
        free(*p);
        *p = NULL;
        return n + 1;
    }
    return 0;
}


int ponerEnOrden(tLista *p, const void *d, unsigned cantBytes, int (*comparar)(const void *, const void *),
                  int (*acumular)(void **, unsigned *, const void *, unsigned))
{
    tNodo *nue;

    while(*p && comparar((*p)->info, d) < 0)
        p = &(*p)->sig;
    if(*p && comparar((*p)->info, d) == 0)
    {
        if(acumular)
            if(!acumular(&(*p)->info, &(*p)->tamInfo, d, cantBytes))
                return SIN_MEM;
        return CLA_DUP;
    }
    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL || (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = *p;
    *p = nue;
    return TODO_OK;
}


void ordenar(tLista *p, int (*comparar)(const void *, const void *))
{
    tLista *pri = p; // obs: ' pri ' siempre apuntará al inicio de la lista

    if(*p == NULL) // si la lista está vacía, retorna
        return;
    while((*p)->sig) // mientras que no estemos en el último nodo de la lista, recorremos la lista mediante ' p '
    {
        if(comparar((*p)->info, (*p)->sig->info) > 0) // si la info. del nodo actual es mayor al ' siguiente '
        {
            tLista *q = pri; // ' q ' siempre apunta al inicio de la lista al comenzar cada iteración
            tNodo *aux = (*p)->sig; // ' aux ' adquiere el ' siguiente ' nodo

            (*p)->sig = aux->sig; // se asigna a ' p ' el próximo nodo del nodo ' siguiente '
            while((*q)->sig && comparar((*q)->info, aux->info) > 0) // mientras que la info. del primer elemento de la lista sea ' mayor ' al ' siguiente '
                q = &(*q)->sig; // avanzo al siguiente nodo
            aux->sig = *q; //
            *q = aux;
        }
        else // si la info. del actual es menor *o igual* a la del sig.
            p = &(*p)->sig; // simplemente avanzo al siguiente nodo
    }
}

tLista *buscarDirMenorOMayor(tLista *pl, int (*comparar)(const void *, const void *)){
    tLista *punteroNodo = pl;

    while(*(pl = &((*pl)->sig))){
        if(comparar((*punteroNodo)->info, (*pl)->info) == BUSCADO)
            punteroNodo = pl;
    }

    return punteroNodo;
}

int ordenarNodosLista(tLista *pl, int (*comparar)(const void *, const void *)){
    tLista *dirNodo;
    tNodo *nodo;

    while(*pl){
        dirNodo = buscarDirMenorOMayor(pl, comparar);
        nodo = *dirNodo;

        *dirNodo = nodo->sig;
        nodo->sig = *pl;
        *pl = nodo;

        pl = &((*pl)->sig);
    }

    return TODO_OK;
}

bool listaGrabarEnArchivo(tLista *pl, const char *nomArch){
    FILE *arch = fopen(nomArch, "wb");
    if(!arch)
        return false;

    while(*pl)
    {
        fwrite(*pl, sizeof(tNodo), 1, arch);
        pl = &(*pl)->sig;
    }

    fclose(arch);
    return true;
}

bool listaCrearDeArchivos(tLista *pl, const char *nomArch, size_t tamElem, Comparar cmp){
    FILE *arch = fopen(nomArch, "rb");

    if(!arch)
        return false;

    fseek(arch, 0L, SEEK_END);
    // int cantBytesArch = ftell(arch);
    // int ce = cantBytesArch / tamElem;
    tNodo *aux = malloc(tamElem);

    rewind(arch);

    while(fread(aux, tamElem, 1, arch))
        ponerEnOrden(pl, aux, tamElem, cmp, NULL);

    fclose(arch);
    return true;
}

tLista *obtenerLaDireccionDelSiguiente(tLista *pl){
    return &((*pl)->sig);
}

int accionarSobreElPrimero(tLista *pl, void *recurso, accionManejoDatos tarea){
    tarea((*pl)->info, recurso);
    return TODO_OK;
}

tLista *buscarDirClave(tLista *pl, void *clave, int (*comparar)(const void *, const void *)){
    tLista *punteroNodo = NULL;
    bool encontrado = false;

    while((*pl) && !encontrado){
        if(comparar((*punteroNodo)->info, clave) == BUSCADO){
            punteroNodo = pl;
            encontrado = true;
        }
        pl = &((*pl)->sig);
    }

    return punteroNodo;
}

/** void eliminarElemLista(tLista *p, void *recurso, int (*comparar)(const void *, const void *))
{
    tLista *anterior = p; // obs: ' pri ' siempre apuntará al inicio de la lista
    bool encontrado = false;

    if(*p == NULL) // si la lista está vacía, retorna
        return;
    while( (*p) && !encontrado ) // mientras que no estemos en el último nodo de la lista, recorremos la lista mediante ' p '
    {
        if(comparar((*p)->info, recurso) == BUSCADO) // si la info. del nodo actual es mayor al ' siguiente '
        {
            tLista *q = anterior; // ' q ' siempre apunta al inicio de la lista al comenzar cada iteración
            tNodo *aux = p; // ' aux ' adquiere el ' siguiente ' nodo

            (*p)->sig = aux->sig; // se asigna a ' p ' el próximo nodo del nodo ' siguiente '
            aux->sig = *q; //
            *q = aux;
        }
        else{ // si la info. del actual es menor *o igual* a la del sig.
            p = &(*p)->sig; // simplemente avanzo al siguiente nodo
            anterior = &(*anterior)->sig;
        }
    }
} **/


int mapLista(const tLista *pl, int (*accion)(void *, void *), void *contexto)
{
    int cant = 0;

    while(*pl)
    {
        cant = accion((*pl)->info, contexto);
        pl = &(*pl)->sig;
    }

    return cant;
}

//int filterLista(tLista *pl, Comparar cmp, void *recurso)
//{
//
//}

int insertarOrdenadoDescConLimite(tLista *pl, const void *info, unsigned tamInfo, Comparar cmp, Acumular acm, unsigned limite)
{
    tNodo *nue;
    unsigned cant = 0;
    tNodo *menor = NULL,
          *elim;
    void *reubicarInfo;
    tLista *pos = pl,
           *excedente = NULL;
    int res;
    /// Inicio buscar posición
    while(*pos && (cmp((*pos)->info, info) > 0) && (cant < limite))
    {
        cant++;
        pos = &((*pos)->sig);
    }
    /// fin buscar posición
    pl = pos; /// me guardo esto para recortar excedentes si es necesario

    while(*pl && (cant < limite)) /// en caso de corresponder, retomo desde el úlrimo elemento para determinar si tengo excedentes
    {
        cant++;
        excedente = pl;
        menor = *pl;
        pl = &((*pl)->sig);
    }

    if(*pos && !(res = cmp((*pos)->info, info))) /// verifico si el último elemento comparado no es el mismo que el nuevo dato
    {
        if(acm)
            acm(&((*pos)->info), &((*pos)->tamInfo), info, tamInfo);
        return CLA_DUP;
    }
    else if((cant >= limite) && (*pos == menor)) /// si no existe, puede pasar que estemos en una situación límite
    {
        if(!menor || cmp(menor->info, info) > 0) /// si el dato ingresante es menor al menor de mi colección
            return NO_ENTRA;
        else if((reubicarInfo = realloc(menor->info, tamInfo))) /// si no, corresponde reemplazar al menor, opto por reubicar la info para no complicarla
        {
            menor->info = reubicarInfo;
            memcpy(menor->info, info, tamInfo);
            menor->tamInfo = tamInfo;

            return D_INS;
        }
        else
            return SIN_MEM;
    }

    /// [Si hay margen para que entre, y se dan todas las condiciones]

    if(RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, tamInfo) != TODO_OK)
        return SIN_MEM;

    memcpy(nue->info, info, (nue->tamInfo = tamInfo));
    nue->sig = *pos;
    *pos = nue;

    while((cant >= limite) && *excedente) /// recorto excedentes
    {
        elim = *excedente;
        *excedente = elim->sig;
        free(elim->info);
        free(elim);
    }

    return TODO_OK;
}
