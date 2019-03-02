#include <iostream>
#include <fstream>
#include <syslog.h>
#include <ctime>
#include <sys/stat.h>
using namespace std;

class Tintin_reporter{
	private:
		FILE* 		logfile;
		const char	*_logfile_path;
	public:
		Tintin_reporter(const char *);
		void	start(void);
		void 	log(const char*);
		void 	info(const char*);
		void 	error(const char*);
		void	quit();
		char	*getTime();
};
