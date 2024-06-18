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

int multiplicarEntero(void *info, void *recurso)
{
    if(!info || !recurso)
        return NO_VAL;

    *((int *) info) *= *((int *) recurso);

    return TODO_OK;
}

void mostrarEntero(const void *info, FILE *pf)
{
    if(!info || !pf)
        return;

    fprintf(pf, "%d\n", *((int *) info));
}

int compararEntero(const void *nro1, const void *nro2)
{
    if(!nro1)
        return -1;

    if(!nro2)
        return 1;

    return *((int *) nro1) - *((int *) nro2);
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

//int main()
//{
//    tPilaCirc pilaCirc;
//    tColaCirc colaCirc;
//    int vec[] = {1, 2, 3, 4, 5, 6};
//    byte i;
//
//    crearPilaCirc(&pilaCirc);
//    crearColaCirc(&colaCirc);
//
//    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
//        ponerEnPilaCirc(&pilaCirc, vec + i, sizeof(int));
//
//    sacarNyMostrarPila(&pilaCirc, sizeof(vec) / sizeof(*vec), stdout);
//    puts("Verificando si queda algo");
//    sacarNyMostrarPila(&pilaCirc, sizeof(vec) / sizeof(*vec), stdout);
//
//    puts("_________________________________________");
//
//    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
//        ponerEnColaCirc(&colaCirc, vec + i, sizeof(int));
//
//    sacarNyMostrarCola(&colaCirc, sizeof(vec) / sizeof(*vec), stdout);
//    puts("Verificando si queda algo");
//    sacarNyMostrarCola(&colaCirc, sizeof(vec) / sizeof(*vec), stdout);
//
//    vaciarColaCirc(&colaCirc);
//    vaciarPilaCirc(&pilaCirc);
//
//    return 0;
//}


//int main()
//{
//    tListaDoble listaDoble;
//
//    int vec[] = {25, 1, 2, 3, 4, 5, 6, 6, 7, 8, 7, 84, -1, 11, 88},
//        filtrar = 6;
//    byte i;
//
//    crearListaDoble(&listaDoble);
//
//    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
//        insertarAlFinalListaDoble(&listaDoble, vec + i, sizeof(int));
//
//    puts("Derecha a izquierda");
//    mostrarDerAIzq(&listaDoble, mostrarEntero, stdout);
//    puts("_________________________________");
//    puts("Izquierda a derecha");
//    mostrarIzqADer(&listaDoble, mostrarEntero, stdout);
//    puts("_________________________________");
//    printf("Cantidad de elementos que tenia la lista: %d\n", vaciarListaDoble(&listaDoble));
//
//    puts("Viendo si queda algo");
//    mostrarDerAIzq(&listaDoble, mostrarEntero, stdout);
//
//    puts("_________________________________");
//
//    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
//        insertarAlFinalListaDoble(&listaDoble, vec + i, sizeof(int));
//
//    puts("Pruebas filter\n======= ======");
//    puts("Detalles de la coleccion:");
//    mostrarIzqADer(&listaDoble, mostrarEntero, stdout);
//
//    printf("\nSe busca filtrar el %d\n", filtrar);
//    printf("Cantidad de elementos hallados: %d\n", filterListaDoble(&listaDoble, &filtrar, compararEntero));
//    puts("Lista despues del filter: ");
//    mostrarIzqADer(&listaDoble, mostrarEntero, stdout);
//    filtrar = 3;
//    printf("\nAhora se busca filtrar el %d\n", filtrar);
//    printf("Cantidad de elementos hallados %d\n", filterListaDoble(&listaDoble, &filtrar, compararEntero));
//    puts("Lista despues del filter: ");
//    mostrarIzqADer(&listaDoble, mostrarEntero, stdout);
//    filtrar = 55;
//    printf("\nFiltrando un nro. que no existe en la coleccion, por ejemplo el %d\n", filtrar);
//    printf("Cantidad de elementos hallados %d\n", filterListaDoble(&listaDoble, &filtrar, compararEntero));
//    puts("Lista despues del filter: ");
//    mostrarIzqADer(&listaDoble, mostrarEntero, stdout);
//    puts("_________________________________");
//
//    puts("Probando ordenar la lista");
//    ordenarListaDoble(&listaDoble, compararEntero);
//    puts("Finalmente, la lista ordenada queda:");
//    mostrarIzqADer(&listaDoble, mostrarEntero, stdout);
//    vaciarListaDoble(&listaDoble);
//    puts("_________________________________");
//    puts("Insercion de 0 en orden (sin duplicados)");
//    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
//        insertarEnOrdenListaDoble(&listaDoble, vec + i, sizeof(int), compararEntero, NULL);
//    mostrarIzqADer(&listaDoble, mostrarEntero, stdout);
//    puts("_________________________________");
//    puts("Eliminar primero");
//    eliminarPrimeroListaDoble(&listaDoble);
//    mostrarIzqADer(&listaDoble, mostrarEntero, stdout);
//    puts("_________________________________");
//    puts("Eliminar ultimo");
//    eliminarUltimoListaDoble(&listaDoble);
//    mostrarIzqADer(&listaDoble, mostrarEntero, stdout);
//    puts("_________________________________");
//    filtrar = 25;
//    printf("Eliminar por clave, se busca el nro: %d\n", filtrar);
//    eliminarPorClaveListaDoble(&listaDoble, &filtrar, sizeof(filtrar), compararEntero);
//    mostrarIzqADer(&listaDoble, mostrarEntero, stdout);
//    puts("_________________________________");
//    puts("Mapeo multiplicando por 2 los nros. que quedan");
//    filtrar = 2;
//    mapListaDoble(&listaDoble, &filtrar, multiplicarEntero);
//    mostrarIzqADer(&listaDoble, mostrarEntero, stdout);
//    puts("_________________________________");
//    insertarAlComienzoListaDoble(&listaDoble, &listaDoble, sizeof(filtrar));
//
//    vaciarYmostrarIzqADer(&listaDoble, mostrarEntero, stdout);
//
//    puts("[Ultima prueba insertar al inicio y vaciar mostrando]");
//
//    if(vaciarListaDoble(&listaDoble))
//        puts("Si se ejecuta esta linea, algo falla con la anterior primitiva...");
//
//    return 0;
//}


int main()
{


    return 0;
}
