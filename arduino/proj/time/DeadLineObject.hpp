/************************
 *-=DeadLineObject.hpp=-*
 ************************

 Auteur : Florian Dupeyron (My?terious)
 Description : C'est un objet qui appelle une fonction particulière quand un certain temps
 c'est éculé.
*/
#ifndef HEADER_TIME_DEADLINEOBJECT
#define HEADER_TIME_DEADLINEOBJECT

//-=Inclusion des headers=-//
//#include <Arduino.h>
#include "DeltaObject.hpp"
//-=Fin de la section=-//

namespace time
{
	class DeadLineObject : public DeltaObject
	{
		public:
		DeadLineObject();
		virtual ~DeadLineObject();

		//-=Fonctions de réglage=-//
		void setPeriod(const uint64_t p); //Permet de définir le temps au bout duquel le compteur est fini.
		void setInterval(bool enable = true);

		void start();
		void pause();
		void reset();
		void stop();
		//-=Fin de la section=-//

		//-=Fonctions de mise à jour=-//
		virtual void update(const uint32_t dt);
		//-=Fin de la section=-//

		protected:
		virtual void update_imp() = 0; //Fonctions de mise à jour spéciale, appelée que quand le temps est écoulé.

		protected:
		//-=Configuration=-//
		uint64_t	m_period;	//Indique le nombre de millisecondes qui doivent s'écouler
		uint64_t	m_time;		//Compteur indiquant combien de temps s'est écoulé depuis le début.
		bool		m_run;		//Indique s'il faut continuer de compter ou pas.
		bool		m_interval;	//Indique si l'objet fonctionne en mode intervalle ou lancer unique.
		//-=Fin de la section=-//
		
	};
}

#endif
