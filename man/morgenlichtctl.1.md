# morgenlichtctl 1 "July 2016" morgenlichtctl "User Manual"

# NAME

morgenlichtctl - command-line client for morgenlichtd

# SYNOPSIS

**morgenlichtctl** [-hv]

**morgenlichtctl** server-info

**morgenlichtctl** alarm list

**morgenlichtctl** alarm enable|disable <ALARM>

**morgenlichtctl** alarm add <HH:MM:SS> -n <ALARM> -d DayDay [-c <COLOR>] [-s <SOUND>]

# DESCRIPTION

Manage alarms on a **morgenlicht**(7) system.

 -h, --help                Print help and exit.

 -v, --version             Print version and exit.

 enable|disable <ALARM>    Enable or disable an alarm.

 <HH:MM:SS>                The ringing time of the alarm

 -n, --name=<ALARM>        The name of the alarm

 -d, --days=DayDay         The weekdays at which the alarm is enabled. String of Mon Tue Wed etc. in order.

 -c, --color=<COLOR>       The color profile to use.

 -s, --sound=<SOUND>       The sound to play

# EXAMPLES

Disable an alarm:

```
morgenlichtctl alarm disable "my old alarm"
```

Add a new alarm:

```
morgenlichtctl alarm add 06:30:00 -n "my alarm" -d MonWedFri
```

# ENVIRONMENT VARIABLES

**MORGENLICHT_SERVER** Override "localhost" as the server to use.

# AUTHORS

Written by Bennett Piater and Andreas Postel.

Soli Deo Gloria!

# REPORTING BUGS

File an issue at http://github.com/ClawOfLight/morgenlichtctl

# COPYRIGHT

Copyright © 2016 Bennett Piater. Licensed GPLv3: GNU GPL version 3 http://gnu.org/licenses/gpl.html
This is free software: you are welcome to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

# SEE ALSO

**morgenlichtd**(1), **morgenlicht**(7)
