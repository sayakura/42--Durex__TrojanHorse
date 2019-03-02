#include "./Tintin_reporter.h"

Tintin_reporter::Tintin_reporter(const char *logfile_path) {
	struct stat st;

	_logfile_path = logfile_path;
	logfile = fopen(logfile_path, "ab+");
}

void	Tintin_reporter::start(void){
	if (logfile && _logfile_path)
		fprintf(logfile, "[%s] [ INFO ] - Matt_daemon: Started.\n", this->getTime());
}

void	Tintin_reporter::info(const char *message){
	if (logfile && _logfile_path)
		fprintf(logfile, "[%s] [ INFO ] - Matt_daemon: %s\n", this->getTime(), message);
}

void	Tintin_reporter::log(const char *message){
	if (logfile && _logfile_path)
		fprintf(logfile, "[%s] [ INFO ] - Matt_daemon: %s\n", this->getTime(), message);
}

void	Tintin_reporter::error(const char *message){
	if (logfile && _logfile_path)
		fprintf(logfile, "[%s] [ INFO ] - Matt_daemon: %s\n", this->getTime(), message);
}

char	*Tintin_reporter::getTime()
{
	time_t		timer;
	static char	buffer[26];
	struct tm*	tm_info;

	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, "%d/%m/%Y-%H:%M:%S", tm_info);
	return buffer;
}

void	Tintin_reporter::quit(){
	if (logfile && _logfile_path)
		fprintf(logfile, "[%s] [ INFO ] - Matt_daemon: Quitting.\n", this->getTime());
}
