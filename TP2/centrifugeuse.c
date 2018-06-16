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
#define DEBUG

#include "centrifugeuse.h"

// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*retourne une centrifugeuse neuve à l’état EN_ARRET.  Sa probabilité initiale 
de bris est donnée par une constante du module.*/
t_centrifugeuse init_centrifugeuse(void) {
	t_centrifugeuse nouvel_centri;
	
	nouvel_centri.etat = EN_ARRET;
	nouvel_centri.prob_bris = PROB_BRIS_INIT;
	nouvel_centri.compte_rebours = 20;
	nouvel_centri.nb_tocs_en_attente = 0;
	nouvel_centri.nb_tocs_en_fonction = 0;
	nouvel_centri.nb_bris = 0;
	for (int i = 0; i < 4; i++)
		nouvel_centri.tab_tocs[i] = 0;

	return nouvel_centri;
}
/*permet de mettre une centrifugeuse EN_ATTENTE  dans l’état   EN_FONCTION.
Retour de 1 si réussi, 0 sinon (si elle n’est pas en état EN_ATTENTE).*/
int set_en_fonction(t_centrifugeuse * ptr_cnt) {
	if (ptr_cnt->etat == EN_ATTENTE) {
		ptr_cnt->etat = EN_FONCTION;
		return 1;
	}	
	return 0;
}
/*permet de mettre une centrifugeuse EN_ARRET ou EN_FONCTION dans l’état  
EN_ATTENTE.  Retour de 1 si réussi, 0 sinon.*/
int set_en_attente(t_centrifugeuse * ptr_cnt) {
	if (ptr_cnt->etat == EN_ARRET || ptr_cnt->etat == EN_FONCTION) {
		ptr_cnt -> etat = EN_ATTENTE;
		return 1;
	}
	return 0;
}
/*permet de mettre une centrifugeuse EN_ATTENTE  ou EN_FONCTION dans l’état 
EN_ARRET.  Retour de 1 si réussi, 0 sinon.*/
int set_en_arret(t_centrifugeuse * ptr_cnt) {
	if (ptr_cnt->etat == EN_ATTENTE || ptr_cnt->etat == EN_FONCTION) {
		ptr_cnt->etat = EN_ARRET;
		return 1;
	}
	return 0;
}
/*déclenche les changements de compteurs selon son état.  Si la centrifugeuse 
est EN_BRIS et son compte à rebours ≠ INFINI alors décrémenter le compte à 
rebours et s’il tombe à 0, la centrifugeuse passe à l’état EN_ARRET et les deux
compteurs tout comme la probabilité de bris sont réinitialisés à leurs valeurs
de départ.  Si la centrifugeuse est EN_ATTENTE ou EN_FONCTION,  la probabilité
de bris s’applique et déclenche un test de bris, si la centrifugeuse passe 
EN_BRIS suite à ce test, son compte à rebours est fixé à une constante très 
grande du module (INFINI) et son nombre de bris est incrémenté. Sinon, seule 
la probabilité de bris va croitre (avec une fonction static du module).  
La fonction retourne l’état de la centrifugeuse.*/
int  toc_centrifugeuse(t_centrifugeuse * ptr_cnt) {
	double test_bris;

	/*pour eviter la repitition des memes valeurs retourne par rand() a chaque 
	execution*/
	//srand(time(NULL));
	test_bris = 1.0 * rand() / RAND_MAX;
	#ifdef DEBUG
		printf("\ntest bris: %lf\n", test_bris);
	#endif
	if (ptr_cnt->etat == EN_BRIS && ptr_cnt->compte_rebours != INFINI) {
		ptr_cnt->compte_rebours--;
	}

	/*ce if doit rester avant le if (test_bris < ptr_cnt->prob_bris)
	afin que tab_tocs EN_BRIS s'incremente au prochain toc suivant
	un bris*/
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

	if (test_bris < ptr_cnt->prob_bris) {
		ptr_cnt->etat = EN_BRIS;
		ptr_cnt->compte_rebours = INFINI;
		ptr_cnt->nb_bris++;
	}
	else {
		accroitre_prob(ptr_cnt);
	}
	
	if (ptr_cnt->compte_rebours <= 0) {
		ptr_cnt->etat = EN_ARRET;
		ptr_cnt->nb_tocs_en_fonction = 0;
		ptr_cnt->nb_tocs_en_attente = 0;
		ptr_cnt->prob_bris = PROB_BRIS_INIT;
	}
	//La fonction retourne l’état de la centrifugeuse.
	return ptr_cnt->etat;
}

/*qui ne s’applique qu’à une centrifugeuse EN_BRIS dont le compte à rebours est
égal à INFINI, elle fixe alors le compte à rebours de la centrifugeuse au temps
reçu en paramètre et retourne 1, sinon elle retourne 0.*/
int set_temps_reparation(t_centrifugeuse * ptr_cnt, uint temps) {
	if (ptr_cnt->etat == EN_BRIS && ptr_cnt->compte_rebours == INFINI) {
		ptr_cnt->compte_rebours = temps;
		return 1;
	}
	return 0;
}

/*va placer à partir de l’adresse reçue et dans l’ordre prescrit les huit 
compteurs présents dans la variable :  les quatre compteurs d’état suivi du 
nombre de bris, des deux compteurs de tocs depuis la dernière réparation et
du compte à rebours.*/
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

//retourne la probabilité de bris actuelle de la centrifugeuse
double get_prob_bris(const t_centrifugeuse * ptr_cnt) {
	return ptr_cnt->prob_bris;
}

/*
fait croitre la probabilité de bris d’une centrifugeuse EN_ATTENTE ou 
EN_FONCTION après un toc sans bris.  ATTENTION, dans sa définition 
l’accroissement calculé va dépendre de trois des compteurs de la 
centrifugeuse : principalement du nombre de bris déjà subis et des deux 
compteurs depuis la réparation. Ce procédé reste personnel à votre équipe.
L’accroissement donné à une centrifugeuse  EN_ATTENTE doit être une fraction
moindre de celle donnée à une EN_FONCTION (cette fraction doit être définie 
par une constante du module).

HYPOTHESES: 
	-On suppose que l'etat est seulement soit EN_ATTENTE ou EN_FONCTION
	-On suppose que la fonction se fait appele apres un
		toc sans bris*/
static void accroitre_prob(t_centrifugeuse * ptr_cnt) {
	/*
		L’accroissement de prob_bris calculé va dépendre de 3 des compteurs de 
		la centrifugeuse :
			-nombre de bris déjà subis:
				1-ptr_cnt->nb_bris
			-des deux compteurs depuis la réparation:
				2-ptr_cnt->nb_tocs_en_attente
				3-ptr_cnt->nb_tocs_en_fonction
	*/
	double prob_bris_en_fonction = ptr_cnt->prob_bris;
	double prob_bris_en_attente;

	prob_bris_en_fonction += (double)ptr_cnt->nb_tocs_en_fonction *
		ptr_cnt->prob_bris + (double)ptr_cnt->nb_tocs_en_attente * 
		ptr_cnt->prob_bris + (double)ptr_cnt->nb_bris * ptr_cnt->prob_bris;

	/*L’accroissement donné à une centrifugeuse  EN_ATTENTE doit être une 
	fraction moindre de celle donnée à une EN_FONCTION(cette fraction doit
	être définie par une constante du module).*/
	//fraction = FRACTION_PROB_BRIS
	prob_bris_en_attente = FRACTION_PROB_BRIS * prob_bris_en_fonction;
	
	if (ptr_cnt->etat == EN_FONCTION) {
		ptr_cnt->prob_bris = prob_bris_en_fonction;
	}
	else if (ptr_cnt->etat == EN_ATTENTE) {
		ptr_cnt->prob_bris = prob_bris_en_attente;
	}
	
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


