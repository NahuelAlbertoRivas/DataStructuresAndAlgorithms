#define BTN_ACEPTAR 13
#define ARRIBA 80
#define ABAJO 72

#define OP1 " Op1\n"
#define OP2 " Op2\n"
#define OP3 " Op3\n"
#define OP4 " Finalizar\n"

#define PRI_ITEM 1
#define SEG_ITEM 2
#define TER_ITEM 3
#define CUA_ITEM 4

#define MAX_OP 4
#define MIN_OP 1

void _indicadorFlecha(int posItem, int posFlecha){
    if(posItem == posFlecha) { printf(" ---->>   "); } /// simplemente se da el estilo del seleccionado/espaciado
    else                  { printf("          "); }
}

void _menu(){
    int posicionFlecha = 1, teclaIng = 0; /// ' posicionFlecha ' es el ítem señalado;  ' teclaIng ' refiere a la tecla que ingresa el user;
                                          /// obs: se hardcodea para inicializar y dar formato al listado

    while(teclaIng != BTN_ACEPTAR || ((teclaIng == BTN_ACEPTAR) && (posicionFlecha != CUA_ITEM))){
        system("cls");

        if(teclaIng == BTN_ACEPTAR) { _accion(posicionFlecha); }

        _indicadorFlecha(PRI_ITEM, posicionFlecha); printf(OP1);
        _indicadorFlecha(SEG_ITEM, posicionFlecha); printf(OP2);
        _indicadorFlecha(TER_ITEM, posicionFlecha); printf(OP3);
        _indicadorFlecha(CUA_ITEM, posicionFlecha); printf(OP4);

        teclaIng = getch();
        fflush(stdin);

        if(teclaIng == ARRIBA){
            if(posicionFlecha != MAX_OP) { posicionFlecha++; }
            else{ posicionFlecha = PRI_ITEM; }
        }
        else if(teclaIng == ABAJO){
            if(posicionFlecha != MIN_OP) { posicionFlecha--; }
            else{ posicionFlecha = CUA_ITEM; }
        }
    }
    system("cls");
    printf("Saliendo...\n\n");
}
