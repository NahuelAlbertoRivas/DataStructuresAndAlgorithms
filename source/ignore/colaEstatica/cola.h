#ifndef COLA
#define COLA

#define COLA_LLENA 0
#define TODO_OK 1
#define COLA_VACIA 0
#define SIN_MEM 0
#define TAM_COLA 100

typedef struct
{
    char cola[TAM_COLA];
    unsigned primero,
             ultimo,
             tamDisponible;
} tCola;

void crearCola(tCola *pc);

int colaVacia(const tCola *pc);

int colaLlena(const tCola *pc, unsigned cantBytes);

ponerEnCola();

verTope();

sacarDeCola();

void vaciarCola(tCola *pc);

#endif
