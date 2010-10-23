#include <windows.h>
#include "hge.h"
#include <hgeresource.h>
#include <hgesprite.h>
#include <hgeanim.h>

HGE *hge = 0;
hgeResourceManager* Res;
hgeSprite* bgSprite;



bool FrameFunc() // Fonction appel�e � chaque image
{
	/*if(hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;
	return false;*/

	
 
 
 hge->Gfx_BeginScene();
 hge->Gfx_Clear(0);  //clear the screen, filling it with black
 bgSprite->RenderStretch(0, 0, 800, 600); //render the background sprite stretched
 //bgSprite->Render(0, 0);
 hge->Gfx_EndScene(); 

 return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_WINDOWED, true); // programme fen�tre ou plein �cran ?
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_TITLE, "Gumble"); 
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_LOGFILE,"bootlog.txt");


	if(hge->System_Initiate()) 
	{ 
		Res = new hgeResourceManager("resource.res");  
		bgSprite = Res->GetSprite("bgSprite");
		hge->System_Start();
	}
	else
	{
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL); // Erreur si le syst�me ne s'initialise pas
	}
	
	delete Res;

	hge->System_Shutdown();
	hge->Release();
	return 0; 
}

