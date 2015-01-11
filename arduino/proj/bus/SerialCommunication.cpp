/*****************************
 *-=SerialCommunication.cpp=-*
 *****************************
 
 Auteur : Florian Dupeyron (My?terious)
 Description : Gère la communication série.
*/

//-=Inclusion des headers=-//
#include "SerialCommunication.hpp"
#include "Parser.hpp"

#include <Arduino.h>	//Pour pouvoir utiliser le serial matériel.
#include <avr/pgmspace.h>
//#include <memory.h>		//Fonctions de gestion avancée de la mémoire (memset, memcpy...)

#include "Register.hpp"
#include "string_constants.hpp"
//-=Fin de la section=-//

namespace bus
{
	SerialCommunication::SerialCommunication() :
		m_status(0)
	{
	}
	
	SerialCommunication::~SerialCommunication()
	{
	}
	
	void SerialCommunication::setup()
	{
		Serial.begin(SERIALCOMMUNICATION_BAUDRATE);
	}
	
	void SerialCommunication::update()
	{
		//-=Groupe 1=-//
		switch(m_status)
		{
			case SERIALCOMMUNICATION_STATUS_WAITING:
			updateWait();
			break;
			
			case SERIALCOMMUNICATION_STATUS_EXECUTING:
			case SERIALCOMMUNICATION_STATUS_RECEIVING:
			updateReceive();
			break;
		}
		//-=Fin de la section=-//
	}
	
	void SerialCommunication::updateWait()
	{
		while(Serial.available())
		{
			char readByte = Serial.read();
			if(readByte == '$') //Attente terminée !
			{
				m_status = SERIALCOMMUNICATION_STATUS_RECEIVING;
				
				#ifdef SERIALCOMMUNICATION_VERBOSE
				Serial.println("Dollar !");
				#endif
				
				return; //On quitte la fonction car on a plus à attendre.
			}
		}
	}
	
	void SerialCommunication::updateReceive()
	{
		bus::Parser.update();
		if(Parser.status())
		{			
			//-=Affichage=-//
			#ifdef SERIALCOMMUNICATION_VERBOSE
			Serial.println(Parser.getToken());
			#endif
			//-=Fin de la section=-//

			switch(m_status)
			{
				case SERIALCOMMUNICATION_STATUS_RECEIVING:
				//-=Récupération du pointeur de fonction=-//
				m_fc = bus::Register::getFunction(bus::Parser.getToken());
				//-=Fin de la section=-//
				
				//-=Première exécution=-//
				switch(m_fc(NULL))
				{
					case FUNCTION_STATUS_OK:
					if(Parser.status() == PARSER_STATUS_END) //C'est pas normal
					{
						m_fc(bus::fun_param_stop); //On arrête tout.
						m_status = SERIALCOMMUNICATION_STATUS_WAITING; //On repasse en mode attente :(
						
						Serial.println(bus::string::resp_err);
					}
					
					else
					{
						m_status = SERIALCOMMUNICATION_STATUS_EXECUTING; //On entre dans la phase d'exécution de la fonction, avec passage de paramètres.
					}
					break;
					
					case FUNCTION_STATUS_DONE: //Si la fonction ne requiert aucun argument
					m_status = SERIALCOMMUNICATION_STATUS_WAITING; //On repart sur de l'attente.
					break;
				}
				//-=Fin de la section=-//
				break;
				
				case SERIALCOMMUNICATION_STATUS_EXECUTING:
				switch(m_fc(bus::Parser.getToken())) //On exécute la fonction avec le nouveau paramètre.
				{
					case FUNCTION_STATUS_OK:
					if(Parser.status() == PARSER_STATUS_END) //Pas normal :(
					{
						m_fc(bus::fun_param_stop); //On arrête tout :(
						m_status = SERIALCOMMUNICATION_STATUS_WAITING;
						
						Serial.println(bus::string::resp_err);
					}
					break;
					
					case FUNCTION_STATUS_DONE:
					m_fc = NULL; //Juste au cas où ^^
					m_status = SERIALCOMMUNICATION_STATUS_WAITING; //On peut repasser en mode attente
					break;
				}
				break;
			}
		}
	}
}