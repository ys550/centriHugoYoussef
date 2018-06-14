
#include <stdlib.h>
#include <stdio.h>

#define NB_BITS (sizeof(uint) * 8)

typedef struct {
	t_centrifugeuse tab_cnt[NB_BITS];

	uint nb_cnt_en_fonction;
	uint nb_cnt_en_bris;
	uint nb_cnt_en_attente;
	uint nb_cnt_en_arret;

	//(&) entre deux quelconques des 4 membres suivant sera toujours 0

	uint pos_cnt_fonction;
	uint pos_cnt_bris;
	uint pos_cnt_attente;
	uint pos_cnt_arret;

} t_ligne_centrifugeuse;

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

/***************** BITS2STRING ****************************/
/*
SOURCE: TP1 
PAR : H. Saulnier,  F. Henri, E. Thé
donne une représentation string ( chaine de caractère constante) aux
bits du nombre reçu.
PARAMETRE : nombre , un entier non signé
RETOUR : une chaine constante
SPECIFICATIONS :
Les bits sont donnés dans la string du moins significatif au plus
significatif, peu importe le signe du paramètre effectif
*/
const char* bits2string(unsigned int nombre);
