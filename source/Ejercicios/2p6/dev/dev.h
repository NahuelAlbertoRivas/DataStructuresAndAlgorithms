#ifndef DEV
#define DEV

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../pilaDinamica/pila.h"

#define ERR_APERTURA_ARCH -222
#define FIN_PROCESO 551
#define ASC 12122
#define DESC 3453

int procesarArchivo(const char *path, int orden);

#endif
