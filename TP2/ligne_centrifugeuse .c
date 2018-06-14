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

/*agit sur la ligne reçue en référence, remplit son tableau de centrifugeuses 
neuves (avec configuration de départ du TP1), va mettre nb centrifugeuses 
EN_FONCTION et le nombre constant EN_ATTENTE, tous les champs du struct doivent
être bien ajustés.Elle retourne 1 pour succès ou 0 sinon (un nb trop grand).*/
int init_ligne_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, uint nb) {
	
	if (nb <= NB_BITS - 1) {

		//initialiser tout
		for (int i = 0; i < NB_BITS; i++) {
			ptr_lig->tab_cnt[i] = init_centrifugeuse();
		}

		int i = 2;
		uint cnt_fonct_restant = nb;

		for (int j = 0; cnt_fonct_restant > 0; j++) {
			if (j == i) {  //pour les 0
				j++;
				i += 3;	
			}
			
			set_en_attente(&ptr_lig->tab_cnt[j]);
			set_en_fonction(&ptr_lig->tab_cnt[j]);
			ptr_lig->config_fonction = set_bit(ptr_lig->config_fonction, j);
			--cnt_fonct_restant;
			
			if (cnt_fonct_restant == 0) {
				for (int i = j; i = j+2; i++) {
					ptr_lig->config_attente = set_bit(ptr_lig->config_attente, i);
				}
			}
				
		}

		for (int i = 0; i < NB_BITS; i++) {
			if (GET_BIT(ptr_lig->config_attente, i) != 1 && 
				GET_BIT(ptr_lig->config_fonction, i) != 1) {
				ptr_lig->config_arret = set_bit(ptr_lig->config_arret, i);
			}
		}
		return 1;
	}
	return 0;
}

/*ajoute si possible une centrifugeuse  EN_FONCTION dans la ligne.  Retour de 1
si réussi, 0 sinon (configuration impossible).*/
int ajouter_cnt(t_ligne_centrifugeuse *ptr_lig) {
	//if (configuration_valide(ptr_lig->))
}

/*
réduit de un le nombre de  centrifugeuses EN_FONCTION dans la ligne.  
Retour de 1 si réussi, 0 sinon (aucune EN_FONCTION).
*/
int reduire_cnt(t_ligne_centrifugeuse *ptr_lig) {
	/*int i = 0;
	while (i < NB_BITS) {
		if (GET_BIT(ptr_lig->config_fonction, i) != 1) {
			//return 0;
		}
		i++;
	}*/
	
	return 0;
}
void toc_ligne(t_ligne_centrifugeuse *ptr_lig) {}
t_centrifugeuse remplacer_cnt(t_ligne_centrifugeuse *ptr_lig, uint pos) {}

/*qui retourne le train de bits de la ligne qui donne les positions des 
centrifugeuses dans cet état. SPEC : Le second paramètre doit être une des 
quatre constantes d’état sinon le résultat obtenu n’a pas de sens.*/
uint get_en_etat(const t_ligne_centrifugeuse * ptr_lig, int etat) {

	if (etat <= EN_FONCTION) {
		switch (etat) {
			case EN_ARRET:
				return ptr_lig->config_fonction;
				break;
			case EN_ATTENTE:
				return ptr_lig->config_attente;
				break;
			case EN_FONCTION:
				return ptr_lig->config_fonction;
				break;
			default:
				return ptr_lig->config_bris;
		}
	}
	return 0;
}
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


