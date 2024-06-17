#include "dev.h"

#define ERR_APERT_ARCH_ -22
#define OK 1

int procesarArchivoPolinomios(const char *path_p1, const char *path_p2, const char *path_res)
{
    FILE *pfP1 = fopen(path_p1, "rt"),
         *pfP2 = fopen(path_p2, "rt");
    tLista p1,
           p2;

    if(!pfP1)
        return ERR_APERT_ARCH_;

    if(!pfP2)
    {
        fclose(pfP1);
        return ERR_APERT_ARCH_;
    }

    fclose(pfP1);
    fclose(pfP2);

    return OK;
}
