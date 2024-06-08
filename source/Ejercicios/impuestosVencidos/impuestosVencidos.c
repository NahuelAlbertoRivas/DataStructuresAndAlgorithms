#include "impuestosVencidos.h"

#define MENOR -1
#define MAYOR 1
#define MAX_TAM_LINEA 101

int procesarArchivo(const char *src_path, const char *op, const char *res_path)
{
    FILE *pfImpuestos = fopen(src_path, "rb");
    tArbolBinBusq impuestos;
    CompararImp cmp = (!strcmpi(op, "a"))? compararDNI : compararDNIyPatente;
    char linea[MAX_TAM_LINEA];

    if(!pfImpuestos)
        return -1;

    crearArbolBinBusq(&impuestos);

    while(fgets(linea, MAX_TAM_LINEA, pfImpuestos))
    {

    }

    eliminarArbol(&impuestos);

    fclose(pfImpuestos);

    return 1;
}

void parsearLinea(char *linea, tImpuesto *imp)
{

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

    return (d1->dni < d2->dni)? MENOR : MAYOR;
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
