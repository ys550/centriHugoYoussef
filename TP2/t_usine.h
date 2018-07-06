/*

Module : t_usine.h
Par    : Youssef Soliman, Hugo Belin
Date   :07/04/18

-Ce module permet la simulation d'une usine de centrifigeuse qui doit être
responsable de ce maintenir en marche avec toujours 100 centrifugeuse en
fonction.

-Il va permettre à l'utilisateur à faire varier 2 variables:
	- le nombre de ligne de 32 centrifugeuses (t_ligne_centrifugeuse)
	- le nombre de centrifugeuse active initialement dans une ligne 
Nous devons trouver une statégie pour maintenir le plus longtemps possible
l'usine avec la condtion des 100 centrifugeuses en fonction tout en étant
"economiquement valable".

-Le module offre le type structuré t_usine avec dans son interface 
les déclarations de trois fonctions publiques capables d’assurer 
l’initialisation.
Le module offre aussi des fonctions capables de renseigner l’état de l’usine.



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

/*le nb de cent en fonction par ligne ne doit pas depasser le 
max(NB_FONC_MAX (22))*/
#define NB_FONC_LIG 12

//le nombre max de bris d'une cent avant son remplacement
#define MAX_BRIS 4

//remplacer cent en bris apres un nb de tocs definis par cette constante
#define TOCS_REMP 500

#define TAILLE_POUBELLE_INIT 32
#define ACCROISSEMENT_TAB_POUBELLE 22

#define LIGNE_FIN 1
//ligne supplementaire prete a prendre la releve en cas de bris (realloc)
#define ACCROISSEMENT_TAB_LIGNE 1




/*=========================================================*/
/*                       STRUCTURE                         */
/*=========================================================*/

typedef struct {

	//Tableau dynamique de t_ligne_centrifugeuse
	t_ligne_centrifugeuse * tab_ligne_centrifugeuse;
	
	/* Tableau dynamique de conservation des centrifugeuse mises 
	au rebus lors de l'entretien sur une ligne*/
	t_centrifugeuse * tab_poubelle_ligne;


	/*Taille dynamique du tableau pour les cent mises au rebus*/
	int taille_tab_poubelle;

	//Nombre de centrifugeuse en entretien sur une ligne
	int  nb_cent_remplace;

	//Le nombre de ligne
	int taille_tab_ligne; 

	//Le nombre initial de centrifugeuses EN_FONCTION
	//obtenue par le PARAMETRE nb_fonction de init_usine()
	int nb_ini_fonction; 

	/***************************************/

	//Nombre de centrifugueuse en fonction et en bris au toc donne
	int nb_actuel_en_fonction;
	int nb_actuel_en_bris;

	//Nombre de toc declenche a date dans l'usine
	int nb_toc;

	//Nombre de bris observs a date dans l'usine
	int nb_bris_usine;

}t_usine;


/********************************************************************/
/*						DECLARATIONS DE FONCTIONS					*/
/********************************************************************/

/*init_usine

Cette fonction initialise un nombre de t_ligne_centrifugeuse et le nombre
de centrifugeuse en fonction dans chaque ligne

PARAMETRE : -la structure t_usine définie 
			-le nombre de centrifugeuse initialisées en fonction
			 dans chaque ligne
			
VALEUR DE RETOUR : 1 si réussi, 0 sinon.
*/
int init_usine(t_usine * ptr_usine, uint nb_fonction);


/*******************************************************************************/

/*toc_usine

Cette fonction assure que chaque ligne de centrifugeuse subissent un toc.
Pour chaque centrifugeuse devenu en bris, la fonction trouvera une 
centrifugeuse à mettre en fonctionn(peu importe sa ligne).

PARAMETRE : -la structure t_usine définie

VALEUR DE RETOUR : Nombre de centrifeuse en fonction après le toc
*/
int  toc_usine(t_usine * ptr_usine, int temps);


/******************************************************************************/

/*entretien_usine

Cette fonction observe les centrifugeuses de l'usine et va les remplacer
si les conditions de remplacement définie dans le programme (nb de bris de la 
centrifugeuse et sa probabilité de bris > seuil de tolérance définie).
Les centrifugeuse remplacées sont mises dans le tableau dynamique poubelle_ligne.

PARAMETRE : -la structure t_usine définie

VALEUR DE RETOUR : Nombre de centrifeuse qui sont remplacées
*/
int entretien_usine(t_usine * ptr_usine);

/******************************************************************************/

/*print_usine

Cette fonction affiche les statistique et lignes de l'usine

PARAMETRE : -ptr_usine:la structure t_usine définie (type:t_usine)

VALEUR DE RETOUR : Aucune
*/
void print_usine(const t_usine * ptr_usine);

/******************************************************************************/

/*get_nb_actuel_en_fonction

Cette fonction donne le nombre de centrifigeuse en fonction dans l'usine

PARAMETRE : -la structure t_usine définie

VALEUR DE RETOUR : Nombre de centrifeuse en fonction dans l'usine
*/
int get_nb_actuel_en_fonction(t_usine * ptr_usine);


/******************************************************************************/

/*get_nb_actuel_en_bris

Cette fonction donne le nombre de centrifigeuse en bris dans l'usine

PARAMETRE : -la structure t_usine définie

VALEUR DE RETOUR : Nombre de centrifeuse en bris actuellement dans l'usine
*/
int get_nb_actuel_en_bris(t_usine * ptr_usine);


/******************************************************************************/

/*get_nb_toc

Cette fonction donne le nombre de toc depuis le démarage de l'usine

PARAMETRE : -la structure t_usine définie 

VALEUR DE RETOUR : Nombre de =toc depuis l'initialisation de l'usine
*/
int get_nb_toc(t_usine * ptr_usine);


/******************************************************************************/

/*get_nb_bris_total

Cette fonction donne le nombre bris depuis le démarage de l'usine 

PARAMETRE : -la structure t_usine définie

VALEUR DE RETOUR : Nombre de bris depuis l'initialisation de l'usine
*/
int get_nb_bris_total(t_usine * ptr_usine);

/********************************************************************/
/*				DECLARATIONS DE FONCTIONS STATIQUE					*/
/********************************************************************/
