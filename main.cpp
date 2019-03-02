#include <iostream>
#include <syslog.h>
#include <ctime>
#include <sys/stat.h>
using namespace std;

char	*getTime()
{
	time_t timer;
    static char buffer[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%d/%m/%Y-%H:%M:%S", tm_info);
    return buffer;
}

int main() {
	struct stat st;
	if (stat("/var/log/matt_daemon", &st) == -1) {
    		mkdir("/var/log/matt_daemon", 0777);
	}   
	FILE* logfile = fopen("/var/log/matt_daemon/matt-daemon.log", "ab+");
	if (logfile)
		fprintf(logfile, "[%s] [ INFO ] - Matt_daemon: Started\n", getTime());
	else
		printf("I dont know what to say\n");
		
	return 0;
}
