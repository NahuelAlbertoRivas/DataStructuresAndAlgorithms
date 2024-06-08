#include "strValidators.h"

void cambiarStringAUpperCase(char *linea){
    if(ES_MINUSCULA(*linea)){
        *linea = A_MAYUSC(*linea);
        return cambiarStringAUpperCase(++linea);
    }
    else if(*linea)
        return cambiarStringAUpperCase(++linea);
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
        return eliminarEspaciosPrePalabra(++palabra);
    }
    return palabra;
}

char *eliminarEspaciosPosPalabra(char *palabra){
    if(*palabra && !ES_LETRA(*palabra) && !ES_CARACTER_ESPECIAL(*palabra)){
        (*palabra) = '\0';
        return eliminarEspaciosPosPalabra(--palabra);
    }
    return palabra;
}

char *eliminarLetrasPrefijo(char *palabra){
    if(*palabra && !ES_NUMERO(*palabra)){
        return eliminarLetrasPrefijo(++palabra);
    }
    return palabra;
}

void ingresaCaracterEspecial(char *linea, int *pos, int caracter){
    switch(caracter){
        case -63:
            strcat(linea, "�");
            break;
        case -55:
            strcat(linea, "�");
            break;
        case -51:
            strcat(linea, "�");
            break;
        case -47:
            strcat(linea, "�");
            break;
        case -45:
            strcat(linea, "�");
            break;
        case -42:
            strcat(linea, "�");
            break;
        case -38:
            strcat(linea, "�");
            break;
        case -36:
            strcat(linea, "�");
            break;
        case -31:
            strcat(linea, "�");
            break;
        case -23:
            strcat(linea, "�");
            break;
        case -19:
            strcat(linea, "�");
            break;
        case -17:
            strcat(linea, "�");
            break;
        case -15:
            strcat(linea, "�");
            break;
        case -13:
            strcat(linea, "�");
            break;
        case -10:
            strcat(linea, "�");
            break;
        case -6:
            strcat(linea, "�");
            break;
        case -4:
            strcat(linea, "�");
            break;
        case 129:
            strcat(linea, "�");
            break;
        case 130:
            strcat(linea, "�");
            break;
        case 137:
            strcat(linea, "�");
            break;
        case 144:
            strcat(linea, "�");
            break;
        case 148:
            strcat(linea, "�");
            break;
        case 153:
            strcat(linea, "�");
            break;
        case 154:
            strcat(linea, "�");
            break;
        case 160:
            strcat(linea, "�");
            break;
        case 161:
            strcat(linea, "�");
            break;
        case 162:
            strcat(linea, "�");
            break;
        case 163:
            strcat(linea, "�");
            break;
        case 164:
            strcat(linea, "�");
            break;
        case 165:
            strcat(linea, "�");
            break;
        case 181:
            strcat(linea, "�");
            break;
        case 214:
            strcat(linea, "�");
            break;
        case 224:
            strcat(linea, "�");
            break;
        case 233:
            strcat(linea, "�");
            break;
        default:
            return;
    }
    printf("%c", *(linea + ((*pos)++)));
}
