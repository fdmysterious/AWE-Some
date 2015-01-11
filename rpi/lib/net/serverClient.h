/********************
 *-=serverClient.h=-*
 ********************

 Auteur : Florian Dupeyron (My?terious)
 Description : S'occupe d'un client sur le serveur.
*/
#ifndef HEADER_NET_SERVERCLIENT
#define HEADER_NET_SERVERCLIENT

//-=Inclusion des headers=-//
#include <inttypes.h>
#include <pthread.h>

#include "socket.h"
#include "../core/parser.h"
//-=Fin de la section=-//

//-=Structures=-//
struct ServerClient_t
{
	struct Socket_t socket;

	//-=Gestion du handler=-//
	uint8_t		active;
	pthread_t	handler;
	pthread_mutex_t	mtx;
	//-=Fin de la section=-//
	
	//-=Parser=-//
	struct Parser_t parser;
	//-=Fin de la section=-//
};
//-=Fin de la section=-//

//-=Fonctions=-//
struct ServerClient_t net_serverClient_create();

void net_serverClient_handler_create(struct ServerClient_t * sc);	//Démarre le handler qui s'occupe du client
void net_serverClient_handler_stop(struct ServerClient_t * sc);		//Force l'arrêt du handler

void net_serverClient_close();						//Ferme la connection.
//-=Fin de la section=-//

#endif

