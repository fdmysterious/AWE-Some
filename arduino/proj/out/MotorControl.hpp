/***************
 *-=Motor.hpp=-*
 ***************

 Auteur : Florian Dupeyron (My?terious)
 Description : Contrôle un moteur simplement.

 Il est impératif de connecter la pwm du moteur sur les ports utilisant le timer1
 qui est un timer de résolution 16bits. Ces ports sont les ports 9 et 10.

 Cela permet de pouvoir changer la fréquence de la PWM pour obtenir quelque chose
 de silencieux qui ne détruit pas les oreilles.

 Il faut par contre faire attention en changeant la fréquence de la PWM car cela affecte
 des fonctions de l'arduino utilisant le temps. Sur ces deux pins, la bibliothèque Servo
 risque de ne plus fonctionner correctement.

 La bibliothèque Timer1 est installée dans le projet et permet de modifier la fréquence
 de la pwm.

 Avec la carte DRI0018, la fréquence PWM max supportée est 25 Khz.
*/
#ifndef HEADER_OUT_MOTOR
#define HEADER_OUT_MOTOR

//-=Inclusion des headers=-//
//#include <Arduino.h>
#include <Arduino.h>
#include <inttypes.h>
#include "../sys/TimerOne.h"
//-=Fin de la section=-//

//-=Defines=-//
#define MOTOR_DIR_CWISE		HIGH //Sens des aiguilles d'une montre (Clockwise)
#define MOTOR_DIR_ANTICWISE	LOW  //Sens contraire des aiguilles d'une montre (Anticlockwise)

#define MOTOR_PWM_PERIOD	50	//Période PWM de 50 micro secondes (20 kHz)
//-=Fin de la section=-//


namespace out 
{
	class MotorControl
	{
		public:
		MotorControl(const uint8_t pin_pwm, const uint8_t pin_dir);
		virtual ~MotorControl();

		//-=Fonctions gestion moteur=-//
		//--Puissance
		void setDuty(const uint16_t cycle);
		void stop(); //Arrête le moteur pour éviter le bruit de la PWM

		//--Direction
		void setDirection(const uint8_t dir);
		//-=Fin de la section=-//
		
		//-=Obtention des informations=-//
		uint16_t duty();
		uint8_t direction();
		//-=Fin de la section=-//
		
		//-=Initialisation du moteur=-//
		void setup();
		//-=Fin de la section=-//
		
		private:
		//-=Applications fonctions=-//
		void applyPWM();
		void applyDir();
		//-=Fin de la section=-//
		
		private:
		//-=Pins=-//
		uint8_t m_pin_pwm; //Pin pour envoyer la PWM
		uint8_t m_pin_dir; //Pin pour gérer la direction
		//-=Fin de la section=-//

		//-=Informations=-//
		uint16_t m_cycle;		//0-1023, duty cycle
		uint8_t  m_direction;	//impose la direction
		//-=Fin de la section=-//
	};
}

#endif
