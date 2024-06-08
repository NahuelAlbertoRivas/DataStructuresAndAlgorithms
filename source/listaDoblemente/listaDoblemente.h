#ifndef LISTADOBLEMENTE
#define LISTADOBLEMENTE

#include <stdlib.h>
#include <winsock2.h>
#include <stdio.h>
#include <string.h>

#define TODO_OK 1
#define LISTA_VACIA 0
#define SIN_MEM 0
#define CLA_DUP 3

typedef struct sNodo{
    void *info;
    unsigned tamInfo;
    struct sNodo *ant,
                 *sig;
}tNodo;

typedef tNodo *tLista;

typedef struct{
    long id_producto;
    tLista *dirRegistro;
}tIndice;

typedef int (*Accion)(void *);

typedef int (*Comparacion)(const void *, const void*);

typedef int (*Acumular)(void **, unsigned *, const void *, unsigned);

typedef void (*Mostrar)(const void *, FILE *);

void crearLista(tLista *pl);

int listaVacia(const tLista *pl);

int insertarAlComienzo(tLista *pl, const void *info, unsigned cantBytes);

int insertarAlFinal(tLista *pl, const void *info, unsigned cantBytes);

int insertarEnOrden(tLista *pl, const void *info, unsigned cantBytes, Comparacion cmp, Acumular acm);

int ordenar(tLista *pl, Comparacion cmp);

int listaLlena(const tLista *pl, unsigned cantBytes);

int eliminarPorClave(tLista *pl, void *dato, unsigned cantBytes, Comparacion cmp);

int mostrarIzqADer(const tLista *pl, Mostrar mostrar, FILE *pf);

int mostrarDerAIzq(const tLista *pl, Mostrar mostrar, FILE *pf);

int mostrarYVaciarLista(tLista *pl);

int vaciarLista(tLista *pl);

#endif // LISTADOBLEMENTE
