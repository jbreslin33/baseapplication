#include "dreamSockLog.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

FILE *LogFile;

void StartLog(void)
{
	time_t current = time(NULL);

	if((LogFile = fopen("dreamSock.log", "w")) != NULL)
	{
		fprintf(LogFile, "Log file started %s", ctime(&current));
		
		fclose(LogFile);
	}

	if((LogFile = fopen("dreamSock.log", "a")) != NULL)
	{
	}
}

void StopLog(void)
{
	fclose(LogFile);
}

void LogString(const char *string, ...)
{
	char buf[1024];
	va_list ap;
	va_start(ap, string);
	size_t t = 1024;
	
vsprintf(buf,string,ap);
	va_end(ap);

	// Get current time and date
	time_t current = time(NULL);

	char timedate[64];
	size_t tt = 64;
char buf2[64];

ctime(&current);

	sprintf(timedate,"%s", ctime(&current));
	// Remove linefeed from time / date string
	int i = 0;

	while(timedate[i] != '\n')
	{
		i++;
	}

	timedate[i] = '\0';

	// Linux outputs to screen and to the open file when running as daemon
	printf("%s: %s\n", timedate, buf);
}

