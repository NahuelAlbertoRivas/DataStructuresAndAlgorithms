#include "arbolBinBusq.h"

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo)(  (    !( (nodo) = (tNodoArbol *) malloc() )        \
                                                                || !( (info) = malloc(tamInfo) )         )?     \
                                                                        free(nodo), SIN_MEM : TODO_OK           )
