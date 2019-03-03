#include "Tintin_reporter.h"
#include "utils.h"

FILE* 		logfile;

void	Tintin_reporter::init(const char *logfile_path)
{
	_logfile_path = logfile_path;
	logfile = fopen(logfile_path, "ab+");
	if (!logfile)
	{
		fprintf(stderr, "Can't open log file.\n");
		exit(EXIT_FAILURE);
	}
	setvbuf (logfile, NULL, _IONBF, 0);
}

void	Tintin_reporter::log(LOG_TYPE type, const char *message)
{
	if (!logfile || !_logfile_path)
		fprintf(stderr, "Logfile path not initialized.\n");
	switch(type)
	{
		case L_START:
			fprintf(logfile, "[%s] [ INFO ] - Matt_daemon: Started.\n", getTime());
			return ;
		case L_QUIT:
			fprintf(logfile, "[%s] [ INFO ] - Matt_daemon: Quitting.\n", getTime());
			fclose(logfile);
			return ;
		default:
			fprintf(logfile, "[%s] [ %s ] - Matt_daemon: %s\n", getTime(), type_labels[type], message);
	}
}
