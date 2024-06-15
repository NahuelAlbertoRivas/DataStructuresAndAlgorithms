#include "../include/ferreteria.h"
#include "../../../colaDinamica/cola.h"
#include "../include/utilitarias.h"
#include "../../../strValidators/strValidators.h"

#define MAX_TAM_LINEA 30
#define MAX_RECURSO 20
#define ERROR_ARCHIVO -23

#define LONG_COD_PEDIDO 6
#define LONG_COD_PROD 10
#define LONG_CANT 3

#define ERR_APERT_ARCH_ -12

#define PATH_FALTANTES "../source/Ejercicios/ferreteria/Archivos/pedidos_faltantes.txt"
#define PATH_REALIZADOS "../source/Ejercicios/ferreteria/Archivos/pedidos_realizados.txt"

#define OK 1
#define HAY_STOCK 1
#define NO_HAY_STOCK 0

int procesar_pedidos(const char *path_prods, const char *path_pedidos, const char *path_indice)
{
    FILE *pfPedidos = fopen(path_pedidos, "rt"),
         *pfProds = fopen(path_prods, "rb"),
         *pfFaltantes = fopen(PATH_FALTANTES, "wt"),
         *pfRealizados = fopen(PATH_REALIZADOS, "wt");
    tArbolBinBusq Indices;
    tCola Pedidos;
    t_pedido regPedidoEntrante;
    char linea[MAX_TAM_LINEA],
         *res;
    unsigned cantProds,
             cantFaltantes,
             codPedActual;

    if(!pfPedidos)
        return ERR_APERT_ARCH_;

    if(!pfProds)
    {
        fclose(pfPedidos);
        return ERR_APERT_ARCH_;
    }

    if(!pfFaltantes)
    {
        fclose(pfPedidos);
        fclose(pfProds);
        return ERR_APERT_ARCH_;
    }

    if(!pfRealizados)
    {
        fclose(pfPedidos);
        fclose(pfProds);
        fclose(pfFaltantes);
        return ERR_APERT_ARCH_;
    }

    crearArbolBinBusq(&Indices);
    crearCola(&Pedidos);

    cargarIndice(&Indices, path_indice);

    if((res = fgets(linea, MAX_TAM_LINEA, pfPedidos)))
    {
        formatearLineaPedido(linea, &regPedidoEntrante);
        codPedActual = regPedidoEntrante.cod_ped;
    }

    while(*res)
    {
        cantFaltantes = 0;
        cantProds = 0;
        while(*res && (regPedidoEntrante.cod_ped == codPedActual))
        {
            cantProds++;
            cantFaltantes += (estadoStock(&Indices, regPedidoEntrante, pfProds) == NO_HAY_STOCK)? 1 : 0;
            ponerEnCola(&Pedidos, &regPedidoEntrante, sizeof(t_pedido));
            if((res = fgets(linea, MAX_TAM_LINEA, pfPedidos)))
                formatearLineaPedido(linea, &regPedidoEntrante);
        }
        cantFaltantes?
              imprimirFaltante(&Pedidos, &Indices, cantProds, pfFaltantes, pfProds)
            : imprimirRealizado(&Pedidos, &Indices, cantProds, pfRealizados, pfProds);
        codPedActual = regPedidoEntrante.cod_ped;
    }

    /// actualizarIndices(&Indices);

    vaciarCola(&Pedidos);
    eliminarArbol(&Indices);

    fclose(pfPedidos);
    fclose(pfProds);
    fclose(pfFaltantes);
    fclose(pfRealizados);

    return TODO_BIEN;
}

/// esta función podría contener validadores, y en función a estos retornar si se recupera un registro válido o no
byte formatearLineaPedido(char *linea, t_pedido *regPedido) /// esta fn. más adelante podría contener validadores y retornar
{                                                           /// 1 ó 0 si recupera (o no) un reg. válido
    char recurso[MAX_RECURSO];

    recuperarSecuenciaCaracteres(linea, recurso, LONG_COD_PEDIDO, 0);
    regPedido->cod_ped = atoi(recurso);
    recuperarSecuenciaCaracteres(linea, recurso, LONG_COD_PROD, LONG_COD_PEDIDO);
    strcpy(regPedido->cod_prod, eliminarEspaciosPrePalabra(recurso));
    puts(regPedido->cod_prod);
    recuperarSecuenciaCaracteres(linea, recurso, LONG_CANT, LONG_COD_PEDIDO + LONG_COD_PROD);
    regPedido->cant = atoi(recurso);

    return OK;
}
/// esta fn. podría tener varios códigos si se hiciera una clasificación de distintos rangos a considerar,
/// por eso no retorna bool
byte estadoStock(tArbolBinBusq *Indices, t_pedido regPedidoEntrante, FILE *pfProds)
{
    t_producto_stock regProducto;
    t_reg_ind regIndice;
    byte r = HAY_STOCK;

    strcpy(regIndice.cod_prod, regPedidoEntrante.cod_prod);
    if((r = buscarElemArbolBinBusq(Indices, &regIndice, sizeof(t_reg_ind), compararIndices)))
    {
        fseek(pfProds, regIndice.nro_reg * sizeof(t_producto_stock), SEEK_SET);
        fread(&regProducto, sizeof(t_producto_stock), 1, pfProds);
        if(regProducto.stock < regPedidoEntrante.cant)
            r = NO_HAY_STOCK;
    }

    return r;
}

void imprimirFaltante(tCola *Pedidos, tArbolBinBusq *Indices, unsigned cantRegs, FILE *pfImpr, FILE* pfProds)
{
    t_producto_stock regProd;
    t_reg_ind regInd;
    t_pedido regPed;

    if(!cantRegs || !Pedidos || !Indices)
        return;

    if(verPrimeroCola(Pedidos, &regPed, sizeof(t_pedido)))
        fprintf(pfImpr, "Pedido %d con faltantes:\n", regPed.cod_ped);

    while((cantRegs--) && sacarDeCola(Pedidos, &regPed, sizeof(t_pedido)))
    {
        strcpy(regInd.cod_prod, regPed.cod_prod);
        if(buscarElemArbolBinBusq(Indices, &regInd, sizeof(t_reg_ind), compararIndices))
        {
            fseek(pfProds, regInd.nro_reg * sizeof(t_producto_stock), SEEK_SET);
            fread(&regProd, sizeof(t_producto_stock), 1, pfProds);
            fprintf(pfImpr, "%8s%28s:%-7d%-7d%-2c", " -",
                                            regPed.cod_prod,
                                            regProd.stock,
                                            regPed.cant,
                                            (regProd.stock < regPed.cant)? 'F' : ' ');
        }
    }
}

void imprimirRealizado(tCola *Pedidos, tArbolBinBusq *Indices, unsigned cantRegs, FILE *pfImpr, FILE *pfProds)
{
    t_producto_stock regProd;
    t_reg_ind regInd;
    t_pedido regPed;
    double total = 0;

    if(!cantRegs || !Pedidos || !Indices)
        return;

    if(verPrimeroCola(Pedidos, &regPed, sizeof(t_pedido)))
        fprintf(pfImpr, "Pedido %d realizado:\n", regPed.cod_ped);

    while((cantRegs--) && sacarDeCola(Pedidos, &regPed, sizeof(t_pedido)))
    {
        strcpy(regInd.cod_prod, regPed.cod_prod);
        if(buscarElemArbolBinBusq(Indices, &regInd, sizeof(t_reg_ind), compararIndices))
        {
            fseek(pfProds, regInd.nro_reg * sizeof(t_producto_stock), SEEK_SET);
            fread(&regProd, sizeof(t_producto_stock), 1, pfProds);
            fprintf(pfImpr, "%8s%28s:%-7d%-7d $%-5.2lf $%5.2lf", " -",
                                                                 regPed.cod_prod,
                                                                 regProd.stock,
                                                                 regPed.cant,
                                                                 regProd.precio,
                                                                 regPed.cant * regProd.precio);
            total += regPed.cant * regProd.precio;
        }
    }
    fprintf(pfImpr, "%-47s $%lf", "TOTAL:", total);
}

int compararIndices(const void *reg1, const void *reg2)
{
    t_reg_ind *r1 = (t_reg_ind *)reg1,
              *r2 = (t_reg_ind *)reg2;
    return strcmpi(r1->cod_prod, r2->cod_prod);
}

int cargarIndice(tArbolBinBusq *pa, const char *path_indice)
{
    FILE *pfIndice = fopen(path_indice, "rb");

    if(!pfIndice)
        return ERROR_ARCHIVO;

    return cargarArchivoBinOrdenadoAbiertoArbolBinBusq(pa, pfIndice, sizeof(t_reg_ind));
}

/** *********************************** **/

//void actualizarIndices(tArbolBinBusq *pa)
//{
//    FILE *pfIndice = fopen(PATH_INDICE_PRODUCTOS, "wb");
//
//    if(!pfIndice)
//        return;
//
//    recorrerEnOrdenSimpleArbolBinBusq(pa, pfIndice, escribirArchivoBin);
//
//    fclose(pfIndice);
//}

//void escribirArchivoBin(void *info, unsigned tam, void *recurso)
//{
//    FILE *pf = (FILE *)recurso;
//    t_reg_ind *reg = (t_reg_ind *)info;
//
//    if(!info || !recurso)
//        return;
//
//    fseek(pf, reg->nro_reg * tam, SEEK_SET);
//    fwrite(reg, tam, 1, pf);
//}
