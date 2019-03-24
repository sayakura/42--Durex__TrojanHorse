#ifndef DUREX_H

# define DUREX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <string.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <net/if.h>
# include <dirent.h>
# include <iostream>
# include <fstream>
# include <syslog.h>
# include <ctime>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>


int deamon(int ac, const char **av);

#endif
