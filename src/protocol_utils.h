/* © 2015, 2016 Andreas Postel and Bennett Piater.
 This file is part of morgenlichtctl.

 Morgenlichtctl is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, version 3 of the License.
 morgenlichtctl is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with morgenlichtctl. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MORGENLICHTCTL_VARIOUS_H
#define MORGENLICHTCTL_VARIOUS_H
/**
 * @file protocol_utils.h
 * This file provides helpers for common protocol functionality and basic queries.
 */

#include "networking.h"
#include <string.h>

/**
 * Read and parse a response from the server.
 *
 * This will print out the warning if the server sent one,
 * parse the status code and payload, write the status code to the given char,
 * and allocate memory for the payload.
 *
 * @note The payload will have to be free'd by the caller, as it is dynamically allocated.
 *
 * @param  status  Address of a char to which to write the status code.
 * @param  payload Pointer to a char pointer that will point to the payload.
 *
 * @return 0 on success, or non-zero otherwise.
 */
int parse_response(char* status, char** payload);

/**
 * Print out some basic info about a morgenlichtd server.
 *
 * @param  hostname The hostname of the server
 *
 * @return 0 on success, or non-zero otherwise.
 */
int server_info(const char *const hostname);

#endif // MORGENLICHTCTL_VARIOUS_H
