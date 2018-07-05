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
		/*les centrifugeuses en fonction dans la derniere avant la ligne 
		supplementaire de l'usine*/
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
	//l'etat courant d'une centri sur une ligne
	int etat_suivant;
	//un tableau contenant les etats precedant de chaque cent de chaque ligne
	int ** tab_etat_precedant;

	//Assignation de memoire au tableau dynamique 2D des etats precedant
	tab_etat_precedant = (int *)malloc(ptr_usine->taille_tab_ligne * sizeof(int));
	for (i = 0; i < ptr_usine->taille_tab_ligne; i++) {
		tab_etat_precedant[i] = (int *)malloc(NB_BITS * sizeof(int));
	}

	/*Initialisation du tableau d'etat precedant avec les etats precedant de 
	chaque ligne de l'usine*/
	for (i = 0; i < ptr_usine->taille_tab_ligne; i++) {
		for (j = 0; j < NB_BITS; j++) {
			tab_etat_precedant[i][j] = 
				ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j].etat;
		}
	}
	
	for (i = 0; i < ptr_usine->taille_tab_ligne; i++) {

		toc_ligne(&ptr_usine->tab_ligne_centrifugeuse[i], temps);

		for (j = 0; j < NB_BITS; j++) {
			etat_suivant = ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j].etat;
			if (etat_suivant == EN_BRIS) {
				ptr_usine->nb_actuel_en_fonction--;
				ptr_usine->nb_actuel_en_bris++;
				ptr_usine->nb_bris_usine++;

				//Si l'etat precedant de la cent en bris etait en fonction
				if (tab_etat_precedant[i][j] == EN_FONCTION) {
					//ajoute une cnt en fonction a partir d'une EN_ATTENTE
					ajouter_cnt(&ptr_usine->tab_ligne_centrifugeuse[i]);
					ptr_usine->nb_actuel_en_fonction++;
				}
				//Si l'etat precedant de la cent en bris etait en attente
				else if (tab_etat_precedant[i][j] == EN_ATTENTE) {
					//ajoute une cnt en attente a partir d'une EN_ARRET
					ajouter_cnt_attente(&ptr_usine->tab_ligne_centrifugeuse[i]);
				}
			}
		}	
	}
	ptr_usine->nb_toc++;

	return ptr_usine->nb_actuel_en_fonction;
}

/*
va observer chaque  centrifugeuse de l’usine et selon les critères de 
remplacement de la stratégie utilisée (avec fonction privée static)  va choisir
de la remplacer ou non par une centrifugeuse neuve.  S’il y a remplacement, la
vieille centrifugeuse (retournée par la fonction de remplacement) est conservée
dans un tableau de centrifugeuses mises au rebus. La fonction retourne le nombre
de centrifugeuses qui viennent d’être remplacées.
*/
int entretien_usine(t_usine * ptr_usine) {
	int i, j;
	static int index_poubelle = 0;
	//pour le realloc()
	t_centrifugeuse * tab_poubelle_etire;

	for (i = 0; i < ptr_usine->taille_tab_ligne; i++) {
		for (j = 0; j < NB_BITS; j++) {
			if (ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j].etat == EN_BRIS &&
				ptr_usine->tab_ligne_centrifugeuse[i].tab_cnt[j].nb_bris <= MAX_BRIS) {

				ptr_usine->tab_poubelle_ligne[index_poubelle++] =
					remplacer_cnt(&ptr_usine->tab_ligne_centrifugeuse[i], j);

				if (index_poubelle >= ptr_usine->taille_tab_poubelle - 1) {

					ptr_usine->taille_tab_poubelle += ACCROISSEMENT_TAB_POUBELLE;

					/*creer un autre tab poubelle au cas que realloc() ne peut 
					pas etirer le tab courant?*/
					ptr_usine->tab_poubelle_ligne = (t_centrifugeuse *)
						realloc(ptr_usine->tab_poubelle_ligne, 
							ptr_usine->taille_tab_poubelle);
				}
				ptr_usine->nb_cent_remplace++;
			}
		}
		
	}
	return ptr_usine->nb_cent_remplace;
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

//TO-DO: ajouter print_usine