/* © 2015, 2016 Andreas Postel and Bennett Piater.
 This file is part of morgenlichtctl.
 morgenlichtctl is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 morgenlichtctl is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with morgenlichtctl.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MORGENLICHTCTL_ALARM_H
#define MORGENLICHTCTL_ALARM_H
/**
 * @file alarm.h
 * Implements the client-side of the MorgenLicht alarm protocol.
 */
#include "networking.h"
#include <stdbool.h>
#include <time.h>

/**
 * Lists all configured alarms on the given morgenlichtd server.
 *
 * @param  hostname The remote host
 *
 * @return          0 on success, 1 on error
 */
int alarm_list(const char* const hostname);

/**
 * Enables or disables the given alarm on the given morgenlichtd server.
 *
 * @param  hostname The remote host
 * @param  alarm_name The name of the alarm to enable
 * @param  enable Whether to enable or disable the alarm
 *
 * @return          0 on success, 1 on error
 */
int alarm_enable_disable(const char* const hostname, char* const a_name, bool enable);

/**
 * Adds a new alarm on the given morgenlichtd server.
 *
 * @param  hostname The remote host
 * @param  a_time   The time at which the new alarm should sound
 * @param  a_name   The name of the new alarm
 * @param  a_days   The days at which the new alarm should trigger
 * @param  a_color  The color profile (nullable)
 * @param  a_sound  The sound file (nullable)
 *
 * @return          0 on success, 1 on error
 */
int alarm_add(const char* const hostname,
              struct tm* const a_time,
              char* const a_name,
              const char* const a_days,
              const char* const a_color,
              const char* const a_sound);

#endif // MORGENLICHTCTL_ALARM_H
