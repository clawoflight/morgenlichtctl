AM_CFLAGS = --pedantic -g -Wall -Wextra -std=c99 -O2 -fstack-protector-strong

bin_PROGRAMS = morgenlichtctl

morgenlichtctl_SOURCES = morgenlichtctl.c cli.c cli.h networking.c networking.h alarm.c alarm.h
morgenlichtctl_LDADD = -largtable2 -lSDL2_net
