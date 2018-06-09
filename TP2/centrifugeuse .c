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

t_centrifugeuse init_centrifugeuse(void) {
	t_centrifugeuse nouvel_centri;
	
	nouvel_centri.etat = EN_ARRET;
	nouvel_centri.prob_bris = PROB_BRIS_INIT;
	nouvel_centri.compte_rebours = 20;

	return nouvel_centri;
}
int set_en_fonction(t_centrifugeuse * ptr_cnt) {
	if (ptr_cnt -> etat == EN_ATTENTE) {
		ptr_cnt -> etat = EN_FONCTION;
		return 1;
	}	
	return 0;
}
int set_en_attente(t_centrifugeuse * ptr_cnt) {
	if (ptr_cnt -> etat == EN_ARRET || ptr_cnt -> etat == EN_FONCTION) {
		ptr_cnt -> etat = EN_ATTENTE;
		return 1;
	}
	return 0;
}
int set_en_arret(t_centrifugeuse * ptr_cnt) {
	if (ptr_cnt -> etat == EN_ATTENTE || ptr_cnt -> etat == EN_FONCTION) {
		ptr_cnt -> etat = EN_ARRET;
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

}
int set_temps_reparation(t_centrifugeuse * ptr_cnt, uint temps) {}
void get_compteurs(const t_centrifugeuse * ptr_cnt, uint * compteurs) {}
double get_prob_bris(const t_centrifugeuse * ptr_cnt) {}
static  void accroitre_prob(t_centrifugeuse * ptr_cnt) {}


