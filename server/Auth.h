#ifndef AUTH_H
# define AUTH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tintin_reporter.h"

#define SESSION_TABLE_SIZE 20
#define IS_LOGIN 1
#define IS_PASSWORD 0

typedef struct	s_session
{
	char 	*login, *pw;
	bool	is_login;
}				t_session;

enum	LOGIN_STATUS
{
	LOGIN_WAIT,
	LOGIN_FAILED,
	LOGIN_PASSED,
	LOGIN_NOT_ENABLED
};

class Auth
{
	private:
		char			*auth_login;
		char			*auth_pw;
		t_session		*session_table[SESSION_TABLE_SIZE];
		bool			auth_enabled;
	public:
		Auth(void) { this->auth_enabled = false; };
		Auth(char*, char *, bool);
		LOGIN_STATUS	logining(int, char *, int, Tintin_reporter &);
		void			loggout(int);
		bool			is_logined(int);
		static char		*encrypt(char *);
		bool			login(char*, char *, int);
		bool			is_enable(void);
};
#endif
