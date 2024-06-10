#ifndef LOCMAYORSUP
#define LOCMAYORSUP

#include "../../lista/lista.h"
#include <winsock2.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>

#define MAX_TAM_LOCALIDAD 51

typedef struct
{
    byte provincia;
    char localidad[MAX_TAM_LOCALIDAD];
    float superficie; /// podría tratarse como un DECIMAL en sql
    short unsigned poblacion;
} tLocalidad;

int procesarArchivoLote(const char *src_path, const char *res_path);
byte recuperarRegLocVal(tLocalidad *loc);
int generarInformeLocalidades(tLista *localidades, const char *path);
void mostrarLocalidad(const void *info, FILE *pf);
int cmpLocalidades(const void *info1, const void *info2);

byte validarProv(byte nro);
byte validarSuperficie(float sup);
byte validarPoblacion(short unsigned poblacion);
int quedarseConRegMayor(void **info, unsigned *tamInfo, const void *dato, unsigned tamDato);

#endif
