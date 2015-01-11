/****************
 *-=Parser.cpp=-*
 ****************
 
 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de découper le message
*/

//-=Inclusion des headers=-//
#include "Parser.hpp"
#include <Arduino.h>
//-=Fin de la section=-//

namespace bus
{
	ParserClass::ParserClass() :
		m_buffer(NULL),
		m_buffer_index(0),
		m_status(0)
	{
		//-=Allocation mémoire=-//
		m_buffer = (char *)malloc(sizeof(char) * PARSER_BUFFER_SIZE);
		//-=Fin de la section=-//
	}
	
	ParserClass::~ParserClass()
	{
	}
	
	void ParserClass::update()
	{
		static char readByte = 0; //Octet lecture.
		
		//-=Reset du token s'il le faut=-//
		if(m_status)
		{
			m_status = 0;
			resetBuffer();
		}
		//-=Fin de la section=-//
		
		while(Serial.available())
		{
			readByte = Serial.read();
			switch(readByte)
			{
				case ',':
				m_status = PARSER_STATUS_PARAM;
				break;
				
				case '\r':
				m_status = PARSER_STATUS_END;
				break;
				
				default:
				m_buffer[m_buffer_index] = readByte;
				m_buffer_index++;
				break;
			}
			
			if(m_status) break;
		}
		
		if(m_status)
		{
			m_buffer[m_buffer_index] = '\0';
		}
	}
	
	uint8_t ParserClass::status()
	{
		return m_status;
	}
	
	char * ParserClass::getToken()
	{
		return m_buffer;
	}
	
	void ParserClass::resetBuffer()
	{
		m_buffer_index = 0;
		memset(m_buffer, 0, PARSER_BUFFER_SIZE);
	}
	
	ParserClass Parser;
}