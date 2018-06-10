/*===========================================================*/
/* 	INF145 - Gabarit (template) de base d'un programme en C. */
/*===========================================================*/

/*
Cette section servira plus tard dans l'écriture du fichier "*.h" d'un module.

Module :
Par    :
Date   :

Ce module offre .....
avec ici plein de commentaires ESSENTIEL À TOUT CLIENT ÉVENTUEL du
module, chaque élément public (constante, type, fonction) offert
par ce module doit être bien expliqué ici.
*/


/*=========================================================*/
/*
Ce gabarit d'un programme en première semaine de C contient un "main()".

N'oubliez pas de commenter votre code. Préférablement au fûr et à mesure que vous
etes en train d'écrire.	Du code correct, bien testé mais sans indication du
problème résolu, ça vaut quoi?
*/

/*=========================================================*/
//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

#include "centrifugeuse.h"
// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "ligne_centrifugeuse .h"

int init_ligne_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, uint nb) {}
int ajouter_cnt(t_ligne_centrifugeuse *ptr_lig) {}
int reduire_cnt(t_ligne_centrifugeuse *ptr_lig) {}
void toc_ligne(t_ligne_centrifugeuse *ptr_lig) {}
t_centrifugeuse remplacer_cnt(t_ligne_centrifugeuse *ptr_lig, uint pos) {}
uint get_en_etat(const t_ligne_centrifugeuse * ptr_lig, int etat) {}
t_centrifugeuse get_centrifugeuse(const t_ligne_centrifugeuse *ptr_lig, uint  pos) {}
static  void permuter_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, uint pos1, uint pos2) {}
void print_ligne_centrifugeuse(void) {}

/*fonction configuration_valide du TP1*/
unsigned short configuration_valide(uint valeur, unsigned short nb_bits_actifs) {
	//TO-DO: Modifier fonction configuration_valide
	return 0;
}

/*
*****************SOURCE: TP1************************
********PAR : H. Saulnier,  F. Henri, E. Thé********
****************************************************/
const char * bits2string(unsigned int nombre) {
	//TO-DO: Modifier fonction bits2string
	// un buffer de taille de 200 char c'est plus que suffisant
	// buffer[] est une variable locale statique dont la position est permanente
	/*static char buffer[200] = { 0 };
	int i;      // iterateur

				// s'assure de l'indicateur de fin de chaine 
	buffer[NB_BITS] = 0;

	// boucle d'assignation de chaque bit obtenu 
	// de get_bit dans la string ( mais en ordre inverse )
	for (i = 0; i< NB_BITS; i += 1) {
		buffer[NB_BITS - 1 - i] = GET_BIT(nombre, i) ? '1' : '0';
	}

	// retour de la string
	return buffer;*/
}


