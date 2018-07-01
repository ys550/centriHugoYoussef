/*===========================================================*/
/* 	INF145 - t_usine.h                                          */
/*===========================================================*/

/*

Module : t_usine.h
Par    :
Date   :22/06/18

-Ce module permet la simulation d'une usine de centrifigeuse qui doit �tre
responsable de ce maintenir en marche avec toujours 100 centrifugeuse en
fonction.

-Il va permettre � l'utilisateur � faire varier 2 variables:
	- le nombre de ligne de 32 centrifugeuses (t_ligne_centrifugeuse)
	- le nombre de centrifugeuse active initialement dans une ligne 
Nous devons trouver une stat�gie pour maintenir le plus longtemps possible
l'usine avec la condtion des 100 centrifugeuses en fonction tout en �tant
"economiquement valable".

-Le module offre le type structur� t_usine avec dans son interface 
les d�clarations de trois fonctions publiques capables d�assurer 
l�initialisation.
Le module offre aussi des fonctions capables de renseigner l��tat de l�usine.



*/

/*=========================================================*/
/*                  FICHERS INCLUDE                        */
/*=========================================================*/


#include <stdlib.h>
#include <stdio.h>
#include "op_bits.h"



/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/


#define NB_FONC_LIG_MAX 22
#define NB_FONC_LIG 22
#define MAX_BRIS 4
//remplacer apres 500 tocs
#define TOCS_REMP 500
#define USINE_EN_MARCHE 100
#define NB_LIGNE_MAX 50
#define TAILLE_POUBELLE_INIT 10




/*=========================================================*/
/*                       STRUCTURE                         */
/*=========================================================*/

typedef struct {

	//Tableau dynamique de t_ligne_centrifugeuse
	t_ligne_centrifugeuse* tab_ligne_centrifugeuse;
	
	/* Tableau dynamique de conservation des centrifugeuse mises 
	au rebus lors de l'entretien sur une ligne*/
	t_centrifugeuse* tab_poubelle_ligne; //realloc


	/*Ce nombre repr�sente le nombre de centrifugeuse qui ont �t�
	remplac�es par une neuve.*/
	int taille_poubelle; //cette taille vas changer

	//Nombre de centrifugeuse en entretien sur une ligne
	int  nb_poubelle_ligne; //TO-DO: initialiser a 0

	//Le nombre de ligne
	//strategie: nb_fonc=ceil(USINE_EN_MARCHE/NB_FONC_LIG)
	int taille_tab_ligne; 

	//Le nombre initial de centrifugeuses EN_FONCTION
	//obtenue par le PARAMETRE nb_fonction de init_usine()
	int nb_ini_fonction; 

	//Nombre de centrifugueuse en fonction et en bris au toc donn�
	int nb_actuel_en_fonction;
	int nb_actuel_en_bris;

	//Nombre de toc d�clench�
	int nb_toc;

	//Nombre de bris observs � date dans l'usine
	int nb_bris_usine;

}t_usine;


/********************************************************************/
/*						DECLARATIONS DE FONCTIONS					*/
/********************************************************************/

/*init_usine

Cette fonction initialise un nombre de t_ligne_centrifugeuse et le nombre
de centrifugeuse en fonction dans chaque ligne

PARAMETRE : -la structure t_usine d�finie 
			-le nombre de centrifugeuse initialis�es en fonction
			 dans chaque ligne
			
VALEUR DE RETOUR : 1 si r�ussi, 0 sinon.
*/
int init_usine(t_usine * ptr_usine, uint nb_fonction);


/*******************************************************************************/

/*toc_usine

Cette fonction assure que chaque ligne de centrifugeuse subissent un toc.
Pour chaque centrifugeuse devenu en bris, la fonction trouvera une 
centrifugeuse � mettre en fonctionn(peu importe sa ligne).

PARAMETRE : -la structure t_usine d�finie

VALEUR DE RETOUR : Nombre de centrifeuse en fonction apr�s le toc
*/
int  toc_usine(t_usine * ptr_usine);


/******************************************************************************/

/*entretien_usine

Cette fonction observe les centrifugeuses de l'usine et va les remplacer
si les conditions de remplacement d�finie dans le programme (nb de bris de la 
centrifugeuse et sa probabilit� de bris > seuil de tol�rance d�finie).
Les centrifugeuse remplac�es sont mises dans le tableau dynamique poubelle_ligne.

PARAMETRE : -la structure t_usine d�finie

VALEUR DE RETOUR : Nombre de centrifeuse qui sont remplac�es
*/
int entretien_usine(t_usine * ptr_usine);


/******************************************************************************/

/*get_nb_total_en_fonction

Cette fonction donne le nombre de centrifigeuse en fonction dans l'usine

PARAMETRE : -la structure t_usine d�finie

VALEUR DE RETOUR : Nombre de centrifeuse en fonction dans l'usine
*/
int get_nb_total_en_fonction(t_usine * ptr_usine);


/******************************************************************************/

/*get_nb_actuel_en_bris

Cette fonction donne le nombre de centrifigeuse en bris dans l'usine

PARAMETRE : -la structure t_usine d�finie

VALEUR DE RETOUR : Nombre de centrifeuse en bris actuellement dans l'usine
*/
int get_nb_actuel_en_bris(t_usine * ptr_usine);


/******************************************************************************/

/*get_nb_toc

Cette fonction donne le nombre de toc depuis le d�marage de l'usine

PARAMETRE : -la structure t_usine d�finie 

VALEUR DE RETOUR : Nombre de =toc depuis l'initialisation de l'usine
*/
int get_nb_toc(t_usine * ptr_usine);


/******************************************************************************/

/*get_nb_bris_total

Cette fonction donne le nombre bris depuis le d�marage de l'usine 

PARAMETRE : -la structure t_usine d�finie

VALEUR DE RETOUR : Nombre de bris depuis l'initialisation de l'usine
*/
int get_nb_bris_total(t_usine * ptr_usine);



/********************************************************************/
/*				DECLARATIONS DE FONCTIONS STATIQUE					*/
/********************************************************************/