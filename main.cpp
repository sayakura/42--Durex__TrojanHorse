#include "daemonize.h"
#include "server.h"
#include "Tintin_reporter.h"
#include "utils.h"

# define MAX_CLIENTS 3

const char *lock_path;
const char *log_path;
int g_port = 4242;

int		socket_setup_ip6(void)
{
	int					main_sock;
	struct sockaddr_in6	address;
	int					opt;

	opt = 1;
	if ((main_sock = socket(AF_INET6, SOCK_STREAM, 0)) == 0)
	{
		fprintf(stderr, "socket failed");
		exit(EXIT_FAILURE);
	}
	if (setsockopt(main_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,\
													sizeof(opt)) < 0)
	{
		fprintf(stderr, "setsocket failed");
		exit(EXIT_FAILURE);
	}
	address.sin6_family = AF_INET6;
	address.sin6_port = htons(g_port);
	address.sin6_addr = in6addr_any;
	bind(main_sock, (struct sockaddr *)&address, sizeof(address));
	return (main_sock);
}

void	handle_request(int *client_socks, fd_set *fd_list, Tintin_reporter &logger)
{
	int		offset;
	char	buf[1024];
	int 	sock;
	char 	*ptr;

	for (int i = 0; i < MAX_CLIENTS; i++)
		if (FD_ISSET(client_socks[i], fd_list))
		{
			bzero(buf, sizeof(buf));
			sock = client_socks[i];
			offset = 0;
			for(;;)
			{
				if (recv(sock, buf + offset, 1, 0) <= 0)
				{
					close(client_socks[i]);
					client_socks[i] = 0;
					break ;
				}
				if (*(buf + offset) == '\n')
					break ;
				offset++;
				if (offset >= 1023)
					break ;
			}
			if (strlen(buf))
			{
				*(buf + offset) = '\0';
				if (strcmp(buf, "quit") == 0)
				{
					logger.log(L_INFO, "Request quit.");
					logger.log(L_QUIT, NULL);
					unlock();
					exit(EXIT_SUCCESS);
				}
				ptr = strjoin("User input: ", buf);
				free(ptr);
				logger.log(L_LOG, ptr);
			}
			offset = 0;
		}
}

void	handle_connection(int master_s, fd_set *fd_list, int *client_socks, Tintin_reporter &logger)
{
	int					connected_s;
	struct sockaddr_in6	address;
	int					addrlen;

	if (FD_ISSET(master_s, fd_list))
	{
		if ((connected_s = accept(master_s,
			(struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
		{
			logger.log(L_ERROR, "Accept failed.");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < MAX_CLIENTS; i++)
			if (client_socks[i] == 0)
			{
				client_socks[i] = connected_s;
				break ;
			}
	}
}

void	run_serser(int master_sock, Tintin_reporter &logger)
{
	fd_set	fd_list;
	int		max_sock;
	int		i;
	int		client_socks[MAX_CLIENTS];

	bzero(client_socks, sizeof(client_socks));
	while (1)
	{
		i = -1;
		FD_ZERO(&fd_list);
		FD_SET(master_sock, &fd_list);
		max_sock = master_sock;
		while (++i < MAX_CLIENTS)
		{
			if (client_socks[i] > 0)
				FD_SET(client_socks[i], &fd_list);
			if (client_socks[i] > max_sock)
				max_sock = client_socks[i];
		}
		if (select(max_sock + 1, &fd_list, NULL, NULL, NULL) < 0)
		{
			logger.log(L_ERROR, "Select failed.");
			exit(EXIT_FAILURE);
		}
		handle_connection(master_sock, &fd_list, client_socks, logger);
		handle_request(client_socks, &fd_list, logger);
	}
}

int		create_server(Tintin_reporter &logger)
{
	int		master_sock;

	master_sock = socket_setup_ip6();
	if (listen(master_sock, 3) < 0)
	{
		logger.log(L_ERROR, "Listen failed.");
		exit(EXIT_FAILURE);
	}
	return (master_sock);
}

void	lock_checking(Tintin_reporter &logger)
{
	int		fd;


	fd = open(lock_path, O_RDWR|O_CREAT, 0640);
	if (fd < 0)
	{
		logger.log(L_ERROR, "Error can't create lockfile.");
		logger.log(L_QUIT, NULL);
		exit(EXIT_FAILURE);
	}
	if (lockf(fd, F_TLOCK, 0) < 0)
	{
		logger.log(L_ERROR, "Error file locked.");
		logger.log(L_QUIT, NULL);
		exit(EXIT_FAILURE);
	}
}

int		main(int ac, char **av)
{
	int				master_sock;
	char			str[256];
	Tintin_reporter	logger;

	if (ac > 1) {
		log_path = av[1];
		lock_path = av[2];
	} else {
		log_path = "./Matt_Daemon.log";
		lock_path = "./lock";
	}

	daemonize(logger);
	logger.init(log_path);
	logger.log(L_START, NULL);
	lock_checking(logger);
	logger.log(L_INFO, "Creating server.");
	master_sock = create_server(logger);
	logger.log(L_INFO, "Server created.");
	logger.log(L_INFO, "Entering Daemon mode.");
	sprintf(str, "started. PID: %d.", getpid());
	logger.log(L_INFO, str);
	run_serser(master_sock, logger);
	logger.log(L_QUIT, NULL);
	return (0);
}
