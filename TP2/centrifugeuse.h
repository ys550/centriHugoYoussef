/****************************************
*******INTERFACE DE centrifugeuse********
****************************************/

/*

Module : centrifugeuse.h
Par    : Youssef Soliman, Hugo Belin
Date   :20/06/18

Ce ficher à pour but de créer les constantes, les structures, les énumérations 
et les définitions des fonctions nécéssaire pour la création de l'interface de 
chaque état d'une centrifugeuse. (module centrifugeuse)


/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/
//pour l'affichage de printf pour debug
//#define DEBUG_MANDAT1
#define DEBUG_MANDAT2
/*valeur initiale de prob de bris. Incremente legerement si centri ne se brise
 pas*/
#define PROB_BRIS_INIT 0.0001
//une constante très grande pour represente INFINI (valeur max d'un uint)
#define INFINI 4294967295
//fraction utilise pour le calcul de accroitre prob bris
#define FRACTION_PROB_BRIS 1 / 8

//tous les  unsigned int  sont identifiées par  uint
typedef unsigned int uint;

/*Définies dans l’interface, un type enum donne les quatre constantes
 qui représentent les quatre états possibles d’une centrifugeuse dans la 
 simulation
*/
typedef enum { EN_BRIS, EN_ARRET, EN_ATTENTE, EN_FONCTION } t_etat;

typedef struct {
	//Une variable d’état toujours égale à une des constantes du type énuméré
	t_etat etat;

	/*Un tableau de quatre compteurs de tocs totaux(uint), un pour chacun des 
	quatre états possibles*/
	uint tab_tocs[4];

	/*Un compteur (uint) qui donne le nombre de bris subis à date par la 
	centrifugeuse*/
	uint nb_bris;

	/*Une probabilité de bris, variable réelle dans l’intervalle [0, 1], qui 
	déterminera si une centrifugeuse EN_FONCTION ou EN_ATTENTE qui subit un toc
	risque de briser et de passer à l’état EN_BRIS.  Si la centrifugeuse ne 
	brise pas, sa probabilité de bris s’accroit alors légèrement*/
	double prob_bris;

	/*
	Deux compteurs de tocs (uint), qui gardent le nombre total de tocs 
	EN_FONCTION et EN_ATTENTE depuis la dernière réparation de la 
	centrifugeuse.
	*/
	uint nb_tocs_en_fonction;
	uint nb_tocs_en_attente;

	/*Un compte à rebours (uint) qui est soit à 0 pour une centrifugeuse qui n’est
	pas EN_BRIS ou, pour une centrifugeuse EN_BRIS, sera égale à soit à une 
	constante très grande (INFINI) du module ou au nombre réel de tocs restant 
	à sa réparation.*/
	uint compte_rebours;

} t_centrifugeuse;



/*********************************************************
*********************Déclaration des fonctions*************
*********************************************************/

/*init_centrigugeuse

Cette fonction retourne une centrifugeuse neuve à l’état EN_ARRET.  
Sa probabilité initiale de bris est donnée par la constante PROB_BRIS_INIT.
*/
t_centrifugeuse init_centrifugeuse(void);


/*******************************************************************************/
/*set_en_fonction

Cette fonction permet de mettre une centrifugeuse EN_ATTENTE  dans l’état
EN_FONCTION.

PARAMETRE : Prend les données issu de la structure t_centrifugeuse, le paramètre 
			est de type t_centrifugeuse.

VALEUR DE RETOUR : 1 si réussi, 0 sinon.
*/
int set_en_fonction(t_centrifugeuse * ptr_cnt);


/*******************************************************************************/
/*set_en_attente

Cette fonction permet de mettre une centrifugeuse EN_ARRET ou EN_FONCTION 
dans l’état  EN_ATTENTE.  

PARAMETRE : Prend les données issu de la structure t_centrifugeuse, le paramètre
est de type t_centrifugeuse.

VALEUR DE RETOUR : 1 si réussi, 0 sinon.
*/
int set_en_attente(t_centrifugeuse * ptr_cnt);


/*******************************************************************************/
/*set_en_arret

Cette fonction permet de mettre une centrifugeuse EN_ATTENTE  ou EN_FONCTION 
dans l’état  EN_ARRET. 

PARAMETRE : Prend les données issu de la structure t_centrifugeuse, le paramètre
est de type t_centrifugeuse.

VALEUR DE RETOUR : 1 si réussi, 0 sinon .
*/
int set_en_arret(t_centrifugeuse * ptr_cnt);


/*******************************************************************************/
/*toc_centrifugeuse

Cette fonction déclenche la dimination ou son changement en fonction de 
l'état de la centrifugeuse.

PARAMETRE : Prend les données issu de la structure t_centrifugeuse, le paramètre
est de type t_centrifugeuse.

VALEUR DE RETOUR : retourne l’état de la centrifugeuse.
*/
int  toc_centrifugeuse(t_centrifugeuse * ptr_cnt);


/*******************************************************************************/
/*set_temps_reparation

Cette fonction qui ne s’applique qu’à une centrifugeuse EN_BRIS dont le
compte à rebours est égal à INFINI, elle fixe alors le compte à rebours
de la centrifugeuse au temps reçu en paramètre. 

PARAMETRE : - Prend les données issu de la structure t_centrifugeuse, le paramètre
              est de type t_centrifugeuse.
			- temps, valeur qui va définir le nombre de toc nécessaire à la 
			  la réparation de la centrifugeuse.

VALEUR DE RETOUR : 1 si réussi, 0 sinon .
*/
int set_temps_reparation(t_centrifugeuse * ptr_cnt, uint temps);


/*******************************************************************************/
/*get_compteurs

Cette fonction va donner les compteurs d'une centrifugeuse :
- les quatre compteurs d’état suivi du nombre de bris
- Les deux compteurs de tocs depuis la dernière réparation 
- Le compte à rebours.

PARAMETRE : - Prend les données issu de la structure t_centrifugeuse, le paramètre
			  est de type t_centrifugeuse.
			- Le tableau de compteur ce cette centrifugeuse.


VALEUR DE RETOUR : Les huits compteurs de la centrifugeuse
*/
void get_compteurs(const t_centrifugeuse * ptr_cnt, uint * compteurs);


/*******************************************************************************/
/*get_prob_bris

Cette fonction va donner la probabilité de bris de la centrifugeuse voulu.

PARAMETRE : - Prend les données issu de la structure t_centrifugeuse, le paramètre
est de type t_centrifugeuse.

VALEUR DE RETOUR : La probabilité de bris de la centrifugeuse (double)
*/
double get_prob_bris(const t_centrifugeuse * ptr_cnt);


/*******************************************************************************/
/*accroitre_prob

Cette fonction fait croitre la probabilité de bris d’une centrifugeuse EN_ATTENTE
ou EN_FONCTION après un toc sans bris.  

PARAMETRE : - Prend les données issu de la structure t_centrifugeuse, le paramètre
est de type t_centrifugeuse.

HYPOTHESES:
-On suppose que l'etat est seulement soit EN_ATTENTE ou EN_FONCTION
-On suppose que la fonction se fait appele apres un
toc sans bris
*/
static void accroitre_prob(t_centrifugeuse * ptr_cnt);


/*******************************************************************************/
/*print_centrifugeuse

Cette fonction va nous donner la totalité des données d'une centrifugeuse 

PARAMETRE : - Prend les données issu de la structure t_centrifugeuse, le paramètre
est de type t_centrifugeuse.

VALEUR DE RETOUR : Toutes les données possible sur une centrifugeuse 
*/
void print_centrifugeuse(const t_centrifugeuse * ptr_cnt);


/*******************************************************************************/