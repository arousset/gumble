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

HGE *hge = 0;
hgeResourceManager* Res;
hgeSprite* bgSprite;
char* pMap = NULL; // pointeur sur la desctiption de la map
int sizeX, sizeY;
float fScale =27;
const int xMap = 290; // abscisse de la plus basse ligne pour afficher les boules
const int yMap = 400; // ordonn�e de la plus basse ligne pour afficher les boules
const float bouleSize = 40; // taille de la boule
float timeDown = 3; // temps avant de faire tomber les boules(secondes)
float timeCpt = 0; // compteur de temps
int swapPair = 0; // variables utile pour d�termin�e si la ligne a besoin d'etre d�cal�e
bool isDowning = false; // les boules sont en train de descendre ?
float animDowning = 1; // utile pour faire une sorte d'animation lors de la descente des boules


// Sprite pour les boules
hgeAnimation* b_rouge; //rouge
hgeAnimation* b_vert; // vert
hgeAnimation* b_bleu; //bleu
hgeAnimation* b_orange; //orange
hgeAnimation* b_jaune; //jaune
hgeAnimation* b_violet; //violet
hgeAnimation* b_gris; //gris

/*
// Some resource handles
HEFFECT				snd;
HTEXTURE			tex;

// Pointeurs pour HGE object
hgeGUI				*gui;
hgeFont				*fnt;
hgeSprite			*spr;
*/
bool FrameFunc() // Fonction appel�e � chaque image
{
	
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;
 /* int id;
  static int lastid=0;
  float dt=hge->Timer_GetDelta();

  // Si 'echap' => exit
  if(hge->Input_GetKeyState(HGEK_ESCAPE)) { lastid=5; gui->Leave(); }

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

  */
 return false;
}

bool RenderFunc()
{
	float dt=hge->Timer_GetDelta();  //get the time since the last call to FrameFunc
	timeCpt += dt; // on additionne les temps entre les images
	if(timeCpt > timeDown) // si ce compteur est sup�rieur aux temps d�finis pour faire tomber les boules :
	{													// on actualise pMap pour lui enlever une ligne en bas (la ligne la plus basse disparait pour faire descendre les autres)
		if(!isDowning) // les boules ne sont pas en train de descendre
		{
			sizeY -= 1; // nouveau nombre de ligne (on supprime celle en bas)
			char* pMapTmp = new char[(sizeX*sizeY)];		// pour cela, on cr�� un nouveau tableau		
			for(int cpt = 0; cpt < (sizeX*sizeY);cpt++)   // puis on recopie les valeurs de pMap en enlevant la premiere ligne
			{
				pMapTmp[cpt] = pMap[cpt+7];
			}
			char* toFree = pMap;
			pMap = pMapTmp;
			free(toFree); // on free l'ancien tableau
			timeCpt = 0; // on remet le compteur de temps � 0;
			swapPair = (swapPair+1)%2; // on modifie la variable a chaque descente de boules (elle prend soit 1 soit 0)
			isDowning = true;
		}
	}

	/*b_rouge->Update(dt);  //update the animation
	b_vert->Update(dt);
	b_bleu->Update(dt);
	b_orange->Update(dt);*/

	// Render graphics
	hge->Gfx_BeginScene();
	bgSprite->Render(0, 0);
	//b_rouge->Render(250, 70);
	//b_rouge->RenderStretch(250,70,290,110);
	//gui->Render();
	for(int y=0; y<sizeY; ++y)
	{
		float posY =y*fScale;
		for(int x=0; x<sizeX; ++x)
		{
			if(y < 9)
			{
				if(y == 0 && x == 0 && isDowning) // si les boules sont en train de descendre, on leur attribut pour chaque image une position d�cal�e de 0.05 px (descente petit � petit)
					animDowning += 0.05;


				float decalage = 0.0;       // si la ligne est paire, on la d�cale
				if((y+swapPair)%2 == 0)
					decalage = bouleSize/2;
				/*
				On utilise swapPair pour regarder si on doit d�caler ou non la ligne
				Exemple : premieres secondes du jeu, la ligne 5 est impaire et la ligne 6 est paire
				On affiche donc la ligne 26 d�cal�e � droite par rapport � la ligne 5 (selon les modalit�s du jeu)

				Ensuite, durant la deuxi�me phase (les boules descendent d'un cran), la ligne 5 devient la ligne 4 (donc paire) et la ligne 6 devient la ligne 5 (donc impaire)
				on doit donc dire � l'affichage de ne plus d�caler les lignes paires, mais impaires pour que les lignes restent toujours au m�me endroit en ordonn�es.
				La variable swapPair sert alterner le modulo 2 du num�ro de ligne pour que celui ci reste contant selon la ligne.
				*/

				// Nouvelles positions pour l'affichages des boules
				float x1 = xMap+((x-1)*bouleSize+decalage);
				float y1 = yMap-((y-1)*bouleSize);
				float x2 = xMap+bouleSize+((x-1)*bouleSize+decalage);
				float y2 = yMap-bouleSize-((y-1)*bouleSize);
				if(isDowning)
				{
					if(animDowning < bouleSize)
					{
						// Modification des coordonn�es des boules si elles sont en train de descendre (descente progressive sur les y)
						y1 -= (bouleSize-animDowning);
						y2 -= (bouleSize-animDowning);
					}
					else
					{
						animDowning = 1;
						isDowning = false;
						timeCpt = 0;
					}
				}

				float posX =x*fScale;

				int index =y*sizeX+x;

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
			   }
			}
		}
	}	
	hge->Gfx_EndScene();
	return false;
}

void LoadMap()
{
	FILE* f = NULL;
	f = fopen("../Debug/map.txt", "rb"); // ouverture du fichier map
	if(f == NULL)
		return;

	char line[512];
	fgets(line, sizeof(line),f);
	sizeX  =atoi(line); // nombre de colones
	fgets(line, sizeof(line),f);
	sizeY = atoi(line); // nombres de lignes

	//!\\ La premi�re ligne de la map est la ligne se tranvant le plus en bas sur le jeu. La derni�re ligne de la map repr�sente donc la ligne de boules le plus en haut possible

	pMap = new char[sizeX*sizeY]; // la pointeur sur la map r�serve la taille de la map en m�moire

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
		b_rouge = Res->GetAnimation("br");
		b_vert = Res->GetAnimation("bv");
		b_bleu = Res->GetAnimation("bb");
		b_orange = Res->GetAnimation("bo");

		b_rouge->Play();  //start playback of animation
		b_vert->Play();
		b_bleu->Play();
		b_orange->Play();
		LoadMap(); // charge la map

		// Chargement textures et sons
		//tex=hge->Texture_Load("cursor.png");
		//snd=hge->Effect_Load("boing_2.wav");
		
		// Chargement de la police et du sprite du cursor
		//fnt=new hgeFont("font1.fnt");
		//spr=new hgeSprite(tex,0,0,32,32);


		// Initialise le GUI
		/*gui=new hgeGUI();

		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,385,360,0.0f,"Play"));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,385,bouleSize0,0.1f,"Options"));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,385,4bouleSize,0.2f,"Instructions"));
		gui->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,385,480,0.3f,"Credits"));
		gui->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,385,520,0.4f,"Exit"));

		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(spr);
		gui->SetFocus(1);
		gui->Enter();*/

		// Let's rock now!
		hge->System_Start();

		// Lib�ration des ressoureces
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

