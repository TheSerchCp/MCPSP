
#ifndef STATEPLAY_H_
#define STATEPLAY_H_

#include <Aurora/Utils/StateManager.h>
#include <Aurora/Utils/GameState.h>

#include <math.h>
#include <psptypes.h>

#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Utils/Logger.h>
#include <Aurora/Utils/Timer.h>
#include <Aurora/System/SystemManager.h>
#include <Aurora/Graphics/Models/ObjModel.h>
#include <Aurora/Graphics/Camera.h>
#include <Aurora/Graphics/Sprite.h>

#include <Aurora/Graphics/Effects/InventoryPlayer.h>
#include <Aurora/Graphics/Effects/SkyLight.h>
#include <Aurora/Graphics/Effects/SnowBall2.h>
#include <Aurora/Graphics/Effects/ArrowEn2.h>
#include <Aurora/Graphics/Effects/Arrow2.h>
#include <Aurora/Graphics/Effects/SkyBox.h>
#include <Aurora/Graphics/Effects/Destroyer.h>
#include <Aurora/Graphics/Effects/StarsBox.h>
#include <Aurora/Graphics/Effects/Drop.h>
#include <Aurora/Graphics/Effects/Particle.h>

#include "ChunkDataProvider.h"

//mobs
#include <LameCraft/mobs/Chicken2.h>
#include <LameCraft/mobs/Cow2.h>
#include <LameCraft/mobs/Creeper2.h>
#include <LameCraft/mobs/Pig2.h>
#include <LameCraft/mobs/Pigman2.h>
#include <LameCraft/mobs/Sheep2.h>
#include <LameCraft/mobs/Skeleton2.h>
#include <LameCraft/mobs/Spider2.h>
#include <LameCraft/mobs/Spidercave2.h>
#include <LameCraft/mobs/Villager2.h>
#include <LameCraft/mobs/WitherSkeleton2.h>
#include <LameCraft/mobs/Wolf2.h>
#include <LameCraft/mobs/Zombie2.h>
#include "LameMob.h"

#include "CraftWorld2.h"
#include "Recipes.h"
#include "Trades.h"
#include "InputHelper.h"
#include "SoundManager.h"
#include "GlobalFunctions.h"
#include "Chest2.h"
#include "Furnace2.h"
#include "NoteBlockEntity.h"
#include "JukeboxEntity.h"
#include "MonsterSpawnerEntity.h"
#include "ItemFrameEntity.h"

#include "GameMode.h"

#include "LameFunctions.h"

#include "LanguageManager.h"


using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;

class GameMode;

class StatePlay : public CGameState
{
public:
	StatePlay();
	virtual ~StatePlay();

	void Init();
	void InitParametric(bool makeDungeons,bool makeBonus, unsigned int seedIII, int worldType, char gameMode, bool nether);
	void Enter();
	void CleanUp();

	void Pause();
	void Resume();
	void LoadTextures();

	void HandleEvents(StateManager* sManager);
	void Update(StateManager* sManager);
	void Draw(StateManager* sManager);

	void LoadMap(std::string fileName, bool compressed);
	void SetWorldAndSaveName(std::string worldName,std::string fileName);
	void InitCamera();
	void initAnims();

	//keys helpers
	bool keyPressed(int currentKey);
	bool keyHold(int currentKey);
	void PutInInventory(int id, int num, bool st);
	
	void ExperienceSystem(int a, int b);
	
	int WORLD_SIZE;
	int WORLD_HEIGHT;
	int CHUNK_SIZE;
	
	LanguageManager langManager;
	
	Recipes recipesManager;
	
	Trades tradesManager;
	
	const char* getGeneneralTranslation(int id);
	std::string langStatePlay;

private:

	void advancedBlit(int sx, int sy, int sw, int sh, int dx, int dy, int slice);
	bool TryToMove(Vector3 moveVector,float dt);
	void SetDayTimeAfterLoad();

	void DrawSlotItem(short& itemId);
	void DrawSlotAmount(short& itemAmount, bool& itemStackable);
	void DrawSlotToolPoints(short& itemAmount, bool& itemStackable);

	void CheckForFurnFuel(Furnace* Fur);
	void CheckForFurnWorking(Furnace* Fur);
	void ReadyFurnSmelting(Furnace* Fur);

    int FindFurnaceId(int x, int y, int z);
	int FindChestId(int x, int y, int z);

	void HungerTime();
	void FireBurning(); //delete
	void HealthTime();
	void OxygenTime();
	void HurtPlayer(float damage);
	void HurtPlayerConsiderArmor(float damage, bool InCamaraAtack);
	
	int UniInvId(int itemId, int reSlot);
	
	

private:

    double time12;

	RenderManager *mRender;
	SystemManager *mSystemMgr;
	SoundManager *mSoundMgr;
	GlobalFunctions *mGlobalFun;
	InputHelper *mIhelper;
	Camera *fppCam;
	GameMode *mGameMode;

	std::string saveFileName;
	int freeMemory;
	float freeMemoryTimer;

    float cloudsOffset;

	CraftWorld *mWorld;

    SkyLight *skyLight;
    SkyLight *skyMoonLight;
    SkyBox *skyBox;
    Destroyer *destroyer;
    StarsBox *starsBox;
    InventoryPlayer* invPlayer;

    double temp_total_time_ms;

    bool cycle;
    bool loadReady;
	bool startDt;
	bool tryToDt;
    float dT;
    float dET;          // Конец таймера
    char dStd;          // Стадия анимации разрушения блока
    float last_HP;

    float sleepMessageTime;
    int sleepMessageType;
    float sleepTime;

    bool hurt;
    float hurt_time;
    float dtt;

    float furnaceTimes;

    Vector3 testPos1;
	Vector3 cubePos;

	bool showCube;
	
	int PagCraft;
	int IndexCraft;
	int SlotEnCraft;
	
	int SlotEnVillager;
	
	int IDDrawRe[4]; //DibujarPreview
	float tickReChange;

    float musicTimeGo;
    float musicTime;

    char chestId;
	char villageId;
    char furnaceId;
	
	int villageProfession;
	int villageLvl;
	int villageRandom;

    Chest* UseChest;
    Furnace* UseFurnace;
	//zmienne do poruszania
	float GRAVITY;
	float JUMPVELOCITY;
	float CLIMBVELOCITY;

	Vector3 playerVelocity;
	Vector3 playerPosition;
	Vector3 newPlayerPos;
	Vector3 oldPlayerPos;
	Vector3 globalOffset;

    bool moveForward;
    bool moving;
	bool walkingOnGround;
	bool jumping;
	bool headInWater;
	bool footInWater;
	bool headInLava;
	bool footInLava;
	bool footInFire;
	bool playerInCobweb;
	bool InHellPortal;
	bool touchingCactus;
	bool burning;
	
	bool sprint;
	bool crouch;
	bool slowWalk;
	
	bool HungerPoisoned;
	bool HPPoisoned;
	
	bool usingSlider; // craive vars
	bool onDestroySlot;

	bool invEn;
	bool villEn;
	bool upEn;
	bool armorEn;
	bool slot2En;
	bool craft3xEn;
	bool chestEn;
	bool furnaceEn;

    char barPosition;
    int invXPosition;
    int invYPosition;
    float invSteveAngle;

	int ram1;
	int ram2;
	
	int HGP;
	int HPE;

    float tickCave; //cave sounds timer
	float tickHunger;
	float tickHealth;
	float tickChunk;
	float tickLavaDamage;
	float tickFireDamage; //fire
	float tickCactusDamage;
	float tickOS;
	float tickFR;
	float tickHungerPoisoned;
	float tickHPveneno;
	float tickShowSlotName;
	float tickSprintTime;
	float tickTp;
	float eatingTick;
	
	//### from creative ###//
	float tickShowFlymodeMessage;
	float tickFlyTime;
	
	short chunks; // 0 - 7;

	int tutorialTimer;

	float rainSoundFrequency;

	float inputDiskNameTimer;
	std::string inputDiskName;

    int chunkId;
	
	//int EXPcount;

	Timer mTimer;
	float dt;

	//int texture[16];
	int barItems;
	int texture;
	int texture_mips;
	int waterAnimation;

	unsigned char blue;
	unsigned char red;
	unsigned char purple;
	unsigned char black;
	unsigned char stars;

    int invPlayerTex;
    int zombieTex;
	int skeletonTex;
    int spiderTex;
    int spidercaveTex;
    int cowTex;
	int chickenTex;
	int pigTex;
    int snowBall4;
	int arrow4;
	int cloudsTex;
	int suntex;
	int moontex;
	int rainTex;

	unsigned char currentTexture;
	unsigned char timeTexture;

	float pre_fps;
	int average_fps;
	float tick_fps;
	int ticks;
	
	// Edit Mode Variables
	
	float editModeMoveX;
	float editModeMoveY;
	float editModeMoveZ;
	
	float editModeRotateX;
	float editModeRotateY;
	float editModeRotateZ;
	
	float editModeScale;
	float editSum;
	
	bool editModeManager;
	int editModeType;
	bool editMode;
	
	// New Anims
	float lerp(float a, float b, float t);
	int currentState;
	float animationTime;
	float animationSpeed;
	float swingAmountX;
	float swingAmountY;
	
	float swingAnimY;
	float swingAnimValueY;
	
	// Anims Variables

	// Anim Hand Values
	std::vector<Vector3> animHandPos;
	std::vector<Vector3> animHandRot;
	
	// Anim Cube Values
	std::vector<Vector3> animBlockPos;
	std::vector<Vector3> animBlockRot;
	
	// Anim Item Values
	std::vector<Vector3> animItemPos;
	std::vector<Vector3> animItemRot;
	
	Sprite *invSprite;
	Sprite *invVillage;
	Sprite *invSpriteCreative;

	Sprite *waterScreen;
	Sprite *pumpkinMask;

    Sprite *invCellSprite;
    Sprite *crtSprite;
    Sprite *chtSprite;
    Sprite *selectInvSprite;
	Sprite *barSprite;
	Sprite *selectInvVillSprite;
	
	Sprite *xIcon;
	Sprite *TriIcon;
	Sprite *SquIcon;
	Sprite *oIcon;
	
	Sprite *cellRedSprite2;
	Sprite *leftIcon;
	Sprite *rightIcon;
	//Sprite *XPbarSprite;
	//Sprite *XPprogressSprite[182];
	
	/*Sprite *num0Sprite;
	Sprite *num1Sprite;
	Sprite *num2Sprite;
	Sprite *num3Sprite;
	Sprite *num4Sprite;
	Sprite *num5Sprite;
	Sprite *num6Sprite;
	Sprite *num7Sprite;
	Sprite *num8Sprite;
	Sprite *num9Sprite;*/
	
	Sprite *crossSprite;
	Sprite *lSprite;
	Sprite *l2Sprite;
	Sprite *r2Sprite;
	Sprite *rSprite;
	Sprite *selectSprite;
	Sprite *slot2Sprite;

	Sprite *furArrowSprite[22];
	Sprite *furFireSprite[14];
    Sprite *furSprite;
	
	Sprite *buttonAchiSprite;

	Sprite *cellRedSprite;
	
	Sprite *invCraftSelSprite;
	Sprite *invCraft2Sprite;
	Sprite *invCraftSelPagSprite;

	Sprite *toolPointSprite[14];
	
	Sprite *AchiBoxSprite;
	
	float ya;
	float tickAchie;

	float hpAnim;

	float cameraSpeed;
	float cameraMoveSpeed;

	//menu sprites
	Sprite *buttonSprite;
	Sprite *sbuttonSprite;
	Sprite *nbuttonSprite;
	Sprite *moverSprite;
	
		//menu options
	Sprite *menuOptionsSprite;
	Sprite *menuOptionsSpriteFo;
	Sprite *sbuttonSprite2;
	Sprite *LogoMenu;
	Sprite *CheckFo;
	Sprite *Check;

	bool menuOptions;
	char menuState;//0 game,1 menu
	char optionsMenuPos;
	char selectPos;
	char menuOptionsPag;
	char diePos;//muerte

    char statisticsPage;

	// some settings
	bool canFly;
	bool devMode;
	bool analogLeft,analogRight,analogUp,analogDown;

	// for sound of walkinng
	float walkSoundAccu;
	bool  isWalking;

	// Headbob
	bool canHeadBob;
	float bobCycle;
	bool bobType;
	
	float bobCiclo;
	bool bobTipo;
	
	float cubeLight;

    float shift_x;
    float shift_y;
    float idle_y;
	
	// Comida
    float foodAnim;
	float previousFoodAnimFloat;
	float eatSoundTimer;
	
	bool canEatAgain;
	bool foodEaten2;
	bool foodBool;
	
	// Bow
	float tickBow;
	float changeYBow;
	bool buttonBowPressed;
	bool AtackBow;
	float bowAnim;
	
	// Shield
	float recoidShield;
	bool shield;
	
    float changeY;
	float changeX;
    float changeScale;
    int slotForChangeScale;

    float animDest;
    float animSpeed;
    bool animGo;

    bool anim[3];
	bool makeScreen;
	bool dieFactor;

	float angleFactor;

    void DrawText(int x,int y, unsigned int color, float size, const char *message, ...);
    void DrawText2(int x,int y, unsigned int color, float size, const char *message, ...);
	void DrawItemAc(int id,int x,int y,int Scale);
	void DrawBlockAc(int id,int x,int y,int Scale);
	void DrawPagAc();
    void DrawAmount(int x,int y, int amount);
	
	std::vector<SnowBall2*> mSnowBalls;
	std::vector<Arrow2*> mArrows;
	std::vector<ArrowEn2*> mArrowEns;
	std::vector<Particle*> mParticles;
	
	// from creative
	void SetCreativePage(char page);
	void InitCreativeInventory();
	
	std::vector<int> inventoryCoItems;
	std::vector<int> inventoryEqItems;
	std::vector<int> inventoryDeItems;
	std::vector<int> inventoryNaItems;
	
	bool check;
	int creativePlace;
    int creativePage;
    int creativePageMax1;
	int creativePageMax2;
	int creativePageMax3;
	int creativePageMax4;
};

#endif
