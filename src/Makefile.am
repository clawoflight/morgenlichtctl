AM_CFLAGS = -g -Wall -Wextra -std=gnu11 -O2 -fstack-protector-strong

bin_PROGRAMS = morgenlichtctl

morgenlichtctl_SOURCES = morgenlichtctl.c\
 cli.c cli.h\
 networking.c networking.h protocol_utils.c protocol_utils.h\
 alarm.c alarm.h

morgenlichtctl_LDADD = -largtable2
