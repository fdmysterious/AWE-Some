/***************
 *-=Motor.cpp=-*
 ***************

 Auteur : Florian Dupeyron (My?terious)
 Description : Contrôle un moteur simplement.
*/

//-=Inclusion des headers=-//
#include "MotorControl.hpp"
//-=Fin de la section=-//

namespace out
{
	MotorControl::MotorControl(const uint8_t pin_pwm, const uint8_t pin_dir) :
		m_pin_pwm(pin_pwm),
		m_pin_dir(pin_dir),
		m_cycle(0),
		m_direction(MOTOR_DIR_CWISE)
	{
	}

	MotorControl::~MotorControl()
	{
	}

	void MotorControl::setDuty(const uint16_t cycle)
	{
		m_cycle = cycle;
		applyPWM(); //On applique la PWM.
	}

	void MotorControl::stop()
	{
		digitalWrite(m_pin_pwm, LOW); //On arrête la PWM en mettant la tension basse.
	}

	void MotorControl::setDirection(const uint8_t dir)
	{
		//On effectue un contrôle de la valeur avant de l'assigner, pour éviter
		//des erreurs involontaires. Cela demande un peu plus de puissance de calcul,
		//Mais peut éviter des problèmes je pense.
		switch(dir)
		{
			case MOTOR_DIR_CWISE	 :
			case MOTOR_DIR_ANTICWISE :
			m_direction = dir;
			default:
			break;
		}

		//-=On applique l'information=-//
		applyDir();
		//-=Fin de la section=-//
	}
	
	uint16_t MotorControl::duty()
	{
		return m_cycle;
	}
	
	uint8_t MotorControl::direction()
	{
		return m_direction;
	}

	void MotorControl::applyPWM()
	{
		//analogWrite(m_pin_pwm, m_cycle);
		Timer1.pwm(m_pin_pwm, m_cycle); //On applique la PWM
	}

	void MotorControl::applyDir()
	{
		//La direction étant juste une tension à appliquer, il suffit
		//d'appliquer l'état de la variable m_direction.
		digitalWrite(m_pin_dir, m_direction);
	}

	void MotorControl::setup()
	{
		//-=Initialisation ports=-//
		pinMode(m_pin_pwm, OUTPUT);
		pinMode(m_pin_dir, OUTPUT);
		//-=Fin de la section=-//
		
		//-=Initialisation PWM=-//
		Timer1.initialize(MOTOR_PWM_PERIOD);
		//-=Fin de la section=-//
		
		//-=Application paramètres (reset)=-//
		applyPWM();
		applyDir();
		//-=Fin de la section=-//
	}
}

