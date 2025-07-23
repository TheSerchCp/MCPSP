#include "GameMode.h"

#define ENGLISH 1
#define RUSSIAN 2

GameMode GameMode::m_GameMode;

GameMode* GameMode::Instance()
{
	return &m_GameMode;
}

GameMode::GameMode()
{
	currentGameMode = 0;
}

GameMode::~GameMode()
{

}

void GameMode::Init()
{
	mWorld = new CraftWorld();
	currentGameMode = mWorld->gameModeWorld;
	
	AchievementItem = 0;
	DrawAchievement = false;
}

void GameMode::Update()
{
	
}

// En este apartado se realiza la carga de texturas
// de sprites que se dibujaran en la pantalla
void GameMode::LoadTextures(int gamemode)
{
	// SURVIVAL 0 | CREATIVE 1 | HARDCORE 2
	if(gamemode == 0 || gamemode == 2) gamemode = 0;
	
	int iconS = TextureManager::Instance()->getWidth(TextureHelper::Instance()->GetTexture(TextureHelper::Icons));
	int utilS = TextureManager::Instance()->getWidth(TextureHelper::Instance()->GetTexture(TextureHelper::Utils));
	
	int iconT = TextureHelper::Instance()->GetTexture(TextureHelper::Icons);
	int utilT = TextureHelper::Instance()->GetTexture(TextureHelper::Utils);
	
	// Escala por defecto: (1,1)

	// health sprites
	hpCellSpriteW = new Sprite(utilT,60*utilS/182,36*utilS/182,82*utilS/182,10*utilS/182);
	hpCellSpriteW->SetPosition(100,100);
	
	hpCellSprite = new Sprite(utilT,60*utilS/182,46*utilS/182,82*utilS/182,10*utilS/182);
	hpCellSprite->SetPosition(100,100);
	
	arCellSprite = new Sprite(utilT,60*utilS/182,66*utilS/182,82*utilS/182,10*utilS/182);
	arCellSprite->SetPosition(100,27);

	hpSprite = new Sprite(utilT,0*utilS/182,66*utilS/182,10*utilS/182,10*utilS/182);
	hpSprite->SetPosition(100,22);

	hpSpriteW = new Sprite(utilT,20*utilS/182,66*utilS/182,10*utilS/182,10*utilS/182);
	hpSpriteW->SetPosition(100,22);

	hpHardSprite = new Sprite(utilT,0*utilS/182,56*utilS/182,10*utilS/182,10*utilS/182);
	hpHardSprite->SetPosition(100,22);

	hpHardSpriteW = new Sprite(utilT,20*utilS/182,56*utilS/182,10*utilS/182,10*utilS/182);
	hpHardSpriteW->SetPosition(100,22);

	hpHalfSprite = new Sprite(utilT,10*utilS/182,66*utilS/182,10*utilS/182,10*utilS/182);
	hpHalfSprite->SetPosition(100,22);

	hpHalfSpriteW = new Sprite(utilT,30*utilS/182,66*utilS/182,10*utilS/182,10*utilS/182);
	hpHalfSpriteW->SetPosition(100,22);

	hpHardHalfSprite = new Sprite(utilT,10*utilS/182,56*utilS/182,10*utilS/182,10*utilS/182);
	hpHardHalfSprite->SetPosition(100,22);

	hpHardHalfSpriteW = new Sprite(utilT,30*utilS/182,56*utilS/182,10*utilS/182,10*utilS/182);
	hpHardHalfSpriteW->SetPosition(100,22);

	hpVenenoSprite = new Sprite(iconT,0*utilS/182,56*utilS/182,10*utilS/182,10*utilS/182);
	hpVenenoSprite->SetPosition(100,22);
	
	hpVenenoHalfSprite = new Sprite(iconT,10*utilS/182,56*utilS/182,10*utilS/182,10*utilS/182);
	hpVenenoHalfSprite->SetPosition(100,22);
	
	hpVenenoSpriteW = new Sprite(iconT,0*utilS/182,66*utilS/182,10*utilS/182,10*utilS/182);
	hpVenenoSpriteW->SetPosition(100,22);
	
	hpVenenoHalfSpriteW = new Sprite(iconT,10*utilS/182,66*utilS/182,10*utilS/182,10*utilS/182);
	hpVenenoHalfSpriteW->SetPosition(100,22);

	// hunger sprites
	hgCellSprite = new Sprite(utilT,60*utilS/182,56*utilS/182,82*utilS/182,10*utilS/182);
	hgCellSprite->SetPosition(100,24);
	
	hg2CellSprite = new Sprite(iconT,20*iconS/182,56*iconS/182,82*iconS/182,10*iconS/182);
	hg2CellSprite->SetPosition(100,24);
	
	hgSprite = new Sprite(utilT,30*utilS/182,46*utilS/182,10*utilS/182,10*utilS/182);
	hgSprite->SetPosition(100,26);

	hgHalfSprite = new Sprite(utilT,40*utilS/182,46*utilS/182,10*utilS/182,10*utilS/182);
	hgHalfSprite->SetPosition(100,26);
	
	hg2Sprite = new Sprite(iconT,20*iconS/182,46*iconS/182,10*iconS/182,10*iconS/182);
	hg2Sprite->SetPosition(100,26);

	hg2HalfSprite = new Sprite(iconT,30*iconS/182,46*iconS/182,10*iconS/182,10*iconS/182);
	hg2HalfSprite->SetPosition(100,26);
	
	bubbleSprite = new Sprite(utilT,0*utilS/182,46*utilS/182,10*utilS/182,10*utilS/182);
	bubbleSprite->SetPosition(100,27);

	arSprite = new Sprite(utilT,10*utilS/182,46*utilS/182,10*utilS/182,10*utilS/182);
	arSprite->SetPosition(100,27);

	arHalfSprite = new Sprite(utilT,20*utilS/182,46*utilS/182,10*utilS/182,10*utilS/182);
	arHalfSprite->SetPosition(100,27);
	
	// experience sprites
	XPbarSprite = new Sprite(iconT,0*iconS/182,0*iconS/182,182*iconS/182,5*iconS/182,true);
	XPbarSprite->SetPosition(149,212);
	
	for(int j = 0; j <= 181; j++){
		XPprogressSprite[j] = new Sprite(iconT,0*iconS/182,5*iconS/182,j*iconS/182,5*iconS/182,true);
		XPprogressSprite[j]->SetPosition(149,212);
	}

	// experience numbers
	num0Sprite = new Sprite(iconT,0*iconS/182,30*iconS/182,9*iconS/182,9*iconS/182,true);
	num1Sprite = new Sprite(iconT,9*iconS/182,30*iconS/182,9*iconS/182,9*iconS/182,true);
	num2Sprite = new Sprite(iconT,18*iconS/182,30*iconS/182,9*iconS/182,9*iconS/182,true);
	num3Sprite = new Sprite(iconT,27*iconS/182,30*iconS/182,9*iconS/182,9*iconS/182,true);
	num4Sprite = new Sprite(iconT,36*iconS/182,30*iconS/182,9*iconS/182,9*iconS/182,true);
	num5Sprite = new Sprite(iconT,45*iconS/182,30*iconS/182,9*iconS/182,9*iconS/182,true);
	num6Sprite = new Sprite(iconT,54*iconS/182,30*iconS/182,9*iconS/182,9*iconS/182,true);
	num7Sprite = new Sprite(iconT,63*iconS/182,30*iconS/182,9*iconS/182,9*iconS/182,true);
	num8Sprite = new Sprite(iconT,72*iconS/182,30*iconS/182,9*iconS/182,9*iconS/182,true);
	num9Sprite = new Sprite(iconT,81*iconS/182,30*iconS/182,9*iconS/182,9*iconS/182,true);
	
	sliderSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::invSlider),0,0,12,15);
	sliderSprite->SetPosition(240,136);
	
	sliderLightedSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::invSlider),12,0,12,15);
	sliderLightedSprite->SetPosition(240,136);
	
	tapSe = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::tapsSel));
	tapSe->SetPosition(240,136);

	
}

void GameMode::CleanUp()
{

	delete hpCellSpriteW;
	delete hpCellSprite;
	delete arCellSprite;
	delete hpSprite;
	delete hpSpriteW;
	delete hpHardSprite;
	delete hpHardSpriteW;
	delete hpHalfSprite;
	delete hpHalfSpriteW;
	delete hpHardHalfSprite;
	delete hpHardHalfSpriteW;
	delete hpVenenoSprite;
	delete hpVenenoHalfSprite;
	delete hpVenenoSpriteW;
	delete hpVenenoHalfSpriteW;
	
	delete hgCellSprite;
	delete hg2CellSprite;
	delete hgSprite;
	delete hgHalfSprite;
	delete hg2Sprite;
	delete hg2HalfSprite;
	delete bubbleSprite;
	delete arSprite;
	delete arHalfSprite;
	
	delete XPbarSprite;
	for(int j = 0; j <= 181; j++) delete XPprogressSprite[j];
	
	delete num0Sprite;
	delete num1Sprite;
	delete num2Sprite;
	delete num3Sprite;
	delete num4Sprite;
	delete num5Sprite;
	delete num6Sprite;
	delete num7Sprite;
	delete num8Sprite;
	delete num9Sprite;
	
	delete sliderSprite;
	delete sliderLightedSprite;
	delete tapSe;
}

void GameMode::DrawSprite(Sprite* sprite)
{
    sprite->Draw();
}

void GameMode::GuiDraw(int gamemode)
{
	// SURVIVAL 0 | CREATIVE 1 | HARDCORE 2
	switch(gamemode)
	{
		case 0:
		{
			
		}
		break;
		case 1:
		{
			
		}
		break;
		case 2:
		{

		}
		break;
	}
}

void GameMode::InventoryRender(int gamemode)
{
	// SURVIVAL 0 | CREATIVE 1 | HARDCORE 2	
	if(gamemode != 1)
	{
		
	}
	else
	{
		
	}
}

void GameMode::InventoryValues(int gamemode)
{	
	if(gamemode == 0 || gamemode == 2)
	{
		
	}
}

void GameMode::InventoryGetRecipies()
{

}
//AchievementItem es el item a ser dibujado
void GameMode::ArchievementsMessage(int Achievement)
{	
	switch(Achievement)
	{
		case 1:
			AchievementItem = 298;
		break;
		case 2:
			AchievementItem = 8;
		break;
		case 3:
			AchievementItem = 105;
		break;
		case 4:
			AchievementItem = 255;
		break;
		case 5:
			AchievementItem = 250;
		break;
		case 6:
			AchievementItem = 321;
		break;
		case 7:
			AchievementItem = 251;
		break;
		case 8:
			AchievementItem = 106;
		break;
		case 9:
			AchievementItem = 270;
		break;
		case 10:
			AchievementItem = 288;
		break;
		case 11:
			AchievementItem = 278;
		break;
		case 12:
			AchievementItem = 279;
		break;
	}
	
	DrawAchievement = true;
}
///Logros -oldBlock: si el logro corresponde a un bloque destruido -Achievement: Se consigue de otra manera -Recipes: Si se consigue cocinando un item - CraftItem: si se consigue crafteando un item 
void GameMode::ArchievementsValues(int oldBlock, int Achievement, int Recipes, int CraftItem, CraftWorld *myWorld)
{
	if(oldBlock > 0)
	{
		switch(oldBlock)
		{
			case 8:
				if(myWorld->mainAchievements.GettingWo == 0)
				{
					myWorld->mainAchievements.GettingWo = 1;
					ArchievementsMessage(2);
				}
			break;
			case 30:
				if(myWorld->mainAchievements.GettingWo == 0)
				{
					myWorld->mainAchievements.GettingWo = 1;
					ArchievementsMessage(2);
				}
			break;
			case 31:
				if(myWorld->mainAchievements.GettingWo == 0)
				{
					myWorld->mainAchievements.GettingWo = 1;
					ArchievementsMessage(2);
				}
			break;
			case 43:
				if(myWorld->mainAchievements.Diamond == 0)
				{
					myWorld->mainAchievements.Diamond = 1;
					ArchievementsMessage(12);
				}				
			break;
		}
	}
	else if(Achievement > 0)
	{
		switch(Achievement)
		{
			case 1:
				myWorld->mainAchievements.TakingInventory = 1;
				ArchievementsMessage(1);
			break;
			case 6:
				myWorld->mainAchievements.MonsterHunter = 1;
				ArchievementsMessage(6);
			break;
		}
	}
	else if(Recipes > 0)
	{
		switch(Recipes)
		{
			case 278:
				if(myWorld->mainAchievements.Acquire == 0)
				{
					myWorld->mainAchievements.Acquire = 1;
					ArchievementsMessage(11);
				}
			break;
		}
	}
	else if(CraftItem > 0)
	{
		switch(CraftItem)
		{
			case 105:
				if(myWorld->mainAchievements.Benchmarking == 0)
				{
					myWorld->mainAchievements.Benchmarking = 1;
					ArchievementsMessage(3);
				}
			break;
			case 255:
			{
				if(myWorld->mainAchievements.TimeS == 0)
				{
					myWorld->mainAchievements.TimeS = 1;
					ArchievementsMessage(4);
				}
			}
			break;
			case 250:
			{
				if(myWorld->mainAchievements.TimeM == 0)
				{
					myWorld->mainAchievements.TimeM = 1;
					ArchievementsMessage(5);
				}
			}
			break;
			case 251:
			{
				if(myWorld->mainAchievements.GettingUp == 0)
				{
					myWorld->mainAchievements.GettingUp = 1;
					ArchievementsMessage(7);
				}
			}
			break;
			case 106:
			{
				if(myWorld->mainAchievements.HotTopic == 0)
				{
					myWorld->mainAchievements.HotTopic = 1;
					ArchievementsMessage(8);
				}
			}
			break;
			case 270:
			{
				if(myWorld->mainAchievements.TimeF == 0)
				{
					myWorld->mainAchievements.TimeF = 1;
					ArchievementsMessage(9);
				}
			}
			break;
			case 271:
			{
				if(myWorld->mainAchievements.TimeF == 0)
				{
					myWorld->mainAchievements.TimeF = 1;
					ArchievementsMessage(9);
				}
			}
			break;
			case 272:
			{
				if(myWorld->mainAchievements.TimeF == 0)
				{
					myWorld->mainAchievements.TimeF = 1;
					ArchievementsMessage(9);
				}
			}
			break;
			case 273:
			{
				if(myWorld->mainAchievements.TimeF == 0)
				{
					myWorld->mainAchievements.TimeF = 1;
					ArchievementsMessage(9);
				}
			}
			break;
			case 274:
			{
				if(myWorld->mainAchievements.TimeF == 0)
				{
					myWorld->mainAchievements.TimeF = 1;
					ArchievementsMessage(9);
				}
			}
			break;
			case 288:
			{
				if(myWorld->mainAchievements.BakeBread == 0)
				{
					myWorld->mainAchievements.BakeBread = 1;
					ArchievementsMessage(10);
				}
			}
			break;
		}
	}

}

// SURVIVAL THINGS
void GameMode::ExperienceSystem(int a, int b)
{

}

// CREATIVE THINGS
void GameMode::Fly()
{
	
}