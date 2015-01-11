/***************************
 *-=Interpolation.hpp.inc=-*
 ***************************

 Auteur : Florian Dupeyron (My?terious)
 Description : Fonctions d'interpolation simples.
*/

//-=Inclusion des headers=-//
//-=Fin de la section=-//

namespace math
{
	template<typename T>
	T Interpolation::linear(T x, T y1, T y2, T x2)
	{
		return y1 + x * ((y2 - y1) / x2);
	}
}
