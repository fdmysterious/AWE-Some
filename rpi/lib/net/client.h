/**************
 *-=client.h=-*
 **************

 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de gérer un client.
*/
#ifndef HEADER_NET_CLIENT
#define HEADER_NET_CLIENT

//-=Inclusion des headers=-//
#include "socket.h"
#include "function.h"

#include "../core/parser.h"
//-=Fin de la section=-//

//-=Structures=-//
struct Client_t
{
	struct Socket_t socket;
	struct Parser_t parser;

	struct sockaddr_un addr; //Informations quant à la connexion
	uint8_t error;		 //Permet de savoir s'il y a une erreur.
};
//-=Fin de la section=-//

//-=Fonctions=-//
struct Client_t	net_client_open(const char * socket_name);
void		net_client_send(struct Client_t * c, const char * msg);
void		net_client_receive(struct Client_t * c);
void		net_client_close(struct Client_t * c);
//-=Fin de la section=-//

#endif
