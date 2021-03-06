#include "cli.h"

void init_argtable()
{
    /* Initialise the option structs */
    help = arg_lit0("h", "help", "Print help and exit.");
    version = arg_lit0("v", "version", "Print version and exit.");
    end0 = arg_end(15);

    cmd1 = arg_rex1(NULL, NULL, "alarm", NULL, REG_ICASE, NULL);
    list = arg_rex1(NULL, NULL, "list", NULL, REG_ICASE, NULL);
    csv = arg_lit0(NULL, "csv", "Use machine-readable CSV format.");
    end1 = arg_end(15);

    cmd2 = arg_rex1(NULL, NULL, "alarm", NULL, REG_ICASE, NULL);
    cmd2b = arg_rex1(NULL, NULL, "enable", NULL, REG_ICASE, NULL);
    enable_alarm_name = arg_str1(NULL, NULL, "<ALARM>", "The alarm to enable");
    end2 = arg_end(15);

    cmd3 = arg_rex1(NULL, NULL, "alarm", NULL, REG_ICASE, NULL);
    cmd3b = arg_rex1(NULL, NULL, "disable", NULL, REG_ICASE, NULL);
    disable_alarm_name = arg_str1(NULL, NULL, "<ALARM>", "The alarm to disable");
    end3 = arg_end(15);

    cmd6 = arg_rex1(NULL, NULL, "alarm", NULL, REG_ICASE, NULL);
    cmd6b = arg_rex1(NULL, NULL, "delete", NULL, REG_ICASE, NULL);
    delete_alarm_name = arg_str1(NULL, NULL, "<ALARM>", "The alarm to delete");
    end6 = arg_end(15);

    cmd4 = arg_rex1(NULL, NULL, "alarm", NULL, REG_ICASE, NULL);
    cmd4b = arg_rex1(NULL, NULL, "add", NULL, REG_ICASE, NULL);
    alarm_time = arg_date1(NULL, NULL, "%H:%M:%S", "<HH:MM:SS>", "The ringing time");
    alarm_name = arg_str1("n", "name", "<ALARM>", "The name of the alarm");
    days = arg_rex1("d", "days", "^(Mon)?(Tue)?(Wed)?(Thu)?(Fri)?(Sat)?(Sun)?$", "DayDay", REG_ICASE | REG_EXTENDED,
        "The weekdays at which the alarm is enabled. String of MonTueWedThuFriSatSun.");
    color_profile = arg_str0("c", "color", "<COLOR>", "The color profile to use.");
    sound_file = arg_str0("s", "sound", "<SOUND>", "The sound to play");
    end4 = arg_end(15);

    cmd5 = arg_rex1(NULL, NULL, "server-info", NULL, REG_ICASE, NULL);
    end5 = arg_end(15);

    cmd7 = arg_rex1(NULL, NULL, "set-leds", NULL, REG_ICASE, NULL);
    led_r1 = arg_int1(NULL, NULL, "R1", "Red channel 1 value (0-255)");
    led_r2 = arg_int1(NULL, NULL, "R2", "Red channel 2 value (0-255)");
    led_g1 = arg_int1(NULL, NULL, "G1", "Green channel 1 value (0-255)");
    led_g2 = arg_int1(NULL, NULL, "G2", "Green channel 2 value (0-255)");
    led_b1 = arg_int1(NULL, NULL, "B1", "Blue channel 1 value (0-255)");
    led_b2 = arg_int1(NULL, NULL, "B2", "Blue channel 2 value (0-255)");
    end7 = arg_end(15);
}
