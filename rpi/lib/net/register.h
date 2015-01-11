/****************
 *-=register.h=-*
 ****************

 Auteur : Florian Dupeyron (My?terious)
 Description : Registre des fonctions.
*/
#ifndef HEADER_COM_REGISTER
#define HEADER_COM_REGISTER

//-=Inclusion des headers=-//
#include "function.h"
//-=Fin de la section=-//

NetFunctionCallback net_register_get_function(const char * n);
const char * net_register_get_name(NetFunctionCallback fc);	//Sens inverse, permet d'avoir le nom de la fonction à partir de son pointeur.

#endif
