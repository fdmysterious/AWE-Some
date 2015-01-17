/****************
 *-=Motors.hpp=-*
 ****************
 
 Auteur : Florian Dupeyron (My?terious)
 Description : R�f�rence les moteurs exisntants
*/
#ifndef HEADER_OUT_MOTORS
#define HEADER_OUT_MOTORS

//-=Inclusion des headers=-//
#include "../time/TransitionalValue.hpp"
#include "MotorControl.hpp"
#include "MotorMovementControl.hpp"
//-=Fin de la section=-//

namespace out
{
	extern MotorControl mot;
	extern time::TransitionalValue mot_duty;
	extern out::MotorMovementControl mot_ctrl;
}

#endif