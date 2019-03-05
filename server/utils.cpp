# include "utils.h"

char
*getTime(void)
{
	time_t		timer;
	static char	buffer[26];
	struct tm*	tm_info;

	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, "%d/%m/%Y-%H:%M:%S", tm_info);
	return buffer;
}

char
*strjoin(const char *s1, const char *s2)
{
	char*		result;

	result = (char *)malloc(strlen(s1) + strlen(s2) + 1);
	if (result)
	{
		strcpy(result, s1);
		strcat(result, s2);
	}
	return result;
}
