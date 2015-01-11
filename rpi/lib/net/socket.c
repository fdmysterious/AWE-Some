/**************
 *-=client.c=-*
 **************

 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de s'occuper des clients
*/

//-=Inclusion des headers=-//
#include "socket.h"
#include "../sys/log.h"
#include "register.h"

#include <errno.h>
//-=Fin de la section=-//

struct Socket_t net_socket_create()
{
	struct Socket_t s =
	{
		.fd = 0,
		.error = 0,
		.status = SOCKET_STATUS_DISCONNECTED
	};

	bzero(s.buffer, SOCKET_BUFFER_SIZE);

	return s;
}

void net_socket_close(struct Socket_t * s)
{
	syslog(LOG_NOTICE, "Fermeture socket n°%i...", s->fd);
	close(s->fd);
	s->status = SOCKET_STATUS_DISCONNECTED;
}

void net_socket_send(struct Socket_t * s, const char * msg)
{
	syslog(LOG_NOTICE, "Envoi message : %s sur socket n°%i", msg, s->fd);

	s->error = 0; //On reset le status des erreurs.

	if(send(s->fd, msg, strlen(msg) + 1, 0) < 1)
	{
		syslog(LOG_ERR, "Erreur envoi données sur socket n°%i : %s", s->fd, strerror(errno));
		s->error = 1;
	}
}

size_t net_socket_update(struct Socket_t * s)
{
	int rval = 0;

	//-=Reset error=-//
	s->error = 0;
	//-=Fin de la section=-//
	
	//-=Reset buffer=-//
	bzero(s->buffer, SOCKET_BUFFER_SIZE);
	//-=Fin de la section=-//
	
	//-=Reset status=-//
	s->status = SOCKET_STATUS_IDLE;
	//-=Fin de la section=-//
	
	
	if((rval = recv(s->fd, s->buffer, SOCKET_BUFFER_SIZE, 0)) < 0)
	{
		syslog(LOG_ERR, "Erreur lors de la réception des données sur le socket n°%i : %s", s->fd, strerror(errno));
		s->error = 1; //Quelque chose c'est mal passé :(
		return 0; //Aucun octet lu.
	}

	else if(rval == 0) //Socket fermé
	{
		syslog(LOG_NOTICE, "Le socket a été fermé.");
		net_socket_close(s);
		return 0;
	}

	else
	{
		return rval;
	}
}
