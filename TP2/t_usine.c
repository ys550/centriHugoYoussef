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
		//les centrifugeuses en fonction dans la derniere ligne de l'usine
		int cnt_fnc_restant;

		ptr_usine->nb_ini_fonction = nb_fonction;
		ptr_usine->taille_tab_ligne = (nb_fonction / NB_FONC_LIG) + 1;
		cnt_fnc_restant = nb_fonction - NB_FONC_LIG * (ptr_usine->taille_tab_ligne - 1);

		ptr_usine->tab_ligne_centrifugeuse = (t_ligne_centrifugeuse *)
			malloc(ptr_usine->taille_tab_ligne, sizeof(t_ligne_centrifugeuse));

		ptr_usine->tab_poubelle_ligne = (t_ligne_centrifugeuse *)
			malloc(TAILLE_POUBELLE_INIT, sizeof(t_ligne_centrifugeuse));

		ptr_usine->nb_actuel_en_fonction = ptr_usine->nb_ini_fonction;
		ptr_usine->nb_actuel_en_bris = 0;
		ptr_usine->nb_toc = 0;
		ptr_usine->nb_bris_usine = 0;

		for (i = 0; i < ptr_usine->taille_tab_ligne - 1; i++) {
			init_ligne_centrifugeuse(&ptr_usine->tab_ligne_centrifugeuse[i], 
				NB_FONC_LIG);
		}

		init_ligne_centrifugeuse(&ptr_usine->tab_ligne_centrifugeuse[i + 1],
			cnt_fnc_restant);

		return 1;
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