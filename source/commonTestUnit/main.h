#ifndef MAIN_H
#define MAIN_H

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../pilaCircular/pila.h"
#include "../colaCircular/cola.h"
#include "../listaDoblemente/listaDoblemente.h"

typedef byte (*Sacar)(void *, void *, unsigned);
typedef void (*Mostrar)(const void *, FILE *);

#endif
