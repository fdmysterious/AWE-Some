/****************
 *-=Motors.cpp=-*
 ****************
 
 Auteur : Florian Dupeyron
 Description : Permet d'avoir acc�s aux moteurs.
*/

//-=Inclusion des headers=-//
#include "Motors.hpp"
//-=Fin de la section=-//

namespace out
{
	MotorControl mot(10, 9);
	time::TransitionalValue mot_duty(0.f, 0.f, 0.5f);
	out::MotorMovementControl mot_ctrl(0.5f, 200.f, 1023.f);
}