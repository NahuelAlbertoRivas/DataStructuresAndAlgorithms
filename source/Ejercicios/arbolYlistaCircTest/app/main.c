#include "imports.h"

#define PATH_ARBOL_ORDENADO "../logs/arbolOrdenado.dat"
#define MAX_TAM_COD 7
#define MAYOR_DEF 1
#define MENOR_DEF -1

typedef struct
{
    void *vec;
    unsigned offset;
} tGuardadoEnVec;

typedef struct
{
    char codProd[MAX_TAM_COD];
    float precio;
} tProducto;

int compararEnteros(const void *nro1, const void *nro2)
{
    if(!nro1)
        return -1;
    if(!nro2)
        return 1;

    return *((int *) nro1) - *((int *) nro2);
}

void mostrarEntero(void *info, unsigned tamInfo, unsigned n, void *recurso)
{
    if(!info)
        return;

    printf("valor: %d, nivel = %d\n", *((int *)info), n);
}

void mostrarEnteroSimple(const void *info, FILE *recurso)
{
    if(!info || !recurso)
        return;

    printf("valor: %d\n", *((int *)info));
}

void grabarEnArchivoBin(void *info, unsigned tamInfo, unsigned n, void *pf)
{
    if(!info || !pf)
        return;

    fwrite(info, tamInfo, 1, (FILE *) pf);
}

void guardarEnVec(void *info, unsigned tamInfo, unsigned n, void *recurso)
{
    tGuardadoEnVec *reg;

    if(!info || !recurso)
        return;

    reg = (tGuardadoEnVec *) recurso;

    *(((int *)reg->vec) + reg->offset) = *((int *) info);
    reg->offset++;
}

//int main()
//{
//    tArbolBinBusq arbol;
//    FILE *pfArbolOrdenado = fopen(PATH_ARBOL_ORDENADO, "w+");
//    byte i;
//    tGuardadoEnVec regGuardadoEnVec;
//    int vec[] = {100, 75, 50, 60, 80, 175, 130, 150, 200};
//
//    if(!pfArbolOrdenado)
//        return 0;
//
//    crearArbol(&arbol);
//
//    puts("Probamos cargar desde \"datos ordenados\" con el vector tal cual esta\nVemos el resultado en pre orden");
//    cargarVectorEnArbol(&arbol, sizeof(*vec), sizeof(vec) / sizeof(*vec), vec);
//    recorrerEnPreOrdenArbol(&arbol, NULL, mostrarEntero);
//    puts("Igualmente no era lo que se esperaba...\nSi queremos ver el resultado en orden nos damos cuenta por que");
//    recorrerEnOrdenArbol(&arbol, NULL, mostrarEntero);
//    puts("Borramos todo");
//    vaciarArbol(&arbol);
//    puts("____________________________________");
//    puts("Probamos insertar mediante la primitiva mas basica para hacerlo (de a uno), nuevamente con el vector tal cual esta");
//    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
//        insertarEnArbol(&arbol, vec + i, sizeof(*vec), compararEnteros, NULL);
//    puts("Vemos resultados en pre orden");
//    recorrerEnPreOrdenArbol(&arbol, NULL, mostrarEntero);
//    puts("Y de paso en orden");
//    recorrerEnOrdenArbol(&arbol, NULL, mostrarEntero);
//    puts("Se ve claramente por que el primero estaba mal...");
//    puts("____________________________________");
//    puts("Carga de vector ordenado\n===== == ====== ========");
//    puts("Vector antes:");
//    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
//        printf("%d\n", *(vec + i));
//    puts("Vector despues de cargarlo desde el arbol con recorrido en orden:");
//    regGuardadoEnVec.offset = 0;
//    regGuardadoEnVec.vec = vec;
//    recorrerEnOrdenArbol(&arbol, &regGuardadoEnVec, guardarEnVec);
//    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
//        printf("%d\n", *(vec + i));
//    puts("____________________________________");
//    printf("Vaciado contando nodos borrados\nCantidad de elementos que tenia el arbol: %d\n", vaciarArbol2(&arbol));
//    puts("____________________________________");
//    puts("Ahora que el vector esta ordenado, probemos una carga ineficiente\nArbol resultante visto desde pre orden:");
//    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
//        insertarEnArbol(&arbol, vec + i, sizeof(*vec), compararEnteros, NULL);
//    recorrerEnPreOrdenArbol(&arbol, NULL, mostrarEntero);
//    puts("Guardemos el arbol asi como esta (\"ordenado\" pero no llega ni a AVL) en un archivo para recuperarlo balanceado como estaba antes");
//    recorrerEnOrdenArbol(&arbol, pfArbolOrdenado, grabarEnArchivoBin);
//    vaciarArbol(&arbol);
//    puts("____________________________________");
//    puts("Ahora recuperamos el arbol desde el archivo ordenado\nArbol resultante visto desde pre orden:");
//    cargarArchivoBinEnArbol(&arbol, sizeof(*vec), pfArbolOrdenado);
//    recorrerEnPreOrdenArbol(&arbol, NULL, mostrarEntero);
//    puts("____________________________________");
//    printf("Vaciado contando nodos borrados\nCantidad de elementos que tenia el arbol: %d\n", vaciarArbol2(&arbol));
//
//    vaciarArbol(&arbol);
//    fclose(pfArbolOrdenado);
//
//    return 0;
//}

int compararCodProd(const void *prod1, const void *prod2)
{
    tProducto *reg1,
              *reg2;

    if(!prod1)
        return MENOR_DEF;
    if(!prod2)
        return MAYOR_DEF;

    reg1 = (tProducto *) prod1;
    reg2 = (tProducto *) prod2;

    return strcmpi(reg1->codProd, reg2->codProd);
}

void mostrarProducto(void *info, unsigned tamInfo, unsigned n, void *pf)
{
    tProducto *reg;

    if(!info || !pf)
        return;

    reg = (tProducto *) info;

    fprintf((FILE *)pf, "Cod. prod.: %s, precio %.2f, nivel: %d\n", reg->codProd, reg->precio, n);
}

void mostrarProductoSimple(const void *info, void *pf)
{
    tProducto *reg;

    if(!info || !pf)
        return;

    reg = (tProducto *) info;

    fprintf((FILE *)pf, "Cod. prod.: %s, precio %.2f\n", reg->codProd, reg->precio);
}

int compararPrecioProductos(const void *prod1, const void *prod2)
{
    tProducto *reg1,
              *reg2;

    if(!prod1)
        return MENOR_DEF;
    if(!prod2)
        return MAYOR_DEF;

    reg1 = (tProducto *) prod1;
    reg2 = (tProducto *) prod2;

    return reg1->precio - reg2->precio;
}

//int main()
//{
//    tArbolBinBusq arbol;
//    byte i;
//    tProducto vec[] = {
//        {"df788", 324.21},
//        {"h67OL", 42321.02},
//        {"545Jj", 2133},
//        {"fdfe4", 64123.99},
//        {"5yG32", 5434},
//        {"re43", 43324},
//        {"fgty", 4234},
//        {"g564", 5322},
//        {"KJ34", 634}
//    },
//            buscado;
//
//    crearArbol(&arbol);
//
//    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
//        insertarEnArbol(&arbol, vec + i, sizeof(*vec), compararCodProd, NULL);
//
//    puts("Mostrar arbol en pre orden");
//    recorrerEnPreOrdenArbol(&arbol, stdout, mostrarProducto);
//    puts("________________________________________________________________________");
//    puts("Buscamos el producto de menor clave\nResultado\n=========");
//    mostrarProductoSimple(buscarMenorClaveArbol(&arbol, &buscado, sizeof(tProducto)), stdout);
//    puts("________________________________________________________________________");
//    puts("Buscamos el producto de mayor clave\nResultado\n=========");
//    mostrarProductoSimple(buscarMayorClaveArbol(&arbol, &buscado, sizeof(tProducto)), stdout);
//    puts("________________________________________________________________________");
//    puts("Buscamos el producto de mayor precio\nResultado\n=========");
//    mostrarProductoSimple(buscarMayorNoClave(&arbol, &buscado, sizeof(tProducto), compararPrecioProductos), stdout);
//    puts("________________________________________________________________________");
//    puts("Buscamos el producto de menor precio\nResultado\n=========");
//    mostrarProductoSimple(buscarMenorNoClaveArbol(&arbol, &buscado, sizeof(tProducto), compararPrecioProductos), stdout);
//    puts("________________________________________________________________________");
//    printf("Altura del arbol: %d\n", alturaArbolBinBusq(&arbol));
//    puts("________________________________________________________________________");
//    printf("Buscamos el producto de clave: %s\n", strcpy(buscado.codProd, "h67OL"));
//    printf("Estado\n======\n -> %s <-\n", (buscarElemClaveArbol(&arbol, &buscado, sizeof(tProducto), compararCodProd))?
//                                            "Encontrado correctamente"
//                                          : "No existe");
//    printf("____________________\nAhora buscamos el producto de clave: %s\n", strcpy(buscado.codProd, "KE"));
//    printf("Estado\n======\n -> %s <-\n", (buscarElemClaveArbol(&arbol, &buscado, sizeof(tProducto), compararCodProd))?
//                                            "Encontrado correctamente"
//                                          : "No existe");
//    puts("________________________________________________________________________");
//    printf("Cantidad de elementos que tenia el arbol: %d\n\n", vaciarArbol2(&arbol));
//    if(buscarMenorNoClaveArbol(&arbol, &buscado, sizeof(tProducto), compararPrecioProductos))
//        puts("Esto no deberia mostrarse");
//    if(buscarMayorNoClave(&arbol, &buscado, sizeof(tProducto), compararPrecioProductos))
//        puts("Esto tampoco");
//    if(buscarMenorClaveArbol(&arbol, &buscado, sizeof(tProducto)))
//        puts("Tampoco");
//    if(buscarMayorClaveArbol(&arbol, &buscado, sizeof(tProducto)))
//        puts("Tamo bien (excepto si se muestra esto)");
//
//    vaciarArbol(&arbol);
//
//    return 0;
//}

void multiplicarEntero(void *info, void *multiplicador)
{
    if(!info || !multiplicador)
        return;

    *((int *) info) *= *((int *) multiplicador);
}

int main()
{
    tListaCircular lista;
    byte i,
         cant;
    int vec[] = {100, 75, 50, 60, 80, 175, 130, 150, 200},
        mult;

    crearLSC(&lista);

    puts("");
    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
        insertarLSC(&lista, vec + i, sizeof(*vec));
    puts("Mostramos la lista");
    mostrarLSC(&lista, stdout, mostrarEnteroSimple);
    puts("____________________________________");
    puts("Multiply all items by list size");
    mult = sizeof(vec) / sizeof(*vec);
    mapLSC(&lista, &mult, multiplicarEntero);
    puts("List after map:");
    mostrarLSC(&lista, stdout, mostrarEnteroSimple);
    puts("____________________________________");
    puts("Borramos todo con eliminarSiguiente (despues insertamos de nuevo para probar +)");
    cant = 0;
    while(eliminarSiguienteLSC(&lista, NULL, 0) != LISTA_VACIA)
        cant++;
    printf("Cantidad de elementos que se borraron: %d\n", cant);
    for(i = 0; i < (sizeof(vec) / sizeof(*vec)); i++)
        if((i % 2) == 0)
            insertarLSC(&lista, vec + i, sizeof(*vec));
    puts("____________________________________");
    puts("Ultima, borremos la siguiente lista con vaciarLSC");
    mostrarLSC(&lista, stdout, mostrarEnteroSimple);
    printf("Cantidad de elementos que se borraron: %d\n", vaciarLSC2(&lista));
    if(vaciarLSC2(&lista))
        puts("Some memory leaks were detected...");
    puts("____________________________________");

    vaciarLSC(&lista);

    return 0;
}
