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
/****************CODE EMPRUNTE**********************
*****************SOURCE: TP1************************
*************PAR: Youssef Soliman*******************
****************************************************/
unsigned short configuration_valide(uint valeur, unsigned short nb_bits_actifs) {
	//TO-DO: Modifier fonction configuration_valide
	int nb_actif = 0;
	int nb_actif_contigus = 0;

	if (nb_bits_actifs < NB_BITS) {
		for (int i = 0; i <= NB_BITS - 1; i++) {
			if (GET_BIT(valeur, i)) {
				nb_actif++;
				nb_actif_contigus++;
			}
			else {
				nb_actif_contigus = 0;
			}

			if (nb_actif_contigus > 2) {
				return 0;
			}
			}
		if (nb_actif == nb_bits_actifs && nb_actif_contigus <= 2) {
			return 1;
		}
		}
	return 0;
}


