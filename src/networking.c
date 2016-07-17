/* © 2015, 2016 Andreas Postel and Bennett Piater.
 This file is part of morgenlichtctl.

 Morgenlichtctl is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, version 3 of the License.
 morgenlichtctl is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with morgenlichtctl.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "networking.h"

static IPaddress ipaddress; ///< The IP address of the server to connect to
static TCPsocket server_sock; ///< The TCP socket of the server

int init_networking(const char* const remote_host)
{
    /* Init the libraries that we use */
    if (SDL_Init(0) == -1) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    if (SDLNet_Init() == -1) {
        fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
        return 1;
    }

    // Resolve the host name of the server
    if (SDLNet_ResolveHost(&ipaddress, remote_host, MORGENLICHTD_PORT) == -1)
    {
        fprintf(stderr, "Could not resolve %s:\n\t%s\n", remote_host, SDLNet_GetError());
        return 1;
    }

    printf("Connecting to %s...", remote_host);
    fflush(stdout); // Flush to make sure that the previous line is printed

    // Connect to the server
    if ((server_sock = SDLNet_TCP_Open(&ipaddress)) == NULL) {
        fprintf(stderr, " Could not open a TCP connection with %s:\n\t%s\n", remote_host, SDLNet_GetError());
        return 1;
    }

    printf(" done.\n\n");

    return 0;
}

int network_write(const char* const message)
{
    int len = strlen(message) + 1; // add one for the terminating NULL
    int sent = SDLNet_TCP_Send(server_sock, message, len);

    if (sent < len) {
        fprintf(stderr, "Could not write to the server: %s\n", SDLNet_GetError());
        // It may be good to disconnect because it is likely invalid now.
        return 1;
    }

    return 0;
}

int network_read(int maxlen, char* const buff)
{
    if (SDLNet_TCP_Recv(server_sock, buff, maxlen) <= 0) {
        // An error may have occured, but sometimes you can just ignore it
        // It may be good to disconnect sock because it is likely invalid now.
        fprintf(stderr, "Could not read from the server: %s\n", SDLNet_GetError());
        return 1;
    }

    return 0;
}

char network_read_char()
{
    char buf;
    if (SDLNet_TCP_Recv(server_sock, &buf, 1) <= 0) {
        fprintf(stderr, "Could not read from the server: %s\n", SDLNet_GetError());
        return -1;
    }

    return buf;
}

void term_networking()
{
    SDLNet_TCP_Close(server_sock);
    SDLNet_Quit();
    SDL_Quit();
}
