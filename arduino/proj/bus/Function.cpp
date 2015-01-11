/******************
 *-=Function.cpp=-*
 ******************
 
 Auteur : Florian Dupeyron (My?terious)
 Description : Contient les fonctions disponibles dans la communication.
*/

//-=Inclusion des headers=-//
#include "../sys/utilities.hpp"

#include "Function.hpp"
#include "string_constants.hpp"

#include "../out/Motors.hpp"

#include <Arduino.h>
#include <inttypes.h>
//-=Fin de la section=-//

//-=Mémoire partagée entre toutes les fonctions=-//
bool done = true;
//-=Fin de la section=-//

namespace bus
{
	//-=Initialisation valeurs spéciales=-//
	const char * fun_param_stop = (char*)malloc(sizeof(char));
	//-=Fin de la section=-//
	
	uint8_t fun_hello(const char * p)
	{
		Serial.println(bus::string::resp_hello);

		return FUNCTION_STATUS_DONE;
	}
	
	uint8_t fun_ans(const char * p)
	{
		Serial.println(bus::string::resp_ans);
		return FUNCTION_STATUS_DONE;
	}
	
	uint8_t fun_mduty(const char * p)
	{
		//-=Variables paamètres=-//
		static uint16_t * p1 = NULL;
		//-=Fin de la section=-//
		
		//-=Contrôle paramètres spéciaux=-//
		if(p == fun_param_stop)
		{
			if(p1 != NULL)
			{
				free(p1);
				p1 = NULL;
			}
			
			return FUNCTION_STATUS_ERROR;
		}
		//-=Fin de la section=-//
		
		//-=Allocation mémoire=-//
		if(p1 == NULL)
		{
			p1 = (uint16_t*)malloc(sizeof(uint16_t));
			return FUNCTION_STATUS_OK;
		}
		//-=Fin de la section=-//
		
		//-=Récupération des paramètres=-//
		else
		{
			*p1 = (uint16_t) atoi(p);
			
			//-=Fonction en elle-même=-//
			out::mot_duty.setGoalValue(*p1);
			//-=Fin de la section=-//
			
			//-=On confirme la demande=-//
			Serial.println(bus::string::resp_ok);
			//-=Fin de la section=-//
			
			//-=On libère la mémoire=-//
			free(p1);
			p1 = NULL;
			//-=Fin de la section=-//
			
			//-=Retour=-//
			return FUNCTION_STATUS_DONE;
			//-=Fin de la section=-//
		}
		//-=Fin de la section=-//
	}
	
	uint8_t fun_test(const char * p)
	{
		//-=Variables paramètres=-//
		static int * p1 = NULL;
		//-=Fin de la section=-//
		
		//-=Paramètres spéciaux=-//
		if(p == fun_param_stop)
		{
			if(p1 != NULL)
			{
				free(p1);
				p1 = NULL;
			}
			
			return FUNCTION_STATUS_ERROR;
		}
		//-=Fin de la section=-//
		
		//-=Allocation mémoire=-//
		if(p == NULL)
		{
			p1 = (int*) malloc(sizeof(int));
			return FUNCTION_STATUS_OK;
		}
		//-=Fin de la section=-//
		
		//-=Exécution fonction=-//
		else
		{
			//-=Récupération paramètre=-//
			*p1 = (int)atoi(p);
			//-=Fin de la section=-//
			
			//-=Fonction en elle-même=-//
			Serial.print(bus::string::resp_ok);
			Serial.print(',');
			Serial.println(*p1);
			//-=Fin de la section=-//
			
			//-=Libération mémoire=-//
			free(p1);
			//-=Fin de la section=-//
			
			//-=Retour fonction=-//
			return FUNCTION_STATUS_DONE;
			//-=Fin de la section=-//
		}
		//-=Fin de la section=-//
	}
	
	uint8_t fun_nt(const char * p)
	{
		//-=Variables paramètres=-//
		static uint8_t * pi	= NULL;
		static int * p1		= NULL;
		static int * p2		= NULL;
		//-=Fin de la section=-//
		
		//-=Contrôle paramètres spéciaux=-//
		if(p == fun_param_stop)
		{
			//-=Libération mémoire=-//
			if(pi != NULL) free(pi);
			if(p1 != NULL) free(p1);
			if(p2 != NULL) free(p2);
			//-=Fin de la section=-//
			
			return FUNCTION_STATUS_ERROR;
		}
		//-=Fin de la section=-//
		
		//-=Allocation mémoire=-//
		if(pi == NULL)
		{
			pi = (uint8_t*)malloc(sizeof(uint8_t));
			*pi = 0;
			
			p1 = (int*)malloc(sizeof(int));
			p2 = (int*)malloc(sizeof(int));
			
			return FUNCTION_STATUS_OK;
		}
		//-=Fin de la section=-//
		
		//-=Récupération paramètres=-//
		else
		{
			switch(*pi)
			{
				case 0:
				*p1 = (int)atoi(p);
				*pi += 1;
				return FUNCTION_STATUS_OK;
				break;
				
				case 1:
				*p2 = (int)atoi(p);
				
				Serial.print(bus::string::resp_ok);
				Serial.print(',');
				Serial.print(*p1);
				Serial.print(",");
				Serial.println(*p2);
				
				//-=Libération mémoire=-//
				free(pi);
				free(p1);
				free(p2);
				//-=Fin de la section=-//
				
				return FUNCTION_STATUS_DONE;
				
				break;
			}
		}
		//-=Fin de la section=-//
	}
	
	uint8_t fun_ram(const char * p)
	{
		//-=Récupération de l'information=-//
		uint32_t r = sys::freeRam();
		//-=Fin de la section=-//
		
		//-=Affichage=-//
		Serial.print(bus::string::resp_ok);
		Serial.print(',');
		Serial.println(r);
		//-=Fin de la section=-//
		
		return FUNCTION_STATUS_DONE;
	}
}