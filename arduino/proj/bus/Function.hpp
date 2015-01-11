/******************
 *-=Function.hpp=-*
 ******************
 
 Auteur : Florian Dupeyron (My?terious)
 Description : Contient les fonctions disponibles dans la communication.
*/
#ifndef HEADER_BUS_FUNCTION
#define HEADER_BUS_FUNCTION

//-=Inclusion des headers=-//
#include <inttypes.h>
//-=Fin de la section=-//

//-=Defines=-//
#define FUNCTION_STATUS_OK 			1
#define FUNCTION_STATUS_DONE		2

#define FUNCTION_STATUS_ERROR		3
//-=Fin de la section=-//

namespace bus
{
	//-=Typedefs=-//
	typedef uint8_t (*FunctionCallback)(const char * p);
	//-=Fin de la section=-//
	
	//-=Valeurs spéciales=-//
	extern const char * fun_param_stop;
	//-=Fin de la section=-//

	uint8_t fun_hello(const char * p);
	uint8_t fun_ans(const char * p);
	uint8_t fun_mduty(const char * p);
	uint8_t fun_test(const char * p);
	uint8_t fun_nt(const char * p);
	
	//-=Diagnostic système=-//
	uint8_t fun_ram(const char * p); //Permet de savoir la RAM disponible
	//-=Fin de la section=-//
}

#endif