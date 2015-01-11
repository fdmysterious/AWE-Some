/*******************
 *-=utilities.cpp=-*
 *******************

 Auteur : Florian Dupeyron
 Description : Utilitaires pour l'arduino.
*/

//-=Inclusion des headers=-//
#include "utilities.hpp"
//-=Fin de la section=-//

namespace sys
{

//int freeMemory() {
//int free_memory;
//if((int)__brkval == 0)
//free_memory = ((int)&free_memory) - ((int)&__bss_end);
//else
//free_memory = ((int)&free_memory) - ((int)__brkval);
//return free_memory;
//}
	uint32_t freeRam()
	{
	
		static unsigned int __bss_end;
		static unsigned int __heap_start;
		static void *__brkval;
		
		uint32_t r;
		
		if((uint32_t)__brkval == 0)
		{
			r = ((uint32_t)&r) - ((uint32_t)&__bss_end);
		}
		
		else
		{
			r = ((uint32_t)&r) - ((uint32_t)__brkval);
		}
		
		return r;
	}
}

