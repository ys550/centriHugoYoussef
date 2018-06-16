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

// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "centrifugeuse.h"
#include "ligne_centrifugeuse.h"

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/
#define DEBUG

/*=========================================================*/
/*=========================================================*/
//Programme principal: fonction qui retourne un entier (int)
int main(void) {
	int est_reussi;
	t_centrifugeuse cent;

	/*********************************************************
	*******************TEST: Set et Init**********************
	*********************************************************/
	#if (0)
		//Resultat attendu: valeurs par defaut EN_BRIS (0)
		print_centrifugeuse(&cent);

		/*
		Resultat attendu: Non-Reussi(0) avec valeurs par defaut EN_BRIS (0)
		*/
		est_reussi = set_en_attente(&cent);
		printf("\nReussi (Oui = 1, Non = 0) : %d", est_reussi);
		print_centrifugeuse(&cent);

		/*
		Resultat attendu: valeurs initialise
		Etat: EN_ARRET
		Nb Bris: 0
		Probabilite de Bris: 0.001000
		Compte a rebours: 20
		Nb tocs en fonction: 0
		Nb tocs en attente: 0
		Compte d'etat EN_BRIS: 0
		Compte d'etat EN_ARRET: 0
		Compte d'etat EN_ATTENTE: 0
		Compte d'etat EN_FONCTION: 0
		*/
		cent = init_centrifugeuse();
		print_centrifugeuse(&cent);

		/*
		Resultat attendu: Non-Reussi (0)
		Valeurs inchange
		*/
		est_reussi = set_en_arret(&cent);
		printf("\nReussi (Oui = 1, Non = 0) : %d", est_reussi);
		print_centrifugeuse(&cent);

		/*
		Resultat attendu: Reussi (1)
		Reussi (Oui = 1, Non = 0) : 1
		Etat: EN_ATTENTE
		Nb Bris: 0
		Probabilite de Bris: 0.001000
		Compte a rebours: 20
		Nb tocs en fonction: 0
		Nb tocs en attente: 0
		Compte d'etat EN_BRIS: 0
		Compte d'etat EN_ARRET: 0
		Compte d'etat EN_ATTENTE: 0
		Compte d'etat EN_FONCTION: 0
		*/
		est_reussi = set_en_attente(&cent);
		printf("\nReussi (Oui = 1, Non = 0) : %d", est_reussi);
		print_centrifugeuse(&cent);

		/*
		Resultat attendu: Reussi(1)
		Reussi (Oui = 1, Non = 0) : 1
		Etat: EN_ARRET
		Nb Bris: 0
		Probabilite de Bris: 0.001000
		Compte a rebours: 20
		Nb tocs en fonction: 0
		Nb tocs en attente: 0
		Compte d'etat EN_BRIS: 0
		Compte d'etat EN_ARRET: 0
		Compte d'etat EN_ATTENTE: 0
		Compte d'etat EN_FONCTION: 0
		*/
		est_reussi = set_en_arret(&cent);
		printf("\nReussi (Oui = 1, Non = 0) : %d", est_reussi);
		print_centrifugeuse(&cent);
	#endif
		
	/*********************************************************
	**********************TEST: Tocs**************************
	*********************************************************/
	#if (0)
		int nb_toc = 10;
		int etat;
		uint compteur[8];

		cent = init_centrifugeuse();
		set_en_attente(&cent);
		set_en_fonction(&cent);

		while (nb_toc >= 0) {
			etat = toc_centrifugeuse(&cent);
			printf("EN_BRIS = 0, EN_ARRET = 1, EN_ATTENTE = 2, " 
				"EN_FONCTION = 3");
			printf("\nETAT Retourne par toc_centri: %d\n", etat);
			//Test: get_prob_bris
			printf("\n get_prob_bris: %lf \n", get_prob_bris(&cent));
			print_centrifugeuse(&cent);
			nb_toc--;
		}
		printf("\n*****FIN PREMIERE BOULCE DE TOC*****\n");
		set_temps_reparation(&cent, 3);

		while (nb_toc <= 4) {
			etat = toc_centrifugeuse(&cent);
			printf("EN_BRIS = 0, EN_ARRET = 1, EN_ATTENTE = 2, "
				"EN_FONCTION = 3");
			printf("\nETAT Retourne par toc_centri: %d\n", etat);
			//Test: get_prob_bris
			printf("\n get_prob_bris: %lf \n", get_prob_bris(&cent));
			print_centrifugeuse(&cent);
			nb_toc++;
		}

		//Test: get_compteur
		get_compteurs(&cent, compteur);
		printf("\nCompte d'etat EN_BRIS: %u", compteur[EN_BRIS]);
		printf("\nCompte d'etat EN_ARRET: %u", compteur[EN_ARRET]);
		printf("\nCompte d'etat EN_ATTENTE: %u", compteur[EN_ATTENTE]);
		printf("\nCompte d'etat EN_FONCTION: %u\n", compteur[EN_FONCTION]);
		printf("\nNb Bris: %u", compteur[4]);
		printf("\nNb tocs en attente: %u", compteur[5]);
		printf("\nNb tocs en fonction: %u", compteur[6]);
		printf("\nCompte a rebours: %u", compteur[7]);
	
	#endif
	#if (1)
		/*********************************************************
		**********************TEST: ligne**************************
		*********************************************************/
		t_ligne_centrifugeuse ligne;
		init_ligne_centrifugeuse(&ligne, 32);
		print_ligne_centrifugeuse(&ligne);

		printf("\n*********************************************\n");

		init_ligne_centrifugeuse(&ligne, 10);
		print_ligne_centrifugeuse(&ligne);

		printf("\n*********************************************\n");

		init_ligne_centrifugeuse(&ligne, 33);
		print_ligne_centrifugeuse(&ligne);

	#endif

	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."	
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}

/*=========================================================*/


