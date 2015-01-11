/****************
 *-=function.c=-*
 ****************

 Auteur : Florian Dupeyron (My?terious)
 Description : Fonctions utilisables par les sockets.
*/

//-=Inclusion des headers=-//
#include "function.h"
#include "../sys/log.h"
//-=Fin de la section=-//

void net_function_hello(const char * p, struct Socket_t * s)
{
	//-=Log=-//
	syslog(LOG_NOTICE, "Sending hello to client...");
	//-=Fin de la section=-//
	
	//-=Envoi d'un gentil message !=-//
	net_socket_send(s, "hello;");
	//-=Fin de la section=-//
}

void net_function_rep(const char * p, struct Socket_t * s)
{
	syslog(LOG_NOTICE, "Sending back data...");
	net_socket_send(s, p);
}

void net_function_ok(const char * p, struct Socket_t * s)
{
	syslog(LOG_NOTICE, "Everything seems to be nice...");
	s->status = SOCKET_STATUS_OK;
}

void net_function_err(const char * p, struct Socket_t * s)
{
	syslog(LOG_ERR, "Something wront happened");
	s->status = SOCKET_STATUS_ERR;
}
