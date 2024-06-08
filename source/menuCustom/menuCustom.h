#ifndef MENUCUSTOM
#define MENUCUSTOM

#include "../strValidators/strValidators.h"
#include "../lista/lista.h"
#include <locale.h>

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif // STDIO

#ifndef STRING
#define STRING
#include <string.h>
#endif // STRING

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif // STDLIB

#ifndef WINSOCK2
#define WINSOCK2
#include <winsock2.h>
#endif // WINSOCK2

#ifndef WINSOCK
#define WINSOCK
#include <winsock.h>
#endif // WINSOCK

#ifndef WINDOWS
#define WINDOWS
#include <windows.h>
#endif // WINDOWS

#ifndef CONIO
#define CONIO
#include <conio.h>
#endif // CONIO

#ifndef MAX_LINEA_MENU
#define MAX_LINEA_MENU 60
#endif // MAX_LINEA_MENU

#ifndef TAM_MIN_OPCIONES
#define TAM_MIN_OPCIONES 3
#endif // TAM_MIN_OPCIONES

#ifndef MINIMO
#define MINIMO(x, y) ((x) < (y))?(x):(y)
#endif // MINIMO

typedef int (*Accion)(void *);

typedef void (*Mostrar)(const void*);

#define BTN_ACEPTAR 13 /// modificables a gusto
#define ARRIBA 80
#define ABAJO 72

#define MIN_OP 1 /// como estándar defino que el menú comience por la opción 1

void indicadorFlecha(int posItem, int posFlecha);

void menu(FILE *pf, char *buffer, void *recurso, Accion *acciones);

#endif
