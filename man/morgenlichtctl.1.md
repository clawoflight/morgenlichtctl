% MORGENLICHTCTL(1) MorgenLicht user manuals
% Andreas Postel and Bennett Piater
% December 19, 2016

# NAME
morgenlichtctl - command-line client for morgenlichtd

# SYNOPSIS
**morgenlichtctl** [-hv]

**morgenlichtctl** server-info

**morgenlichtctl** alarm list

**morgenlichtctl** alarm enable|disable|delete *ALARM*

**morgenlichtctl** alarm add *HH:MM:SS* -n *ALARM* -d *DayDay* [-c *COLOR*] [-s *SOUND*]

# DESCRIPTION
Manage alarms on a **morgenlicht**(7) system.

# OPTIONS
Mandatory options for long options are mandatory for short options too.

-h, --help
: Print help and exit.

-v, --version
: Print version and exit.

enable|disable|delete *ALARM*
: Enable, disable or delete an alarm.

*HH:MM:SS*
: The ringing time of the alarm

-n, --name=*ALARM*
: The name of the alarm

-d, --days=*DayDay*
: The weekdays at which the alarm is enabled. String of Mon Tue Wed etc. in order.

-c, --color=*COLOR*
: The color profile to use.

-s, --sound=*SOUND*
: The sound to play

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
MORGENLICHT_SERVER
: Override "localhost" as the server to use.

# AUTHORS
Written by Bennett Piater and Andreas Postel.

Soli Deo Gloria!

# REPORTING BUGS
File an issue at http://github.com/ClawOfLight/morgenlichtctl

# COPYRIGHT
Copyright © 2016 Bennett Piater. Licensed BSD 3-Clause: https://opensource.org/licenses/BSD-3-Clause
This is free software: you are welcome to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

# SEE ALSO
**morgenlichtd**(1), **morgenlicht**(7)
