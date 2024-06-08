#ifndef COLA_ESTATICA
#define COLA_ESTATICA

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MINIMO(x, y) ((x) <= (y))?(x):(y)

#define COLA_VACIA 0
#define SIN_MEM 0
#define TODO_OK 1

#define TAM_COLA 360

typedef struct
{
    char cola[TAM_COLA];
    unsigned pri,
             ult,
             tamDisp;
} tCola;

void crearCola(tCola *pc);

int colaVacia(const tCola *pc);

int colaLlena(const tCola *pc, unsigned tamInfo);

int ponerEnCola(tCola *pc, const void *dato, unsigned tamInfo);

int verPrimero(const tCola *pc, void *buffer, unsigned tamInfo);

int sacarDeCola(tCola *pc, void *buffer, unsigned tamInfo);

void vaciarCola(tCola *pc);

#endif
