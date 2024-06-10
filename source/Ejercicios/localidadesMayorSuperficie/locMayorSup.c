#include "locMayorSup.h"

#define ERR_APERT_ARCH -21
#define ERR_PARAMS -43
#define LIMITE_SUPERIOR 5
#define REG_NO_VAL 0
#define MISMA_LOC 0
#define MEN_DEF -1
#define MAY_DEF 1
#define OK 1

int procesarArchivoLote(const char *src_path, const char *res_path)
{
    FILE *pfLotes = fopen(src_path, "rb");
    tLista localidades;
    tLocalidad loc;

    if(!pfLotes)
        return ERR_APERT_ARCH;

    crearLista(&localidades);

    while(fread(&loc, sizeof(tLocalidad), 1, pfLotes))
    {
        if(recuperarRegLocVal(&loc))
            insertarOrdenadoDescConLimite(&localidades, &loc, sizeof(tLocalidad), cmpLocalidades, quedarseConRegMayor, LIMITE_SUPERIOR);
    }

    generarInformeLocalidades(&localidades, res_path);

    vaciarLista(&localidades);
    fclose(pfLotes);

    printf("¡Nos vemos!");
    sleep(3);
    system("cls");

    return OK;
}

byte recuperarRegLocVal(tLocalidad *loc)
{
    return validarProv(loc->provincia) && validarSuperficie(loc->superficie) && validarPoblacion(loc->poblacion);
}

byte validarProv(byte nro)
{
    return ((nro > 0) && (nro < 24));
}

byte validarSuperficie(float sup)
{
    return ((sup > 0) && (sup < 100000));
}

byte validarPoblacion(short unsigned poblacion)
{
    return ((poblacion >= 0) && (poblacion < 10000));
}

int generarInformeLocalidades(tLista *localidades, const char *path)
{
    FILE *pfInf = fopen(path, "wt");

    if(!pfInf)
        return ERR_APERT_ARCH;

    mostrarLista(localidades, mostrarLocalidad, pfInf);

    fclose(pfInf);

    return OK;
}


void mostrarLocalidad(const void *info, FILE *pf)
{
    tLocalidad *d;

    if(!info || !pf)
        return;

    d = (tLocalidad *)info;

    fprintf(pf, "%d|%s|%.2lf|%d\n", d->provincia, d->localidad, d->superficie, d->poblacion);
}

int cmpLocalidades(const void *info1, const void *info2)
{
    tLocalidad *d1,
               *d2;

    if(!info1)
        return MEN_DEF;

    if(!info2)
        return MAY_DEF;

    d1 = (tLocalidad *) info1;
    d2 = (tLocalidad *) info2;

    if(!strcmpi(d1->localidad, d2->localidad) && (d1->provincia == d2->provincia))
        return MISMA_LOC;

    return d1->superficie - d2->superficie;
}
/// si tuvieramos un campo con la fecha del dato sería más óptimo
int quedarseConRegMayor(void **info, unsigned *tamInfo, const void *dato, unsigned tamDato)
{
    tLocalidad *loc,
               *act;
    if(!info || !dato)
        return ERR_PARAMS;

    loc = (tLocalidad *)(*info);
    act = (tLocalidad *)dato;

    if(loc->superficie < act->superficie)
        memcpy(loc, act, *tamInfo);

    return OK;
}
