#include "dev.h"

#define ES_NUMERO(x) ( (x) >= 48 && (x) <= 57 )
#define ES_LETRA(x) ( ( ((x) >= 'A') && ((x) <= 'Z') ) || ( ((x) >= 'a') && ((x) <= 'z') ) )
#define A_MINUSC(x) ( ( (x) >= 65 && (x) <= 90 )? (x) + 32 : (x) )
#define MINIMO(x, y) ( ( (x) < (y) )? (x) : (y) )

#define PATH_MENOS_MOV "../files/prodMenosMov.txt"
#define PATH_MAS_MOV "../files/prodMuchoMov.txt"
#define CANT_MOV_CONSIDERADA 50
#define MAX_TAM_LINEA 201
#define MAX_TAM_MOVS 31

int procesarMovimientos(const char *path)
{
    FILE *pfMovs = fopen(path, "rt"),   /// archivo fuente de movimientos
          *pfMas,                       /// archivo que contendrá las secuencias de movimientos menores al target establecido ('CANT_MOV_CONSIDERADA')
          *pfMenos;                     ///    "     "      "      "       "      "     "       mayores  "   "         "
    tCola movimientos;
    regProd prodActual,
            prodIngresante;
    unsigned cantRegistros = 0;
    int resLectura;

    if(!pfMovs)
        return ERR_APERTURA_ARCH;

    if(!(pfMenos = fopen(PATH_MENOS_MOV, "w+")))
    {
        fclose(pfMovs);
        return ERR_APERTURA_ARCH;
    }

    if(!(pfMas = fopen(PATH_MAS_MOV, "w+")))
    {
        fclose(pfMovs);
        fclose(pfMenos);
        return ERR_APERTURA_ARCH;
    }

    crearCola(&movimientos);

    prodActual.cantMovimientos = 0; /// seed ante eventualidades

    /// el siguiente algoritmo responde a cada caso planteado en ' Lógica ', en el directorio principal de la solución ("QueueMov")
    while(((resLectura = leerMov(pfMovs, &prodIngresante, &movimientos)) != SIN_CONTENIDO) || !colaVacia(&movimientos)) /// mientras haya contenido por leer, o secuencia de movimientos por registrar
    {
        if((resLectura == LECTURA_CORRECTA) /// si la lectura del movimiento ingresante fue relativamente exitosa,
            && (prodIngresante.codProd == prodActual.codProd)) /// y el cód. ingresante coincide con el que se está procesando actualmente
        {
            prodActual.cantMovimientos += prodIngresante.cantMovimientos; /// acumulo cantidad de movimientos
            cantRegistros++; /// incremento cantidad de registros correspondientes al cód. producto actual a sacar
        }
        else if((resLectura == SIN_CONTENIDO) || (prodIngresante.codProd != prodActual.codProd)) /// la primer condición cubre el caso n° 3), mientras que la segunda al 1.b)
        {
            if(prodActual.cantMovimientos < CANT_MOV_CONSIDERADA) /// identifico a qué archivo corresponde grabar la secuencia
                sacarNyGrabarEnArchivo(&movimientos, pfMenos, cantRegistros);
            else
                sacarNyGrabarEnArchivo(&movimientos, pfMas, cantRegistros);
            /// reseteo y dejo el contexto preparado para la siguiente secuencia
            prodActual.codProd = prodIngresante.codProd;
            prodActual.cantMovimientos = prodIngresante.cantMovimientos;
            cantRegistros = 1;
        }
    }

    vaciarCola(&movimientos);

    fclose(pfMovs);
    fclose(pfMas);
    fclose(pfMenos);

    return FIN_PROCESO;
}

int sacarNyGrabarEnArchivo(tCola *movimientos, FILE *pfReporte, unsigned cant)
{
    char linea[MAX_TAM_LINEA];

    if(colaVacia(movimientos))
        return SIN_CONTENIDO;

    while(cant--)
        if(sacarDeCola(movimientos, linea, MAX_TAM_LINEA))
            fprintf(pfReporte, "%s", linea);

    return TODO_OK;
}

int recuperarCantMovs(const char *linea, unsigned *cantMovs)
{
    const char *iniLinea = linea,
                *lectura;
    char movs[MAX_TAM_MOVS],
         *escritura = movs,
          *fin = movs + MAX_TAM_MOVS;

    if(!(*linea)) /// si el string es nulo, nos vamos
        return SIN_CONTENIDO;

    if( !(lectura = strrchr(linea, '\n')) && !(lectura = strrchr(linea, '\0')) ) /// si el string no está bien formado
        lectura = linea + strlen(linea); /// de alguna manera nos situamos en donde termina, para recorrerlo de atrás hacia delante

    while(!ES_NUMERO(*lectura) && (lectura > iniLinea)) /// retrocedemos tanto como podamos hasta que encontremos una secuencia de números, considerando también que no podemos exceder el inicio de la línea fuente
        lectura--;

    while(ES_NUMERO(*lectura) && (lectura > iniLinea)) /// delimitamos la secuencia de números
        lectura--;

    lectura++; /// queda delimitado el inicio

    while(ES_NUMERO(*lectura) && (escritura < fin))
    {
        *escritura = *lectura;
        escritura++;
        lectura++;
    }

    *escritura = '\0';

    *cantMovs = atoi(movs);

    return TODO_OK;
}

int recuperarCodProd(const char *linea, char *codProd)
{
    const char *lectura = linea;

    while(*lectura && !ES_LETRA(*lectura))
        lectura++;

    if(!(*lectura))
        return SIN_CONTENIDO;

    *codProd = A_MINUSC(*lectura);

    return TODO_OK;
}

int leerMov(FILE *pfMovs, regProd *prodInfo, tCola *movimientos)
{
    char linea[MAX_TAM_LINEA];

    if(!fgets(linea, MAX_TAM_LINEA, pfMovs))
        return SIN_CONTENIDO; /// si no logra leer más info., nos vamos

    if((recuperarCodProd(linea, &(prodInfo->codProd)) != TODO_OK) ||
            (recuperarCantMovs(linea, &(prodInfo->cantMovimientos)) != TODO_OK))
        return LECTURA_DEFECTUOSA; /// en caso de que la línea de texto recuperada no sea mínimamente consistente, se reportará el caso

    ponerEnCola(movimientos, linea, MINIMO(strlen(linea) + 1, MAX_TAM_LINEA));

    return LECTURA_CORRECTA;
}
