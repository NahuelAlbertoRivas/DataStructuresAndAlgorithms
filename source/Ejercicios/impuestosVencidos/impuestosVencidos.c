#include "impuestosVencidos.h"
#include "../../strValidators/strValidators.h"

#define MENOR -1
#define IGUAL 0
#define MAYOR 1
#define MAX_TAM_LINEA 101
#define COTA_INF_A 2010
#define COTA_SUP_A 2080
#define REG_NO_VAL 0
#define CANT_TOTAL_ITEMS 6
#define ERROR_PARAMS -3
#define ERROR_APERT_ARCH -7
#define BIEN 1
#define FIN_PROCESO 5

#include <conio.h>

int procesarArchivoImpVencidos(const char *src_path, const char *op, const char *res_path)
{
    FILE *pfImpuestos = fopen(src_path, "rb");
    tArbolBinBusq impuestos;
    CompararImp cmp;
    MostrarImp mst;
    tImpuesto imp;

    if(!pfImpuestos)
        return ERROR_APERT_ARCH;

    crearArbolBinBusq(&impuestos);

    definirFuncionesPorClave(op, &cmp, &mst);

    while(fread(&imp, sizeof(tImpuesto), 1, pfImpuestos))
    {
        if(recuperarRegValido(&imp) == BIEN)
            insertarArbolBinBusq(&impuestos, &imp, sizeof(imp), cmp, acumularDeuda);
    }

    generarInforme(&impuestos, res_path, mst);

    eliminarArbol(&impuestos);

    fclose(pfImpuestos);

    getch();
    system("cls");

    return FIN_PROCESO;
}

int recuperarRegValido(tImpuesto *imp)
{
    if(!validarDNI(imp->dni) || !validarImporte(imp->importe) || !validarNroCuota(imp->nroCuota) || !validarVto(imp->vto))
        return REG_NO_VAL;

    return BIEN;
}

char *buscarCharEnLineaVerificando(char *linea, char *dir, char caracter)
{
    if((dir = strrchr(linea, caracter)))
        *dir = '\0';

    return dir;
}

int compararDNI(const void *dato1, const void *dato2)
{
    tImpuesto *d1,
              *d2;

    if(!dato1)
        return MENOR;

    if(!dato2)
        return MAYOR;

    d1 = (tImpuesto *) dato1;
    d2 = (tImpuesto *) dato2;

    return (d1->dni < d2->dni)? MENOR : (d1->dni > d2->dni)? MAYOR : IGUAL;
}

int compararDNIyPatente(const void *dato1, const void *dato2)
{
    tImpuesto *d1,
              *d2;

    if(!dato1)
        return MENOR;

    if(!dato2)
        return MAYOR;

    d1 = (tImpuesto *) dato1;
    d2 = (tImpuesto *) dato2;

    return (d1->dni < d2->dni)? MENOR : (d1->dni > d2->dni)? MAYOR : strcmpi(d1->patente, d2->patente);
}

int acumularDeuda(void **info, unsigned *tamInfo, const void *dato, unsigned tamDato)
{
    tImpuesto *imp,
              *d;

    if(!info || !tamInfo || !dato)
        return ERROR_PARAMS;

    imp = (tImpuesto *) (*info);
    d = (tImpuesto *) dato;

    imp->importe += d->importe;
    if(imp->vto < d->vto)
        imp->vto = d->vto;

    return BIEN;
}

void mostrarImpuestosDNI(void *info, unsigned tamInfo, void *recursos)
{
    tImpuesto *imp;
    FILE *pf;

    if(!info || !recursos)
        return;

    imp = (tImpuesto *) info;
    pf = (FILE *)recursos;

    fprintf(pf, "%d|%.2lf\n", imp->dni, imp->importe);
}

void mostrarImpuestosDNIyPatente(void *info, unsigned tamInfo, void *recursos)
{
    tImpuesto *imp;
    FILE *pf;

    if(!info || !recursos)
        return;

    imp = (tImpuesto *) info;
    pf = (FILE *)recursos;

    fprintf(pf, "%d|%s|%.2lf\n", imp->dni, imp->patente, imp->importe);
}

byte validarImporte(double imp)
{
    return ((imp > 0) && (imp < 100000));
}

byte validarVto(unsigned vto)
{
    unsigned a;
    byte m,
         d;
    if( ((a = vto / 10000) < COTA_INF_A) || (a > COTA_SUP_A) ) /// las cotas son random, simple check
        return REG_NO_VAL;

    vto -= a * 10000;

    if(((m = vto / 100) < 1) || (m > 12))
        return REG_NO_VAL;

    d = vto - (m * 100);

    if((d < 1) || (d > 31)) /// podría hacer esFechaVal con bisiesto pero no viene al caso
        return REG_NO_VAL;

    return BIEN;
}

byte validarDNI(unsigned DNI)
{
    return ((DNI > 1000000) && (DNI < 100000000));
}

byte validarNroCuota(byte cta)
{
    return ((cta > 0) && (cta < 7));
}

void generarInforme(tArbolBinBusq *impuestos, const char *path, MostrarImp mst)
{
    FILE *pfInf = fopen(path, "wt");
    double total = 0;

    if(!pfInf)
        return;

    recorrerEnOrdenSimpleArbolBinBusq(impuestos, pfInf, mst);
    recorrerEnOrdenSimpleArbolBinBusq(impuestos, &total, acumularTotal); /// podría optimizarse y crear una fn. unificada que muestre y acumule el total de todas las cuotas vencidas

    fprintf(pfInf, "%.2lf", total);

    fclose(pfInf);
}

void acumularTotal(void *info, unsigned tamInfo, void *recurso)
{
    tImpuesto *imp;
    double *total;

    if(!info || !recurso)
        return;

    imp = (tImpuesto *)info;
    total = (double *)recurso;

    *total += imp->importe;
}

void definirFuncionesPorClave(const char *op, CompararImp *cmp, MostrarImp *mst)
{
    switch(ES_MINUSCULA(*op)?A_MAYUSC(*op):*op)
    {
        case 'A':
            *cmp = compararDNI;
            *mst = mostrarImpuestosDNI;
            break;
        case 'B':
            *cmp = compararDNIyPatente;
            *mst = mostrarImpuestosDNIyPatente;
    }
}

/// ignorar
//    char *p = linea;
//
//    buscarCharEnLineaVerificando(linea, p, '\n');
//    /// importe
//    if(!buscarCharEnLineaVerificando(linea, p, '|'))
//        return REG_NO_VAL;
//    p++;
//    if(!(*p) || !validarImporte((imp->importe = atof(p))))
//        return REG_NO_VAL;
//    /// vto
//    if(!buscarCharEnLineaVerificando(linea, p, '|'))
//        return REG_NO_VAL;
//    p++;
//    if(!(*p) || !validarVto((imp->vto = atoi(p))))
//        return REG_NO_VAL;
//    /// dni
//    if(!buscarCharEnLineaVerificando(linea, p, '|'))
//        return REG_NO_VAL;
//    p++;
//    if(!(*p) || !validarDNI((imp->dni = atoi(p))))
//        return REG_NO_VAL;
//    /// titular
//    if(!buscarCharEnLineaVerificando(linea, p, '|'))
//        return REG_NO_VAL;
//    p++;
//    if(!(*p))
//        return REG_NO_VAL;
//    strcpy(imp->titular, p); /// podría validarse, no lo hago para ahorrar tiempo
//    *(imp->titular + MAX_TAM_TITULAR) = '\0';
//    /// nro cuota
//    if(!buscarCharEnLineaVerificando(linea, p, '|'))
//        return REG_NO_VAL;
//    p++;
//    if(!(*p) || !validarNroCuota((imp->nroCuota = atoi(p)))) /// podría verificar la correlatividad de cuotas
//        return REG_NO_VAL;
//    /// patente
//    strcpy(imp->patente, linea); /// podría validarse, no lo hago para ahorrar tiempo
//    *(imp->patente + MAX_TAM_PATENTE) = '\0';
//
