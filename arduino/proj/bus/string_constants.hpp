/**************************
 *-=string_constants.hpp=-*
 **************************
 
 Auteur : Florian Dupeyron (My?terious)
 Description : Contient toutes les constantes
*/
#ifndef HEADER_BUS_STRING_CONSTANTS
#define HEADER_BUS_STRING_CONSTANTS

//-=Inclusion des headers=-//
#include <avr/pgmspace.h>
//-=Fin de la section=-//

namespace bus
{
	namespace string
	{
		//static PGM_P __attribute((section(".progmem.string"))) resp_ok		="$OK";
		//static PGM_P __attribute((section(".progmem.string"))) resp_hello		="$HELLO";
		//static PGM_P __attribute((section(".progmem.string"))) resp_err		="$ERR";
		
		//extern PGM_P __attribute((section(".progmem.data"))) resp_ok;
		//extern PGM_P __attribute((section(".progmem.data"))) resp_hello;
		//extern PGM_P __attribute((section(".progmem.data"))) resp_err;
		
		extern PGM_P PROGMEM resp_ok;
		extern PGM_P PROGMEM resp_hello;
		extern PGM_P PROGMEM resp_err;
		extern PGM_P PROGMEM resp_ans;
		
		//extern const char * resp_ok;
		//extern const char * resp_err;
		//extern const char * resp_hello;
	}
}

#endif