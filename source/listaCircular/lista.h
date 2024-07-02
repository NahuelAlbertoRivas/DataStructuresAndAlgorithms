#ifndef LISTA
#define LISTA

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define OK 434534
#define SIN_MEM 32434
#define LISTA_LLENA 34332
#define LISTA_VACIA 5453

typedef struct sNodo
{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tLista;

typedef void (*AccionarSimple)(void *, void *);

typedef void (*Mostrar)(const void *, FILE *);

#endif
