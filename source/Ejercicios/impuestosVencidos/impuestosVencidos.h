#ifndef IMPUESTOSVENCIDOS
#define IMPUESTOSVENCIDOS

#include "../../arbolBinBusq/arbol.h"
#include "../../strValidators/strValidators.h"
#include <winsock2.h>
#include <windows.h>
#include <unistd.h>

#define MAX_TAM_PATENTE 9
#define MAX_TAM_TITULAR 26

typedef struct
{
    char patente[MAX_TAM_PATENTE];
    byte nroCuota;
    char titular[MAX_TAM_TITULAR];
    unsigned dni,
             vto;
    double importe;
} tImpuesto;

typedef int (*CompararImp)(const void *, const void *);

int procesarArchivoImpVencidos(const char *src_path, const char *op, const char *res_path);
int recuperarRegValido(tImpuesto *imp);
int acumularDeuda(void **info, unsigned *tamInfo, const void *dato, unsigned tamDato);
int generarInforme(tArbolBinBusq *impuestos, const char *res_path);
int compararDNI(const void *dato1, const void *dato2);
int compararDNIyPatente(const void *dato1, const void *dato2);
void mostrarImpuestos(void *info, unsigned tamInfo, void *recursos);

char* buscarCharEnLineaVerificando(char *linea, char *dir, char caracter);
byte validarImporte(double imp);
byte validarVto(unsigned vto);
byte validarDNI(unsigned DNI);
byte validarNroCuota(byte cta);


#endif
