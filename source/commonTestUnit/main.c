#include "main.h"

#define ES_LETRA(x)( ((x) >= 'A' && (x) <= 'Z') || ((x) >= 'a' && (x) <= 'z'))
#define VAL 1
#define NO_VAL 0

void imprimirProximaPalabra(char *ini, char *fin, FILE *pf)
{
    while(ini <= fin)
    {
        fprintf(pf, "%c", *ini);
        ini++;
    }
}

unsigned short proximaPalabra(char *cadena, char **iniPalabra, char **finPalabra)
{
    unsigned short longitudPalabra = 0; /// cuenta cuántos caracteres tiene la próxima palabra

    if(!(*cadena))
        return longitudPalabra;

    if((*iniPalabra < cadena) || (*iniPalabra > (cadena + strlen(cadena)))) /// esta condición detecta si previamente se ejecutó la fn. sobre la cadena enviada
        *iniPalabra = cadena;
    else
        *iniPalabra = (*finPalabra) + 1; /// si previamente se ejecutó la fn. sobre la cadena enviada, retomamos en la siguiente posición del final de la palabra anterior detectada

    while(**iniPalabra && !ES_LETRA(**iniPalabra)) /// adelantamos el puntero al inicio de la siguiente palabra
        (*iniPalabra)++;

    *finPalabra = *iniPalabra; /// establecemos una referencia para que ' finPalabra ' delimite la secuencia

    while(**finPalabra && ES_LETRA(**finPalabra))
    {
        longitudPalabra++;
        (*finPalabra)++;
    }

    (*finPalabra)--; /// corrijo porque ' finPalabra ' cuando corte es justamente porque el último caracter no es letra (o termino la cadena)

    return longitudPalabra;
}

//int main()
//{
//    char cadena[] = "     Esta es ,,,,, una secuenc    ia  ..__234 cualquie+ra de c a r a c t e res |||1 <a> {reconocer}  ",
//        *ini,
//        *fin;
//    unsigned short cantidad;
//    while(proximaPalabra(cadena, &ini, &fin))
//    {
//        imprimirProximaPalabra(ini, fin, stdout);
//        fprintf(stdout, "%c", 32);
//    }
//    puts("\n");
//    fprintf(stdout, "Otras pruebas\n\n");
//    while((cantidad = proximaPalabra("     Ips *¨¨¨¨$# um M O R___T;i^^^^If ññññññ", &ini, &fin)))
//        printf("%.*s", cantidad, ini);
//    printf("\n\n%25s", "FIN\n\n");
//    return 0;
//}

//int main()
//{
//    char parParentizado[] = "[]",
//         param[] = "[21422][0213]",
//         buffer[100],
//         otro[100];
//    int res = 0,
//        num1,
//        num2,
//        num3;
//    FILE *pf = fopen("sf.txt", "rt");
//
//    if(!pf)
//        return 1;
//
//    fgets(buffer, 100, pf);
//    sscanf(buffer, "[%d][%d] %[^\\0]", &num1, &num2, otro);
//    printf("[%d][%3d] %s", num1, num2, otro);
//    fgets(buffer, 100, pf);
//    sscanf(buffer, "[%d][%d]", &num1, &num3);
//    printf("[%.*d][%.*d]", 3, num1, 3, num3);
//    fclose(pf);
//}

void mostrarEntero(const void *info, FILE *pf)
{
    if(!info || !pf)
        return;

    fprintf(pf, "%d\n", *((int *) info));
}

void sacarNyMostrarPila(tPilaCirc *pp, unsigned ce, FILE *pf)
{
    int buff;
    unsigned i;

    for(i = 0; i < ce; i++)
    {
        if(sacarDePilaCirc(pp, &buff, sizeof(buff)))
            mostrarEntero(&buff, pf);
    }
}

void sacarNyMostrarCola(tColaCirc *pc, unsigned ce, FILE *pf)
{
    int buff;
    unsigned i;

    for(i = 0; i < ce; i++)
    {
        if(sacarDeColaCirc(pc, &buff, sizeof(buff)))
            mostrarEntero(&buff, pf);
    }
}

int main()
{
    tPilaCirc pilaCirc;
    tColaCirc colaCirc;
    int vec[] = {1, 2, 3, 4, 5, 6};
    byte i;

    crearPilaCirc(&pilaCirc);
    crearColaCirc(&colaCirc);

    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
        ponerEnPilaCirc(&pilaCirc, vec + i, sizeof(int));

    sacarNyMostrarPila(&pilaCirc, sizeof(vec) / sizeof(*vec), stdout);
    puts("Verificando si queda algo");
    sacarNyMostrarPila(&pilaCirc, sizeof(vec) / sizeof(*vec), stdout);

    puts("_________________________________________");

    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
        ponerEnColaCirc(&colaCirc, vec + i, sizeof(int));

    sacarNyMostrarCola(&colaCirc, sizeof(vec) / sizeof(*vec), stdout);
    puts("Verificando si queda algo");
    sacarNyMostrarCola(&colaCirc, sizeof(vec) / sizeof(*vec), stdout);

    vaciarColaCirc(&colaCirc);
    vaciarPilaCirc(&pilaCirc);

    return 0;
}
