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

typedef struct sNodoColaCirc{
    void *info;
    unsigned tamInfo;
    struct sNodoColaCirc *sig;
} tNodoColaCirc;

typedef tNodoColaCirc *tColaCirc;

void crearColaCirc(tColaCirc *pc);
int colaLlenaCirc(const tColaCirc *pc, unsigned cantBytes);
int ponerEnColaCirc(tColaCirc *pc, const void *d, unsigned cantBytes);
int verPrimeroColaCirc(const tColaCirc *pc, void *d, unsigned cantBytes);
int colaVaciaCirc(const tColaCirc *pc);
int sacarDeColaCirc(tColaCirc *pc, void *d, unsigned cantBytes);
void vaciarColaCirc(tColaCirc *pc);


#endif
