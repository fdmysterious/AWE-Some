/***********************
 *-=Interpolation.hpp=-*
 ***********************

 Auteur : Florian Dupeyron (My?terious)
 Description : Fonctions d'interpolation simples.
*/
#ifndef HEADER_MATH_INTERPOLATION
#define HEADER_MATH_INTERPOLATION

//-=Inclusion des headers=-//
//-=Fin de la section=-//

namespace math
{
	template<typename T>
	class Interpolation
	{
		public:
		static T linear(T x, T y1, T y2, T x2);
	};
}

#include "Interpolation.hpp.inc"

#endif
