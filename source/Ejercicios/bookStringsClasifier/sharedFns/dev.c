#include "dev.h"

#define MAX_TAM_LINEAS 1024

void menu(int mayorCnt, int menorCnt, tArbolBinBusq *palabras)
{
    char teclaIngresada = ' ';

    while(teclaIngresada != 'E')
    {
        printf("A: ver lista asc\nB: ver lista desc\nC: mostrar palabra mayor rep\nD: mostrar palabra menor rep\nE: salir\n\nOpcion: ");
        teclaIngresada = getc(stdin);
        fflush(stdin);
        puts("");
        switch(teclaIngresada)
        {
            case 'A':
                recorrerEnOrdenSimpleArbolBinBusq(palabras, stdout, mostrarRegs);
                break;
            case 'B':
                recorrerEnOrdenInversoSimpleArbolBinBusq(palabras, stdout, mostrarRegs);
                break;
            case 'C':
                recorrerEnOrdenSimpleArbolBinBusq(palabras, &mayorCnt, mostrarSiCumple);
                break;
            case 'D':
                recorrerEnOrdenSimpleArbolBinBusq(palabras, &menorCnt, mostrarSiCumple);
                break;
            case 'E':
                break;
            default:
                printf("Ingrese una opci�n v�lida");
        }
        printf("\n\nPresion� cualquier tecla para continuar");
        getch();
        system("cls");
    }
}

int procesarLibro(char *path, tArbolBinBusq *palabras)
{
    FILE *pfLibro;
    char linea[MAX_TAM_LINEAS],
         *ini,
         *fin;
    unsigned longitud;
    tRegistroPalabra regPalabra;

    pfLibro = abrirArchivoTexto(path);

    if(!pfLibro)
        return ERROR_ABRIR_ARCHIVO;

    while(fgets(linea, MAX_TAM_LINEAS, pfLibro))
    {
        if( (fin = strrchr(linea, '\n')) )
            *fin = '\0';
        ini = NULL;
        fin = NULL;
        while((longitud = proximaPalabra(linea, &ini, &fin)))
        {
            sprintf(regPalabra.palabra, "%*s", longitud, ini);
            regPalabra.cantRep = 0;
            insertarArbolBinBusq(palabras, &regPalabra, sizeof(regPalabra), compararRegsPalabra, acumularCantRepeticiones);
        }
    }

    fclose(pfLibro);

    return TODO_OK;
}

int proximaPalabra(char *linea, char **ini, char **fin)
{
    unsigned cant = 0;
    const char *finRef = linea + strlen(linea);

    if(!(*linea))
        return cant;

    if((*ini < linea) || (*ini > finRef) || !(*ini))
        *ini = linea;

    while(**ini && !ES_LETRA(**ini) && !ES_CARACTER_ESPECIAL(**ini)) /// delimito el inicio de la palabra
        (*ini)++;

    *fin = *ini; /// seteo a fin para que comience a identificar la palabra

    while(**fin && (ES_LETRA(**fin) || ES_CARACTER_ESPECIAL(**fin) || (**fin != 32)))
    {
        cant++;
        (*fin)++;
    }

    *ini = *fin; /// ini en la pr�xima iteraci�n comenzar� a recorrer desde la sig. posici�n a del fin de la palabra reconocida
    (*fin)--; /// ajusto a fin nuevamente

    return cant;
}

void mostrarRegs(void *reg, unsigned tamInfo, void *recurso)
{
    FILE *pf = (FILE *)recurso;
    tRegistroPalabra *r = (tRegistroPalabra *)reg;

    if(r)
        fprintf(pf, "-> ' %s '    ", r->palabra);
}

void mostrarSiCumple(void *reg, unsigned tamInfo, void *recurso)
{
    int cant = *((int *)recurso);
    const tRegistroPalabra *r = (tRegistroPalabra *)reg;

    if(r && (r->cantRep == cant) )
        printf("%s -> %d %s repetida\n\n", r->palabra, r->cantRep, (r->cantRep > 1)?"veces":"vez");
}

void buscarMayor(void *reg, unsigned tamInfo, void *recurso)
{
    int *cant = (int *)recurso;
    tRegistroPalabra *r = (tRegistroPalabra *)reg;

    if(r && (r->cantRep > *cant ))
        *cant = r->cantRep;
}

void buscarMenor(void *reg, unsigned tamInfo, void *recurso)
{
    int *cant = (int *)recurso;
    tRegistroPalabra *r = (tRegistroPalabra *)reg;

    if(r && ( ( *cant == -1 ) || ( ( r->cantRep != 0 ) && ( r->cantRep < *cant ) ) ) )
        *cant = r->cantRep;
}

int acumularCantRepeticiones(void **reg, unsigned *tamReg, const void *info, unsigned tamInfo)
{
    tRegistroPalabra **r = (tRegistroPalabra **)reg;

    (*r)->cantRep += 1;

    return TODO_OK;
}

int compararRegsPalabra(const void *reg1, const void *reg2)
{
    tRegistroPalabra *r1 = (tRegistroPalabra *)reg1, *r2 = (tRegistroPalabra *)reg2;
    return strcmpi(r1->palabra, r2->palabra);
}

int liberarBufferPalabra(void *reg, void *rec)
{
    tRegistroPalabra *r = (tRegistroPalabra *) reg;
    free(r->palabra);

    return TODO_OK;
}

int crearArchivoTexto(char *path)
{
    FILE *pf;

    if(!(pf = fopen(path, "wt")))
        return ERROR_CREAR_ARCHIVO;

    fclose(pf);
    return TODO_OK;
}

FILE *abrirArchivoTexto(char *path)
{
    FILE *pf;
    pf = fopen(path, "rt");

    return pf;
}
