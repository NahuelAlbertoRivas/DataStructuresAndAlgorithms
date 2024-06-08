#ifndef COLA
#define COLA

#define COLA_VACIA 0
#define COLA_LLENA 1
#define TODO_OK 1
#define SIN_MEM 0

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

void crearCola(tCola *pc);

int colaVacia(const tCola *pc);

int colaLlena(const tCola *pc, unsigned cantBytes);

int ponerEnCola(tCola *pc, const void *info, unsigned tamInfo);

int verPrimero(const tCola *pc, void *buffer, unsigned cantBytes);

int sacarDeCola(tCola *pc, void *buffer, unsigned cantBytes);

void vaciarCola(tCola *pc);

#endif
