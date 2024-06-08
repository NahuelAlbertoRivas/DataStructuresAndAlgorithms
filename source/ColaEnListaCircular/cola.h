#ifndef COLA_LISTA_CIRCULAR
#define COLA_LISTA_CIRCULAR

#ifndef STDIO
#include <stdio.h>
#endif // STDIO

#ifndef STDLIB
#include <stdlib.h>
#endif // STDLIB

#ifndef STRING
#include <string.h>
#endif // STRING

#ifndef MINIMO
#define MINIMO(x, y) ( (x) <= (y) ? (x) : (y) )
#endif // MINIMO

#ifndef TODO_BIEN
#define TODO_BIEN 1
#endif // TODO_BIEN

#ifndef COLA_VACIA
#define COLA_VACIA 0
#endif // COLA_VACIA

#ifndef SIN_MEM
#define SIN_MEM 2
#endif // SIN_MEM

typedef struct sNodo{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
}tNodo;

#ifndef tCola
typedef tNodo *tCola;
#endif // tCola

void crearCola(tCola *pc);
int colaLlena(const tCola *pc, unsigned cantBytes);
int ponerEnCola(tCola *pc, const void *d, unsigned cantBytes);
int verPrimeroCola(const tCola *pc, void *d, unsigned cantBytes);
int pilaVacia(const tCola *pc);
int sacarDeCola(tCola *pc, void *d, unsigned cantBytes);
void vaciarCola(tCola *pc);


#endif
