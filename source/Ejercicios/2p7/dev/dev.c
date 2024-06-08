#include "dev.h"


void sumarDigitosPilas()
{
    tPila pila1,
          pila2,
          pila3;
    int suma,    // poner default 0 para cuando ninguna pila tiene elementos
        carry,
        resto,
        topePila1,
        topePila2;

    crearPila(&pila1);
    crearPila(&pila2);
    crearPila(&pila3);

    while(!pilaVacia(&pila1) || !pilaVacia(&pila2))
    {

        if(sacarDePila(&pila1, &topePila1, sizeof(topePila1)))
        {
            if(sacarDePila(&pila2, &topePila2, sizeof(topePila2)))
            {
                suma = topePila1 + topePila2;
            }
            else
                ;

        }
    }

    vaciarPila(&pila1);
    vaciarPila(&pila2);
    vaciarPila(&pila3);
}

void cargarPilas(tPila *pila1, tPila *pila2)
{
    int num1[] = {9, 8, 7, 6, 5, 4, 3, 2,1, 0},
                 num2[] = {1, 0},
                          i;

    for(i = 0; i < (sizeof(num1) / sizeof(*num1)); i++)
        ponerEnPila(pila1, num1 + i, sizeof(*(num1 + i)));

    for(i = 0; i < (sizeof(num2) / sizeof(*num2)); i++)
        ponerEnPila(pila2, num2 + i, sizeof(*(num2 + i)));
}
