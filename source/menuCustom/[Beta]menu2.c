#define BTN_ACEPTAR 13 /// modificables a gusto
#define ARRIBA 80
#define ABAJO 72

#define TIPO_TDA tLista /// por ej.

#define MIN_OP 1 /// como estándar defino que el menú comience por la opción 1

typedef int (* Comparar) (const void *, const void*);
typedef int (* Acumular) (void **, unsigned *, const void *, unsigned);

int _accion(TIPO_TDA *tda, Comparar cmp, Acumular acm, char *nomArch){
    /// a desarrollar...
}

void _indicadorFlecha(int posItem, int posFlecha){ /// simplemente se da el estilo del seleccionado/espaciado
    if(posItem == posFlecha) { printf(" ---->>   "); }
    else                  { printf("          "); }
}

void _menu(char **nomOpciones, unsigned cantOpciones, TIPO_TDA *tda, Comparar cmp, Acumular acm, char *nomArch){
    int posicionFlecha = 1, teclaIng = 0 , i; /// ' posicion ' es el ítem señalado;  ' op ' refiere a la tecla que ingresa el user;
                                                 /// obs: se hardcodea para inicializar y dar formato al listado

    while(teclaIng != BTN_ACEPTAR || ((teclaIng == BTN_ACEPTAR) && (posicionFlecha != cantOpciones))){ /// se deja la segunda condición suponiendo que el usuario va a ofrecer el último ítem como salida
        system("cls");

        if(teclaIng == BTN_ACEPTAR) { _accion(tda, cmp, acm, nomArch); }

        i = 0;
        while(i < cantOpciones){
            _indicadorFlecha(i + 1, posicionFlecha); printf("%s\n", nomOpciones[i]); /// se hardcodea ' i + 1 ' en ' _indicadorFlecha() ' a fin de continuar la lógica (se arranca en la posición 1 hasta cantOpciones)
            i++;
        }

        teclaIng = getch();
        fflush(stdin);

        if(teclaIng == ARRIBA){
            if(posicionFlecha != MAX_OP) { posicionFlecha++; }
            else{ posicionFlecha = PRI_ITEM; }
        }
        else if(teclaIng == ABAJO){
            if(posicionFlecha != MIN_OP) { posicionFlecha--; }
            else{ posicionFlecha = cantOpciones; }
        }
    }
    system("cls");
    printf("Saliendo...\n\n");
}
