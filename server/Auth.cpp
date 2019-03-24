#include "Auth.h"

Auth::Auth(char* keycode, bool enable)
	: keycode(encrypt(keycode)), auth_enabled(enable)
	{
		bzero(this->session_table, sizeof(this->session_table));
	};

LOGIN_STATUS
Auth::logining(char *str, int i, Tintin_reporter &logger)
{
	if (!this->auth_enabled)
		return (LOGIN_NOT_ENABLED);
	if (this->session_table[i] == NULL)
	{
		this->session_table[i] = (t_session *)malloc(sizeof(t_session));
		this->session_table[i]->keycode = NULL;
		this->session_table[i]->is_login = false;
	}
	this->session_table[i]->keycode = encrypt(str);
	if (strcmp(this->keycode, this->session_table[i]->keycode) == 0)
	{
		this->session_table[i]->is_login = true;
		return (LOGIN_PASSED);
	}
	else
	{
		free(this->session_table[i]);
		this->session_table[i] = NULL;
		return (LOGIN_FAILED);
	}
}

bool
Auth::is_logined(int i)
{
	if (!this->auth_enabled)
		return (false);
	if (this->session_table[i] == 0)
		return (false);
	return this->session_table[i]->is_login;
}

void
Auth::loggout(int i)
{
	if (!this->auth_enabled)
		return ;
	if (this->session_table[i] == 0)
		return ;
	free(this->session_table[i]->keycode);
	free(this->session_table[i]);
	this->session_table[i] = 0;
}

bool
Auth::is_enable(void)
{
	return this->auth_enabled;
}

char
*Auth::encrypt(char *input)
{
	FILE 		*fp;
	char		*path;
	char		str[256];

	path = (char *)malloc(sizeof(char) * 1024);
	sprintf(str, "echo %s | shasum -a 256", input);
	fp = popen(str, "r");
	if (fp == NULL)
		printf("Failed to run command\n");
	if (fgets(path, 1024, fp) != NULL)
	{
		pclose(fp);
		return path;
	}
	return (NULL) ;
}
