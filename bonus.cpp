#include "bonus.h"

extern Auth	g_auth;
extern const char	*g_log_path;

void
authentication_setup(int ac, char **av)
{
	int		i;
	char	*login_and_pw[2];
	char	*token;

	if (ac < 2)
		return ;

	for (i = 1; i < ac; i++)
		if (strcmp("-a", av[i]) == 0)
			break ;
	if (i >= ac - 1)
		return ;
	token = strtok(av[i + 1], ":");
	i = 0;
	while (token != NULL)
	{
		login_and_pw[i++] = strdup(token);
		token = strtok(NULL, ":");
	}
	if (login_and_pw[0] == NULL || login_and_pw[1] == NULL)
	{
		fprintf(stderr, "Invalid parameter format.\n");
		::exit(EXIT_FAILURE);
	}
	g_auth = Auth(login_and_pw[0], login_and_pw[1], true);
	free(login_and_pw[0]);
	free(login_and_pw[1]);
}

void
g_log_path_setup(int ac, char **av)
{
	int		i;
	int		found;

	found = 0;
	if (ac < 2)
		return ;
	for (i = 1; i < ac; i++)
		if (strcmp("-p", av[i]) == 0)
		{
			found = 1;
			break ;
		}
	if (found && i + 1 < ac)
		g_log_path = av[i + 1];
}

void
setup(int ac, char **av)
{
	int i;

	for (i = 1; i < ac; i++)
	if (strcmp("-h", av[i]) == 0)
	{
		printf("Usage: make [options] [parameters] ...\n");
		printf("Options:\n");
		printf("  -h                         Print this menu.\n");
		printf("  -p                         Path for the log file.\n");
		printf("  -a                         Enable authentication, enter login and password seperated by ':' \n");
		exit(EXIT_SUCCESS);
	}
	g_log_path_setup(ac, av);
	authentication_setup(ac, av);
}
