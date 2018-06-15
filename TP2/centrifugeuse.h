/****************************************
*******INTERFACE DE centrifugeuse********
****************************************/

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/
/*valeur initiale de prob de bris. Incremente legerement si centri ne se brise
 pas*/
#define PROB_BRIS_INIT 0.0001
//une constante tr�s grande pour represente INFINI (valeur max d'un uint)
#define INFINI 0xFFFFFFFF
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