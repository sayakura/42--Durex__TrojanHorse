#include "encrypt.h"

void	decrypt(char *msg, int client)
{
	int len;

	len = strlen(msg) - client;
	for (int i = 0; i < len; i++)
		msg[i] -= 42;
}

void
encrypt(char *msg)
{
	int len;

	len = strlen(msg) - 1;
	for (int i = 0; i < len; i++)
		msg[i] += 42;
}
