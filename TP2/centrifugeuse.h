/****************************************
*******INTERFACE DE centrifugeuse********
****************************************/

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/
/*valeur initiale de prob de bris. Incremente legerement si centri ne se brise
 pas*/
#define PROB_BRIS_INIT 0.0001
//une constante très grande pour represente INFINI (valeur max d'un uint)
#define INFINI 0xFFFFFFFF
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

t_centrifugeuse init_centrifugeuse(void);
int set_en_fonction(t_centrifugeuse * ptr_cnt);
int set_en_attente(t_centrifugeuse * ptr_cnt);
int set_en_arret(t_centrifugeuse * ptr_cnt);
int  toc_centrifugeuse(t_centrifugeuse * ptr_cnt);
int set_temps_reparation(t_centrifugeuse * ptr_cnt, uint temps);
void get_compteurs(const t_centrifugeuse * ptr_cnt, uint * compteurs);
double get_prob_bris(const t_centrifugeuse * ptr_cnt);
static void accroitre_prob(t_centrifugeuse * ptr_cnt);
void print_centrifugeuse(const t_centrifugeuse * ptr_cnt);