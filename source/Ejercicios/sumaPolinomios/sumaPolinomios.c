#include "exports.h"
#include "dev.h"

#define PATH_POLINOMIOS_1 "../source/Ejercicios/sumaPolinomios/Archivos/p1.txt"
#define PATH_POLINOMIOS_2 "../source/Ejercicios/sumaPolinomios/Archivos/p2.txt"
#define PATH_RES "../source/Ejercicios/sumaPolinomios/Archivos/pr.txt"
#define OK 1

int sumaPolinomios(void *recurso)
{
    procesarArchivoPolinomios(PATH_POLINOMIOS_1, PATH_POLINOMIOS_2, PATH_RES);

    return OK;
}

