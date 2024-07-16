#include "../env/commonData.h"

#define MX_COL 25

/// BEGIN CREACION LOTE PROD_OK /////

int main()
{
    FILE *pfLote = fopen(PATH_STOCK, "wb");
    unsigned i;
    tRegStock vec[] = {
        {"ADS323", "gfdskd", 1234, {22, 7, 2024}, 4},
        {"ADS323", "gtdsat", 124, {22, 2, 2024}, 3},
        {"ADS323", "435ter", 1234, {22, 1, 2024}, 6},
        {"ADS323", "rg443", 987, {22, 10, 2024}, 7},
        {"ADS323", "rg443", 217, {22, 10, 2024}, 8},
        {"ADS323", "rg443", 217, {22, 11, 2024}, 10},
        {"BFJ323", "treg54", 432, {22, 06, 2025}, 15},
        {"BFJ323", "treg54", 432, {20, 06, 2025}, 1},
        {"BFJ323", "treg54", 432, {19, 06, 2025}, 1},
        {"BFJ323", "treg54", 212, {22, 06, 2025}, 15},
        {"BFJ323", "treg54", 120, {22, 01, 2025}, 15},
        {"BFJ323", "treg54", 990, {22, 10, 2025}, 2},
        {"BFJ323", "treg54", 432, {1, 02, 2025}, 3},
        {"CS432F", "43tdrsg", 324, {16, 04, 2025}, 4},
        {"CS432F", "43tdrsg", 324, {15, 04, 2025}, 3},
        {"CS432F", "43tdrsg", 324, {14, 04, 2025}, 2},
        {"CS432F", "43tdrsg", 324, {2, 02, 2025}, 1},
        {"CS432F", "43tdrsg", 324, {14, 04, 2025}, 1},
        {"CS432F", "43tdrsg", 323, {14, 10, 2025}, 2},
        {"CS432F", "43tdrsg", 324, {6, 02, 2025}, 1},
        {"D324FD", "terag", 453, {22, 8, 2025}, 10},
        {"D324FD", "terag", 453, {22, 8, 2025}, 10},
        {"D324FD", "terag", 453, {22, 8, 2025}, 10},
        {"D324FD", "terag", 453, {22, 8, 2025}, 10},
        {"D324FD", "terag", 453, {22, 8, 2025}, 10},
        {"D324FD", "terag", 453, {22, 8, 2025}, 10},
        {"D324FD", "terag", 453, {22, 8, 2025}, 10},
        {"D324FD", "terag", 453, {22, 8, 2025}, 10},
        {"D324FD", "terag", 453, {22, 8, 2025}, 10},
        {"EGDS33", "tardyg", 54, {4, 2, 2024}, 1},
        {"EGDS33", "tardyg", 54, {3, 2, 2024}, 2},
        {"EGDS33", "tardyg", 35, {2, 2, 2024}, 3},
        {"EGDS33", "tardyg", 35, {1, 2, 2024}, 4},
        {"EGDS33", "tardyg", 700, {30, 1, 2024}, 5},
//        {"FB2324", "hfds", 547,{2202024}},
//        {"GHEWU3", "43gterg", 64,{2202024}},
//        {"HTRW33", "gdgerer", 4343,{2202024}},
//        {"I43JNR", "yerhtr", 436,{2202024}},
//        {"JI65J3", "juseat", 643,{220202}},
//        {"KJ435F", "reayt54", 43,{2202024}},
//        {"N4353R", "uy6rw4ewa", 64,{2202024}},
//        {"O3325F", "y5erst4", 64, {2202024}},
//        {"Q54334", "5yeys", 43, {2202024}},
//        {"X4JK43", "54why", 43, {2202024}},
//        {"ZHU344", "5yw4y54", 2, {22, 2,024}},
//        {},
//        {},
//        {},
//        {},
//        {},
//        {},
//        {},
//        {},
//        {},
//        {},
//        {}
    };

    if(!pfLote)
        return 0;

    for(i = 0; i < (sizeof(vec) / sizeof(tRegStock)); i++)
        fwrite(vec + i, sizeof(tRegStock), 1, pfLote);

    fclose(pfLote);

    return 0;
}

//int loteAvencer()
//{
//    FILE *pfLote = fopen(PATH_LOTE_PRODOK, "wb");
//
//
    /// PRODUCTO(6)   FECHA DE VENCIMIENTO MÁS ACTUAL(DDMMAAAA = 8)   CANTIDAD(entero)
//    char vence[][MAX_COL] = {
//        {"ADS323 22072024"},
//        {"BFJ323 22062024"},
//        {"CS432F 22042024"},
//        {"D324FD 22082024"},
//        {"EGDS33 2202024"},
//        {"FB2324 2202024"},
//        {"GHEWU3 2202024"},
//        {"HTRW33 2202024"},
//        {"I43JNR 2202024"},
//        {"JI65J3 2202024"},
//        {"KJ435F 2202024"},
//        {"N4353R 2202024"},
//        {"O3325F 2202024"},
//        {"Q54334 2202024"},
//        {"X4JK43 2202024"},
//        {"ZHU344 2202024"},
////        {""},
////        {""},
////        {""},
////        {""},
////        {""},
////        {""},
////        {""},
////        {""}
//    };
//
//    if(!pfLote)
//        return 0;
//
//
//
//    fclose(pfLote);
//
//    return 0;
//
//    return 0;
//}

/// END CREACION LOTE PROD_OK /////

//int main()
//{
//    FILE *pfLote = fopen()
//
//
//    return 0;
//}
//
//int main()
//{
//    FILE *pfLote = fopen()
//
//
//    return 0;
//}
//
//int main()
//{
//    FILE *pfLote = fopen()
//
//
//    return 0;
//}
