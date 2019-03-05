
#include "client.h"
#include "../server/encrypt.h"

bool encryption_mode = 0;
bool authtication_mode = 0;

int
ip_version(const char *src)
{
	char buf[16];

	if (inet_pton(AF_INET, src, buf))
		return (4);
	else if (inet_pton(AF_INET6, src, buf))
		return (6);
	return (-1);
}


char
get_char(void)
{
	char buff[1];

	read(0, buff, 1);
	return (buff[0]);
}

char
*get_input(void)
{
	int			i;
	static char	buf[101];

	i = 0;
	bzero(buf, sizeof(buf));
	write(1, "> ", 2);
	while (i <= 100 && ((buf[i++] = get_char()) != '\n'))
		;
	if (i >= 100)
	{
		bzero(buf, sizeof(buf));
		printf("%s» Can't read more than 100 char characters.%s\n", RED, RESET);
		get_input();
	}
	return (buf);
}

int
prompt(int sock)
{
	char		*buf;
	char		msg[50];
	int 		len;
	static int	is_authenticated;
	int			will_quit;

	will_quit = 0;
	buf = get_input();
	if((len = strlen(buf)))
	{
		if ((strncmp(buf, "quit", 4)) == 0)
			will_quit = 1;
		if (encryption_mode == 1)
			encrypt(buf);
		send(sock, buf, len, 0);
		if (!is_authenticated && authtication_mode)
		{
			recv(sock, msg, 50, 0);
				if (encryption_mode)
			decrypt(msg, 1);
			if (strcmp(msg, "Authentication successed!\n") == 0)
				is_authenticated = 1;
			printf("%s", msg);
		}
		if (will_quit)
		{
			close(sock);
			exit(EXIT_SUCCESS);
		}
	}
	else
		printf("%s» Command not found: %s%s\n", RED, buf, RESET);
	return (1);
}

int
socket_setup_6(char *host, int port)
{
	int					s;
	struct sockaddr_in6	addr;

	printf("%s» Using IP6...%s\n", GREEN, RESET);
	s = socket(AF_INET6, SOCK_STREAM, 0);
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(port);
	inet_pton(AF_INET6, host, &addr.sin6_addr);
	if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		printf("\x1b[31m» Connection Failed. \n\x1b[0m");
		exit(EXIT_FAILURE);
	}
	return (s);
}

void
socket_setup(char *host, int port)
{
	int					sock;
	struct sockaddr_in	servaddr;

	if (strcmp(host, "localhost") == 0)
		host = (char *)"127.0.0.1";
	printf("\x1b[33mConnecting...\x1b[0m %s %d\n", host, port);
	if (ip_version(host) == 4)
	{
		printf("%s» Using IP4...%s\n", GREEN, RESET);
		sock = socket(AF_INET, SOCK_STREAM, 0);
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = inet_addr(host);
		servaddr.sin_port = htons(port);
		if (connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		{
			printf("\x1b[31m» Connection Failed. \n\x1b[0m");
			exit(EXIT_FAILURE);
		}
	}
	else
		sock = socket_setup_6(host, port);
	while (1)
		if (!prompt(sock))
			break ;
	close(sock);
}

int
main(int ac, char **av)
{
	if (ac < 3)
	{
		printf("\x1b[31m» Need to specify the ip and the port.\n\x1b[0m");
		exit(EXIT_FAILURE);
	}
	if (ac > 3)
		for (int i = 0; i < ac; i++)
			if (strcmp(av[i], "-e") == 0)
				encryption_mode = 1;
	if (ac > 3)
		for (int i = 0; i < ac; i++)
			if (strcmp(av[i], "-a") == 0)
				authtication_mode = 1;

	printf("%s================================================\n", MAGENTA);
	printf("|                                              |\n");
	printf("|                  Ben_AFK                     |\n");
	printf("|                                              |\n");
	printf("|                                              |\n");
	printf("|              - Daemon Client -               |\n");
	printf("|                                              |\n");
	printf("================================================\n%s", RESET);
	socket_setup(av[1], atoi(av[2]));
	return (0);
}
