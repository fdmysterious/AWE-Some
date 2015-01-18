/***************
 *-=fcgi test=-*
 ***************

 Auteur : Florian Dupeyron (My?terious)
 Description : Test d'un petit serveur FCGI.
*/

//-=Inclusion des headers=-//
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include <syslog.h>
#include <fcgi_stdio.h>
//-=Fin de la section=-//

void initlog(char * appName)
{
	setlogmask(LOG_UPTO(LOG_NOTICE));
	openlog(appName, LOG_PERROR | LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER);
}

float readTemp()
{
	float result = 0.f;

	//-=Lecture du fichier de la température=-//
	FILE * tempFile;
	syslog(LOG_NOTICE, "Reading temperature...");
	
	tempFile = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
	if(tempFile == NULL) 
	{
		syslog(LOG_CRIT, "Failed to open the temperature file... Aborting :(");
		exit(EXIT_FAILURE);
	}

	char readBuffer[8];
	if(fread(readBuffer, 1, 5, tempFile) >= 5)
	{
		syslog(LOG_NOTICE, "Temperature read ! Converting...");

		//--Conversion en int
		result = atof(readBuffer);
		result /= 1000.f;
		//--Conversion en float.
	}

	fclose(tempFile);
	//-=Fin de la section=-//
	
	syslog(LOG_NOTICE, "Read temperature : %4.2f°C", result);
	return result; 
}

int main(int argc, char * argv[])
{
	initlog(argv[0]);

	while(FCGI_Accept() >= 0)
	{
		syslog(LOG_NOTICE, "Let's send temperature !");
		float temperature = readTemp();

		printf("Content-type: application/json\r\n");
		printf("\r\n");
		printf("{\"value\": %4.2f}", temperature);
	}	

	closelog();
	return EXIT_SUCCESS;	
}
