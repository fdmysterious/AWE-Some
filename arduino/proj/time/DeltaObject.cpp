/*********************
 *-=DeltaObject.cpp=-*
 *********************

	Auteur : Florian Dupeyron (My?terious)
	Description : Objet fournissant des utilitaires qui aident à mettre à jour
		un objet dont l'état évolue dans le temps;
*/

//-=Inclusion des headers=-//
#include "DeltaObject.hpp"
//-=Fin de la section=-//

namespace time
{
	DeltaObject::DeltaObject()
	{
	}

	DeltaObject::~DeltaObject()
	{
	}

	void DeltaObject::update(const uint32_t dt)
	{
		m_delta = dt;
		update_imp(); // On appelle la fonction implémentée par l'utilisateur pour l'instance
	}
}
