#ifndef DEV
#define DEV

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#include "../../../arbolBinBusq/arbol.h"
#include "../../../strValidators/strValidators.h"

#define ERROR_CREAR_ARCHIVO -2132
#define ERROR_ABRIR_ARCHIVO -5232
#define MAX_TAM_PALABRA 34

typedef struct
{
    char palabra[MAX_TAM_PALABRA];
    unsigned cantRep;
} tRegistroPalabra;

int liberarBufferPalabra(void *reg, void *rec);

void mostrarRegs(void *reg, unsigned tamInfo, void *recurso);

void menu(int mayorCnt, int menorCnt, tArbolBinBusq *pa);

void mostrarSiCumple(void *reg, unsigned tamInfo, void *recurso);

int procesarLibro(char *path, tArbolBinBusq *pa);

int proximaPalabra(char *linea, char **ini, char **fin);

void buscarMayor(void *reg, unsigned tamInfo, void *recurso);

void buscarMenor(void *reg, unsigned tamInfo, void *recurso);

int compararRegsPalabra(const void *reg1, const void *reg2);

int crearArchivoTexto(char *path);

FILE *abrirArchivoTexto(char *path);

int acumularCantRepeticiones(void **reg, unsigned *tamReg, const void *info, unsigned tamInfo);

#endif
