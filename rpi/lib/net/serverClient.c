/********************
 *-=serverClient.c=-*
 ********************

 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de gérer un client du point de vue du serveur.
*/

//-=Inclusion des headers=-//
#include "../sys/log.h"
#include "register.h"
#include "serverClient.h"
//-=Fin de la section=-//

//-=Handler=-//
void * serverClient_handler(void * p)
{
	//-=Récupération paramètre=-//
	struct ServerClient_t * sc = (struct ServerClient_t *) p;
	//-=Fin de la section=-//
	
	//-=Variables=-//
	size_t rval = 0;
	//-=Fin de la section=-//
	
	do
	{
		//-=Bloquage mutex=-//
		pthread_mutex_lock(&sc->mtx);
		//-=Fin de la section=-//
		
		if((rval = net_socket_update(&sc->socket)))
		{
			fprintf(stdout, "Données reçues : %s\n", sc->socket.buffer);

			//-=Mise a jour parser=-//
			if(core_parser_update(&sc->parser, sc->socket.buffer))
			{
				syslog(
						LOG_NOTICE,
						"Instruction reçue : %s avec les arguments suivants : %s",
						core_parser_get_name(&sc->parser), core_parser_get_args(&sc->parser)
				);

				//-=Récupération et exécution fonction=-//
				NetFunctionCallback fc = net_register_get_function(core_parser_get_name(&sc->parser));

				if(fc == NULL)
				{
					syslog(LOG_ERR, "Fonction inconnue : %s", core_parser_get_name(&sc->parser));
					net_socket_send(&sc->socket, "err;");
				}

				else
				{
					fc(core_parser_get_args(&sc->parser), &sc->socket);
				}
				//-=Fin de la section=-//
			}
			//-=Fin de la section=-//
		}

		//-=Débloquage mutex=-//
		pthread_mutex_unlock(&sc->mtx);
		//-=Fin de la section=-//
	} while(sc->socket.status); //tant que le socket n'est pas déconnecté.

	//-=Modification status=-//
	pthread_mutex_lock(&sc->mtx);
	sc->active = 0;
	pthread_mutex_unlock(&sc->mtx);
	//-=Fin de la section=-//
}
//-=Fin de la section=-//


struct ServerClient_t net_serverClient_create()
{
	struct ServerClient_t sc =
	{
		.socket	= net_socket_create(),
		.parser	= core_parser_create(),
		.active	= 0,
		.mtx	= PTHREAD_MUTEX_INITIALIZER
	};

	return sc;
}

void net_serverClient_handler_create(struct ServerClient_t * sc)
{
	syslog(LOG_NOTICE, "Création du handler pour le client...");

	//-=Bloquage mute=-//
	pthread_mutex_lock(&sc->mtx);
	//-=Fin de la section=-//
	
	//-=Modification status=-//
	sc->active = 1;
	//-=Fin de la section=-//
	
	//-=Lancement thread=-//
	pthread_create(&sc->handler, NULL, serverClient_handler, sc);
	//-=Fin de la section=-//
	
	//-=Débloquage mutex=-//
	pthread_mutex_unlock(&sc->mtx);
	//-=Fin de la section=-//
}

void net_serverClient_handler_stop(struct ServerClient_t * sc)
{
	syslog(LOG_NOTICE, "Arrêt forcé du handler du client...");

	//-=Bloquage mutex=-//
	pthread_mutex_lock(&sc->mtx);
	//-=Fin de la section=-//
	
	//-=Arrêt thread=-//
	pthread_cancel(sc->handler);
	//-=Fin de la section=-//
	
	//-=Modification status=-//
	sc->active = 0;
	//-=Fin de la section=-//
	
	//-=Débloquage mutex=-//
	pthread_mutex_unlock(&sc->mtx);
	//-=Fin de la section=-//
}

void net_serverClient_close(struct ServerClient_t * sc)
{
	syslog(LOG_NOTICE, "Fermeture de la connection avec le client...");

	//-=Bloquage mutex=-//
	pthread_mutex_lock(&sc->mtx);
	//-=Fin de la section=-//
	
	//-=Arrêt du handler ?=-//
	if(sc->active) net_serverClient_handler_stop(sc); //arrêt forcé du handler si besoin.
	//-=Fin de la section=-//
	
	//-=Fermeture connection=-//
	net_socket_close(&sc->socket);
	//-=Fin de la section=-//

	//-=Débloquage mutex=-//
	pthread_mutex_unlock(&sc->mtx);
	//-=Fin de la section=-//
}
