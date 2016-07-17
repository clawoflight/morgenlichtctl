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
#include "cli.h"

void init_argtable()
{
    /* Initialise the option structs */
    help = arg_lit0("h", "help", "Print help and exit.");
    version = arg_lit0("v", "version", "Print version and exit.");
    end0 = arg_end(15);

    cmd1 = arg_rex1(NULL, NULL, "alarm", NULL, REG_ICASE, NULL);
    list = arg_rex1(NULL, NULL, "list", NULL, REG_ICASE, NULL);
    end1 = arg_end(15);

    cmd2 = arg_rex1(NULL, NULL, "alarm", NULL, REG_ICASE, NULL);
    cmd2b = arg_rex1(NULL, NULL, "enable", NULL, REG_ICASE, NULL);
    enable_alarm_name = arg_str1(NULL, NULL, "<ALARM>", "The alarm to enable");
    end2 = arg_end(15);

    cmd3 = arg_rex1(NULL, NULL, "alarm", NULL, REG_ICASE, NULL);
    cmd3b = arg_rex1(NULL, NULL, "disable", NULL, REG_ICASE, NULL);
    disable_alarm_name = arg_str1(NULL, NULL, "<ALARM>", "The alarm to disable");
    end3 = arg_end(15);

    cmd4 = arg_rex1(NULL, NULL, "alarm", NULL, REG_ICASE, NULL);
    cmd4b = arg_rex1(NULL, NULL, "add", NULL, REG_ICASE, NULL);
    alarm_time = arg_date1(NULL, NULL, "%H:%M:%S", "<HH:MM:SS>", "The ringing time");
    alarm_name = arg_str1("n", "name", "<ALARM>", "The name of the alarm");
    days = arg_rex1("d", "days", "^(Mon)?(Tue)?(Wed)?(Thu)?(Fri)?(Sat)?(Sun)?$", "DayDay", REG_ICASE | REG_EXTENDED, "The weekdays at which the alarm is enabled. String of MonTueWedThuFriSatSun.");
    color_profile = arg_str0("c", "color", "<COLOR>", "The color profile to use.");
    sound_file = arg_str0("s", "sound", "<SOUND>", "The sound to play");
    end4 = arg_end(15);

    cmd5 = arg_rex1(NULL, NULL, "server-info", NULL, REG_ICASE, NULL);
    end5 = arg_end(15);
}
