/************
 *-=main.c=-*
 ************

 Auteur : Florian Dupeyron (My?terious)
 Description : Test FCGI Client.
*/

//-=Inclusion des headers=-//
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

#include <fcgi_stdio.h>

#include <lib/sys/log.h>
#include <lib/net/client.h>

#include <lib/fcgi/query_parser.h>
//-=Fin de la section=-//

struct Client_t client;

uint8_t send_request(char * r, char * buf, size_t size)
{
	//-=Connection=-//
	syslog(LOG_NOTICE, "Connection au serveur");
	//-=Fin de la section=-//
	
	//-=Envoi du message=-//
	syslog(LOG_NOTICE, "Envoi du message.");
	net_client_send(&client, r);
	//-=Fin de la section=-//

	//-=Réponse=-//
	syslog(LOG_NOTICE, "Attente réponse du serveur...");
	net_client_receive(&client);
	//-=Fin de la section=-//
	
	strncpy(buf, client.socket.buffer, size); //Copie de la réponse.
	return EXIT_SUCCESS;
}

int main(int argc, const char *argv[])
{
	//-=Initialisation du log=-//
	syslog_open(argv[0]);
	//-=Fin de la section=-//
	
	////-=Initialisation client=-//
	//client = net_client_open("/var/run/caveavin/socket/srv");

	//if(client.error)
	//{
	//	syslog(LOG_ERR, "Impossible de se connecter au socket : %s.", strerror(errno));
	//	return EXIT_FAILURE;
	//}
	////-=Fin de la section=-//
	
	//-=Prise en charges des requêtes=-//
	while(FCGI_Accept() >= 0)
	{
		//syslog(LOG_NOTICE, "Request !");

		//bzero(buffer, 1024);
		//
		//printf("Content-type: applcation/json\r\n");
		//printf("\r\n");

		//if(send_request(buffer, 1024))
		//{
		//	printf("{\"resp\" : \"Erreur survenue\"}\r\n");
		//	FCGI_setExitStatus(500);
		//}

		//else
		//{
		//	printf("{\"resp\": \"%s\"}\r\n", buffer);
		//}

		char * query = getenv("QUERY_STRING");

		printf("Content-type: text-plain\r\n");
		printf("\r\n");
		
		printf("Requête effectuée : %s\n", query);
		printf("Paramètres : ");
		
		struct QueryParser_Arg_t a;

		if(query != NULL)
		{
			char fname[128];
			char fargs[512];

			printf("%s\n", query);

			if(fcgi_query_parse(&a, query)) do
			{
				printf("-> %s avec la valeur %s\n", a.name, a.value);

			} while(fcgi_query_parse(&a, NULL) == QUERY_PARSER_FOUND);

			//-=Fin de la section=-//
		}

		else
		{
			printf("NULL\n");
			FCGI_SetExitStatus(400); //Code d'erreur 400 -> La requête a mal été formulée.
		}
		
	}
	//-=Fin de la section=-//
	
	//-=Arrêt du log=-//
	syslog_close();
	//-=Fin de la section=-//

	return 0;
}
