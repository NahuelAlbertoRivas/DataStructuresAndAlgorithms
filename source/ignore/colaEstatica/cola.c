#include "cola.h"

void crearCola(tCola *pc)
{
    pc->tamDisponible = TAM_COLA;
    pc->primero = 0;
    pc->ultimo = 0;
}

int colaVacia(const tCola *pc)
{
    return pc->tamDisponible == TAM_COLA;
}

int colaLlena(const tCola *pc, unsigned cantBytes)
{
    return pc->tamDisponible < (cantBytes + sizeof(unsigned));
}


/*
sacarDeCola()
{

    // despues de todo

    pc->primero = (pc->primero + tamOriginal) % TAM_COLA;

}
*/

void vaciarCola(tCola *pc)
{
    pc->tamDisponible = TAM_COLA;
    pc->primero = pc->ultimo;
}
