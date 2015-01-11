/************************
 *-=DeadLineObject.cpp=-*
 ************************

 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de gérer un objet avec une tempo.
*/

//-=Inclusion des headers=-//
#include "DeadLineObject.hpp"
//-=Fin de la section=-//

namespace time
{
	DeadLineObject::DeadLineObject() :
		m_period(0),
		m_time(0),
		m_run(false),
		m_interval(false)
	{
	}

	DeadLineObject::~DeadLineObject()
	{
	}

	void DeadLineObject::setPeriod(const uint64_t p)
	{
		m_period = p;
	}

	void DeadLineObject::start()
	{
		m_run = m_period > 0; //On démarre que s'il y a un temps minimum
	}

	void DeadLineObject::pause()
	{
		m_run = false;
	}
	
	void DeadLineObject::reset()
	{
		m_time = 0;
	}
	
	void DeadLineObject::stop()
	{
		pause();
		reset();
	}

	void DeadLineObject::update(const uint32_t dt)
	{
		//-=Mise a jour dt=-//
		m_delta = dt;
		//-=Fin de la section=-//
		
		//-=Mise a jour compteur=-//
		if(m_run)
		{
			m_time += dt;
			if(m_time >= m_period)
			{
				switch(m_interval)
				{
					case true:
					m_time = 0;

					case false:
					m_run = false;
					break;
				}
				update_imp(); //On appelle la fonction implémentée
			}
		}
		//-=Fin de la section=-//
	}
}

