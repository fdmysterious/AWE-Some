/********************
 *-=query_parser.h=-*
 ********************

 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de parser les arguments d'une requête.
*/
#ifndef HEADER_QUERY_PARSER
#define HEADER_QUERY_PARSER

//-=Inclusion des headers=-//
#include <inttypes.h>
//-=Fin de la section=-//

//-=Defines=-//
#define QUERY_PARSER_FOUND 1
#define QUERY_PARSER_DONE  0

#define QUERY_PARSER_BUFFER_SIZE 32
//-=Fin de la section=-//

//-=structures=-//
struct QueryParser_Arg_t
{
	char name[QUERY_PARSER_BUFFER_SIZE];
	char value[QUERY_PARSER_BUFFER_SIZE];
};
//-=Fin de la section=-//

//-=Fonctions=-//
uint8_t	fcgi_query_parse(struct QueryParser_Arg_t * a, char * str);
void	fcgi_query_parser_buffer_reset(struct QueryParser_Arg_t * a);
//-=Fin de la section=-//


#endif
