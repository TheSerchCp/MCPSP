#include "LoadingScreen.h"
#include "TextureHelper.h"
#include <pspthreadman.h>
#include <pspgu.h>
#include <pspgum.h>
#include <pspdisplay.h>

#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Graphics/Sprite.h>
#include <Aurora/Utils/Logger.h>

// font vars
#define default_size 0.5
#define default_big_size 0.687

#define ENGLISH 1
#define RUSSIAN 2

using namespace Aurora::Graphics;

Sprite* backSprite;
Sprite* backSprite2;

Sprite* loadSprite;
Sprite* subLoadSprite;

Sprite* infoLoad;

Sprite* steveSprite;
Sprite* steveSprite2;
	
Sprite* sheepSprite;
Sprite* sheepSprite2;
Sprite* sheepSprite3;
Sprite* sheepSprite4;
Sprite* sheepSprite5;

Panorama* panorama;

bool LoadingScreen::Nether = false;
bool LoadingScreen::LoadNether = false;
int LoadingScreen::readiness = 0;
int LoadingScreen::stateName = 0;

LoadingScreen::LoadingScreen()
{
	// the loadingscreen is loaded as a thread
	thid_ = sceKernelCreateThread("LoadingThread", RunLoadingScreen, 0x18, 0x10000, THREAD_ATTR_VFPU|THREAD_ATTR_USER, NULL);
	// start the thread
	sceKernelStartThread(thid_, 0, 0);
}


void LoadingScreen::KillLoadingScreen()
{
	// shut down the loading screen again.
	sceKernelTerminateDeleteThread(thid_);
	// free the mem space of the images
	delete backSprite;
	delete backSprite2;
	delete loadSprite;
	delete subLoadSprite;
	delete panorama;
	
	delete steveSprite;
	delete steveSprite2;
		
	delete sheepSprite;
	delete sheepSprite2;
	delete sheepSprite3;
	delete sheepSprite4;
	delete sheepSprite5;
	
	TextureManager::Instance()->RemoveConstTextures();
	
	Utils::Logger::Instance()->LogMessage("Delete Loading Screen \n");
}


int LoadingScreen::RunLoadingScreen(SceSize args, void *argp)
{
	// load up the images
	backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt),0,0,32,32);
	backSprite->Scale(2,2);
	
	backSprite2 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Nether),0,0,32,32);
	backSprite2->Scale(2,2);

	loadSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Load),0,0,16,8);
	loadSprite->Scale(1,0.5f);

    subLoadSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Load),0,8,16,8);
	subLoadSprite->Scale(1,0.5f);

	infoLoad = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::infLoad), true);
	infoLoad->SetPosition(240,136);
	infoLoad->Scale(1,1);
	
	steveSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::steveLoad), true);
	steveSprite->SetPosition(61,109);
	steveSprite->Scale(1,1);
	
	steveSprite2 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::steveLoad2), true);
	steveSprite2->SetPosition(61,109);
	steveSprite2->Scale(1,1);
	
	sheepSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::sheepLoad), true);
	sheepSprite->SetPosition(61,109);
	sheepSprite->Scale(1,1);
	
	sheepSprite2 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::sheepLoad2), true);
	sheepSprite2->SetPosition(61,109);
	sheepSprite2->Scale(1,1);
	
	sheepSprite3 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::sheepLoad3), true);
	sheepSprite3->SetPosition(61,109);
	sheepSprite3->Scale(1,1);
	
	sheepSprite4 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::sheepLoad4), true);
	sheepSprite4->SetPosition(61,109);
	sheepSprite4->Scale(1,1);
	
	sheepSprite5 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::sheepLoad5), true);
	sheepSprite5->SetPosition(61,109);
	sheepSprite5->Scale(1,1);

    int tip = rand() % 6;
	float loadingProcess = 0.0f;
	int stateLoad = 0;
	
	int indexAni = 0;
	float tickAni = 0.0f;
	
	panorama = new Panorama();

	// start the render loop
	while(1)
	{
		RenderManager::InstancePtr()->StartFrame(0.466,0.72,1);
		
		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75, 480.0f / 272.0f, 0.3f, 1000.0f); //Into 3D Mode for panorama
		
		panorama->update(0.02f);
		panorama->render();
		
		sceGumMatrixMode(GU_PROJECTION);
        sceGumLoadIdentity();
        sceGumOrtho(0, 480, 272, 0, -30, 30); //Into 2D Mode for menu

		sceGuDisable(GU_DEPTH_TEST);
		sceGuEnable(GU_BLEND);
		sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 5; y++)
            {
				if(Nether == true)
				{
					backSprite2->SetPosition(x*64,y*64);
					backSprite2->Draw();
				}
				else if(LoadNether == true)
				{
					backSprite->SetPosition(x*64,y*64);
					backSprite->Draw();
				}
				
                sceGuDisable(GU_BLEND);
                sceGuEnable(GU_DEPTH_TEST);
            }
        }

		infoLoad->ConstDraw();

        if(readiness == 0)
        {
            if(loadingProcess < 160)
            {
                loadingProcess += 1.1f;
            }
			
			tickAni += 0.02f;
			
			if(tickAni >= 1.2f)
			{
				if(indexAni < 4) indexAni += 1;
				else if(indexAni == 4) indexAni = 0;
				
				tickAni = 0.0f;
			}
			
			switch(indexAni)
			{
				case 0: 
					sheepSprite->ConstDraw();
				break;
				case 1: 
					sheepSprite2->ConstDraw();
				break;
				case 2: 
					sheepSprite3->ConstDraw();
				break;
				case 3: 
					sheepSprite4->ConstDraw();
				break;
				case 4: 
					sheepSprite5->ConstDraw();
				break;
			}
        }
        else
        {
            if(loadingProcess <= readiness/100.0f*160)
            {
                loadingProcess += 0.65f;
            }
			
			tickAni += 0.02f;
			
			if(tickAni >= 1.2f)
			{
				if(indexAni < 1) indexAni += 1;
				else if(indexAni == 1) indexAni = 0;
				
				tickAni = 0.0f;
			}
			
			switch(indexAni)
			{
				case 0: 
					steveSprite->ConstDraw();
				break;
				case 1: 
					steveSprite2->ConstDraw();
				break;
			}
        }

        subLoadSprite->NewScale(160);
        subLoadSprite->SetPosition(160,150);

        loadSprite->NewScale(loadingProcess);
        loadSprite->SetPosition(160,150);

        if(loadingProcess < 159)
        {
            subLoadSprite->Draw();
            loadSprite->Draw();
        }

		sceGuDisable(GU_BLEND);
		sceGuEnable(GU_DEPTH_TEST);

		//draw subtitles on buttons
        RenderManager::InstancePtr()->SetFontStyle(default_size,0xFFFFFFFF,0,0x00000200|0x00000000);

        if(RenderManager::InstancePtr()->GetFontLanguage() == ENGLISH)
        {
            if(stateName == 0)
            {
                RenderManager::InstancePtr()->DebugPrint(240,90,"Loading world");
            }
            else
            {
				if(Nether == true){
					RenderManager::InstancePtr()->DebugPrint(240,90,"Generating nether");
				}else{
					RenderManager::InstancePtr()->DebugPrint(240,90,"Generating world");
				}       
                switch(stateName)
                {
                    case 1:
                    RenderManager::InstancePtr()->DebugPrint(240,131,"Building terrain %i %%",readiness);
                    break;
                    case 2:
                    RenderManager::InstancePtr()->DebugPrint(240,131,"Digging caves");
                    break;
                    case 3:
                    RenderManager::InstancePtr()->DebugPrint(240,131,"Planting pumpkins");
                    break;
                    case 4:
                    RenderManager::InstancePtr()->DebugPrint(240,131,"Growing trees");
                    break;
                    case 5:
                    RenderManager::InstancePtr()->DebugPrint(240,131,"Placing ore");
                    break;
                    case 6:
                    RenderManager::InstancePtr()->DebugPrint(240,131,"Creating shadow map");
                    break;
                    case 7:
                    RenderManager::InstancePtr()->DebugPrint(240,131,"Saving chunks");
                    break;
                }
            }

            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(1,1,1,1.0f),0,0x00000200|0x00000000);
			
			if(Nether == true){
				RenderManager::InstancePtr()->DebugPrint(240,196,"Please wait 20s - 1min");
			}else{
				switch(tip)
				{
					case 0:
					RenderManager::InstancePtr()->DebugPrint(240,178,"Tip : press R+L to open inventory menu");
					break;
					case 1:
					RenderManager::InstancePtr()->DebugPrint(240,178,"Tip : place items, according to recipe and");
					RenderManager::InstancePtr()->DebugPrint(240,193,"press R to craft recipe item");
					break;
					case 2:
					RenderManager::InstancePtr()->DebugPrint(240,178,"Tip : press up button + R trigger to drop item");
					break;
					case 3:
					RenderManager::InstancePtr()->DebugPrint(240,178,"Tip : aim at crafting table and");
					RenderManager::InstancePtr()->DebugPrint(240,193,"press R to open crafting table menu");
					break;
					case 4:
					RenderManager::InstancePtr()->DebugPrint(240,178,"Tip : take food item in your hand and");
					RenderManager::InstancePtr()->DebugPrint(240,193,"press R trigger to eat it");
					break;
					case 5:
					RenderManager::InstancePtr()->DebugPrint(240,178,"Tip : build a small shelter before the night");
					RenderManager::InstancePtr()->DebugPrint(240,193,"otherwise zombies will slain you");
					break;
				}
			}
        }
        if(RenderManager::InstancePtr()->GetFontLanguage() == RUSSIAN)
        {
            if(stateName == 0)
            {
                RenderManager::InstancePtr()->DebugPrint(240,90,"Cargando mundo");
            }
            else
            {
				if(Nether == true){
					RenderManager::InstancePtr()->DebugPrint(240,90,"Generando nether");
				}else{
					RenderManager::InstancePtr()->DebugPrint(240,90,"Generando mundo");
				}
				
                switch(stateName)
                {
                    case 1:
                    RenderManager::InstancePtr()->DebugPrint(240,131,"Terreno en construccion %i %%",readiness);
                    break;
                    case 2:
                    RenderManager::InstancePtr()->DebugPrint(240,131,"Cavando cuevas");
                    break;
                    case 3:
                    RenderManager::InstancePtr()->DebugPrint(240,131,"Plantando calabazas");
                    break;
                    case 4:
                    RenderManager::InstancePtr()->DebugPrint(240,131,"Arboles en crecimiento");
                    break;
                    case 5:
                    RenderManager::InstancePtr()->DebugPrint(240,131,"Colocación de mineral");
                    break;
                    case 6:
                    RenderManager::InstancePtr()->DebugPrint(240,131,"Generando sombras");
                    break;
                    case 7:
                    RenderManager::InstancePtr()->DebugPrint(240,131,"Guardando chunks");
                    break;
                }
            }

            RenderManager::InstancePtr()->SetFontStyle(default_size,GU_COLOR(0.45f,0.45f,0.45f,1.0f),0,0x00000200|0x00000000);
			
			if(Nether == true)
			{
				RenderManager::InstancePtr()->DebugPrint(240,196,"Por Favor esperar 20s - 1 min");
			}
			else
			{
				switch(tip)
				{
					case 0:
					RenderManager::InstancePtr()->DebugPrint(240,178,"Tip : presione R+L para abrir el inventario");
					break;
					case 1:
					RenderManager::InstancePtr()->DebugPrint(240,178,"Tip : Coloque los elementos, segun la receta y");
					RenderManager::InstancePtr()->DebugPrint(240,193,"presione R para elaborar el articulo de la receta");
					break;
					case 2:
					RenderManager::InstancePtr()->DebugPrint(240,178,"Tip : presione el boton up + R trigger");
					RenderManager::InstancePtr()->DebugPrint(240,193,"para tirar objetos");
					break;
					case 3:
					RenderManager::InstancePtr()->DebugPrint(240,178,"Tip : apunta a la mesa de crafteo y");
					RenderManager::InstancePtr()->DebugPrint(240,193,"presione R para abrir el menu de elaboracion");
					break;
					case 4:
					RenderManager::InstancePtr()->DebugPrint(240,178,"Tip : toma el alimento en tu mano y");
					RenderManager::InstancePtr()->DebugPrint(240,193,"presione el gatillo R para comerlo");
					break;
					case 5:
					RenderManager::InstancePtr()->DebugPrint(240,178,"Tip : construye un pequeño refugio antes de la noche");
					RenderManager::InstancePtr()->DebugPrint(240,193,"de lo contrario, los zombis te mataran");
					break;
				}
			}
        }

        RenderManager::InstancePtr()->SetFontStyle(default_size,0xFFFFFFFF,0,0x00000200|0x00000000);
		RenderManager::InstancePtr()->EndFrame();
	}
	return 0;
}

