/**************
 *-=parser.c=-*
 **************

 Auteur : Florian Dupeyron (My?terious)
 Description : Permet de gérer le parsage des expressions
*/

//-=Inclusion des headers=-//
#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../sys/log.h"
//-=Fin de la section=-//

struct Parser_t core_parser_create()
{
	struct Parser_t p =
	{
		.bIndex = 0,
		.fName = NULL,
		.fArgs = NULL
	};

	core_parser_buffer_reset(&p);

	return p;
}

uint8_t core_parser_update(struct Parser_t * p, const char * buf)
{
	size_t i = 0;

	uint8_t status = 0;

	char * c; //Pointeur de la première occurence du caractère ','

	for(i = 0; i < strlen(buf); i++)
	{
		if(buf[i] == ';') //Fin de l'instruction.
		{
			//-=Libération de la mémoire si besoin=-//
			if(p->fName != NULL) free(p->fName);
			if(p->fArgs != NULL) free(p->fArgs);
			//-=Fin de la section=-//
			
			//-=Récupération du nom de la fonction=-//
			c = strchr(buf, ',');
			if(c == NULL) //La fonction ne possède aucun argument
			{
				//-=Allocation mémoire=-//
				p->fName = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
				bzero(p->fName, sizeof(p->fName));
				//-=Fin de la section=-//

				//-=Copie=-//
				strncpy(p->fName, buf, strlen(buf) - 1);
				//-=Fin de la section=-//
			}

			else
			{
				size_t sep = c - buf + 1; //Permet de récupérer l'index de la fin du nom.

				//-=Récupération du nom=-//
				//--Allocation mémoire
				p->fName = (char*)malloc(sizeof(char) * sep);
				bzero(p->fName, sizeof(p->fName));

				//--Copie
				strncpy(p->fName, buf, sep - 1);
				//-=Fin de la section=-//
				
				//-=Récupération des arguments=-//
				//--Allocation mémoire
				p->fArgs = (char*)malloc(sizeof(char) * strlen(c + 1));

				//--Copie
				strncpy(p->fArgs, c + 1, strlen(c + 1) - 1);
				//-=Fin de la section=-//
			}
			//-=Fin de la section=-//

			//-=Reset buffer=-//
			core_parser_buffer_reset(p);
			//-=Fin de la section=-//

			status = 1; //On a du nouveau !
		}

		else
		{
			p->buffer[p->bIndex] = buf[i];	//Ajout du caractère au buffer
			p->bIndex++;			//on Incrémente l'index.
		}
	}

	return status;
}

char * core_parser_get_name(struct Parser_t * p)
{
	return p->fName;
}

char * core_parser_get_args(struct Parser_t * p)
{
	return p->fArgs;
}

void core_parser_buffer_reset(struct Parser_t * p)
{
	//-=Reset buffer=-//
	bzero(p->buffer, PARSER_BUFFER_SIZE);
	//-=Fin de la section=-//
	
	//-=Reset compteur=-//
	p->bIndex = 0;
	//-=Fin de la section=-//
}
