#include "menu.h"
#include "../dev/dev.h"

#define ByO ("¡Bienvenida/o!\n\
Por favor, selecciona una opcion\n\
A) Generar archivos\n\
B) Seleccionar archivo y mostrar datos\n\
C) Ver archivo de productos vencidos\n\
S) Salir\n\
Opcion: \
")

#define A_MAYUSC(x) ( ( ( (x) >= 97 ) && ( (x) <= 126 ) )? (x) - 32 : (x) )

char ingresoMostrandoMsj(const char *msj, char *op)
{
    printf(msj);
    *op = getc(stdin);
    fflush(stdin);

    *op = A_MAYUSC(*op);

    return *op;
}

void ingresoNoRequerido(char buff)
{
    buff = getch();
    fflush(stdin);
}

void mostrarMenu(unsigned n, tFecha fAct)
{
    char op,
         opArch;

    while(ingresoMostrandoMsj(ByO, &op) != 'S')
    {
        switch(op)
        {
            case 'A':
                puts("\n¡Archivos generados!\n");
                procesarStockDat(n, fAct);
                break;
            case 'B':
                ingresoMostrandoMsj("\nSelecciona el archivo\n1) prod_ok\n2) stock_dat\nOpcion: ", &opArch);
                (opArch == '1')?
                    puts("\nMostrando prod_ok\n"),
                    mostrarArchRegStock(PATH_PROD_OK)
                    : (opArch == '2')?
                        puts("\nMostrando stock_dat\n"),
                        mostrarArchRegStock(PATH_STOCK)
                        : puts("Por favor, revisa la entrada");
                break;
            case 'C':
                puts("\nMostrando vence.txt\n");
                mostrarVence();
                break;
            case 'S':
                puts("Saliendo\n");
                break;
            default:
                puts("Por favor revisa la entrada\n");
        }
        puts("\nIngresa cualquier tecla para continuar");
        ingresoNoRequerido(' ');
        system("cls");
    }
}
