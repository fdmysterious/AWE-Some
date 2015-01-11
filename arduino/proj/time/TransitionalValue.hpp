/***************************
 *-=TransitionalValue.hpp=-*
 ***************************

 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de gérer une valeur qui se met à jour grâce à un coef. directeur.
*/
#ifndef HEADER_TIME_TRANSITIONALVALUE
#define HEADER_TIME_TRANSITIONALVALUE

//-=Inclusion des headers=-//
#include "DeltaObject.hpp"
#include <inttypes.h>
//-=Fin de la section=-//

namespace time
{
	class TransitionalValue : public DeltaObject
	{
		public:
		TransitionalValue();
		TransitionalValue(float vStart, float vGoal, float vel);
		~TransitionalValue();

		//-=Fonctions de réglage=-//
		void setCurrentValue(float v);
		void setGoalValue(float g);
		//-=Fin de la section=-//

		//-=Contrôle de la mise à jour de la valeur=-//
		void start();
		void pause();
		//-=Fin de la section=-//
		
		//-=Obtention valeur=-//
		float value();
		float goal();
		
		bool running();
		//-=Fin de la section=-//
		
		protected:
		//-=Fonction mise à jour=-//
		void update_imp();
		//-=Fin de la section=-//
		
		protected:
		//-=Paramètres=-//
		float	m_vel; //Vélocité (coefficient directeur)
		//-=Fin de la section=-//
		
		//-=Valeurs=-//
		float	m_value_current;
		float	m_value_goal;
		//-=Fin de la section=-//

		//-=Variables internes de fonctionnement=-//
		bool	m_run;	//Permet de savoir s'il faut effectuer des calculs ou pas.
		//-=Fin de la section=-//
	};
}
#endif
