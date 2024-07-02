#include "menu.h"
#include "../strHandler/strHandler.h"

#define ByO ( \
"¡Bienvenida/o!\nSelecciona la tarea a realizar\n \
A) Algo\n \
B) Otra cosa\n \
C) Otra\n \
D) La ultima\n \
S) Salir\n\
Opcion: " \
)

void ingresoNoRequerido(char buff)
{
    buff = getch();
    fflush(stdin);
}

char ingresoOpcion(char *op)
{
    *op = getc(stdin);
    fflush(stdin);

    *op = A_MAYUSC(*op);

    return *op;
}

void mostrarMenu()
{
    char op;

    printf(ByO);

    while(ingresoOpcion(&op) != 'S')
    {
        switch(op)
        {
            case 'A':
                printf("\nOpcion A) seleccionada\n");
                break;
            case 'B':
                printf("\nOpcion B) seleccionada\n");
                break;
            case 'C':
                printf("\nOpcion C) seleccionada\n");
                break;
            case 'D':
                printf("\nOpcion D) seleccionada\n");
                break;
            default:
                printf("\nOpcion inexistente, por favor, revisa la entrada\n");
        }
        printf("\nIngresa cualquier tecla para continuar");
        ingresoNoRequerido(' ');
        system("cls");
        printf(ByO);
    }
}
