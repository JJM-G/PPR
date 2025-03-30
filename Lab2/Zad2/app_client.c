/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "app.h"


void testowy_1(char *host, FILE *file) {
    CLIENT *clnt;
    wyjscie *result_1;
    wejscie obliczenia_1_arg;
    size_t read_size;

    #ifndef DEBUG
    clnt = clnt_create(host, TESTOWY, PROBNA, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }
    #endif /* DEBUG */

    while ((read_size = fread(obliczenia_1_arg.x1, 1, 19, file)) > 0) {
        obliczenia_1_arg.x1[read_size] = '\0';
        result_1 = obliczenia_1(&obliczenia_1_arg, clnt);
        if (result_1 == (wyjscie *)NULL) {
            clnt_perror(clnt, "call failed");
            break;
        }
    }

    #ifndef DEBUG
    clnt_destroy(clnt);
    #endif /* DEBUG */
}




int main(int argc, char *argv[]) {
    char *host;
    FILE *file;

    if (argc < 3) {
        printf("usage: %s server_host filename\n", argv[0]);
        exit(1);
    }

    host = argv[1];
    file = fopen(argv[2], "r");
    if (!file) {
        perror("Nie można otworzyć pliku");
        exit(1);
    }

    testowy_1(host, file);
    fclose(file);
    return 0;
}
