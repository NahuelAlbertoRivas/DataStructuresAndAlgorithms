#include "impuestosVencidos.h"
#include "lotePrueba/lotePrueba.h"
#include <winsock2.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>

#define TAM_OP 2
#define SRC_PATH "../source/Ejercicios/impuestosVencidos/files/impuestosVencidos.dat"
#define RES_PATH "../source/Ejercicios/impuestosVencidos/files/deuda.txt"

int impVencidos(void *recursos)
{
    char op[TAM_OP] = "q";

    while(strcmpi(op, "f"))
    {
        printf("¡Bienvenida/o! Por favor, selecciona la clave con que se va a ordenar el archivo \"deuda.txt\" [o bien ingresa \"F\" para abandonar el proceso]\n[A] DNI\n[B] DNI y patente\nOpcion: ");
        fgets(op, TAM_OP, stdin);
        fflush(stdin);
        if(!strcmpi(op, "a") || !strcmpi(op, "b"))
        {
            crearLoteImpVencidos();
            procesarArchivoImpVencidos(SRC_PATH, op, RES_PATH);
        }
        else if(strcmpi(op, "f"))
        {
            printf("\nPor favor, revisa la entrada y selecciona una opcion existente");
            sleep(2);
            system("cls");
        }
    }

    printf("\n¡Nos vemos!");
    sleep(2);
    system("cls");

    return 1;
}
