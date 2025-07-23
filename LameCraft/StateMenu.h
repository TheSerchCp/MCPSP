#ifndef STATEMENU_H_
#define STATEMENU_H_

#include <stdlib.h>

#include <Aurora/Utils/StateManager.h>
#include <Aurora/Utils/GameState.h>
#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Utils/Logger.h>
#include <Aurora/Utils/Timer.h>
#include <Aurora/Utils/pgeZip.h>
#include <Aurora/Utils/pgeDir.h>
#include <Aurora/Utils/pge.h>

#include <Aurora/System/SystemManager.h>
#include <Aurora/Graphics/Models/ObjModel.h>
#include <Aurora/Graphics/Camera.h>
#include <Aurora/Graphics/Sprite.h>

#include <pspiofilemgr.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include<fstream>
#include<iostream>

#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

#include "Panorama.h"

#ifdef __PSP__
	#include <sys/stat.h>
#endif


#include "SoundManager.h"
#include "GlobalFunctions.h"
#include "LanguageManager.h"
#include "Credits.h"

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;

class SaveFile
{
public:

	int saveVersion;
	bool compression;
	char worldGameMode;
	bool locked;
	int currentDimension;
	char worldName[50];
	std::string fileName;
	std::string fileData;
	std::string folderName;
	
	int saveSize;
};

class TP
{
public:
    Sprite* packSprite;
	std::string name;
	std::string description;
};

class StateMenu : public CGameState
{
public:
	StateMenu();
	virtual ~StateMenu();
	
	void Init();
	void Enter();
	void CleanUp();

	void Pause();
	void Resume();

	//void NetherCreateSystemCreative(StateManager* sManager,std::string filename);
	//void NetherEnteringSystemCreative(StateManager* sManager,std::string filename);
	void HandleEvents(StateManager* sManager);
	void Update(StateManager* sManager);
	void Draw(StateManager* sManager);
	void panoramaPass();
	
	Timer mTimer;

	short menuState;//0 main,1 load,2 options
	
	// LanguageManager 
	LanguageManager langManager;
	Credits credits;
	
	const char* getGeneneralTrans(int id);
	int langPos;
	int langPosSel;
	int langVectorLength;
	
	float yCredits;

private:

	void ScanSaveFiles(const char* dirName);
	void ScanTexturePacks(const char* dirName);
	void DrawText(int x,int y, unsigned int color, float size, const char *message, ...);
	void DrawTextLeft(int x,int y, unsigned int color, float size, const char *message, ...);
	inline bool fileExists(const std::string& name);
	int fileSize(const std::string& name);

    unsigned int hash(const char* s, unsigned int seed);

private:

	unsigned short int langValue;
	
	Panorama* panorama;

    typedef struct Statistics
    {		
        unsigned short daysInGame;
        unsigned short minutesPlayed;
        unsigned short cropsGrowned;
        unsigned short soilPlowed;
    } st;
	
	typedef struct Achievements
    {
		unsigned short TakingInventory;
		unsigned short GettingWo;
		unsigned short Benchmarking;
		unsigned short TimeS;
		unsigned short TimeM;
		unsigned short MonsterHunter;
		unsigned short GettingUp;
		unsigned short HotTopic;
		unsigned short TimeF;
		unsigned short BakeBread;
		unsigned short Acquire;
		unsigned short Diamond;

    } ac;


    typedef struct Options
    {
        bool useMipsTexturing;
        bool detailedSky;
        bool fastRendering;
        bool newSprintOption;
        bool freezeDayTime;
        bool sounds;
        bool music;
        bool autoJump;
        bool worldBlockAnimation;
        bool fogRendering;
        bool smoothLighting;
        bool particles;
        bool guiDrawing;
        bool buttonsDrawing;

        float fov;
        char horizontalViewDistance;
        char verticalViewDistance;
        int difficult;
    } opt;

	std::string fileskins;
	
    st mainStatistics;
	ac mainAchievements;
    opt mainOptions;

    Sprite *buttonSmallSprite;
	Sprite *sbuttonSmallSprite;
	Sprite *nbuttonSmallSprite;

	Sprite *buttonSprite;
	Sprite *buttonSpritem;
	Sprite *sbuttonSpritem;
	Sprite *buttonSpritem2;
	Sprite *sbuttonSpritem2;
	Sprite *buttonSprite2;
	Sprite *sbuttonSprite;
	Sprite *sbuttonSprite2;

	Sprite *nbuttonSprite;

	Sprite *mbuttonSprite;
	Sprite *smbuttonSprite;
	
	Sprite *menuSprite;//menu
	Sprite *smenuSprite;

	Sprite *skinselector;

	Sprite *backSprite;
	Sprite *lenguageSprite;
	Sprite *slenguageSprite;
	Sprite *logoSprite;
	Sprite *lamecraftSprite;
	Sprite *SelectSkin;

	Sprite *rectFilledSprite;
	Sprite *rectEmptySprite;
	
	Sprite *rectFilledBigSprite;
	Sprite *rectEmptyBigSprite;

	Sprite *blackBackground;
	Sprite *blackSkinBackground;
	Sprite *selectworldBox;
	Sprite *worldinfo;
	Sprite *backselectworld;
	Sprite *sworldinfo;
	Sprite *sbuttonLoadSprite;
	Sprite *Check;
	Sprite *CheckFo;
	
	Sprite *xIcon;
	Sprite *TriIcon;
	Sprite *SquIcon;
	Sprite *oIcon;
	
	Sprite *steveHead;
	Sprite *steveHeadCapa;
	Sprite *steveBody;
	Sprite *steveHand;
	Sprite *steveLeg;

	Sprite *skinHead[5];
	Sprite *skinHeadCapa[5];
	Sprite *skinBody[5];
	Sprite *skinHand[5];
	Sprite *skinLeg[5];
	
	Sprite *menuTexture;
	
	Sprite *textureSelect;
	Sprite *stextureSelect;
	
	Sprite *langBoxSprite;
	Sprite *langLogoSprite;


	RenderManager *mRender;
	SystemManager *mSystemMgr;
	SoundManager *mSoundMgr;
	GlobalFunctions *mGlobalFun;

    // converter vars
    bool schematicExists;

	short newW_width;
	short newW_height;
	short newW_length;

	char newW_gameMode;
	bool newW_deleteCaves;
	
	int conversionStage;
	int errorType;

	std::string lol;

    int converterPos;
	//

    int SplashNumber;
    float splashSize;

    unsigned int seed_1;
	int selectPos;
	int loadSavePos;
	int aboutPos;
	int about2Pos;
	int donatePos;
	int skinPos;
	char worldName[32];

    float size_f;

	float fontcolor;
	bool fontcoloroption;

	bool saveSubmenu;
	int saveSubMenuSelect;

    pgeZip* theZip;

	int loadSaveStart;
	int loadSaveEnd;
	int loadSaveMax;

	short animationscreen;

	int nextSaveFileNumber;
	std::string nextSaveFileName;

	std::vector<SaveFile> saveFilesList;
	std::vector<TP> texturePackList;
	std::vector<std::string> newFolderNameList;
	std::string newWorldName;
	std::string newWorldSeed;
	std::string newWorldNamestr;
	//options for parametric map generation
	bool makeWater;
	bool makeBonus;
	bool makeDungeons;
    int terrainBuilder;
	short gameMode;
	int worldType;

    short generateSelectPose;

	//game version
	short currentVersion;

	int tpCurrent;
	int tpMax;
	int tpEnd;
	int tpStart;
	int tpPos;
	int skinSelectPos;
	
	// string langManager
	std::string langManagerPathStateMenu;
};

#endif
