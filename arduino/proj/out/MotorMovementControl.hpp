/******************************
 *-=MotorMovementControl.hpp=-*
 ******************************
 
 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de gérer le mouvement du moteur.
*/
#ifndef HEADER_OUT_MOTORMOVEMENTCONTROL
#define HEADER_OUT_MOTORMOVEMENTCONTROL

//-=Inclusion des headers=-//
#include <Arduino.h>
#include <inttypes.h>
//-=Fin de la section=-//

//-=Configuration=-//
#define MOTORMOVEMENTCONTROL_STEP_LOW_PERCENT 10.f //Pourcentage du mouvement total pendant lequel le moteur va lentement.
//-=Fin de la section=-//


namespace out
{
	class MotorMovementControl
	{
		public:
		//-=Typedefs=-//
		typedef uint64_t	step_t;
		typedef float		speed_t;
		typedef uint16_t	pwm_t;
		//-=Fin de la section=-//
		
		public:
		MotorMovementControl(speed_t vel, speed_t vlow, speed_t vmax);
		~MotorMovementControl();
		
		void init(step_t sTotal);
		pwm_t tick();

		bool available();
		
		private:
		//-=Gestion des pas=-//
		step_t m_step;
		step_t m_step_total;
		step_t m_step_low;
		step_t m_step_acdc;
		//-=Fin de la section=-//
		
		//-=Gestion vitesse=-//
		//--Vitesses
		speed_t m_vel;
		speed_t m_vlow;
		speed_t m_vmax;
		
		speed_t m_speed;
		//-=Fin de la section=-//
		
		//-=Informations d'état=-//
		uint8_t m_phase;
		//-=Fin de la section=-//
	};
}

#endif
