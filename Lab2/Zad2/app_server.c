#include "app.h"

wyjscie * obliczenia_1_svc(wejscie *argp, struct svc_req *rqstp) {
    static wyjscie result;

    // Wypisujemy natychmiast odebrane dane
    printf("%s", argp->x1);
    fflush(stdout);  // Zapewnia natychmiastowe wyświetlenie

    // Kopiujemy dane do wyniku (ale bez gromadzenia ich na zawsze)
    strncpy(result.suma, argp->x1, sizeof(result.suma) - 1);
    result.suma[sizeof(result.suma) - 1] = '\0';  // Zapewniamy zakończenie stringa

    return &result;
}


