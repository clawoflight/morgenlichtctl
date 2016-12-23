#ifndef MORGENLICHTCTL_NETWORKING_H
#define MORGENLICHTCTL_NETWORKING_H
/**
* @file networking.h
* This file provides an abstraction layer for the network connection to the morgenlichtd server.
*/
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/**
 * Initialise the required libraries and the TCP connection to the server.
 * This must be called before using the other functions provided by this header.
 *
 * @param  remote_host The host name of the server
 * @param  port        The port of the server
 *
 * @return 0 on success, or non-zero otherwise.
 */
int init_networking(const char* const remote_host, const int port);


/**
 * Close the TCP connection if it is still active, then de-initialize the used libraries.
 */
void term_networking();

/**
 * Send a message to the server via TCP.
 *
 * @param  message The message to send
 *
 * @return 0 on success, or non-zero otherwise.
 */
int network_write(const char* const message);

/**
 * Read a single char from the server.
 *
 * @return The read character, or -1 on error.
 */
char network_read_char();

#endif // MORGENLICHTCTL_NETWORKING_H
