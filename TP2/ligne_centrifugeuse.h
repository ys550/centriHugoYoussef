/*
Module : ligne_centrifugeuse.h
Par    : Youssef Soliman, Hugo Belin
Date   :20/06/18

-Ce module � pour but de repr�senter sur 32 bits les �tats possibles des 
 centrifugeuse et respectant les contraintes de maintenance et de s�curit� qui
 oblige � ne pas avoir plus de 2 centrifugeuse fonctionelle voisine.
-Permet de recevoir les informations d'une centrifugeuse issu du module 
 centrifugeuse, de faire des actions (reduire, ajouter, remplacer,r�parer,initialiser
 permuter) des centrifugeuses.
 - Ce ficher � pour but de cr�er les constantes, les structures, les �num�rations 
et les d�finitions des fonctions n�c�ssaire pour la representation et leurs actions
en chaine de bits des centrifugeuses.

*/


#include <stdlib.h>
#include <stdio.h>
#include "op_bits.h"

//pour l'affichage lors de tests du mandat 2(0 : sans affichage 1: avec)
#define DEBUG_MANDAT2 1

//le nb initiale de cnt en attente
#define NBR_K_EN_ATTENTE 2

//pour le test toc ligne
#define NB_CENT_DEPART 26

//pour la regle des 2 / 3
#define REGLE_DEUX_TIERS 2.0 / 3.0

//le max des cent en fonction sur une ligne = 22
#define NB_FONC_MAX (int)ceil(NB_BITS * REGLE_DEUX_TIERS)


typedef struct {
	//Un tableau de centrifugeuse taille:32bits
	t_centrifugeuse tab_cnt[NB_BITS];

	/*
	Tableau de compteur pour chaque etat:
	tab_nb_cnt[0] OU tab_nb_cnt[EN_BRIS] : compteur pour EN_BRIS 
	tab_nb_cnt[1] OU tab_nb_cnt[EN_ARRET] : compteur pour EN_ARRET
	tab_nb_cnt[2] OU tab_nb_cnt[EN_ATTENTE] : compteur pour EN_ATTENTE 
	tab_nb_cnt[3] OU tab_nb_cnt[EN_FONCTION] :  compteur pour EN_FONCTION
	*/
	uint tab_nb_cnt[4];

	//(&) entre deux quelconques des 4 membres suivant sera toujours 0
	//Les positions
	uint config_fonction;
	uint config_bris;
	uint config_attente;
	uint config_arret;

	//un entier qui compte le nombre de bris subis par toutes les centrifugeuses
	int  nb_bris_ligne;

} t_ligne_centrifugeuse;

/********************************************************************/
/*						DECLARATIONS DE FONCTIONS					*/
/********************************************************************/


/*******************************************************************************/
/*init_ligne_centrifugeuse

Cette fonction agit sur la ligne re�ue en r�f�rence, remplit son tableau de 
centrifugeuses neuves (avec configuration de d�part du TP1), va mettre nb 
centrifugeuses EN_FONCTION et le nombre constant EN_ATTENTE,

PARAMETRE : - ptr_lig: Prend les donn�es issu de la structure t_ligne_centrifugeuse, le param�tre
              est de type t_ligne_centrifugeuse. (t_ligne_centrifugeuse)
			- nb : nombre de centrifugeuse en fonction (uint) 

VALEUR DE RETOUR : Elle retourne 1 pour succ�s ou 0 sinon (un nb trop grand).
*/
int init_ligne_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, uint nb);



/*******************************************************************************/
/*ajouter_cnt

Cette fonction ajoute si possible une centrifugeuse  EN_FONCTION dans la ligne.

PARAMETRE : - Prend les donn�es issu de la structure t_ligne_centrifugeuse, le param�tre
est de type t_ligne_centrifugeuse.

VALEUR DE RETOUR : Elle retourne 1 pour succ�s ou 0 sinon.
*/
int ajouter_cnt(t_ligne_centrifugeuse * ptr_lig);



/*******************************************************************************/
/*reduire_cnt

Cette fonction r�duit de un le nombre de  centrifugeuses EN_FONCTION 
dans la ligne.

PARAMETRE : - Prend les donn�es issu de la structure t_ligne_centrifugeuse,
              le param�tre est de type t_ligne_centrifugeuse.

VALEUR DE RETOUR : Elle retourne 1 pour succ�s ou 0 sinon.
*/
int reduire_cnt(t_ligne_centrifugeuse * ptr_lig);



/*******************************************************************************/
/*toc_ligne

Cette fonction d�clenche la fonction toc_centrifugeuse() pour
chacune des centrifugeuses du tableau et r�agit correctement 
� tout changement d��tat d�une des centrifugeuses.

PARAMETRE : - Prend les donn�es issu de la structure t_ligne_centrifugeuse,
le param�tre est de type t_ligne_centrifugeuse.
*/
void toc_ligne(t_ligne_centrifugeuse * ptr_lig, int temps);



/*******************************************************************************/
/*remplacer_cnt

Si la position est valide et si cette centrifugeuse du tableau n�est ni
EN_FONCTION ni EN_ATTENTE,  une  centrifugeuse neuve remplace celle � la
position donn�e dans le tableau.

PARAMETRE : - Prend les donn�es issu de la structure t_ligne_centrifugeuse,
le param�tre est de type t_ligne_centrifugeuse.
			- pos : la position de la centrifigeuse dans la chaine de bits <32 

VALEUR DE RETOUR : retourne une copie de la centrifugeuse �limin�e, 
                   sinon une centrifugeuse dont tous les membres sont 0 est retourn�e.
*/
t_centrifugeuse remplacer_cnt(t_ligne_centrifugeuse * ptr_lig, uint pos);



/*******************************************************************************/
/*get_en_etat

La fonction retourne le train de bits de la ligne qui donne les positions des
centrifugeuses dans l'�tat choisi 

PARAMETRE : - Prend les donn�es issu de la structure t_ligne_centrifugeuse,
le param�tre est de type t_ligne_centrifugeuse.
- �tat : Le second param�tre doit �tre une des quatre constantes

VALEUR DE RETOUR : retourne la chaine de bit d�fini de l'�tat
*/
uint get_en_etat(const t_ligne_centrifugeuse * ptr_lig, int etat);



/*******************************************************************************/
/*get_centrifugeuse

La fonction retourne une copie de la centrifugeuse � cette position 
dans le tableau. 

PARAMETRE : - Prend les donn�es issu de la structure t_ligne_centrifugeuse,
le param�tre est de type t_ligne_centrifugeuse.
- pos : la position de la centrifigeuse dans la chaine de bits <32

VALEUR DE RETOUR : Elle retourne une centrifugeuse dont tous les membres
                   sont 0 si la position est non-valide.
*/
t_centrifugeuse get_centrifugeuse(const t_ligne_centrifugeuse * ptr_lig, uint  pos);



/*******************************************************************************/
/*permuter_centrifugeuse

La fonction  permute  les centrifugeuses aux positions
pos1 et pos2 du tableau et dans les trains de bits 
correspondants si leurs �tats diff�rent.

PARAMETRE : - Prend les donn�es issu de la structure t_ligne_centrifugeuse,
le param�tre est de type t_ligne_centrifugeuse.
- pos1 et pos2 : la position de la centrifigeuse dans la chaine de bits <32

VALEUR DE RETOUR : Elle retourne une centrifugeuse dont tous les membres
sont 0 si la position est non-valide.
*/
void permuter_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, uint pos1, uint pos2);


/*******************************************************************************/
/*print_ligne_centrifugeuse

Fonction d�affichage des lignes de centrifugeuses

PARAMETRE : - Prend les donn�es issu de la structure t_ligne_centrifugeuse,
le param�tre est de type t_ligne_centrifugeuse.

VALEUR DE RETOUR : affichage des chaines de bits de tous les �tats 
*/
void print_ligne_centrifugeuse(const t_ligne_centrifugeuse * ptr_lig);



/*******************************************************************************/
/*set_config

Donne la chaine de bits correspondant � l�tat demander (EN_BRIS, EN_ARRET,
EN_ATTENTE, EN_FONCTION)

PARAMETRE : - Prend les donn�es issu de la structure t_ligne_centrifugeuse,
le param�tre est de type t_ligne_centrifugeuse.
			- L'�tat voulu (EN_BRIS, EN_ARRET, EN_ATTENTE, EN_FONCTION)


VALEUR DE RETOUR : affichage du chaine de l'�tat voulu 
*/
static void set_config(t_ligne_centrifugeuse * ptr_lig, int etat, uint config);


/*******************************************************************************/
/*configuration_valide

fonction configuration_valide du TP1

*/
static unsigned short configuration_valide(uint valeur);


/*******************************************************************************/
/*t_centrifugeuse

La fonction priv�e du module permute  les centrifugeuses aux positions
pos1 et pos2 du tableau et dans les trains de bits correspondants si 
leurs �tats diff�rent.

*/
static t_centrifugeuse centrifugeuse_membres_0(void);

/*******************************************************************************/
/*get_nb_bris_lig
fonction qui retourne la valeur de nb_bris_ligne.
*/
int  get_nb_bris_lig(const t_ligne_centrifugeuse * ptr_lig);


/*******************************************************************************/