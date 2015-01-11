/**************
 *-=server.h=-*
 **************

 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de gérer le serveur.
*/
#ifndef HEADER_NET_SERVER
#define HEADER_NET_SERVER

//-=Inclusion des headers=-//
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "serverClient.h"
//-=Fin de la section=-//

//-=Configuration=-//
#define MAX_CLIENTS 32
//-=Fin de la section=-//

//-=Structures=-//
struct Server_t
{
	int			sock;
	struct sockaddr_un	addr;

	uint8_t			error;

	struct ServerClient_t	clients[MAX_CLIENTS];
};
//-=Fin de la section=-//

//-=Fonctions=-//
struct Server_t	net_server_init(const char * socket_name);
uint8_t		net_server_run(struct Server_t * srv);
void		net_server_stop(struct Server_t * srv);
//-=Fin de la section=-//

#endif
