/**************************
 *-=string_constants.hpp=-*
 **************************
 
 Auteur : Florian Dupeyron (My?terious)
 Description : Contient toutes les constantes
*/

//-=Inclusion des headers=-//
#include "string_constants.hpp"
//-=Fin de la section=-//

namespace bus
{
	namespace string
	{
		//const char * resp_ok	= "$OK";
		//const char * resp_err	= "$ERR";
		//const char * resp_hello	= "$HELLO";
		
		//PGM_P __attribute((section(".progmem.data"))) resp_ok			= "$OK";
		//PGM_P __attribute((section(".progmem.data"))) resp_hello		= "$HELLO";
		//PGM_P __attribute((section(".progmem.data"))) resp_err			= "$ERR";
		
		extern PGM_P PROGMEM resp_ok	= "$OK";
		extern PGM_P PROGMEM resp_hello	= "$HELLO";
		extern PGM_P PROGMEM resp_err	= "$ERR";
		extern PGM_P PROGMEM resp_ans	= "$42";
		
		char buffer[8];
	}
}