#include "app.h"



wyjscie *obliczenia_1_svc(wejscie *argp, struct svc_req *rqstp) {
    static wyjscie result;
    snprintf(result.suma, sizeof(result.suma), "%s", argp->x1);
    
    printf("%s", argp->x1);
    
    return &result;
}



