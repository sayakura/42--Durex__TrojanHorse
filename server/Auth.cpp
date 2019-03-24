#include "Auth.h"

Auth::Auth(char* login, char *pw, bool enable)
	: auth_login(encrypt(login)), auth_pw(encrypt(pw)), auth_enabled(enable)
	{
		bzero(this->session_table, sizeof(this->session_table));
	};

LOGIN_STATUS
Auth::logining(int type, char *str, int i, Tintin_reporter &logger)
{
	if (!this->auth_enabled)
		return (LOGIN_NOT_ENABLED);
	if (this->session_table[i] == NULL)
	{
		this->session_table[i] = (t_session *)malloc(sizeof(t_session));
		this->session_table[i]->login = NULL;
		this->session_table[i]->pw = NULL;
		this->session_table[i]->is_login = false;
	}
	if (type == IS_LOGIN)
		this->session_table[i]->login = encrypt(str);
	else if (type == IS_PASSWORD)
		this->session_table[i]->pw = encrypt(str);
	if (this->session_table[i]->login != NULL &&
		this->session_table[i]->pw != NULL)
	{
		if ((strcmp(this->auth_login, this->session_table[i]->login) == 0)
			&& (strcmp(this->auth_pw, this->session_table[i]->pw) == 0))
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
	else
		return (LOGIN_WAIT);
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
	free(this->session_table[i]->login);
	free(this->session_table[i]->pw);
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
