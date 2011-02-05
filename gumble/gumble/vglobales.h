#ifndef VGLOBALES_H
#define VGLOBALES_H

#include <windows.h>
#include "hge.h"
#include <hgeresource.h>
#include <hgesprite.h>
#include <hgeanim.h>
#include "menuitem.h"
#include <math.h>
#include "hgefont.h"
#include "hgegui.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <hgeparticle.h>
#include "hgeguictrls.h"

#include <math.h>

// Particules
hgeParticleSystemInfo particle;
hgeParticleSystemInfo particle_bulles;
hgeParticleManager *particleManager;

HGE *hge = 0;

// Permet de créer un flux pour gérer la music
HSTREAM myMusic;
HSTREAM myMusic_menu; // Music du menu
HSTREAM l4; //music level 4
HSTREAM myMusic_fin; // Music du menu


// Channel pour gere plusieurs flux musicaux
HCHANNEL chan[2];

hgeResourceManager* Res;
hgeSprite* bgSprite;
hgeSprite* game_over;
hgeSprite* you_win;
hgeSprite* canon_img;
hgeSprite* bgfin;

// Pointeur pour la police d'écriture
hgeFont* font1;

int id_menu = -1; // Pour gérer les différents écrans de jeux
char* pMap = NULL; // pointeur sur la desctiption de la map
int* Tboule_count; // Pointeur pour les boules
int sizeX, sizeY;
float fScale =27;
const int xMap = 245; // abscisse de la plus basse ligne pour afficher les boules
const int yMap = 385; // ordonnée de la plus basse ligne pour afficher les boules
const float bouleSizeX = 37; // taille de la boule
const float bouleSizeY = 31;
float timeDown = 3000; // temps avant de faire tomber les boules(secondes)
float timeCpt = 0; // compteur de temps
int swapPair = 0; // variables utile pour déterminée si la ligne a besoin d'etre décalée
bool isDowning = false; // les boules sont en train de descendre ?
float animDowning = 0; // utile pour faire une sorte d'animation lors de la descente des boules
float speedY = (float)0.05; // vitesse de la boule du joueur
float speedX = (float)0.1; // inclinaison de la boule du joueur
bool loose = false; // Permet de gérer si la partie est perdu
bool win = false;
float rot = 0.0; // Permet la rotation du canon
float mouseX, mouseY; // Coordonnées de la souris
float canonLocX = 398, canonLocY = 498; // Coordonnées pour le canon
bool lunched = false; // Permet de savoir si la boule courante a été lancé ou non
int alea_c = 1; // Chiffre qui prendra une valeur aléatoire entre [1 - 7] qui représente le nombre de couleur des boules
int alea_n = 4; // Chiffre qui prendra une valeur aléatoire entre [1 - 7] qui représente le nombre de couleur des boules
float tglobal =0;
bool blunched_boule = false; // Pour que la boule grimpe tte seul ! 
bool first = true; // Pour la 1er génération de nombre aléatoire
bool firstTimeMenu = true; // Pour le premier passage au menu
bool ttest = true;
//boolean pour stopper le temps
bool stop_time = false;
bool premier = true;
//Compteur pour supprimer les boules si plus de 2 sont accolées
int cptDestroy = 0;
bool tabToDestroy[88];

// pour faire descendre les boules non suspendus
bool noSuspendedIsDowning = false;
int noSuspendedAnimDowning = 0;
bool noSuspendedTab[80];

// Variable pour calculer le score
int score = 0;

bool firstTimeMenufin = true;
bool musicmenu = true;
// Pour afficher le tire canon (bonus)
int bonus = 0;

// Variables pour gérer les boules 'courante' et 'suivante'
	// Boule courante
	char coul_bcourante;
	float posX_bcourante = 0;
	float posY_bcourante = 0;
	
	float posX_depart = 380; // Coordonnées de la boule de départ dans le canon
	float posY_depart = 480;

	// position boule suivante
	float bnext_X = 78;
	float bnext_Y = 445;
	
	// Boule suivante
	char coul_bsuivante;
	float ttime=0; // Permet de gérer le compteur de temps

//test
float posboulex = 240+(320/2)-(bouleSizeX/2);
float posbouley = yMap-5;
bool jesus = true;
bool premierelignepaire = false;
//test

// Sprite pour le bouton du menu
hgeAnimation* bt_menu; // bouton menu sur l'espace de jeux

// Background intro
hgeSprite* bgg; // Sprite pour le fond de l'intro
// Back level
hgeSprite* bg4;

// Sprite pour les boules
hgeAnimation* b_rouge; //rouge
hgeAnimation* b_vert; // vert
hgeAnimation* b_bleu; //bleu
hgeAnimation* b_orange; //orange
hgeAnimation* b_jaune; //jaune
hgeAnimation* b_violet; //violet
hgeAnimation* b_gris; //gris

// frog animation
hgeAnimation* frog;

// numbers animation
hgeAnimation* anumb;

// Some resource handles
HEFFECT				snd;
HTEXTURE			tex;

HEFFECT sgameover;
HEFFECT	swin;
HEFFECT letire;
HEFFECT explosion;

// Pointeurs pour HGE object
hgeGUI				*gui;
hgeFont				*fnt;
hgeSprite			*spr;

hgeGUIButton		*btn;


int lastid = 0; // pour gérer le menu

// prototype de la mort 
bool menu();
bool game();
bool instruction();
bool credit();
bool multiplayer();
bool smenu();
bool fin();

float rotTd = 0; // variable temporaire pour la direction du tir
bool game_int();
float timeBegin;
int niveau = 0;// niveau du joueur

#endif

