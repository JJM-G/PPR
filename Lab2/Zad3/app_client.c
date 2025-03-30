#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <rpc/rpc.h>
#include "app.h"  // Zawiera definicje RPC

#define PORT 5000
#define BUFFER_SIZE 100

// Funkcja do obsługi komunikacji TCP i RPC
void testowy_1(char *host, int client_sock) {
    CLIENT *clnt;
    wyjscie *result_1;
    wejscie obliczenia_1_arg;
    size_t read_size;

    // Tworzenie klienta RPC
    #ifndef DEBUG
    clnt = clnt_create(host, TESTOWY, PROBNA, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }
    #endif /* DEBUG */

    // Odbieranie danych przez TCP i wysyłanie do RPC w porcjach
    while ((read_size = recv(client_sock, obliczenia_1_arg.x1, 19, 0)) > 0) {
        obliczenia_1_arg.x1[read_size] = '\0';  // Zapewniamy zakończenie stringa

        

        // Wysyłanie danych przez RPC
        result_1 = obliczenia_1(&obliczenia_1_arg, clnt);
        if (result_1 == (wyjscie *)NULL) {
            clnt_perror(clnt, "RPC call failed");
            break;
        }
    }

    printf("[TCP -> RPC] Koniec transmisji.\n");

    #ifndef DEBUG
    clnt_destroy(clnt);
    #endif /* DEBUG */
}

int main(int argc, char *argv[]) {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    if (argc < 2) {
        printf("usage: %s server_host\n", argv[0]);
        exit(1);
    }

    // Tworzenie gniazda TCP
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Błąd tworzenia gniazda");
        exit(1);
    }

    // Ustawienia adresu serwera
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Powiązanie gniazda z portem
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Błąd bindowania");
        exit(1);
    }

    // Nasłuchiwanie na połączenia
    if (listen(server_sock, 1) == -1) {
        perror("Błąd nasłuchiwania");
        exit(1);
    }

    printf("[TCP Server] Czekam na połączenie...\n");

    // Akceptowanie połączenia z klientem
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
    if (client_sock == -1) {
        perror("Błąd akceptowania połączenia");
        exit(1);
    }

   

    // Przekazywanie gniazda do funkcji obsługującej RPC
    testowy_1(argv[1], client_sock);

    // Zamknięcie gniazda
    close(client_sock);
    close(server_sock);

    return 0;
}

