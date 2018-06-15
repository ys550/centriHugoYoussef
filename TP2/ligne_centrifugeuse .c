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
#include "ligne_centrifugeuse .h"
#include "op_bits.h"
// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>


/*agit sur la ligne reçue en référence, remplit son tableau de centrifugeuses 
neuves (avec configuration de départ du TP1), va mettre nb centrifugeuses 
EN_FONCTION et le nombre constant EN_ATTENTE, tous les champs du struct doivent
être bien ajustés.Elle retourne 1 pour succès ou 0 sinon (un nb trop grand).*/
int init_ligne_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, uint nb) {
	
	if (nb <= NB_BITS - 1) {

		//initialiser tout
		ptr_lig->config_fonction = 0;
		ptr_lig->config_bris = 0;
		ptr_lig->config_attente = 0;
		ptr_lig->config_arret = 0;
		for (int i = 0; i < NB_BITS; i++) {
			ptr_lig->tab_cnt[i] = init_centrifugeuse();
			ptr_lig->config_arret = SET_BIT(ptr_lig->config_arret, i);
		}

		int i = 2;
		uint cnt_fonct_restant = nb;

		for (int j = 0; cnt_fonct_restant > 0; j++) {
			if (j == i) {  //pour les positions
				j++;	//position pour les 1
				i += 3;	//position pour les 0
			}
			
			set_en_attente(&ptr_lig->tab_cnt[j]);
			set_en_fonction(&ptr_lig->tab_cnt[j]);
			ptr_lig->config_fonction = SET_BIT(ptr_lig->config_fonction, j);
			--cnt_fonct_restant;
			
			/*
			 *si nb < NB_BITS : il a au moins 1 bits de libre pour inserer 1
			 bit en attente.
			 si nb = 31 : il reste 1 de libre. On peut donc seulement inserrer 1
			 centrifigueuse en attente.
			 si nb = 30 : il reste 2 de libre. On peut donc inserrer 2
			 centrifigueuse en attente.
			 */
			//lorsqu'il est possible d'ajouter NBR_K_EN_ATTENTE (2) centri en attente
			if (cnt_fonct_restant == 0 && ( (j + NBR_K_EN_ATTENTE) < (NB_BITS - 
				NBR_K_EN_ATTENTE))) {
				for (int i = j + 1; i = (j + NBR_K_EN_ATTENTE); i++) {
					//on met les derniers libres les plus a droite en attente
					set_en_attente(&ptr_lig->tab_cnt[i]);
					ptr_lig->config_attente = SET_BIT(ptr_lig->config_attente, i);
				}
			}
			//lorsqu'il est possible d'ajouter NBR_K_EN_ATTENTE - 1 (1) cnt en attente
			else if (cnt_fonct_restant == 0 && ((j + (NBR_K_EN_ATTENTE - 1)) < (NB_BITS -
				(NBR_K_EN_ATTENTE - 1)))) {
				for (int i = j + 1; i = (j + (NBR_K_EN_ATTENTE - 1)); i++) {
					//on met les derniers libres les plus a droite en attente
					ptr_lig->config_attente = SET_BIT(ptr_lig->config_attente, i);
					set_en_attente(&ptr_lig->tab_cnt[i]);
				}
			}
				
		}

		for (int i = 0; i < NB_BITS; i++) {
			if (GET_BIT(ptr_lig->config_attente, i) != 1 && 
				GET_BIT(ptr_lig->config_fonction, i) != 1 && 
				GET_BIT(ptr_lig->config_bris, i) != 1) {
				ptr_lig->config_arret = SET_BIT(ptr_lig->config_arret, i);
				set_en_arret(&ptr_lig->tab_cnt[i]);
			}
		}
		return 1;
	}
	return 0;
}

/*ajoute si possible une centrifugeuse  EN_FONCTION dans la ligne.  Retour de 1
si réussi, 0 sinon (configuration impossible).*/
int ajouter_cnt(t_ligne_centrifugeuse * ptr_lig) {
	for (int i = 0; i < NB_BITS; i++) {
		if (GET_BIT(ptr_lig->config_attente, i) == 1) {
			ptr_lig->config_fonction = SET_BIT(ptr_lig->config_fonction, i);
			ptr_lig->config_attente = CLEAR_BIT(ptr_lig->config_attente, i);
			set_en_fonction(&ptr_lig->tab_cnt[i]);
			return 1;
		}
		else if (GET_BIT(ptr_lig->config_arret, i) == 1) {
			ptr_lig->config_fonction = SET_BIT(ptr_lig->config_fonction, i);
			ptr_lig->config_arret = CLEAR_BIT(ptr_lig->config_arret, i);
			set_en_fonction(&ptr_lig->tab_cnt[i]);
			return 1;
		}
	}
	return 0;
}

/*
réduit de un le nombre de  centrifugeuses EN_FONCTION dans la ligne.  
Retour de 1 si réussi, 0 sinon (aucune EN_FONCTION).
*/
int reduire_cnt(t_ligne_centrifugeuse * ptr_lig) {
	for (int i = NB_BITS - 1; i >= 0; i--) {
		if (GET_BIT(ptr_lig->config_fonction, i) == 1) {
			ptr_lig->config_fonction = CLEAR_BIT(ptr_lig->config_fonction, i);
			ptr_lig->config_attente = SET_BIT(ptr_lig->config_attente, i);
			set_en_attente(&ptr_lig->tab_cnt[i]);
			return 1;
		}
	}
	return 0;
}
void toc_ligne(t_ligne_centrifugeuse * ptr_lig) {}
t_centrifugeuse remplacer_cnt(t_ligne_centrifugeuse * ptr_lig, uint pos) {}

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
/*retourne une copie de la centrifugeuse à cette position dans le tableau. Elle
retourne une centrifugeuse dont tous les membres sont 0 si la position est 
non-valide.*/
t_centrifugeuse get_centrifugeuse(const t_ligne_centrifugeuse * ptr_lig, uint  pos) {
	if (pos < NB_BITS) {
		return ptr_lig->tab_cnt[pos];
	}

	t_centrifugeuse cnt_membres_0;
	cnt_membres_0 = init_centrifugeuse();
	cnt_membres_0.etat = 0;
	cnt_membres_0.prob_bris = 0;
	cnt_membres_0.compte_rebours = 0;
	
	return cnt_membres_0;
}
static  void permuter_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, uint pos1, uint pos2) {}

/*fonction d’affichage des lignes de centrifugeuses*/
void print_ligne_centrifugeuse(const t_ligne_centrifugeuse * ptr_lig) {
	printf("\n\n config_fonction == %s ", bits2string(ptr_lig->config_fonction));
	printf("\n\n config_attente  == %s ", bits2string(ptr_lig->config_attente));
	printf("\n\n config_arret    == %s ", bits2string(ptr_lig->config_arret));
	printf("\n\n config_bris     == %s ", bits2string(ptr_lig->config_bris));
}

/*fonction configuration_valide du TP1*/
/****************CODE EMPRUNTE**********************
*****************SOURCE: TP1************************
*************PAR: Youssef Soliman*******************
****************************************************/
static unsigned short configuration_valide(uint valeur, unsigned short nb_bits_actifs) {
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


