/****************************************
*******INTERFACE DE centrifugeuse********
****************************************/

/*

Module : centrifugeuse.h
Par    : Youssef Soliman, Hugo Belin
Date   :20/06/18

Ce ficher � pour but de cr�er les constantes, les structures, les �num�rations 
et les d�finitions des fonctions n�c�ssaire pour la cr�ation de l'interface de 
chaque �tat d'une centrifugeuse. (module centrifugeuse)


/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/
//pour l'affichage de printf pour debug
//#define DEBUG_MANDAT1
#define DEBUG_MANDAT2
/*valeur initiale de prob de bris. Incremente legerement si centri ne se brise
 pas*/
#define PROB_BRIS_INIT 0.0001
//une constante tr�s grande pour represente INFINI (valeur max d'un uint)
#define INFINI 4294967295
//fraction utilise pour le calcul de accroitre prob bris
#define FRACTION_PROB_BRIS 1 / 8

//tous les  unsigned int  sont identifi�es par  uint
typedef unsigned int uint;

/*D�finies dans l�interface, un type enum donne les quatre constantes
 qui repr�sentent les quatre �tats possibles d�une centrifugeuse dans la 
 simulation
*/
typedef enum { EN_BRIS, EN_ARRET, EN_ATTENTE, EN_FONCTION } t_etat;

typedef struct {
	//Une variable d��tat toujours �gale � une des constantes du type �num�r�
	t_etat etat;

	/*Un tableau de quatre compteurs de tocs totaux(uint), un pour chacun des 
	quatre �tats possibles*/
	uint tab_tocs[4];

	/*Un compteur (uint) qui donne le nombre de bris subis � date par la 
	centrifugeuse*/
	uint nb_bris;

	/*Une probabilit� de bris, variable r�elle dans l�intervalle [0, 1], qui 
	d�terminera si une centrifugeuse EN_FONCTION ou EN_ATTENTE qui subit un toc
	risque de briser et de passer � l��tat EN_BRIS.  Si la centrifugeuse ne 
	brise pas, sa probabilit� de bris s�accroit alors l�g�rement*/
	double prob_bris;

	/*
	Deux compteurs de tocs (uint), qui gardent le nombre total de tocs 
	EN_FONCTION et EN_ATTENTE depuis la derni�re r�paration de la 
	centrifugeuse.
	*/
	uint nb_tocs_en_fonction;
	uint nb_tocs_en_attente;

	/*Un compte � rebours (uint) qui est soit � 0 pour une centrifugeuse qui n�est
	pas EN_BRIS ou, pour une centrifugeuse EN_BRIS, sera �gale � soit � une 
	constante tr�s grande (INFINI) du module ou au nombre r�el de tocs restant 
	� sa r�paration.*/
	uint compte_rebours;

} t_centrifugeuse;



/*********************************************************
*********************D�claration des fonctions*************
*********************************************************/

/*init_centrigugeuse

Cette fonction retourne une centrifugeuse neuve � l��tat EN_ARRET.  
Sa probabilit� initiale de bris est donn�e par la constante PROB_BRIS_INIT.
*/
t_centrifugeuse init_centrifugeuse(void);


/*******************************************************************************/
/*set_en_fonction

Cette fonction permet de mettre une centrifugeuse EN_ATTENTE  dans l��tat
EN_FONCTION.

PARAMETRE : Prend les donn�es issu de la structure t_centrifugeuse, le param�tre 
			est de type t_centrifugeuse.

VALEUR DE RETOUR : 1 si r�ussi, 0 sinon.
*/
int set_en_fonction(t_centrifugeuse * ptr_cnt);


/*******************************************************************************/
/*set_en_attente

Cette fonction permet de mettre une centrifugeuse EN_ARRET ou EN_FONCTION 
dans l��tat  EN_ATTENTE.  

PARAMETRE : Prend les donn�es issu de la structure t_centrifugeuse, le param�tre
est de type t_centrifugeuse.

VALEUR DE RETOUR : 1 si r�ussi, 0 sinon.
*/
int set_en_attente(t_centrifugeuse * ptr_cnt);


/*******************************************************************************/
/*set_en_arret

Cette fonction permet de mettre une centrifugeuse EN_ATTENTE  ou EN_FONCTION 
dans l��tat  EN_ARRET. 

PARAMETRE : Prend les donn�es issu de la structure t_centrifugeuse, le param�tre
est de type t_centrifugeuse.

VALEUR DE RETOUR : 1 si r�ussi, 0 sinon .
*/
int set_en_arret(t_centrifugeuse * ptr_cnt);


/*******************************************************************************/
/*toc_centrifugeuse

Cette fonction d�clenche la dimination ou son changement en fonction de 
l'�tat de la centrifugeuse.

PARAMETRE : Prend les donn�es issu de la structure t_centrifugeuse, le param�tre
est de type t_centrifugeuse.

VALEUR DE RETOUR : retourne l��tat de la centrifugeuse.
*/
int  toc_centrifugeuse(t_centrifugeuse * ptr_cnt);


/*******************************************************************************/
/*set_temps_reparation

Cette fonction qui ne s�applique qu�� une centrifugeuse EN_BRIS dont le
compte � rebours est �gal � INFINI, elle fixe alors le compte � rebours
de la centrifugeuse au temps re�u en param�tre. 

PARAMETRE : - Prend les donn�es issu de la structure t_centrifugeuse, le param�tre
              est de type t_centrifugeuse.
			- temps, valeur qui va d�finir le nombre de toc n�cessaire � la 
			  la r�paration de la centrifugeuse.

VALEUR DE RETOUR : 1 si r�ussi, 0 sinon .
*/
int set_temps_reparation(t_centrifugeuse * ptr_cnt, uint temps);


/*******************************************************************************/
/*get_compteurs

Cette fonction va donner les compteurs d'une centrifugeuse :
- les quatre compteurs d��tat suivi du nombre de bris
- Les deux compteurs de tocs depuis la derni�re r�paration 
- Le compte � rebours.

PARAMETRE : - Prend les donn�es issu de la structure t_centrifugeuse, le param�tre
			  est de type t_centrifugeuse.
			- Le tableau de compteur ce cette centrifugeuse.


VALEUR DE RETOUR : Les huits compteurs de la centrifugeuse
*/
void get_compteurs(const t_centrifugeuse * ptr_cnt, uint * compteurs);


/*******************************************************************************/
/*get_prob_bris

Cette fonction va donner la probabilit� de bris de la centrifugeuse voulu.

PARAMETRE : - Prend les donn�es issu de la structure t_centrifugeuse, le param�tre
est de type t_centrifugeuse.

VALEUR DE RETOUR : La probabilit� de bris de la centrifugeuse (double)
*/
double get_prob_bris(const t_centrifugeuse * ptr_cnt);


/*******************************************************************************/
/*accroitre_prob

Cette fonction fait croitre la probabilit� de bris d�une centrifugeuse EN_ATTENTE
ou EN_FONCTION apr�s un toc sans bris.  

PARAMETRE : - Prend les donn�es issu de la structure t_centrifugeuse, le param�tre
est de type t_centrifugeuse.

HYPOTHESES:
-On suppose que l'etat est seulement soit EN_ATTENTE ou EN_FONCTION
-On suppose que la fonction se fait appele apres un
toc sans bris
*/
static void accroitre_prob(t_centrifugeuse * ptr_cnt);


/*******************************************************************************/
/*print_centrifugeuse

Cette fonction va nous donner la totalit� des donn�es d'une centrifugeuse 

PARAMETRE : - Prend les donn�es issu de la structure t_centrifugeuse, le param�tre
est de type t_centrifugeuse.

VALEUR DE RETOUR : Toutes les donn�es possible sur une centrifugeuse 
*/
void print_centrifugeuse(const t_centrifugeuse * ptr_cnt);


/*******************************************************************************/