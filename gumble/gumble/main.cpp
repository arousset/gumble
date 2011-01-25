#include "vglobales.h"

// Fonction permettant de générer un nombre aléatoire entre 2 bornes [x-y]
int my_rand ()
{
	hge->Random_Seed(0);  //sets the seed to the current time
	return (hge->Random_Int(1, 7));
}



char attrib_boule(int couleur)
{
	char Ccouleur;
	switch (couleur)
	{
		case 1: {
			  Ccouleur = 'r';break;
		}
		case 2: {
			  Ccouleur = 'v';break;
		}
		case 3: {
			  Ccouleur = 'b';break;
		}
		case 4: {
			  Ccouleur = 'o';break;
		}
		case 5: {
			  Ccouleur = 'g';break;
		}
		case 6: {
			  Ccouleur = 'j';break;
		}
		case 7: {
			  Ccouleur = 'w';break;
		}
	}
	return Ccouleur;
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
		mapX =  calculPosX((int)(newX-bouleSizeX/2));
		
		if(mapX < 8 && mapY < 11)
			if(pMap[(mapX)+((mapY)*8)] != 'x')
			{
				xcoll = (int)(xMap+    ((mapX)*bouleSizeX)    +(bouleSizeX/2)   +decalage);
				ycoll = (int)(yMap-         ((mapY-1)*bouleSizeY)      -(bouleSizeX/2));
				if(isDowning)
					ycoll -= (int)(bouleSizeY-animDowning);
				b_orange->RenderStretch((float)(xcoll-2), (float)(ycoll-2), (float)(xcoll+2), (float)(ycoll+2));

				int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
				if(detect < bouleSizeX*bouleSizeX)
					collision = true;
			}
		if(mapX < 8 && mapY > 1)
			if(pMap[(mapX)+((mapY-2)*8)] != 'x')
			{
				xcoll = (int)(xMap+    ((mapX)*bouleSizeX)    +(bouleSizeX/2)   +decalage);
				ycoll = (int)(yMap-         ((mapY-3)*bouleSizeY)      -(bouleSizeX/2));
				if(isDowning)
					ycoll -= (int)(bouleSizeY-animDowning);
				b_orange->RenderStretch((float)(xcoll-2), (float)(ycoll-2), (float)(xcoll+2), (float)(ycoll+2));

				int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
				if(detect < bouleSizeX*bouleSizeX)
					collision = true;
			}
	}
	else
	{
		mapX =  calculPosX(newX);
		decalage = (int)(bouleSizeX/2);

		if(mapX > 1 && mapY < 11)
		if(pMap[(mapX-2)+((mapY)*8)] != 'x')
		{
		xcoll = (int)(xMap+    ((mapX-2)*bouleSizeX)    +(bouleSizeX/2)   +decalage);
		ycoll = (int)(yMap-         ((mapY-1)*bouleSizeY)      -(bouleSizeX/2));
		if(isDowning)
			ycoll -= (int)(bouleSizeY-animDowning);
		b_orange->RenderStretch((float)(xcoll-2), (float)(ycoll-2), (float)(xcoll+2), (float)(ycoll+2));

		int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
			if(detect < bouleSizeX*bouleSizeX)
				collision = true;
		}

		if(mapX > 1 && mapY > 1)
		if(pMap[(mapX-2)+((mapY-2)*8)] != 'x')
		{
		xcoll = (int)(xMap+    ((mapX-2)*bouleSizeX)    +(bouleSizeX/2)   +decalage);
		ycoll = (int)(yMap-         ((mapY-3)*bouleSizeY)      -(bouleSizeX/2));
		if(isDowning)
			ycoll -= (int)(bouleSizeY-animDowning);
		b_orange->RenderStretch((float)(xcoll-2), (float)(ycoll-2), (float)(xcoll+2), (float)(ycoll+2));

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
		decalage = (int)(bouleSizeX/2);
	else
		decalage = 0;
	if(mapX > 1)
	if(pMap[(mapX-2)+((mapY-1)*8)] != 'x')
	{
		xcoll = (int)(xMap+    ((mapX-2)*bouleSizeX)    +(bouleSizeX/2)   +decalage);
		ycoll = (int)(yMap-         ((mapY-2)*bouleSizeY)      -(bouleSizeX/2));
		if(isDowning)
			ycoll -= (int)(bouleSizeY-animDowning);
		b_orange->RenderStretch((float)(xcoll-2), (float)(ycoll-2), (float)(xcoll+2), (float)(ycoll+2));

		int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
			if(detect < bouleSizeX*bouleSizeX)
					collision = true;
	}
	if(mapX < 8)
	if(pMap[(mapX)+((mapY-1)*8)] != 'x')
	{
		xcoll = (int)(xMap+    ((mapX)*bouleSizeX)    +(bouleSizeX/2)   +decalage);
		ycoll = (int)(yMap-         ((mapY-2)*bouleSizeY)      -(bouleSizeX/2));
		if(isDowning)
			ycoll -= (int)(bouleSizeY-animDowning);
		b_orange->RenderStretch((float)(xcoll-2), (float)(ycoll-2), (float)(xcoll+2), (float)(ycoll+2));

		int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
			if(detect < bouleSizeX*bouleSizeX)
					collision = true;
	}
	if(!yPaire)
		decalage = (int)(bouleSizeX/2);
	else
		decalage = 0;
	if(mapY < 11)
	if(pMap[(mapX-1)+((mapY)*8)] != 'x')
	{
		xcoll = (int)(xMap+    ((mapX-1)*bouleSizeX)    +(bouleSizeX/2)   +decalage);
		ycoll = (int)(yMap-         ((mapY-1)*bouleSizeY)      -(bouleSizeX/2));
		if(isDowning)
			ycoll -= (int)(bouleSizeY-animDowning);
		b_orange->RenderStretch((float)(xcoll-2), (float)(ycoll-2), (float)(xcoll+2), (float)(ycoll+2));

		int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
			if(detect < bouleSizeX*bouleSizeX)
					collision = true;
	}
	if(mapY > 1)
	if(pMap[(mapX-1)+((mapY-2)*8)] != 'x')
	{
		xcoll = (int)(xMap+    ((mapX-1)*bouleSizeX)    +(bouleSizeX/2)   +decalage);
		ycoll = (int)(yMap-         ((mapY-3)*bouleSizeY)      -(bouleSizeX/2));
		if(isDowning)
			ycoll -= (int)(bouleSizeY-animDowning);
		b_orange->RenderStretch((float)(xcoll-2), (float)(ycoll-2), (float)(xcoll+2), (float)(ycoll+2));

		int detect = (newX-xcoll)*(newX-xcoll) + (newY-ycoll)*(newY-ycoll);
				if(detect < bouleSizeX*bouleSizeX)
					collision = true;
	}
	return collision;
}

void affiche_next(char couleur)
{
	switch (couleur)
			{
				case 'r': {
					  b_rouge->RenderStretch(bnext_X,bnext_Y,bnext_X+bouleSizeX,bnext_Y+bouleSizeX);break;
				}
				case 'v': {
					  b_vert->RenderStretch(bnext_X,bnext_Y,bnext_X+bouleSizeX,bnext_Y+bouleSizeX);break;
				}
				case 'b': {
					  b_bleu->RenderStretch(bnext_X,bnext_Y,bnext_X+bouleSizeX,bnext_Y+bouleSizeX);break;
				}
				case 'o': {
					  b_orange->RenderStretch(bnext_X,bnext_Y,bnext_X+bouleSizeX,bnext_Y+bouleSizeX);break;
				}
				case 'g': {
					  b_gris->RenderStretch(bnext_X,bnext_Y,bnext_X+bouleSizeX,bnext_Y+bouleSizeX);break;
				}
				case 'j': {
					  b_jaune->RenderStretch(bnext_X,bnext_Y,bnext_X+bouleSizeX,bnext_Y+bouleSizeX);break;
				}
				case 'w': {
					  b_violet->RenderStretch(bnext_X,bnext_Y,bnext_X+bouleSizeX,bnext_Y+bouleSizeX);break;
				}
			}
}

// destroy() va bientôt être supprimée pour laisser place a destroy2()
void destroy(int index, char couleur, bool lignePaire)
{
	bool destroyBCourante = false;
	//pMap[index] = 'x';

	if(index%8 != 0)
		if(pMap[index-1] == couleur)
		{
			pMap[index-1] = 'x';
			destroyBCourante = true;
			cptDestroy++;
			destroy(index-1, couleur, lignePaire);
		}
	if(index%8 != 7)
		if(pMap[index+1] == couleur)
		{
			pMap[index+1] = 'x';
			destroyBCourante = true;
			cptDestroy++;
			destroy(index+1, couleur, lignePaire);
		}
	if(pMap[index+8] == couleur)
	{
		pMap[index+8] = 'x';
		destroyBCourante = true;
		cptDestroy++;
		destroy(index+8, couleur, lignePaire);
	}
	if(pMap[index-8] == couleur)
	{
		pMap[index-8] = 'x';
		destroyBCourante = true;
		cptDestroy++;
		destroy(index-8, couleur, lignePaire);
	}
	if(lignePaire)
	{
		if(index%8 != 7)
			if(pMap[index+8+1] == couleur)
			{
				pMap[index+8+1] = 'x';
				destroyBCourante = true;
				cptDestroy++;
				destroy(index+8+1, couleur, lignePaire);
			}
		if(index%8 != 7)
			if(pMap[index-8+1] == couleur)
			{
				pMap[index-8+1] = 'x';
				destroyBCourante = true;
				cptDestroy++;
				destroy(index-8+1, couleur, lignePaire);
			}
	}
	else
	{
		if(index%8 != 0)
			if(pMap[index+8-1] == couleur)
			{
				pMap[index+8-1] = 'x';
				destroyBCourante = true;
				cptDestroy++;
				destroy(index+8-1, couleur, lignePaire);
			}
		if(index%8 != 0)
			if(pMap[index-8-1] == couleur)
			{
				pMap[index-8-1] = 'x';
				destroyBCourante = true;
				cptDestroy++;
				destroy(index-8-1, couleur, lignePaire);
			}
	}
	//if(destroyBCourante && cptDestroy > 2)
	if(destroyBCourante)
		pMap[index] = 'x';

}

void particleDisplay(int index)
{
	int posXParticule = (int)((index%8)*bouleSizeX + (bouleSizeX/2));
	posXParticule = xMap + posXParticule;
	int poxYParticule = (int)((index/8)*bouleSizeX + (bouleSizeX/2));
	poxYParticule = yMap - poxYParticule;
	particleManager->SpawnPS(&particle, (float)posXParticule, (float)poxYParticule);
}

void destroy2(int index, char couleur, bool lignePaire)
{
	if(!tabToDestroy[index])
	{
		cptDestroy++;
		tabToDestroy[index] = true;

		if(index%8 != 0)
			if(pMap[index-1] == couleur)
			{
				destroy2(index-1, couleur, lignePaire);
			}
		if(index%8 != 7)
			if(pMap[index+1] == couleur)
			{
				destroy2(index+1, couleur, lignePaire);
			}
		if(pMap[index+8] == couleur)
		{
			destroy2(index+8, couleur, !lignePaire);
		}
		if(pMap[index-8] == couleur)
		{
			destroy2(index-8, couleur, !lignePaire);
		}
		if(lignePaire)
		{
			if(index%8 != 7)
				if(pMap[index+8+1] == couleur)
				{
					destroy2(index+8+1, couleur, !lignePaire);
				}
			if(index%8 != 7)
				if(pMap[index-8+1] == couleur)
				{
					destroy2(index-8+1, couleur, !lignePaire);
				}
		}
		else
		{
			if(index%8 != 0)
				if(pMap[index+8-1] == couleur)
				{
					destroy2(index+8-1, couleur, !lignePaire);
				}
			if(index%8 != 0)
				if(pMap[index-8-1] == couleur)
				{
					destroy2(index-8-1, couleur, !lignePaire);
				}
		}
	}

}

void init(bool *tab)
{
	for(int i = 0;i < 88;i++)
		tab[i] = false;
} 

bool needDestroyation(bool *tab)
{
	for(int i = 80; i < 88;i++)
	{
		if(tab[i])
			return false;
	}
	noSuspendedIsDowning = true;
	return true;
}

void destroyNoSuspended(int index, bool lignePaire, bool *tab)
{
	if(!tab[index] && index/8 < 11 )
	{
		tab[index] = true;

		if(index%8 != 0)
			if(pMap[index-1] != 'x')
			{
				destroyNoSuspended(index-1, lignePaire, tab);
			}
		if(index%8 != 7)
			if(pMap[index+1] != 'x')
			{
				destroyNoSuspended(index+1, lignePaire, tab);
			}
		if(pMap[index+8] != 'x')
		{
			destroyNoSuspended(index+8, !lignePaire, tab);
		}
		if(pMap[index-8] != 'x')
		{
			destroyNoSuspended(index-8, !lignePaire, tab);
		}
		if(lignePaire)
		{
			if(index%8 != 7)
				if(pMap[index+8+1] != 'x')
				{
					destroyNoSuspended(index+8+1, !lignePaire, tab);
				}
			if(index%8 != 7)
				if(pMap[index-8+1] != 'x')
				{
					destroyNoSuspended(index-8+1, !lignePaire, tab);
				}
		}
		else
		{
			if(index%8 != 0)
				if(pMap[index+8-1] != 'x')
				{
					destroyNoSuspended(index+8-1, !lignePaire, tab);
				}
			if(index%8 != 0)
				if(pMap[index-8-1] != 'x')
				{
					destroyNoSuspended(index-8-1, !lignePaire, tab);
				}
		}
	}
}

void tmp2(bool *tab)
{
	for(int i = 0; i < 88;i++)
	{
		if(tab[i])
		{
			pMap[i] = 'x';
			noSuspendedTab[i] = true;
		}
	}
}

void tmp(int index, bool lignePaire)
{
	bool* tab = new bool[88];

/*////////////// tableau 1
	init(tab);
	destroyNoSuspended(index-1, lignePaire, tab);
	if(needDestroyation(tab))
	{
		int loooool = 0;
	// detruire les boules de tab
	}
	
////////////// tableau 2
	init(tab);
	destroyNoSuspended(index+1, lignePaire, tab);
	if(needDestroyation(tab))
	{
		int loooool = 0;
	// detruire les boules de tab
	}*/

		if(index%8 != 0)
			if(pMap[index-1] != 'x')
			{
				init(tab);
				destroyNoSuspended(index-1, lignePaire, tab);
				if(needDestroyation(tab))
				{
					tmp2(tab);
				}
			}
		if(index%8 != 7)
			if(pMap[index+1] != 'x')
			{
				init(tab);
				destroyNoSuspended(index+1, lignePaire, tab);
				if(needDestroyation(tab))
				{
					tmp2(tab);
				}
			}
		if(pMap[index+8] != 'x')
		{
			init(tab);
			destroyNoSuspended(index+8, !lignePaire, tab);
			if(needDestroyation(tab))
			{
				tmp2(tab);
			}
		}
		if(pMap[index-8] != 'x')
		{
			init(tab);
			destroyNoSuspended(index-8, !lignePaire, tab);
			if(needDestroyation(tab))
				{
					tmp2(tab);
				}
		}
		if(lignePaire)
		{
			if(index%8 != 7)
				if(pMap[index+8+1] != 'x')
				{
					init(tab);
					destroyNoSuspended(index+8+1, !lignePaire, tab);
					if(needDestroyation(tab))
					{
						tmp2(tab);
					}
				}
			if(index%8 != 7)
				if(pMap[index-8+1] != 'x')
				{
					init(tab);
					destroyNoSuspended(index-8+1, !lignePaire, tab);
					if(needDestroyation(tab))
					{
						tmp2(tab);
					}
				}
		}
		else
		{
			if(index%8 != 0)
				if(pMap[index+8-1] != 'x')
				{
					init(tab);
					destroyNoSuspended(index+8-1, !lignePaire, tab);
					if(needDestroyation(tab))
					{
						tmp2(tab);
					}
				}
			if(index%8 != 0)
				if(pMap[index-8-1] != 'x')
				{
					init(tab);
					destroyNoSuspended(index-8-1, !lignePaire, tab);
					if(needDestroyation(tab))
					{
						tmp2(tab);
					}
				}
		}
}

void lunched_boule(char couleur, float angle)
{
		bool test = Collision((int)(posX_bcourante+(bouleSizeX/2)), (int)(posY_bcourante+(bouleSizeX/2)));
		if(!test)
		{
			switch (couleur)
			{
				case 'r': {
					  b_rouge->RenderStretch(posX_bcourante,posY_bcourante,posX_bcourante+bouleSizeX,posY_bcourante+bouleSizeX);break;
				}
				case 'v': {
					  b_vert->RenderStretch(posX_bcourante,posY_bcourante,posX_bcourante+bouleSizeX,posY_bcourante+bouleSizeX);break;
				}
				case 'b': {
					  b_bleu->RenderStretch(posX_bcourante,posY_bcourante,posX_bcourante+bouleSizeX,posY_bcourante+bouleSizeX);break;
				}
				case 'o': {
					  b_orange->RenderStretch(posX_bcourante,posY_bcourante,posX_bcourante+bouleSizeX,posY_bcourante+bouleSizeX);break;
				}
				case 'g': {
					  b_gris->RenderStretch(posX_bcourante,posY_bcourante,posX_bcourante+bouleSizeX,posY_bcourante+bouleSizeX);break;
				}
				case 'j': {
					  b_jaune->RenderStretch(posX_bcourante,posY_bcourante,posX_bcourante+bouleSizeX,posY_bcourante+bouleSizeX);break;
				}
				case 'w': {
					  b_violet->RenderStretch(posX_bcourante,posY_bcourante,posX_bcourante+bouleSizeX,posY_bcourante+bouleSizeX);break;
				}
			}

			posY_bcourante -= 0.5; 
			posX_bcourante += rot;
			if(posX_bcourante < xMap)
				rot = -rot;
			if(posX_bcourante+bouleSizeX > xMap + (8*bouleSizeX) + bouleSizeX/2)
				rot = -rot;

		}
		int y = calculPosY((int)(posY_bcourante+(bouleSizeX/2)));
		if(test || y == 11)
		{
			int x;

			bool yPaire = premierelignepaire;
			for(int cpt = 1;cpt < y;cpt++)
				yPaire = !yPaire;

			if(yPaire)
				x = calculPosX((int)posX_bcourante);
			else
				x = calculPosX((int)(posX_bcourante+(bouleSizeX/2)));

			int index = (y-1)*8+x-1;

			//initialisation du tableau des boules a détruire
			for(int i = 0;i < 88;i++)
				tabToDestroy[i] = false;
			cptDestroy = 0; // initialisation du compteur de boules a supprimer ( > 3? )

			if(!isDowning)
			{
				pMap[index] = couleur;
				destroy2(index, couleur, yPaire);
			}
			else
			{
				if(pMap[(x-1)+((y-1)*8)] != 'x')
				{
					index -= 8;
					pMap[index] = couleur;
					destroy2(index, couleur, yPaire);
				}
				else
				{
					pMap[index] = couleur;
					destroy2(index, couleur, yPaire);
				}
			}

			// destruction des boules
			if(cptDestroy > 2)
			{
				for(int i = 0;i < 88;i++)
				{
					if(tabToDestroy[i])
					{
						particleDisplay(i);
						pMap[i] = 'x';
						tmp(i, yPaire);
					}
				}
			}
			
			blunched_boule = false;
			lunched=true;  
		}

}

void menu_pfiout()
{
	// La bidouille du Siou !!!!!
		// Non sans déconner c'est pour virer le menu quant on est sur le jeux :)
		gui->ShowCtrl(1,false);
		gui->ShowCtrl(2,false);
		gui->ShowCtrl(3,false);
		gui->ShowCtrl(4,false);
		gui->ShowCtrl(5,false);
		hge->Effect_Free(snd);
}


bool FrameFunc() // Fonction appelée à chaque image
{
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;
	int id = -1;
	static int lastid=0;
	float dt=hge->Timer_GetDelta();

	  id = gui->Update(dt);
	  
	  if(id == -1)
	  {
		switch(lastid)
		{
		  case 1:
			  id_menu = 1;
			  break;
		  case 2:
			  id_menu = 2;
			  break;
		  case 3:
			  id_menu = 3;
			  break;
		  case 4:
			  id_menu = 4;	
			  break;
		  case 5: return true;
		}
	  }
	  else if(id) 
	  {   
        lastid = id;   
        gui->Leave();     
      }  
	  
 return false;
}

bool RenderFunc()
{
	if(id_menu == 1) // Pour le menu du jeux 
	{
		// tetre pas necessaire à vérifier
		//menu_pfiout(); // Bidouille du siou pour virer le menu sur le jeux
		
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
		if( (hge->Input_GetKey()==HGEK_SPACE) && (!blunched_boule))
		{
				posX_bcourante = posX_depart;
				posY_bcourante = posY_depart;
				blunched_boule=true; // La boule courante a été lancée

				alea_c = alea_n; // Permet de passer la boule suivante à la boule courante
		}

		
		// Permet de récupérer les coordonnées de la souris à virer par la suite //////////////////////////////////
		hge->Input_GetMousePos(&mouseX, &mouseY);
		////////////////////////////// A virer par la suite ! //////////////////////////////////

		//Génerer un nombre aléatoire si la variable 'lunched' est à vrai pour générer un boule suivante
		if(lunched==true)
		{
			alea_n = my_rand(); // Génére un nombre entre 1 et 7 compris pour la boule suivante
			coul_bsuivante = attrib_boule(alea_n); // idem
			coul_bcourante = attrib_boule(alea_c);

			lunched = false; // on passe lunched à faux tant que la boule n'est pas lancée
		}

		/////// AVIRER PAR LA SUITE ///////////////// Pour l'affichage des particule à la souris 
		particleManager->Update(dt);  //update all particles
		if(hge->Input_GetKey()==HGEK_LBUTTON)
		{
			particleManager->SpawnPS(&particle, mouseX, mouseY);
		}////////////////////////////////////////////////////  

  // Render graphics
  hge->Gfx_BeginScene();
  bgSprite->Render(0, 0);
  hge->Gfx_Clear(0);
	
		bt_menu->Render(640,390);
		gui->Render(); // Permet de lancer le GUI et donc d'utiliser d'afficher le curseur.png définit avant

		b_rouge->Update(dt);  //update the animation
		b_vert->Update(dt);
		b_bleu->Update(dt);
		b_orange->Update(dt);
		b_jaune->Update(dt);
		b_violet->Update(dt);
		b_gris->Update(dt);

		// test pour afficher la direction du tir
		for(int i = 0; i < 400;i++)
		{
			//b_violet->RenderStretch(380+(bouleSizeX/2)-2.5+(i*rot), 480+(bouleSizeX/2)-(i*1),380+(bouleSizeX/2)-2.5+(i*rot)+5,480+(bouleSizeX/2)-(i*1)+5);
			b_violet->RenderStretch(
				(float)(380+(bouleSizeX/2)-2.5+(i*rot)),
				(float)(480+(bouleSizeX/2)-(i*0.5)),
				(float)(380+(bouleSizeX/2)-2.5+(i*rot)+5),
				(float)(480+(bouleSizeX/2)-(i*0.5)+5));
		}


		if(blunched_boule)
		{
			lunched_boule(coul_bcourante, rot); // coul b_courante
		}

		/* du bon gros caca pour l'instant
		if(noSuspendedIsDowning) ///// FAIRE DESCENDRE LES BOULES NON SUSPENDUES (chaud chaud chaud !)
		{
			noSuspendedAnimDowning += 0.5;
			if(animDowning < 100)
			{
				for(int i = 0;i < 80;i++)
				{
					if(noSuspendedTab[i])
					{
						int y = i/8;
						int x = i%8;

						float decalage = 0.0;       // si la ligne est paire, on la décale

						if((y+swapPair)%2 == 0)
						{
							decalage = bouleSizeX/2;
							if(y == 0)
								premierelignepaire = true;
							if(y == 1)
								premierelignepaire = false;
						}
						float x1 = xMap+((x)*bouleSizeX+decalage);
						float y1 = yMap-((y-1)*bouleSizeY);

						float x2 = xMap+bouleSizeX+((x)*bouleSizeX+decalage);
						float y2 = yMap-bouleSizeX-((y-1)*bouleSizeY);

						y1 -= noSuspendedAnimDowning;
						y2 -= noSuspendedAnimDowning;
						b_orange->RenderStretch(x1, y1, x2, y2);
					}
				}
			}
			else
			{
				animDowning = 0;
				for(int i = 0; i < 80;i++)
				{
					noSuspendedTab[i] = false;
				}
				noSuspendedIsDowning = false;
			}
		}*/

		for(int y=0; y<sizeY; ++y) // affiche les boules et leur descente
		{
			float posY =y*bouleSizeY;
			for(int x=0; x<sizeX; ++x)
			{
				if(y < 11)
				{
					if(y == 0 && x == 0 && isDowning) // si les boules sont en train de descendre, on leur attribut pour chaque image une position décalée de 0.05 px (descente petit à petit)
						animDowning += (float)0.05;


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
						
							for(int i=0; i<8; i++)
							{
								if(pMap[i] != 'x')
								{
									loose = true; // Permet d'arreter le jeux
									stop_time = true; // Permet d'arreter le temps quand la partie GameOver
								}
							}

							animDowning = 0;
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
								  b_rouge->RenderStretch(x1, y1, x2, y2);
								  //font1->printf(x1+10, y1-30, HGETEXT_LEFT,"%d", index);
								  break;
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
							//case 'x' : {
								  b_violet->RenderStretch(x1, y1, x2, y2);
								  //font1->printf(x1, y1-30, HGETEXT_LEFT,"%d", index);break;
							}
					   }
					}
				}
			}
		}	
		

		//!\\ A revoir car je dois faire un pointeur pour stopper le temps quand la partie est perdu ou gagné ! :)
		// initialisation du compteur de temps et test pour l'affichage
		if(stop_time == false)
		{
			float time=0; // Permet de gérer le compteur de temps
			time = hge->Timer_GetTime();
			font1->SetColor(ARGB(255,1,148,48));  //set color of text to black
			font1->printf(678,142, HGETEXT_LEFT, "%.2f", time); // .2f pour afficher uniquement 2 décimales
		}
	
		// Affiche le message GameOver 
		if (loose == true)
		{
			game_over->Render(262,250);
		}
	
		// Affichage du score du joueur
		font1->printf(120, 142, HGETEXT_LEFT,"%d", score);


		//!\\ Permet d'afficher les coordonnées de la souris pour mieux placer les sprites.
		font1->printf(5, 5, HGETEXT_LEFT,"%.2f, %.2f", mouseX, mouseY); //affiche les coordonnées de la souris.
		//!\\
		
		// Permet d'afficher la boule suivante
		affiche_next(coul_bsuivante);
	
		// Affichage du canon
		canon_img->SetHotSpot(65,65);
		canon_img->RenderEx(canonLocX, canonLocY,(float)(rot*1.5));
	
		if(hge->Input_GetKeyState(HGEK_RIGHT) && rot < 1)
			rot += (float)0.0005;
		if(hge->Input_GetKeyState(HGEK_LEFT) && rot > -1)
			rot -= (float)0.0005;
	

		/* Cette partie est en construction cela va permettre de faire des tests pour générer les boules aléatoirement.*/
		/* Bon Je sais c'est déguellasse car je code en dur les coordonnées :p */
		if(!blunched_boule)
		{
			switch (alea_c)
			{
				case 1: {
					  b_rouge->RenderStretch(posX_depart,posY_depart,posX_depart+bouleSizeX,posY_depart+bouleSizeX);break;
				}
				case 2: {
					  b_vert->RenderStretch(posX_depart,posY_depart,posX_depart+bouleSizeX,posY_depart+bouleSizeX);break;
				}
				case 3: {
					  b_bleu->RenderStretch(posX_depart,posY_depart,posX_depart+bouleSizeX,posY_depart+bouleSizeX);break;
				}
				case 4: {
					  b_orange->RenderStretch(posX_depart,posY_depart,posX_depart+bouleSizeX,posY_depart+bouleSizeX);break;
				}
				case 5: {
					  b_gris->RenderStretch(posX_depart,posY_depart,posX_depart+bouleSizeX,posY_depart+bouleSizeX);break;
				}
				case 6: {
					  b_jaune->RenderStretch(posX_depart,posY_depart,posX_depart+bouleSizeX,posY_depart+bouleSizeX);break;
				}
				case 7: {
					  b_violet->RenderStretch(posX_depart,posY_depart,posX_depart+bouleSizeX,posY_depart+bouleSizeX);break;
				}
			}
		}
	}

	if(id_menu == -1) // Pour le menu du jeux 
	{
		// Render graphics
		hge->Gfx_BeginScene();
		bgg->Render(0, 0); // pour le backg gumble
		gui->Render(); // Permet de lancer le GUI et donc d'utiliser d'afficher le curseur.png définit avant
	}

	if (id_menu == 2) // Mode multijoueur 
	{
	
	
	}

	if (id_menu == 3) // Intructions
	{
		hge->Gfx_BeginScene();
		hge->Gfx_Clear(0);
		bgg->Render(0, 0);	// Affichage du fond 
		fnt->SetColor(0xFFFFFFFF);
		fnt->Render(390, 345, HGETEXT_CENTER, "Instructions\n"
			"Shoot the color balls\n\n"
			"\n\n"
			"ESPACE - Shoot\n"
			"Left / Right - Turn the canon\n\n"
			"");
		gui->Render();
	}

	if (id_menu == 4) // Crédits 
	{
		hge->Gfx_BeginScene();
		hge->Gfx_Clear(0);
		bgg->Render(0, 0);	// Affichage du fond
		fnt->SetColor(0xFFFFFFFF);
		fnt->Render(390, 345, HGETEXT_CENTER, "Credit\n"
			"GUMBLE\n\n"
			"KAWCZAK Clement & ROUSSET Alban\n"
			"\n\n"
			"using HGE and C++\n\n"
			"Space to quit");

 		/*if(hge->Input_GetKey()==HGEK_SPACE)
		{*/
			id_menu = -1; // Pour quitter la page crédit et revenir au menu
			fnt->Render(200, 150, HGETEXT_LEFT, "Credit\n" "dfgdfgdfgdfgdfgdfgdfg");
		//}
		 // sa plante un peux a coause du refresh Gfx_scene()
  		gui->Render();
	}


	particleManager->Render();  //render all particles
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
	sizeX = atoi(line); // nombre de colones
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
		canon_img = Res->GetSprite("img_canon");
		// Chargement image menu 
		bgg = Res->GetSprite("bgg");
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
		snd=hge->Effect_Load("boing_2.wav");
		
		// Chargement de la police et du sprite du cursor
		fnt=new hgeFont("font1.fnt");
		spr=new hgeSprite(tex,0,0,32,32);


		// Initialise le GUI
		gui=new hgeGUI();

		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,385,360,0.0f,"Play 1 Player"));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,385,400,0.1f,"Multiplayer"));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,385,440,0.2f,"Instructions"));
		gui->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,385,480,0.3f,"Credits"));
		gui->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,385,520,0.4f,"Exit"));
		
		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(spr);
		gui->SetFocus(1);
		gui->Enter();
		gui->Render();

		if(first)
		{
			alea_n = my_rand(); // Génére un nombre entre 1 et 7 compris pour la boule suivante
			coul_bsuivante = attrib_boule(alea_n); // Permet de faire le lien entre les chiffres et les couleurs de boules
			affiche_next(coul_bsuivante);
			coul_bcourante = attrib_boule(alea_c); // Permet d'initialiser la 1er boule 
			
			first = false;
		}

		particle = Res->GetParticleSystem("particle")->info;
		particleManager= new hgeParticleManager();

		// Let's rock now!
		hge->System_Start();

		// Libération des ressoureces
		delete gui;
	    delete fnt;
	    delete spr;
	    hge->Texture_Free(tex);
	    hge->Effect_Free(snd);
	}
	free(pMap);
	delete particleManager;
	hge->System_Shutdown();
	hge->Release();
	return 0; 
}