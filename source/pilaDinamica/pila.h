#ifndef PILA_DINAMICA
#define PILA_DINAMICA

#define TODO_OK 1
#define SIN_MEM 0
#define PILA_LLENA 1
#define PILA_VACIA 0

typedef struct sNodo
{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tPila;

void crearPila(tPila *pp);

int pilaVacia(const tPila *pp);

int pilaLlena(const tPila *pp, unsigned tamInfo);

int ponerEnPila(tPila *pp, const void *info, unsigned tamInfo);

int verTope(const tPila *pp, void *buffer, unsigned cantBytes);

int sacarDePila(tPila *pp, void *buffer, unsigned cantBytes);

void vaciarPila(tPila *pp);

#endif
