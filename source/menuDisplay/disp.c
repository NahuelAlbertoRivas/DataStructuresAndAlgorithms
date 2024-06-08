#include "disp.h"
#define B 1
#define MST_OPS ("mst_ops.txt")
#define CANT_OPS 2

int byo(void *recurso)
{
    setlocale(LC_ALL, "Spanish");
    Accion *tareas = malloc(sizeof(Accion) * CANT_OPS);
    char bufferMenu[MAX_LINEA_MENU];
    FILE *pfConfig = fopen(MST_OPS, "rt");

    if(!pfConfig)
        return -2;

    if(!tareas)
    {
        fclose(pfConfig);
        return -1;
    }

    tareas[0] = mostrarOpciones;
    tareas[1] = p3_5;

    printf("Hola!");
    sleep(3);
    system("cls");
    printf("Elegi lo que quieras ver");
    sleep(3);
    system("cls");
    menu(pfConfig, bufferMenu, NULL, tareas);

    system("cls");

    fclose(pfConfig);
    free(tareas);

    return B;
}

int mostrarOpciones(void *recurso)
{
    printf("Nice");
    sleep(4);
    system("cls");
    return B;
}
