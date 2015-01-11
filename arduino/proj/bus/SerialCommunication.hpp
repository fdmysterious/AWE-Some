/*****************************
 *-=SerialCommunication.hpp=-*
 *****************************
 
 Auteur : Florian Dupeyron (My?terious)
 Description : Gère la communication série.
*/
#ifndef HEADER_BUS_SERIALCOMMUNICATION
#define HEADER_BUS_SERIALCOMMUNICATION

//-=Inclusion des headers=-//
#include <inttypes.h>
#include "Function.hpp"
//-=Fin de la section=-//

//-=Configuration=-//
#define SERIALCOMMUNICATION_BLOCK_SIZE			16	//On procède le décodage du message par blocs de 32 octets.

#define SERIALCOMMUNICATION_FUNCTION_BUFFER_SIZE 8	//On peut stocker jusqu'à 4 messages.

#define SERIALCOMMUNICATION_TOKEN_BUFFER_SIZE	8	//8 tokens max par instruction

#define SERIALCOMMUNICATION_BAUDRATE		  9600	//Baud rate.

//#define SERIALCOMMUNICATION_VERBOSE
//-=Fin de la section=-//

//-=Defines status=-//
#define SERIALCOMMUNICATION_STATUS_WAITING		0
#define SERIALCOMMUNICATION_STATUS_RECEIVING	1
#define SERIALCOMMUNICATION_STATUS_EXECUTING	2
//-=Fin de la section=-//

namespace bus
{
	class SerialCommunication
	{
		public:
		SerialCommunication();
		~SerialCommunication();
		
		//-=Initialisation=-//
		void setup();
		//-=Fin de la section=-//
		
		//-=Mise a jour=-//
		void update();
		//-=Fin de la section=-//
		
		private:
		//-=Attente du dollar=-//
		void updateWait();
		void updateReceive();
		//-=Fin de la section=-//
		
		private:
		FunctionCallback m_fc;	//Function callback
		uint8_t m_status;
	};
}
#endif