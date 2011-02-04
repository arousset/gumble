#include "vglobales.h"
#include <iostream> 


// permet de connaitre le nombre de boule total présente dans le jeux
int sum_boule()
{
		int sum=0;
		for(int i=0;i<8;i++)
		{
			sum += Tboule_count[i];
		}
		
		return sum;
}

// permet de connaitre l'indice de la couleur la plus présente dans l'air de jeux
int see_max_ind()
{
	int j=0;
	int max=0;
	int gmax=0;

	while (j < 8)
	{						
		if (Tboule_count[j] > max){
			max = Tboule_count[j];
			gmax = j; 
		}
		j++;
	}
	return gmax;
}

// permet de connaitre le max de la couleur la plus présente dans l'air de jeux
int see_max_nb()
{
	int j=0;
	int max=0;
	int gmax=0;

	while (j < 8)
	{						
		if (Tboule_count[j] > max){
			max = Tboule_count[j];
			gmax = max; 
		}
		j++;
	}
	return gmax;
}

// Permet de compter le nombre d'occurence de chaque boule dans le jeux
void count_occurence()
{
	// Nous devons parcourir le tableau de boules du jeux de 1 à 88 pour 
	// pouvoir effectuer un bilan sur le nombre de chaque boules pour 
	// faire des statistiques.
	 // Tableau de boule pMap[]
	 
	 // Correspondance entre indice et char : r v b o g j w
	 //										  0 1 2 3 4 5 6
	 
	 //faire un tab qui commpte genre Tboule_count[7];
	 for(int i=0;i<88;i++)
	 {
		switch(pMap[i])
		{
				case 'r' : //0
					Tboule_count[0] +=1; 
				break;
				
				case 'v' : //1
					Tboule_count[1] +=1; 
				break;
				
				case 'b' : //2
					Tboule_count[2] +=1; 
				break;
				
				case 'o' : //3
					Tboule_count[3] +=1; 
				break;
				
				case 'g' : //4
					Tboule_count[4] +=1; 
				break;
				
				case 'j' : //5
					Tboule_count[5] +=1; 
				break;
				
				case 'w' : //6
					Tboule_count[6] +=1; 
				break;

				case 'x' : // NULL
				break;
		}
	 }
}

// Fonction permettant de générer un nombre aléatoire entre 2 bornes [x-y]
int my_rand ()
{
	int maxnb = 0;
	int ind=0;
	int sum = 0;
	float division=0;
	
	for(int i = 0;i<8;i++)
	{
		Tboule_count[i]=0;
	}

	count_occurence();
	sum = sum_boule();
	ind = see_max_ind();
	maxnb = see_max_nb();
	division = (float)maxnb/(float)sum;
	
	// On fait les statistiques (Little player !!!)
	if(division > 0.3)
	{ 
		return ind+1; // retourne l'indice de la couleur la plus présente si >50% || 35%
	}else{
			hge->Random_Seed(0);  //sets the seed to the current time
			return (hge->Random_Int(1, 7)); // Aleatoire
	}
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
		default: {
			  Ccouleur = 'r';break;
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
	int mapY = 11;
	while(mapY*bouleSizeY > y - ((yMap+bouleSizeY)-(11*bouleSizeY)))
	{
		mapY--;
	}
	mapY = 11-mapY;
	int jesus = 465456;
	return mapY;
}

bool Collision(int newX, int newY)
{
	if(newY > yMap + bouleSizeX/2)
	{
		return false;
	}
	int mapY = calculPosY(newY);
	bool yPaire = premierelignepaire;
	for(int cpt = 1;cpt < mapY;cpt++)
	{
		yPaire = !yPaire;
	}
	int mapX;
	bool collision = false;
	int decalage = 0;
	int xcoll = 0;
	int ycoll = 0;
	if(yPaire)
	{
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
	particleManager->Render();
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
			posX_bcourante += angle;
			if(posX_bcourante < xMap)
				rotTd = -angle;
			if(posX_bcourante+bouleSizeX > xMap + (8*bouleSizeX) + bouleSizeX/2)
				rotTd = -angle;

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
						score += 100;
						if(cptDestroy > 5)
							score += 500;
							bonus = 3;
							// rajouter un petit son
							if(cptDestroy > 10)
								score += 2000;
								bonus = 5;
								// rajouter un petit son
						tmp(i, yPaire);
					}
				}
				explosion=hge->Effect_Load("explode.wav");
				hge->Effect_Play(explosion);
			}
			
			blunched_boule = false;
			lunched=true;  
		}

}

void LoadMap(int map)
{
	FILE* f = NULL;
	switch (map)
	{
		case 0: {
			  f = fopen("../Debug/map.txt", "rb");break;
		}
		case 1: {
			  f = fopen("../Debug/map2.txt", "rb");break;
		}
		case 2: {
			  f = fopen("../Debug/map3.txt", "rb");break;
		}
		case 3: {
			  f = fopen("../Debug/map4.txt", "rb");break;
		}
		case 4: {
			  f = fopen("../Debug/map4.txt", "rb");break;
		}
		default : {
			  f = fopen("../Debug/map.txt", "rb");break;
		}
	}
		
	
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

// Sous menu pourl e mode 1 player (difficulté)
bool smenu()
{
	hge->Gfx_BeginScene();
	bgg->Render(0, 0); // background gumble
	
	if (firstTimeMenu)
	{
		// Chargement sons munu click
		snd=hge->Effect_Load("boing_2.mp3");
		
		// Initialise le GUI
		delete gui;
		gui=new hgeGUI();

		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,385,360,0.0f,"Hard"));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,385,400,0.1f,"Middle"));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,385,440,0.2f,"Easy"));
		gui->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,385,480,0.3f,"Back to menu"));
		
		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		
		gui->SetFocus(1);
		gui->Enter();
		
		firstTimeMenu = false;
	}

	float dt=hge->Timer_GetDelta();
	static int bulles = 0;


	frog->RenderStretch(328,250,454,333);	
	frog->Update(dt);

	particleManager->Update(dt);

	if(bulles%3000 == 0)
	{
		bulles = 0;
		particleManager->SpawnPS(&particle_bulles, 340, 260);
	}
	particleManager->Render();

	bulles++;

	gui->SetCursor(spr);
	gui->Render();

	int id;
	 id=gui->Update(dt);
	  if(id == -1)
	  {
		switch(lastid)
		{
		  case 1: 
			  LoadMap(0); // Charge Map0 pourle début du jeu
			  score = 0;
			  niveau = 0;
			  timeDown = 7;
			  timeBegin = hge->Timer_GetTime();
			  rot = 0.0;
			  if(first)
				{
					alea_n = my_rand(); // Génére un nombre entre 1 et 7 compris pour la boule suivante
					coul_bsuivante = attrib_boule(alea_n); // Permet de faire le lien entre les chiffres et les couleurs de boules
					affiche_next(coul_bsuivante);
					coul_bcourante = attrib_boule(alea_c); // Permet d'initialiser la 1er boule 
					first = false;
				}
			   ttest = true; // Pour le son gameover à chaque partie recommencée 
			   hge->System_SetState(HGE_FRAMEFUNC, game); //gaem_int
			   break;
		  case 2:
			  LoadMap(0); // Charge Map0 pourle début du jeu
			  score = 0;
			  niveau = 0;
			  timeDown = 30;
			  timeBegin = hge->Timer_GetTime();
			  rot = 0.0;
			  if(first)
				{
					alea_n = my_rand(); // Génére un nombre entre 1 et 7 compris pour la boule suivante
					coul_bsuivante = attrib_boule(alea_n); // Permet de faire le lien entre les chiffres et les couleurs de boules
					affiche_next(coul_bsuivante);
					coul_bcourante = attrib_boule(alea_c); // Permet d'initialiser la 1er boule 
					first = false;
				}
			   ttest = true; // Pour le son gameover à chaque partie recommencée 
			   hge->System_SetState(HGE_FRAMEFUNC, game); //gaem_int
			   break;
		  case 3:
			  LoadMap(0); // Charge Map0 pourle début du jeu
			  score = 0;
			  niveau = 0;
			  timeDown = 60;
			  timeBegin = hge->Timer_GetTime();
			  rot = 0.0;
			  if(first)
				{
					alea_n = my_rand(); // Génére un nombre entre 1 et 7 compris pour la boule suivante
					coul_bsuivante = attrib_boule(alea_n); // Permet de faire le lien entre les chiffres et les couleurs de boules
					affiche_next(coul_bsuivante);
					coul_bcourante = attrib_boule(alea_c); // Permet d'initialiser la 1er boule 
					first = false;
				}
			   ttest = true; // Pour le son gameover à chaque partie recommencée 
			   hge->System_SetState(HGE_FRAMEFUNC, game); //gaem_int
			   break;
		  case 4:
			   lastid = 0;
			   firstTimeMenu = true;
			   hge->System_SetState(HGE_FRAMEFUNC, menu);
			   break;
		}
	  }
	  else if(id) { lastid=id; gui->Leave(); }

	  hge->Gfx_EndScene();
	  return false;
}

bool menu() 
{
	hge->Gfx_BeginScene();
	bgg->Render(0, 0); // background gumble
	
	if (firstTimeMenu)
	{
	
		// Initialise le GUI
		delete gui;
		gui=new hgeGUI();

		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,385,360,0.0f,"Play 1 Player"));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,385,400,0.1f,"Multiplayer"));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,385,440,0.2f,"Instructions"));
		gui->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,385,480,0.3f,"Credits"));
		gui->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,385,520,0.4f,"Exit"));
		
		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		
		gui->SetFocus(1);
		gui->Enter();
		
		firstTimeMenu = false;
		chan[0] = hge->Stream_Play(myMusic_menu, true);
	}

	float dt=hge->Timer_GetDelta();
	static int bulles = 0;


	frog->RenderStretch(328,250,454,333);	
	frog->Update(dt);

	particleManager->Update(dt);

	if(bulles%3000 == 0)
	{
		bulles = 0;
		particleManager->SpawnPS(&particle_bulles, 340, 260);
	}
	particleManager->Render();

	bulles++;

	gui->SetCursor(spr);
	gui->Render();

	int id;
	 id=gui->Update(dt);
	  if(id == -1)
	  {
		switch(lastid)
		{
		  case 1: 
			  firstTimeMenu = true;
			  LoadMap(0); // Charge Map0 pourle début du jeu
			  score = 0;
			  niveau = 0;
			  timeBegin = hge->Timer_GetTime();
			  rot = 0.0;
			  if(first)
				{
					alea_n = my_rand(); // Génére un nombre entre 1 et 7 compris pour la boule suivante
					coul_bsuivante = attrib_boule(alea_n); // Permet de faire le lien entre les chiffres et les couleurs de boules
					affiche_next(coul_bsuivante);
					coul_bcourante = attrib_boule(alea_c); // Permet d'initialiser la 1er boule 
					first = false;
				}
			   ttest = true; // Pour le son gameover à chaque partie recommencée 
			   hge->System_SetState(HGE_FRAMEFUNC, smenu); 
			   break;
		  case 2:
			    firstTimeMenu = true;
			    hge->System_SetState(HGE_FRAMEFUNC, multiplayer);
			   break;
		  case 3:
			   firstTimeMenu = true;
			   hge->System_SetState(HGE_FRAMEFUNC, instruction);
			   break;
		  case 4:
			   firstTimeMenu = true;
			   hge->System_SetState(HGE_FRAMEFUNC, credit);
			break;
		  case 5: return true;
		}
	  }
	  else if(id) { lastid=id; gui->Leave(); }

	  hge->Gfx_EndScene();
	  return false;
}

//fin du jeux gumble 
bool fin()
{
	hge->Gfx_BeginScene();
	float dt=hge->Timer_GetDelta();
	bgfin->Render(0, 0); // background gumble
	if(premier)
			{	
				hge->Stream_Play(myMusic_menu,true,0);
				// Initialisation de la music
				chan[0] = hge->Stream_Play(l4, true);	
				premier = false;
			}			


		// Mise en place menu 
		if (firstTimeMenu)
		{
			// Chargement sons munu click
			snd=hge->Effect_Load("boing_2.mp3");
		
			// Initialise le GUI
			delete gui;
			gui=new hgeGUI();

			gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,385,360,0.0f,"Back to menu"));
					
			gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		
			gui->Enter();
			hge->Stream_Play(myMusic_menu,true,0);
			hge->Stream_Play(l4,true,0);
			// Initialisation de la music
			chan[0] = hge->Stream_Play(myMusic_fin, true);	
			firstTimeMenu = false;
		}

		// Pour gérer le cursor et l'update des images
		gui->SetCursor(spr);
		gui->Render();
		gui->Update(dt);
	
		int id;
	 id=gui->Update(dt);
	  if(id == -1)
	  {
		switch(lastid)
		{
		  case 1: 
			   hge->System_SetState(HGE_FRAMEFUNC, menu); //gaem_int
			   break;
		}
	  }
	  else if(id) { lastid=id; gui->Leave(); }

		// Mise en place du score
		font1->printf(50, 142, HGETEXT_LEFT,"%d", score);
		// Mise en place du temps
		font1->printf(678,142, HGETEXT_LEFT, "%.2f", tglobal); // .2f pour afficher uniquement 2 décimales
		
		
	hge->Gfx_EndScene();
	return false;
}

bool game()
{
	hge->Gfx_BeginScene();

	if(hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		hge->System_SetState(HGE_FRAMEFUNC, menu);
		lastid = 0;
		firstTimeMenu = true;
	}
	
	// Pour charger le fond et la musique en fonction du niveau
	switch (niveau)
	{
		case 0: {
			// Render graphics
			bgSprite->Render(0, 0); 
			
			if(premier)
			{	
				hge->Stream_Play(myMusic_menu,true,0);
				// Initialisation de la music
				chan[0] = hge->Stream_Play(l4, true);	
				premier = false;
			}			
			break;
		}
		case 1: {
			// Render graphics
			bg4->Render(0, 0); 
			if(premier)
			{	
				hge->Stream_Play(myMusic_menu,true,0);
				// Initialisation de la music
				chan[0] = hge->Stream_Play(l4, true);	
				premier = false;
			}	
			break;
		}
		case 2: {
			// Render graphics
			bgSprite->Render(0, 0);   
			break;
		}
		case 3: {
			// Render graphics
			bgSprite->Render(0, 0);   
			break;
		}
		case 4: {
			// Render graphics
			bgSprite->Render(0, 0);   
			break;
		}
		default : {
			  break;
		}
	}

	float dt=hge->Timer_GetDelta();  //get the time since the last call to FrameFunc
		timeCpt += dt; // on additionne les temps entre les images
		if(timeCpt > timeDown && !loose && !win) // si ce compteur est supérieur aux temps définis pour faire tomber les boules :
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
		if(!loose && !win)
		{
			if( (hge->Input_GetKey()==HGEK_SPACE) && (!blunched_boule))
			{
					rotTd = rot;
					posX_bcourante = posX_depart;
					posY_bcourante = posY_depart;
					blunched_boule=true; // La boule courante a été lancée
					
					// Pour le bruit du tire du canon
					letire=hge->Effect_Load("tire.wav");
					hge->Effect_Play(letire);

					alea_c = alea_n; // Permet de passer la boule suivante à la boule courante

					if(bonus > 0)
					{
						bonus -= 1;
					}
			}
		}
		else if(win)
		{
			if( (hge->Input_GetKey()==HGEK_SPACE) && (!blunched_boule))
			{
				
				timeBegin = hge->Timer_GetTime();
				rot = 0.0;
				if(first)
				{
					alea_n = my_rand(); // Génére un nombre entre 1 et 7 compris pour la boule suivante
					coul_bsuivante = attrib_boule(alea_n); // Permet de faire le lien entre les chiffres et les couleurs de boules
					affiche_next(coul_bsuivante);
					coul_bcourante = attrib_boule(alea_c); // Permet d'initialiser la 1er boule 
					first = false;
				}
				lastid = 0;
				niveau++;
				LoadMap(niveau);
				win = false;
				stop_time = false;

				if(niveau == 1 && hge->Input_GetKey()==HGEK_SPACE)
				{
					firstTimeMenu = true;
					hge->System_SetState(HGE_FRAMEFUNC, fin);
				}

				
			}

			
		}
		else
		{
			if( (hge->Input_GetKey()==HGEK_SPACE) && (!blunched_boule))
			{
				hge->System_SetState(HGE_FRAMEFUNC, menu);
				lastid = 0;
				firstTimeMenu = true;
				loose = false;
				stop_time = false;
			}
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

		particleManager->Update(dt);  //update all particles

		
 
		particleManager->Render();
		bt_menu->Render(640,390);
		gui->SetCursor(spr);
		gui->Render(); // Permet de lancer le GUI et donc d'utiliser d'afficher le curseur.png définit avant
		gui->Update(dt);
		

		b_rouge->Update(dt);  //update the animation
		b_vert->Update(dt);
		b_bleu->Update(dt);
		b_orange->Update(dt);
		b_jaune->Update(dt);
		b_violet->Update(dt);
		b_gris->Update(dt);
		
		hge->Input_GetMousePos(&mouseX, &mouseY);   //get the current mouse position
		// Permet de gérer le bouton menu !
		if(mouseX > 643 && mouseX < 770 && mouseY > 393 && mouseY < 513){
			bt_menu->Update(dt);
			if(hge->Input_GetKey()==HGEK_LBUTTON){
				hge->System_SetState(HGE_FRAMEFUNC, menu);
				lastid = 0;
				firstTimeMenu = true;
			}
		}

		// Pour afficher ou non le bonus (aide au canon)
		if(bonus > 0)
		{
			// test pour afficher la direction du tir
			for(int i = 0; i < 400;i++)
			{
				b_violet->RenderStretch(
					(float)(380+(bouleSizeX/2)-2.5+(i*rot)),
					(float)(480+(bouleSizeX/2)-(i*0.5)),
					(float)(380+(bouleSizeX/2)-2.5+(i*rot)+5),
					(float)(480+(bouleSizeX/2)-(i*0.5)+5));
			}
		}

			if(blunched_boule)
			{
				lunched_boule(coul_bcourante, rotTd);
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
								if(loose == false)
								{
									// Modification des coordonnées des boules si elles sont en train de descendre (descente progressive sur les y)
									y1 -= (bouleSizeX-animDowning);
									y2 -= (bouleSizeX-animDowning);
								}
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
									  b_violet->RenderStretch(x1, y1, x2, y2);break;
								}
						   }
						}
					}
				}
			}	

		bool winTest = true;
		for(int i = 0;i < 88;i++)
		{
			if(pMap[i] != 'x')
			{
				winTest = false;
			}
		}
		if(winTest)
			win = true;
		
		if(win)
		{
			stop_time = true;
			you_win->Render(292,248);
			float end_time = 0;
			end_time = ttime;
			tglobal += end_time;
			font1->printf(678,142, HGETEXT_LEFT, "%.2f", end_time); // .2f pour afficher uniquement 2 décimales
			hge->Stream_Play(myMusic_menu,true,100); // Permet de couper le son quand on perd et de le remettre dans le menu 
				if(ttest)
				{
					swin=hge->Effect_Load("win.wav");
					hge->Effect_Play(swin);
					ttest=false;
				}
		}

		//!\\ A revoir car je dois faire un pointeur pour stopper le temps quand la partie est perdu ou gagné ! :)
		// initialisation du compteur de temps et test pour l'affichage
		if(stop_time == false)
		{
			ttime = hge->Timer_GetTime() - timeBegin;
			font1->SetColor(ARGB(255,1,148,48));  //set color of text to black
			font1->printf(678,142, HGETEXT_LEFT, "%.2f", ttime); // .2f pour afficher uniquement 2 décimales

		}
	
		// Affiche le message GameOver 
		if (loose == true)
		{
			game_over->Render(262,250);
			float end_time = 0;
			end_time = ttime;
			font1->printf(678,142, HGETEXT_LEFT, "%.2f", end_time); // .2f pour afficher uniquement 2 décimales
			hge->Stream_Play(myMusic_menu,true,100); // Permet de couper le son quand on perd et de le remettre dans le menu 
				
				if(ttest)
				{
					sgameover=hge->Effect_Load("gameover.wav");
					hge->Effect_Play(sgameover);
					ttest=false;
				}
		}
	
		// Affichage du score du joueur
		font1->printf(50, 142, HGETEXT_LEFT,"%d", score);

		// Affichage du niveau 
		font1->printf(90, 242, HGETEXT_LEFT,"%d", niveau+1);

		// Permet d'afficher la boule suivante
		affiche_next(coul_bsuivante);
	
		// Affichage du canon
		canon_img->SetHotSpot(65,65);


		// pas très joli mais au moins ça fonctionne
		if(rot > 0)
			canon_img->RenderEx(canonLocX, canonLocY,(float)(atan(-0.5/rot))+(M_PI/2));
		else if(rot < 0)
			canon_img->RenderEx(canonLocX, canonLocY,(float)(atan(-0.5/rot))-(M_PI/2));
		else
			canon_img->RenderEx(canonLocX, canonLocY,(float)(atan(-0.5/rot))-(3*M_PI/2));


		if(hge->Input_GetKeyState(HGEK_RIGHT) && rot < 1)
			rot += (float)0.0005;
		if(hge->Input_GetKeyState(HGEK_LEFT) && rot > -1)
			rot -= (float)0.0005;
	
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


	hge->Gfx_EndScene();
	return false;
}
	
bool instruction()
{
	float dt=hge->Timer_GetDelta();  //get the time since the last call to FrameFunc
	hge->Gfx_BeginScene();
	bgg->Render(0, 0);	// Affichage du fond 

	// Pour gumble la grounouille particule !
	static int bulles = 0;
	frog->RenderStretch(328,250,454,333);	
	frog->Update(dt);

	particleManager->Update(dt);

	if(bulles%3000 == 0)
	{
		bulles = 0;
		particleManager->SpawnPS(&particle_bulles, 340, 260);
	}
	particleManager->Render();

	bulles++;

	fnt->SetColor(0xFFFFFFFF);
	fnt->Render(390, 345, HGETEXT_CENTER, "Instructions\n"
								     	"Shoot the color balls\n\n"
										"\n\n"
										"ESPACE - Shoot\n"
										"Left / Right - Turn the canon\n\n"
										"");
	gui->Render();
	gui->Update(dt);
	gui->SetCursor(spr);
	if(hge->Input_GetKeyState(HGEK_SPACE))
	{
		hge->System_SetState(HGE_FRAMEFUNC, menu);
		lastid = 0;
		firstTimeMenu = true;
	}

	hge->Gfx_EndScene();
	return false;
}

bool credit()
{
	float dt=hge->Timer_GetDelta();  //get the time since the last call to FrameFunc
	hge->Gfx_BeginScene();
	bgg->Render(0, 0);	// Affichage du fond
	
	// Pour gumble la grounouille particule !
	static int bulles = 0;
	frog->RenderStretch(328,250,454,333);	
	frog->Update(dt);

	particleManager->Update(dt);

	if(bulles%3000 == 0)
	{
		bulles = 0;
		particleManager->SpawnPS(&particle_bulles, 340, 260);
	}
	particleManager->Render();

	bulles++;

	fnt->SetColor(0xFFFFFFFF);
	fnt->Render(390, 345, HGETEXT_CENTER, "Credit\n"
			"GUMBLE\n\n"
			"KAWCZAK Clement & ROUSSET Alban\n"
			"\n\n"
			"using HGE and C++\n\n"
			"Space to return menu");
	//hge->System_SetState(HGE_WINDOWED, (MessageBox(NULL, "Run game in windowed mode?", "Windowed?", MB_YESNO | MB_ICONQUESTION) == IDYES) ? true : false);
	gui->SetCursor(spr);
	gui->Render();
	gui->Update(dt);
	
	if(hge->Input_GetKeyState(HGEK_SPACE))
	{
		hge->System_SetState(HGE_FRAMEFUNC, menu);
		lastid = 0;
		firstTimeMenu = true;
	}

	hge->Gfx_EndScene();
	return false;
}

// Menu pour le partie multiplayer
bool multiplayer()
{
	hge->Gfx_BeginScene();
	bgg->Render(0, 0); // background gumble

	if (firstTimeMenu)
	{
		// Chargement sons munu click
		snd=hge->Effect_Load("boing_2.mp3");
		
		// Initialise le GUI
		delete gui;
		gui=new hgeGUI();

		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,385,360,0.0f,"Create a party"));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,385,400,0.1f,"Join a party"));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,385,440,0.2f,"Back to menu"));
		
		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		
		gui->SetFocus(1);
		gui->Enter();
		
		firstTimeMenu = false;
	}

	float dt=hge->Timer_GetDelta();
	static int bulles = 0;


	frog->RenderStretch(328,250,454,333);	
	frog->Update(dt);

	particleManager->Update(dt);

	if(bulles%3000 == 0)
	{
		bulles = 0;
		particleManager->SpawnPS(&particle_bulles, 340, 260);
	}
	particleManager->Render();

	bulles++;

	gui->SetCursor(spr);
	gui->Render();

	int id;
	 id=gui->Update(dt);
	  if(id == -1)
	  {
		switch(lastid)
		{
		  case 1:
			   lastid = 0;
			   firstTimeMenu = true;
			   hge->System_SetState(HGE_FRAMEFUNC, menu);
			   break;
		  case 2:
			   lastid = 0;
			   firstTimeMenu = true;
			   hge->System_SetState(HGE_FRAMEFUNC, menu);
			   break;
		  case 3:
			   lastid = 0;
			   firstTimeMenu = true;
			   hge->System_SetState(HGE_FRAMEFUNC, menu);
			   break;
		}
	  }
	  else if(id) { lastid=id; gui->Leave(); }

	  hge->Gfx_EndScene();
	  return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "hge.log");
	hge->System_SetState(HGE_FRAMEFUNC, menu);
	hge->System_SetState(HGE_TITLE, "Gumble");
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);

	if(hge->System_Initiate())
	{
		Tboule_count = new int[7];
		
		// Chargement du fichier 'ressource.res'
		Res = new hgeResourceManager("resource.res");  
		// Chargement du background
		bgSprite = Res->GetSprite("bgSprite");
		canon_img = Res->GetSprite("img_canon");
		// Chargement image menu 
		bgg = Res->GetSprite("bgg");
		
		// Chargement des images fonds (level)
		bg4 = Res->GetSprite("blevel4");

		//chargement image fin
		bgfin = Res->GetSprite("bgdelafin");

		//Chargement des différentes boules de couleurs
		b_rouge = Res->GetAnimation("br");
		b_vert = Res->GetAnimation("bv");
		b_bleu = Res->GetAnimation("bb");
		b_orange = Res->GetAnimation("bo");
		b_jaune = Res->GetAnimation("bj");
		b_violet = Res->GetAnimation("bvi");
		b_gris = Res->GetAnimation("bgris");


		frog = Res->GetAnimation("frog");

		// Chargement de la police d'écriture
		font1 = Res->GetFont("font1");

		// Chargement du 'GameOver' et du 'YouWin'
		game_over = Res->GetSprite("game_over");
		you_win = Res->GetSprite("you_win");
	
		// Chargement de l'animation du bouton 'menu' sur l'espace de jeux
		bt_menu = Res->GetAnimation("bt_anim");

		// Initialisation de la music
		myMusic_menu = Res->GetStream("theme_menu");
		//Level 1
		l4 = Res->GetStream("mlevel4");
		//music fin
		myMusic_fin = Res->GetStream("lafin");
		

		// Jouer la music de fond 
		//chan[0] = hge->Stream_Play(myMusic_menu, true);
		
		
		
		b_rouge->Play();  //start playback of animation
		b_vert->Play();
		b_bleu->Play();
		b_orange->Play();
		b_jaune->Play();
		b_violet->Play();
		b_gris->Play();
		bt_menu->Play();

		frog ->Play();

		// Chargement textures et sons
		tex=hge->Texture_Load("cursor.png");
		
		
		// Chargement de la police et du sprite du cursor
		fnt=new hgeFont("font1.fnt");
		spr=new hgeSprite(tex,0,0,32,32);

		particle = Res->GetParticleSystem("particle")->info;
		particle_bulles = Res->GetParticleSystem("particle_bulles")->info;
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