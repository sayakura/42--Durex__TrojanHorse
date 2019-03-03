
#include "daemonize.h"
#include "Tintin_reporter.h"
#define lock_path "./var/lock/matt_daemon.lock"

void daemonize(Tintin_reporter &logger)
{
	pid_t pid = 0;
	int fd;

	pid = fork();
	if (pid < 0) {
		exit(EXIT_FAILURE);
	}
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}
	if (setsid() < 0) {
		exit(EXIT_FAILURE);
	}
	signal(SIGCHLD, SIG_IGN);
	pid = fork();

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	umask(0);
	// chdir("/");
	for (fd = sysconf(_SC_OPEN_MAX); fd > 0; fd--) {
		close(fd);
	}

	stdin = fopen("/dev/null", "r");
	stdout = fopen("/dev/null", "w+");
	stderr = fopen("/dev/null", "w+");

	logger.init("./matt-daemon.log");
	logger.start();
	int pid_fd = open(lock_path, O_RDWR|O_CREAT, 0640);
	if (pid_fd < 0) {
		logger.error("Error can't create lockfile.");
		logger.quit();
		exit(EXIT_FAILURE);
	}
	if (lockf(pid_fd, F_TLOCK, 0) < 0) {
		logger.error("Error file locked.");
		logger.quit();
		exit(EXIT_FAILURE);
	}
}

void	unlock()
{
	unlink(lock_path);
}

void	log_signal(int sig)
{
	Tintin_reporter logger;

	logger.info("Signal handler");
	logger.quit();
	unlock();
	exit(EXIT_SUCCESS);
}
