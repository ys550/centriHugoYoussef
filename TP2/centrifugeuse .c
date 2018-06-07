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

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/
//Si vous en avez, voici un bon endroit pour les introduire. 

#define  CONSTANTE1  -1     //d�finition d'une constante qui vaut -1


/*=========================================================*/
/*=========================================================*/
//Programme principal: fonction qui retourne un entier (int)
int main(void) {





	printf("hello world");



	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."	
	system("pause");

	// et �A, c'est le retour d'un 0 au syst�me d'exploitation.
	return EXIT_SUCCESS;
}

/*=========================================================*/


