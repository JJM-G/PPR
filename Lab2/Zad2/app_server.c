#include "app.h"

wyjscie * obliczenia_1_svc(wejscie *argp, struct svc_req *rqstp) {
    static wyjscie result;

   
    printf("%s", argp->x1);
    fflush(stdout);
    strncpy(result.suma, argp->x1, sizeof(result.suma) - 1);
    result.suma[sizeof(result.suma) - 1] = '\0'; 

    return &result;
}


