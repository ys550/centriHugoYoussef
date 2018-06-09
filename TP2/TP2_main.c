/*===========================================================*/
/* 	INF145 - Gabarit (template) de base d'un programme en C. */
/*===========================================================*/

/*
Cette section servira plus tard dans l'�criture du fichier "*.h" d'un module.

Module :
Par    :
Date   :

Ce module offre .....
avec ici plein de commentaires ESSENTIEL � TOUT CLIENT �VENTUEL du
module, chaque �l�ment public (constante, type, fonction) offert
par ce module doit �tre bien expliqu� ici.
*/


/*=========================================================*/
/*
Ce gabarit d'un programme en premi�re semaine de C contient un "main()".

N'oubliez pas de commenter votre code. Pr�f�rablement au f�r et � mesure que vous
etes en train d'�crire.	Du code correct, bien test� mais sans indication du
probl�me r�solu, �a vaut quoi?
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

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/
//Si vous en avez, voici un bon endroit pour les introduire. 

#define  CONSTANTE1  -1     //d�finition d'une constante qui vaut -1


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

	// et �A, c'est le retour d'un 0 au syst�me d'exploitation.
	return EXIT_SUCCESS;
}

/*=========================================================*/


