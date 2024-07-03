#include "cola.h"

void crearCola(tCola *pc)
{
    pc->pri = pc->ult = 0;
    pc->tamDisp = TAM_COLA;
}

int colaVacia(const tCola *pc)
{
    return pc->tamDisp == TAM_COLA;
}

int colaLlena(const tCola *pc, unsigned cantBytes)
{
    return pc->tamDisp < (cantBytes + sizeof(unsigned));
}

int ponerEnCola(tCola *pc, const void *info, unsigned cantBytes)
{
    unsigned ini,
             fin;

    if(pc->tamDisp < (cantBytes + sizeof(unsigned)))
        return SIN_MEM;

    pc->tamDisp -= (sizeof(unsigned) + cantBytes);
    if((ini = MINIMO(sizeof(unsigned), TAM_COLA - pc->ult)))
        memcpy(pc->cola + pc->ult, &cantBytes, ini);
    if((fin = sizeof(unsigned) - ini))
        memcpy(pc->cola, ((char *)&cantBytes) + ini, fin);
    pc->ult = fin ? fin : pc->ult + ini;
    if((ini = MINIMO(cantBytes, TAM_COLA - pc->ult)))
        memcpy(pc->cola + pc->ult, info, ini);
    if((fin = cantBytes - ini))
        memcpy(pc->cola, ((char *)info) + ini, fin);
    pc->ult = fin ? fin : pc->ult + ini;

    return TODO_OK;
}

int verPrimero(const tCola *pc, void *buffer, unsigned cantBytes)
{
    unsigned ini,
             fin,
             tamAux,
             pos = pc->ult;

    if(pc->tamDisp == TAM_COLA)
        return COLA_VACIA;

    if((ini = MINIMO(sizeof(unsigned), TAM_COLA - pos)))
        memcpy(&tamAux, pc->cola + pos, ini);
    if((fin = sizeof(unsigned) - ini))
        memcpy(((char *)&tamAux) + ini, pc->cola, fin);
    pos = fin ? fin : pos + ini;
    tamAux = MINIMO(cantBytes, tamAux);
    if((ini = MINIMO(tamAux, TAM_COLA - pos)))
        memcpy(buffer, pc->cola + pos, ini);
    if((fin = tamAux - ini))
        memcpy(((char *)&buffer) + ini, pc->cola, fin);

    return TODO_OK;
}

int sacarDeCola(tCola *pc, void *buffer, unsigned cantBytes)
{
    unsigned ini,
             fin,
             tamAux;

    if(pc->tamDisp == TAM_COLA)
        return COLA_VACIA;

    if((ini = MINIMO(sizeof(unsigned), TAM_COLA - pc->pri)))
        memcpy(&tamAux, pc->cola + pc->pri, ini);
    if((fin = sizeof(unsigned) - ini))
        memcpy(((char *)&tamAux) + ini, pc->cola, fin);
    pc->pri = fin ? fin : pc->pri + ini;

    pc->tamDisp += tamAux + sizeof(unsigned);
    cantBytes = MINIMO(cantBytes, tamAux);

    if((ini = MINIMO(cantBytes, TAM_COLA - pc->pri)))
        memcpy(buffer, pc->cola + pc->pri, ini);
    if((fin = tamAux - ini))
        memcpy(((char *)buffer) + ini, pc->cola, fin);

    pc->pri = (pc->pri + tamAux) % TAM_COLA;

    return TODO_OK;
}

void vaciarCola(tCola *pc)
{
    pc->pri = pc->ult = 0;
    pc->tamDisp = TAM_COLA;
}
