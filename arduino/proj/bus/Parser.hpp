/****************
 *-=Parser.hpp=-*
 ****************
 
 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de découper le message.
*/
#ifndef HEADER_BUS_PARSER
#define HEADER_BUS_PARSER

//-=Inclusion des headers=-//
#include <inttypes.h>
//-=Fin de la section=-//

//-=Configuration=-//
//#define PARSER_BLOCK_SIZE 32 //Combien d'octet on procède au maxi avant de laisser à nouveau la main au programme.
#define PARSER_BUFFER_SIZE 8 //Taille buffer token

#define PARSER_STATUS_PARAM	1 //Quand on a un argument avec une virgule
#define PARSER_STATUS_END	2 //Fin de l'instruction
//-=Fin de la section=-//

namespace bus
{
	class ParserClass
	{
		public:
		ParserClass();
		~ParserClass();
		
		//-=Fonctions de mise à jour=-//
		void update();
		//-=Fin de la section=-//
		
		//-=Fonctions d'obtention=-//
		uint8_t status();
		char * getToken();
		//-=Fin de la section=-//
		
		private:
		//-=Fonctions de gestion de la mémoire=-//
		void resetBuffer();
		//-=Fin de la section=-//
		
		private:
		//-=Mémoire=-//
		char * m_buffer;
		uint8_t m_buffer_index;
		//-=Fin de la section=-//
		
		//-=Status=-//
		uint8_t m_status;
		//-=Fin de la section=-//
	};
	
	extern ParserClass Parser; //Objet principal
}

#endif