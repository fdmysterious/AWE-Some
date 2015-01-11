/********************
 *-=query_parser.c=-*
 ********************

 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de parser les arguments d'une requête.
*/

//-=Inclusion des header=-//
#include <stdlib.h>
#include <string.h>
#include "query_parser.h"
//-=Fin de la section=-//

uint8_t fcgi_query_parse(struct QueryParser_Arg_t * a, char * str)
{
	static char * tok = NULL;

	//-=Buffer reset=-//
	fcgi_query_parser_buffer_reset(a);
	//-=Fin de la section=-//
	
	//-=Recherche=-//
	tok = strtok(str, "&\r"); //Séparateurs : &, fin d'instruction
	if(tok == NULL) return QUERY_PARSER_DONE; //On a rien trouvé.
	//-=Fin de la section=-//

	//-=Parsage token=-//
	char * sep = strchr(tok, '='); //Recherche du égal dans le token
	if(sep == NULL) //Le signe n'a pas été trouvé.
	{
		strcpy(a->name, tok);
		strcpy(a->value, "null"); //La valeur est nulle.
	}

	else
	{
		//-=Récupération position du séparateur=-//
		size_t iSep = sep - tok + 1;
		//-=Fin de la section=-//

		//-=Copie=-//
		//--Nom
		strncpy(a->name, tok, iSep - 1); //-1 pour ne pas inclure le =
		
		//--Valeur
		strcpy(a->value, sep + 1); //+1 pour le pas inclure le =
		//-=Fin de la section=-//
	}
	//-=Fin de la section=-//
	
	return QUERY_PARSER_FOUND;
}

void fcgi_query_parser_buffer_reset(struct QueryParser_Arg_t * a)
{
	bzero(a->name, QUERY_PARSER_BUFFER_SIZE);
	bzero(a->value, QUERY_PARSER_BUFFER_SIZE);
}
