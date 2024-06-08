#ifndef FUNCIONES
#define FUNCIONES
#include "../../colaDinamica/cola.h"

typedef struct
{
    int numero,
        demora,
        arribo;
}tPersona;

int demoraAleatoria();
int arriboAleatorio();
void generarPersonaAleatoria(tPersona * persona, int numero);
void simulacionPersonasEnCola(tCola * cola, int tTotal, int personaNueva);

#endif
