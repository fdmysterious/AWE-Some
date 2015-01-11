/**************
 *-=parser.h=-*
 **************

 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de parser les instructions.
*/
#ifndef HEADER_COM_PARSER
#define HEADER_COM_PARSER

//-=Inclusion des headers=-//
#include <stdlib.h>
#include <inttypes.h>
//-=Fin de la section=-//

//-=Configuration=-//
#define PARSER_BUFFER_SIZE 1024
//-=Fin de la section=-//

//-=Structures=-//
struct Parser_t
{
	char buffer[PARSER_BUFFER_SIZE];
	int bIndex;	//Index dans le buffer

	char * fName;	//Nom de la fonction appelée
	char * fArgs;	//Arguments de la fonction appelée
};
//-=Fin de la section=-//

//-=Fonctions=-//
struct Parser_t core_parser_create();

uint8_t core_parser_update(struct Parser_t * p, const char * buf); //Met à jour le parser à partir du buffer donné.
char *	core_parser_get_name(struct Parser_t * p); //Obtient le nom du Parser
char *	core_parser_get_args(struct Parser_t * p); //Obtient les arguments du Parser

//-=Gestion du buffer=-//
void	core_parser_buffer_reset(struct Parser_t * p);
//-=Fin de la section=-//

//-=Fin de la section=-//

#endif
