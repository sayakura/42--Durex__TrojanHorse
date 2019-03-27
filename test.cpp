#include <sys/xattr.h>
#include <stdio.h>
int	main(int ac, char **av)
{
	setxattr(__FILE__, "virtus", "yes", 3, 0);
	perror("set");
	return (0);
}
