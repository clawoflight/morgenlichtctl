#include "networking.h"

static int connection; ///< The TCP socket of the server

int init_networking(const char* const remote_host, const int port)
{
    // Create a new socket
    connection = socket(AF_INET, SOCK_STREAM, 0);

    // Resolve the host name of the server
    struct hostent *server;
    server = gethostbyname(remote_host);
    if (server == NULL) {
        fprintf(stderr, "Could not resolve host '%s'\n", remote_host);
        return 1;
    }

    // Create the server address struct
    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(port);

    // Connect to the server
    if (connect(connection, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        fprintf(stderr, "Could not connect to %s:%d\n", remote_host, port);
        return 1;
    }

    return 0;
}

int network_write(const char* const message)
{
    int len = strlen(message);
    if (write(connection, message, len) < len) {
        fprintf(stderr, "Could not write to the server!\n");
        return 1;
    }

    return 0;
}

char network_read_char()
{
    char buf;
    if (read(connection, &buf, 1) < 0) {
        fprintf(stderr, "Could not read from the server!\n");
        return -1;
    }

    return buf;
}

void term_networking()
{
    close(connection);
}
