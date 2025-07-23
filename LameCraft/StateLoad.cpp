#include "StateLoad.h"
#include "StateMenu.h"
#include "StatePlay.h"
#include "StateOptions.h"
#include "InputHelper.h"
#include "TextureHelper.h"
#include <Aurora/Utils/Logger.h>

// font vars
#define default_size 0.5
#define default_big_size 0.687

#define ENGLISH 1
#define RUSSIAN 2

StateLoad::StateLoad()
{

}

StateLoad::~StateLoad()
{

}

void StateLoad::Init()
{
	//set render manager instance
	mRender = RenderManager::InstancePtr();
	mSystemMgr = SystemManager::Instance();
	mSoundMgr = SoundManager::Instance();
	mGlobalFun = GlobalFunctions::Instance();
	
	TextureHelper::Instance()->LoadConstTexture();
	LoadTextures();
	tick = 0.0f;
}

void StateLoad::Enter()
{
	mRender->SetOrtho(0,0,0,0,0,0);
}

void StateLoad::CleanUp()
{
	delete load;
	delete load2;
	delete load3;
	delete load4;
	delete load5;
	delete load6;
	delete load7;
	delete load8;
	delete load9;
	delete panorama;
}

void StateLoad::Pause()
{

}

void StateLoad::Resume()
{
	mRender->SetOrtho(0,0,0,0,0,0);
}

void StateLoad::HandleEvents(StateManager* sManager)
{
	if(mGlobalFun->Return == true)
	{	
		CleanUp();
		
		Utils::Logger::Instance()->LogMessage("ClearUp StateLoad \n");
		
		LoadTextures();
		
		Utils::Logger::Instance()->LogMessage("Load Textures StateLoad \n");
		
		mGlobalFun->Return = false;
	}
	
	if(tick < 5.4f) tick  += 0.08f;
	
	if(tick >= 5.4f)
	{
		tick = 0.0f;
		
		if(mGlobalFun->teleported == true)
		{
			if(mGlobalFun->CreateHell == true)
			{
				mGlobalFun->Load = 4;
			}
			else
			{
				mGlobalFun->Load = 2;
			}
		}
		
		if(mGlobalFun->Load == 1)
		{
			if(TextureHelper::Instance()->LoadTex == false) 
			{
				TextureHelper::Instance()->LoadTextureMenu();
			}
			else
			{
				TextureHelper::Instance()->LoadTex = false;
				StateMenu *stateMenu = new StateMenu();
				
				stateMenu->Init();
				
				if(mGlobalFun->Start == false) 
				{
					stateMenu->menuState = -1;
					mGlobalFun->Start = true;
				}
				else
				{
					stateMenu->menuState = 0;
				}
				
				mGlobalFun->Return = true;
				sManager->PushState(stateMenu);
			}
		}
		else if(mGlobalFun->Load == 2)
		{
			if(TextureHelper::Instance()->LoadTex == false)
			{
		
				TextureHelper::Instance()->LoadTextureStatePlay();
			}
			else
			{
				TextureHelper::Instance()->LoadTex = false;
				
				mSoundMgr->StopMenu(); //menu
				StatePlay *statePlay = new StatePlay();
				if (mSoundMgr->Ram32 == true)
				{
					statePlay->WORLD_SIZE = 112;
					statePlay->WORLD_HEIGHT = 112;
					statePlay->CHUNK_SIZE = 7;
				}
				else
				{
					statePlay->WORLD_SIZE = 252;
					statePlay->WORLD_HEIGHT = 112;
					statePlay->CHUNK_SIZE = 14;
				}

				statePlay->LoadMap(mGlobalFun->filename, mGlobalFun->compressed);
				statePlay->InitCamera();
				mGlobalFun->Return = true;
				sManager->PushState(statePlay);
			}
		}
		else if(mGlobalFun->Load == 3)
		{
			if(TextureHelper::Instance()->LoadTex == false)
			{
		
				TextureHelper::Instance()->LoadTextureStatePlay();
			}
			else
			{
				TextureHelper::Instance()->LoadTex = false;
				
				mSoundMgr->StopMenu(); //menu
				StatePlay *statePlay = new StatePlay();
				if (mSoundMgr->Ram32 == true)
				{
					statePlay->WORLD_SIZE = 112;
					statePlay->WORLD_HEIGHT = 112;
					statePlay->CHUNK_SIZE = 7;
				}
				else
				{
					statePlay->WORLD_SIZE = 252;
					statePlay->WORLD_HEIGHT = 112;
					statePlay->CHUNK_SIZE = 14;
				}
				statePlay->InitParametric(mGlobalFun->makeDungeons,mGlobalFun->makeBonus,mGlobalFun->seed_1,mGlobalFun->worldType,mGlobalFun->GameMode,false);
				Utils::Logger::Instance()->LogMessage("Init Parametric \n");
				statePlay->InitCamera();
				statePlay->SetWorldAndSaveName(mGlobalFun->newWorldName,mGlobalFun->nextSaveFileName);
				Utils::Logger::Instance()->LogMessage("Init Parametric \n");
				mGlobalFun->Return = true;
				sManager->PushState(statePlay);
			}
		}
		else if(mGlobalFun->Load == 4)
		{
			if(TextureHelper::Instance()->LoadTex == false)
			{
		
				TextureHelper::Instance()->LoadTextureStatePlay();
			}
			else
			{
				TextureHelper::Instance()->LoadTex = false;
				
				mSoundMgr->StopMenu();
				StatePlay *statePlay = new StatePlay();
				
				if (mSoundMgr->Ram32 == true)
				{
					statePlay->WORLD_SIZE = 112;
					statePlay->WORLD_HEIGHT = 112;
					statePlay->CHUNK_SIZE = 7;
				}
				else
				{
					statePlay->WORLD_SIZE = 252;
					statePlay->WORLD_HEIGHT = 112;
					statePlay->CHUNK_SIZE = 14;
				}
				
				statePlay->InitParametric(true , false, 0, 0, mGlobalFun->GameMode, true);
				statePlay->InitCamera();
				mGlobalFun->Return = true;
				sManager->PushState(statePlay);
			}
		}
		else if(mGlobalFun->Load == 5)
		{
			if(TextureHelper::Instance()->LoadTex == false)
			{
		
				TextureHelper::Instance()->LoadTextureOptions();
			}
			else
			{
				TextureHelper::Instance()->LoadTex = false;
				
				StateOptions *stateOptions = new StateOptions();
				stateOptions->Init();
				mGlobalFun->Return = true;
				sManager->PushState(stateOptions);
			}
		}
	}
}

void StateLoad::Update(StateManager* sManager)
{

}

void StateLoad::Draw(StateManager* sManager)
{
	//start rendering
	mRender->StartFrame(1,1,1);
	
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

	

	//background->ConstDraw();
			
	if(tick > 0.0f && tick < 0.6f) load->ConstDraw();	
	else if(tick > 0.6f && tick < 1.2f) load2->ConstDraw();
	else if(tick > 1.2f && tick < 1.8f) load3->ConstDraw();
	else if(tick > 1.8f && tick < 2.4f) load4->ConstDraw();
	else if(tick > 2.4f && tick < 3.0f) load5->ConstDraw();
	else if(tick > 3.0f && tick < 3.6f) load6->ConstDraw();
	else if(tick > 3.6f && tick < 4.2f) load7->ConstDraw();
	else if(tick > 4.2f && tick < 4.8f) load8->ConstDraw();
	else if(tick > 4.8f && tick < 5.4f) load9->ConstDraw();
	
		
	//end frame
	mRender->EndFrame();
}

void StateLoad::DrawText(int x,int y, unsigned int color, float size, const char *message, ...)
{
    mRender->SetFontStyle(size,color,0,0x00000200|0x00000000);
    mRender->DebugPrint(x,y,message);
}

void StateLoad::LoadTextures()
{
	panorama = new Panorama();
	
	load = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::LoadingCycle), true);
	load->SetPosition(240,136);
	load->Scale(1,1);
	
	load2 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::LoadingCycle2), true);
	load2->SetPosition(240,136);
	load2->Scale(1,1);
	
	load3 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::LoadingCycle3), true);
	load3->SetPosition(240,136);
	load3->Scale(1,1);
	
	load4 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::LoadingCycle4), true);
	load4->SetPosition(240,136);
	load4->Scale(1,1);
	
	load5 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::LoadingCycle5), true);
	load5->SetPosition(240,136);
	load5->Scale(1,1);
	
	load6 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::LoadingCycle6), true);
	load6->SetPosition(240,136);
	load6->Scale(1,1);
	
	load7 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::LoadingCycle7), true);
	load7->SetPosition(240,136);
	load7->Scale(1,1);
	
	load8 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::LoadingCycle8), true);
	load8->SetPosition(240,136);
	load8->Scale(1,1);
	
	load9 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::LoadingCycle9), true);
	load9->SetPosition(240,136);
	load9->Scale(1,1);
}
