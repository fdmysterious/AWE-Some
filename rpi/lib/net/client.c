/**************
 *-=client.c=-*
 **************

 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de gérer le client.
*/

//-=Inclusion des headers=-//
#include "client.h"
#include "register.h"

#include "../sys/log.h"

#include <errno.h>
//-=Fin de la section=-//

struct Client_t net_client_open(const char * socket_name)
{
	//-=Variables=-//
	struct Client_t c;
	c.error = 0;
	//-=Fin de la section=-//

	c.socket = net_socket_create();
	c.parser = core_parser_create();

	do
	{
		syslog(LOG_NOTICE, "Ouverture du client sur le socket suivant : %s", socket_name);
		c.socket.fd = socket(AF_UNIX, SOCK_STREAM, 0);

		if(c.socket.fd < 0)
		{
			syslog(LOG_ERR, "Impossible d'ouvrir le socket : %s", strerror(errno));
			c.error = 1;
			break;
		}

		c.addr.sun_family = AF_UNIX;
		strcpy(c.addr.sun_path, socket_name);

		//-=Activation socket=-//
		if(connect(c.socket.fd, (struct sockaddr*)&c.addr, sizeof(struct sockaddr_un)))
		{
			syslog(LOG_ERR, "Erreur lors de la connection : %s", strerror(errno));
			c.error = 1;
			break;
		}
		//-=Fin de la section=-//

		//-=Modification status socket=-//
		c.socket.status = SOCKET_STATUS_IDLE; //Le socket est en fonctionnement standard.
		//-=Fin de la section=-//
	} while(0);

	return c;
}

void net_client_send(struct Client_t * c, const char * msg)
{
	net_socket_send(&c->socket, msg);
}

void net_client_receive(struct Client_t * c)
{
	syslog(LOG_NOTICE, "Réception message...");
	//-=Variables=-//
	int rval = 0;
	//-=Fin de la section=-//
	
	do
	{
		if(rval = net_socket_update(&c->socket))
		{
			fprintf(stdout, "Données : %s\n", c->socket.buffer);

			//-=Mise a jour parser=-//
			if(core_parser_update(&c->parser, c->socket.buffer))
			{
				syslog(
						LOG_NOTICE,
						"Instruction reçue : %s avec les arguments suivants : %s",
						core_parser_get_name(&c->parser), core_parser_get_args(&c->parser)
				);
				break; //Break while
			}
			//-=Fin de la section=-//
		}
	} while(c->socket.status);
}

void net_client_close(struct Client_t * c)
{
	//-=Arrêt socket=-//
	net_socket_close(&c->socket);
	//-=Fin de la section=-//
}
