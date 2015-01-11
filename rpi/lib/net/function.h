/****************
 *-=function.h=-*
 ****************

 Auteur : Florian Dupeyron (My?terious)
 Description : Contient les fonctions qui peuvent être appelée par le socket.
*/
#ifndef HEADER_COM_FUNCTION
#define HEADER_COM_FUNCTION

//-=Inclusion des headers=-//
#include <inttypes.h>
#include "../net/socket.h"
//-=Fin de la section=-//

//-=Typedef=-//
typedef void (*NetFunctionCallback)(const char * p, struct Socket_t * s);
//-=Fin de la section=-//

//-=Fonctions existantes=-//
void net_function_hello(const char * p, struct Socket_t * s);
void net_function_rep(const char * p, struct Socket_t * s);

//--Fonctions de statut
void net_function_ok(const char * p, struct Socket_t * s);
void net_function_err(const char * p, struct Socket_t * s);
//-=Fin de la section=-//

#endif
