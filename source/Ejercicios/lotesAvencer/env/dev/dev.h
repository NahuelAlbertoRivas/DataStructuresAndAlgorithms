#ifndef DEV
#define DEV

#include "../commonData.h"
#include "../fileHandler/fileHandler.h"
#include "../menu/menu.h"
#include "../strHandler/strHandler.h"
#include "../../TDA/TDA.h"

char iniciarProceso(const char *fecha, unsigned n);

int compararFechas(tLote *info1, tLote *info2);

int claveNroLoteYfecha(const void *info1, const void *info2);

int dejarFechaMasActual(void **info, unsigned *tamInfo, const void *dato, unsigned tamDato);

int venceEnLosProximosNmeses(void *info, void *recurso);

void informarEnProdOk(tRegStock regStock, tLote regLote, FILE *pfInf);

void informarEnVence(const void *reg, FILE *pfVence);

void mostrarVence();

void procesarStockDat(unsigned n, tFecha fAct);

void mostrarArchRegStock(const char *path);

int compararFechasTipo(tFecha reg1, tFecha reg2);

int compararFechaRefAmeses(tFecha compara, tFecha refe);

//void mostrarProdOk();
//void mostrarStockDat();

#endif
