#include <windows.h>
#include "hge.h"
#include <hgeresource.h>
#include <hgesprite.h>
#include <hgeanim.h>

HGE *hge = 0;
hgeResourceManager* myRes;
hgeSprite* bgSprite;



bool FrameFunc() // Fonction appelée à chaque image
{
	/*if(hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;
	return false;*/

	
 
 
 hge->Gfx_BeginScene();
 hge->Gfx_Clear(0);  //clear the screen, filling it with black
 bgSprite->RenderStretch(0, 0, 800, 600); //render the background sprite stretched
 hge->Gfx_EndScene(); 

 return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_WINDOWED, true); // programme fenêtre ou plein écran ?
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_TITLE, "Gumble"); 
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);


	if(hge->System_Initiate()) 
	{ 
		myRes = new hgeResourceManager("resource.res");  
		bgSprite = myRes->GetSprite("bgSprite");
		hge->System_Start();
	}
	else
	{
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL); // Erreur si le système ne s'initialise pas
	}
	
	delete myRes;

	hge->System_Shutdown();
	hge->Release();
	return 0; 
}

