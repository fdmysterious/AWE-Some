/***********
 *-=log.h=-*
 ***********
 
 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de g�rer les journaux d'�v�nements
*/
#ifndef HEADER_SYS_LOG
#define HEADER_SYS_LOG

//-=Inclusion des headers=-//
#include <syslog.h>
//-=Fin de la section=-//

void syslog_open(const char * n);	//Initialise le journal d'�v�nements
#define syslog_close closelog		//Alias qui permet de garder une certaine esth�tique de codage.

#endif
