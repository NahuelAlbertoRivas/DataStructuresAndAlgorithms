#ifndef FERRETERIA
#define FERRETERIA

#define PATH_PRODUCTOS "../source/Ejercicios/ferreteria/Archivos/productos.dat"
#define PATH_INDICE_PRODUCTOS "../source/Ejercicios/ferreteria/Archivos/productos.idx"
#define PATH_PEDIDOS "../source/Ejercicios/ferreteria/Archivos/pedidos.txt"

#include "../../../arbolBinBusq/arbol.h"
#include "../../../colaDinamica/cola.h"
#include <stdbool.h>
#include <winsock2.h>
#include <windows.h>
#include <unistd.h>

typedef struct {
    char cod[11];
    char descripcion[21];
    unsigned stock;
    float precio;
} t_producto_stock;

typedef struct {
    short unsigned cod_ped;
    char cod_prod[11];
    unsigned cant;
} t_pedido;

typedef struct {
    char cod_prod[11];
    unsigned nro_reg;
} t_reg_ind;

void imprimirDetalle(tCola *Pedidos, tArbolBinBusq *Indices, unsigned cantRegs, byte tipo, FILE *pfImpr, FILE* pfProds);
void imprimirRealizado(tCola *Pedidos, tArbolBinBusq *Indices, unsigned cantRegs, FILE *pfImpr, FILE *pfProds);
void imprimirFaltante(tCola *Pedidos, tArbolBinBusq *Indices, unsigned cantRegs, FILE *pfImpr, FILE *pfProds);

byte estadoStock(tArbolBinBusq *Indices, t_pedido regPedidoEntrante, FILE *pfProds);

int compararIndices(const void *reg1, const void *reg2);

byte formatearLineaPedido(char *linea, t_pedido *regPedidoActual);

int cargarIndice(tArbolBinBusq *pa, const char *path_indice);

void actualizarIndices(tArbolBinBusq *pa);

void escribirArchivoBin(void *info, unsigned tam, void *recurso);

int procesar_pedidos(const char * path_prods, const char * path_pedidos, const char * path_indice);
int procesar_pedidos_res(const char * path_prods, const char * path_pedidos, const char * path_indice);


int procesar_pedidos_simple(const char * path_prods, const char * path_pedidos, const char * path_indice);
int procesar_pedidos_simple_res(const char * path_prods, const char * path_pedidos, const char * path_indice);

#endif
