#ifndef PILA_LISTA_CIRCULAR
#define PILA_LISTA_CIRCULAR

#ifndef STDLIB
#include <stdlib.h>
#endif // STDLIB

#ifndef STRING
#include <string.h>
#endif // STRING

#ifndef STDIO
#include <stdio.h>
#endif // STDIO

#ifndef MINIMO
#define MINIMO(x, y) ( (x) <= (y) ? (x) : (y) )
#endif // MINIMO

#ifndef tNodo
typedef struct sNodo
{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
} tNodo;
#endif // tNodo

#ifndef tPila
typedef tNodo *tPila;
#endif // tPila

void crearPila(tPila *p);
int pilaLlena(const tPila *p, unsigned cantBytes);
int ponerEnPila(tPila *p, const void *d, unsigned cantBytes);
int verTope(const tPila *p, void *d, unsigned cantBytes);
int pilaVacia(const tPila *p);
int sacarDePila(tPila *p, void *d, unsigned cantBytes);
void vaciarPila(tPila *p);

#endif
