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
	
	if (nb <= NB_BITS) {

		//initialiser tout
		ptr_lig->config_fonction = 0;
		ptr_lig->config_bris = 0;
		ptr_lig->config_attente = 0;
		ptr_lig->config_arret = 0;
		for (int i = 0; i < NB_BITS; i++) {
			ptr_lig->tab_cnt[i] = init_centrifugeuse();
			//init_centrifugeuse() mets les cnt en etat ARRET
			ptr_lig->config_arret = SET_BIT(ptr_lig->config_arret, i);
		}

		int i = 2;
		uint cnt_fonct_restant = nb;

		for (int j = 0; cnt_fonct_restant > 0; j++) {
			if (j == i) {  //pour les positions
				j++;	//position pour les 1
				i += 3;	//position pour les 0
			}
			
			//set en fonction en respectant la regle <= 2 en contigus
			set_en_attente(&ptr_lig->tab_cnt[j]);
			set_en_fonction(&ptr_lig->tab_cnt[j]);
			ptr_lig->config_fonction = SET_BIT(ptr_lig->config_fonction, j);
			--cnt_fonct_restant;
			
			/*On mets ceux qui restent en attente. Le nombre de centri en 
			attente depend de la constante NBR_K_EN_ATTENTE*/
			if (cnt_fonct_restant == 0) {
				/*calcule combien de bits libre dans la ligne il reste pour 
				mettre en attente*/
				int nbr_k_possible = ((NB_BITS - 1) - j);

				//Valeur max de nbr_k_possible = NBR_K_EN_ATTENTE
				if (nbr_k_possible > NBR_K_EN_ATTENTE) {
					nbr_k_possible = NBR_K_EN_ATTENTE;
				}

				if (nbr_k_possible != 0) {
					for (int i = j + 1; i <= (j + nbr_k_possible); i++) {
						/*on met les derniers libres les plus a droite en attente*/
						set_en_attente(&ptr_lig->tab_cnt[i]);
						ptr_lig->config_attente = SET_BIT(ptr_lig->config_attente, i);
					}
				}	
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
		if (GET_BIT(ptr_lig->config_attente, i) == 1 || 
			GET_BIT(ptr_lig->config_arret, i) == 1) {

			set_en_fonction(&ptr_lig->tab_cnt[i]);
			ptr_lig->config_fonction = SET_BIT(ptr_lig->config_fonction, i);
			ptr_lig->config_attente = CLEAR_BIT(ptr_lig->config_attente, i);
			ptr_lig->config_arret = CLEAR_BIT(ptr_lig->config_arret, i);
			
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
	//Reduit celle la plus a gauche (a la fin)
	for (int i = NB_BITS - 1; i >= 0; i--) {
		if (GET_BIT(ptr_lig->config_fonction, i) == 1) {
			/*reduit de 1 une cnt EN_FONCTION en changeant sont etat a 
			EN_ATTENTE*/
			set_en_attente(&ptr_lig->tab_cnt[i]);
			ptr_lig->config_fonction = CLEAR_BIT(ptr_lig->config_fonction, i);
			ptr_lig->config_attente = SET_BIT(ptr_lig->config_attente, i);
			return 1;
		}
	}
	return 0;
}
/*déclenche la fonction toc_centrifugeuse() pour chacune des centrifugeuses du 
tableau et réagit correctement à tout changement d’état d’une des 
centrifugeuses.*/
void toc_ligne(t_ligne_centrifugeuse * ptr_lig) {
	//***************A TERMINER************
	for (int i = 0; i < NB_BITS; i++) {
		toc_centrifugeuse(&ptr_lig->tab_cnt[i]);
	}
	/**********************************/
}
/*si la position est valide et si cette centrifugeuse du tableau n’est ni 
EN_FONCTION ni EN_ATTENTE,  une  centrifugeuse neuve remplace celle à la 
position donnée dans le tableau. La fonction retourne une copie de la 
centrifugeuse éliminée, sinon une centrifugeuse dont tous les membres sont 0 
est retournée.*/
t_centrifugeuse remplacer_cnt(t_ligne_centrifugeuse * ptr_lig, uint pos) {
	if (pos < NB_BITS && ptr_lig->tab_cnt[pos].etat != EN_FONCTION && 
		ptr_lig->tab_cnt[pos].etat != EN_ATTENTE) {
		
		t_centrifugeuse copie_cnt_elimine = ptr_lig->tab_cnt[pos];

		/*Il n'est pas necessaire de changer (clear bit) les config EN_FONCTION
		et EN_ATTENTE, car car on ne les remplace pas s'il sont dans cet etat
		il seront donc deja a 0 si on remplace la cnt.
		*/

		//changer config bris au cas que celle remplacer ete brise
		ptr_lig->config_bris = CLEAR_BIT(ptr_lig->config_bris, pos);
		//insere la nouvelle centri init_centri-> etat = en arret
		ptr_lig->tab_cnt[pos] = init_centrifugeuse();
		//la nouvelle centri est en etat arret
		ptr_lig->config_arret = SET_BIT(ptr_lig->config_arret, pos);

		return copie_cnt_elimine;
	}
	return centrifugeuse_membres_0();
}

/*qui retourne le train de bits de la ligne qui donne les positions des 
centrifugeuses dans cet état. SPEC : Le second paramètre doit être une des 
quatre constantes d’état sinon le résultat obtenu n’a pas de sens.*/
uint get_en_etat(const t_ligne_centrifugeuse * ptr_lig, int etat) {
	switch (etat) {
		case EN_ARRET:
			return ptr_lig->config_arret;
			break;
		case EN_ATTENTE:
			return ptr_lig->config_attente;
			break;
		case EN_FONCTION:
			return ptr_lig->config_fonction;
			break;
		/* Le second paramètre doit être une des quatre constantes d’état sinon
		le résultat obtenu n’a pas de sens: Donc, par defaut, retourne le train
		de la ligne de bris si l'etat en parametre n'est pas valide donc la
		fonction retourne toujours une ligne de position meme si le deuxime
		parametre n'est pas valide.*/
		default:
			return ptr_lig->config_bris;
		}
}
/*retourne une copie de la centrifugeuse à cette position dans le tableau. Elle
retourne une centrifugeuse dont tous les membres sont 0 si la position est 
non-valide.*/
t_centrifugeuse get_centrifugeuse(const t_ligne_centrifugeuse * ptr_lig, uint  pos) {
	if (pos < NB_BITS) {
		t_centrifugeuse copie_cnt = ptr_lig->tab_cnt[pos];
		return copie_cnt;
	}
	return centrifugeuse_membres_0();
}
/*cette fonction privée du module permute  les centrifugeuses aux positions 
pos1 et pos2 du tableau et dans les trains de bits correspondants si leurs états
diffèrent.*/
static void permuter_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, uint pos1,
	uint pos2) {

	if (pos1 < NB_BITS && pos2 < NB_BITS && ptr_lig->tab_cnt[pos1].etat !=
		ptr_lig->tab_cnt[pos2].etat) {
		//Pour la permutation des configs (positions)
		int etat_pos1 = ptr_lig->tab_cnt[pos1].etat;
		//les 2 etats sont differents
		int etat_pos2 = ptr_lig->tab_cnt[pos2].etat;
		
		//***************A TERMINER*****************
		/*
		Effectuer la permutation des configurations ici
		ptr_lig->config_arret
		ptr_lig->config_attente
		ptr_lig->config_fonction
		ptr_lig->config_bris
		*/
		//******************************************
	
		//permutation des centrifugeuses
		//cnt temporaire pour permettre la permutation
		t_centrifugeuse temp_cnt = ptr_lig->tab_cnt[pos1];
		ptr_lig->tab_cnt[pos1] = ptr_lig->tab_cnt[pos2];
		ptr_lig->tab_cnt[pos2] = temp_cnt;
	}
}

/*fonction d’affichage des lignes de centrifugeuses*/
void print_ligne_centrifugeuse(const t_ligne_centrifugeuse * ptr_lig) {
	printf("\n\n config_fonction == %s ", bits2string(ptr_lig->config_fonction));
	printf("\n\n config_attente  == %s ", bits2string(ptr_lig->config_attente));
	printf("\n\n config_arret    == %s ", bits2string(ptr_lig->config_arret));
	printf("\n\n config_bris     == %s ", bits2string(ptr_lig->config_bris));
}
static t_centrifugeuse centrifugeuse_membres_0() {
	t_centrifugeuse cnt_membres_0;
	cnt_membres_0 = init_centrifugeuse();
	cnt_membres_0.etat = 0;
	cnt_membres_0.prob_bris = 0;
	cnt_membres_0.compte_rebours = 0;

	return cnt_membres_0;
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


