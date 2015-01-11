/****************
 *-=Motors.cpp=-*
 ****************
 
 Auteur : Florian Dupeyron
 Description : Permet d'avoir accès aux moteurs.
*/

//-=Inclusion des headers=-//
#include "Motors.hpp"
//-=Fin de la section=-//

namespace out
{
	MotorControl mot(10, 9);
	time::TransitionalValue mot_duty(0.f, 0.f, 0.5f);
}