#include "menuCustom.h"

void indicadorFlecha(int posItem, int posFlecha){ /// simplemente se da el estilo del seleccionado/espaciado
    if(posItem == posFlecha) { printf(" ---->>   "); }
    else                  { printf("          "); }
}

void menu(FILE *pf, char *linea, void *recurso, Accion *accion){ /// decid� que me pasaran un archivo que tenga en l�neas separadas los nombres de las opciones ya que lo consider� el m�todo m�s seguro en caso de que pretendan vulnerar el programa/sistema (ya que desde un archivo tengo m�s posibilidades de control)
    int posicionFlecha = MIN_OP, /// ' posicionFlecha ' es el �tem se�alado;
        teclaIng = 0,            /// ' teclaIng ' refiere a la tecla que ingresa el user;
        cantOpciones = 1,
        posItemSalir = 0,
        i = 0;
    char *p;
    ///FILE *pf = fopen(nomArch, "rt");
    tLista lista,
          *pl;
    setlocale(LC_CTYPE, "Spanish");

    if(!pf)
        return;

    crearLista(&lista);

    while(fgets(linea, MAX_LINEA_MENU, pf)){ /// mientras lea registros
        if((p = strrchr(linea, '\n'))) /// en caso de que la opci�n tenga menos caracteres que el tama�o m�ximo predefinido, busco el salto de l�nea y termino la cadena correctamente
            *p = '\0';
        else /// si no, mandaron algo muy largo y qued� sin el '\0', corresponde finalizarlo correctamente
            *(p = linea + MAX_LINEA_MENU) = '\0';
        p = eliminarEspaciosPrePalabra((p = linea));
        if(DETECTA_STR_VACIO_O_NULO(linea) != EMPTY_OR_NULL_FIELD){ /// si me mandaron un string vac�o, ni operamos
            if(!(ponerAlFinal(&lista, p, strlen(p) + 1))){ /// trato de insertar, si no, me voy
                vaciarLista(&lista);
                return;
            }
            cantOpciones++;
        }
    }

    posItemSalir = cantOpciones;

    while( teclaIng != BTN_ACEPTAR || ( ((teclaIng == BTN_ACEPTAR) && (posicionFlecha != posItemSalir)) )){ /// se deja la segunda condici�n suponiendo que el usuario va a ofrecer el �ltimo �tem como salida; la �ltima condici�n es para asegurar que manden todas las funciones acorde a las opciones registradas
        system("cls");

        if(teclaIng == BTN_ACEPTAR){
            if(accion)
                if(accion[posicionFlecha - 1])
                    accion[posicionFlecha - 1](recurso);
        }

        pl = &lista;
        for(i = 0; i < cantOpciones; i++){
            indicadorFlecha(i + 1, posicionFlecha); /// se hardcodea ' i + 1 ' en ' _indicadorFlecha() ' a fin de continuar la l�gica (se arranca en la posici�n 1 hasta cantOpciones)
            if(i < cantOpciones - 1){
                verPrimeroLista(pl, linea, MAX_LINEA_MENU);
                pl = &((*pl)->sig);
                printf("%s\n", linea);
            }
            else
                printf("Salir\n");
        }

        teclaIng = getch();
        fflush(stdin);

        if(teclaIng == ARRIBA){
            if(posicionFlecha != cantOpciones) { posicionFlecha++; }
            else{ posicionFlecha = MIN_OP; }
        }
        else if(teclaIng == ABAJO){
            if(posicionFlecha != MIN_OP) { posicionFlecha--; }
            else{ posicionFlecha = cantOpciones; }
        }
    }
    vaciarLista(&lista);
    system("cls");
    printf("Saliendo...\n\n");
    Sleep(3);
    system("cls");
}
