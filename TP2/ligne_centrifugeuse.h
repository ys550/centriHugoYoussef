
#include <stdlib.h>
#include <stdio.h>
#include "op_bits.h"

#define NBR_K_EN_ATTENTE 2

typedef struct {
	//Un tableau de centrifugeuse taille:32bits
	t_centrifugeuse tab_cnt[NB_BITS];

	/*
	Tableau de compteur pour chaque etat:
	tab_nb_cnt[0] = tab_nb_cnt[EN_BRIS] = compteur pour EN_BRIS 
	tab_nb_cnt[1] = tab_nb_cnt[EN_ARRET] = compteur pour EN_ARRET
	tab_nb_cnt[2] = tab_nb_cnt[EN_ATTENTE] = compteur pour EN_ATTENTE 
	tab_nb_cnt[3] = tab_nb_cnt[EN_FONCTION] =  compteur pour EN_FONCTION
	*/
	uint tab_nb_cnt[4];

	//(&) entre deux quelconques des 4 membres suivant sera toujours 0
	//Les positions
	uint config_fonction;
	uint config_bris;
	uint config_attente;
	uint config_arret;

} t_ligne_centrifugeuse;

//nb trop grand si depasse regle des 2/3




/*********************************************************
*********************D�finition des fonctions*************
*********************************************************/


/*Agit sur la ligne re�ue en r�f�rence, remplit son tableau de centrifugeuses
neuves (avec configuration de d�part du TP1), va mettre nb centrifugeuses
EN_FONCTION et le nombre constant EN_ATTENTE, tous les champs du struct doivent
�tre bien ajust�s.Elle retourne 1 pour succ�s ou 0 sinon (un nb trop grand).*/
int init_ligne_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, uint nb);

/*Ajoute si possible une centrifugeuse  EN_FONCTION dans la ligne.  Retour de 1
si r�ussi, 0 sinon (configuration impossible).*/
int ajouter_cnt(t_ligne_centrifugeuse * ptr_lig);

/*R�duit de un le nombre de  centrifugeuses EN_FONCTION dans la ligne.
Retour de 1 si r�ussi, 0 sinon (aucune EN_FONCTION).*/
int reduire_cnt(t_ligne_centrifugeuse * ptr_lig);

/*D�clenche la fonction toc_centrifugeuse() pour chacune des centrifugeuses du
tableau et r�agit correctement � tout changement d��tat d�une des
centrifugeuses.*/
void toc_ligne(t_ligne_centrifugeuse * ptr_lig);

/*Si la position est valide et si cette centrifugeuse du tableau n�est ni
EN_FONCTION ni EN_ATTENTE,  une  centrifugeuse neuve remplace celle � la
position donn�e dans le tableau. La fonction retourne une copie de la
centrifugeuse �limin�e, sinon une centrifugeuse dont tous les membres sont 0
est retourn�e.*/
t_centrifugeuse remplacer_cnt(t_ligne_centrifugeuse * ptr_lig, uint pos);

/*Qui retourne le train de bits de la ligne qui donne les positions des
centrifugeuses dans cet �tat. SPEC : Le second param�tre doit �tre une des
quatre constantes d��tat sinon le r�sultat obtenu n�a pas de sens.*/
uint get_en_etat(const t_ligne_centrifugeuse * ptr_lig, int etat);

/*Retourne une copie de la centrifugeuse � cette position dans le tableau. Elle
retourne une centrifugeuse dont tous les membres sont 0 si la position est
non-valide.*/
t_centrifugeuse get_centrifugeuse(const t_ligne_centrifugeuse * ptr_lig, uint  pos);

/*Cette fonction du module permute  les centrifugeuses aux positions
pos1 et pos2 du tableau et dans les trains de bits correspondants si leurs �tats
diff�rent.*/
void permuter_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, uint pos1, uint pos2);

/*Fonction d�affichage des lignes de centrifugeuses*/
void print_ligne_centrifugeuse(const t_ligne_centrifugeuse * ptr_lig);

/*Donne la chaine de bits correspondant � l�tat demander (EN_BRIS, EN_ARRET,
EN_ATTENTE, EN_FONCTION)*/
static void set_config(t_ligne_centrifugeuse * ptr_lig, int etat, uint config);

/*fonction configuration_valide du TP1*/
static unsigned short configuration_valide(uint valeur);

/*Initialise toute les valeurs (compte_rebours,prob_bris,en bris et
initialisation des centrifugeuses)*/
static t_centrifugeuse centrifugeuse_membres_0(void);
