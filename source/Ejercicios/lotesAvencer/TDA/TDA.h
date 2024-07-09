#ifndef TDA
#define TDA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <winsock2.h>
#include <windows.h>
#include <unistd.h>

#define TODO_OK 1
#define SIN_MEM -1
#define LISTA_VACIA -2
#define CLA_DUP 2
#define ERR_PARAMS -4

typedef struct sNodo
{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tLista;

typedef int (*Comparar)(const void *, const void *);

typedef int (*Accionar)(void *, void *);

typedef void (*Mostrar)(const void *, FILE *);

typedef int (*Acumular)(void **, unsigned *, const void *, unsigned);

void crearLista(tLista *pl);

bool listaVacia(tLista *pl);

char insertarEnOrden(tLista *pl, const void *info, unsigned tamInfo, Comparar cmp, Acumular acm);

const void *verPrimero(tLista *pl, void *buffer, unsigned cantBytes);

void mapLista(tLista *pl, void *recurso, Accionar task);

const void *buscarMenorNoClave(tLista *pl, void *buffer, unsigned cantBytes, Comparar cmp);

void vaciarLista(tLista *pl);

void mostrarYvaciarN(tLista *pl, unsigned n, FILE *pf, Mostrar mst);

#endif
