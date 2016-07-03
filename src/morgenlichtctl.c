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
#include "cli.h"
#include "networking.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void cleanup(int count, ...);

int main(int argc, char *argv[])
{
    // Init the structs for argtable
    init_argtable();

    /* Create the alternative syntaxes */
    void* argtable0[] = {help, version, end0};
    void* argtable1[] = {cmd1, list, end1};
    void* argtable2[] = {cmd2, cmd2b, enable_alarm_name, end2};
    void* argtable3[] = {cmd3, cmd3b, disable_alarm_name, end3};
    void* argtable4[] = {cmd4, cmd4b, alarm_time, alarm_name, color_profile, sound_file, days, end4};

    /* Check for problems */
    if (arg_nullcheck(argtable0) ||
        arg_nullcheck(argtable1) ||
        arg_nullcheck(argtable2) ||
        arg_nullcheck(argtable3) ||
        arg_nullcheck(argtable4))
    {
        fprintf(stderr, "error: insufficient memory\n");
        exit(EXIT_FAILURE);
    }

    /* Do the actual parsing and count the resulting errors */
    arg_errors0 = arg_parse(argc, argv, argtable0);
    arg_errors1 = arg_parse(argc, argv, argtable1);
    arg_errors2 = arg_parse(argc, argv, argtable2);
    arg_errors3 = arg_parse(argc, argv, argtable3);
    arg_errors4 = arg_parse(argc, argv, argtable4);

    // TODO: Init TCP connection

    /* Work and handle errors */
    if (arg_errors0 == 0)
        ; // TODO: Perform the corresponding action
    else if (arg_errors1 == 0)
        ; // TODO: Perform the corresponding action
    else if (arg_errors2 == 0)
        ; // TODO: Perform the corresponding action
    else if (arg_errors3 == 0)
        ; // TODO: Perform the corresponding action
    else if (arg_errors4 == 0)
        ; // TODO: Perform the corresponding action
    // No command was correct
    // TODO: find the syntax with the least errors and show those
    else {
        //arg_print_errors(stdout, end1, argv[0]);
        printf("usage 0: %s ", argv[0]); arg_print_syntaxv(stdout, argtable0, "\n");
        printf("usage 1: %s ", argv[0]); arg_print_syntaxv(stdout, argtable1, "\n");
        printf("usage 2: %s ", argv[0]); arg_print_syntaxv(stdout, argtable2, "\n");
        printf("usage 3: %s ", argv[0]); arg_print_syntaxv(stdout, argtable3, "\n");
        printf("usage 4: %s ", argv[0]); arg_print_syntaxv(stdout, argtable4, "\n");
    }

    /* Clean up :) */
    cleanup(5, argtable0, argtable1, argtable2, argtable3, argtable4);

    return EXIT_SUCCESS;
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

    // TODO: close TCP connection
}
