#ifndef GAMEMODE_H_
#define GAMEMODE_H_

#include "StatePlay.h"
#include "TextureHelper.h"

#include <math.h>
#include <psptypes.h>

#include <string>
#include <pspiofilemgr.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

class GameMode
{
public:

	GameMode();
    ~GameMode();
	
	static GameMode* Instance();
	static GameMode m_GameMode;
	
	void Init();
	void Update();
	void CleanUp();
	void LoadTextures(int gamemode);
	void DrawSprite(Sprite* sprite);
	void GuiDraw(int gamemode);
	void InventoryRender(int gamemode);
	void InventoryValues(int gamemode);
	void InventoryGetRecipies();
	void ArchievementsMessage(int Achievement);
	void ArchievementsValues(int oldBlock, int Achievement, int Recipes, int CraftItem, CraftWorld *myWorld);
	void ExperienceSystem(int a, int b);
	void Fly();
	
	int AchievementItem;
	bool DrawAchievement;
	
	// survival sprites
	Sprite *hpCellSpriteW;
	Sprite *hpCellSprite;
	Sprite *arCellSprite;
	Sprite *hpSprite;
	Sprite *hpSpriteW;
	Sprite *hpHardSprite;
	Sprite *hpHardSpriteW;
	Sprite *hpHalfSprite;
	Sprite *hpHalfSpriteW;
	Sprite *hpHardHalfSprite;
	Sprite *hpHardHalfSpriteW;
	Sprite *hpVenenoSprite;
	Sprite *hpVenenoHalfSprite;
	Sprite *hpVenenoSpriteW;
	Sprite *hpVenenoHalfSpriteW;
	
	Sprite *hgCellSprite;
	Sprite *hg2CellSprite;
	Sprite *hgSprite;
	Sprite *hgHalfSprite;
	Sprite *hg2Sprite;
	Sprite *hg2HalfSprite;
	Sprite *bubbleSprite;
	Sprite *arSprite;
	Sprite *arHalfSprite;

	Sprite *XPbarSprite;
	Sprite *XPprogressSprite[182];
	
	Sprite *num0Sprite;
	Sprite *num1Sprite;
	Sprite *num2Sprite;
	Sprite *num3Sprite;
	Sprite *num4Sprite;
	Sprite *num5Sprite;
	Sprite *num6Sprite;
	Sprite *num7Sprite;
	Sprite *num8Sprite;
	Sprite *num9Sprite;
	
	Sprite *sliderSprite;
	Sprite *sliderLightedSprite;
	Sprite *tapSe;
	
private:

	CraftWorld *mWorld;
	int currentGameMode;
	
};

#endif
