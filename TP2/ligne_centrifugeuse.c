/*===========================================================*/
/* 	INF145 - ligne_centrifugeuse                             */
/*===========================================================*/

/*

Module :ligne_centrifugeuse
Par    :
Date   :21/05/18

-Ce module offre Le second module va implémenter le type structuré 
t_ligne_centrifugeuse dans son interface (*.H) et va offrir des 
fonctions visant à maintenir un nombre variable dans le temps de
centrifugeuses EN_FONCTION dans une ligne de centrifugeuses 
(comme pour le TP1).

- Ce ficher permet de voir précisement comment les fonctions définie dans
ligne_centrifugeuse.h ont été programmé.
Pour comprendre l'utilité de ces fonctions, veuillez vous référer 
au ficher centrifugeuse.h 
*/



/*=========================================================*/
//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

#include "centrifugeuse.h"
#include "ligne_centrifugeuse.h"
#include "op_bits.h"
// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>


/*********************************************************
*********************FONCTIONS****************************
*********************************************************/


int init_ligne_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, uint nb) {

	ptr_lig->config_fonction = 0;
	ptr_lig->config_bris = 0;
	ptr_lig->config_attente = 0;
	ptr_lig->config_arret = 0;
	ptr_lig->tab_nb_cnt[EN_BRIS] = 0;
	ptr_lig->tab_nb_cnt[EN_ATTENTE] = 0;
	ptr_lig->tab_nb_cnt[EN_FONCTION] = 0;
	ptr_lig->tab_nb_cnt[EN_ARRET] = 0;


	if (nb <= NB_BITS) {
		//initialiser tout
		for (int i = 0; i < NB_BITS; i++) {
			ptr_lig->tab_cnt[i] = init_centrifugeuse();
			//init_centrifugeuse() mets les cnt en etat ARRET
			ptr_lig->config_arret = SET_BIT(ptr_lig->config_arret, i);
			ptr_lig->tab_nb_cnt[EN_ARRET]++;

		}

		int i = 2;
		//regle des 2/3
		uint cnt_fonct_restant = ceil(2.0 / 3.0 * nb);;

		for (int j = 0; cnt_fonct_restant > 0; j++) {
			if (j == i) {  //pour les positions
				j++;	//position pour les 1
				i += 3;	//position pour les 0
			}
			
			//set en fonction en respectant la regle <= 2 en contigus
			set_en_attente(&ptr_lig->tab_cnt[j]);
			set_en_fonction(&ptr_lig->tab_cnt[j]);
			ptr_lig->tab_nb_cnt[EN_ARRET]--;
			ptr_lig->tab_nb_cnt[EN_FONCTION]++;
			ptr_lig->config_fonction = SET_BIT(ptr_lig->config_fonction, j);
			ptr_lig->config_arret = CLEAR_BIT(ptr_lig->config_arret, j);
			--cnt_fonct_restant;
			
			/*On mets ceux qui restent en attente. Le nombre de centri en 
			attente depend de la constante NBR_K_EN_ATTENTE*/
			if (cnt_fonct_restant == 0) {
				/*calcule combien de bits libre dans la ligne il reste pour 
				mettre en attente*/
				//int nbr_k_possible = ((NB_BITS - 1) - j);
				int nbr_k_possible = ((NB_BITS - 1) - j);

				//Valeur max de nbr_k_possible = NBR_K_EN_ATTENTE
				if (nbr_k_possible > NBR_K_EN_ATTENTE) {
					nbr_k_possible = NBR_K_EN_ATTENTE;
				}

				if (nbr_k_possible != 0) {
					for (int i = j + 1; i <= (j + nbr_k_possible); i++) {
						/*on met les derniers libres les plus a droite en attente*/
						set_en_attente(&ptr_lig->tab_cnt[i]);
						if (nb > NB_BITS - 2) {
							ptr_lig->config_attente = SET_BIT(ptr_lig->config_attente, i);
							ptr_lig->config_arret = CLEAR_BIT(ptr_lig->config_arret, i);
						}
						/*else if (nb == 0) {
							ptr_lig->config_attente = SET_BIT(ptr_lig->config_attente, i - 1);
							ptr_lig->config_arret = CLEAR_BIT(ptr_lig->config_arret, i - 1);
						}*/
						else {
							ptr_lig->config_attente = SET_BIT(ptr_lig->config_attente, i + 1);
							ptr_lig->config_arret = CLEAR_BIT(ptr_lig->config_arret, i + 1);
						}
						
						ptr_lig->tab_nb_cnt[EN_ATTENTE]++;
						ptr_lig->tab_nb_cnt[EN_ARRET]--;
					}
				}	
			}	
		}
		return 1;
	}
	return 0;
}


int ajouter_cnt(t_ligne_centrifugeuse * ptr_lig) {
	/*il est seulement possible d'ajouter une centrifugueuse EN_FONCTION si le
	resultat ne donne pas plus que 2 EN_FONCTION en contigus et si la 
	centrifuguese dans la position trouve est en attente ou en arret*/

	//pour verifier si configuration valide(pas plus de 2 EN_FONCTION contigus)
	uint copie_config_fonction = ptr_lig->config_fonction;

	for (int i = 0; i < NB_BITS; i++) {

		if (GET_BIT(ptr_lig->config_attente, i) == 1 || 
			GET_BIT(ptr_lig->config_arret, i) == 1) {

			copie_config_fonction = SET_BIT(ptr_lig->config_fonction, i);
			
			/*verifie si la config serait valide si on ajoute une 
			centrifuguese en fonction dans la position (i) courante de 
			l'iteration de la boucle avant de l'ajouter*/
			if (configuration_valide(copie_config_fonction)) {

				if (GET_BIT(ptr_lig->config_attente, i) == 1) {
					ptr_lig->config_attente = CLEAR_BIT(ptr_lig->config_attente, i);
					ptr_lig->tab_nb_cnt[EN_ATTENTE]--;
				}
				else if (GET_BIT(ptr_lig->config_arret, i) == 1) {
					ptr_lig->config_arret = CLEAR_BIT(ptr_lig->config_arret, i);
					ptr_lig->tab_nb_cnt[EN_ARRET]--;
				}
				set_en_attente(&ptr_lig->tab_cnt[i]);
				set_en_fonction(&ptr_lig->tab_cnt[i]);
				ptr_lig->tab_nb_cnt[EN_FONCTION]++;
				ptr_lig->config_fonction = SET_BIT(ptr_lig->config_fonction, i);

				return 1;
			}	
		}
	}
	return 0;
}


int reduire_cnt(t_ligne_centrifugeuse * ptr_lig) {
	//Reduit celle la plus a gauche (a la fin)
	for (int i = NB_BITS - 1; i >= 0; i--) {
		if (GET_BIT(ptr_lig->config_fonction, i) == 1) {
			/*reduit de 1 une cnt EN_FONCTION en changeant sont etat a 
			EN_ATTENTE*/
			set_en_attente(&ptr_lig->tab_cnt[i]);
			ptr_lig->tab_nb_cnt[EN_ATTENTE]++;
			ptr_lig->tab_nb_cnt[EN_FONCTION]--;
			ptr_lig->config_fonction = CLEAR_BIT(ptr_lig->config_fonction, i);
			ptr_lig->config_attente = SET_BIT(ptr_lig->config_attente, i);
			return 1;
		}
	}
	return 0;
}


void toc_ligne(t_ligne_centrifugeuse * ptr_lig, int temps) {
	int etat_precedant;
	int etat;
	
	for (int i = 0; i < NB_BITS; i++) {
		etat_precedant = ptr_lig->tab_cnt[i].etat;
		etat = toc_centrifugeuse(&ptr_lig->tab_cnt[i]);
		
		if (etat == EN_BRIS) {
			if (GET_BIT(ptr_lig->config_fonction, i)) {
				etat_precedant = EN_FONCTION;
				ptr_lig->tab_nb_cnt[EN_FONCTION]--;
				ptr_lig->config_fonction = CLEAR_BIT(ptr_lig->config_fonction, i);
			}
			else if (GET_BIT(ptr_lig->config_attente, i)) {
				etat_precedant = EN_ATTENTE;
				ptr_lig->tab_nb_cnt[EN_ATTENTE]--;
				ptr_lig->config_attente = CLEAR_BIT(ptr_lig->config_attente, i);
			}
			else if (GET_BIT(ptr_lig->config_arret, i)) {
				etat_precedant = EN_ARRET;
				ptr_lig->tab_nb_cnt[EN_ARRET]--;
				ptr_lig->config_arret = CLEAR_BIT(ptr_lig->config_arret, i);
			}
			else {
				etat_precedant = EN_BRIS;
			}
			ptr_lig->config_bris = SET_BIT(ptr_lig->config_bris, i);
			remplacer_cnt(ptr_lig, i);
			ptr_lig->nb_bris_ligne++;
			ptr_lig->tab_nb_cnt[EN_BRIS]++;
		}

		if (etat != EN_BRIS && etat_precedant == EN_BRIS) {
			printf("Machine [%d] REPAREE a temps = %d\n", i, temps);
			print_ligne_centrifugeuse(ptr_lig);
		}
		else if (etat == EN_BRIS && etat_precedant != EN_BRIS) {
			printf("Machine [%d] EN_BRIS a temps = %d\n", i, temps);
			print_ligne_centrifugeuse(ptr_lig);
		}

	}
}


t_centrifugeuse remplacer_cnt(t_ligne_centrifugeuse * ptr_lig, uint pos) {
	if (pos < NB_BITS && ptr_lig->tab_cnt[pos].etat != EN_FONCTION && 
		ptr_lig->tab_cnt[pos].etat != EN_ATTENTE) {
		
		t_centrifugeuse copie_cnt_elimine = ptr_lig->tab_cnt[pos];

		if (copie_cnt_elimine.etat == EN_BRIS) {
			ptr_lig->tab_nb_cnt[EN_BRIS]--;
			//changer config bris au cas que celle remplacer ete brise
			ptr_lig->config_bris = CLEAR_BIT(ptr_lig->config_bris, pos);
		}
		else if (copie_cnt_elimine.etat == EN_ARRET) {
			ptr_lig->tab_nb_cnt[EN_ARRET]--;
			//changer config bris au cas que celle remplacer ete en arret
			ptr_lig->config_arret = CLEAR_BIT(ptr_lig->config_arret, pos);
		}

		//insere la nouvelle centri init_centri-> etat = en arret
		ptr_lig->tab_cnt[pos] = init_centrifugeuse();
		//la nouvelle centri est en etat arret
		ptr_lig->config_arret = SET_BIT(ptr_lig->config_arret, pos);
		ptr_lig->tab_nb_cnt[EN_ARRET]++;

		return copie_cnt_elimine;
	}
	return centrifugeuse_membres_0();
}


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


t_centrifugeuse get_centrifugeuse(const t_ligne_centrifugeuse * ptr_lig, uint  pos) {
	if (pos < NB_BITS) {
		t_centrifugeuse copie_cnt = ptr_lig->tab_cnt[pos];
		return copie_cnt;
	}
	return centrifugeuse_membres_0();
}


void permuter_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, uint pos1,
	uint pos2) {

	if (pos1 < NB_BITS && pos2 < NB_BITS && ptr_lig->tab_cnt[pos1].etat !=
		ptr_lig->tab_cnt[pos2].etat) {

		//Pour la permutation des configs (positions)
		int etat_pos1;
		int etat_pos2;
		uint config_1_temp;
		uint config_2_temp;

		//permutation des configs
		for (int etat = EN_BRIS; etat <= EN_FONCTION; etat++) {
			if (GET_BIT(get_en_etat(ptr_lig, etat), pos1) == 1) {
				config_1_temp = get_en_etat(ptr_lig, etat);
				etat_pos1 = etat;
				config_1_temp = CLEAR_BIT(config_1_temp, pos1);
				config_1_temp = SET_BIT(config_1_temp, pos2);
			}
			if (GET_BIT(get_en_etat(ptr_lig, etat), pos2) == 1) {
				config_2_temp = get_en_etat(ptr_lig, etat);
				etat_pos2 = etat;
				config_2_temp = CLEAR_BIT(config_2_temp, pos2);
				config_2_temp = SET_BIT(config_2_temp, pos1);
			}
		}

		/*Verifie si les configs temp sont valides: Il sont seulement invalide
		si c'est une config EN_FONCTION avec plus que 2 EN_FONTION contigus sur
		la ligne*/
		if (etat_pos1 == EN_FONCTION &&
			configuration_valide(config_1_temp) != 1) {
			return;
		}
		else if (etat_pos2 == EN_FONCTION &&
			configuration_valide(config_2_temp) != 1) {
			return;
		}
		//copie les config temp aux vrais configs
		set_config(ptr_lig, etat_pos1, config_1_temp);
		set_config(ptr_lig, etat_pos2, config_2_temp);

		//permutation des centrifugeuses
		//cnt temporaire pour permettre la permutation
		t_centrifugeuse temp_cnt = ptr_lig->tab_cnt[pos1];
		ptr_lig->tab_cnt[pos1] = ptr_lig->tab_cnt[pos2];
		ptr_lig->tab_cnt[pos2] = temp_cnt;
	}
}


void print_ligne_centrifugeuse(const t_ligne_centrifugeuse * ptr_lig) {
	printf("FONCTION: %s = %u\n", bits2string(ptr_lig->config_fonction),
		ptr_lig->tab_nb_cnt[EN_FONCTION]);
	printf("ATTENTE:  %s = %u\n", bits2string(ptr_lig->config_attente),
		ptr_lig->tab_nb_cnt[EN_ATTENTE]);
	printf("ARRET:    %s = %u\n", bits2string(ptr_lig->config_arret),
		ptr_lig->tab_nb_cnt[EN_ARRET]);
	printf("BRIS:     %s = %u\n\n", bits2string(ptr_lig->config_bris),
		ptr_lig->tab_nb_cnt[EN_BRIS]);
}
static t_centrifugeuse centrifugeuse_membres_0() {
	t_centrifugeuse cnt_membres_0;
	cnt_membres_0 = init_centrifugeuse();
	cnt_membres_0.etat = 0;
	cnt_membres_0.prob_bris = 0;
	cnt_membres_0.compte_rebours = 0;

	return cnt_membres_0;
}
/*Permet d'atribuer la valeur unsigned int en parametre a la configuration choisi
avec l'etat en deuxieme parametre de la ligne en premier parametre*/
static void set_config(t_ligne_centrifugeuse * ptr_lig, int etat, uint config) {
	switch (etat) {
	case EN_BRIS:
		ptr_lig->config_bris = config;
		break;

	case EN_ARRET:
		ptr_lig->config_arret = config;
		break;

	case EN_ATTENTE:
		ptr_lig->config_attente = config;
		break;

	case EN_FONCTION:
		ptr_lig->config_fonction = config;
		break;
	}
}

/*fonction configuration_valide du TP1*/
/****************CODE EMPRUNTE**********************
*****************SOURCE: TP1************************
*************PAR: Youssef Soliman*******************
****************************************************/
static unsigned short configuration_valide(uint valeur) {
	int nb_actif_contigus = 0;

	for (int i = 0; i <= NB_BITS - 1; i++) {
		if (GET_BIT(valeur, i)) {
			nb_actif_contigus++;
		}
		else {
			nb_actif_contigus = 0;
		}

		if (nb_actif_contigus > 2) {
			return 0;
		}
	}

	if (nb_actif_contigus <= 2) {
		return 1;
	}
		
	return 0;
}

int  get_nb_bris_lig(const t_ligne_centrifugeuse * ptr_lig) {
	return ptr_lig->nb_bris_ligne;
}


