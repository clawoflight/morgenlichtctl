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
#ifndef MORGENLICHTCTL_NETWORKING_H
#define MORGENLICHTCTL_NETWORKING_H
/**
* @file networking.h
* This file provides an abstraction layer for the network connection to the morgenlichtd server.
*/
#include <SDL2/SDL.h>
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

#endif // MORGENLICHTCTL_NETWORKING_H
