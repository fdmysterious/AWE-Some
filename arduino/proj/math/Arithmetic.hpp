/****************
 *-=Arithmetic=-*
 ****************

 Auteur : Florian Dupeyron
 Description : Quelques fonctions arithmétiques simples
*/
#ifndef HEADER_MATH_ARITHLETIC
#define HEADER_MATH_ARITHLETIC

//-=Inclusion des headers=-//
//-=Fin de la section=-//

namespace math
{
	template<typename T>
	//typedef float T;
	class Arithmetic
	{
		public:
		static T sign(T n) //Retourne le signe d'un nombre(1, 0 et -1)
		{
			return (n > 0) - (n < 0);
		}
	};
}


#endif

