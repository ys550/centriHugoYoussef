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

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/
//Si vous en avez, voici un bon endroit pour les introduire. 

#define  CONSTANTE1  -1     //définition d'une constante qui vaut -1


/*=========================================================*/
/*=========================================================*/
//Programme principal: fonction qui retourne un entier (int)
int main(void) {
	int est_reussi;
	t_centrifugeuse cent;
	cent = init_centrifugeuse();
	//affiche EN_ARRET (1) et prob = 0.001
	printf("initialise: %d prob: %lf\n", cent.etat, cent.prob_bris);

	est_reussi = set_en_arret(&cent);
	//affiche EN_ARRET (1) et prob = 0.001 est_reussi = 0
	printf("initialise: %d prob: %lf Est-reussis?: %d\n", cent.etat, cent.prob_bris, est_reussi);

	est_reussi = set_en_attente(&cent);
	//affiche EN_ATTENTE (2) et prob = 0.001 est_reussi = 1
	printf("initialise: %d prob: %lf Est-reussis?: %d\n", cent.etat, cent.prob_bris, est_reussi);

	//printf("taille uint: %d\n", sizeof(uint));

	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."	
	system("pause");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}

/*=========================================================*/


