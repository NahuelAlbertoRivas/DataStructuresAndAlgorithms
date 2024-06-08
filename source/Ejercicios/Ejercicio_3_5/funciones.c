#include <stdlib.h>
#include <stdio.h>
#include "funciones.h"

int demoraAleatoria()
{
     return 2* (rand()%3) + 1;
}

int arriboAleatorio()
{
     return 4* (rand()%3) + 1;
}

void generarPersonaAleatoria(tPersona * persona, int numero)
{
    persona->numero = numero;
    persona->demora = demoraAleatoria();
    persona->arribo = arriboAleatorio();
}

void simulacionPersonasEnCola(tCola * cola, int tTotal, int personaNueva)
{
    int i;
    tPersona buffer;
    printf("\n%02d min - COLA:", tTotal);

    if(verPrimeroCola(cola, &buffer, sizeof(tPersona)))
    {
        for(i=buffer.numero; i< personaNueva; i++)
            printf(" %d", i);

        printf("\n");
    }

}
