int abrirSecuenciaArchivos(FILE **vecPfs, const char **nombresArchs, const char *modo, unsigned cant)
{
    int i,
        res;

    for(i = 0; (cant--) && ( ( res = ( vecPfs[i] = fopen(nombresArchs[i], modo) )? TODO_OK : ERR_APERTURA_ARCH ) == TODO_OK ) ; i++)
        ;

    if(res != TODO_OK)
    {
        for(res = 0; res < i; res++)
            fclose(vecPfs[i]);
        return ERR_APERTURA_ARCH;
    }

    return TODO_OK;
}
