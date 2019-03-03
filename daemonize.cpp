
#include "daemonize.h"
#include "Tintin_reporter.h"

extern const char *lock_path;
extern const  char *log_path;

void daemonize(Tintin_reporter &logger)
{
	pid_t pid = 0;
	int fd;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid > 0)
		exit(EXIT_SUCCESS);
	if (setsid() < 0)
		exit(EXIT_FAILURE);
	signal(SIGCHLD, SIG_IGN);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid > 0)
		exit(EXIT_SUCCESS);
	umask(0);
	// chdir("/");
	for (fd = sysconf(_SC_OPEN_MAX); fd > 0; fd--)
		close(fd);
	stdin = fopen("/dev/null", "r");
	stdout = fopen("/dev/null", "w+");
	stderr = fopen("/dev/null", "w+");
}

void	unlock()
{
	unlink(lock_path);
}

void	log_signal(int sig)
{
	Tintin_reporter logger;

	logger.log(L_INFO, "Signal handler");
	logger.log(L_QUIT, NULL);
	unlock();
	exit(EXIT_SUCCESS);
}
