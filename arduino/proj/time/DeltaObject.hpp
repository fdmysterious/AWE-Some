/*********************
 *-=DeltaObject.hpp=-*
 *********************

	Auteur : Florian Dupeyron (My?terious)
	Description : Objet fournissant des utilitaires qui aident à mettre à jour
		un objet dont l'état évolue dans le temps;
*/
#ifndef HEADER_TIME_DELTAOBJECT
#define HEADER_TIME_DELTAOBJECT

//-=Inclusion des headers=-//
//#include <Arduino.h>
#include <inttypes.h>
//-=Fin de la section=-//

namespace time
{
	class DeltaObject
	{
		public:
		DeltaObject();
		virtual ~DeltaObject();

		//-=Fonctions spécifiques=-//
		virtual void update(const uint32_t dt);
		//-=Fin de la section=-//

		protected:
		//-=Fonctions virtuelles pures=-//
		virtual void update_imp() = 0;
		//-=Fin de la section=-//

		protected:
		//-=Accès au temps=-//
		uint32_t m_delta; //Temps delta en millisecondes
		//-=Fin de la section=-//
	};
}

#endif
