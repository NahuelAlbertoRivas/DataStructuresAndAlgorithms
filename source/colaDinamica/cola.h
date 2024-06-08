/* --------------------------------o---x---o--------------------------------
* cola.h TDA COLA con asignaci�n din�mica de memoria
* --------------------------------o---x---o-------------------------------- */

#ifndef COLA_H_
#define COLA_H_

#include <stdlib.h>
#include <string.h>

#define MINIMO( X , Y ) ( ( X ) <= ( Y ) ? ( X ) : ( Y ) )


typedef struct sNodo
{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
} tNodo;

typedef struct
{
    tNodo *pri,
          *ult;
} tCola;

void crearCola(tCola *p);

int colaLlena(const tCola *p, unsigned cantBytes);

int ponerEnCola(tCola *p, const void *d, unsigned cantBytes);

int verPrimeroCola(const tCola *p, void *d, unsigned cantBytes);

int colaVacia(const tCola *p);

int sacarDeCola(tCola *p, void *d, unsigned cantBytes);

void vaciarCola(tCola *p);

#endif
