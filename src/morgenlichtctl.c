#ifndef VERSION
#define VERSION "unknown" ///< VERSION is normally set by autoconf
#endif
/**
 * @file morgenlichtctl.c
 * The primary file. This produces the command-line program.
 */

#include "cli.h"
#include "protocol_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

static void cleanup(int count, ...);

/**
 * The entry point.
 *
 * @param  argc number of arguments
 * @param  argv argument array
 *
 * @return      0 on success, and 1 otherwise.
 */
int main(int argc, char *argv[])
{
    // Init the structs for argtable
    init_argtable();

    /* Create the alternative syntaxes */
    void* argtable0[] = {help, version, end0};
    void* argtable1[] = {cmd1, list, end1};
    void* argtable2[] = {cmd2, cmd2b, enable_alarm_name, end2};
    void* argtable3[] = {cmd3, cmd3b, disable_alarm_name, end3};
    void* argtable4[] = {cmd4, cmd4b, alarm_time, alarm_name, days, color_profile, sound_file, end4};
    void* argtable5[] = {cmd5, end5};
    void* argtable6[] = {cmd6, cmd6b, delete_alarm_name, end6};
    void* argtable7[] = {cmd7, led_r1, led_r2, led_g1, led_g2, led_b1, led_b2, end7};

    /* Check for problems */
    if (arg_nullcheck(argtable0) ||
        arg_nullcheck(argtable1) ||
        arg_nullcheck(argtable2) ||
        arg_nullcheck(argtable3) ||
        arg_nullcheck(argtable4) ||
        arg_nullcheck(argtable5) ||
        arg_nullcheck(argtable6) ||
        arg_nullcheck(argtable7))
    {
        fprintf(stderr, "error: insufficient memory\n");
        exit(EXIT_FAILURE);
    }

    char* hostname;
    char* env_port;
    int port;
    if ((hostname = getenv("MORGENLICHT_SERVER")) == NULL)
        hostname = "localhost";
    if ((env_port = getenv("MORGENLICHT_PORT")) == NULL
       || (port = atoi(env_port)) == 0)
        port = 4242;

    /* Do the actual parsing and count the resulting errors */
    arg_errors0 = arg_parse(argc, argv, argtable0);
    arg_errors1 = arg_parse(argc, argv, argtable1);
    arg_errors2 = arg_parse(argc, argv, argtable2);
    arg_errors3 = arg_parse(argc, argv, argtable3);
    arg_errors4 = arg_parse(argc, argv, argtable4);
    arg_errors5 = arg_parse(argc, argv, argtable5);
    arg_errors6 = arg_parse(argc, argv, argtable6);
    arg_errors7 = arg_parse(argc, argv, argtable7);

    int status = EXIT_SUCCESS;
    /* Work and handle errors */
    if (version->count >0 || help->count >0) { // --help | --version

        if (version->count)
            printf("morgenlichtctl %s\n", VERSION);
        else {
            printf("usage: %s ", argv[0]);
            arg_print_syntax(stdout, argtable0, "\n");
            arg_print_glossary_gnu(stdout, argtable0);

            printf("\n%s", argv[0]);
            arg_print_syntax(stdout, argtable5, "\n");
            arg_print_glossary_gnu(stdout, argtable5);

            printf("\n%s ", argv[0]);
            arg_print_syntax(stdout, argtable1, "\n");
            arg_print_glossary_gnu(stdout, argtable1);

            printf("\n%s ", argv[0]);
            arg_print_syntax(stdout, argtable2, "\n");
            arg_print_glossary_gnu(stdout, argtable2);

            printf("\n%s ", argv[0]);
            arg_print_syntax(stdout, argtable3, "\n");
            arg_print_glossary_gnu(stdout, argtable3);

            printf("\n%s ", argv[0]);
            arg_print_syntax(stdout, argtable6, "\n");
            arg_print_glossary_gnu(stdout, argtable6);

            printf("\n%s ", argv[0]);
            arg_print_syntax(stdout, argtable4, "\n");
            arg_print_glossary_gnu(stdout, argtable4);

            printf("\n%s", argv[0]);
            arg_print_syntax(stdout, argtable7, "\n");
            arg_print_glossary_gnu(stdout, argtable7);
        }
    }
    else if (arg_errors1 == 0)
        status = alarm_list(hostname, port);
    else if (arg_errors2 == 0)
        status = alarm_basic_cmd(hostname, port, *enable_alarm_name->sval, AlarmEnable);
    else if (arg_errors3 == 0)
        status = alarm_basic_cmd(hostname, port, *disable_alarm_name->sval, AlarmDisable);
    else if (arg_errors4 == 0)
        status = alarm_add(hostname, port, *alarm_name->sval,
           alarm_time->tmval->tm_hour, alarm_time->tmval->tm_min, alarm_time->tmval->tm_sec,
           *days->sval, *color_profile->sval, *sound_file->sval);
    else if (arg_errors5 == 0)
        status = server_info(hostname, port);
    else if (arg_errors6 == 0)
        status = alarm_basic_cmd(hostname, port, *delete_alarm_name->sval, AlarmDelete);
    else if (arg_errors7 == 0)
        status = leds_set(hostname, port, *led_r1->ival, *led_r2->ival, *led_g1->ival, *led_g2->ival, *led_b1->ival, *led_b2->ival);

    // No command was correct: show the appropriate error message.
    else {
        if (cmd4b->count > 0)
            arg_print_errors(stderr, end4, argv[0]);
        else if (cmd3b->count > 0)
            arg_print_errors(stderr, end3, argv[0]);
        else if (cmd2b->count > 0)
            arg_print_errors(stderr, end2, argv[0]);
        else if (list->count > 0)
            arg_print_errors(stderr, end1, argv[0]);
        else if (cmd7->count > 0)
            arg_print_errors(stderr, end7, argv[0]);

        else { // morgenlichtctl was called without arguments
            fprintf(stderr, "usage: %s", argv[0]);
            arg_print_syntaxv(stderr, argtable0, "\n");
        }
        status = EXIT_FAILURE;
    }

    /* Clean up :) */
    cleanup(8, argtable0, argtable1, argtable2, argtable3, argtable4, argtable5, argtable6, argtable7);

    return status;
}

void cleanup(int count, ...)
{
    va_list arguments;
    va_start(arguments, count);

    for (int i = 0; i < count; ++i)
    {
        void** table = va_arg(arguments, void**);
        arg_freetable(table, sizeof(table)/sizeof(table[0]));
    }

    va_end(arguments);
}
