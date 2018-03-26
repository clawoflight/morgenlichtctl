#ifndef MORGENLICHTCTL_VARIOUS_H
#define MORGENLICHTCTL_VARIOUS_H
/**
 * @file protocol_utils.h
 * This file provides helpers for common protocol functionality and basic queries.
 */

#define _GNU_SOURCE
#include "networking.h"
#include <string.h>
#include <stdlib.h>

/**
 * Basic alarm commands.
 */
enum AlarmCmd {AlarmEnable, AlarmDisable, AlarmDelete};

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
 * @param  port     The port of the server
 *
 * @return 0 on success, or non-zero otherwise.
 */
int server_info(const char *const hostname, const int port);

/**
 * Directly set the LEDs.
 *
 * @param  hostname The hostname of the server
 * @param  port     The port of the server
 * @param  r1       Red channel 1 value
 * @param  r2       Red channel 2 value
 * @param  g1       Green channel 1 value
 * @param  g2       Green channel 2 value
 * @param  b1       Blue channel 1 value
 * @param  b2       Blue channel 2 value
 *
 * @return 0 on success, or non-zero otherwise
 */
int leds_set(const char *const hostname, const int port, int r1, int r2, int g1, int g2, int b1, int b2);

/**
 * Perform the most basic alarm commands.
 *
 * These only require the profile name as argument and return success or failure,
 * which makes them specially simple to implement.
 *
 * @param  hostname The hostname of the server
 * @param  port     The port of the server
 * @param  profile  The alarm profile to act upon
 * @param  cmd      The command to execute
 *
 * @return 0 on success, or non-zero otherwise.
 */
int alarm_basic_cmd(const char *const hostname, const int port, const char *const profile, enum AlarmCmd cmd);

/**
 * List all alarms on the server.
 *
 * @param  hostname         The hostname of the server
 * @param  port             The port of the server
 * @param  machine_readable Whether to use a machine_readable representation
 *
 * @return 0 on success, or non-zero otherwise.
 */
int alarm_list(const char *const hostname, const int port, const int machine_readable);

/**
 * Add a new alarm or update an existing one.
 *
 * @param  hostname    The hostname of the server
 * @param  port        The port of the server
 * @param  profile     The alarm profile to create or overwrite
 * @param  hour        The trigger hour
 * @param  minute      The trigger minute
 * @param  second      The trigger second
 * @param  active_days The days on which the profile is active
 * @param  color       The color profile
 * @param  sound       The sound file
 *
 * @return 0 on success, or non-zero otherwise.
 */
int alarm_add(const char *const hostname, const int port, const char* const profile,
    const int hour, const int minute, const int second,
    const char* const active_days, const char* const color, const char* const sound);

#endif // MORGENLICHTCTL_VARIOUS_H
