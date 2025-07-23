#include "StateMenu.h"
#include "StateOptions.h"
#include "StatePlay.h"
#include "GameMode.h"
#include "LoadingScreen.h"
#include "InputHelper.h"
#include "TextureHelper.h"
#include "StateLoad.h"

#include <Aurora/System/NetworkManager.h>
#include <zlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

// font vars
#define default_size 0.5
#define default_tiny_size 0.4
#define default_big_size 0.687
#define PI 3.1415926535897f

#define ENGLISH 1
#define RUSSIAN 1

#define SURVIVAL 0
#define CREATIVE 1
#define HARDCORE 2

/*
q = э
w = ш
e = е
y = ч
u = y
i = и
o = o
p = п
g = г
j = ж
z = з
x = щ
c = ц
v = в
~ = й

$ = ь
& = ъ
^ = €
@ = ы
# = ю
*/

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;

StateMenu::StateMenu()
{
	
}

StateMenu::~StateMenu()
{

}

void StateMenu::Init()
{
    newW_width = 0;
    newW_height = 0;
    newW_length = 0;

    newW_gameMode = SURVIVAL;
    newW_deleteCaves = true;
	
    conversionStage = 0;
    errorType = 0;

    converterPos = 0;
    schematicExists = false;	//cuevas

    lol = "";
	
	
	
	// Incializamos langManager
	langManager.init();
	// Inicializamos Credits
	credits.Init();
	
	//Cargar el idioma
	langManager.getFolderName();
	langManagerPathStateMenu = langManager.folderNameCD;
	if(langManagerPathStateMenu == "ja_ja") langManagerPathStateMenu = "en_us";
	
	if(!langManager.load_language("Assets/Lang/"+langManagerPathStateMenu+"/general.txt"))
	{
		std::cerr << "Error al cargar el idioma." << std::endl;
    }
	
	// Variables para el gestor de idiomas
	langPos = 0;
	langPosSel = 0;
	langVectorLength = langManager.languageNameVector.size(); //Uso general

    mainStatistics.daysInGame = 0;
    mainStatistics.minutesPlayed = 0;
    mainStatistics.cropsGrowned = 0;
    mainStatistics.soilPlowed = 0;
	
	mainAchievements.TakingInventory = 0;
	mainAchievements.GettingWo = 0;
    mainAchievements.Benchmarking = 0;
	mainAchievements.TimeS = 0;
	mainAchievements.TimeM = 0;
	mainAchievements.MonsterHunter = 0;
	mainAchievements.GettingUp = 0;
	mainAchievements.HotTopic = 0;
	mainAchievements.TimeF = 0;
	mainAchievements.BakeBread = 0;
	mainAchievements.Acquire = 0;
	mainAchievements.Diamond = 0;
    // end

    // »нициализируем переменные опций
    mainOptions.detailedSky = 1;
    mainOptions.smoothLighting = true;
    mainOptions.sounds = 1;
    mainOptions.music = 1;
    mainOptions.fogRendering = 1;
    mainOptions.fastRendering = true;
    mainOptions.newSprintOption = true;
    mainOptions.autoJump = 1;
    mainOptions.fov = 65;
    mainOptions.freezeDayTime = 0;
    mainOptions.worldBlockAnimation = 1;
    mainOptions.particles = 0;
    mainOptions.difficult = 2; // normal
    mainOptions.horizontalViewDistance = 4;
    mainOptions.verticalViewDistance = 1;
    mainOptions.guiDrawing = 1;
	mainOptions.buttonsDrawing = 1;



    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
	mGlobalFun = GlobalFunctions::Instance();

    logoSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Logo),0,0,256,64);
    logoSprite->Scale(1.5f,1.5f);
    logoSprite->SetPosition(240,50);

    rectFilledSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Rectangles),0,0,230,37);
    rectFilledSprite->SetPosition(240,150);
    rectFilledSprite->Scale(2,2);

    rectEmptySprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Rectangles),0,37,230,37);
    rectEmptySprite->SetPosition(240,150);
    rectEmptySprite->Scale(2,2);
	
	rectFilledBigSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::skinselectButtons),0,0,124,24);
    rectFilledBigSprite->SetPosition(240,150);
    rectFilledBigSprite->Scale(1,1);

    rectEmptyBigSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::skinselectButtons),0,24,124,24);
    rectEmptyBigSprite->SetPosition(240,150);
    rectEmptyBigSprite->Scale(1,1);

    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,0,95,12); // stand
    buttonSprite->SetPosition(240,150);
    buttonSprite->Scale(2,2);
	
	sbuttonSpritem = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons2),0,0,148,30); // stand
    sbuttonSpritem->SetPosition(240,150);
    sbuttonSpritem->Scale(1,1);
	
	buttonSpritem = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons2),0,31,148,30); // stand
    buttonSpritem->SetPosition(240,150);
    buttonSpritem->Scale(1,1);
	
	sbuttonSpritem2 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons2),0,61,82,25); // stand
    sbuttonSpritem2->SetPosition(240,150);
    sbuttonSpritem2->Scale(1,1);
	
	buttonSpritem2 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons2),0,86,82,25); // stand
    buttonSpritem2->SetPosition(240,150);
    buttonSpritem2->Scale(1,1);
	
	buttonSprite2 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,0,95,12); // stand
    buttonSprite2->SetPosition(240,150);
    buttonSprite2->Scale(1.5,1.5);
	
	//menu
	menuSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::World));
    menuSprite->Scale(1,1);
	
	textureSelect = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons2),98,113,50,50); // stand
    textureSelect->Scale(1,1);
	
	stextureSelect = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons2),98,63,50,50); // stand
	stextureSelect->Scale(1,1);
	
	menuTexture = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::menuTexture));
    menuTexture->Scale(1,1);

	smenuSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::DeselectedWorld));
    smenuSprite->Scale(1,1);
	
	skinselector = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::skinselector));
    skinselector->Scale(1,1);
	
	xIcon = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Icons2),16,34,15,16);
	TriIcon = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Icons2),0,17,15,16);
	SquIcon = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Icons2),16,17,15,16);
	oIcon = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Icons2),0,34,15,16);

    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,12,95,12); // stand selected
    sbuttonSprite->SetPosition(240,150);
    sbuttonSprite->Scale(2,2);
	
	sbuttonSprite2 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,12,95,12); // stand selected
    sbuttonSprite2->SetPosition(240,150);
    sbuttonSprite2->Scale(1.5,1.5);

    nbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,24,95,12); // dark
    nbuttonSprite->SetPosition(240,150);
    nbuttonSprite->Scale(1.5,1.5);
	
	CheckFo = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),60,60,12,12);
	CheckFo->SetPosition(240,139);
	CheckFo->Scale(1.5,1.5);
						
	Check = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),72,60,12,12);
	Check->SetPosition(240,139);
	Check->Scale(1.5,1.5);

    // small buttons
    buttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::NewButtons),0,0,42,12); // stand
    buttonSmallSprite->SetPosition(240,150);
    buttonSmallSprite->Scale(2,2);

    sbuttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::NewButtons),0,12,42,12); // stand selected
    sbuttonSmallSprite->SetPosition(240,150);
    sbuttonSmallSprite->Scale(2,2);
	
	sbuttonLoadSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::sselectworld)); // stand selected
    sbuttonLoadSprite->SetPosition(240,150);
    sbuttonLoadSprite->Scale(1,1);

    nbuttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::NewButtons),0,24,42,12); // dark
    nbuttonSmallSprite->SetPosition(240,150);
    nbuttonSmallSprite->Scale(2,2);
	
    mbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,36,95,12); // gray
    mbuttonSprite->SetPosition(240,150);
    mbuttonSprite->Scale(2,2);

    smbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,48,95,12); // gray selected
    smbuttonSprite->SetPosition(240,150);
    smbuttonSprite->Scale(2,2);

    backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt),0,0,32,32);
    backSprite->Scale(2,2);
	
	selectworldBox = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::selectworldBox));
    selectworldBox->SetPosition(240,136);
	selectworldBox->Scale(1,1);
	
	worldinfo = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::worldinfo));
    worldinfo->SetPosition(240,136);
	worldinfo->Scale(1,1);
	
	sworldinfo = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::sworldinfo));
    sworldinfo->SetPosition(240,136);
	sworldinfo->Scale(1,1);
	
	lenguageSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons2),0,138,24,25);
	lenguageSprite->SetPosition(0,0);
	lenguageSprite->Scale(1,1);
	
	slenguageSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons2),0,113,24,25);
	slenguageSprite->SetPosition(0,0);
	slenguageSprite->Scale(1,1);

    lamecraftSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::lameCraft),0,0,350,65);
    lamecraftSprite->SetPosition(240,50);
    lamecraftSprite->Scale(1,1);

    blackBackground = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),87,60,8,8);
    blackBackground->SetPosition(240,116);
    blackBackground->Scale(60,22);
	
	blackSkinBackground = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),87,60,4,4);
    blackSkinBackground->SetPosition(240,116);
    blackSkinBackground->Scale(56,45);
	
	///*-----STEVE MODEL-----*///
	
	steveHead = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),8,8,8,8);
	steveHead->Scale(3,3);
	
	steveHeadCapa = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),40,8,8,8);
	steveHeadCapa->Scale(3,3);
	
	steveBody = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),20,20,8,12);
	steveBody->Scale(3,3);
	
	steveHand = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),44,20,4,12);
	steveHand->Scale(3,3);
	
	steveLeg = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),4,20,4,12);
	steveLeg->Scale(3,3);
	
	//Skin1

	skinHead[0] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin1),8,8,8,8);
	skinHead[0]->Scale(3,3);
	
	skinHeadCapa[0] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin1),40,8,8,8);
	skinHeadCapa[0]->Scale(3,3);
	
	skinBody[0] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin1),20,20,8,12);
	skinBody[0]->Scale(3,3);
	
	skinHand[0] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin1),44,20,4,12);
	skinHand[0]->Scale(3,3);
	
	skinLeg[0] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin1),4,20,4,12);
	skinLeg[0]->Scale(3,3);
	
	//Skin2

	skinHead[1] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin2),8,8,8,8);
	skinHead[1]->Scale(3,3);
	
	skinHeadCapa[1] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin2),40,8,8,8);
	skinHeadCapa[1]->Scale(3,3);
	
	skinBody[1] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin2),20,20,8,12);
	skinBody[1]->Scale(3,3);
	
	skinHand[1] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin2),44,20,4,12);
	skinHand[1]->Scale(3,3);
	
	skinLeg[1] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin2),4,20,4,12);
	skinLeg[1]->Scale(3,3);
	
	//Skin3

	skinHead[2] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin3),8,8,8,8);
	skinHead[2]->Scale(3,3);
	
	skinHeadCapa[2] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin3),40,8,8,8);
	skinHeadCapa[2]->Scale(3,3);
	
	skinBody[2] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin3),20,20,8,12);
	skinBody[2]->Scale(3,3);
	
	skinHand[2] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin3),44,20,4,12);
	skinHand[2]->Scale(3,3);
	
	skinLeg[2] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin3),4,20,4,12);
	skinLeg[2]->Scale(3,3);
	
	//Skin4

	skinHead[3] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin4),8,8,8,8);
	skinHead[3]->Scale(3,3);
	
	skinHeadCapa[3] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin4),40,8,8,8);
	skinHeadCapa[3]->Scale(3,3);
	
	skinBody[3] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin4),20,20,8,12);
	skinBody[3]->Scale(3,3);
	
	skinHand[3] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin4),44,20,4,12);
	skinHand[3]->Scale(3,3);
	
	skinLeg[3] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin4),4,20,4,12);
	skinLeg[3]->Scale(3,3);
	
	//Skin5

	skinHead[4] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin5),8,8,8,8);
	skinHead[4]->Scale(3,3);
	
	skinHeadCapa[4] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin5),40,8,8,8);
	skinHeadCapa[4]->Scale(3,3);
	
	skinBody[4] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin5),20,20,8,12);
	skinBody[4]->Scale(3,3);
	
	skinHand[4] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin5),44,20,4,12);
	skinHand[4]->Scale(3,3);
	
	skinLeg[4] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Skin5),4,20,4,12);
	skinLeg[4]->Scale(3,3);
	
	SelectSkin = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),60,60,12,12);
    SelectSkin->Scale(3,3);
	
	// Lang Sprites required
	
	langBoxSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::langBoxTexture));
	langBoxSprite->SetPosition(240,136);
	langBoxSprite->Scale(1,1);
	
	langLogoSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::lameCraft),0,0,350,65);
	langLogoSprite->SetPosition(240,50);
    langLogoSprite->Scale(0.6,0.6);
	
	///*-----END-----*///

    selectPos = 0;

    //load save info
    ScanSaveFiles("Save/");
    //ScanTexturePacks("Assets/Textures/");

    menuState = 0;
    loadSavePos = 0;
    aboutPos = 0;
	about2Pos = 0;

    newWorldName = "New World";
    newWorldNamestr = "";
    newWorldSeed = "";

    size_f = 0.347f;

    //for map generation
    makeDungeons = true;
    makeBonus = false;

    terrainBuilder = 0;
    worldType = 0; // default
    gameMode = SURVIVAL;
    seed_1 = 0;

    SplashNumber = rand() % 16;
    splashSize = 0.0f;

    saveSubmenu = false;
    saveSubMenuSelect = 2;
    generateSelectPose = 0;

    newWorldNamestr = newWorldName.c_str();
    currentVersion = 140;

    //input helper
    InputHelper::Instance()->Init();
    InputHelper::Instance()->Load();

	mGlobalFun->teleported = false;
	mGlobalFun->thisWorld = false;
	mGlobalFun->CreateHell = false;
	mGlobalFun->GameMode = 0;
	mGlobalFun->Load = 1;
	
	mGlobalFun->seed_1 = 0;
	mGlobalFun->makeBonus = false;
	mGlobalFun->makeDungeons = true;
	mGlobalFun->worldType = 0;
	
	mGlobalFun->compressed = true;

	animationscreen = 1;
	fontcoloroption = 0;
	fontcolor = 0;
	srand(time(0));

    tpCurrent = 0;
	tpMax = 0;
	tpEnd = 0;
	tpStart = 0;
	tpPos = 0;
	skinSelectPos = 0;
	skinPos = 0;
	
	yCredits = 0.0f;

	for(int i = 0; i <= 31; i++)
	{
	    worldName[i] = ' ';
	}
	
	//PANORAMA 3D

	panorama = new Panorama();
	
}

void StateMenu::Enter()
{
    mRender->SetOrtho(0,0,0,0,0,0);
    selectPos = 0;
}

void StateMenu::CleanUp()
{
    delete logoSprite;
    delete buttonSprite;
	delete buttonSpritem;
	delete sbuttonSpritem;
	delete buttonSpritem2;
	delete sbuttonSpritem2;
    delete sbuttonSprite;
    delete nbuttonSprite;
	delete buttonSprite2;
	delete sbuttonSprite2; 
    delete mbuttonSprite;
    delete smbuttonSprite;
	delete backSprite;
    delete lenguageSprite;
    delete slenguageSprite;
    delete lamecraftSprite;
	delete SelectSkin;
	
	delete menuSprite;
	delete smenuSprite;
	
	delete skinselector;
	
	delete selectworldBox;
	delete worldinfo;
	delete sworldinfo;
	delete backselectworld;
	
	delete xIcon;
	delete TriIcon;
	delete SquIcon;
	delete oIcon;

    delete buttonSmallSprite;
	delete sbuttonLoadSprite;
    delete sbuttonSmallSprite;
    delete nbuttonSmallSprite;

    delete blackBackground;
	delete blackSkinBackground;
	
    delete steveHead;
    delete steveHeadCapa;
    delete steveBody;
    delete steveHand;
    delete steveLeg;

	for(int is = 0; is <= 4; is ++)
	{
		delete skinHead[is];
		delete skinHeadCapa[is];
		delete skinBody[is];
		delete skinHand[is];
		delete skinLeg[is];
	}
	delete panorama;
	
	delete menuTexture;
	
	delete textureSelect;
	delete stextureSelect;
	delete langBoxSprite;
	delete langLogoSprite;
}

void StateMenu::Pause()
{
	
}

void StateMenu::Resume()
{
    menuState = 0;
    loadSavePos = 0;
    mRender->SetOrtho(0,0,0,0,0,0);
}

void StateMenu::HandleEvents(StateManager* sManager)
{
    //update input
    mSystemMgr->InputUpdate();
	
	
    switch(menuState)
    {
		case -1:// lang manager (select lenguage menu)
		{
			//up, down
			if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
			{
				if(langPosSel == 0){
					langPos--;
					if(langPos < 0) langPos = 0;
				}
				
				if(langPosSel != 0) langPosSel--;
				
				mSoundMgr->PlayMenuSound();
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
			{
				if(langPosSel == 5){
					langPos++;
					if(langPos >(langVectorLength -6)) langPos = langVectorLength - 6;
				}
				
				if(langPosSel != 5) langPosSel++;
				
				mSoundMgr->PlayMenuSound();
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
			{
				// Variables
				int langSelected = langPosSel + langPos;
				
				// Obtenemos el directorio y previo a eso cargamos y guardamos el nuevo idioma
				std::string getFolderName = langManager.languageVector[langSelected];
				TextureHelper::Instance()->SetLangPath(getFolderName);
				langManager.load_language("Assets/Lang/" + getFolderName + "/general.txt");
				
				// Si seleccionamos el idioma Japones cambiamos la font (.pgf)
				if(getFolderName == "ja_ja")
					mRender->japanFont(true);
				else
					mRender->japanFont(false);
				
				// Salir del menu de seleccion de idioma
				menuState = 0;
				langPos = 0;
				langPosSel = 0;
				selectPos = 0;
				SplashNumber = rand() % 16;
			}
			
			// Back button (Salimos sin escojer ningun lenguaje)
			if (mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
			{
                RenderManager::InstancePtr()->defaultFontType = selectPos+1;
				RenderManager::InstancePtr()->SetDefaultFont();
				menuState = 0;
				langPos = 0;
				langPosSel = 0;
				selectPos = 0;
				SplashNumber = rand() % 16;
            }
		}
		break;
		case 0://main menu
		{	

			//up, down
			
			if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
			{
				if(selectPos > 3)
				{
					selectPos = 3;
					
					mSoundMgr->PlayMenuSound();
				}
				else if(selectPos > 0)
				{
					selectPos--;
					
					mSoundMgr->PlayMenuSound();
				}
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
			{
				if(selectPos < 3)
				{
					selectPos++;
					
					mSoundMgr->PlayMenuSound();
				}
			}
			
			if(mSystemMgr->KeyPressed(PSP_CTRL_LEFT))
			{
				if(selectPos == 3)
				{
					selectPos = 4;
					mSoundMgr->PlayMenuSound();
				}
				else if(selectPos == 6)
				{
					selectPos = 3;
					mSoundMgr->PlayMenuSound();
				}
				else if(selectPos == 4)
				{
					selectPos = 5;
					mSoundMgr->PlayMenuSound();
				}
			}
			
			if(mSystemMgr->KeyPressed(PSP_CTRL_RIGHT))
			{
				if(selectPos == 3)
				{
					selectPos = 6;
					mSoundMgr->PlayMenuSound();
				}
				else if(selectPos == 4)
				{
					selectPos = 3;
					mSoundMgr->PlayMenuSound();
				}
				else if(selectPos == 5)
				{
					selectPos = 4;
					mSoundMgr->PlayMenuSound();
				}
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
			{
				if(selectPos == 0) // mundos lista de worlds
				{
					ScanSaveFiles("Save/");

					loadSavePos = 0;
					loadSaveStart = 0;
					loadSaveEnd = saveFilesList.size();
					loadSaveMax = 4;
					if(loadSaveMax > loadSaveEnd)
					loadSaveMax = loadSaveEnd;

					menuState = 1;
				}
				if(selectPos == 1)
				{
					//options
					StateLoad *stateLoad = new StateLoad();
					mGlobalFun->Load = 5;
					stateLoad->Init();
					sManager->PushState(stateLoad);
				}
				if(selectPos == 5)
				{
					//about
					menuState = 3;
					yCredits = 0.0f;
				}
				if(selectPos == 2)
				{
					//textures
					tpMax = 0;
					tpEnd = 0;
					tpStart = 0;
					tpPos = 0;
					tpCurrent = 0;
					tpEnd = texturePackList.size();
					tpMax = 6;
					ScanTexturePacks("Assets/Textures/");

					menuState = 11;
				}
				
				//if(selectPos == 4)
				//{
					//donate
					//menuState = 4;
					//donatePos = 1;
				//}
				
				if(selectPos == 3)
				{
					sManager->Quit();
				}
				
				if(selectPos == 6)
				{
					menuState = 7;
					selectPos = 0;
					
					if(TextureHelper::Instance()->defaultSkin == "skin1.png")
					{
						skinSelectPos = 0;
						skinPos = 0;
					}
					else if(TextureHelper::Instance()->defaultSkin == "skin2.png")
					{
						skinSelectPos = 1;
						skinPos = 1;
					}
					else if(TextureHelper::Instance()->defaultSkin == "skin3.png")
					{
						skinSelectPos = 2;
						skinPos = 2;
					}
					else if(TextureHelper::Instance()->defaultSkin == "skin4.png")
					{
						skinSelectPos = 3;
						skinPos = 3;
					}
					else if(TextureHelper::Instance()->defaultSkin == "skin5.png")
					{
						skinSelectPos = 4;
						skinPos = 4;
					}
	
				}
				
				if(selectPos == 4)
				{
					menuState = -1;
					selectPos = 0;
					mSoundMgr->StopMenu();
				}
				
			}
		}
		break;
		case 1: //select world
		{
			if(saveSubmenu)
			{
				if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
				{
					saveSubMenuSelect--;
					if(saveSubMenuSelect < 1)
						saveSubMenuSelect = 2;

					mSoundMgr->PlayMenuSound();
				}

				if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
				{
					saveSubMenuSelect++;
					if(saveSubMenuSelect > 2)
						saveSubMenuSelect = 1;

					mSoundMgr->PlayMenuSound();
				}

				if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
				{
					if(saveSubMenuSelect == 1) // mundos elliminar
					{
						//remove file
						if(saveFilesList.size() > 0)
						{
							if(saveFilesList[loadSavePos].compression)
							{
								std::string worldName = saveFilesList[loadSavePos].fileName.c_str();
								
								//remove overworld file
								remove(saveFilesList[loadSavePos].fileName.c_str());

								//remove compressed one
								saveFilesList[loadSavePos].fileName += "c";
								remove(saveFilesList[loadSavePos].fileName.c_str());
								//remove compressed two
								saveFilesList[loadSavePos].fileName += "d";
								remove(saveFilesList[loadSavePos].fileName.c_str());	
								
								//remove nether files
								saveFilesList[loadSavePos].fileName = worldName;
								saveFilesList[loadSavePos].fileName += "ch";
								remove(saveFilesList[loadSavePos].fileName.c_str());
							}
							else
							{
								remove(saveFilesList[loadSavePos].fileName.c_str());
							}

							ScanSaveFiles("Save/");

							loadSavePos = 0;
							loadSaveStart = 0;
							loadSaveEnd = saveFilesList.size();
							loadSaveMax = 4;
							if(loadSaveMax > loadSaveEnd) loadSaveMax = loadSaveEnd;

							saveSubmenu = false;
							saveSubMenuSelect = 2;
						}
					}
					if(saveSubMenuSelect == 2)//return
					{
						saveSubMenuSelect = 2;
						saveSubmenu = false;
					}
				}
			}
			else
			{
				
				if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
				{
					generateSelectPose = 0;
					menuState = 5;

					makeBonus = false;
					makeDungeons = true;
					terrainBuilder = 0;
					worldType = 0;

					newWorldName = "New World";
					newWorldSeed = "";
				}
				
				if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
				{
					if(saveFilesList.empty() == false)
					{
						loadSavePos--;

						if(loadSavePos < loadSaveStart)
						{
							loadSaveStart--;
							loadSaveMax--;

							if(loadSaveMax < 4)
							{
								loadSaveStart = 0;
								loadSaveMax = 4;
							}
						}

						if(loadSavePos < 0)
						{
							loadSavePos = saveFilesList.size() - 1;
							loadSaveMax = loadSaveEnd;
							loadSaveStart = loadSaveEnd - 4;
							if(loadSaveStart < 0)
								loadSaveStart = 0;
						}
						
						mSoundMgr->PlayMenuSound();
					}
				}

				if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
				{
					if(saveFilesList.empty() == false)
					{
						loadSavePos++;
						if(loadSavePos == loadSaveMax)
						{
							loadSaveStart++;
							loadSaveMax++;
							if(loadSaveMax > loadSaveEnd)
							{
								loadSaveStart = loadSaveEnd - 4;
								if(loadSaveStart < 0)
									loadSaveStart = 0;
								loadSaveMax = loadSaveEnd;
							}
						}
						if(loadSavePos >= saveFilesList.size())
						{
							loadSavePos = 0;
							loadSaveStart = 0;
							loadSaveMax = 4;
							if(loadSaveMax > loadSaveEnd)
								loadSaveMax = loadSaveEnd;
						}
						
						mSoundMgr->PlayMenuSound();
					}
				}

				if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
				{
					menuState = 0;
					mSoundMgr->PlayMenuSound();
				}

				if(mSystemMgr->KeyPressed(PSP_CTRL_TRIANGLE))
				{
					if(saveFilesList.size() > 0)
					{
						saveSubmenu = true;
						saveSubMenuSelect = 2;
						mSoundMgr->PlayMenuSound();
					}
				}
				
				if(mSystemMgr->KeyPressed(PSP_CTRL_SQUARE))
				{
					if(saveFilesList.size() > 0)	// mundos editar nombre
					{
						mSoundMgr->PlayMenuSound();
						
						char worldNameTemp[50];

						unsigned short test[128];
						unsigned short opis[10] = {'W','o','r','l','d',' ','n','a','m','e'};
						if(mSystemMgr->ShowOSK(opis,test,128) != -1)
						{
							std::string newWorldName = "";
							for(int j = 0; test[j]; j++)
							{
								unsigned c = test[j];

								if(32 <= c && c <= 127) // print ascii only
									newWorldName += c;
							}

							sprintf(worldNameTemp,"%s",newWorldName.c_str());
						}

						int saveVersionTemp = 3;
						char worldGameModeTemp = saveFilesList[loadSavePos].worldGameMode;
						bool locked = saveFilesList[loadSavePos].locked;
						int currentDimensionTemp = saveFilesList[loadSavePos].currentDimension;

						FILE * pFile;
						pFile = fopen(saveFilesList[loadSavePos].fileName.c_str(),"wb");

						if(pFile != NULL)
						{
							//version
							fwrite(&saveVersionTemp, sizeof(int),1,pFile);
							fwrite(&worldGameModeTemp, sizeof(char),1,pFile);
							fwrite(&locked, sizeof(bool),1,pFile);
							fwrite(&currentDimensionTemp, sizeof(int),1,pFile);	
							fwrite(worldNameTemp ,sizeof(char),50,pFile);

							fclose(pFile);
						}

						ScanSaveFiles("Save/");
						
					}
				}

				if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
				{
					// mundos cargar mundo
					if(saveFilesList.size() > 0)
					{
						if(saveFilesList[loadSavePos].locked == false)
						{
							StateLoad *stateLoad = new StateLoad();
							mGlobalFun->filename = saveFilesList[loadSavePos].folderName;
							mGlobalFun->compressed = saveFilesList[loadSavePos].compression;
							mGlobalFun->Load = 2;
							stateLoad->Init();
							sManager->PushState(stateLoad);
						}
					}
				}
			}
		}
		break;
		case 3://about
		{
			yCredits -= 0.5f; 
			
			if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
			{
				menuState = 0;
			}
		}
		break;
		case 4://updateinfo
		{
			if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
			{
				donatePos--;
				if(donatePos < 0)
					donatePos = 1;

				mSoundMgr->PlayMenuSound();
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
			{
				donatePos++;
				if(donatePos > 1)
					donatePos = 0;

				mSoundMgr->PlayMenuSound();
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
			{
				menuState = 0;
			}
			
			if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
			{
				if(donatePos == 1)
				{
					menuState = 0;
				}
			}
		}
		break;	
		case 5://parametric terrain
		{

			if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
			{
	
				switch(generateSelectPose)
				{
					case 3:
					generateSelectPose = 1;
					mSoundMgr->PlayMenuSound();
					case 2:
					generateSelectPose = 1;
					mSoundMgr->PlayMenuSound();
					break;
					default:
						if(generateSelectPose > 0) generateSelectPose --;
						mSoundMgr->PlayMenuSound();
					break;
				}
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
			{
				switch(generateSelectPose)
				{
					case 3:
					generateSelectPose = 4;
					mSoundMgr->PlayMenuSound();
					case 2:
					generateSelectPose = 4;
					mSoundMgr->PlayMenuSound();
					break;
					default:
						if(generateSelectPose < 6) generateSelectPose ++;
						mSoundMgr->PlayMenuSound();
					break;
				}
			}
			
			if(mSystemMgr->KeyPressed(PSP_CTRL_LEFT))
			{
				switch(generateSelectPose)
				{
					case 2:
					generateSelectPose = 3;
					mSoundMgr->PlayMenuSound();
					break;
					case 3:
					generateSelectPose = 2;
					mSoundMgr->PlayMenuSound();
					break;
				}
			}
			
			if(mSystemMgr->KeyPressed(PSP_CTRL_RIGHT))
			{
				switch(generateSelectPose)
				{
					case 3:
					generateSelectPose = 2;
					mSoundMgr->PlayMenuSound();
					break;
					case 2:
					generateSelectPose = 3;
					mSoundMgr->PlayMenuSound();
					break;
				}
			}
			
			if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
			{
				ScanSaveFiles("Save/");

				menuState = 1;
				loadSavePos = 0;
				loadSaveStart = 0;
				loadSaveEnd = saveFilesList.size();
				loadSaveMax = 4;
				if(loadSaveMax > loadSaveEnd)
				loadSaveMax = loadSaveEnd;

				menuState = 1;
			}
			
			if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
			{
				ScanSaveFiles("Save/");

				menuState = 1;
				loadSavePos = 0;
				loadSaveStart = 0;
				loadSaveEnd = saveFilesList.size();
				loadSaveMax = 4;
				if(loadSaveMax > loadSaveEnd)
				loadSaveMax = loadSaveEnd;

				menuState = 0;
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
			{
				if(generateSelectPose == 0)
				{
					newWorldName = "";

					unsigned short test[128];
					unsigned short opis[10] = {'W','o','r','l','d',' ','n','a','m','e'};
					if(mSystemMgr->ShowOSK(opis,test,128) != -1)
					{
						for(int j = 0; j < 14; j++)
						{
							unsigned c = test[j];

							if(32 <= c && c <= 127) // print ascii only
								newWorldName += c;
						}
					}
					newWorldNamestr = newWorldName.c_str();
				}

				if(generateSelectPose == 1)
				{
					seed_1 = 0;
					newWorldSeed = "";

					unsigned short test[128];
					unsigned short opis[10] = {'W','o','r','l','d',' ','s','e','e','d'};
					if(mSystemMgr->ShowOSK(opis,test,128) != -1)
					{

						for(int j = 0; j < 14; j++)
						{
							unsigned c = test[j];

							if(c >= 32 && c <= 127)
							{
								newWorldSeed += c;
							}
						}
						seed_1 = hash(newWorldSeed.c_str(),0);
						//seed_1 = std::atoi(newWorldSeed.c_str());
					}
				}
				
				if(generateSelectPose == 4)
				{
					makeDungeons == true ? makeDungeons = false : makeDungeons = true;
				}
				
				if(generateSelectPose == 5)
				{
					makeBonus == true ? makeBonus = false : makeBonus = true;
				}

				if(generateSelectPose == 2)
				{
					gameMode += 1;
					if (gameMode == 3)
					{
						gameMode = 0;
					}
				}

				if(generateSelectPose == 3)
				{
					worldType += 1;
					if(worldType > 1)
					{
						worldType = 0;
					}
				}

				if(generateSelectPose == 6)
				{
					// Mundos crear nuevo mundo
					// create new world
					// terrainBuilder = 2;
					
					StateLoad *stateLoad = new StateLoad();
					mGlobalFun->makeDungeons = makeDungeons;
					mGlobalFun->makeBonus = makeBonus;
					mGlobalFun->seed_1 = seed_1;
					mGlobalFun->worldType = worldType;
					mGlobalFun->GameMode = gameMode;
					mGlobalFun->newWorldName = newWorldName;
					mGlobalFun->nextSaveFileName = nextSaveFileName;
					mGlobalFun->Load = 3;
					stateLoad->Init();
					sManager->PushState(stateLoad);
					
					seed_1 = 0;
				}
			}
		}
		break;
		case 6://converter //cuevas
		{
			if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
			{
				converterPos--;
				if(converterPos < 0)
					converterPos = 3;

				mSoundMgr->PlayMenuSound();
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
			{
				converterPos++;
				if(converterPos > 3)
					converterPos = 0;

				mSoundMgr->PlayMenuSound();
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
			{
				if(converterPos == 0)
				{
					newW_deleteCaves == true ? newW_deleteCaves = false : newW_deleteCaves = true;
				}
				if(converterPos == 1)
				{
					newW_gameMode == SURVIVAL ? newW_gameMode = CREATIVE : newW_gameMode = SURVIVAL;
				}
				if(converterPos == 2)
				{
					errorType = 0;
					if(schematicExists)
					{
						char buffer[40];
						char empty;
						gzFile saveFile;
						gzFile DataFile;

						/// (1) FETCH SCHEMATIC WIDTH HEIGHT LENGTH AND TAKING ITS BLOCK IDS
						saveFile = gzopen("Converter/world.schematic","rb");
						if(saveFile == 0)
							return;
						//compound
						gzread(saveFile, &empty,sizeof(char));
						gzread(saveFile, &empty,sizeof(char));
						gzread(saveFile, &empty,sizeof(char));

						for(int i = 0; i < 9; i++)
						{
							gzread(saveFile, &empty,sizeof(char));
							lol += empty;
						}

						//height
						gzread(saveFile, &empty,sizeof(char));

						gzread(saveFile, &empty,sizeof(char));
						gzread(saveFile, &empty,sizeof(char));

						for(int i = 0; i < 6; i++)
						{
							gzread(saveFile, &empty,sizeof(char));
							lol += empty;
						}
						gzread(saveFile, &empty,sizeof(char));
						gzread(saveFile, &newW_height,sizeof(char));


						//length
						gzread(saveFile, &empty,sizeof(char));

						gzread(saveFile, &empty,sizeof(char));
						gzread(saveFile, &empty,sizeof(char));

						for(int i = 0; i < 6; i++)
						{
							gzread(saveFile, &empty,sizeof(char));
							lol += empty;
						}
						gzread(saveFile, &empty,sizeof(char));
						gzread(saveFile, &newW_length,sizeof(char));


						//width
						gzread(saveFile, &empty,sizeof(char));

						gzread(saveFile, &empty,sizeof(char));
						gzread(saveFile, &empty,sizeof(char));

						for(int i = 0; i < 5; i++)
						{
							gzread(saveFile, &empty,sizeof(char));
							lol += empty;
						}
						gzread(saveFile, &empty,sizeof(char));
						gzread(saveFile, &newW_width,sizeof(char));

						if(newW_height + newW_length + newW_width != 252+112+252)
						{
							errorType = 1;
							return;
						}

						//blocks
						unsigned char* m_Array1;
						m_Array1 = new block_t[252 * 112 * 252];
						memset(m_Array1, 0, sizeof(unsigned char) * 252 * 252 * 112);

						char need[6];
						bool again = false;
						for(int i = 0; i < 100000000; i++)
						{
							for(int j = 1; j <= 5; j++)
							{
								need[j-1] = need[j];
							}
							gzread(saveFile, &empty,sizeof(char));
							need[5] = empty;

							if(need[0] == 'B' &&
							   need[1] == 'l' &&
							   need[2] == 'o' &&
							   need[3] == 'c' &&
							   need[4] == 'k' &&
							   need[5] == 's')
							{
								i = 100000000;
								break;
							}

							if(need[2] == 'D' &&
							   need[3] == 'a' &&
							   need[4] == 't' &&
							   need[5] == 'a')
							{
								gzread(saveFile, &empty,sizeof(char));
								gzread(saveFile, &empty,sizeof(char));
								gzread(saveFile, &empty,sizeof(char));
								gzread(saveFile, &empty,sizeof(char));

								gzread(saveFile, m_Array1,sizeof(unsigned char)*(252 * 112 * 252));

								again = true;;
								i = 100000000;
								break;
							}
						}

						if(again)
						{
							memset(m_Array1, 0, sizeof(unsigned char) * 252 * 252 * 112);
							for(int j = 0; j <= 6; j++)
							{
								need[j] = '/0';
							}

							for(int i = 0; i < 100000000; i++)
							{
								for(int j = 1; j <= 5; j++)
								{
									need[j-1] = need[j];
								}
								gzread(saveFile, &empty,sizeof(char));
								need[5] = empty;

								if(need[0] == 'B' &&
								   need[1] == 'l' &&
								   need[2] == 'o' &&
								   need[3] == 'c' &&
								   need[4] == 'k' &&
								   need[5] == 's')
								{
									i = 100000000;
									break;
								}
							}
						}
						gzread(saveFile, &empty,sizeof(char));
						gzread(saveFile, &empty,sizeof(char));
						gzread(saveFile, &empty,sizeof(char));
						gzread(saveFile, &empty,sizeof(char));

						gzread(saveFile, m_Array1,sizeof(unsigned char)*(252 * 112 * 252));

						gzclose(saveFile);

						// id converter
						std::vector <unsigned char> id_map;
						id_map.push_back(0); //0
						id_map.push_back(RockBlock::getID());
						id_map.push_back(GrassBlock::getID());
						id_map.push_back(DirtBlock::getID());
						id_map.push_back(CobbleStone::getID());
						id_map.push_back(OakPlanks::getID());
						id_map.push_back(OakSapling::getID());
						id_map.push_back(IronBlock::getID());
						id_map.push_back(WaterBlock::getID());
						id_map.push_back(WaterBlock::getID());
						id_map.push_back(Lava::getID());
						id_map.push_back(Lava::getID());
						id_map.push_back(SandBlock::getID());
						id_map.push_back(Gravel::getID());
						id_map.push_back(GoldBlock::getID());
						id_map.push_back(IronOre::getID());
						id_map.push_back(CoalOre::getID());
						id_map.push_back(WoodBlock::getID());
						id_map.push_back(LeavesBlock::getID());
						id_map.push_back(0);	//sponge
						id_map.push_back(GlassBlock::getID());
						id_map.push_back(LapisOre::getID());
						id_map.push_back(LapisBlock::getID());
						id_map.push_back(0);
						id_map.push_back(SandStone::getID());
						id_map.push_back(NoteBlock::getID());
						id_map.push_back(0); // bed
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(WhiteWoolBlock::getID()); // 35
						id_map.push_back(0);
						id_map.push_back(Flower1::getID());
						id_map.push_back(Flower2::getID());
						id_map.push_back(Mooshroom1::getID());
						id_map.push_back(Mooshroom2::getID());
						id_map.push_back(GoldBlock::getID());
						id_map.push_back(IronBlock::getID());
						id_map.push_back(DoubleSlab::getID());
						id_map.push_back(Slab::getID());
						id_map.push_back(BrickBlock::getID());
						id_map.push_back(TNTBlock::getID());
						id_map.push_back(ShelfBlock::getID());
						id_map.push_back(MossyCobblestone::getID());
						id_map.push_back(Obsidian::getID());
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(BirchPlanks::getID());
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(DiamondOre::getID());
						id_map.push_back(Diamond::getID());
						id_map.push_back(CraftingTable::getID());
						id_map.push_back(WheatBlock6::getID());
						id_map.push_back(Soil::getID());
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(CobbleStone::getID());
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(RedstoneOre::getID());
						id_map.push_back(RedstoneOre::getID());
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(Snow2::getID());
						id_map.push_back(IceBlock::getID());
						id_map.push_back(SnowBlock::getID());
						id_map.push_back(CactusBlock::getID());
						id_map.push_back(ClayBlock::getID());
						id_map.push_back(CaneBlock::getID());
						id_map.push_back(JukeBox::getID());
						id_map.push_back(WoodenFence::getID());
						id_map.push_back(Pumpkin1::getID());
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(JackOLantern1::getID());
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(StoneBrick::getID());
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(IronBars::getID());
						id_map.push_back(GlassPanel::getID());
						id_map.push_back(MelonBlock::getID());
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(BrickBlock::getID());
						id_map.push_back(0);
						id_map.push_back(GrassBlock::getID());
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(0);
						id_map.push_back(OakHalfBlock::getID());


						unsigned char* m_Array2;
						m_Array2 = new block_t[252 * 112 * 252];
						memset(m_Array2, 0, sizeof(unsigned char) * 252 * 252 * 112);

						for(int x = 0; x < 252; x++)
						{
							for(int z = 0; z < 252; z++)
							{
								for(int y = 0; y < 112; y++)
								{
									int take_adress = x+z*252+y*252*252;
									int take_id = m_Array1[take_adress];

									int put_adress = x+y*252+z*252*112;
									int put_id = 0;

									if(take_id < id_map.size())
									{
										put_id = id_map[take_id];
									}

									m_Array2[put_adress] = put_id;
								}
							}
						}

						// creating height map
						unsigned char* m_Heightmap;
						m_Heightmap = new block_t[252 * 252];
						memset(m_Heightmap, 0, sizeof(unsigned char) * 252 * 252);

						for(int x = 0; x < 252; x++)
						{
							for(int z = 0; z < 252; z++)
							{
								int adress = x+z*252;
								for(int y = 111; y >= 0; y--)
								{
									int block_adress = x+y*252+z*252*112;
									unsigned char& block = m_Array2[block_adress];

									if(block == DirtBlock::getID() || block == GrassBlock::getID() || block == SandBlock::getID() || block == RockBlock::getID() || block == Gravel::getID() || block == SandStone::getID())
									{
										m_Heightmap[adress] = y;
										y = -1;
									}
								}
							}
						}

					// cuevas
					if(newW_deleteCaves == true)
					{
						for(int x = 0; x < 252; x++)
						{
							for(int z = 0; z < 252; z++)
							{
								int adress = x+z*252;
								int height = m_Heightmap[adress];
								for(int y = 0; y <= height-1; y++)
								{
									int block_adress = x+y*252+z*252*112;
									unsigned char& block = m_Array2[block_adress];


									if(block != 0)
									{
										if(block != IronBlock::getID() && block != RockBlock::getID() &&  block != DirtBlock::getID() && block != GoldBlock::getID() && block != IronOre::getID() && block != LapisOre::getID() && block != RedstoneOre::getID()
										   && block != Lava::getID() && block != WaterBlock::getID() && block != RedstoneOre::getID() && block != CoalOre::getID() && block != Gravel::getID() && block != DiamondOre::getID()
										   && block != SandStone::getID() && block != SandBlock::getID() && block != Mooshroom1::getID() && block != Mooshroom2::getID())
										{
											y = 100;
											continue;
										}
									}
									if(block == 0 || block == Lava::getID() || block == WaterBlock::getID())
									{
										block = RockBlock::getID();
									}

								}
							}
						}
						free(m_Heightmap);
					}


						/// (2) FETCH SCHEMATIC DATA
						saveFile = gzopen("Converter/world.schematic","rb");
						if(saveFile == 0)
							return;

						for(int j = 0; j <= 6; j++)
						{
							need[j] = '/0';
						}

						//data
						again = false;
						for(int i = 0; i < 100000000; i++)
						{
							for(int j = 1; j <= 5; j++)
							{
								need[j-1] = need[j];
							}
							gzread(saveFile, &empty,sizeof(char));
							need[5] = empty;

							if(need[0] == 'B' &&
							   need[1] == 'l' &&
							   need[2] == 'o' &&
							   need[3] == 'c' &&
							   need[4] == 'k' &&
							   need[5] == 's')
							{
								again = true;
								i = 100000000;

								gzread(saveFile, &empty,sizeof(char));
								gzread(saveFile, &empty,sizeof(char));
								gzread(saveFile, &empty,sizeof(char));
								gzread(saveFile, &empty,sizeof(char));

								gzread(saveFile, m_Array1,sizeof(unsigned char)*(252 * 112 * 252));

								break;
							}

							if(need[2] == 'D' &&
							   need[3] == 'a' &&
							   need[4] == 't' &&
							   need[5] == 'a')
							{
								i = 100000000;
								break;
							}
						}

						if(again)
						{
							memset(m_Array1, 0, sizeof(unsigned char) * 252 * 252 * 112);
							for(int j = 0; j <= 6; j++)
							{
								need[j] = '/0';
							}

							for(int i = 0; i < 100000000; i++)
							{
								for(int j = 1; j <= 5; j++)
								{
									need[j-1] = need[j];
								}
								gzread(saveFile, &empty,sizeof(char));
								need[5] = empty;

								if(need[2] == 'D' &&
								   need[3] == 'a' &&
								   need[4] == 't' &&
								   need[5] == 'a')
								{
									i = 100000000;
									break;
								}
							}
						}

						gzread(saveFile, &empty,sizeof(char));
						gzread(saveFile, &empty,sizeof(char));
						gzread(saveFile, &empty,sizeof(char));
						gzread(saveFile, &empty,sizeof(char));

						memset(m_Array1, 0, sizeof(unsigned char) * 252 * 252 * 112);
						gzread(saveFile, m_Array1,sizeof(unsigned char)*(252 * 112 * 252));

						gzclose(saveFile);

						// place correct blocks in our world using schematic blocks data
						for(int x = 0; x < 252; x++)
						{
							for(int z = 0; z < 252; z++)
							{
								for(int y = 0; y < 112; y++)
								{
									int address = x+y*252+z*252*112;
									int data_address = x+z*252+y*252*252;
									unsigned char& block = m_Array2[address];
									unsigned char data = m_Array1[data_address];

									if(y < 111)
									{
										int up_address = x+(y+1)*252+z*252*112;
										unsigned char& up_block = m_Array2[up_address];

										if(up_block == Snow2::getID() && (block == GrassBlock::getID() || block == DirtBlock::getID()))
										{
											block = SnowSoil::getID();
											continue;
										}
									}

									if(block == LeavesBlock::getID())
									{
										if(data == 1 || data == 5 || data == 9 || data == 13)
										{
											block = SpruceLeaves::getID();
										}
										if(data == 2 || data == 6 || data == 10 || data == 14)
										{
											block = BirchLeaves::getID();
										}
										continue;
									}

									if(block == OakPlanks::getID())
									{
										if(data == 1)
										{
											block = SprucePlanks::getID();
										}
										if(data == 2)
										{
											block = BirchPlanks::getID();
										}
										continue;
									}
									if(block == WoodBlock::getID())
									{
										if(data == 1)
										{
											block = DarkWoodBlock::getID();
										}
										if(data == 2)
										{
											block = WhiteWoodBlock::getID();
										}
										continue;
									}
									if(block == WheatBlock6::getID())
									{
										if(data == 0)
										{
											block = WheatBlock1::getID();
										}
										if(data == 1 || data == 2)
										{
											block = WheatBlock2::getID();
										}
										if(data == 3 || data == 4)
										{
											block = WheatBlock3::getID();
										}
										if(data >= 5)
										{
											block = WheatBlock4::getID() + (data-5);
										}
										continue;
									}

									if(block == DoubleSlab::getID())
									{
										if(data == 1)
										{
											block = SandStone::getID();
										}
										if(data == 2)
										{
											block = OakPlanks::getID();
										}
										if(data == 3)
										{
											block = CobbleStone::getID();
										}
										if(data == 4)
										{
											block = BrickBlock::getID();
										}
										if(data == 5)
										{
											block = StoneBrick::getID();
										}
										continue;
									}
									if(block == Slab::getID())
									{
										if(data == 2)
										{
											block = OakHalfBlock::getID();
										}
										if(data == 3)
										{
											block = CobbleHalfBlock::getID();
										}
										if(data == 4)
										{
											block = BrickHalfBlock::getID();
										}
										if(data == 5)
										{
											block = HalfStoneBrick::getID();
										}
										continue;
									}
									if(block == OakHalfBlock::getID())
									{
										if(data == 1)
										{
											block = SpruceHalfBlock::getID();
										}
										if(data == 2)
										{
											block = BirchHalfBlock::getID();
										}
										continue;
									}
									if(block == StoneBrick::getID())
									{
										if(data == 2)
										{
											block = CrackedStoneBrick::getID();
										}
										if(data == 3)
										{
											block = CarvedStoneBrick::getID();
										}
										continue;
									}
									if(block == Pumpkin1::getID())
									{
										block = Pumpkin1::getID() + data;
										continue;
									}
									if(block == WhiteWoolBlock::getID())
									{
										if(data == 1)
										{
											block = OrangeWoolBlock::getID();
										}
										if(data == 2)
										{
											block = VioletWoolBlock::getID();
										}
										if(data == 3)
										{
											block = LightBlueWoolBlock::getID();
										}
										if(data == 4)
										{
											block = YellowWoolBlock::getID();
										}
										if(data == 5)
										{
											block = GreenWoolBlock::getID();
										}
										if(data == 6)
										{
											block = PinkWoolBlock::getID();
										}
										if(data == 7)
										{
											block = GrayWoolBlock::getID();
										}
										if(data == 8)
										{
											block = LightGrayWoolBlock::getID();
										}
										if(data == 9)
										{
											block = PastelWoolBlock::getID();
										}
										if(data == 10)
										{
											block == VioletWoolBlock::getID();
										}
										if(data == 11)
										{
											block = BlueWoolBlock::getID();
										}
										if(data == 12)
										{
											block = BrownWoolBlock::getID();
										}
										if(data == 13)
										{
											block = DarkGreenWoolBlock::getID();
										}
										if(data == 14)
										{
											block = RedWoolBlock::getID();
										}
										if(data == 15)
										{
											block = BlackWoolBlock::getID();
										}
										continue;
									}
								}
							}
						}

						free(m_Array1);
						saveFile=0;

						/// (2.1) SET SUITABLE PLAYER POSITION

						Vector3 playerPos = Vector3(128,69,128);
						for(int y = 111; y >= 40; y--)
						{
							int address = 128+y*252+128*252*112;
							unsigned char block = m_Array2[address];

							if(block != 0)
							{
								playerPos = Vector3(128.5f,y+1.7f,128.5f);
								break;
							}
						}


						/// (3) SAVE WORLD
						std::string filename = nextSaveFileName;
						std::string filedata = filename + "cd";
						//first save version and name on normal file
						FILE * pFile;
						pFile = fopen(filename.c_str(),"wb");

						if(pFile == NULL)
							return;

						//version
						int _worldVersion = 150;
						fwrite(&_worldVersion,sizeof(int),1,pFile);

						//game mode
						fwrite(&newW_gameMode,sizeof(char),1,pFile);

						//game mode
						bool locked = 0;
						fwrite(&locked,sizeof(bool),1,pFile);
						
						bool createdHell = false;
						char currentWorld = 0;
						fwrite(&currentWorld,sizeof(char),1,pFile);
						fwrite(&createdHell,sizeof(bool),1,pFile);

						//name
						char _worldName[50];
						_worldName[0] = 'C';
						_worldName[1] = 'o';
						_worldName[2] = 'n';
						_worldName[3] = 'v';
						_worldName[4] = 'e';
						_worldName[5] = 'r';
						_worldName[6] = 't';
						_worldName[7] = 'e';
						_worldName[8] = 'd';
						_worldName[9] = 1+rand()%126;
						_worldName[10] = '\0';
						fwrite(_worldName,sizeof(char),50,pFile);

						//close file
						fclose(pFile);

						DataFile = gzopen(filedata.c_str(),"wb");
						if(DataFile == 0)
							return;
						
						gzwrite(DataFile, &mainStatistics,sizeof(st));
						
						gzwrite(DataFile, &mainAchievements,sizeof(ac));

						gzwrite(DataFile, &mainOptions,sizeof(opt));


						short invId[36];
						short invAm[36];
						bool invSt[36];
						short armorId[4];
						short armorAm[4];
						bool armorSt[4];

						for(int o = 0; o <= 35; o += 1) // »нициализаци€ инвентар€
						{
							invAm[o] = -1; //  оличество вещей в €чейки = -1 (0)
							invId[o] = -1; // Id вещей в €чейке = -1 (€чейка пуста)
							invSt[o] = false; // ¬ещь в €чейке не стакаетс€ (по умолчанию)
						}

						for(int o = 0; o <= 3; o += 1)
						{
							armorId[o] = 324+o;
							armorAm[o] = -1;
							armorSt[o] = false;
						}
						gzwrite(DataFile, &invId,sizeof(short)*(36));

						gzwrite(DataFile, &invAm,sizeof(short)*(36));

						gzwrite(DataFile, &invSt,sizeof(bool)*(36));

						gzwrite(DataFile, &armorId,sizeof(short)*(4));

						gzwrite(DataFile, &armorAm,sizeof(short)*(4));

						gzwrite(DataFile, &armorSt,sizeof(bool)*(4));

						float HP = 20;
						gzwrite(DataFile, &HP,sizeof(unsigned int));

						float HG = 20;
						gzwrite(DataFile, &HG,sizeof(unsigned int));

						float OS = 10;
						gzwrite(DataFile, &OS,sizeof(unsigned int));
						
						int EXP = 0;
						gzwrite(DataFile, &EXP,sizeof(int));
						
						int EXPcount = 0;
						gzwrite(DataFile, &EXPcount,sizeof(int));
						
						//close file
						gzclose(DataFile);
						DataFile=0;
						
						//now save compressed map info
						filename = filename + "c";

						saveFile = gzopen(filename.c_str(),"wb");
						if(saveFile == 0)
							return;
						
						//player pos

						gzwrite(saveFile, &playerPos.x,sizeof(float));
						gzwrite(saveFile, &playerPos.y,sizeof(float));
						gzwrite(saveFile, &playerPos.z,sizeof(float));

						//player spawn pos
						Vector3 playerSpawnPointPosition = playerPos;
						gzwrite(saveFile, &playerSpawnPointPosition.x,sizeof(float));
						gzwrite(saveFile, &playerSpawnPointPosition.y,sizeof(float));
						gzwrite(saveFile, &playerSpawnPointPosition.z,sizeof(float));

						//snow biome pos
						Vector3 snowBiomePosition = Vector3(0,0,0);
						float snowBiomeRadius = -1;
						gzwrite(saveFile, &snowBiomePosition.x,sizeof(float));
						gzwrite(saveFile, &snowBiomePosition.z,sizeof(float));
						gzwrite(saveFile, &snowBiomeRadius,sizeof(float));

						//desert biome pos
						Vector3 desertBiomePosition = Vector3(0,0,0);
						float desertBiomeRadius = -1;
						gzwrite(saveFile, &desertBiomePosition.x,sizeof(float));
						gzwrite(saveFile, &desertBiomePosition.z,sizeof(float));
						gzwrite(saveFile, &desertBiomeRadius,sizeof(float));
						
						//forest biome pos
						//Vector3 forestBiomePosition = Vector3(0,0,0);
						//float forestBiomeRadius = -1;
						//gzwrite(saveFile, &forestBiomePosition.x,sizeof(float));
						//gzwrite(saveFile, &forestBiomePosition.z,sizeof(float));
						//gzwrite(saveFile, &forestBiomeRadius,sizeof(float));

						//size
						int WORLD_SIZE = 252;
						gzwrite(saveFile, &WORLD_SIZE,sizeof(int));

						//size
						int WORLD_HEIGHT = 112;
						gzwrite(saveFile, &WORLD_HEIGHT,sizeof(int));

						//chunksize
						int CHUNK_SIZE = 14;
						gzwrite(saveFile, &CHUNK_SIZE,sizeof(int));

						//cubes
						gzwrite(saveFile, m_Array2,sizeof(unsigned char)*(WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE));

						for(int x = 0; x < 252; x++)
						{
							for(int z = 0; z < 252; z++)
							{
								for(int y = 0; y < 112; y++)
								{
									m_Array2[z*112*252+y*252+x] = 0;
								}
							}
						}

						//settings
						gzwrite(saveFile, m_Array2,sizeof(unsigned char)*(WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE));

						float worldDayTime = 12.0f;
						//world time
						gzwrite(saveFile, &worldDayTime,sizeof(float));
						//sun time
						//gzwrite(saveFile, &sunTime,sizeof(float));

						float brightFactor = 1.0f;
						gzwrite(saveFile, &brightFactor,sizeof(float));

						float starsFactor = 0.0f;
						gzwrite(saveFile, &starsFactor,sizeof(float));

						int worldSeed = 0;
						gzwrite(saveFile, &worldSeed,sizeof(int));

						float skyTime = 112.0f;
						gzwrite(saveFile, &skyTime,sizeof(float));
						
						int savedWeatherType = 0;
						gzwrite(saveFile, &savedWeatherType,sizeof(int));

						float savedWeatherDuration = 600+rand()%300;
						gzwrite(saveFile, &savedWeatherDuration,sizeof(float));

						int null_var = 0;
						gzwrite(saveFile, &null_var,sizeof(int));

						gzwrite(saveFile, &null_var,sizeof(int));

						gzwrite(saveFile, &null_var,sizeof(int));

						gzwrite(saveFile, &null_var,sizeof(int));

						gzwrite(saveFile, &null_var,sizeof(int));

						gzwrite(saveFile, &null_var,sizeof(int));

						gzwrite(saveFile, &null_var,sizeof(int));

						gzwrite(saveFile, &null_var,sizeof(int));

						gzwrite(saveFile, &null_var,sizeof(int));

						gzwrite(saveFile, &null_var,sizeof(int));

						gzwrite(saveFile, &null_var,sizeof(int));

						//close file
						gzclose(saveFile);
						saveFile=0;

						free(m_Array2);
					}
				}
				if(converterPos == 3)
				{
					menuState = 3;
				}
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
			{
				menuState = 3;
			}
		}
		break;
		case 7://player options
		{
			
			if(mSystemMgr->KeyPressed(PSP_CTRL_LEFT))
			{	
				skinPos--;
				if(skinPos < 0)
					skinPos = 4;
				
				mSoundMgr->PlayMenuSound();
			}
			
			if(mSystemMgr->KeyPressed(PSP_CTRL_RIGHT))
			{	
				skinPos++;
				if (skinPos > 4) skinPos = 0;
				
				mSoundMgr->PlayMenuSound();
			}
			
			if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
			{
				menuState = 0;
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
			{

				switch(skinPos)
				{
					case 0:
						TextureHelper::Instance()->SetSkin("skin1.png");
						skinSelectPos = 0;
						
						delete steveHead;
						delete steveHeadCapa;
						delete steveBody;
						delete steveHand;
						delete steveLeg;
						
						steveHead = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),8,8,8,8);
						steveHead->Scale(3,3);
						
						steveHeadCapa = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),40,8,8,8);
						steveHeadCapa->Scale(3,3);
						
						steveBody = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),20,20,8,12);
						steveBody->Scale(3,3);
						
						steveHand = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),44,20,4,12);
						steveHand->Scale(3,3);
						
						steveLeg = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),4,20,4,12);
						steveLeg->Scale(3,3);
					break;
					case 1:
						TextureHelper::Instance()->SetSkin("skin2.png");
						skinSelectPos = 1;
						
						delete steveHead;
						delete steveHeadCapa;
						delete steveBody;
						delete steveHand;
						delete steveLeg;
						
						steveHead = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),8,8,8,8);
						steveHead->Scale(3,3);
						
						steveHeadCapa = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),40,8,8,8);
						steveHeadCapa->Scale(3,3);
						
						steveBody = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),20,20,8,12);
						steveBody->Scale(3,3);
						
						steveHand = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),44,20,4,12);
						steveHand->Scale(3,3);
						
						steveLeg = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),4,20,4,12);
						steveLeg->Scale(3,3);
					break;
					case 2:
						TextureHelper::Instance()->SetSkin("skin3.png");
						skinSelectPos = 2;
						
						delete steveHead;
						delete steveHeadCapa;
						delete steveBody;
						delete steveHand;
						delete steveLeg;
						
						steveHead = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),8,8,8,8);
						steveHead->Scale(3,3);
						
						steveHeadCapa = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),40,8,8,8);
						steveHeadCapa->Scale(3,3);
						
						steveBody = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),20,20,8,12);
						steveBody->Scale(3,3);
						
						steveHand = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),44,20,4,12);
						steveHand->Scale(3,3);
						
						steveLeg = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),4,20,4,12);
						steveLeg->Scale(3,3);
					break;
					case 3:
						TextureHelper::Instance()->SetSkin("skin4.png");
						skinSelectPos = 3;
						
						delete steveHead;
						delete steveHeadCapa;
						delete steveBody;
						delete steveHand;
						delete steveLeg;
						
						steveHead = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),8,8,8,8);
						steveHead->Scale(3,3);
						
						steveHeadCapa = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),40,8,8,8);
						steveHeadCapa->Scale(3,3);
						
						steveBody = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),20,20,8,12);
						steveBody->Scale(3,3);
						
						steveHand = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),44,20,4,12);
						steveHand->Scale(3,3);
						
						steveLeg = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),4,20,4,12);
						steveLeg->Scale(3,3);
					break;
					case 4:
						TextureHelper::Instance()->SetSkin("skin5.png");
						skinSelectPos = 4;
						
						delete steveHead;
						delete steveHeadCapa;
						delete steveBody;
						delete steveHand;
						delete steveLeg;
						
						steveHead = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),8,8,8,8);
						steveHead->Scale(3,3);
						
						steveHeadCapa = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),40,8,8,8);
						steveHeadCapa->Scale(3,3);
						
						steveBody = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),20,20,8,12);
						steveBody->Scale(3,3);
						
						steveHand = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),44,20,4,12);
						steveHand->Scale(3,3);
						
						steveLeg = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),4,20,4,12);
						steveLeg->Scale(3,3);
					break;
				}
			}
		}
		break;	
		case 10:
		{
			if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
			{
				saveSubMenuSelect == 0 ? saveSubMenuSelect = 1 : saveSubMenuSelect = 0;

				mSoundMgr->PlayMenuSound();
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
			{
				saveSubMenuSelect == 1 ? saveSubMenuSelect = 0 : saveSubMenuSelect = 1;

				mSoundMgr->PlayMenuSound();
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
			{
				char worldNameTemp[50];
				for(char i = 0; i <= 49; i++)
				{
					worldNameTemp[i] = saveFilesList[loadSavePos].worldName[i];
				}

				int saveVersionTemp = 3;
				char worldGameModeTemp = saveSubMenuSelect;
				bool locked = saveFilesList[loadSavePos].locked;
				int currentDimensionTemp = saveFilesList[loadSavePos].currentDimension;
				
				FILE * pFile;
				pFile = fopen(saveFilesList[loadSavePos].fileName.c_str(),"wb");

				if(pFile != NULL)
				{
					//version
					fwrite(&saveVersionTemp, sizeof(int),1,pFile);
					fwrite(&worldGameModeTemp, sizeof(char),1,pFile);
					fwrite(&locked, sizeof(bool),1,pFile);
					fwrite(&currentDimensionTemp, sizeof(int),1,pFile);
					fwrite(worldNameTemp ,sizeof(char),50,pFile);

					fclose(pFile);
				}

				ScanSaveFiles("Save/");

				menuState = 1;
			}
		}
		break;
		case 11://texturepack
		{
			if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
			{
				tpPos--;
				if(tpPos < tpStart)
				{
					tpStart--;
					tpMax--;

					if(tpMax < 6)
					{
						tpStart = 0;
						tpMax = 6;
					}
				}

				if(tpPos < 0)
				{
					tpPos = texturePackList.size() - 1;
					tpMax = tpEnd;
					tpStart = tpEnd - 6;
					if(tpStart < 0)
						tpStart = 0;
				}
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
			{
				tpPos++;
				if(tpPos == tpMax)
				{
					tpStart++;
					tpMax++;
					if(tpMax > tpEnd)
					{
						tpStart = tpEnd - 6;
						if(tpStart < 0)
						{
							tpStart = 0;
						}
						tpMax = tpEnd;
					}
				}
				if(tpPos >= texturePackList.size())
				{
					tpPos = 0;
					tpStart = 0;
					tpMax = 6;
					if(tpMax > tpEnd)
						tpMax = tpEnd;
				}
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
			{
				menuState = 0;
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
			{
				if(texturePackList.empty() == false)
				{
					TextureHelper::Instance()->SetTexturePack(texturePackList[tpPos].name);
					tpCurrent = tpPos;
					
					ScanTexturePacks("Assets/Textures/");
						
					delete steveHead;
					delete steveHeadCapa;
					delete steveBody;
					delete steveHand;
					delete steveLeg;
						
					steveHead = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),8,8,8,8);
					steveHead->Scale(3,3);
						
					steveHeadCapa = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),40,8,8,8);
					steveHeadCapa->Scale(3,3);
						
					steveBody = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),20,20,8,12);
					steveBody->Scale(3,3);
						
					steveHand = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),44,20,4,12);
					steveHand->Scale(3,3);
						
					steveLeg = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve),4,20,4,12);
					steveLeg->Scale(3,3);
				}
			}
		}
		break;
		case 12:
		{
			if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
			{
				about2Pos--;
				if(about2Pos < 0)about2Pos = 1;

				mSoundMgr->PlayMenuSound();
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
			{
				about2Pos++;
				if(about2Pos > 1) about2Pos = 0;
				mSoundMgr->PlayMenuSound();
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
			{
				if(about2Pos == 1) menuState = 3;
			}

			if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
			{
				menuState = 3;
			}
		}
		break;
    }
	
}

void StateMenu::Update(StateManager* sManager)
{
	
}

void StateMenu::Draw(StateManager* sManager)
{
    //start rendering
    mRender->StartFrame(1,1,1);

    switch(menuState)
    {
    case -1://language menu
    {
		// Renderizar panorama 3D
        sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75, 480.0f / 272.0f, 0.3f, 1000.0f);
		panoramaPass();
		
		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumOrtho(0, 480, 272, 0, -30, 30);
		
		// Dibujar sprites en pantalla
		langBoxSprite->SetPosition(240, 150);
		langBoxSprite->Draw();
		langLogoSprite->SetPosition(240, 25);
		langLogoSprite->Draw();
		
		// Botones (sprite)
		xIcon->SetPosition(20,263);
		xIcon->Draw();
		oIcon->SetPosition(120,263);
		oIcon->Draw();
		
		// Variables (longitud de array, espaciado, etc..)
		unsigned short int getLangLength;
		unsigned short int startY = 92;
		unsigned short int spacing = 26;
		int index1;
		
		// Realizamos un for para dibujar los botones (Sprite)
		for (int i = 0; i < 6; i++)
		{
			int posY = startY + (i * spacing);
			buttonSprite->SetPosition(240, posY);
			buttonSprite->Draw();
			
			// Dibujar resaltado
			if (i == langPosSel) {
				sbuttonSprite->SetPosition(240, posY);
				sbuttonSprite->Draw();
			}
		}

		// Dibujamos los textos - Funciona o doy 20 tiros al aire
		for (int i = 0; i < 6; i++)
		{
			index1 = langPos + i;
			int posY = startY + (i * spacing);
			
			// En tal caso de no tener algun dato lanzar un texto de Error para evitar problemas
			if (langManager.languageNameVector[i].empty()) {
				mRender->SetFontStyle(0.4, GU_COLOR(0.25,0.25,0.25,1), 2, INTRAFONT_ALIGN_CENTER);
				mRender->DebugPrint(240, posY + 8.3, "Lang Manager Error");
				continue;
			}
			
			// Dibujar el texto con los idiomas (Extraidos del vector desde Language Manager)
			i == langPosSel ? mRender->SetFontStyle(0.4, GU_COLOR(1,1,1,1), 2, INTRAFONT_ALIGN_CENTER) : mRender->SetFontStyle(0.4, GU_COLOR(0.25,0.25,0.25,1), 2, INTRAFONT_ALIGN_CENTER);
			mRender->DebugPrint(240, posY + 8.3, langManager.languageNameVector[index1].c_str());
			//mRender->DebugPrint(140, posY + 2.3, "ID: %d",index1); //Solo para verificar ID
		}
		
		// Dibujar titulo pantalla principal
		mRender->SetFontStyle(0.5, GU_COLOR(0.25,0.25,0.25,1), 2, INTRAFONT_ALIGN_CENTER);
		mRender->DebugPrint(240, 74, "Select Language");
		mRender->SetFontStyle(0.4, GU_COLOR(1,1,1,1), 2, 0x00000000);
		mRender->DebugPrint(29, 270, "Select");
		mRender->DebugPrint(129, 270, "Back");
    }
    break;
    case 0://main menu
    {
		//g_RenderCore.BeginCommands();
        //g_RenderCore.Clear();
		
		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75, 480.0f / 272.0f, 0.3f, 1000.0f); //Into 3D Mode for panorama
		panoramaPass();
		
		sceGumMatrixMode(GU_PROJECTION);
        sceGumLoadIdentity();
        sceGumOrtho(0, 480, 272, 0, -30, 30); //Into 2D Mode for menu
		
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        //logo
		lamecraftSprite->SetPosition(240,50);
        lamecraftSprite->Draw();

        //play
		buttonSpritem->SetPosition(240,129);
        buttonSpritem->Draw();

        //options
        buttonSpritem->SetPosition(240,161);
        buttonSpritem->Draw();

		//texture pack
        buttonSpritem->SetPosition(240,193);
        buttonSpritem->Draw();
		
		//Quit
        buttonSpritem->SetPosition(240,225);
        buttonSpritem->Draw();
		
		//idioma
		lenguageSprite->SetPosition(103,239);
		lenguageSprite->Draw();
		
		buttonSpritem2->SetPosition(46,239);	
		buttonSpritem2->Draw();
		
		buttonSpritem2->SetPosition(397,239);	
		buttonSpritem2->Draw();
		
		if(selectPos < 4)
		{
			sbuttonSpritem->SetPosition(240,129 + (32 * selectPos));
			sbuttonSpritem->Draw();
		}
		else if(selectPos == 4)
		{
			slenguageSprite->SetPosition(103,239);
			slenguageSprite->Draw();
		}
		else if(selectPos == 5)
		{
			sbuttonSpritem2->SetPosition(46,239);
			sbuttonSpritem2->Draw();
		}
		else if(selectPos == 6)
		{
			sbuttonSpritem2->SetPosition(397,239);
			sbuttonSpritem2->Draw();
		}
		
		steveHead->SetPosition(396,135);
		steveHead->Draw();
		
		steveHeadCapa->SetPosition(396,135);
		steveHeadCapa->Draw();
		
		steveBody->SetPosition(396,165);
		steveBody->Draw();
		
		steveLeg->SetPosition(390,201);
		steveLeg->Draw();
		
		steveLeg->SetPosition(402,201);
		steveLeg->Draw();
		
		steveHand->SetPosition(378,165);
		steveHand->Draw();
		
		steveHand->SetPosition(414,165);
		steveHand->Draw();
		
		
        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        splashSize += 0.25f;
        if(splashSize > 2*PI)
        {
            splashSize = 0.0f;
        }

		DrawText(360,272,GU_COLOR(1,1,1,1) ,0.35,"Copyright Mojang AB. This is a Fanmade");
		DrawText(60,272,GU_COLOR(1,1,1,1) ,0.35,"Minecraft PSP 4.4");

		selectPos == 0 ? DrawText(240,137,GU_COLOR(1,1,1,1) ,default_tiny_size,getGeneneralTrans(1)) : DrawText(240,137,GU_COLOR(0.25,0.25,0.25,1) ,default_tiny_size,getGeneneralTrans(1)); // play
		selectPos == 1 ? DrawText(240,169,GU_COLOR(1,1,1,1) ,default_tiny_size,getGeneneralTrans(2)) : DrawText(240,169,GU_COLOR(0.25,0.25,0.25,1) ,default_tiny_size,getGeneneralTrans(2)); // options
		selectPos == 2 ? DrawText(240,201,GU_COLOR(1,1,1,1) ,default_tiny_size,getGeneneralTrans(3)) : DrawText(240,201,GU_COLOR(0.25,0.25,0.25,1) ,default_tiny_size,getGeneneralTrans(3)); // texture packs
		selectPos == 3 ? DrawText(240,233,GU_COLOR(1,1,1,1) ,default_tiny_size,getGeneneralTrans(4)) : DrawText(240,233,GU_COLOR(0.25,0.25,0.25,1) ,default_tiny_size,getGeneneralTrans(4)); // exit
		
		selectPos == 5 ? DrawText(46,247,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(5)) : DrawText(46,247,GU_COLOR(0.25,0.25,0.25,1) ,default_size,getGeneneralTrans(5)); //skins
		selectPos == 6 ? DrawText(397,247,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(6)) : DrawText(397,247,GU_COLOR(0.25,0.25,0.25,1) ,default_size,getGeneneralTrans(6)); //about

		
		float rotationAngle = PI/6;
		
		switch(SplashNumber)
		{
			case 0: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"No tengas miedo a fallar, ten miedo a no intentarlo"); break;
			case 1: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"Hay algo en ti que el mundo necesita <3"); break;
			case 2: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"No elimines tu mundo por un mal momento!"); break;
			case 3: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"Music by C418!"); break;
			case 4: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"Ride the pig!"); break;
			case 5: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"Not approved by Mojang!"); break;
			case 6: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"Do not distribute!"); break;
			case 7: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"Spiders everywhere!"); break;
			case 8: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"Sublime!"); break;
			case 9: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"12345 is a bad password!"); break;
			case 10: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"Follow the train, CJ!"); break;
			case 11: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"Exploding creepers!"); break;
			case 12: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"RegenStudio = new Regen();"); break;
			case 13: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"Kiss the sky"); break;
			case 14: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"Llegar al end no significa que sea el final"); break;
			case 15: DrawText(335,85,GU_COLOR(1,1,0,1) ,0.35+sinf(splashSize)*0.02f,"Error 404"); break;
		}
    }
    break;
    case 1://select world
    {
		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75, 480.0f / 272.0f, 0.3f, 1000.0f); //Into 3D Mode for panorama
		panoramaPass();
		
		sceGumMatrixMode(GU_PROJECTION);
        sceGumLoadIdentity();
        sceGumOrtho(0, 480, 272, 0, -30, 30); //Into 2D Mode for menu
		
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));
		
		
		if(saveSubmenu == false) 
		{
			selectworldBox->SetPosition(240,136);
			selectworldBox->Draw();
	
			//backselectworld->SetPosition(240,161);
			//backselectworld->Draw();
		
			xIcon->SetPosition(89,263);
			xIcon->Draw();
			
			TriIcon->SetPosition(169,263);
			TriIcon->Draw();
			
			SquIcon->SetPosition(263,263);
			SquIcon->Draw();
			
			oIcon->SetPosition(403,263);
			oIcon->Draw();
			
			if(saveFilesList.size() > 0)
			{
				for(int i = loadSaveStart; i <loadSaveMax; i++)
				{
					
					if(loadSavePos == i) 
					{	
						sworldinfo->SetPosition(240,108 + (36 * i) - (loadSaveStart * 36));
						sworldinfo->Draw();
						
						menuSprite->SetPosition(118,108 + (i * 36) - (loadSaveStart * 36));//menu
						menuSprite->Draw();
					}
					else
					{
						worldinfo->SetPosition(240,108 + (36 * i) - (loadSaveStart * 36));
						worldinfo->Draw();
						
						smenuSprite->SetPosition(118,108 + (i * 36) - (loadSaveStart * 36));//menu
						smenuSprite->Draw();
					}
					
				}
			}

			sbuttonLoadSprite->SetPosition(145,56);
			sbuttonLoadSprite->Draw();

			//select sprite
			if(saveFilesList.size() > 0)
			{
				//save files
				for(int i = loadSaveStart; i <loadSaveMax; i++)
				{
					
					mRender->SetFont(ENGLISH);
						
					if(saveFilesList[i].worldName[0] != '\0')
							
					{
						mRender->SetFontStyle(0.6f,GU_COLOR(1,1,1,1),0,0x00000000);
						mRender->DebugPrint(145,112 + (i * 36) - (loadSaveStart * 36),"%s",saveFilesList[i].worldName);
							
					}
					else
					{
						mRender->SetFontStyle(0.6f,GU_COLOR(0.6,0.6,0.6,1),0,0x00000000);
						mRender->DebugPrint(145,112 + (i * 36) - (loadSaveStart * 36),"<no name>");
					}

					//mRender->SetFontStyle(0.4f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
					//mRender->DebugPrint(148,107 + (i * 36) - (loadSaveStart * 36),"%s",saveFilesList[i].fileName.c_str());
					
					mRender->SetFontStyle(0.4f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
					mRender->DebugPrint(331,122 + (i * 36) - (loadSaveStart * 36),"%i KB",saveFilesList[i].saveSize/1024);

					mRender->SetDefaultFont();
					
					switch(saveFilesList[i].worldGameMode)
					{
						case 0:
						mRender->SetFontStyle(0.4f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
						mRender->DebugPrint(145,122 + (i * 36) - (loadSaveStart * 36),getGeneneralTrans(23)); //survival
						break;
						case 1:
						mRender->SetFontStyle(0.4f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
						mRender->DebugPrint(145,122 + (i * 36) - (loadSaveStart * 36),getGeneneralTrans(24)); //creative
						break;
						case 2:
						mRender->SetFontStyle(0.4f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
						mRender->DebugPrint(145,122  + (i * 36) - (loadSaveStart * 36),getGeneneralTrans(25)); //hardcore
						break;
					}
				}
			}
		}
		else
		{	
			sworldinfo->SetPosition(240,136);
			sworldinfo->Draw();
			
			menuSprite->SetPosition(118,136);//menu
			menuSprite->Draw();	

			buttonSprite->SetPosition(240,235);
			buttonSprite->Draw();
			
			buttonSprite->SetPosition(240,260);
			buttonSprite->Draw();
			
			if (saveSubMenuSelect != 0)
			{
				sbuttonSprite->SetPosition(240,235 + (25 * (saveSubMenuSelect - 1)));
				sbuttonSprite->Draw();
			}
				
			

			mRender->SetFont(ENGLISH);
						
			if(saveFilesList[loadSavePos].worldName[0] != '\0')
			{
				mRender->SetFontStyle(0.6f,GU_COLOR(1,1,0,1),0,0x00000000);
				mRender->DebugPrint(148,134,"%s",saveFilesList[loadSavePos].worldName);
			}
			else
			{
				mRender->SetFontStyle(0.6f,GU_COLOR(0.6,0.6,0,1),0,0x00000000);
				mRender->DebugPrint(148,134,"<no name>");
				
				smenuSprite->SetPosition(127,136);//menu
				smenuSprite->Draw();
			}

			mRender->SetFontStyle(0.4f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
			mRender->DebugPrint(148,144,"%s",saveFilesList[loadSavePos].fileName.c_str());

			mRender->SetDefaultFont();
			
			switch(saveFilesList[loadSavePos].worldGameMode)
			{
				case 0:
					mRender->SetFontStyle(0.4f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
					mRender->DebugPrint(148,154,"Survival mode (%i KB)",saveFilesList[loadSavePos].saveSize/1024);
				break;
				case 1:
					mRender->SetFontStyle(0.4f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
					mRender->DebugPrint(148,154,"Creative mode (%i KB)",saveFilesList[loadSavePos].saveSize/1024);
				break;
				case 2:
					mRender->SetFontStyle(0.4f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
					mRender->DebugPrint(148,154,"Hardcore mode (%i KB)",saveFilesList[loadSavePos].saveSize/1024);
				break;
			}
		}

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

		if(saveSubmenu)
		{
			saveSubMenuSelect == 0 ? DrawText(240,219,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(35)) : DrawText(240,219,GU_COLOR(1,1,1,1),default_size,getGeneneralTrans(35)); //are u shure?
			saveSubMenuSelect == 1 ? DrawText(240,244,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(36)) : DrawText(240,244,GU_COLOR(0.25,0.25,0.25,1),default_size,getGeneneralTrans(36)); //yes
			saveSubMenuSelect == 2 ? DrawText(240,269,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(37)) : DrawText(240,269,GU_COLOR(0.25,0.25,0.25,1),default_size,getGeneneralTrans(37)); //no
			
			DrawText(240,24,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(33)); //Do you wish to delete this world?
			DrawText(240,34,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(34)); //(This cannot be reverted)
		}
		else
		{
			float buttonTextColor = 1.0f; // for left part
			if(saveFilesList.empty() == true)
			{
				buttonTextColor = 0.5f;
			}

			DrawText(124,272,GU_COLOR(1.0f,1.0f,1.0f,1),default_size,getGeneneralTrans(1)); //play
			DrawText(220,272,GU_COLOR(1.0f,1.0f,1.0f,1),default_size,getGeneneralTrans(31)); //rename
			DrawText(307,272,GU_COLOR(1.0f,1.0f,1.0f,1),default_size,getGeneneralTrans(32)); //delete
			DrawText(447,272,GU_COLOR(1.0f,1.0f,1.0f,1),default_size,getGeneneralTrans(9)); //return
			DrawText(119,90,GU_COLOR(1.0f,1.0f,1.0f,1),default_size,getGeneneralTrans(22)); //worlds
			DrawText(145,67,GU_COLOR(1,1,0.25,1) ,default_size,getGeneneralTrans(20)); //load
			DrawText(334,67,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(21)); //create
		}
    }
    break;
    case 3://about
    {
		
		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75, 480.0f / 272.0f, 0.3f, 1000.0f); //Into 3D Mode for panorama
		panoramaPass();
		
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
				backSprite->SetPosition(x*64,y*64);
				backSprite->Draw();
            }
        }
		
		oIcon->SetPosition(403,263);
		oIcon->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);
		
		int partCredits = 0;
	
		mRender->SetFont(1);
	
		//Minecraft PSP Team
		DrawText(240,272 + yCredits,GU_COLOR(1,1,1,1) ,default_size,"==================");
		DrawText(240,292 + yCredits,GU_COLOR(1,1,0.25,1) ,default_size,"Minecraft PSP Team");
		DrawText(240,312 + yCredits,GU_COLOR(1,1,1,1) ,default_size,"==================");

		for(int colCre = 0; colCre < 49; colCre++)
		{
			if(colCre == 0) DrawText(240,362 + (20 * colCre) + (115 * partCredits) + yCredits,GU_COLOR(0.25,0.25,0.25,1) ,default_size,credits.CreditTitles[partCredits].c_str());
				
			if(credits.CreditText[colCre] == "Fin") 
			{
				partCredits += 1; //Salto de Categoria
				if(partCredits < 5) DrawText(240,362 + (20 * colCre) + (115 * partCredits) + yCredits,GU_COLOR(0.25,0.25,0.25,1) ,default_size,credits.CreditTitles[partCredits].c_str());
			}
			if(credits.CreditText[colCre] != "Fin") DrawText(240,387 + (20 * colCre) + (115 * partCredits) + yCredits,GU_COLOR(1,1,1,1) ,default_size,credits.CreditText[colCre].c_str());
		}
		
		mRender->SetFontStyle(0.4, GU_COLOR(1,1,1,1), 2, 0x00000000);
		mRender->DebugPrint(447,272, "Back");
		
		sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));
		
		langLogoSprite->SetPosition(240, 25);
		langLogoSprite->Draw();
    }
    break;
    case 4://update info
    {


        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 5; y++)
            {
                backSprite->SetPosition(x*64,y*64);
                backSprite->Draw();
            }
        }

        //check for update
        buttonSprite->SetPosition(240,225);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,255);
        buttonSprite->Draw();

        //back
        sbuttonSprite->SetPosition(240,(donatePos * 30) + 225);
        sbuttonSprite->Draw();

        blackBackground->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,80-40,"- Portal system");

		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,90-40,"- New dimension: The Nether");

		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,100-40,"- Fortress structures (Status: Alpha)");

		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,110-40,"- Hell generation (Status: Alpha)");

		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,120-40,"- Hell ambient music");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,130-40,"- New blocks and items (hell)");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,140-40,"- New crafting recipes (hell)");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,150-40,"- New mob: pigman");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,160-40,"- Improved skeleton model");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,170-40,"- Moving camera movement");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,180-40,"- Improved on-screen animations");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,190-40,"- New world gen (Without perlin 3D)");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,200-40,"- Perlin 3D (Not in this version)");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,210-40,"- Cliff generation (Not in this version)");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,220-40,"- Shield (Status: beta)");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,230-40,"- Code optimization (15%)");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(5,240-40,"- New menu, with 3D panorama");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(230,80-40,"- Better structure gen (Not in this version)");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(230,90-40,"- Improved fov without object distortions");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(230,100-40,"- Nerfed spider");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(230,110-40,"- Dynamic fov when sprint");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(230,120-40,"- Crouch fixed");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(230,130-40,"- Visual bugs fixed and improved");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(230,140-40,"- Sprint improved");
		
		mRender->SetFontStyle(0.36,GU_COLOR(1,1,1,1),1,0x00000000);
		mRender->DebugPrint(230,150-40,"- Cloud optimization");

		donatePos == 0 ? DrawText(240,234,GU_COLOR(1,1,0.25,1) ,default_size,"Nothing Here") : DrawText(240,234,GU_COLOR(1,1,1,1) ,default_size,"Nothing Here");
		donatePos == 1 ? DrawText(240,264,GU_COLOR(1,1,0.25,1) ,default_size,getGeneneralTrans(9)) : DrawText(240,264,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(9)); //back
		DrawText(240,20,GU_COLOR(1,1,1,1) ,default_size,"MINECRAFT PSP 4.0 CHANGELOG");
    }
    break;
    case 5://paramateric view
    {
        sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75, 480.0f / 272.0f, 0.3f, 1000.0f); //Into 3D Mode for panorama
		panoramaPass();
		
		sceGumMatrixMode(GU_PROJECTION);
        sceGumLoadIdentity();
        sceGumOrtho(0, 480, 272, 0, -30, 30); //Into 2D Mode for menu
		
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));
		
		selectworldBox->SetPosition(240,136);
		selectworldBox->Draw();
		
		sbuttonLoadSprite->SetPosition(334,56);
		sbuttonLoadSprite->Draw();
		
        worldinfo->SetPosition(240,97);
		worldinfo->Draw();
		
		//seed
        nbuttonSprite->SetPosition(200,129);
        nbuttonSprite->Draw();
		
		//game mode
        buttonSprite2->SetPosition(168,153);//+30
        buttonSprite2->Draw();
		
		//Tipo de mundo
        buttonSprite2->SetPosition(311,153);//+30
        buttonSprite2->Draw();

		//estructuras
        CheckFo->SetPosition(118,176);//+60
        CheckFo->Draw();
		//cofre bonus
        CheckFo->SetPosition(118,204);
        CheckFo->Draw();

		//crear mundo
        buttonSprite->SetPosition(240,227);
        buttonSprite->Draw();
		
		if(makeDungeons)
		{
			Check->SetPosition(118,176);//+60
			Check->Draw();
		}
		
		if(makeBonus)
		{
			Check->SetPosition(118,204);
			Check->Draw();
		}
		
		xIcon->SetPosition(89,263);
		xIcon->Draw();
			
		oIcon->SetPosition(403,263);
		oIcon->Draw();
			
		
		switch(generateSelectPose)
		{
			case 0:
			sworldinfo->SetPosition(240,97);
			sworldinfo->Draw();
			break;
			case 1:
			sbuttonSprite2->SetPosition(200,129);
            sbuttonSprite2->Draw();
			break;
			case 2:
			sbuttonSprite2->SetPosition(168,153);
            sbuttonSprite2->Draw();
			break;
			case 3:
			sbuttonSprite2->SetPosition(311,153);
            sbuttonSprite2->Draw();
			break;
			case 6:
			sbuttonSprite->SetPosition(240,227);
            sbuttonSprite->Draw();
			break;
		}

		menuSprite->SetPosition(118,97);
		menuSprite->Draw();
		
        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

		DrawText(145,67,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(20)); //load
		DrawText(334,67,GU_COLOR(1,1,0.25,1) ,default_size,getGeneneralTrans(21)); //create
		
		DrawText(240,96,GU_COLOR(1,1,1,1) ,default_size,"Name"); //name
		DrawText(318,137,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Seed"); //seed
		
		DrawText(134,272,GU_COLOR(1.0f,1.0f,1.0f,1) ,default_size,getGeneneralTrans(38)); //confirm
		DrawText(447,272,GU_COLOR(1.0f,1.0f,1.0f,1) ,default_size,getGeneneralTrans(9)); //back

		//draw subtitles on buttons
		if(gameMode == SURVIVAL)
		{
			generateSelectPose == 2 ? DrawTextLeft(100,159,GU_COLOR(1,1,1,1) ,default_tiny_size,getGeneneralTrans(39)) : DrawTextLeft(100,159,GU_COLOR(0.25,0.25,0.25,1) ,default_tiny_size,getGeneneralTrans(39)); //Game Mode: Survival
		}
		if(gameMode == CREATIVE)
		{
			generateSelectPose == 2 ? DrawTextLeft(100,159,GU_COLOR(1,1,1,1) ,default_tiny_size,getGeneneralTrans(40)) : DrawTextLeft(100,159,GU_COLOR(0.25,0.25,0.25,1) ,default_tiny_size,getGeneneralTrans(40)); //Game Mode: Creative
		}
		if(gameMode == HARDCORE)
		{
			generateSelectPose == 2 ?DrawTextLeft(100,159,GU_COLOR(1,1,1,1) ,default_tiny_size,getGeneneralTrans(41)) : DrawTextLeft(100,159,GU_COLOR(0.25,0.25,0.25,1) ,default_tiny_size,getGeneneralTrans(41)); //Game Mode: Hardcore
		}
		if(makeDungeons)
		{
			generateSelectPose == 4 ? DrawText(240,185,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(42)) : DrawText(240,185,GU_COLOR(0.25,0.25,0.25,1) ,default_size,getGeneneralTrans(42)); //Structures: ON
		}
		else
		{
			generateSelectPose == 4 ? DrawText(240,185,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(43)) : DrawText(240,185,GU_COLOR(0.25,0.25,0.25,1) ,default_size,getGeneneralTrans(43)); //Structures: OFF
		}
		if(makeBonus)
		{
			generateSelectPose == 5 ? DrawText(240,212,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(44)) : DrawText(240,212,GU_COLOR(0.25,0.25,0.25,1) ,default_size,getGeneneralTrans(44)); //Bonus Chest: ON
		}
		else
		{
			generateSelectPose == 5 ? DrawText(240,212,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(45)) : DrawText(240,212,GU_COLOR(0.25,0.25,0.25,1) ,default_size,getGeneneralTrans(45)); //Bonus Chest: OFF
		}
		if(worldType == 0)
		{
			generateSelectPose == 3 ? DrawTextLeft(244,159,GU_COLOR(1,1,1,1) ,default_tiny_size,getGeneneralTrans(46)) : DrawTextLeft(244,159,GU_COLOR(0.25,0.25,0.25,1) ,default_tiny_size,getGeneneralTrans(46)); //World Type: Default
		}
		if(worldType == 1)
		{
			generateSelectPose == 3 ? DrawTextLeft(244,159,GU_COLOR(1,1,1,1) ,default_tiny_size,getGeneneralTrans(47)) : DrawTextLeft(244,159,GU_COLOR(0.25,0.25,0.25,1) ,default_tiny_size,getGeneneralTrans(47)); //World Type: Flat
		}

		generateSelectPose == 6 ? DrawText(240,237,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(30)) : DrawText(240,237,GU_COLOR(0.25,0.25,0.25,1) ,default_size,getGeneneralTrans(30)); //Create New World

        mRender->SetFont(ENGLISH);
        mRender->SetFontStyle(default_size ,GU_COLOR(1,1,1,1),0,0x00000000|0x00004000);
        mRender->DebugPrint(150,113,"%s",newWorldName.c_str());
        if(seed_1 == 0)
        {
            mRender->SetFontStyle(default_size ,GU_COLOR(0.65,0.65,0.65,1),999,0x00000200|0x00004000);
            mRender->DebugPrint(200,137,getGeneneralTrans(48));
        }
        else
        {
			mRender->SetFontStyle(default_size ,GU_COLOR(1,1,1,1),0,0x00000200|0x00004000);
            mRender->DebugPrint(200,137,"%s",newWorldSeed.c_str());
        }
        mRender->SetDefaultFont();
    }
    break;
    case 6://about
    {


        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 5; y++)
            {
                backSprite->SetPosition(x*64,y*64);
                backSprite->Draw();
            }
        }

        //check for update
		buttonSprite->SetPosition(240,130);
        buttonSprite->Draw();
		
        buttonSprite->SetPosition(240,165);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,200);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,245);
        buttonSprite->Draw();

        //back	//cuevas
        int y_pos = 130;
        if(converterPos == 1)
        {
            y_pos = 165;
        }
        if(converterPos == 2)
        {
            y_pos = 200;
        }
		if(converterPos == 3)
        {
            y_pos = 245;
        }
        sbuttonSprite->SetPosition(240,y_pos);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        if(mRender->GetFontLanguage() == ENGLISH)
        {
            if(schematicExists)
            {
                DrawText(240,60,GU_COLOR(0.1,0.9,0.1,1),default_size,"world.schematic exists!");
            }
            else
            {
                DrawText(240,60,GU_COLOR(0.9,0.1,0.1,1),default_size,"world.schematic doesn't exist!");
            }
            if(errorType == 1)
            {
                DrawText(240,80,GU_COLOR(0.9,0.1,0.1,1),default_size,"invalid schematic size");
            }
            else
            {
                DrawText(240,80,GU_COLOR(0.9,0.1,0.1,1),default_size,"process of conversion can take about 1 minute");
            }
			
			if(newW_deleteCaves == true)
            {
				DrawText(240,114,GU_COLOR(0.5,0.5,0.5,1),0.35,"recommended for optimizing normal maps");
                converterPos == 0 ? DrawText(240,139,GU_COLOR(1,1,0.25,1) ,default_size,"Clean caves: Enabled") : DrawText(240,139,GU_COLOR(1,1,1,1) ,default_size,"Clean caves: Enabled");
            }
            if(newW_deleteCaves == false)
            {
				DrawText(240,114,GU_COLOR(0.5,0.5,0.5,1),0.35,"recommended for competitive maps [skywars, uhc, etc]");
                converterPos == 0 ? DrawText(240,139,GU_COLOR(1,1,0.25,1) ,default_size,"Clean caves: Disable") : DrawText(240,139,GU_COLOR(1,1,1,1) ,default_size,"Clean caves: Disable");
            }

            if(newW_gameMode == SURVIVAL)
            {
                converterPos == 1 ? DrawText(240,174,GU_COLOR(1,1,0.25,1) ,default_size,"Game Mode: Survival") : DrawText(240,174,GU_COLOR(1,1,1,1) ,default_size,"Game Mode: Survival");
            }
            if(newW_gameMode == CREATIVE)
            {
                converterPos == 1 ? DrawText(240,174,GU_COLOR(1,1,0.25,1) ,default_size,"Game Mode: Creative") : DrawText(240,174,GU_COLOR(1,1,1,1) ,default_size,"Game Mode: Creative");
            }
            converterPos == 2 ? DrawText(240,209,GU_COLOR(1,1,0.25,1) ,default_size,"Try to convert") : DrawText(240,209,GU_COLOR(1,1,1,1) ,default_size,"Try to convert");
            converterPos == 3 ? DrawText(240,254,GU_COLOR(1,1,0.25,1) ,default_size,"Cancel") : DrawText(240,254,GU_COLOR(1,1,1,1) ,default_size,"Cancel");

            DrawText(240,29,GU_COLOR(1,1,1,1) ,default_size,"Converter");
        }
        if(mRender->GetFontLanguage() == RUSSIAN)
        {
            if(schematicExists)
            {
                DrawText(240,60,GU_COLOR(0.1,0.9,0.1,1),default_size,"world.schematic existe!");
            }
            else
            {
                DrawText(240,60,GU_COLOR(0.9,0.1,0.1,1),default_size,"world.schematic no existe!");
            }
            if(errorType == 1)
            {
                DrawText(240,80,GU_COLOR(0.9,0.1,0.1,1),default_size,"Tamano de schematic no compatible");
            }
            else
            {
                DrawText(240,80,GU_COLOR(0.9,0.1,0.1,1),default_size,"el proceso de conversion puede durar 1 minuto!");
            }
			
			if(newW_deleteCaves == true)
            {
				DrawText(240,114,GU_COLOR(0.5,0.5,0.5,1),0.35,"recomendado para optimizar mapas normales");
                converterPos == 0 ? DrawText(240,139,GU_COLOR(1,1,0.25,1) ,default_size,"Cuevas: Enabled") : DrawText(240,139,GU_COLOR(1,1,1,1) ,default_size,"Cuevas: Enabled");
            }
            if(newW_deleteCaves == false)
            {
				DrawText(240,114,GU_COLOR(0.5,0.5,0.5,1),0.35,"recomendado para mapas competitivos [skywars, uhc, etc]");
                converterPos == 0 ? DrawText(240,139,GU_COLOR(1,1,0.25,1) ,default_size,"Cuevas: Disable") : DrawText(240,139,GU_COLOR(1,1,1,1) ,default_size,"Cuevas: Disable");
            }

            if(newW_gameMode == SURVIVAL)
            {
                converterPos == 1 ? DrawText(240,174,GU_COLOR(1,1,0.25,1) ,default_size,"Game Mode: Survival") : DrawText(240,174,GU_COLOR(1,1,1,1) ,default_size,"Game Mode: Survival");
            }
            if(newW_gameMode == CREATIVE)
            {
                converterPos == 1 ? DrawText(240,174,GU_COLOR(1,1,0.25,1) ,default_size,"Game Mode: Creativo") : DrawText(240,174,GU_COLOR(1,1,1,1) ,default_size,"Game Mode: Creativo");
            }
            converterPos == 2 ? DrawText(240,209,GU_COLOR(1,1,0.25,1) ,default_size,"Convertir") : DrawText(240,209,GU_COLOR(1,1,1,1) ,default_size,"Convertir");
            converterPos == 3 ? DrawText(240,254,GU_COLOR(1,1,0.25,1) ,default_size,"Regresar") : DrawText(240,254,GU_COLOR(1,1,1,1) ,default_size,"Regresar");

            DrawText(240,29,GU_COLOR(1,1,1,1) ,default_size,"Convertidor");
        }
    }
    break;
	case 7://player options
	{
		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75, 480.0f / 272.0f, 0.3f, 1000.0f); //Into 3D Mode for panorama
		panoramaPass();
		
		sceGumMatrixMode(GU_PROJECTION);
        sceGumLoadIdentity();
        sceGumOrtho(0, 480, 272, 0, -30, 30); //Into 2D Mode for menu
		
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));
		
		//Sprites Here
		
		skinselector->SetPosition(240,136);
		skinselector->Draw();
		
		for(int is = 0; is <= 4; is ++)
		{
			skinHead[is]->SetPosition((240 + (110 * is)) - (110 * skinPos),105);
			skinHead[is]->Draw();
					
			skinHeadCapa[is]->SetPosition((240 + (110 * is)) - (110 * skinPos),105);
			skinHeadCapa[is]->Draw();
					
			skinBody[is]->SetPosition((240 + (110 * is)) - (110 * skinPos),135);
			skinBody[is]->Draw();
					
			skinLeg[is]->SetPosition((234 + (110 * is)) - (110 * skinPos),171);
			skinLeg[is]->Draw();
					
			skinLeg[is]->SetPosition((246 + (110 * is)) - (110 * skinPos),171);
			skinLeg[is]->Draw();
					
			skinHand[is]->SetPosition((222 + (110 * is)) - (110 * skinPos),135);
			skinHand[is]->Draw();
					
			skinHand[is]->SetPosition((258 + (110 * is)) - (110 * skinPos),135);
			skinHand[is]->Draw();
		}
		
		//Buttons
		
		rectFilledBigSprite->SetPosition(240,214);
		rectFilledBigSprite->Draw();

		xIcon->SetPosition(8,263);
		xIcon->Draw();
		
		oIcon->SetPosition(403,263);
		oIcon->Draw();
			
		sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);
		
		//Texts
		
		/*int skinIndex = skinPos + 1;
		int textColor = (skinSelectPos == skinPos) ? GU_COLOR(1,1,1,1) : GU_COLOR(0.25,0.25,0.25,1);
		rectEmptyBigSprite->SetPosition(240, 214);
		rectEmptyBigSprite->Draw();
		
		char text;  // Espacio suficiente para el n?mero
		snprintf(text, sizeof(text), "%d", skinIndex);  // Convertir el int a const char*

		DrawText(240, 223, textColor, default_size, "Skin " + text);*/


		switch(skinPos)
		{
			case 0:
				if(skinSelectPos == 0)
				{
					rectEmptyBigSprite->SetPosition(240,214);
					rectEmptyBigSprite->Draw();
					
					DrawText(240,223,GU_COLOR(1,1,1,1) ,default_size,"Skin 1"); 
				}
				else
				{
					DrawText(240,223,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Skin 1");
				}
			break;
			case 1:
				if(skinSelectPos == 1)
				{
					rectEmptyBigSprite->SetPosition(240,214);
					rectEmptyBigSprite->Draw();
					
					DrawText(240,223,GU_COLOR(1,1,1,1) ,default_size,"Skin 2"); 
				}
				else
				{
					DrawText(240,223,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Skin 2");
				}
			break;
			case 2:
				if(skinSelectPos == 2)
				{
					rectEmptyBigSprite->SetPosition(240,214);
					rectEmptyBigSprite->Draw();
					
					DrawText(240,223,GU_COLOR(1,1,1,1) ,default_size,"Skin 3"); 
				}
				else
				{
					DrawText(240,223,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Skin 3");
				}
			break;
			case 3:
				if(skinSelectPos == 3)
				{
					rectEmptyBigSprite->SetPosition(240,214);
					rectEmptyBigSprite->Draw();
					
					DrawText(240,223,GU_COLOR(1,1,1,1) ,default_size,"Skin 4"); 
				}
				else
				{
					DrawText(240,223,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Skin 4");
				}
			break;
			case 4:
				if(skinSelectPos == 4)
				{
					rectEmptyBigSprite->SetPosition(240,214);
					rectEmptyBigSprite->Draw();
					
					DrawText(240,223,GU_COLOR(1,1,1,1) ,default_size,"Skin 5"); 
				}
				else
				{
					DrawText(240,223,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Skin 5");
				}
			break;
		}
		
		DrawText(240,53,GU_COLOR(1,1,1,1) ,default_size,getGeneneralTrans(11));
		DrawText(56,272,GU_COLOR(1.0f,1.0f,1.0f,1),default_size,getGeneneralTrans(38));
		DrawText(447,272,GU_COLOR(1.0f,1.0f,1.0f,1) ,default_size,getGeneneralTrans(9));
	}
	break;
    case 10://New or load map
    {
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 5; y++)
            {
                backSprite->SetPosition(x*64,y*64);
                backSprite->Draw();
            }
        }

        buttonSprite->SetPosition(240,100);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,140);
        buttonSprite->Draw();

        sbuttonSprite->SetPosition(240,100+saveSubMenuSelect*40);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        if(mRender->GetFontLanguage() == ENGLISH)
        {
            DrawText(240,64,GU_COLOR(1,1,1,1) ,default_size,"Choose Game Mode");

            saveSubMenuSelect == 0 ? DrawText(240,109,GU_COLOR(1,1,1,1) ,default_size,"Survival") : DrawText(240,109,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Survival");
            saveSubMenuSelect == 1 ? DrawText(240,149,GU_COLOR(1,1,1,1) ,default_size,"Creative") : DrawText(240,149,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Creative");
        }
        if(mRender->GetFontLanguage() == RUSSIAN)
        {
            DrawText(240,64,GU_COLOR(1,1,1,1) ,default_size,"Escojer modo de juego");

            saveSubMenuSelect == 0 ? DrawText(240,109,GU_COLOR(1,1,1,1) ,default_size,"Survival") : DrawText(240,109,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Survival");
            saveSubMenuSelect == 1 ? DrawText(240,149,GU_COLOR(1,1,1,1) ,default_size,"Creativo") : DrawText(240,149,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Creativo");
        }
    }
    break;
    case 11://textures
    {
        sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75, 480.0f / 272.0f, 0.3f, 1000.0f); //Into 3D Mode for panorama
		panoramaPass();
		
		sceGumMatrixMode(GU_PROJECTION);
        sceGumLoadIdentity();
        sceGumOrtho(0, 480, 272, 0, -30, 30); //Into 2D Mode for menu
		
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

		menuTexture->SetPosition(240,136);
        menuTexture->Draw();
		
		xIcon->SetPosition(8,263);
		xIcon->Draw();
			
		oIcon->SetPosition(403,263);
		oIcon->Draw();

        //select sprite
        if(texturePackList.size() > 0)
        {

        }

        for(int i = tpStart; i < tpMax; i++)
        {
            if(i < texturePackList.size())
            {	
				sceGuEnable(GU_BLEND);
		
				Sprite* DrawSprite = texturePackList[i].packSprite;

				textureSelect->SetPosition(114 + (i * 50) - (tpStart * 50),198);
				textureSelect->Draw();
						
				if(i == tpPos) 
				{
					stextureSelect->SetPosition(114 + (i * 50) - (tpStart * 50),198);
					stextureSelect->Draw();
				}
			
						
				DrawSprite = texturePackList[i].packSprite;
				DrawSprite->SetPosition(114 + (i * 50) - (tpStart * 50),198);
				DrawSprite->Draw();
				
				sceGuDisable(GU_BLEND);
	
				if(i == tpPos)
				{
					sceGuEnable(GU_BLEND);
					
					Sprite* DrawSprite2 = texturePackList[i].packSprite;
					DrawSprite2->SetPosition(363,99);
					DrawSprite2->Draw();
					
					sceGuDisable(GU_BLEND);
					sceGuEnable(GU_DEPTH_TEST);
					
					mRender->SetFont(ENGLISH);
		
					mRender->SetFontStyle(default_big_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00000000);
					mRender->DebugPrint(90,91,"%s",texturePackList[i].name.c_str());

					mRender->SetFontStyle(default_big_size,GU_COLOR(1,1,1,1),0,0x00000000);
					mRender->DebugPrint(88,89,"%s",texturePackList[i].name.c_str());

					mRender->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00000000);
					mRender->DebugPrint(88,104,"%s",texturePackList[i].description.c_str());

				}
				
				
                mRender->SetDefaultFont();
            }
        }

        buttonSpritem2->SetPosition(240,158);
        buttonSpritem2->Draw();

		if(tpPos == tpCurrent)
		{
			sbuttonSpritem2->SetPosition(240,158);
			sbuttonSpritem2->Draw();
		}
		
        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

		DrawText(240,167,GU_COLOR(1.0f,1.0f,1.0f,1),default_size,getGeneneralTrans(7));
		DrawText(56,272,GU_COLOR(1.0f,1.0f,1.0f,1),default_size,getGeneneralTrans(38));
		DrawText(447,272,GU_COLOR(1.0f,1.0f,1.0f,1) ,default_size,getGeneneralTrans(9));
    }
    break;
	case 12://about special thanks
    {
		
		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75, 480.0f / 272.0f, 0.3f, 1000.0f); //Into 3D Mode for panorama
		panoramaPass();
		
		sceGumMatrixMode(GU_PROJECTION);
        sceGumLoadIdentity();
        sceGumOrtho(0, 480, 272, 0, -30, 30); //Into 2D Mode for menu
		
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        //check for update
        buttonSprite->SetPosition(240,225);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,255);
        buttonSprite->Draw();

        //back
        sbuttonSprite->SetPosition(240,(about2Pos * 30) + 225);
        sbuttonSprite->Draw();

        blackBackground->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

		mRender->SetFontStyle(0.5,GU_COLOR(1,1,0.25,1),2,0x00000000);
		mRender->DebugPrint(40,100-40,"Special thanks to:");
		mRender->SetFontStyle(0.5,GU_COLOR(1,1,1,1),2,0x00000400);
		mRender->DebugPrint(440,100-40,"AlexDev2");

		mRender->SetFontStyle(0.5,GU_COLOR(1,1,0.25,1),2,0x00000000);
		mRender->DebugPrint(40,115-40,"Youtube:");
		mRender->SetFontStyle(0.5,GU_COLOR(1,1,1,1),2,0x00000400);
		mRender->DebugPrint(440,115-40,"@alexdev2306");
		
		mRender->SetFontStyle(0.5,GU_COLOR(1,1,0.25,1),2,0x00000000);
		mRender->DebugPrint(40,150-40,"Past modder:");
		mRender->SetFontStyle(0.5,GU_COLOR(1,1,1,1),2,0x00000400);
		mRender->DebugPrint(440,150-40,"Kiril Skibin (Woolio)");
		
		mRender->SetFontStyle(0.5,GU_COLOR(1,1,0.25,1),2,0x00000000);
		mRender->DebugPrint(40,165-40,"Author:");
		mRender->SetFontStyle(0.5,GU_COLOR(1,1,1,1),2,0x00000400);
		mRender->DebugPrint(440,165-40,"Marcin Ploska (Drakon)");

		about2Pos == 0 ? DrawText(240,234,GU_COLOR(1,1,0.25,1) ,default_size,"Nothing here") : DrawText(240,234,GU_COLOR(1,1,1,1) ,default_size,"Nothing here");
		about2Pos == 1 ? DrawText(240,264,GU_COLOR(1,1,0.25,1) ,default_size,"Back") : DrawText(240,264,GU_COLOR(1,1,1,1) ,default_size,"Back");
		DrawText(240,19,GU_COLOR(1,1,1,1) ,default_size,"Contributors");
    }
    break;
    }

    //mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),0,0x00000000);
    //mRender->DebugPrint(30,50,"%f",size_f);

    //draw debug text at the end
    /*mRender->DebugPrint(40,30,"cpu: %d%%",mRender->GetCpuUsage());
    mRender->DebugPrint(40,40,"gpu: %d%%",mRender->GetGpuUsage());
    mRender->DebugPrint(40,50,"saves: %d",saveFilesList.size());*/

    //mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000400);
    //mRender->DebugPrint(475,15,"CraftSite.pl Edition");
    //mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000200);

    //end frame
    mRender->EndFrame();
}

//additional functions
void StateMenu::ScanSaveFiles(const char* dirName)
{
    // Limpiar la lista de archivos guardados
	saveFilesList.clear();
	newFolderNameList.clear();

    DIR *Dir = opendir(dirName);;
	if (!Dir) return;
    struct dirent *DirEntry;

	// Leer los directorios dentro de "Save/"
    while((DirEntry = readdir(Dir)) != NULL)
    {
        if (FIO_SO_ISDIR(DirEntry->d_stat.st_attr))
        {
			std::string folderNameFound = DirEntry->d_name;
			
			if (folderNameFound == "." || folderNameFound == ".." || folderNameFound == ".svn") continue;
			
			// Verificar si los archivos "info.lms", "world.lms" y "dataplayer.lms" existe dentro del directorio
			const char* filesToCheck[] = {"info.lms", "world.lms", "playerdata.lms"};
			bool allFilesExist = true;
			for (int i = 0; i < 3; i++) {
				std::string filePath = std::string(dirName) + "/" + folderNameFound + "/" + filesToCheck[i];
				FILE* fileTest = fopen(filePath.c_str(), "rb");
				if (!fileTest) {
					allFilesExist = false;
					break; // Si falta un archivo, salir del bucle
				}
				fclose(fileTest);
			}
			if (!allFilesExist) continue;

			// Agregar el mundo a la lista solo si "info.lms" existe
			SaveFile newSaveFile;
            newSaveFile.folderName = folderNameFound;
            saveFilesList.push_back(newSaveFile);
			
			// Agregar el nombre de carpeta a la lista
			newFolderNameList.push_back(folderNameFound);
        }
    }
    closedir(Dir);


    // Leer la informacion de cada archivo "info.lms" y actualizar informacion
    for(unsigned int i = 0; i < newFolderNameList.size(); i++)
    {
		// Directorios en string
		std::string infoFile = "Save/" + newFolderNameList[i] + "/info.lms";
		std::string worldFile = "Save/" + newFolderNameList[i] + "/world.lms";
		
        FILE * pFile;
        pFile = fopen(infoFile.c_str(),"rb");

        if(pFile != NULL)
        {
            // Leer la informacion del guardado
            fread(&saveFilesList[i].saveVersion,sizeof(int),1,pFile);
            fread(&saveFilesList[i].worldGameMode,sizeof(char),1,pFile);
            fread(&saveFilesList[i].locked,sizeof(bool),1,pFile);
			fread(&saveFilesList[i].currentDimension,sizeof(int),1,pFile);
            fread(saveFilesList[i].worldName,sizeof(char),50,pFile);
			
			saveFilesList[i].saveVersion >= 2 ? saveFilesList[i].compression = true : saveFilesList[i].compression = false;

            fclose(pFile);
        }

		// Obtener el tamano del archivo "world.lms"
        saveFilesList[i].saveSize = fileSize(worldFile);
    }

    // Configurar el proximo nombre de guardado
    nextSaveFileNumber = newFolderNameList.size() + 1;
    {
        // Generar nombre de la nueva carpeta
        char liczba[10];
        sprintf(liczba,"%d",nextSaveFileNumber);
        nextSaveFileName = "world";
        nextSaveFileName += liczba;
		
		std::string tempCompare = "Save/world";
		tempCompare += liczba;
		
		// Recorrer la lista de guardados para evitar nombres repetidos
        for(unsigned int i = 0; i < newFolderNameList.size(); i++)
        {
			std::string tempCompare2 = "Save/" + newFolderNameList[i];
			
            //if(tempCompare.compare(tempCompare2) == 0)
            if(tempCompare.compare(tempCompare2) == 0)
            {
                nextSaveFileNumber++;
                sprintf(liczba,"%d",nextSaveFileNumber);
                nextSaveFileName = "world";
                nextSaveFileName += liczba;
            }
        }
    }
}

void StateMenu::ScanTexturePacks(const char* dirName)
{
    if(texturePackList.empty() != false)
    {
        TextureHelper::Instance()->LoadConstTextureMenu();
	
        for(int j = 0; j < texturePackList.size(); j++)
        {
            if (texturePackList[j].packSprite != NULL)
            {
                delete texturePackList[j].packSprite;
            }
        }
        texturePackList.clear();
    }
    texturePackList.clear();

    TextureManager::Instance()->LoadTexture("Assets/unknown_pack.png");

    int TPcheck = 0;

    DIR *dir = opendir(dirName);
    struct dirent *entry;

    while((entry = readdir(dir)) != NULL)
    {
        if (FIO_SO_ISDIR(entry->d_stat.st_attr))
        {
            std::string plik = "";
            plik += entry->d_name;

            size_t found = plik.find(".");
            size_t found2 = plik.find("..");
            size_t found3 = plik.find(".svn");

            if(found==std::string::npos && found2==std::string::npos && found3==std::string::npos)//не найдено
            {
                TP newTP;

                std::string plik2 = plik + "/";
                if(plik2 == TextureHelper::Instance()->defaultFolder)
                {
                    tpCurrent = TPcheck;
                }

                newTP.name = plik;

                texturePackList.push_back(newTP);
                TPcheck++;
            }
        }
    }

    closedir(dir);

    for(int j = 0; j < texturePackList.size(); j++)
    {
        std::string packPath = "Assets/Textures/"+texturePackList[j].name+"/pack.png";

        if(fileExists(packPath) == true) // if we have pack sprite
        {
            TextureManager::Instance()->LoadTexture(packPath);
            texturePackList[j].packSprite = new Sprite(TextureManager::Instance()->GetTextureNumber(packPath));
        }
        else
        {
            texturePackList[j].packSprite = new Sprite(TextureManager::Instance()->GetTextureNumber("Assets/unknown_pack.png"));
        }

        std::string packDescriptionPath = "Assets/Textures/"+texturePackList[j].name+"/pack.txt";

        if(fileExists(packDescriptionPath) == true) // if we have pack description file
        {
            std::string str;
            std::string file_contents;

            std::ifstream file(packDescriptionPath.c_str());

            if (file.is_open())
            {
                while (std::getline(file, str))
                {
                    file_contents += str;
                    file_contents.push_back('\n');
                }
            }

            file.close();
            texturePackList[j].description = file_contents;
        }
    }
}

/*
    texturePackList.clear();

	FILE *infile;
	char textLine[80];
	char textPack[80];

	infile = fopen("Assets/texturePacks.txt","rt");

	 while(fgets(textLine, 80, infile) != NULL)
	 {
		 sscanf(textLine,"%s",textPack);
		 std::string texturePack = textPack;

		 size_t found = texturePack.find(".tp");
		 size_t found2 = texturePack.find(".TP");
		 if(found != std::string::npos || found2 != std::string::npos)// found
		 {
		 	texturePackList.push_back(texturePack);
		 }
	 }
	 fclose(infile);

*/

inline bool StateMenu::fileExists (const std::string& name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

unsigned int StateMenu::hash(const char* s, unsigned int seed)
{
    unsigned int hash = seed;
    while (*s)
    {
        hash = hash * 101  +  *s++;
    }
    return hash;
}

int StateMenu::fileSize (const std::string& name)
{
    struct stat stat_buf;
    int rc = stat(name.c_str(), &stat_buf);
    return rc == 0 ? (int)stat_buf.st_size : -1;
}

void StateMenu::DrawText(int x,int y, unsigned int color, float size, const char *message, ...)
{
    mRender->SetFontStyle(size,color,0,0x00000200|0x00000000);
    mRender->DebugPrint(x,y,message);
}

void StateMenu::DrawTextLeft(int x,int y, unsigned int color, float size, const char *message, ...)
{
    mRender->SetFontStyle(size,color,0,0x00000000|0x00004000);
    mRender->DebugPrint(x,y,message);
}

void StateMenu::panoramaPass()
{
	panorama->update(0.02f);
	panorama->render();
}

const char* StateMenu::getGeneneralTrans(int id)
{
	return langManager.getGeneralTranslation(id);
}