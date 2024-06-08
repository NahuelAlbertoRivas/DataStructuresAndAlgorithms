#ifndef LISTA
#define LISTA


#define CLA_DUP 2
#define SIN_MEM 34323
#define LISTA_VACIA 2235
#define LISTA_LLENA 3443
#define OK 325
#define NO_EXISTE 532
#define FILTRADO 3442

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct sNodo
{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tLista;

typedef int (*Accionar)(void *, void *);
typedef int (*Comparar)(const void *, const void *);
typedef int (*Acumular)(void **, unsigned *, const void *, unsigned);
typedef void(*Mostrar)(const void *, FILE *);

void crearLista(tLista *pl);

int listaVacia(const tLista *pl);



#endif
