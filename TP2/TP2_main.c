/*===========================================================*/
/* 	INF145 - MAIN                                            */
/*===========================================================*/

/*

Module : main
Par    : Youssef Soliman, Hugo Belin
Date   :20/06/18

Ce module est la fonction principale de notre programme:
- Le programme simule un controle d'un dispositif linéaire de centrifugeuse,
  le dispositif est soumis à des contraintes de maintenance et de sécurité qui
  oblige à ne pas avoir plus de 2 centrifugeuse fonctionelle voisine.
- L'état d'une centrifugeuse est définie par la valeur 1 d'un bit et nous 
  assumons qu'une ligne de centrifugeuse ne pourra jamais dépasser 32 en taille.
- L'agorithme va nous présenter toutes les configuration possibles en fonction 
  des conditions données par l'utilisateur : le nombre total de centrifugeuse 
  et le nombre d'active.
- Chaque centrifugeuse auront un état défini:
		EN_FONCTION : la centrifugeuse est active (chaque rotation augmente la 
		              probabilitée de cassage (en bris).
		EN_BRIS: La centrifugeuse est cassée, elle est donc inactive jusqu'a la 
				 réparation de celle-ci.
		EN_ATTENTE : pour que la centrifugeuse soit en fonction a vitesse de rotation
					 maximal, il faut la mettre dans un état secondaire où sa vitesse
					 de rotation est moindre.
					 Elle subit toujours le risque de cassage, mais il est plus 
					 faible que lorsqu'elle est en fonction.
		EN_ARRET : la centrifugeuse n'est pas active
  -Pour l'instant, le module main de du programme comporte seulement les tests
   des fonctions crées pour réaliser notre objectif. Pour exécuter chaque test,
   vous devez mettre la condition de compilation #if à 1 et vérifier que les autres 
   test on des #if(0).
*/



/*=========================================================*/
//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles à inclure 
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "centrifugeuse.h"
#include "ligne_centrifugeuse.h"

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/


/*=========================================================*/
/*=========================================================*/
//Programme principal: fonction qui retourne un entier (int)
int main(void) {
	int temps;
	int est_reussi;
	int position;
	uint result;
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
	*************TEST:MANDAT 1 Toc_centrifugeuse**************
	*********************************************************/

	/*ce test mets la centrifugeuse en fonct jusqu'elle ce brise la repare puis la
	mets en fonctionnement une autre fois jusqu'elle se brise une deuxime fois*/
	#if (0)
		uint temps_reparation = 10;
		uint compteur[8];
		int nb_tocs = 0;
		int etat = 0, etat_prec = 0;
		
		cent = init_centrifugeuse();
		print_centrifugeuse(&cent);
		set_en_attente(&cent);
		set_en_fonction(&cent);

		do {
			nb_tocs++;
			etat_prec = etat;
			etat = toc_centrifugeuse(&cent);
			printf("EN_BRIS = 0, EN_ARRET = 1, EN_ATTENTE = 2, " 
				"EN_FONCTION = 3");
			printf("\nETAT Retourne par toc_centri: %d\n", etat);
			//Test: get_prob_bris
			printf("\n get_prob_bris: %lf \n", get_prob_bris(&cent));
			//print_centrifugeuse(&cent);

			if (etat == EN_BRIS) {


				if (set_temps_reparation(&cent, temps_reparation)) {
					printf("\n*****TOC: %d Temps Reparation = %u\n", nb_tocs, temps_reparation);
					print_centrifugeuse(&cent);
					_getch();
				}
			}
			else if (etat != etat_prec && etat == EN_ARRET) {
				set_en_attente(&cent);
				set_en_fonction(&cent);
				_getch();
			}

		} while (nb_tocs < 300);
		printf("\n*****FIN DE REPARATION*****\n");
		
		set_en_attente(&cent);
		etat = toc_centrifugeuse(&cent);
		print_centrifugeuse(&cent);
		set_en_fonction(&cent);
		etat = toc_centrifugeuse(&cent);
		print_centrifugeuse(&cent);

	
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
	#if (1)
		
		t_ligne_centrifugeuse ligne;
		init_ligne_centrifugeuse(&ligne, 33);
		printf("\nNb=33\n");
		print_ligne_centrifugeuse(&ligne);

		init_ligne_centrifugeuse(&ligne, 32);
		printf("\nNb=32\n");
		print_ligne_centrifugeuse(&ligne);

		init_ligne_centrifugeuse(&ligne, 31);
		printf("\nNb=31\n");
		print_ligne_centrifugeuse(&ligne);

		init_ligne_centrifugeuse(&ligne, 10);
		printf("\nNb=10\n");
		print_ligne_centrifugeuse(&ligne);

		init_ligne_centrifugeuse(&ligne, 30);
		printf("\nNb=30\n");
		print_ligne_centrifugeuse(&ligne);

		init_ligne_centrifugeuse(&ligne, 14);
		printf("\nNb=14\n");
		print_ligne_centrifugeuse(&ligne);

		init_ligne_centrifugeuse(&ligne, 15);
		printf("\nNb=15\n");
		print_ligne_centrifugeuse(&ligne);

		init_ligne_centrifugeuse(&ligne, 16);
		printf("\nNb=16\n");
		print_ligne_centrifugeuse(&ligne);

		init_ligne_centrifugeuse(&ligne, 17);
		printf("\nNb=17\n");
		print_ligne_centrifugeuse(&ligne);

		init_ligne_centrifugeuse(&ligne, 18);
		printf("\nNb=18\n");
		print_ligne_centrifugeuse(&ligne);

		init_ligne_centrifugeuse(&ligne, 0);
		printf("\nNb=0\n");
		print_ligne_centrifugeuse(&ligne);

		init_ligne_centrifugeuse(&ligne, 1);
		printf("\nNb=1\n");
		print_ligne_centrifugeuse(&ligne);

		init_ligne_centrifugeuse(&ligne, 2);
		printf("\nNb=2\n");
		print_ligne_centrifugeuse(&ligne);

		init_ligne_centrifugeuse(&ligne, 3);
		printf("\nNb=3\n");
		print_ligne_centrifugeuse(&ligne);

		init_ligne_centrifugeuse(&ligne, 4);
		printf("\nNb=4\n");
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
		**************TEST: MANDAT2 TOC LIGNE********************
		*********************************************************/
	#if (0)
		t_ligne_centrifugeuse ligne;

		//avec NB_CENT_DEPART = 14 par exemple
		init_ligne_centrifugeuse(&ligne, 14);
		print_ligne_centrifugeuse(&ligne);
		printf("\nTEST DE PERUTER avec NB=24 de pos 16 et 24\n\n");
		permuter_centrifugeuse(&ligne, 16, 24);
		print_ligne_centrifugeuse(&ligne);

		printf("\nInit avec NB_CENT_DEPART = 10\n\n");
		init_ligne_centrifugeuse(&ligne, NB_CENT_DEPART);
		print_ligne_centrifugeuse(&ligne);
		/* ici faites imprimer l'état initial de la ligne (trains de bits et compteurs) */
		temps = 0;
		do {
			temps++;
			//*** avec ajout du paramètre "temps" pour les affichages d’événements
			toc_ligne(&ligne, temps);

			//tant que les 10 + 2 ne sont pas toutes brisées
		} while ((get_nb_bris_lig(&ligne) <  (NB_CENT_DEPART + NBR_K_EN_ATTENTE)));
	#endif

		/*********************************************************
		*********************TEST: Ajout et reduire***************
		*********************************************************/
	#if (0)

		t_ligne_centrifugeuse ligne;
		//Mise en place à la configuration initial avec un nb de bit 10
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
	
		//ajout d'une centrifugeuse pour retourner à la configuration initiale
		est_reussi = ajouter_cnt(&ligne);
		printf("\nReussi (Oui = 1, Non = 0) : %d", est_reussi);
		//retour à la configuration initiale
		printf("\nconfiguration initiale");
		print_ligne_centrifugeuse(&ligne);

	#endif

	/*********************************************************
	*********************TEST: remplacer**********************
	*********************************************************/

	#if (0)
		t_ligne_centrifugeuse ligne;
		est_reussi = init_ligne_centrifugeuse(&ligne, 15);
		//Force la centrifugeuse en bris
		cent.etat = EN_BRIS;

		print_centrifugeuse(&cent); //Caracteristique avant le remplacage

		if (cent.etat == EN_BRIS) { //tester avec les conditions ideales
			cent.tab_tocs[EN_BRIS]++;
			SET_BIT(ligne.config_bris, 20);
			// Fonction a tester dans la position qui en bris
			cent = remplacer_cnt(&ligne, 20);
			print_centrifugeuse(&cent); //Caracteristique apres le remplacement
			print_ligne_centrifugeuse(&ligne);
		}

		// Fonction a tester dans la position qui en fonction 
		cent = remplacer_cnt(&ligne, 0);
		print_centrifugeuse(&cent); //donc retourne centrifugeuse_membres_0()

	
	#endif
	
		/*********************************************************
		*********************TEST: get en état********************
		*********************************************************/
   #if(0)  
		const t_ligne_centrifugeuse  ligne;
		est_reussi = init_ligne_centrifugeuse(&ligne, 15);

		//test avec l'état en fonction
		result=get_en_etat(&ligne, EN_FONCTION);
		//Lecture en chaine de bits du unsigned int du retour de la fonction
		printf("\n\n EN_FONCTION   ==%12u == %s ", result, bits2string(result));

		//test avec l'état en attente
		result=get_en_etat(&ligne, EN_ATTENTE);
		//Lecture en chaine de bits du unsigned int du retour de la fonction
		printf("\n\n EN_ATTENTE    ==%12u == %s ", result, bits2string(result));

		//test avec l'état en arret
		result=get_en_etat(&ligne, EN_ARRET);
		//Lecture en chaine de bits du unsigned int du retour de la fonction
		printf("\n\n EN_ARRET      ==%12u == %s ", result, bits2string(result));

		//test avec l'état en bris
		get_en_etat(&ligne, EN_BRIS);
		//Lecture en chaine de bits du unsigned int du retour de la fonction
		result=printf("\n\n EN_BRIS       ==%12u == %s ", result, bits2string(result));
	
	#endif
		
		/*********************************************************
		*********************TEST: GET CENTRIFUGEUSE**************
		*********************************************************/
#if (0)
		const t_ligne_centrifugeuse  ligne; //initialisation 
		est_reussi = init_ligne_centrifugeuse(&ligne, 15);

		result = get_en_etat(&ligne, EN_FONCTION); 
		//Lecture en chaine de bits du unsigned int du retour de la fonction
		printf("\n\n EN_FONCTION   ==%12u == %s ", result, bits2string(result));
		//D'après la lecture de la chaine en fonction, ce test va nous donner une 
		// centrifugeuse à l'arret 
		cent=get_centrifugeuse(&ligne, 2);
		print_centrifugeuse(&cent);

		//Avec la lecture de la chaine, ce test va nous donner une centrifugeuse 
		// en fonction 
		cent = get_centrifugeuse(&ligne, 1);
		print_centrifugeuse(&cent);
#endif

		/*********************************************************
		*********************TEST: PERMUTER********************
		*********************************************************/
	#if (0)
		t_ligne_centrifugeuse ligne;
		est_reussi = init_ligne_centrifugeuse(&ligne, 14);
		print_ligne_centrifugeuse(&ligne);
		permuter_centrifugeuse(&ligne, 16, 24);
		print_ligne_centrifugeuse(&ligne);
	#endif

	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."	
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}

/*=========================================================*/


