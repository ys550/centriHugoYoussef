/*

Module :t_usine.c
Par    : Youssef Soliman, Hugo Belin
Date   :07/04/18

Ce ficher permet de voir précisement comment les fonctions définie dans
t_usine.h ont été programmé.
Pour comprendre l'utilité de ces fonctions, veuillez vous référer
au ficher t_usine.h

*/

//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS

#include "centrifugeuse.h"
#include "ligne_centrifugeuse.h"
#include "t_usine.h"

// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>



/*********************************************************/
/*                DEFINITIONS DES FONCTIONS              */
/*********************************************************/

int init_usine(t_usine * ptr_usine, uint nb_fonction) {
	if (NB_FONC_LIG <= NB_FONC_MAX) {

		//iterateur
		int i;
		/*les centrifugeuses en fonction dans la derniere ligne de l'usine*/
		int cnt_fnc_restant;

		int init_1_est_reussi;
		int init_2_est_reussi = 1;

		ptr_usine->nb_ini_fonction = nb_fonction;
		ptr_usine->nb_actuel_en_fonction = ptr_usine->nb_ini_fonction;
		ptr_usine->nb_actuel_en_bris = 0;
		ptr_usine->nb_toc = 0;
		ptr_usine->nb_bris_usine = 0;
		ptr_usine->nb_cent_remplace = 0;

		//cree une ligne supplementaire lorsque la derniere ligne est pleine
		ptr_usine->taille_tab_ligne = (nb_fonction / NB_FONC_LIG) + LIGNE_FIN;

		cnt_fnc_restant = nb_fonction % NB_FONC_LIG;
		if (cnt_fnc_restant == nb_fonction)
			cnt_fnc_restant = 0;

		ptr_usine->tab_ligne_centrifugeuse = (t_ligne_centrifugeuse *)
			malloc(ptr_usine->taille_tab_ligne * sizeof(t_ligne_centrifugeuse));

		ptr_usine->taille_tab_poubelle = TAILLE_POUBELLE_INIT;

		ptr_usine->tab_poubelle_ligne = (t_centrifugeuse *)
			malloc(ptr_usine->taille_tab_poubelle * sizeof(t_centrifugeuse));

		for (i = 0; i < ptr_usine->taille_tab_ligne; i++) {
			init_1_est_reussi = 
				init_ligne_centrifugeuse(&ptr_usine->tab_ligne_centrifugeuse[i], 
					NB_FONC_LIG);
		}
		//S'il y a des restant. Les mettre dans la derniere ligne
		if (cnt_fnc_restant > 0) {
			init_2_est_reussi =
				init_ligne_centrifugeuse(&ptr_usine->tab_ligne_centrifugeuse[i - 1],
					cnt_fnc_restant);
		}
			
		if (init_1_est_reussi && init_2_est_reussi) {
			return 1;
		}
		else
			return 0;	
	}
	return 0;
}

int  toc_usine(t_usine * ptr_usine, int temps) {

	//Iterateurs
	int i, j;

	int ajouter_fonction_est_reussi;
	int ajouter_attente_est_reussi;

	//un tableau contenant les etats precedant de chaque cent de chaque ligne
	int ** tab_etat_precedant;
	//un tableau des etats courants des centri sur chaque lignes
	int ** tab_etat_suivant;

	
	//Assignation de memoire au tableau dynamique 2D des etats precedant
	tab_etat_precedant = (int *)malloc(ptr_usine->taille_tab_ligne * sizeof(int));
	for (i = 0; i < ptr_usine->taille_tab_ligne; i++) {
		tab_etat_precedant[i] = (int *)malloc(NB_BITS * sizeof(int));
	}

	//Assignation de memoire au tableau dynamique 2D des etats suivants
	tab_etat_suivant = (int *)malloc(ptr_usine->taille_tab_ligne * sizeof(int));
	for (i = 0; i < ptr_usine->taille_tab_ligne; i++) {
		tab_etat_suivant[i] = (int *)malloc(NB_BITS * sizeof(int));
	}
	
	//Enregistre les etats de tout les machines de chaque ligne
	for (i = 0; i < ptr_usine->taille_tab_ligne; i++) {
		for (j = 0; j < NB_BITS; j++) {
			tab_etat_precedant[i][j] = 
				ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j].etat;
		}
	}

	for (i = 0; i < ptr_usine->taille_tab_ligne; i++) {
		//c’est ici qu’une centrifugeuse EN_FONCTION peut briser
		toc_ligne(&ptr_usine->tab_ligne_centrifugeuse[i], temps);
		for (j = 0; j < NB_BITS; j++) {
			
			tab_etat_suivant[i][j] =
				ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j].etat;

			/*Si la fonction "toc_centrifugeuse()" a retourné l'état "EN_BRIS" sur une 
			des lignes*/
			if (tab_etat_suivant[i][j] == EN_BRIS &&
				tab_etat_precedant[i][j] != tab_etat_suivant[i][j]) {
	 
				ptr_usine->nb_actuel_en_bris++;
				ptr_usine->nb_bris_usine++;

				//Si l'état précédent de la machine était "EN_FONCTION"
				if (tab_etat_precedant[i][j] == EN_FONCTION) {
					ptr_usine->nb_actuel_en_fonction--;

					//ajouter une nouvelle machine "EN_FONCTION" à partir d'une machine "EN_ATTENTE"
					ajouter_fonction_est_reussi =
						ajouter_cnt(&ptr_usine->tab_ligne_centrifugeuse[i]);

					//ajouter une nouvelle machine "EN_ATTENTE" à partir d'une machine "EN_ARRET" 
					ajouter_attente_est_reussi =
						ajouter_cnt_attente(&ptr_usine->tab_ligne_centrifugeuse[i]);

					if (ajouter_fonction_est_reussi) {
						ptr_usine->nb_actuel_en_fonction++;
					}
				}
				//Si  l'état précédent de la machine était "EN_ATTENTE"
				else if (tab_etat_precedant[i][j] == EN_ATTENTE) {
					//ajouter une nouvelle machine "EN_ATTENTE" à partir d'une machine "EN_ARRET"
					ajouter_attente_est_reussi =
						ajouter_cnt_attente(&ptr_usine->tab_ligne_centrifugeuse[i]);
				}
				
			}
			//On reactive la machine apres qu'elle est rapare
			if (tab_etat_suivant[i][j] == EN_ARRET &&
				tab_etat_precedant[i][j] == EN_BRIS) {
				set_en_attente(&ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j]);
				set_en_fonction(&ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j]);
				ptr_usine->nb_actuel_en_fonction++;
				ptr_usine->nb_actuel_en_bris--;
			}
		}
	}

	ptr_usine->nb_toc++;

	return ptr_usine->nb_actuel_en_fonction;
}


int entretien_usine(t_usine * ptr_usine) {
	int i, j;
	static int index_poubelle = 0;
	//pour le realloc
	t_centrifugeuse * tab_poubelle_etire;

	/*remplacer ou reparer a chaque nb de tocs defini par TOCS_REMP*/
	if (ptr_usine->nb_toc % TOCS_REMP == 0) {

		for (i = 0; i < ptr_usine->taille_tab_ligne; i++) {
			for (j = 0; j < NB_BITS; j++) {

				/*REPARER si elle n'a pas brise plus que MAX_BRIS lorsque la 
				machine est EN_BRIS*/
				if ((ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j].etat == EN_BRIS) && 
					(ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j].nb_bris < MAX_BRIS)) {

					set_temps_reparation(
						&ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j],
						TEMPS_REPARATION);

					if (ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j].compte_rebours == 
						COMPTE_REBOURS_REPARE) {

						ptr_usine->nb_actuel_en_bris--;

					}

				}
				/*REMPLACER si elle a tombe en bris plus que MAX_BRIS lorsque la 
				machine est EN_BRIS*/
				else if ((ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j].etat == EN_BRIS) &&
					(ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j].nb_bris >= MAX_BRIS)) {

					ptr_usine->tab_poubelle_ligne[index_poubelle++] =
						remplacer_cnt(&ptr_usine->tab_ligne_centrifugeuse[i], j);

					ptr_usine->nb_cent_remplace++;
					ptr_usine->nb_actuel_en_bris--;

					/*Si on est rendu a la fin du tableau de poubelle, on 
					accroit sa taille. L'accroissement est defini par la 
					constante ACCROISSEMENT_TAB_POUBELLE*/
					if (index_poubelle == ptr_usine->taille_tab_poubelle) {

						ptr_usine->taille_tab_poubelle += ACCROISSEMENT_TAB_POUBELLE;

						tab_poubelle_etire = (t_centrifugeuse *)
							realloc(ptr_usine->tab_poubelle_ligne,
								ptr_usine->taille_tab_poubelle *
								sizeof(t_centrifugeuse));

						if (tab_poubelle_etire != NULL) {
							ptr_usine->tab_poubelle_ligne = tab_poubelle_etire;
						}
					}
				}
			}
		}
	}
	
	return ptr_usine->nb_cent_remplace;
}

void print_usine(const t_usine * ptr_usine) {
	int i, j;
	int etat;
	int nb_fonction_ligne;
	int nb_attente_ligne;
	int nb_arret_ligne;
	int nb_bris_ligne;

	for (i = 0; i < ptr_usine->taille_tab_ligne; i++) {
		printf("\nLigne: %d\nEN_BRIS=0, EN_ARRET=1, EN_ATTENTE=2, " 
			"EN_FONCTION=3\n", i);
		for (j = NB_BITS - 1; j >= 0; j--) {
			etat = ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j].etat;
			printf(" %d ", etat);
		}
		nb_fonction_ligne = 
			ptr_usine->tab_ligne_centrifugeuse[i].tab_nb_cnt[EN_FONCTION];
		nb_attente_ligne = 
			ptr_usine->tab_ligne_centrifugeuse[i].tab_nb_cnt[EN_ATTENTE];
		nb_arret_ligne = 
			ptr_usine->tab_ligne_centrifugeuse[i].tab_nb_cnt[EN_ARRET];
		nb_bris_ligne = 
			ptr_usine->tab_ligne_centrifugeuse[i].tab_nb_cnt[EN_BRIS];

		printf("\nEN_BRIS: %d EN_ARRET: %d EN_ATTENTE: %d EN_FONCTION: %d\n",
			nb_bris_ligne, nb_arret_ligne, nb_attente_ligne,
			nb_fonction_ligne);

		printf("\n************************************************\n");
	}
	
	printf("nb_cent_remplace: %d\n", ptr_usine->nb_cent_remplace);
	printf("nb_ini_fonction: %d\n", ptr_usine->nb_ini_fonction);
	printf("nb_actuel_en_fonction: %d\n", ptr_usine->nb_actuel_en_fonction);
	printf("nb_actuel_en_bris: %d\n", ptr_usine->nb_actuel_en_bris);
	printf("nb_toc: %d\n", ptr_usine->nb_toc);
	printf("nb_bris_usine: %d\n\n", ptr_usine->nb_bris_usine);
	printf("************************************************\n");
	printf("************************************************\n");
}

int get_nb_actuel_en_fonction(t_usine * ptr_usine) {
	return ptr_usine->nb_actuel_en_fonction;
}

int get_nb_actuel_en_bris(t_usine * ptr_usine) {
	return ptr_usine->nb_actuel_en_bris;
}

int get_nb_toc(t_usine * ptr_usine) {
	return ptr_usine->nb_toc;
}

int get_nb_bris_total(t_usine * ptr_usine) {
	return ptr_usine->nb_bris_usine;
}