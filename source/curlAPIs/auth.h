#ifndef DB
#define DB

#ifndef CURLLIB
#include <curl/curl.h>
#endif // CURLLIB
#ifndef OK
#define OK 50
#endif // OK
#ifndef CURL_ERR
#define CURL_ERR 502
#endif // CURL_ERR
#ifndef FAILED_REQ
#define FAILED_REQ 507
#endif // FAILED_REQ
#ifndef STDLIB
#include <stdlib.h>
#endif // STDLIB
#ifndef STRING
#include <string.h>
#endif // STRING

size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
CURL *curlInit();
int curlReq(CURL *curl, const char *endpoint, CURLcode *res, long *httpStatus);
void endCurlHandler(CURL *curl);

#endif
