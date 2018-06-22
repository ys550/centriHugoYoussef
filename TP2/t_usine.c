/*===========================================================*/
/* 	INF145 - t_usine                                         */
/*===========================================================*/

/*

Module :t_usine.c
Par    :
Date   :21/05/18

Ce ficher permet de voir précisement comment les fonctions définie dans
t_usine.h ont été programmé.
Pour comprendre l'utilité de ces fonctions, veuillez vous référer
au ficher t_usine.h

*/

//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 
//#define DEBUG

#include "centrifugeuse.h"
#include "ligne_centrifugeuse.h"
#include "t_usine.h"

// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>



/*********************************************************
*********************FONCTIONS****************************
*********************************************************/

int init_usine(t_usine * ptr_usine, uint nb_fonction){}

int  toc_usine(t_usine * ptr_usine){}

int entretien_usine(t_usine * ptr_usine){}

int get_nb_total_en_fonction(t_usine * ptr_usine){}

int get_nb_actuel_en_bris(t_usine * ptr_usine){}

int get_nb_toc(t_usine * ptr_usine){}

int get_nb_bris_total(t_usine * ptr_usine){}



/*********************************************************
*********************FONCTIONS STATIQUE*******************
*********************************************************/
