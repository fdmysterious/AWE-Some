/***************************
 *-=TransitionalValue.hpp=-*
 ***************************

 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de gérer une valeur qui se met à jour grâce à un coef. directeur.
*/

//-=Inclusion des header=-//
#include "TransitionalValue.hpp"
#include "../math/Arithmetic.hpp"
#include <math.h>
//-=Fin de la section=-//

namespace time
{
	TransitionalValue::TransitionalValue() :
		m_vel(0.f),
		m_value_current(0.f),
		m_value_goal(0.f),
		m_run(false)
	{
	}

	TransitionalValue::TransitionalValue(float vStart, float vGoal, float vel) :
		m_vel(vel),
		m_value_current(vStart),
		m_value_goal(vGoal)
	{
		start(); //Lance s'il faut la mise à jour de la valeur.
	}
	
	TransitionalValue::~TransitionalValue()
	{
	}

	void TransitionalValue::setCurrentValue(float v)
	{
		pause(); 		//On arrête les mises à jour de la valeur.
		m_value_current = v;	//On écrit par dessus.
	}

	void TransitionalValue::setGoalValue(float g)
	{
		pause();		//On arrête les mises à jour courantes
		m_value_goal = g;
		start();		//On démarre les calculs !
	}

	void TransitionalValue::start()
	{
		if(m_value_goal != m_value_current) m_run = true; //On démarre que si le calcul s'avère utile.
	}

	void TransitionalValue::pause()
	{
		m_run = false; //Mon dieu c'est dur...
	}

	float TransitionalValue::value()
	{
		return m_value_current;
	}

	float TransitionalValue::goal()
	{
		return m_value_goal;
	}
	
	bool TransitionalValue::running()
	{
		return m_run;
	}

	void TransitionalValue::update_imp()
	{
		//calcul de l'algorithme :
		//On met à jour la valeur en fonction du dt mesuré.
		//Pour cela, on multiplie la valeur de dt avec le coef directeur m_vel,
		//que l'on multiplie par la valeur du signe (1, 0, -1)
		//a adopter.

		m_value_current += m_vel * math::Arithmetic<float>::sign(m_value_goal - m_value_current); //Et voilà le travail !

		//-=On continue les calculs ???=-//
		//-=Fin de la section=-//
		
	}
}

