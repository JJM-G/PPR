<?php
$server = "192.168.21.129";
$port = 5000;

// Tworzenie gniazda TCP
$sock = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if (!$sock) {
    die("Błąd tworzenia gniazda\n");
}

// Połączenie z Procesem 2
if (!socket_connect($sock, $server, $port)) {
    die("Błąd połączenia z serwerem TCP\n");
}

// Czytanie danych z STDIN i wysyłanie do Procesu 2
while ($line = fgets(STDIN)) {
    socket_write($sock, $line, strlen($line));
}

socket_close($sock);
?>

