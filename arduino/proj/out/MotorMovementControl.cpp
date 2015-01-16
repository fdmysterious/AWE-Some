/******************************
 *-=MotorMovementControl.cpp=-*
 ******************************
 
 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de gérer le déplacement du moteur
*/

//-=Inclusion des headers=-//
#include "MotorMovementControl.hpp"
//-=Fin de la section=-//

namespace out
{
	MotorMovementControl(speed_t vel, speed_t vlow, speed_t vmax) :
		m_vel(vel),
		m_vlow(vlow),
		m_vmax(vmax)
	{
	}
	
	MotorMovementControl::~MotorMovementControl()
	{
	}
	
	void MotorMovementControl::init(MotorMovementControl::step_t sTotal)
	{
		//-=Initialisation des valeurs constantes=-//
		m_step	= 0;
		m_phase	= 1;
		m_step_total = sTotal;
		//-=Fin de la section=-//
		
		//-=Calcul des valeurs de traitement=-//
		m_step_low  = (step_t)(MOTORMOVEMENTCONTROL_STEP_LOW_PERCENT * (float)(sTotal));
		m_step_acdc = (step_t)(.5f * (1.f - MOTORMOVEMENTCONTROL_STEP_LOW_PERCENT) * (float)(sTotal));
		//-=Fin de la section=-//
	}

	pwm_t MotorMovementControl::tick()
	{
		//-=Variables traitement=-//
		pwm_t r = 0; //Résultat retourné par la fonction.
		//-=Fin de la section=-//

		//-=Incrémentation compteur position=-//
		m_step++;
		//-=Fin de la section=-//
		
		//-=Traitement par phase=-//
		switch(m_phase)
		{
			case 1:
			if(m_step >= m_step_acdc)
			{
				m_phase++;
			}

			else
			{
				m_speed += m_vel;
			}
			break;

			case 2:
			if(m_step >= 2 * m_step_acdc)
			{
				m_phase++;
			}

			else
			{
				m_speed -= m_speed <= m_vlow ? m_vel : 0;
				if(m_speed < m_vlow) m_speed = m_vlow; //Pour être sûr d'avoir la bonne valeur.
			}
			break;

			case 3:
			if(m_step >= m_step_total)
			{
				m_phase++;
			}
			break;

			case 4:
			m_speed = 0; //On arrête tout
			m_phase = 0; //Phase départ.
			break

			default:break;
		}
		//-=Fin de la section=-//
		
		
		//-=Retour fonction=-//
		r = (pwm_t)(m_speed > m_vmax ? m_vmax : m_speed); //Limitation de la vitesse à VMAX (1023 par défaut)
		return r; //Retour valeur.
		//-=Fin de la section=-//
	}

	bool MotorMovementControl::available()
	{
		return m_phase == 0; //Le moteur a fini sa course si jamais la phase de contrôle est à 0
	}
}
