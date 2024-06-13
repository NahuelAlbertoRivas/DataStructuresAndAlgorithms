#include "strValidators.h"

#define NO_VAL 0
#define VAL 1

#include <winsock2.h>
#include <windows.h>

void cambiarStringAUpperCase(char *linea){
    if(ES_MINUSCULA(*linea)){
        *linea = A_MAYUSC(*linea);
        return cambiarStringAUpperCase(linea + 1);
    }
    else if(*linea)
        return cambiarStringAUpperCase(linea + 1);
}

void cambiarStringALowerCase(char *linea){
    if(ES_MAYUSC(*linea)){
        *linea = A_MINUSC(*linea);
        return cambiarStringALowerCase(linea + 1);
    }
    else if(*linea)
        return cambiarStringALowerCase(linea + 1);
}

void cambiarCaracterAUpperCase(char *linea){
    if(ES_MINUSCULA(*linea)){
        *linea = A_MAYUSC(*linea);
    }
}

int mismaLetra(const void *letra1, const void *letra2){
    char le1 = *((char *)letra1), le2 = *((char *)letra2);

    cambiarCaracterAUpperCase(&le1);
    cambiarCaracterAUpperCase(&le2);

    return (le1 == le2)?EQUALS:NOT_EQUALS;
}

char *eliminarEspaciosPrePalabra(char *palabra){
    if(*palabra && !ES_LETRA(*palabra) && !ES_CARACTER_ESPECIAL(*palabra)){
        return eliminarEspaciosPrePalabra(palabra + 1);
    }
    return palabra;
}

char *eliminarEspaciosPosPalabra(char *palabra){
    if(*palabra && !ES_LETRA(*palabra) && !ES_CARACTER_ESPECIAL(*palabra)){
        (*palabra) = '\0';
        return eliminarEspaciosPosPalabra(palabra - 1);
    }
    return palabra;
}

char *eliminarLetrasPrefijo(char *palabra){
    if(*palabra && !ES_NUMERO(*palabra)){
        return eliminarLetrasPrefijo(palabra + 1);
    }
    return palabra;
}

void ingresaCaracterEspecial(char *linea, int *pos, int caracter){
    switch(caracter){
        case -63:
            strcat(linea, "Á");
            break;
        case -55:
            strcat(linea, "É");
            break;
        case -51:
            strcat(linea, "Í");
            break;
        case -47:
            strcat(linea, "Ñ");
            break;
        case -45:
            strcat(linea, "Ó");
            break;
        case -42:
            strcat(linea, "Ö");
            break;
        case -38:
            strcat(linea, "Ú");
            break;
        case -36:
            strcat(linea, "Ü");
            break;
        case -31:
            strcat(linea, "á");
            break;
        case -23:
            strcat(linea, "é");
            break;
        case -19:
            strcat(linea, "í");
            break;
        case -17:
            strcat(linea, "ï");
            break;
        case -15:
            strcat(linea, "ñ");
            break;
        case -13:
            strcat(linea, "ó");
            break;
        case -10:
            strcat(linea, "ö");
            break;
        case -6:
            strcat(linea, "ú");
            break;
        case -4:
            strcat(linea, "ü");
            break;
        case 129:
            strcat(linea, "ü");
            break;
        case 130:
            strcat(linea, "é");
            break;
        case 137:
            strcat(linea, "ë");
            break;
        case 144:
            strcat(linea, "É");
            break;
        case 148:
            strcat(linea, "ö");
            break;
        case 153:
            strcat(linea, "Ö");
            break;
        case 154:
            strcat(linea, "Ü");
            break;
        case 160:
            strcat(linea, "á");
            break;
        case 161:
            strcat(linea, "í");
            break;
        case 162:
            strcat(linea, "ó");
            break;
        case 163:
            strcat(linea, "ú");
            break;
        case 164:
            strcat(linea, "ñ");
            break;
        case 165:
            strcat(linea, "Ñ");
            break;
        case 181:
            strcat(linea, "Á");
            break;
        case 214:
            strcat(linea, "Í");
            break;
        case 224:
            strcat(linea, "Ó");
            break;
        case 233:
            strcat(linea, "Ú");
            break;
        default:
            return;
    }
    printf("%c", *(linea + ((*pos)++)));
}

/// la siguiente fn. se da debido a la imposibilidad de detectar el valor ASCII decimal exacto
/// que interpreta cada computadora distinta sobre caracteres especiales (por eso la macro ES_CARACTER_ESPECIAL
/// desarrollada en ' strValidators.h ' no responde bien en la mayoría de casos)
//int reconocerCaracterEspecialValido(char *caracter)
//{
//    int res;
//
//    if((res = strcmpi(caracter, "í")))
//        return VAL;
//
////    switch(caracter){
////        case 'Ü':
////            break;
////        case 'ó':
////            break;
////        case 'ü':
////            break;
////        case 'é':
////            break;
////        case 'É':
////            break;
////        case 'á':
////            break;
////        case 'í':
////            break;
////        case 'ú':
////            break;
////        case 'ñ':
////            break;
////        case 'Ñ':
////            break;
////        case 'Á':
////            break;
////        case 'Í':
////            break;
////        case 'Ó':
////            break;
////        case 'Ú':
////            break;
////        default:
////            return NO_VAL;
////    }
//
//    return VAL;
//}

int reconocerCaracterSeparacion(const char *setSeparadores, unsigned longSet, char caracter)
{
    byte i;

    for(i = 0; i < longSet; i++)
        if(caracter == *(setSeparadores + i))
            return VAL;

    return NO_VAL;
}

void formarPalabra(char *buffer, char *source, unsigned longitud)
{
    unsigned i;

    for(i = 0; i < longitud; i++)
        *(buffer + i) = *(source + i);
    *(buffer + i) = '\0';
}
