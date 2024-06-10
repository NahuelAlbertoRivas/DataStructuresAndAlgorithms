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
    short unsigned habitantes;
} tLocalidad;

#endif
