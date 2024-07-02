#include "imports.h"

#define ABS(x)( ((x) < 0)? -(x) : (x) )

/// /////////////////////////////////////////////////////////
#define PATH_LOTE "../files/datos.dat"
#define PATH_IDX "../files/indEmps.idx"

#define MAX_TAM_DNI 11
#define MAX_TAM_NyA 31

typedef struct
{
    char DNI[MAX_TAM_DNI], /// clave
         NyA[MAX_TAM_NyA];
    double sueldo;
} tEmp;

typedef struct
{
    char DNI[MAX_TAM_DNI];
    unsigned pos;
} tIndice;

int compararDNI(const void *info1, const void *info2)
{
    tIndice *reg1,
            *reg2;

    if(!info1)
        return -1;
    if(!info2)
        return 1;

    reg1 = (tIndice *) info1;
    reg2 = (tIndice *) info2;

    return strcmpi(reg1->DNI, reg2->DNI);
}

void crearLote()
{
    FILE *pf = fopen(PATH_LOTE, "wb");
    tEmp emps[] = {
        {"124", "Maserati", 74678},
        {"12323", "Pontiac", 4546},
        {"54533", "Luis Vuitton", 63453},
        {"5632", "Prada", 352654},
        {"65431", "Gucci", 65434},
        {"54352", "Dolce & Gabanna", 463465},
        {"576454", "Hennessy", 35343},
        {"4324", "Audi", 533564},
        {"8134", "Mc Laren", 743654},
        {"4353", "Giuseppe Zanoti", 353634},
        {"8765", "Ferragamo", 5354},
        {"95632", "Calvin Klein", 3554634},
        {"32453", "Burj Khalifa", 754323},
        {"8564", "Gumpert", 35456},
        {"43563", "Terralagos", 6463},
        {"7645", "Nordelta", 53453},
        {"13234", "Miami", 24543},
        {"07567", "Dubai", 4535},
        {"75239", "Galapagos", 46346},
        {"00065", "Ferrari", 73665},
        {"235432", "Lambo", 54356},
        {"6534645", "Bugatti", 53535},
        {"564354", "Porsche", 32434},
        {"786000", "BMW", 3535},
        {"3459000", "Mercedes Benz", 5345435},
        {"2423999", "Pagani", 654634},
        {"99655", "Rolls Royce", 54345}
    };
    byte i;

    if(!pf)
        return;

    for(i = 0; i < (sizeof(emps) / sizeof(tEmp)); i++)
        fwrite(emps + i, sizeof(tEmp), 1, pf);

    fclose(pf);
}

void crearIndice(tArbolBinBusq *pa, const char *path_emps)
{
    FILE *pfEmps = fopen(path_emps, "rb");
    unsigned i = 0;
    tEmp emp;
    tIndice ind;

    if(!pfEmps)
        return;

    while(fread(&emp, sizeof(tEmp), 1, pfEmps))
    {
        strcpy(ind.DNI, emp.DNI);
        ind.pos = i;
        insertarEnArbolBin(pa, &ind, sizeof(tIndice), compararDNI, NULL);
        i++;
    }

    fclose(pfEmps);
}

void mostrarIndice(void *info, unsigned tamInfo, void *pf)
{
    tIndice *ind;

    if(!info || !pf)
        return;

    ind = (tIndice *) info;

    fprintf((FILE *) pf, "%s, %d\n", ind->DNI, ind->pos);
}

void mostrarIndiceDetallado(void *info, unsigned tamInfo, unsigned n, void *pf)
{
    tIndice *ind;

    if(!info || !pf)
        return;

    ind = (tIndice *) info;

    fprintf((FILE *) pf, "DNI (clave): %s, pos. en archivo principal: %d, nivel en arbol: %d\n", ind->DNI, ind->pos, n);
}

void subirDiezPerCent(void *info, unsigned tamInfo, void *recurso)
{
    tIndice *ind;
    tEmp emp;
    FILE *pf;

    if(!info || !recurso)
        return;

    ind = (tIndice *) info;
    pf = (FILE *) recurso;

    fseek(pf, ind->pos * sizeof(tEmp), SEEK_SET);
    fread(&emp, sizeof(tEmp), 1, pf);

    fflush(pf);

    printf("[DNI]: %s, [Nombre comp.]: %s", emp.DNI, emp.NyA);
    puts("\nAntes\n=====");
    printf("%.2lf\n", emp.sueldo);

    emp.sueldo *= 1.1;

    puts("\nDespues\n=======");
    printf("%.2lf\n\n", emp.sueldo);

    fseek(pf, ind->pos * sizeof(tEmp), SEEK_SET);

    fwrite(&emp, sizeof(tEmp), 1, pf);
}

void bajarDiezPerCent(void *info, unsigned tamInfo, void *recurso)
{
    tIndice *ind;
    tEmp emp;
    FILE *pf;

    if(!info || !recurso)
        return;

    ind = (tIndice *) info;
    pf = (FILE *) recurso;

    fseek(pf, ind->pos * sizeof(tEmp), SEEK_SET);
    fread(&emp, sizeof(tEmp), 1, pf);

    fflush(pf);

    printf("[DNI]: %s, [Nombre comp.]: %s", emp.DNI, emp.NyA);
    puts("\nAntes\n=====");
    printf("%.2lf\n", emp.sueldo);

    emp.sueldo *= 0.9;

    puts("\nDespues\n=======");
    printf("%.2lf\n\n", emp.sueldo);

    fseek(pf, ind->pos * sizeof(tEmp), SEEK_SET);

    fwrite(&emp, sizeof(tEmp), 1, pf);
}

void mostrarRegEmp(void *info, unsigned tamInfo, void *recurso)
{
    tIndice *reg;
    tEmp emp;
    FILE *pf;

    if(!info || !recurso)
        return;

    pf = (FILE *) recurso;
    reg = (tIndice *) info;

    fseek(pf, reg->pos * sizeof(tEmp), SEEK_SET);
    fread(&emp, sizeof(tEmp), 1, pf);

    fflush(pf);

    printf("[DNI]: %s\n\t[Nombre completo]: %s,\n\t[Sueldo]: %.2lf,\n\t[Pos. en arch. principal]: %d\n\n", emp.DNI, emp.NyA, emp.sueldo, reg->pos);
}

int compararEnt(const void *info1, const void *info2)
{
    if(!info1)
        return -1;
    if(!info2)
        return 1;

    return *((int *)info1) - *((int *)info2);
}

void mostrarEnt(void *info, unsigned tamInfo, unsigned n, void *rec)
{
    if(!info)
        return;

    printf("[Valor del nro.]: %d, [Nivel]: %d\n", *((int *)info), n);
}

int main()
{
    FILE *pfIdx,
         *pfEmps;
    tArbolBinBusq indiceEmpleados,
                  arbolNoAVL;
    byte i;
    char buff[100];

    crearLote();

    crearArbol(&arbolNoAVL);
    crearArbol(&indiceEmpleados);
    crearIndice(&indiceEmpleados, PATH_LOTE);
    pfIdx = fopen(PATH_IDX, "wb");
    if(!pfIdx)
        return 0;
    guardarArbolEnOrdenAchivoBin(&indiceEmpleados, pfIdx);
    puts("En Orden\n== =====\n");
    recorrerEnOrdenArbolBinBusq(&indiceEmpleados, stdout, mostrarIndiceDetallado);
    puts("\nPre Orden\n=== =====\n");
    recorrerEnPreOrdenArbolBinBusq(&indiceEmpleados, stdout, mostrarIndiceDetallado);
    vaciarArbol(&indiceEmpleados);
    fclose(pfIdx);
    puts("__________________________________________________________________________________________\n\
    Ahora, cargamos desde datos ordenados y nos queda el arbol lo mas balanceado posible\n");
    pfIdx = fopen(PATH_IDX, "rb");
    if(!pfIdx)
        return 0;
    pfEmps = fopen(PATH_LOTE, "r+");
    if(!pfEmps)
    {
        fclose(pfIdx);
        return 0;
    }
    cargarArbolDesdeArchivoBin(&indiceEmpleados, sizeof(tIndice), pfIdx);
    puts("En Orden\n== =====\n");
    recorrerEnOrdenArbolBinBusq(&indiceEmpleados, stdout, mostrarIndiceDetallado);
    puts("\nPre Orden\n=== =====\n");
    recorrerEnPreOrdenArbolBinBusq(&indiceEmpleados, stdout, mostrarIndiceDetallado);
    puts("__________________________________________________________________________________________\n\
    Veamos como esta compuesto originalmente el archivo \"datos.dat\" \n");
    recorrerEnOrdenSimpleArbolBinBusq(&indiceEmpleados, pfEmps, mostrarRegEmp);
    puts("\nLes subimos un diez por ciento a los empleados\n______________________________________________\n");
    recorrerEnOrdenSimpleArbolBinBusq(&indiceEmpleados, pfEmps, subirDiezPerCent);
    puts("__________________________________________________________________________________________\n");
    printf("Altura del arbol: %d\n", alturaArbol(&indiceEmpleados));
    printf("Cantidad de nodos que tiene el arbol: %d\n", contarNodosDelArbol(&indiceEmpleados));
    printf("%s\n", esArbolAVL(&indiceEmpleados)? "Es AVL" : "No es AVL");
    puts("\nProbemos primitiva esAVL con un arbol totalmente pateado como este:\n");
    for(i = 0; i < contarNodosDelArbol(&indiceEmpleados); i++)
        insertarEnArbolBin(&arbolNoAVL, &i, sizeof(byte), compararEnt, NULL);
    recorrerEnOrdenArbolBinBusq(&arbolNoAVL, NULL, mostrarEnt);
    puts("\n¿Sera AVL?");
    printf("%s\n", esArbolAVL(&arbolNoAVL)? "Resulta que si" :
           (sprintf(buff, "Y NO obvio, la altura del arbol es: %d", alturaArbol(&arbolNoAVL)))? buff : "rrrr");
    printf("Cantidad de nodos que tiene el arbol: %d\n", contarNodosDelArbol(&arbolNoAVL));

    vaciarArbol(&arbolNoAVL);
    vaciarArbol(&indiceEmpleados);
    fclose(pfIdx);
    fclose(pfEmps);
    puts("__________________________________________________________________________________________\n");
    /// mostrarMenu();

    return 0;
}
