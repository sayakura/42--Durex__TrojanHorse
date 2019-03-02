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

	openlog("mat_daemon" , 0 , LOG_USER);
	syslog(LOG_INFO, "[%s] [ INFO ] - Matt_daemon: Started", getTime());
	//printf("[%s] [ INFO ] - Matt_daemon: \n", getTime());
	closelog();
	return 0;
}
