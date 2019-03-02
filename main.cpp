#include "Tintin_reporter.h"
#include "server.h"

int		main() {

	Tintin_reporter logger("./var/log/matt_daemon/matt-daemon.log");
	logger.start();
	create_server(&logger);
	logger.quit();
	return 0;
}
