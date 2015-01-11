/************
 *-=daemon=-*
 ************

 Auteur : Florian Dupeyron (My?terious)
 Description : Programme qui permet de gérer le daemon.
*/

//-=Inclusion des headers=-//
#include <errno.h>

#include <lib/sys/log.h>
#include <lib/net/server.h>
//-=Fin de la section=-//


int main(int argc, const char *argv[])
{
	//-=Initialisation syslog=-//
	syslog_open(argv[0]);
	//-=Fin de la section=-//
	
	//-=Ouverture serveur=-//
	struct Server_t srv = net_server_init("/var/run/caveavin/socket/srv");
	if(srv.error)
	{
		syslog(LOG_CRIT, "Erreur lors de l'ouverture du serveur : %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	//-=Fin de la section=-//
	
	//-=chmod=-//
	chmod("/var/run/caveavin/socket/srv", 777);
	//-=Fin de la section=-//
	
	
	//-=Lancement serveur=-//
	net_server_run(&srv);
	//-=Fin de la section=-//
	
	//-=Arrêt serveur=-//
	net_server_stop(&srv);
	//-=Fin de la section=-//
	
	//-=Fermeture syslog=-//
	syslog_close();
	//-=Fin de la section=-//
	
	return 0;
}
