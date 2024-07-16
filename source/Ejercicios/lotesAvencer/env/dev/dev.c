#include "dev.h"

#define MAX_DIGITOS 4
#define FECHA_MAYOR 5
#define MAX_LINEA 100
#define DICIEMBRE 12

typedef struct
{
    bool vence;
    unsigned n;
} tProximoAvencer;

/// donde ' n ' representa los "n meses"
void recuperarFecha(const char *fecha, tFecha *fAct)
{
    sscanf(fecha, "%2d%2d%4d", &fAct->dd, &fAct->mm, &fAct->aaaa);
}

char iniciarProceso(const char *fecha, unsigned n)
{
    tFecha fAct;

    recuperarFecha(fecha, &fAct);

    mostrarMenu(n, fAct);

    return TODO_OK;
}

void procesarStockDat(unsigned n, tFecha fAct)
{
    tLista lotes;
    tRegStock regEntrante,
              regActual = {"", "", 0, {0, 0, 0}, 0};
    tLote regLote;
    unsigned cantProximosAvencer,
             cantLeida = 0;
    int ultLectura;
    FILE *pfStock = fopen(PATH_STOCK, "rb"),
        *pfVence,
        *pfProdOk;

    if(!pfStock)
        return;

    if(!(pfVence = fopen(PATH_PROD_VENCE, "wt")))
    {
        fclose(pfStock);
        return;
    }

    if(!(pfProdOk = fopen(PATH_PROD_OK, "wt")))
    {
        fclose(pfStock);
        fclose(pfVence);
        return;
    }

    crearLista(&lotes);

    while((ultLectura = fread(&regEntrante, sizeof(tRegStock), 1, pfStock)) || !listaVacia(&lotes))
    {
        if(ultLectura && !strcmpi(regActual.codProd, regEntrante.codProd))
        {
            regLote.nro = regEntrante.nroLote;
            regLote.vto = regEntrante.vto;
            regLote.cantStock = regEntrante.cantStock;
            regActual.cantStock += regEntrante.cantStock;
            if((compararFechasTipo(regEntrante.vto, fAct) <= 0)
               || (compararFechaRefAmeses(regEntrante.vto, fAct) <= n))
                cantProximosAvencer++;
            cantLeida++;
            insertarEnOrden(&lotes, &regLote, sizeof(tLote), claveNroLoteYfecha, dejarFechaMasActual);
        }
        else
        { /// realizo el resumen del producto actual
            if(cantLeida)
                mostrarYvaciarN(&lotes,
                                cantLeida,
                                (cantProximosAvencer)?
                                    (fprintf(pfVence, "cod. prod.: %6s, cant. stock producto: %d\n===  ====           ====  ===== ========\n", regActual.codProd, regActual.cantStock),
                                    pfVence)
                                    : (verPrimero(&lotes, &regLote, sizeof(tLote)),
                                      informarEnProdOk(regActual, regLote, pfProdOk),
                                      NULL),
                                (cantProximosAvencer) ?
                                    informarEnVence
                                    : NULL);
            if(cantProximosAvencer)
                fprintf(pfVence, "______________________________________________________________________________\n");
            if(ultLectura)
            {
                regActual = regEntrante;
                regLote.nro = regEntrante.nroLote;
                regLote.vto = regEntrante.vto;
                regLote.cantStock = regEntrante.cantStock;
                cantProximosAvencer = ((compararFechasTipo(regEntrante.vto, fAct) <= 0)
                   || (compararFechaRefAmeses(regEntrante.vto, fAct) <= n))?
                        1
                        : 0;
                cantLeida = 1;
                insertarEnOrden(&lotes, &regLote, sizeof(tLote), claveNroLoteYfecha, dejarFechaMasActual);
            }
        }
    }

    vaciarLista(&lotes);

    fclose(pfStock);
    fclose(pfVence);
    fclose(pfProdOk);
}

void informarEnVence(const void *info, FILE *pfVence)
{
    tLote *reg = (tLote *) info;
    fprintf((FILE *) pfVence, "nro. lote: %d, vto: %02d/%02d/%4d, cant.: %d\n", reg->nro,
                                                                              reg->vto.dd,
                                                                              reg->vto.mm,
                                                                              reg->vto.aaaa,
                                                                              reg->cantStock);
}

void informarEnProdOk(tRegStock regStock, tLote regLote, FILE *pfInf)
{
    regStock.nroLote = regLote.nro;
    regStock.vto = regLote.vto;

    fwrite(&regStock, sizeof(tRegStock), 1, pfInf);
    fflush(stdin);
}

int dejarFechaMasActual(void **info, unsigned *tamInfo, const void *dato, unsigned tamDato)
{
    tLote **regOriginal,
          *nuevo;

    regOriginal = (tLote **) info;
    nuevo = (tLote *) dato;

//    if((nuevo->vto.aaaa <= (*regOriginal)->vto.aaaa) &&
//       (nuevo->vto.mm <= (*regOriginal)->vto.mm) &&
//       (nuevo->vto.dd < (*regOriginal)->vto.dd))
    if(compararFechas(*regOriginal, nuevo) > 0)
        (*regOriginal)->vto = nuevo->vto;

    (*regOriginal)->cantStock += nuevo->cantStock;

    return TODO_OK;
}

int compararFechas(tLote *reg1, tLote *reg2)
{
    int res;

    return ((res = (reg1->vto.aaaa - reg2->vto.aaaa)))?
                res :
                ((res = (reg1->vto.mm - reg2->vto.mm)))?
                    res :
                    (reg1->vto.dd - reg2->vto.dd);
}

int claveNroLoteYfecha(const void *info1, const void *info2)
{
    tLote *reg1 = (tLote *) info1,
          *reg2 = (tLote *) info2;
    int res = reg1->nro - reg2->nro;

    return (res = reg1->vto.aaaa - reg2->vto.aaaa)? /// ordeno por fecha
                ((reg1->nro != reg2->nro)? res : 0)
                : (res = reg1->vto.mm - reg2->vto.mm)?
                    ((reg1->nro != reg2->nro)? res : 0)
                    : (res = reg1->vto.dd - reg2->vto.dd)?
                        ((reg1->nro != reg2->nro)? res : 0)
                        : ((reg1->nro != reg2->nro)? reg1->cantStock - reg2->cantStock : 0); /// ordeno por cant. producto
}

void mostrarArchRegStock(const char *path)
{
    FILE *pf = fopen(path, "rb");
    tRegStock reg;

    if(!pf)
        return;

    while(fread(&reg, sizeof(tRegStock), 1, pf))
        printf("cod: %s, desc.: %s, nro. lote: %d., cant stock: %d, vto.: %02d/%02d/%4d\n",
                reg.codProd, reg.descrip, reg.nroLote, reg.cantStock, reg.vto.dd, reg.vto.mm, reg.vto.aaaa);

    fclose(pf);
}

void mostrarVence()
{
    FILE *pfVence = fopen(PATH_PROD_VENCE, "rt");
    char linea[MAX_LINEA];

    if(!pfVence)
        return;

    while(fgets(linea, MAX_LINEA, pfVence))
        printf("%s", linea);

    fclose(pfVence);
}

int compararFechasTipo(tFecha reg1, tFecha reg2)
{
    return (reg1.aaaa - reg2.aaaa)? reg1.aaaa - reg2.aaaa :
            (reg1.mm - reg2.mm)? reg1.mm - reg2.mm :
            reg1.dd - reg2.dd;
}

int compararFechaRefAmeses(tFecha compara, tFecha ref)
{
    if(compara.aaaa == ref.aaaa)
        return compara.mm - ref.mm;

    return (DICIEMBRE - ref.mm) + compara.mm;
}

//void mostrarProdOk()
//{
//    FILE *pfProdOk = fopen(PATH_PROD_OK, "rb");
//    tInformeOk reg;
//
//    if(!pfProdOk)
//        return;
//
//    while(fread(&reg, sizeof(tInformeOk), 1, pfProdOk))
//        printf("cod: %s, desc: %s, nro. lote: %d. , cant total: %d, vto: %2d/%2d/%4d\n",
//                reg.codProd, reg.descrip, reg.nroLote, reg.cantTotal, reg.vto.dd, reg.vto.mm, reg.vto.aaaa);
//
//    fclose(pfProdOk);
//}
