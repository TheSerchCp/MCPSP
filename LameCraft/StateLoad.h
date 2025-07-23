#ifndef STATELOAD_H_
#define STATELOAD_H_

#include <stdlib.h>

#include <Aurora/Utils/StateManager.h>
#include <Aurora/Utils/GameState.h>

#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Utils/Logger.h>
#include <Aurora/Utils/Timer.h>
#include <Aurora/System/SystemManager.h>
#include <Aurora/Graphics/Models/ObjModel.h>
#include <Aurora/Graphics/Camera.h>
#include <Aurora/Graphics/Sprite.h>

#include "SoundManager.h"
#include "TextureHelper.h"
#include "GlobalFunctions.h"
#include "Panorama.h"

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;

class StateLoad : public CGameState
{
public:
	StateLoad();
	virtual ~StateLoad();

	void Init();
	void Enter();
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(StateManager* sManager);
	void Update(StateManager* sManager);
	void Draw(StateManager* sManager);
	void DrawText(int x,int y, unsigned int color, float size, const char *message, ...);
	void LoadTextures();
	
	float tick;

private:

	RenderManager *mRender;
	SystemManager *mSystemMgr;
	SoundManager *mSoundMgr;
	TextureHelper *mTextureMgr;
	GlobalFunctions *mGlobalFun;
	Panorama* panorama;

	Sprite *load;
	Sprite *load2;
	Sprite *load3;
	Sprite *load4;
	Sprite *load5;
	Sprite *load6;
	Sprite *load7;
	Sprite *load8;
	Sprite *load9;
};

#endif
