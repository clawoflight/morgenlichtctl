#ifndef MORGENLICHTCTL_CLI_H
#define MORGENLICHTCTL_CLI_H
/**
* @file cli.h
* This file describes the command-line parameters for morgenlichtctl.
*/
#include <argtable2.h>
#include <sys/types.h>
#include <regex.h>

/**
 * Initialises all of the structs used by argtable.
 *
 * This effectively configures the behavior of the CLI.
 */
void init_argtable();

/* SYNTAX: --help | --version */
struct arg_lit* help;
struct arg_lit* version;
struct arg_end* end0;
int arg_errors0;

/* SYNTAX: alarm list */
struct arg_rex* cmd1;
struct arg_rex* list;
struct arg_end* end1;
int arg_errors1;

/* SYNTAX: alarm enable PROFILE */
struct arg_rex* cmd2;
struct arg_rex* cmd2b;
struct arg_str* enable_alarm_name;
struct arg_end* end2;
int arg_errors2;

/* SYNTAX: alarm disable PROFILE */
struct arg_rex* cmd3;
struct arg_rex* cmd3b;
struct arg_str* disable_alarm_name;
struct arg_end* end3;
int arg_errors3;

/* SYNTAX: alarm delete PROFILE */
struct arg_rex* cmd6;
struct arg_rex* cmd6b;
struct arg_str* delete_alarm_name;
struct arg_end* end6;
int arg_errors6;

/* SYNTAX: alarm add TIME --name NAME --color-profile PROFILE --sound-file SOUND --days DayDay */
struct arg_rex* cmd4;
struct arg_rex* cmd4b;
struct arg_date* alarm_time;
struct arg_str* alarm_name;
struct arg_str* color_profile;
struct arg_str* sound_file;
struct arg_rex* days;
struct arg_end* end4;
int arg_errors4;

/* SYNTAX: server-info */
struct arg_rex* cmd5;
struct arg_end* end5;
int arg_errors5;

#endif // MORGENLICHTCTL_CLI_H
