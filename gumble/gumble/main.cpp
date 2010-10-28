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


HGE *hge = 0;

// Permet de créer un flux pour gérer la music
HSTREAM myMusic;

// Channel pour gere plusieurs flux musicaux
HCHANNEL chan[2];

hgeResourceManager* Res;
hgeSprite* bgSprite;
hgeSprite* game_over;
hgeSprite* you_win;

// Pointeur pour la police d'écriture
hgeFont* font1;

char* pMap = NULL; // pointeur sur la desctiption de la map
int sizeX, sizeY;
float fScale =27;
const int xMap = 245; // abscisse de la plus basse ligne pour afficher les boules
const int yMap = 385; // ordonnée de la plus basse ligne pour afficher les boules
const float bouleSizeX = 37; // taille de la boule
const float bouleSizeY = 31;
float timeDown = 2; // temps avant de faire tomber les boules(secondes)
float timeCpt = 0; // compteur de temps
int swapPair = 0; // variables utile pour déterminée si la ligne a besoin d'etre décalée
bool isDowning = false; // les boules sont en train de descendre ?
float animDowning = 1; // utile pour faire une sorte d'animation lors de la descente des boules
float speedY = 0.05; // vitesse de la boule du joueur
float speedX = 0.1; // inclinaison de la boule du joueur
bool loose = false; // Permet de gérer si la partie est perdu

float mouseX, mouseY; // Coordonnées de la souris

bool lunched = true; // Permet de savoir si la boule courante a été lancé ou non
int alea = 0; // Chiffre qui prendra une valeur aléatoire entre [1 - 7] qui représente le nombre de couleur des boules

//test
float posboulex = 240+(320/2)-(bouleSizeX/2);
float posbouley = yMap-5;
bool jesus = true;
bool premierelignepaire = false;
//test

// Sprite pour le bouton du menu
hgeAnimation* bt_menu; // bouton menu sur l'espace de jeux

// Sprite pour les boules
hgeAnimation* b_rouge; //rouge
hgeAnimation* b_vert; // vert
hgeAnimation* b_bleu; //bleu
hgeAnimation* b_orange; //orange
hgeAnimation* b_jaune; //jaune
hgeAnimation* b_violet; //violet
hgeAnimation* b_gris; //gris


// Some resource handles
//HEFFECT				snd;
HTEXTURE			tex;

// Pointeurs pour HGE object
hgeGUI				*gui;
//hgeFont				*fnt;
hgeSprite			*spr;

// Fonction permettant de générer un nombre aléatoire entre 2 bornes [x-y]
int my_rand ()
{
	hge->Random_Seed(0);  //sets the seed to the current time
	return (hge->Random_Int(1, 7));
}


int calculPosX(int x)
{
	int mapX = 1;
	while(bouleSizeX*mapX < (x-xMap))
		mapX++;
	return mapX;
}

int calculPosY(int y)
{
	/*int mapY = 1; 
	while((350/11)*mapY < (y-72))
		mapY++;
	mapY = 11-mapY;
	return mapY;
	*/
	//int mapY = 1;
	int mapY = 11;
	//while(mapY*bouleSizeY < y - 72)
	int lol = (yMap+bouleSizeX)-(11*bouleSizeY);
	while(mapY*bouleSizeY > y - ((yMap+bouleSizeY)-(11*bouleSizeY)))
		mapY--;
		//mapY++;
	mapY = 11-mapY;
	int jesus = 465456;
	return mapY;
}

bool Collision(int newX, int newY)
{
	if(newY > yMap + bouleSizeX/2)
		return false;

	//!\\ MERCI DE NE PAS TOUCHER A MA MERDE, CE N'EST PAS FONCTIONNEL MAIS JE SUIS SUR LA BONNE VOIE

	int mapY = calculPosY(newY);
	bool yPaire = premierelignepaire;
	for(int cpt = 1;cpt < mapY;cpt++)
		yPaire = !yPaire;
	int mapX;
	bool collision = false;
	//mapY -= 1;
	int decalage = 0;
	int xcoll = 0;
	int ycoll = 0;
	if(yPaire)
	{
		//decalage = bouleSizeX/2;
		mapX =  calculPosX(newX-bouleSizeX/2);
		
		if(mapX < 8 && mapY < 11)
		if(pMap[(mapX)+((mapY)*8)] != 'x')
		{
		xcoll = xMap+    ((mapX)*bouleSizeX)    +(bouleSizeX/2)   +decalage;
		ycoll = yMap-         ((mapY-1)*bouleSizeY)      -(bouleSizeX/2);
		b_orange->RenderStretch(xcoll-2, ycoll-2, xcoll+2, ycoll+2);

		int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
		if(detect < bouleSizeX*bouleSizeX)
			collision = true;
		}
		if(mapX < 8 && mapY > 1)
		if(pMap[(mapX)+((mapY-2)*8)] != 'x')
		{
		xcoll = xMap+    ((mapX)*bouleSizeX)    +(bouleSizeX/2)   +decalage;
		ycoll = yMap-         ((mapY-3)*bouleSizeY)      -(bouleSizeX/2);
		b_orange->RenderStretch(xcoll-2, ycoll-2, xcoll+2, ycoll+2);

		int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
		if(detect < bouleSizeX*bouleSizeX)
			collision = true;
		}
	}
	else
	{
		mapX =  calculPosX(newX);
		decalage = bouleSizeX/2;

		if(mapX > 1 && mapY < 11)
		if(pMap[(mapX-2)+((mapY)*8)] != 'x')
		{
		xcoll = xMap+    ((mapX-2)*bouleSizeX)    +(bouleSizeX/2)   +decalage;
		ycoll = yMap-         ((mapY-1)*bouleSizeY)      -(bouleSizeX/2);
		b_orange->RenderStretch(xcoll-2, ycoll-2, xcoll+2, ycoll+2);

		int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
		if(detect < bouleSizeX*bouleSizeX)
			collision = true;
		}

		if(mapX > 1 && mapY > 1)
		if(pMap[(mapX-2)+((mapY-2)*8)] != 'x')
		{
		xcoll = xMap+    ((mapX-2)*bouleSizeX)    +(bouleSizeX/2)   +decalage;
		ycoll = yMap-         ((mapY-3)*bouleSizeY)      -(bouleSizeX/2);
		b_orange->RenderStretch(xcoll-2, ycoll-2, xcoll+2, ycoll+2);

		int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
		if(detect < bouleSizeX*bouleSizeX)
			collision = true;
		}

	}

	if(pMap[(mapX-1)+((mapY-1)*8)] != 'x')
	{
		collision = true;
	}
	if(yPaire)
		decalage = bouleSizeX/2;
	else
		decalage = 0;
	if(mapX > 1)
	if(pMap[(mapX-2)+((mapY-1)*8)] != 'x')
	{
		xcoll = xMap+    ((mapX-2)*bouleSizeX)    +(bouleSizeX/2)   +decalage;
		ycoll = yMap-         ((mapY-2)*bouleSizeY)      -(bouleSizeX/2);
		b_orange->RenderStretch(xcoll-2, ycoll-2, xcoll+2, ycoll+2);

		int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
		if(detect < bouleSizeX*bouleSizeX)
			collision = true;
	}
	if(mapX < 8)
	if(pMap[(mapX)+((mapY-1)*8)] != 'x')
	{
		xcoll = xMap+    ((mapX)*bouleSizeX)    +(bouleSizeX/2)   +decalage;
		ycoll = yMap-         ((mapY-2)*bouleSizeY)      -(bouleSizeX/2);
		b_orange->RenderStretch(xcoll-2, ycoll-2, xcoll+2, ycoll+2);

		int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
		if(detect < bouleSizeX*bouleSizeX)
			collision = true;
	}
	if(!yPaire)
		decalage = bouleSizeX/2;
	else
		decalage = 0;
	if(mapY < 11)
	if(pMap[(mapX-1)+((mapY)*8)] != 'x')
	{
		xcoll = xMap+    ((mapX-1)*bouleSizeX)    +(bouleSizeX/2)   +decalage;
		ycoll = yMap-         ((mapY-1)*bouleSizeY)      -(bouleSizeX/2);
		b_orange->RenderStretch(xcoll-2, ycoll-2, xcoll+2, ycoll+2);

		int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
		if(detect < bouleSizeX*bouleSizeX)
			collision = true;
	}
	if(mapY > 1)
	if(pMap[(mapX-1)+((mapY-2)*8)] != 'x')
	{
		xcoll = xMap+    ((mapX-1)*bouleSizeX)    +(bouleSizeX/2)   +decalage;
		ycoll = yMap-         ((mapY-3)*bouleSizeY)      -(bouleSizeX/2);
		b_orange->RenderStretch(xcoll-2, ycoll-2, xcoll+2, ycoll+2);

		int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
		if(detect < bouleSizeX*bouleSizeX)
			collision = true;
	}

	

	return collision;
}

bool FrameFunc() // Fonction appelée à chaque image
{
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;
	int id;
	  static int lastid=0;
	  float dt=hge->Timer_GetDelta();

	  id=gui->Update(dt);
	  if(id == -1)
	  {
		switch(lastid)
		{
		  case 1:
		  case 2:
		  case 3:
		  case 4:
			gui->SetFocus(1);
			gui->Enter();
			break;
		  case 5: return true;
		}
	  }
	  else if(id) { lastid=id; gui->Leave(); }
  
 return false;
}

bool RenderFunc()
{
	float dt=hge->Timer_GetDelta();  //get the time since the last call to FrameFunc
	timeCpt += dt; // on additionne les temps entre les images
	if(timeCpt > timeDown) // si ce compteur est supérieur aux temps définis pour faire tomber les boules :
	{													// on actualise pMap pour lui enlever une ligne en bas (la ligne la plus basse disparait pour faire descendre les autres)
		if(!isDowning) // les boules ne sont pas en train de descendre
		{
			sizeY -= 1; // nouveau nombre de ligne (on supprime celle en bas)
			char* pMapTmp = new char[(sizeX*sizeY)];		// pour cela, on créé un nouveau tableau		
			for(int cpt = 0; cpt < (sizeX*sizeY);cpt++)   // puis on recopie les valeurs de pMap en enlevant la premiere ligne
			{
				pMapTmp[cpt] = pMap[cpt+sizeX];
			}
			char* toFree = pMap;
			pMap = pMapTmp;
			free(toFree); // on free l'ancien tableau
			timeCpt = 0; // on remet le compteur de temps à 0;
			swapPair = (swapPair+1)%2; // on modifie la variable a chaque descente de boules (elle prend soit 1 soit 0)
			isDowning = true;
		}
	}

	// Passe lunched à vrai (pour boule lancée) si espace pressé
	if(hge->Input_GetKey()==HGEK_SPACE) lunched=true;  
	
	// Permet de récupérer les coordonnées de la souris
	hge->Input_GetMousePos(&mouseX, &mouseY);
	

	//Génerer un nombre aléatoire si la variable 'lunched' est à vrai
	if(lunched==true)
	{
		alea = my_rand(); // Génére un nombre entre 1 et 7 compris
		lunched = false; // on passe lunched à faux tant que la boule n'est pas lancée
	}

	
	b_rouge->Update(dt);  //update the animation
	b_vert->Update(dt);
	b_bleu->Update(dt);
	b_orange->Update(dt);
	b_jaune->Update(dt);
	b_violet->Update(dt);
	b_gris->Update(dt);
	//bt_menu->Update(dt);


	// Render graphics
	hge->Gfx_BeginScene();
	bgSprite->Render(0, 0);
	bt_menu->Render(640,390);
	gui->Render(); // Permet de lancer le GUI et donc d'utiliser d'afficher le curseur.png définit avant
	for(int y=0; y<sizeY; ++y) // affiche les boules et leur descente
	{
		float posY =y*bouleSizeY;
		for(int x=0; x<sizeX; ++x)
		{
			if(y < 11)
			{
				if(y == 0 && x == 0 && isDowning) // si les boules sont en train de descendre, on leur attribut pour chaque image une position décalée de 0.05 px (descente petit à petit)
					animDowning += 0.05;


				float decalage = 0.0;       // si la ligne est paire, on la décale
				if((y+swapPair)%2 == 0)
				{
					decalage = bouleSizeX/2;
					if(y == 0)
						premierelignepaire = true;
					if(y == 1)
						premierelignepaire = false;
				}
				/*
				On utilise swapPair pour regarder si on doit décaler ou non la ligne
				Exemple : premieres secondes du jeu, la ligne 5 est impaire et la ligne 6 est paire
				On affiche donc la ligne 26 décalée à droite par rapport à la ligne 5 (selon les modalités du jeu)

				Ensuite, durant la deuxième phase (les boules descendent d'un cran), la ligne 5 devient la ligne 4 (donc paire) et la ligne 6 devient la ligne 5 (donc impaire)
				on doit donc dire à l'affichage de ne plus décaler les lignes paires, mais impaires pour que les lignes restent toujours au même endroit en ordonnées.
				La variable swapPair sert alterner le modulo 2 du numéro de ligne pour que celui ci reste contant selon la ligne.
				*/

				// Nouvelles positions pour l'affichages des boules
				float x1 = xMap+((x)*bouleSizeX+decalage);
				float y1 = yMap-((y-1)*bouleSizeY);
				float x2 = xMap+bouleSizeX+((x)*bouleSizeX+decalage);
				float y2 = yMap-bouleSizeX-((y-1)*bouleSizeY);
				if(isDowning && loose==false)
				{	
					if(animDowning < bouleSizeX)
					{
						// Modification des coordonnées des boules si elles sont en train de descendre (descente progressive sur les y)
						y1 -= (bouleSizeX-animDowning);
						y2 -= (bouleSizeX-animDowning);
					}
					else
					{
						
						for(int i=0; i<7; i++)
						{
							if(pMap[i] != 'x')
							{
								loose = true;
							}
						}

						animDowning = 1;
						isDowning = false;
						timeCpt = 0;
					}
				}
					
				float posX =x*bouleSizeX;

				int index =y*sizeX+x;
				
				if(isDowning && y == 10)
				{	
				}
				else
				{
					switch (pMap[index])
					{
						case 'r': {
							  b_rouge->RenderStretch(x1, y1, x2, y2);break;
						}
						case 'v': {
							  b_vert->RenderStretch(x1, y1, x2, y2);break;
						}
						case 'b': {
							  b_bleu->RenderStretch(x1, y1, x2, y2);break;
						}
						case 'o': {
							  b_orange->RenderStretch(x1, y1, x2, y2);break;
						}
						case 'g': {
							  b_gris->RenderStretch(x1, y1, x2, y2);break;
						}
						case 'j': {
							  b_jaune->RenderStretch(x1, y1, x2, y2);break;
						}
						case 'w': { // pour représenter le violet car la lettre v est déja utilisé pour le vert
							  b_violet->RenderStretch(x1, y1, x2, y2);break;
						}
				   }
				}
			}
		}
	}	
			
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			float time = 0 ;
			time = (int) hge->Timer_GetTime();
			//time += hge->Timer_GetDelta();
			font1->SetColor(ARGB(255,255,0,0));  //set color of text to black
			font1->printf(660,200, HGETEXT_LEFT, "%f", time);
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	// Affiche le message GameOver 
	if (loose == true)
	{
		game_over->Render(262,250);
	}

	/* Cette partie est en construction cela va permettre de faire des tests pour générer les boules aléatoirement.*/
	/* Bon Je sais c'est déguellasse car je code en dur les coordonnées :p */
	switch (alea)
	{
		case 1: {
			  b_rouge->RenderStretch(380,480,380+bouleSizeX,480+bouleSizeX);break;
		}
		case 2: {
			  b_vert->RenderStretch(380,480,380+bouleSizeX,480+bouleSizeX);break;
		}
		case 3: {
			  b_bleu->RenderStretch(380,480,380+bouleSizeX,480+bouleSizeX);break;
		}
		case 4: {
			  b_orange->RenderStretch(380,480,380+bouleSizeX,480+bouleSizeX);break;
		}
		case 5: {
			  b_gris->RenderStretch(380,480,380+bouleSizeX,480+bouleSizeX);break;
		}
		case 6: {
			  b_jaune->RenderStretch(380,480,380+bouleSizeX,480+bouleSizeX);break;
		}
		case 7: {
			  b_violet->RenderStretch(380,480,380+bouleSizeX,480+bouleSizeX);break;
		}
	}
	
	
	// tests tout caca
	if(jesus)
	{
		if(hge->Input_GetKeyState(HGEK_UP))
			posbouley -= 0.1;
		if(hge->Input_GetKeyState(HGEK_DOWN))
			posbouley += 0.1;
		if(hge->Input_GetKeyState(HGEK_LEFT))
		{
			if((posboulex -0.1)>xMap)
				posboulex -= 0.1;
		}
		if(hge->Input_GetKeyState(HGEK_RIGHT))
		{
			if((posboulex+bouleSizeX+ 0.1)<xMap+(8.5*bouleSizeX))
				posboulex += 0.1;
		}
		
		if(isDowning)
		{
			b_bleu->RenderStretch(posboulex-speedX, posbouley+speedY, posboulex+bouleSizeX-speedX, posbouley+bouleSizeX+speedY);
		}
		else
		{
			//bool test = Collision(posboulex, posbouley); // methode 1 
			bool test = Collision(posboulex+(bouleSizeX/2), posbouley+(bouleSizeX/2)); // methode 2 (en test)
			if(!test)
			{
				b_bleu->RenderStretch(posboulex, posbouley, posboulex+bouleSizeX, posbouley+bouleSizeX);
				/*
				if(posboulex <= 240 || posboulex+bouleSizeX >= 240+320)
					speedX = -speedX;
				b_bleu->RenderStretch(posboulex, posbouley, posboulex+bouleSizeX, posbouley+bouleSizeX);
				posbouley -= speedY;
				posboulex += speedX;*/
			}
			else
			{
				b_rouge->RenderStretch(posboulex, posbouley, posboulex+bouleSizeX, posbouley+bouleSizeX);
				/*
				int mapX = calculPosX(posboulex-speedX); 
				int mapY = calculPosY(posbouley+speedY);
				int index = mapY*sizeX+mapX;
				pMap[index] = 'b';
				jesus = false;
				*/
			}
		}
	}
	
	hge->Gfx_EndScene();
	return false;
}

void LoadMap()
{
	FILE* f = NULL;
	f = fopen("../Debug/map3.txt", "rb"); // ouverture du fichier map
	if(f == NULL)
		return;

	char line[512];
	fgets(line, sizeof(line),f);
	sizeX  =atoi(line); // nombre de colones
	fgets(line, sizeof(line),f);
	sizeY = atoi(line); // nombres de lignes

	//!\\ La première ligne de la map est la ligne se trouvant le plus en bas sur le jeu. La dernière ligne de la map représente donc la ligne de boules le plus en haut possible

	pMap = new char[sizeX*sizeY]; // la pointeur sur la map réserve la taille de la map en mémoire

	for(int iline=0; iline<sizeY; ++iline) // copies des informations du fichier map
	{
		fgets(line, sizeof(line),f);
		memcpy(&pMap[iline*sizeX], line, sizeX);
	}

	fclose(f);	
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "hge.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "Gumble");
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);

	if(hge->System_Initiate())
	{
		// Chargement du fichier 'ressource.res'
		Res = new hgeResourceManager("resource.res");  
		// Chargement du background
		bgSprite = Res->GetSprite("bgSprite");

		//Chargement des différentes boules de couleurs
		b_rouge = Res->GetAnimation("br");
		b_vert = Res->GetAnimation("bv");
		b_bleu = Res->GetAnimation("bb");
		b_orange = Res->GetAnimation("bo");
		b_jaune = Res->GetAnimation("bj");
		b_violet = Res->GetAnimation("bvi");
		b_gris = Res->GetAnimation("bgris");

		// Chargement de la police d'écriture
		font1 = Res->GetFont("font1");

		// Chargement du 'GameOver' et du 'YouWin'
		game_over = Res->GetSprite("game_over");
		you_win = Res->GetSprite("you_win");
	
		// Chargement de l'animation du bouton 'menu' sur l'espace de jeux
		bt_menu = Res->GetAnimation("bt_anim");

		// Initialisation de la music
		//myMusic = Res->GetStream("theme");

		// Jouer la music de fond 
		chan[0] = hge->Stream_Play(myMusic, true);

		b_rouge->Play();  //start playback of animation
		b_vert->Play();
		b_bleu->Play();
		b_orange->Play();
		b_jaune->Play();
		b_violet->Play();
		b_gris->Play();
		bt_menu->Play();
		LoadMap(); // charge la map

		// Chargement textures et sons
		tex=hge->Texture_Load("cursor.png");
		//snd=hge->Effect_Load("boing_2.wav");
		
		// Chargement de la police et du sprite du cursor
		//fnt=new hgeFont("font1.fnt");
		spr=new hgeSprite(tex,0,0,32,32);


		// Initialise le GUI
		gui=new hgeGUI();

		/*
		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,385,360,0.0f,"Play"));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,385,bouleSizeX0,0.1f,"Options"));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,385,4bouleSizeX,0.2f,"Instructions"));
		gui->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,385,480,0.3f,"Credits"));
		gui->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,385,520,0.4f,"Exit"));
		*/
		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(spr);
		gui->SetFocus(1);
		//gui->Enter();

		// Let's rock now!
		hge->System_Start();

		// Libération des ressoureces
		/*delete gui;
	    delete fnt;
	    delete spr;
	    hge->Texture_Free(tex);
	    hge->Effect_Free(snd);*/
	}
	free(pMap);
	hge->System_Shutdown();
	hge->Release();
	return 0; 
}

