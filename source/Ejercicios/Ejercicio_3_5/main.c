#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "funciones.h"
#include "exports.h"
#define MIN(x,y) ((x)<(y)?(x):(y))

int p3_5(void *recurso)
{

    int tiempoTotal = 0,
        numeroPersona = 1,
        tiempoHastaProxArribo,
        tiempoPersonaEnCaja,
        tiempoHastaProxEvento,
        vueltasCompletas = 1;

    tCola cola;
    tPersona personaNueva, personaEnCaja, buffer;

    srand(time(NULL));
    crearCola(&cola);

    printf("\nABRE LA CAJA\n");

    generarPersonaAleatoria(&personaNueva, numeroPersona); // Genero una persona nueva y le asigno el numero 1
    tiempoHastaProxArribo = personaNueva.arribo;

    do
    {
        if (colaVacia(&cola))
        {
            printf("\n\n%02d min - CAJA VACIA POR %d MINUTOS \n\n", tiempoTotal, tiempoHastaProxArribo);
            tiempoPersonaEnCaja = personaNueva.demora;

            tiempoTotal += tiempoHastaProxArribo;

            ponerEnCola(&cola, &personaNueva, sizeof(tPersona));


            numeroPersona ++;
            generarPersonaAleatoria(&personaNueva, numeroPersona);
            tiempoHastaProxArribo = personaNueva.arribo;
        }
        else
        {

            simulacionPersonasEnCola(&cola, tiempoTotal, personaNueva.numero);

            tiempoHastaProxEvento = MIN(tiempoPersonaEnCaja, tiempoHastaProxArribo); // Calculo el tiempo hasta el proximo evento

            tiempoHastaProxArribo -= tiempoHastaProxEvento; //Se lo resto al tiempo hasta el proximo arribo
            tiempoPersonaEnCaja -= tiempoHastaProxEvento; //Se lo resto al tiempo de peronson en la caja
            tiempoTotal += tiempoHastaProxEvento; //Se lo sumo al tiempo total

            if(!tiempoHastaProxArribo) // Llego una persona a la caja
            {
                ponerEnCola(&cola, &personaNueva, sizeof(tPersona)); // La agrego a la cola
                numeroPersona++;
                generarPersonaAleatoria(&personaNueva, numeroPersona); // genero una persona nueva para saber el proximo arribo
                tiempoHastaProxArribo = personaNueva.arribo; // Lo guardo en la variable correspondiente
            }

            if(!tiempoPersonaEnCaja) // La persona que estaba en la caja termino su tramite
            {
                sacarDeCola(&cola, &buffer, sizeof(tPersona)); // la saco de la cola

                if(verPrimeroCola(&cola, &personaEnCaja,sizeof(tPersona))) // Me fijo si hay mas personas en la cola
                    tiempoPersonaEnCaja = personaEnCaja.demora; // En caso afirmativo guardo el tiempo que va a estar esa persona en la caja
                else
                    vueltasCompletas ++; // En caso que no haya nadie en la cola, significaria que la caja estaria vacia por un rato, entonces sumo una vuelta
            }
        }
    }while(vueltasCompletas <= 5);


    printf("\nCIERRE DE CAJA\n");

    printf("\n\nREPORTE: Se atendieron a %d personas en %d minutos\n", numeroPersona-1, tiempoTotal);

    getch();
    system("cls");

    return 0;
}
