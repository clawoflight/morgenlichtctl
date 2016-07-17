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

#include "networking.h"

/**
 * Print out some basic info about a morgenlichtd server.
 *
 * @param  hostname The hostname of the server
 *
 * @return 0 on success, or non-zero otherwise.
 */
int server_info(const char *const hostname);

#endif // MORGENLICHTCTL_VARIOUS_H
