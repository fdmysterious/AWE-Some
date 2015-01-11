/**************
 *-=socket.h=-*
 **************

 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de gérer un socket.
*/
#ifndef HEADER_NET_SOCKET
#define HEADER_NET_SOCKET

//-=Inclusion des headers=-//
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
//-=Fin de la section=-//

//-=Configuration=-//
#define SOCKET_BUFFER_SIZE 1024

#define SOCKET_STATUS_DISCONNECTED	0
#define SOCKET_STATUS_IDLE		1
#define SOCKET_STATUS_OK		2
#define SOCKET_STATUS_ERR		3
//-=Structures=-//
struct Socket_t
{
	int fd; //File Descriptor

	uint8_t error;
	uint8_t status;

	char buffer[SOCKET_BUFFER_SIZE];
};
//-=Fin de la section=-//

//-=Fonctions=-//
struct Socket_t net_socket_create();

void net_socket_close(struct Socket_t * s);			//Ferme le socket s.

void	net_socket_send(struct Socket_t * s, const char * msg);	//Envoie le message sur le socket.
size_t	net_socket_update(struct Socket_t * s);			//Lis des données disponibles sur le socket ; renvoie le nombre d'octets lus.
//-=Fin de la section=-//

#endif
