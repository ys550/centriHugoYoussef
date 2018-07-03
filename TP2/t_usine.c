/*

Module :t_usine.c
Par    :
Date   :21/05/18

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

		//cree une ligne supplementaire lorsque la derniere ligne est complete
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

int  toc_usine(t_usine * ptr_usine) {
	
}

int entretien_usine(t_usine * ptr_usine){}

int get_nb_total_en_fonction(t_usine * ptr_usine){}

int get_nb_actuel_en_bris(t_usine * ptr_usine){}

int get_nb_toc(t_usine * ptr_usine){}

int get_nb_bris_total(t_usine * ptr_usine){}

//TO-DO: ajouter print_usine