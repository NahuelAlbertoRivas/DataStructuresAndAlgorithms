#include "locMayorSup.h"
#include "../../strValidators/strValidators.h"

#define FIN_PROCESO 2

void mostrarEnt(const void *info, FILE *pf)
{
    int *d = (int *)info;

    printf("%d\n", *d);
}

int cmpInt(const void *info1, const void *info2)
{
    int *d1 = (int *)info1, *d2 = (int *)info2;

    return *d1 - *d2;
}

int locMayorSup(void *recursos)
{
    int vec[] = {1, 100, 2, 5, -1, 1000, 8, 3, 6, 21, 21, 2, 100, 20, 20, 20, 20, 10, 90, 88, -20, 77};
    byte i;
    tLista nros;
    crearLista(&nros);

    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
        insertarOrdenadoDescConLimite(&nros, vec + i, sizeof(int), cmpInt, NULL, 5);

    mostrarLista(&nros, mostrarEnt, stdout);

    vaciarLista(&nros);

    printf("\n\n¡Nos vemos!");
    sleep(3);
    system("cls");

    return FIN_PROCESO;
}
