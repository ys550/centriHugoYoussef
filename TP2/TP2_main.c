/*===========================================================*/
/* 	INF145 - MAIN                                            */
/*===========================================================*/

/*

Module : main
Par    :
Date   :20/06/18

Ce module est la fonction principale de notre programme:
- Le programme simule un controle d'un dispositif lin�aire de centrifugeuse,
  le dispositif est soumis � des contraintes de maintenance et de s�curit� qui
  oblige � ne pas avoir plus de 2 centrifugeuse fonctionelle voisine.
- L'�tat d'une centrifugeuse est d�finie par la valeur 1 d'un bit et nous 
  assumons qu'une ligne de centrifugeuse ne pourra jamais d�passer 32 en taille.
- L'agorithme va nous pr�senter toutes les configuration possibles en fonction 
  des conditions donn�es par l'utilisateur : le nombre total de centrifugeuse 
  et le nombre d'active.
- Chaque centrifugeuse auront un �tat d�fini:
		EN_FONCTION : la centrifugeuse est active (chaque rotation augmente la 
		              probabilit�e de cassage (en bris).
		EN_BRIS: La centrifugeuse est cass�e, elle est donc inactive jusqu'a la 
				 r�paration de celle-ci.
		EN_ATTENTE : pour que la centrifugeuse soit en fonction a vitesse de rotation
					 maximal, il faut la mettre dans un �tat secondaire o� sa vitesse
					 de rotation est moindre.
					 Elle subit toujours le risque de cassage, mais il est plus 
					 faible que lorsqu'elle est en fonction.
		EN_ARRET : la centrifugeuse n'est pas active
  -Pour l'instant, le module main de du programme comporte seulement les tests
   des fonctions cr�es pour r�aliser notre objectif. Pour ex�cuter chaque test,
   vous devez mettre la condition de compilation #if � 1 et v�rifier que les autres 
   test on des #if(0).
*/



/*=========================================================*/
//Permet de d�sactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles � inclure 
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
	int temps;
	int est_reussi;
	int position;
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
		Compte d'etat EN_ARRET: 1
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
	*****************TEST: Toc_centrifugeuse******************
	*********************************************************/

	/*ce test mets la centrifugeuse en fonct jusqu'elle ce brise la repare puis la
	mets en fonctionnement une autre fois jusqu'elle se brise une deuxime fois*/
	#if (0)
		uint temps_reparation = 5;
		uint compteur[8];
		int nb_tocs = temps_reparation + 1;
		int etat;
		
		cent = init_centrifugeuse();
		print_centrifugeuse(&cent);
		set_en_attente(&cent);
		set_en_fonction(&cent);

		do {
			etat = toc_centrifugeuse(&cent);
			printf("EN_BRIS = 0, EN_ARRET = 1, EN_ATTENTE = 2, " 
				"EN_FONCTION = 3");
			printf("\nETAT Retourne par toc_centri: %d\n", etat);
			//Test: get_prob_bris
			printf("\n get_prob_bris: %lf \n", get_prob_bris(&cent));
			print_centrifugeuse(&cent);
		} while (etat != EN_BRIS);

		printf("\n*****FIN PREMIERE BOULCE DE TOC*****\n Temps Reparation = %u\n", 
			temps_reparation);
		set_temps_reparation(&cent, temps_reparation);
		print_centrifugeuse(&cent);

		do {
			etat = toc_centrifugeuse(&cent);
			printf("EN_BRIS = 0, EN_ARRET = 1, EN_ATTENTE = 2, "
				"EN_FONCTION = 3");
			printf("\nETAT Retourne par toc_centri: %d\n", etat);
			//Test: get_prob_bris
			printf("\n get_prob_bris: %lf \n", get_prob_bris(&cent));
			print_centrifugeuse(&cent);
		} while (etat == EN_BRIS);
		printf("\n*****FIN DE REPARATION*****\n");
		
		set_en_attente(&cent);
		etat = toc_centrifugeuse(&cent);
		print_centrifugeuse(&cent);
		set_en_fonction(&cent);
		etat = toc_centrifugeuse(&cent);
		print_centrifugeuse(&cent);

		do {
			etat = toc_centrifugeuse(&cent);
			printf("EN_BRIS = 0, EN_ARRET = 1, EN_ATTENTE = 2, "
				"EN_FONCTION = 3");
			printf("\nETAT Retourne par toc_centri: %d\n", etat);
			//Test: get_prob_bris
			printf("\n get_prob_bris: %lf \n", get_prob_bris(&cent));
			print_centrifugeuse(&cent);
		} while (etat != EN_BRIS);

		printf("\n*************Test get_compteur**************\n");
		//Test: get_compteur
		get_compteurs(&cent, compteur);
		printf("\nCompte d'etat EN_BRIS: %u", compteur[EN_BRIS]);
		printf("\nCompte d'etat EN_ARRET: %u", compteur[EN_ARRET]);
		printf("\nCompte d'etat EN_ATTENTE: %u", compteur[EN_ATTENTE]);
		printf("\nCompte d'etat EN_FONCTION: %u\n", compteur[EN_FONCTION]);
		printf("\nNb Bris: %u", compteur[4]);
		printf("\nNb tocs en attente: %u", compteur[5]);
		printf("\nNb tocs en fonction: %u", compteur[6]);
		printf("\nCompte a rebours: %u\nB", compteur[7]);
	
	#endif
		
	/*********************************************************
	**********************TEST: ligne**************************
	**********************************************************/
	#if (0)
		
		t_ligne_centrifugeuse ligne;
		init_ligne_centrifugeuse(&ligne, 32);
		print_ligne_centrifugeuse(&ligne);

		printf("\n\n");

		init_ligne_centrifugeuse(&ligne, 10);
		print_ligne_centrifugeuse(&ligne);

		printf("\n\n");

		init_ligne_centrifugeuse(&ligne, 33);
		print_ligne_centrifugeuse(&ligne);

	#endif

	/*********************************************************
	*********************TEST: Ligne**************************
	*********************************************************/
	#if (0)
		t_ligne_centrifugeuse ligne;
		/*mets k=+~2/3 * nb en fonction*/
		init_ligne_centrifugeuse(&ligne, 20);
		//La somme des centrifugueses de chaque etat affiche doit etre = 32
		print_ligne_centrifugeuse(&ligne);
		toc_ligne(&ligne);
	#endif

		/*********************************************************
		*******************TEST: Toc Ligne************************
		*********************************************************/
	#if (1)
		t_ligne_centrifugeuse ligne;

		//avec NB_CENT_DEPART = 10 par exemple
		init_ligne_centrifugeuse(&ligne, NB_CENT_DEPART);
		print_ligne_centrifugeuse(&ligne);
		/* ici faites imprimer l'�tat initial de la ligne (trains de bits et compteurs) */
		temps = 0;
		do {
			temps++;
			//*** avec ajout du param�tre "temps" pour les affichages d��v�nements
			toc_ligne(&ligne, temps);

			//tant que les 10 + 2 ne sont pas toutes bris�es
		} while ((get_nb_bris_lig(&ligne) <  (NB_CENT_DEPART + NBR_K_EN_ATTENTE)));
	#endif
		//avec reparation
	#if (0)
		t_ligne_centrifugeuse ligne;

		//avec NB_CENT_DEPART = 10 par exemple
		init_ligne_centrifugeuse(&ligne, NB_CENT_DEPART);
		print_ligne_centrifugeuse(&ligne, 0);
		/* ici faites imprimer l'�tat initial de la ligne (trains de bits et compteurs) */
		temps = 0;
		do {
			temps++;
			//*** avec ajout du param�tre "temps" pour les affichages d��v�nements
			toc_ligne(&ligne, temps);

			//tant que les 10 + 2 ne sont pas toutes bris�es
		} while ((get_nb_bris_lig(&ligne) <  (NB_CENT_DEPART + NBR_K_EN_ATTENTE)));
	#endif

		/*********************************************************
		*********************TEST: Ajout et reduire***************
		*********************************************************/
#if (0)

	t_ligne_centrifugeuse ligne;
	//Mise en place � la configuration initial avec un nb de bit 10
	est_reussi = init_ligne_centrifugeuse(&ligne, 10);
	printf("\nReussi (Oui = 1, Non = 0) : %d", est_reussi);
	//affiche la configuration initiale
	printf("\nconfiguration initiale");
	print_ligne_centrifugeuse(&ligne);

	printf("\n\n");

	//diminution du nb de centrifugeuse active par 1
	est_reussi=reduire_cnt(&ligne);
	printf("\nReussi (Oui = 1, Non = 0) : %d", est_reussi);
	//configuration initial en elevant une centrifugeuse 
	printf("\nconfiguration initiale - 1 centrifugeuse active");
	print_ligne_centrifugeuse(&ligne);

	printf("\n\n");
	
	//ajout d'une centrifugeuse pour retourner � la configuration initiale
	est_reussi = ajouter_cnt(&ligne);
	printf("\nReussi (Oui = 1, Non = 0) : %d", est_reussi);
	//retour � la configuration initiale
	printf("\nconfiguration initiale");
	print_ligne_centrifugeuse(&ligne);

#endif

	/*********************************************************
	*********************TEST: remplacer**********************
	*********************************************************/

#if (0)

	t_ligne_centrifugeuse ligne;
	//Mise en place � la configuration initial avec un nb de bit 10
	est_reussi = init_ligne_centrifugeuse(&ligne, 10);
	print_ligne_centrifugeuse(&ligne);

	printf("\n\n");

	t_etat position = ligne[10].etat
	
#endif
	
		/*********************************************************
		*********************TEST: get en �tat********************
		*********************************************************/








	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."	
	system("pause");

	// et �A, c'est le retour d'un 0 au syst�me d'exploitation.
	return EXIT_SUCCESS;
}

/*=========================================================*/


