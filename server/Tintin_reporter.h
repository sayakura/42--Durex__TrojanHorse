
#ifndef TINTIN_REPORTER

# define TINTIN_REPORTER

# include <iostream>
# include <fstream>
# include <syslog.h>
# include <ctime>
# include <sys/stat.h>

using namespace std;

enum LOG_TYPE
{
	L_START,
	L_INFO,
	L_ERROR,
	L_LOG,
	L_QUIT
};

const static char *type_labels[5] = {
	NULL,
	"INFO",
	"ERROR",
	"LOG",
	NULL
};

class Tintin_reporter
{
	private:
		const char	*_logfile_path;
	public:
		void 	log(LOG_TYPE, const char *);
		void 	init(const char *);
};

#endif
