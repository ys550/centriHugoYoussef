
#include <stdlib.h>
#include <stdio.h>
#include "op_bits.h"

typedef struct {
	t_centrifugeuse tab_cnt[NB_BITS];

	/*
	Tableau de comteur pour chaque etat:
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
int init_ligne_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, uint nb);
int ajouter_cnt(t_ligne_centrifugeuse *ptr_lig);
int reduire_cnt(t_ligne_centrifugeuse *ptr_lig);
void toc_ligne(t_ligne_centrifugeuse *ptr_lig);
t_centrifugeuse remplacer_cnt(t_ligne_centrifugeuse *ptr_lig, uint pos);
uint get_en_etat(const t_ligne_centrifugeuse * ptr_lig, int etat);
t_centrifugeuse get_centrifugeuse(const t_ligne_centrifugeuse *ptr_lig, uint  pos);
static  void permuter_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, uint pos1, uint pos2);
void print_ligne_centrifugeuse(void);
unsigned short configuration_valide(uint valeur, unsigned short nb_bits_actifs);
