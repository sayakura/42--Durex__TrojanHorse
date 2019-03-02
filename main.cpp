#include <iostream>
#include <syslog.h>
#include <ctime>
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
	FILE* logfile = fopen("var/log/matt_daemon/matt-daemon.log", "ab+");
	fprintf(logfile, "[%s] [ INFO ] - Matt_daemon: Started", getTime());
	return 0;
}
