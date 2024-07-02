#ifndef COMMONDATA
#define COMMONDATA

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

#define SIN_MEM -34
#define ERROR_PARAMS -11
#define TODO_OK 1
#define CLA_DUP 2
#define SIN_CONTENIDO -44
#define SIN_COINCIDENCIAS -21

/// Particular de listas
#define LISTA_VACIA -24

/// Particular de arboles
#define SIN_INICIALIZAR -55

#define MINIMO(x, y)( ( (x) < (y) )? (x) : (y) )

typedef int (*Comparar)(const void *, const void *);

typedef int (*Acumular)(void **, unsigned *, const void *, unsigned);

typedef void (*Mostrar)(const void *, FILE *);

typedef void (*Accionar)(void *, unsigned, unsigned, void *);

typedef void (*AccionarSimple)(void *, void *);

typedef int (*Leer)(void *, unsigned, unsigned, void *);

#endif
