#include <sys/xattr.h>
#include <stdio.h>
# include <unistd.h>

     #include <fcntl.h>
int	main(int ac, char **av)
{
	int fd = open(av[0], O_RDONLY);
	char buff[100];
	read(fd, buff, 100);
	puts(buff);
	return (0);
}
