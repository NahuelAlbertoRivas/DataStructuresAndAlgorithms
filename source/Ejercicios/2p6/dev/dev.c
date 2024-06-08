#include "dev.h"

int procesarArchivo(const char *path, int orden)
{
    FILE *pfDatos = fopen(path, "rb");
    int datoNue,
        topePilaOrdenada,
        topePilaAux,
        actualizaciones;
    tPila pilaOrdenada,
          pilaAux;

    if(!pfDatos)
        return ERR_APERTURA_ARCH;

    crearPila(&pilaOrdenada);
    crearPila(&pilaAux);

    fread(&datoNue, sizeof(datoNue), 1, pfDatos);

    while(!feof(pfDatos))
    {
        do
        {
            actualizaciones = 0;

            if(verTope(&pilaOrdenada, &topePilaOrdenada, sizeof(topePilaOrdenada)))
            {
                if(verTope(&pilaAux, &topePilaAux, sizeof(topePilaAux)))
                {
                    if(datoNue < topePilaAux && datoNue < topePilaOrdenada &&
                        sacarDePila(&pilaOrdenada, &topePilaOrdenada, sizeof(topePilaOrdenada)))
                    {
                        ponerEnPila(&pilaAux, &topePilaOrdenada, sizeof(topePilaOrdenada));
                        actualizaciones = 1;
                    }
                    else if(datoNue > topePilaOrdenada && datoNue > topePilaAux &&
                        sacarDePila(&pilaAux, &topePilaAux, sizeof(topePilaAux)))
                    {
                        ponerEnPila(&pilaOrdenada, &topePilaAux, sizeof(topePilaAux));
                        actualizaciones = 1;
                    }
                }
                else if(datoNue < topePilaOrdenada)
                {
                    if(sacarDePila(&pilaOrdenada, &topePilaOrdenada, sizeof(topePilaOrdenada)))
                        ponerEnPila(&pilaAux, &topePilaOrdenada, sizeof(topePilaOrdenada));
                    actualizaciones = 1;
                }
            }
        }while(actualizaciones);

        ponerEnPila(&pilaOrdenada, &datoNue, sizeof(datoNue));

        fread(&datoNue, sizeof(datoNue), 1, pfDatos);
    }

    if(orden == DESC)
    {
        while(sacarDePila(&pilaOrdenada, &topePilaOrdenada, sizeof(topePilaOrdenada)))
            ponerEnPila(&pilaAux, &topePilaOrdenada, sizeof(pilaOrdenada));
        while(sacarDePila(&pilaAux, &topePilaAux, sizeof(topePilaAux)))
            fprintf(stdout, "%d\n", topePilaAux);
    }
    else
    {
        while(sacarDePila(&pilaAux, &topePilaAux, sizeof(topePilaAux)))
            ponerEnPila(&pilaOrdenada, &topePilaAux, sizeof(topePilaAux));
        while(sacarDePila(&pilaOrdenada, &topePilaOrdenada, sizeof(topePilaOrdenada)))
            fprintf(stdout, "%d\n", topePilaOrdenada);
    }


    vaciarPila(&pilaOrdenada);
    vaciarPila(&pilaAux);
    fclose(pfDatos);

    return FIN_PROCESO;
}
