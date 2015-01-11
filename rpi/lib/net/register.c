/****************
 *-=register.c=-*
 ****************

 Auteur : Florian Dupeyron (My?terious)
 Description : Registre des fonctions utilisables par les sockets.
*/

//-=Inclusion des headers=-//
#include "register.h"
//-=Fin de la section=-//

NetFunctionCallback net_register_get_function(const char * n)
{
	if(strcmp(n, "hello") == 0)
	{
		return net_function_hello;
	}

	else if(strcmp(n, "rep") == 0)
	{
		return net_function_rep;
	}

	else if(strcmp(n, "ok") == 0)
	{
		return net_function_ok;
	}

	else if(strcmp(n, "err") == 0)
	{
		return net_function_err;
	}

	else
	{
		return NULL;
	}
}

const char * net_register_get_name(NetFunctionCallback fc)
{
	if(fc == net_function_hello)
	{
		return "hello";
	}

	else if(fc == net_function_rep)
	{
		return "rep";
	}

	else
	{
		return NULL;
	}
}
