#ifndef STRVALIDATORS
#define STRVALIDATORS

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

#ifndef TODO_OK
#define TODO_OK 200
#endif // TODO_OK

#ifndef WRONG_LOG_PROVIDED
#define WRONG_LOG_PROVIDED 40
#endif // WRONG_LOG_PROVIDED

#ifndef SIN_INFORMACION
#define SIN_INFORMACION 5
#endif // SIN_INFORMACION

#ifndef EMPTY_OR_NULL_FIELD
#define EMPTY_OR_NULL_FIELD 13
#endif // EMPTY_OR_NULL_FIELD

#ifndef EQUALS
#define EQUALS 17
#endif // EQUALS

#ifndef NOT_EQUALS
#define NOT_EQUALS 20
#endif // NOT_EQUALS

#ifndef ES_MAYUSC
#define ES_MAYUSC(x) ((x) >= 65 && (x) <= 90)
#endif // ES_MAYUSC

#ifndef A_MAYUSC
#define A_MAYUSC(x) (x) - 32
#endif // A_MAYUSC

#define A_MINUSC(x) ( (x) + 32 )

#ifndef ES_NUMERO
#define ES_NUMERO(x) ((x) >= 48 && (x) <= 57)
#endif // ES_NUMERO

#ifndef ES_LETRA
#define ES_LETRA(x) (((x) >= 65 && (x) <= 90) || ((x) >= 97 && (x) <= 122) || ( ((x) >= 129) && ((x) <= 165) ) || ( ((x) >= 192) && ((x) <= 253) ))
#endif // ES_LETRA

#ifndef ES_CARACTER_ESPECIAL
#define ES_CARACTER_ESPECIAL(x) (((x) >= 128 && (x) <= 237) || ((x) <= -3  && (x) >= -64))
#endif // ES_CARACTER_ESPECIAL

#ifndef ES_MINUSCULA
#define ES_MINUSCULA(x) ((x) >= 97 && (x) <= 122)
#endif // ES_MINUSCULA

#ifndef GET_NAME
#define GET_NAME(var) #var
#endif // GET_NAME

#ifndef DETECTA_STR_VACIO_O_NULO
#define DETECTA_STR_VACIO_O_NULO(x) ((strcmp(x, "") == 0 || !(*x))?EMPTY_OR_NULL_FIELD:TODO_OK)
#endif // DETECTA_STR_VACIO_O_NULO

#define TAB_CHAR 9

#define SPACE_CHAR 32

void cambiarStringAUpperCase(char *linea);

void cambiarStringALowerCase(char *linea);

void cambiarCaracterAUpperCase(char *linea);

int mismaLetra(const void *letra1, const void *letra2);

char *eliminarEspaciosPrePalabra(char *palabra);

char *eliminarEspaciosPosPalabra(char *palabra);

char *eliminarLetrasPrefijo(char *palabra);

void ingresaCaracterEspecial(char *linea, int *pos, int caracter);

int reconocerCaracterEspecialValido(char *caracter);

int reconocerCaracterSeparacion(const char *setSeparadores, unsigned longSet, char caracter);

void formarPalabra(char *buffer, char *source, unsigned longitud);

#endif
