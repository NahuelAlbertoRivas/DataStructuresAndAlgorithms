#include <stdio.h>
#include <stdlib.h>
#include "../include/ferreteria.h"
#include "../include/utilitarias.h"

#define TODO_OK 1

int resolucion_completa();
int resolucion_simple();

int ferreteria(void *recursos)
{
    /// crear_archivo_productos_res(PATH_PRODUCTOS);
    /// crear_archivo_pedidos_res(PATH_PEDIDOS);
    /// generar_indice_productos_res(PATH_PRODUCTOS, PATH_INDICE_PRODUCTOS);

    /** mostrar_archivo_productos_res(PATH_PRODUCTOS);
    printf("\n\n");
    mostrar_archivo_pedidos_res(PATH_PEDIDOS);
    printf("\n\n");
    mostrar_indice_productos_res(PATH_INDICE_PRODUCTOS); **/

    /// las anteriores líneas tienen fns. desarrolladas por Pezzola en la estática ' libBibliotecaParcial.a '
    /// del proyecto, la cual excluí porque me generaba conflicto de prototipos. Básicamente, todas las fns. que tienen
    /// el sufijo ' _res ' están en dicha biblioteca

    /// Descomente y utilice esta funcion si desea realizar la resolucion SIMPLE
    /// return resolucion_simple()

    /// Descomente y utilice esta funcion si desea realizar la resolucion COMPLETA
    return resolucion_completa();
}

int resolucion_completa()
{
    /**
        Esta función debe realizar la actualización del achivo de stock de productos
        a partir de los pedidos. Procesando uno por uno los pedidos y validando el stock.

        Si alguno de los productos solicitados en el pedido no se puede completar, el stock
        no debe ser actualizado para ningun producto del pedido y el mismo debe ser informado
        en el archivo de pedidos rechazados, mostrando por pantalla las lineas de pedidos que no
        pudieron ser completadas.
        En cambio, si todos los productos del pedido pueden ser completados debe informar el pedido en el
        archivo pedidos realizados y actualizar el stock de los productos en el archivo productos. Ademas
        debe informar el total a cobrar por pedido.

        Preste atencion a la salida ya resuelta (´procesar_pedidos_res´) e intente
        reproducirla desarrollando la funcion ´procesar_pedidos´
    */
    /// procesar_pedidos_res(PATH_PRODUCTOS,PATH_PEDIDOS, PATH_INDICE_PRODUCTOS);
    procesar_pedidos(PATH_PRODUCTOS,PATH_PEDIDOS, PATH_INDICE_PRODUCTOS);

    printf("\n\n********  RESULTADOS  ***********\n");

    /// mostrar_archivo_productos_res(PATH_PRODUCTOS); HACER

    printf("\n\n*********  REALIZADOS  ***********\n");
    /// mostrar_archivo_texto_res("../Archivos/pedidos_realizados.txt"); HACER
    printf("\n*********  FIN REALIZADOS  ***********\n\n");

    printf("\n\n*********  FALTANTES  ***********\n");
    /// mostrar_archivo_texto_res("../Archivos/pedidos_faltantes.txt"); HACER
    printf("\n*********  FIN FALTANTES  ***********\n\n");

    return 0;
}


int resolucion_simple()
{
    /**
        Esta función debe realizar la actualización del achivo de stock de productos
        a partir de los pedidos. Procesando uno por uno los pedidos y validando el stock.
        Mostrando por pantalla las lineas de pedidos que no pudieron ser completadas e
        informando el total a cobrar por pedido.

        Preste atencion a la salida ya resuelta (´procesar_pedidos_simple_res´) e intente
        reproducirla desarrollando la funcion ´procesar_pedidos_simple´
    */
    /// procesar_pedidos_simple_res(PATH_PRODUCTOS,PATH_PEDIDOS, PATH_INDICE_PRODUCTOS);
    //procesar_pedidos_simple(PATH_PRODUCTOS,PATH_PEDIDOS, PATH_INDICE_PRODUCTOS);

    printf("\n\n********  RESULTADOS  ***********\n");

    /// mostrar_archivo_productos_res(PATH_PRODUCTOS); HACER

    return 0;
}
