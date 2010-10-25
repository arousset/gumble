#include <windows.h>
#include "hge.h"
#include <hgeresource.h>
#include <hgesprite.h>
#include <hgeanim.h>
#include "menuitem.h"
#include <math.h>
#include "hgefont.h"
#include "hgegui.h"

HGE *hge = 0;
hgeResourceManager* Res;
hgeSprite* bgSprite;

// Some resource handles
HEFFECT				snd;
HTEXTURE			tex;

// Pointeurs pour HGE object
hgeGUI				*gui;
hgeFont				*fnt;
hgeSprite			*spr;

bool FrameFunc() // Fonction appelée à chaque image
{
  int id;
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


 return false;
}

bool RenderFunc()
{
	// Render graphics
	hge->Gfx_BeginScene();
	bgSprite->Render(0, 0);
	gui->Render();
	hge->Gfx_EndScene();

	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "hge.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "Gumble");
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
			
		// Chargement textures et sons
		tex=hge->Texture_Load("cursor.png");
		snd=hge->Effect_Load("boing_2.wav");
		
		// Chargement de la police et du sprite du cursor
		fnt=new hgeFont("font1.fnt");
		spr=new hgeSprite(tex,0,0,32,32);

		// Initialise le GUI
		gui=new hgeGUI();

		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,385,360,0.0f,"Play"));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,385,400,0.1f,"Options"));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,385,440,0.2f,"Instructions"));
		gui->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,385,480,0.3f,"Credits"));
		gui->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,385,520,0.4f,"Exit"));

		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(spr);
		gui->SetFocus(1);
		gui->Enter();

		// Let's rock now!
		hge->System_Start();

		// Libération des ressoureces
		delete gui;
	    delete fnt;
	    delete spr;
	    hge->Texture_Free(tex);
	    hge->Effect_Free(snd);
	}
	
	hge->System_Shutdown();
	hge->Release();
	return 0; 
}

