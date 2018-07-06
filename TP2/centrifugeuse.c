/*

Module : centrifugeuse.c
Par    : Youssef Soliman, Hugo Belin
Date   :20/06/18

Ce ficher permet de voir précisement comment les fonctions définie dans
centrifugeuse.h ont été programmé.
Pour comprendre l'utilité de ces fonctions, veuillez vous référer
au ficher centrifugeuse.h


*/

//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 


#include "centrifugeuse.h"

// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


/*********************************************************/
/*                DEFINITIONS DES FONCTIONS              */
/*********************************************************/

t_centrifugeuse init_centrifugeuse(void) {
	t_centrifugeuse nouvel_centri;
	//iterateur
	int i;
	
	/* Initialisation des données issu de la structure de
	la nouvelle centrifugeuse */
	nouvel_centri.etat = EN_ARRET;
	nouvel_centri.prob_bris = PROB_BRIS_INIT;
	nouvel_centri.compte_rebours = 0;
	nouvel_centri.nb_tocs_en_attente = 0;
	nouvel_centri.nb_tocs_en_fonction = 0;
	nouvel_centri.nb_bris = 0;

	/* Pour chaque etat possible le nombre de toc est remis à 0*/
	for (i = EN_BRIS; i <= EN_FONCTION; i++)
		nouvel_centri.tab_tocs[i] = 0;

	/* Retourne la centrifugeuse initialisée */
	return nouvel_centri;
}

int set_en_fonction(t_centrifugeuse * ptr_cnt) {
	/* Si la centrifugeuse est en attente, alors elle est mise
	en fonction*/
	if (ptr_cnt->etat == EN_ATTENTE) {
		ptr_cnt->etat = EN_FONCTION;
		return 1;
	}	
	return 0;
}

int set_en_attente(t_centrifugeuse * ptr_cnt) {
	/* Une centrifugeuse peut être mise en attente seulement
	si elle est en fonction ou en arret*/
	if (ptr_cnt->etat == EN_ARRET || ptr_cnt->etat == EN_FONCTION) {
		ptr_cnt->etat = EN_ATTENTE;
		return 1;
	}
	return 0;
}

int set_en_arret(t_centrifugeuse * ptr_cnt) {
	/* Si la centrifugeuse est en attente ou en fonction alors
	elle se met en arret */
	if (ptr_cnt->etat == EN_ATTENTE || ptr_cnt->etat == EN_FONCTION) {
		ptr_cnt->etat = EN_ARRET;
		return 1;
	}
	return 0;
}

int  toc_centrifugeuse(t_centrifugeuse * ptr_cnt) {
	double test_bris;

	if (ptr_cnt->etat != EN_ARRET) {

		/* Si la centrifugeuse n'est pas en arret, elle subit un test
		de bris pour déterminer son risque de bris */
		test_bris = BASE_TEST_BRIS * rand() / RAND_MAX;

		if (ptr_cnt->etat == EN_BRIS && ptr_cnt->compte_rebours != INFINI) {

			/* Si la cnetrifugeuse est en bris mais qu'elle est en reparation
			alors son compte a rebour de reparation diminue */
			ptr_cnt->compte_rebours--;

			if (ptr_cnt->compte_rebours <= 0) {
				/*Si le temps de réparation est nul alors la centrifugeuse est 
				réparée et prend la configuration initiale*/
				ptr_cnt->etat = EN_ARRET;
				ptr_cnt->nb_tocs_en_fonction = 0;
				ptr_cnt->nb_tocs_en_attente = 0;
				ptr_cnt->prob_bris = PROB_BRIS_INIT;
			}
		}

		if (test_bris < ptr_cnt->prob_bris && ptr_cnt->etat != EN_BRIS) {
			/*Si le test de bris est plus faible que la probabilité de bris
			alors la centrifugeuse est en bris*/
			ptr_cnt->etat = EN_BRIS;
			ptr_cnt->compte_rebours = INFINI;
			ptr_cnt->nb_bris++;
		}
		else {
			accroitre_prob(ptr_cnt);
		}
	}
	//incrementation des compteurs selon l'etat
	if (ptr_cnt->etat == EN_BRIS) {
		ptr_cnt->tab_tocs[EN_BRIS]++;
	}
	else if (ptr_cnt->etat == EN_ATTENTE) {
		ptr_cnt->nb_tocs_en_attente++;
		ptr_cnt->tab_tocs[EN_ATTENTE]++;
	}
	else if (ptr_cnt->etat == EN_FONCTION) {
		ptr_cnt->nb_tocs_en_fonction++;
		ptr_cnt->tab_tocs[EN_FONCTION]++;
	}
	else if (ptr_cnt->etat == EN_ARRET) {
		ptr_cnt->tab_tocs[EN_ARRET]++;
	}
	
	return ptr_cnt->etat;
}

int set_temps_reparation(t_centrifugeuse * ptr_cnt, uint temps) {
	/* Si la centrifugeuse est en configuration de bris alors nous
	mettons le compteur à un nombre de toc voulu avant la réparation
	complete */
	if (ptr_cnt->etat == EN_BRIS && ptr_cnt->compte_rebours == INFINI) {
		ptr_cnt->compte_rebours = temps;
		return 1;
	}
	return 0;
}

void get_compteurs(const t_centrifugeuse * ptr_cnt, uint * compteurs) {
	compteurs[0] = ptr_cnt->tab_tocs[EN_BRIS];
	compteurs[1] = ptr_cnt->tab_tocs[EN_ARRET];
	compteurs[2] = ptr_cnt->tab_tocs[EN_ATTENTE];
	compteurs[3] = ptr_cnt->tab_tocs[EN_FONCTION];
	compteurs[4] = ptr_cnt->nb_bris;
	compteurs[5] = ptr_cnt->nb_tocs_en_attente;
	compteurs[6] = ptr_cnt->nb_tocs_en_fonction;
	compteurs[7] = ptr_cnt->compte_rebours;
}

double get_prob_bris(const t_centrifugeuse * ptr_cnt) {
	return ptr_cnt->prob_bris;
}

static void accroitre_prob(t_centrifugeuse * ptr_cnt) {
	
	double prob_bris = ptr_cnt->prob_bris;
	double prob_bris_fnc = PROB_BRIS_INIT;

	/*L’accroissement donné à une centrifugeuse  EN_ATTENTE doit être une
	fraction moindre de celle donnée à une EN_FONCTION(cette fraction doit
	être définie par une constante du module (FRACTION_PROB_BRIS)).*/
	double prob_bris_att = prob_bris_fnc * FRACTION_PROB_BRIS;
	double prob_bis_nb_bris = 0.001;

	if (ptr_cnt->prob_bris == 0) {
		ptr_cnt->prob_bris = PROB_BRIS_INIT;
	}

	/*
	L’accroissement de prob_bris calculé va dépendre de 3 des compteurs de
	la centrifugeuse :
	-nombre de bris déjà subis:
	1-ptr_cnt->nb_bris
	-des deux compteurs depuis la réparation:
	2-ptr_cnt->nb_tocs_en_attente
	3-ptr_cnt->nb_tocs_en_fonction
	*/
	prob_bris +=
		log(BASE_LOG + (double)ptr_cnt->nb_tocs_en_fonction *	prob_bris_fnc)
		+ log(BASE_LOG + (double)ptr_cnt->nb_tocs_en_attente * prob_bris_att)
		+ log(BASE_LOG + (double)ptr_cnt->nb_bris * prob_bis_nb_bris);
	
	ptr_cnt->prob_bris = prob_bris;
}

void print_centrifugeuse(const t_centrifugeuse * ptr_cnt) {
	char * etat;

	switch (ptr_cnt->etat) {
		case EN_ARRET:
			etat = "EN_ARRET";
			break;
		case EN_ATTENTE:
			etat = "EN_ATTENTE";
			break;
		case EN_FONCTION:
			etat = "EN_FONCTION";
			break;
		default:
			etat = "EN_BRIS";
	}

	printf("\nEtat: %s \nNb Bris: %u", etat, ptr_cnt->nb_bris);
	printf("\nProbabilite de Bris: %lf", ptr_cnt->prob_bris);
	printf("\nCompte a rebours: %u", ptr_cnt->compte_rebours);
	printf("\nNb tocs en fonction: %u", ptr_cnt->nb_tocs_en_fonction);
	printf("\nNb tocs en attente: %u", ptr_cnt->nb_tocs_en_attente);
	printf("\nCompte d'etat EN_BRIS: %u", ptr_cnt->tab_tocs[EN_BRIS]);
	printf("\nCompte d'etat EN_ARRET: %u", ptr_cnt->tab_tocs[EN_ARRET]);
	printf("\nCompte d'etat EN_ATTENTE: %u", ptr_cnt->tab_tocs[EN_ATTENTE]);
	printf("\nCompte d'etat EN_FONCTION: %u\n", ptr_cnt->tab_tocs[EN_FONCTION]);
}


