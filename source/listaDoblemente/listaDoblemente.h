#ifndef LISTADOBLEMENTE
#define LISTADOBLEMENTE

#include <stdlib.h>
#include <winsock2.h>
#include <stdio.h>
#include <string.h>

#define TODO_OK 1
#define LISTA_VACIA 0
#define SIN_COINCIDENCIAS -13
#define CLA_DUP 3

typedef struct sNodoListaDoble{
    void *info;
    unsigned tamInfo;
    struct sNodoListaDoble *ant,
                           *sig;
}tNodoListaDoble;

typedef tNodoListaDoble *tListaDoble;

typedef int (*Accion)(void *);

typedef int (*Comparacion)(const void *, const void*);

typedef int (*Acumular)(void **, unsigned *, const void *, unsigned);

typedef void (*Mostrar)(const void *, FILE *);

void crearListaDoble(tListaDoble *pl);

int listaVaciaDoble(const tListaDoble *pl);

int insertarAlComienzoListaDoble(tListaDoble *pl, const void *info, unsigned cantBytes);

int insertarAlFinalListaDoble(tListaDoble *pl, const void *info, unsigned cantBytes);

int insertarEnOrdenListaDoble(tListaDoble *pl, const void *info, unsigned cantBytes, Comparacion cmp, Acumular acm);

int ordenarListaDoble(tListaDoble *pl, Comparacion cmp);

int listaLlenaDoble(const tListaDoble *pl, unsigned cantBytes);

int eliminarUltimoListaDoble(tListaDoble *pl);

int eliminarPorClaveListaDoble(tListaDoble *pl, void *dato, unsigned cantBytes, Comparacion cmp);

int mostrarIzqADer(const tListaDoble *pl, Mostrar mostrar, FILE *pf);

int mostrarDerAIzq(const tListaDoble *pl, Mostrar mostrar, FILE *pf);

int mostrarYVaciarListaDoble(tListaDoble *pl);

int vaciarListaDoble(tListaDoble *pl);

#endif // LISTADOBLEMENTE
