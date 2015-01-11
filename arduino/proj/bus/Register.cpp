/******************
 *-=Register.cpp=-*
 ******************
 
 Auteur : Florian Dupeyron (My?terious)
 Description : Registre des fonctions disponibles pour la communication
*/

//-=Inclusion des headers=-//
#include "Register.hpp"
#include <string.h>
//-=Fin de la section=-//

namespace bus
{
	FunctionCallback Register::getFunction(char * str)
	{
		if(strcmp(str, "HELLO") == 0)
		{
			return fun_hello;
		}
		
		else if(strcmp(str, "ANS") == 0)
		{
			return fun_ans;
		}
		
		else if(strcmp(str, "MDUTY") == 0)
		{
			return fun_mduty;
		}
		
		else if(strcmp(str, "TEST") == 0)
		{
			return fun_test;
		}
		
		else if(strcmp(str, "NT") == 0)
		{
			return fun_nt;
		}
		
		else if(strcmp(str, "RAM") == 0)
		{
			return fun_ram;
		}
		
		else
		{
			return NULL;
		}
	}
}