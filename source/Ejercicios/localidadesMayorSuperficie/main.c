#include "locMayorSup.h"
#include "../../strValidators/strValidators.h"
#include "lotePrueba/lotePrueba.h"

#define FIN_PROCESO 2
#define SRC_PATH "../source/Ejercicios/localidadesMayorSuperficie/files/lote.dat"
#define RES_PATH "../source/Ejercicios/localidadesMayorSuperficie/files/informeLocalidadesMayorSuperficie.txt"

int locMayorSup(void *recursos)
{
    crearLoteLocalidades();
    procesarArchivoLote(SRC_PATH, RES_PATH);

    return FIN_PROCESO;
}
