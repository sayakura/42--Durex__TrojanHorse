
#ifndef DAEMONIZE_H
#define DAEMONIZE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

void 	daemonize(Tintin_reporter *logger);
void	log_signal(int sig);
void	unlock();
#endif
