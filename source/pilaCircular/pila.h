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

typedef struct sNodoPilaCirc
{
    void *info;
    unsigned tamInfo;
    struct sNodoPilaCirc *sig;
} tNodoPilaCirc;

typedef tNodoPilaCirc *tPilaCirc;

void crearPilaCirc(tPilaCirc *p);
int pilaLlenaCirc(const tPilaCirc *p, unsigned cantBytes);
int ponerEnPilaCirc(tPilaCirc *p, const void *d, unsigned cantBytes);
int verTopeCirc(const tPilaCirc *p, void *d, unsigned cantBytes);
int pilaVaciaCirc(const tPilaCirc *p);
int sacarDePilaCirc(tPilaCirc *p, void *d, unsigned cantBytes);
void vaciarPilaCirc(tPilaCirc *p);

#endif
