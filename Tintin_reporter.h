
#ifndef TINTIN_REPORTER

# define TINTIN_REPORTER
# include <iostream>
# include <fstream>
# include <syslog.h>
# include <ctime>
# include <sys/stat.h>

using namespace std;

class Tintin_reporter
{
	private:
		const char	*_logfile_path;
	public:
		void 	init(const char *);
		void	start(void);
		void 	log(const char*);
		void 	info(const char*);
		void 	error(const char*);
		void	quit();
		char	*getTime();
};
#endif
