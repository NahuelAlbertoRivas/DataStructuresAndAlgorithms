#include "dev.h"

#define MAX_TAM_LINEAS 1024
#define MINIMO(X,Y) ((X)<(Y)?(X):(Y))

void menu(int mayorCnt, int menorCnt, tArbolBinBusq *palabras)
{
    char teclaIngresada = ' ';

    while(teclaIngresada != 'E')
    {
        printf("A: ver lista en orden asc\nB: ver lista en orden desc\nC: mostrar palabra/s con mayor cantidad de repeticiones\nD: mostrar palabra/s con menor cantidad de repeticiones\nE: salir\n\nOpcion: ");
        teclaIngresada = getc(stdin);
        fflush(stdin);
        if(ES_MINUSCULA(teclaIngresada))
            teclaIngresada = A_MAYUSC(teclaIngresada);
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
                printf("Ingrese una opción válida");
        }
        printf("\n\nPresioná ' ENTER ' para continuar");
        getc(stdin);
        fflush(stdin);
        system("cls");
    }
}

int procesarLibro(char *path, tArbolBinBusq *palabras, const char *setSeparadores)
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
        while((longitud = proximaPalabra(linea, &ini, &fin, setSeparadores)) || *ini)
        {
            if(longitud)
            {
                formarPalabra(regPalabra.palabra, ini, longitud);
                regPalabra.cantRep = 0;
                insertarArbolBinBusq(palabras, &regPalabra, sizeof(regPalabra), compararRegsPalabra, acumularCantRepeticiones);
            }
        }
    }

    fclose(pfLibro);

    return TODO_OK;
}

int proximaPalabra(char *linea, char **ini, char **fin, const char *setSeparadores)
{
    unsigned cant = 0;

    if(!(*linea))
        return cant;

    if(!(*ini))
        *ini = linea;
    else
        *ini = (*fin) + 1;

    while(**ini && !ES_LETRA(**ini) && !ES_CARACTER_ESPECIAL(**ini) && reconocerCaracterSeparacion(setSeparadores, strlen(setSeparadores), **ini)) /// delimito el inicio de la palabra
        (*ini) = (*ini) + 1;

    *fin = *ini; /// seteo a fin para que comience a identificar la palabra

    while(**fin && (ES_LETRA(**fin)
          || ES_CARACTER_ESPECIAL(**fin)
          || !reconocerCaracterSeparacion(setSeparadores, strlen(setSeparadores), **fin)))
    {
        cant++;
        (*fin) = (*fin) + 1;
    }

    (*fin) = (*fin) - 1; /// ajusto a fin nuevamente

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

    if(r && ( r->cantRep != 0 ) && ( ( *cant == -1 ) || ( ( r->cantRep < *cant ) ) ) )
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
