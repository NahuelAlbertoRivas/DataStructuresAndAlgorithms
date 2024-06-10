#ifndef IMPUESTOSVENCIDOS
#define IMPUESTOSVENCIDOS

#include "../../arbolBinBusq/arbol.h"
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
typedef void (*MostrarImp)(void *, unsigned, void *);

int procesarArchivoImpVencidos(const char *src_path, const char *op, const char *res_path);
void definirFuncionesPorClave(const char *op, CompararImp *cmp, MostrarImp *mst);
int recuperarRegValido(tImpuesto *imp);
int acumularDeuda(void **info, unsigned *tamInfo, const void *dato, unsigned tamDato);

int compararDNI(const void *dato1, const void *dato2);
int compararDNIyPatente(const void *dato1, const void *dato2);
void mostrarImpuestosDNI(void *info, unsigned tamInfo, void *recursos);
void mostrarImpuestosDNIyPatente(void *info, unsigned tamInfo, void *recursos);

char* buscarCharEnLineaVerificando(char *linea, char *dir, char caracter);
byte validarImporte(double imp);
byte validarVto(unsigned vto);
byte validarDNI(unsigned DNI);
byte validarNroCuota(byte cta);

void acumularTotal(void *info, unsigned tamInfo, void *recurso);

void generarInforme(tArbolBinBusq *impuestos, const char *res_path, MostrarImp mst);

#endif
