/**************
 *-=server.c=-*
 **************

 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de gérer le serveur.
*/

//-=Inclusion des headers=-//
#include "server.h"
#include "../sys/log.h"
//-=Fin de la section=-//

struct Server_t net_server_init(const char * socket_name)
{
	//-=Variables=-//
	struct Server_t srv;
	//-=Fin de la section=-//
	
	do
	{
		syslog(LOG_NOTICE, "Ouverture du serveur avec le nom suivant : %s", socket_name);
		srv.sock = socket(AF_UNIX, SOCK_STREAM, 0);

		if(srv.sock < 0)
		{
			syslog(LOG_ERR, "Impossible d'ouvrir le socket.");
			srv.error = 1;
			break;
		}

		srv.addr.sun_family = AF_UNIX;
		strcpy(srv.addr.sun_path, socket_name);

		//-=Activation socket=-//
		if(bind(srv.sock, (struct sockaddr *) &srv.addr, sizeof(struct sockaddr_un))) //> 0 -> Erreur
		{
			syslog(LOG_ERR, "Erreur lors de l'activation du socket");
			srv.error = 1;
			break;
		}
		//-=Fin de la section=-//

		//-=Initialisation clients=-//
		size_t i = 0;
		for(i = 0; i < MAX_CLIENTS; i++)
		{
			srv.clients[i] = net_serverClient_create();
		}
		//-=Fin de la section=-//

		syslog(LOG_NOTICE, "Socket initialisé avec le nom suivant : %s", srv.addr.sun_path);
		listen(srv.sock, MAX_CLIENTS);
	} while(0);

	return srv;
}

uint8_t net_server_run(struct Server_t * srv)
{
	int msgsock = 0;

	for(;;)
	{
		msgsock = accept(srv->sock, 0, 0);

		if(msgsock == -1)
		{
			syslog(LOG_ERR, "Erreur lors de l'ouverture de la connexion entrante... :(");
		}

		else
		{
			//-=Recherche premier emplacement libre=-//
			size_t i = 0;
			while(srv->clients[i].active && i < MAX_CLIENTS) i++;

			if(i >= MAX_CLIENTS)
			{
				syslog(LOG_ERR, "Impossible d'accepter la connexion : Limite de clients atteinte.");
			}

			else
			{
			//	srv->clients[i].sock = msgsock;
			//	net_socket_create_handler(&srv->clients[i]); //On lance le nécessaire pour s'occuper du client.

				srv->clients[i].socket.fd = msgsock;
				srv->clients[i].socket.status = SOCKET_STATUS_IDLE;
				net_serverClient_handler_create(&srv->clients[i]);
			}
			//-=Fin de la section=-//
		}
	}

	return EXIT_SUCCESS;
}

void net_server_stop(struct Server_t * srv)
{
	//-=Arrêt des threads clients=-//
	syslog(LOG_NOTICE, "Déconnexion forcée des clients");

	size_t i = 0;
	for(i = 0; i < MAX_CLIENTS; i++)
	{
		if(srv->clients[i].socket.status) net_serverClient_close(&srv->clients[i]);
	}
	//-=Fin de la section=-//
	
	//-=Fermeture socket=-//
	syslog(LOG_NOTICE, "Fermeture du serveur...");

	//--Fermeture socket
	close(srv->sock);

	//--Suppression fichier socket
	unlink(srv->addr.sun_path);
	//-=Fin de la section=-//
}
