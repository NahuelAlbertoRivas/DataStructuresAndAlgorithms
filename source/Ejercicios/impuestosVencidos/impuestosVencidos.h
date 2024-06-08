#ifndef IMPUESTOSVENCIDOS
#define IMPUESTOSVENCIDOS

#include "../../arbolBinBusq/arbol.h"
#include "../../strValidators/strValidators.h"
#include <winsock2.h>
#include <windows.h>
#include <unistd.h>

#define MAX_TAM_PATENTE 8
#define MAX_TAM_TITULAR 26

typedef struct
{
    char patente[MAX_TAM_PATENTE];
    byte nroCuota;
    char titular[MAX_TAM_TITULAR];
    short unsigned dni,
                   vto;
    double importe;
} tImpuesto;

typedef int (*CompararImp)(const void *, const void *);

int procesarArchivo(const char *src_path, const char *op, const char *res_path);
void parsearLinea(char *linea, tImpuesto *imp);
int generarInforme(tArbolBinBusq *impuestos, const char *res_path);
int compararDNI(const void *dato1, const void *dato2);
int compararDNIyPatente(const void *dato1, const void *dato2);

#endif
