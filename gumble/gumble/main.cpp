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
hgeQuad				quad;

// Pointers to the HGE objects we will use
hgeGUI				*gui;
hgeFont				*fnt;
hgeSprite			*spr;

bool FrameFunc() // Fonction appelée à chaque image
{
	/*if(hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;
	return false;*/

	//debut de l'ajout
	float dt=hge->Timer_GetDelta();
	static float t=0.0f;
	float tx,ty;
	int id;
	static int lastid=0;

	// If ESCAPE was pressed, tell the GUI to finish
	if(hge->Input_GetKeyState(HGEK_ESCAPE)) { lastid=5; gui->Leave(); }
	
	// We update the GUI and take an action if
	// one of the menu items was selected
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

	// Here we update our background animation
	t+=dt;
	tx=50*cosf(t/60);
	ty=50*sinf(t/60);

	quad.v[0].tx=tx;        quad.v[0].ty=ty;
	quad.v[1].tx=tx+800/64; quad.v[1].ty=ty;
	quad.v[2].tx=tx+800/64; quad.v[2].ty=ty+600/64;
	quad.v[3].tx=tx;        quad.v[3].ty=ty+600/64;

	// fin ajout
 
 /*
 hge->Gfx_BeginScene();
 hge->Gfx_Clear(0);  //clear the screen, filling it with black
 bgSprite->RenderStretch(0, 0, 800, 600); //render the background sprite stretched
 //bgSprite->Render(0, 0);
 hge->Gfx_EndScene(); */

 return false;
}

bool RenderFunc()
{
	// Render graphics
	hge->Gfx_BeginScene();
	hge->Gfx_RenderQuad(&quad);
	gui->Render();
	fnt->SetColor(0xFFFFFFFF);
	fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d", hge->Timer_GetDelta(), hge->Timer_GetFPS());
	hge->Gfx_EndScene();

	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	/*hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_WINDOWED, true); // programme fenêtre ou plein écran ?
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
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL); // Erreur si le système ne s'initialise pas
	}
	
	delete Res;*/
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "hge_tut06.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "HGE Tutorial 06 - Creating menus");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);

	if(hge->System_Initiate())
	{
		Res = new hgeResourceManager("resource.res");  
		bgSprite = Res->GetSprite("bgSprite");
		//hge->System_Start();
		// Load sound and textures
		quad.tex=hge->Texture_Load("bg.png");
		tex=hge->Texture_Load("cursor.png");
		snd=hge->Effect_Load("menu.wav");
		if(!quad.tex || !tex || !snd)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
			MessageBox(NULL, "Can't load BG.PNG, CURSOR.PNG or MENU.WAV", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
		}

		// Set up the quad we will use for background animation
		quad.blend=BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;

		for(int i=0;i<4;i++)
		{
			// Set up z-coordinate of vertices
			quad.v[i].z=0.5f;
			// Set up color. The format of DWORD col is 0xAARRGGBB
			quad.v[i].col=0xFFFFFFFF;
		}

		quad.v[0].x=0; quad.v[0].y=0; 
		quad.v[1].x=800; quad.v[1].y=0; 
		quad.v[2].x=800; quad.v[2].y=600; 
		quad.v[3].x=0; quad.v[3].y=600; 


		// Load the font, create the cursor sprite
		fnt=new hgeFont("font2.fnt");
		spr=new hgeSprite(tex,0,0,32,32);

		// Create and initialize the GUI
		gui=new hgeGUI();

		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,"Play"));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,240,0.1f,"Options"));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,280,0.2f,"Instructions"));
		gui->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,320,0.3f,"Credits"));
		gui->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,400,360,0.4f,"Exit"));

		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(spr);
		gui->SetFocus(1);
		gui->Enter();

		// Let's rock now!
		hge->System_Start();

		// Delete created objects and free loaded resources
		delete gui;
		delete fnt;
		delete spr;
		hge->Effect_Free(snd);
		hge->Texture_Free(tex);
		hge->Texture_Free(quad.tex);
	}
	hge->System_Shutdown();
	hge->Release();
	return 0; 
}

