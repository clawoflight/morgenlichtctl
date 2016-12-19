#ifndef MORGENLICHTCTL_NETWORKING_H
#define MORGENLICHTCTL_NETWORKING_H
/**
* @file networking.h
* This file provides an abstraction layer for the network connection to the morgenlichtd server.
*/
#include <SDL2/SDL_net.h>

#define MORGENLICHTD_PORT 1234 ///< The public port of morgenlichtd @todo choose a proper port :)

/**
 * Initialise the required libraries and the TCP connection to the server.
 * This must be called before using the other functions provided by this header.
 *
 * @param  remote_host The host name of the server
 *
 * @return 0 on success, or non-zero otherwise.
 */
int init_networking(const char* const remote_host);


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
 * Read a message sent from the server via TCP.
 *
 * @param  maxlen The length of the receiving buffer
 * @param  buff   The buffer in which to save the reply
 *
 * @return 0 on success, or non-zero otherwise.
 */
int network_read(int maxlen, char* const buff);


/**
 * Read a single char from the server.
 *
 * @return The read character, or -1 on error.
 */
char network_read_char();

#endif // MORGENLICHTCTL_NETWORKING_H
