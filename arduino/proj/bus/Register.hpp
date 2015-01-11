/*******************
 *-=Registers.hpp=-*
 *******************
 
 Auteur : Florian Dupeyron (My?terious)
 Description : Registre des fonctions disponibles pour la communication
*/
#ifndef HEADER_BUS_REGISTERS
#define HEADER_BUS_REGISTERS

//-=Inclusion des headers=-//
#include "Function.hpp"
//-=Fin de la section=-//

namespace bus
{
	class Register
	{
		public:
		static FunctionCallback getFunction(char * name);
	};
}

#endif