#include "db.h"

size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp){
    size_t realsize = size * nmemb;
    /// printf("%.*s", (int)realsize,  (char *)contents);
    return realsize;
}

/**
size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp){
    size_t realsize = size * nmemb;
    memory *mem = (memory *)userp;
    char *ptr = realloc(mem->respuesta, mem->tam + realsize + 1);
    if(!ptr)
        return 0;

    mem->respuesta = ptr;
    memcpy(&(mem->respuesta[mem->tam]), contents, realsize);
    mem->tam += realsize;
    mem->respuesta[mem->tam] = 0;
    printf("%.*s", (int)realsize,  (char *)contents);

    return realsize;
}
**/

CURL *curlInit(){
    CURL *curl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    return curl;
}

int curlReq(CURL *curl, const char *endpoint, CURLcode *res, long *httpStatus){ /// ej. de endpoint: https://api.pons.com/v1/dictionary?l=dees&q=house
    if(curl){
        /// Se establece URL del método GET
        curl_easy_setopt(curl, CURLOPT_URL, endpoint);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "X-Secret: 32cdf9d40fc7e4f5a58fae51cdca97dffff2c1d7c36874394759e49cb2ec4f79");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        /// Se establece fn. de retorno para manejar res
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);

        /// Solicitud HTTP GET
        *res = curl_easy_perform(curl);

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, httpStatus);

        /// Verificación de estado
        if(*res != CURLE_OK)
            return FAILED_REQ;

        return OK;
    }
    return CURL_ERR;
}

void endCurlHandler(CURL *curl){
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}
