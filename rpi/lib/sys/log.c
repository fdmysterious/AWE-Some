/***********
 *-=log.c=-*
 ***********
 
 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de gérer les journaux d'événements
*/
#ifndef HEADER_SYS_LOG
#define HEADER_SYS_LOG

//-=Inclusion des headers=-//
#include <syslog.h>
//-=Fin de la section=-//

void syslog_open(const char * n)
{
	setlogmask(LOG_UPTO(LOG_NOTICE)); //On définit jusqu'où on peut afficher les messages.
	
	//La fonction suivante permet d'ouvrir le journal d'événement. Les paramètres sont les suivants :
	// Paramètres d'affichage :
	// -> LOG_PERROR : 
	// -> LOG_PID :
	// -> LOG_NDELAY :
	// Type de log :
	// -> LOG_USER
	openlog(n, LOG_PERROR | LOG_PID | LOG_NDELAY, LOG_DAEMON);
}

#endif
