#include "StatePlay.h"
#include "TextureHelper.h"

#include "WorldGenerator.h"
#include "LoadingScreen.h"
#include <Aurora/Utils/Logger.h>

#define PI 3.14159265f
#define DEG_TO_RAD (PI / 180.0f)
#define TEXTURE_CHUNKS 8
#define SKY_MOVE 0.003f

#define default_size 0.5
#define default_tiny_size 0.4
#define default_big_size 0.687
#define default_normal_font 0.587

#define ENGLISH 1
#define RUSSIAN 2

// information about the gamemodes
//mWorld->currentDimension | Para saber si esta en el nether o overworld (0 = overworld | 1 = nether)
//mWorld->gameModeWorld | Para saber que modo de juego esta, desde StatePlay
//saveFilesList[loadSavePos].worldGameMode | Para saber el modo de juego desde el Menu
//mGlobalFun->GameMode | Es lo establecido por Alex para proceder con el nombre y modo de juego de el Nether

StatePlay::StatePlay()
{
    time12 = 0.0f;
    mRender = NULL;
    mSystemMgr = NULL;
    fppCam = NULL;
    UseChest = NULL;
    UseFurnace = NULL;

    temp_total_time_ms = 0;

    statisticsPage = 0;

    freeMemory = 30;
    freeMemoryTimer = 0.0f;
	
	// ### from creative ### //
	check = false;
	creativePage = 0;
    creativePageMax1 = 0;
	creativePageMax2 = 0;
	creativePageMax3 = 0;
	creativePageMax4 = 0;
	creativePlace = 0;
	
	// ### end creative ### //

    ram1 = 0;
    ram2 = 0;
    dt = 0.0f;
	
	HGP = 0;
	HPE = 0;

    showCube = true;

    GRAVITY = -6.8f;
    JUMPVELOCITY = 4.6f;
    CLIMBVELOCITY = 2.5f;

    moveForward = false;
    walkingOnGround = false;
    jumping = false;
    moving = false;
    headInWater = false;
    footInWater = false;
    headInLava = false;
    footInLava = false;
    footInFire = false;
    playerInCobweb = false;
    touchingCactus = false;
	burning = false;
	
	sprint = false;
	crouch = false;
	slowWalk = false;
	
	HungerPoisoned = false;
	HPPoisoned = false;

    invEn = false;
	villEn = false;
    craft3xEn = false;
    upEn = false;
	slot2En = false;
    chestEn = false;
    furnaceEn = false;
    armorEn = false;

    cycle = 0;
    dtt = 0.0f;

    shift_x = 0.0f;
    shift_y = 0.0f;
    idle_y = 0.0f;
	
    foodAnim = 0.0f;
    eatSoundTimer = 0.5f;
	
    musicTimeGo = 0;

    chunkId = 0;
    chunks = 0;
	
    angleFactor = 0.0f;

    startDt = false;
    dET = 0;
    dT = 0;
    dStd = -1;
    tryToDt = false;

    testPos1.x = -1;
    testPos1.y = -1;
    testPos1.z = -1;

    barPosition = 0;
    invXPosition = 0;
    invYPosition = 0;

    chestId = -1;
	villageId = -1;
    furnaceId = -1;
	
	villageProfession = 0;
	villageLvl = 0;
	villageRandom = 0;

    cameraSpeed = 2.0f / 60.0f;
    cameraMoveSpeed = 0.0f;

    menuState = 0;
    selectPos = 0;
	diePos = 0;

    cloudsOffset = 0.0f;

    devMode = false;
    makeScreen = false;

	canHeadBob = true;
	invSteveAngle = 0.0f;
	bobCycle = 0.0f;
	bobCiclo = 0.0f;
	changeY = 0.0f;
	changeX = 0.0f;
	changeScale = 0.0f;

    slotForChangeScale = -1;

	anim[0] = 0;
	anim[1] = 0;
	anim[2] = 0;

	hpAnim = 0.0f;

	//### from creative ###///
	canFly = false;

    tickHunger = 0.8f;
    tickHealth = 0.0f;
    tickCave = 0.0f;
    tickChunk = 0.0f;
    tickOS = 0.4f;
	tickFR = 0.4f;
    tickShowSlotName = 0.0f;
    tickSprintTime = 1.0f;
    tickCactusDamage = 0.0f;
    tickLavaDamage = 0.6f;
	tickFireDamage = 0.6f;
	
	//### from creative ###//
	tickShowFlymodeMessage = 0.0f;
	tickFlyTime = 1.0f;
	
    furnaceTimes = 0.0f;
    tutorialTimer = -1;

	tickHungerPoisoned = 1.0f;
	tickHPveneno = 0.0f;
	
	// comida
	eatingTick = 0.0f;
	canEatAgain = true;
	foodEaten2 = false;
	foodBool = false;

    rainSoundFrequency = 1.7f;

    inputDiskNameTimer = 0.0f;
    inputDiskName = "";

    hurt = false;
    hurt_time = 0;
    musicTime = 1;

    dieFactor = true;

    animDest = 0.0f;
    animSpeed = 1.0f;
    animGo = false;

    cubeLight = 0.0f;

    sleepMessageTime = 0.0f;
    sleepMessageType = 0;
    sleepTime = 0.0f;
    loadReady = false;

    pre_fps = 0.0f;
    average_fps = 0;
    tick_fps = 0.0f;
    ticks = 0;

    last_HP = 0;
	
	// bow properties
	tickBow = 0.0f;
	AtackBow = false;
	buttonBowPressed = false;
	bowAnim = 0.0f;
	
	// archievements properties
	tickAchie = 0.0f;
	tickTp = 0.0f;
	
	// shield properties
	recoidShield = 0.0f;
	shield = false;
	
	// slider (from: creative)
	usingSlider = false;
    onDestroySlot = false;
	
	// portal properties
	InHellPortal = false;
	
	// Language Manager
	langManager.getFolderName();
	std::string langStatePlay = langManager.folderNameCD;
	langManager.load_language("Assets/Lang/"+langStatePlay+"/general.txt");
	
	PagCraft = 0;
	IndexCraft = 0;
	SlotEnCraft = 0;
	SlotEnVillager = 0;
	
	for(int i = 0; i < 5; i++)
	{
		IDDrawRe[i] = 0;
	}
	
	tickReChange = 0.0f;
	
	// Edit Mode Variables
	editModeMoveX = 0.0f;
	editModeMoveY = 0.0f;
	editModeMoveZ = 0.0f;
	
	editModeRotateX = 0.0f;
	editModeRotateY = 0.0f;
	editModeRotateZ = 0.0f;
	
	editModeScale = 0.45f;
	
	editModeManager = true;
	editModeType = 1;
	editMode = false;
	
	editSum = 0.1f;
	
	// Animaciones
	animationTime = 0.0f;
	currentState = 0;
	animationSpeed = 30.00f;
	
	swingAmountX = 0.04f;
	swingAmountY = -0.06f;
	
	swingAnimY = 0.0f;
	swingAnimValueY = 0.06f;
	
	initAnims();
}

StatePlay::~StatePlay()
{
	
}

void StatePlay::initAnims()
{
	// Anim hand values
	if(animHandPos.empty()) {
		animHandPos.push_back(Vector3(0.258f, -0.379f, -0.333f));  //state 0 (idle)
		animHandPos.push_back(Vector3(0.252f, -0.321f, -0.336f));  //state 1
		animHandPos.push_back(Vector3(0.223f, -0.211f, -0.332f));  //state 2
		animHandPos.push_back(Vector3(0.216f, -0.201f, -0.374f));  //state 3
		animHandPos.push_back(Vector3(0.204f, -0.238f, -0.395f));  //state  EXTRA
		animHandPos.push_back(Vector3(0.194f, -0.309f, -0.424f));  //state 4
		animHandPos.push_back(Vector3(0.199f, -0.451f, -0.500f));  //state 5
		animHandPos.push_back(Vector3(0.213f, -0.587f, -0.526f));  //state 6
		animHandPos.push_back(Vector3(0.239f, -0.502f, -0.466f));  //state 7
		//animHandPos.push_back(Vector3(0.258f, -0.379f, -0.333f));  //state 8 (back to idle pos)
	}

	if(animHandRot.empty()) {
		animHandRot.push_back(Vector3(-1.630f, -1.029f, -0.721f));  //state 0 (idle)
		animHandRot.push_back(Vector3(-1.230f, -1.022f, -0.302f));  //state 1
		animHandRot.push_back(Vector3(-0.830f, -0.832f, 0.228f));   //state 2
		animHandRot.push_back(Vector3(-0.620f, -0.512f, 0.547f));   //state 3
		animHandRot.push_back(Vector3(-0.609f, -0.471f, 0.635f));   //state EXTRA
		animHandRot.push_back(Vector3(-0.609f, -0.471f, 0.655f));   //state 4
		animHandRot.push_back(Vector3(-0.619f, -0.431f, 0.695f));   //state 5
		animHandRot.push_back(Vector3(-0.889f, -0.712f, 0.401f));   //state 6
		animHandRot.push_back(Vector3(-1.349f, -0.902f, -0.149f));  //state 7
		//animHandRot.push_back(Vector3(-1.630f, -1.029f, -0.721f));  //state 8 (back to idle pos)
	}
	
	// Anim block values
	if(animBlockPos.empty()) {
		animBlockPos.push_back(Vector3(0.69f, -0.64f, -0.96f));	//state 0 (idle)
		animBlockPos.push_back(Vector3(0.46f, -0.43f, -0.99f));	//state 1
		animBlockPos.push_back(Vector3(0.31f, -0.41f, -1.06f));	//state 2
		animBlockPos.push_back(Vector3(0.24f, -0.48f, -1.12f));	//state 3
		animBlockPos.push_back(Vector3(0.20f, -0.64f, -1.15f));	//state 4
		animBlockPos.push_back(Vector3(0.23f, -0.79f, -1.23f));	//state 5
		animBlockPos.push_back(Vector3(0.34f, -0.85f, -1.16f));	//state 6
		animBlockPos.push_back(Vector3(0.54f, -0.81f, -1.16f));	//state 7
		animBlockPos.push_back(Vector3(0.69f, -0.64f, -0.96f));	//state 8 (back to idle pos)
	}

	if(animBlockRot.empty()) {
		animBlockRot.push_back(Vector3(0.02f, 0.81f, 0.00f));	//state 0 (idle)
		animBlockRot.push_back(Vector3(-0.92f, 0.69f, 0.50f));	//state 1
		animBlockRot.push_back(Vector3(-1.39f, 0.53f, 0.70f));	//state 2
		animBlockRot.push_back(Vector3(-1.57f, 0.43f, 0.73f));	//state 3
		animBlockRot.push_back(Vector3(-1.66f, 0.39f, 0.72f));	//state 4
		animBlockRot.push_back(Vector3(-1.47f, 0.42f, 0.62f));	//state 5
		animBlockRot.push_back(Vector3(-1.11f, 0.53f, 0.34f));	//state 6
		animBlockRot.push_back(Vector3(-0.53f, 0.48f, 0.16f));	//state 7
		animBlockRot.push_back(Vector3(0.02f, 0.81f, 0.00f));	//state 8 (back to idle pos)
	}
	
	// Anim item values
	if(animItemPos.empty()) {
		animItemPos.push_back(Vector3(0.443f, -0.235f, -0.516f));	//state 0 (idle)
		animItemPos.push_back(Vector3(0.386f, -0.189f, -0.538f));	//state 1
		animItemPos.push_back(Vector3(0.221f, -0.104f, -0.616f));	//state 2
		animItemPos.push_back(Vector3(0.121f, -0.124f, -0.701f));	//state 3
		animItemPos.push_back(Vector3(0.051f, -0.240f, -0.781f));	//state 4
		animItemPos.push_back(Vector3(0.081f, -0.430f, -1.001f));	//state 5
		animItemPos.push_back(Vector3(0.227f, -0.442f, -1.001f));	//state 6
		animItemPos.push_back(Vector3(0.287f, -0.334f, -0.701f));	//state 7
		animItemPos.push_back(Vector3(0.443f, -0.235f, -0.516f));	//state 8 (back to idle pos)
	}

	if(animItemRot.empty()) {
		animItemRot.push_back(Vector3(0.038f, -1.483f, 0.468f));	//state 0 (idle)
		animItemRot.push_back(Vector3(0.698f, -1.323f, 1.285f));	//state 1
		animItemRot.push_back(Vector3(1.038f, -1.183f, 2.195f));	//state 2
		animItemRot.push_back(Vector3(0.902f, -0.986f, 2.317f));	//state 3
		animItemRot.push_back(Vector3(0.652f, -0.888f, 2.357f));	//state 4
		animItemRot.push_back(Vector3(0.772f, -0.908f, 2.217f));	//state 5
		animItemRot.push_back(Vector3(1.572f, -1.161f, 2.527f));	//state 6
		animItemRot.push_back(Vector3(2.174f, -1.251f, 3.229f));	//state 7
		animItemRot.push_back(Vector3(0.038f, -1.483f, 0.468f));	//state 8 (back to idle pos)
	}
}

void StatePlay::InitCamera()
{
    fppCam = new Camera();
    fppCam->PositionCamera(playerPosition.x,playerPosition.y,playerPosition.z, playerPosition.x,playerPosition.y,playerPosition.z-5.0f, 0.0f,1.0f,0.0f);
    mRender->SetActiveCamera(fppCam);

    mWorld->UpdatePlayerZoneBB(fppCam->m_vPosition);
    mWorld->RebuildVisibleChunks();
	
	Utils::Logger::Instance()->LogMessage("Camera Init \n");
}

void StatePlay::Init()
{
    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
	mGlobalFun = GlobalFunctions::Instance();
    mIhelper = InputHelper::Instance();
	mGameMode = GameMode::Instance();

    WorldGenerator *mGen = new WorldGenerator();

    //then create our perfect world
    mWorld = new CraftWorld();
	
	if(mSoundMgr->Ram32 == true) mWorld->Ram32 = true;
	
	/*if(mGlobalFun->teleported == true)
	{
		if(mGlobalFun->CreateHell == true)
		{
			saveFileName = mGlobalFun->filename;
			
			mWorld->LoadDataPlayer(saveFileName);
			
		}
		if(mGlobalFun->thisWorld == false)
		{
			mWorld->currentDimension = 1;
			mGlobalFun->teleported = false;
			
			if(mGlobalFun->CreateHell)
			{
				mGlobalFun->CreateHell = false;
				mWorld->createdHell = true;
			}
		}
		else
		{
			mWorld->currentDimension = 0;
			mGlobalFun->teleported = false;
			mGlobalFun->CreateHell = false;
		}
	}*/
	
    mWorld->initWorld(WORLD_SIZE, WORLD_HEIGHT, CHUNK_SIZE);
    delete mGen;
    //mWorld->initRandompMap(128,16);
    mWorld->setTextureSize(256,16,64,16,256,16);
    mWorld->initWorldBlocksLight();
    if(mWorld->currentDimension == 0) mWorld->SetWorldTime(10);
    if(mWorld->currentDimension == 1) mWorld->SetWorldTime(10);
    mWorld->UpdatePlayerZoneBB(playerPosition);
    mWorld->buildMap();
	
    playerPosition = newPlayerPos = oldPlayerPos = Vector3(64.0f,mWorld->groundHeight(64,64)+1.65,64.0f);
    
    // Update chunk manager with player position
    mWorld->updatePlayerPosition(playerPosition);

    int	curchunkTarget = mWorld->getChunkId(playerPosition);

    dt = mTimer.GetDeltaTime();

    bobCycle = 3.14/2;
    bobCiclo = 3.14/2;
    cubeLight = 0.0f;

    LoadTextures();
    mWorld->GetTexturesIds();
    mWorld->buildblocksVerts();

    menuOptions = false;
    optionsMenuPos = 0;
	menuOptionsPag = 0;

    analogLeft = analogRight = analogUp = analogDown = false;

    walkSoundAccu = 0.0f;
    isWalking = false;
    loadReady = false;
	
	PagCraft = 0;
	
	for(int i = 0; i < 5; i++)
	{
		IDDrawRe[i] = 0;
	}
	
	IndexCraft = 0;
	SlotEnCraft = 0;
	SlotEnVillager = 0;
	tickReChange = 0.0f;
}

void StatePlay::InitParametric(bool makeDungeons,bool makeBonus,unsigned int seed_1, int worldType, char gameMode, bool nether)
{
    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
	mGlobalFun = GlobalFunctions::Instance();
    mIhelper = InputHelper::Instance();
	mGameMode = GameMode::Instance();

    //then create our perfect world
    mWorld = new CraftWorld();
	
	/*if(mGlobalFun->teleported == true)
	{
		if(mGlobalFun->CreateHell == true)
		{
			saveFileName = mGlobalFun->filename;
			
			mWorld->LoadDataPlayer(saveFileName);
		}
		
		if(mGlobalFun->thisWorld == false)
		{
			mWorld->currentDimension = 1;
			mGlobalFun->teleported = false;
			
			if(mGlobalFun->CreateHell)
			{
				mGlobalFun->CreateHell = false;
				mWorld->createdHell = true;
			}
		}
		else
		{
			mWorld->currentDimension = 0;
			mGlobalFun->teleported = false;
			mGlobalFun->CreateHell = false;
		}
	}*/
	
	if(mSoundMgr->Ram32 == true)
	{
		mWorld->Ram32 = true;
	}
	
    mWorld->initWorld(WORLD_SIZE, WORLD_HEIGHT, CHUNK_SIZE);
    mWorld->gameModeWorld = gameMode;

    WorldGenerator *mGen = new WorldGenerator();
    mGen->initRandompMap(WORLD_SIZE, WORLD_HEIGHT, CHUNK_SIZE, mWorld, makeDungeons, makeBonus, seed_1, worldType, nether);
    delete mGen;
	
	Utils::Logger::Instance()->LogMessage("Init RandompMap \n");
	
    mWorld->setTextureSize(256,16,64,16,256,16);
    if(mWorld->currentDimension == 0) mWorld->SetWorldTime(10);
    if(mWorld->currentDimension == 1) mWorld->SetWorldTime(10);
    mWorld->UpdatePlayerZoneBB(playerPosition);
    mWorld->buildMap();

    playerPosition = newPlayerPos = oldPlayerPos = mWorld->playerSpawnPointPosition;
    
    // Update chunk manager with player position
    mWorld->updatePlayerPosition(playerPosition);

    int	curchunkTarget = mWorld->getChunkId(playerPosition);

    dt = mTimer.GetDeltaTime();
	
	Utils::Logger::Instance()->LogMessage("Init LoadTextures \n");

    LoadTextures();
	
	Utils::Logger::Instance()->LogMessage("LoadTextures \n");

    mWorld->GetTexturesIds();
    mWorld->buildblocksVerts();
    mWorld->buildcloudsVerts();
    mWorld->buildmobVerts();

    menuOptions = false;
    optionsMenuPos = 0;
	menuOptionsPag = 0;

    analogLeft = analogRight = analogUp = analogDown = false;

    walkSoundAccu = 0.0f;
    isWalking = false;

    cubeLight = 0.0f;
    bobCycle = PI/2.0f;
    bobCiclo = PI/2.0f;
    loadReady = true;

	if(mWorld->gameModeWorld == 1) InitCreativeInventory();

    mWorld->haveCompass = mWorld->HaveItemInBarSlots(Compass::getID());


}

void StatePlay::SetWorldAndSaveName(std::string worldName,std::string fileName)
{
    if(mWorld != NULL)
    {
        sprintf(mWorld->worldName,"%s",worldName.c_str());
    }
    saveFileName = fileName;
}

void StatePlay::LoadMap(std::string fileName, bool compressed)
{
    //enter loading screen
    LoadingScreen* loading = new LoadingScreen();

    loading->readiness = 0;
    loading->stateName = 0;

    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
	mGlobalFun = GlobalFunctions::Instance();
    mIhelper = InputHelper::Instance();
	mGameMode = GameMode::Instance();
	
	bool TeleportLoad = false;
	
    //save name
    saveFileName = fileName;
    //set start position
    playerPosition = newPlayerPos = oldPlayerPos = Vector3(64.0f,64,64);

    //then create our perfect world
    mWorld = new CraftWorld();
	
	/*if(mGlobalFun->teleported == true && mGlobalFun->thisWorld == false)
	{
		loading->Nether = true;
	}
	else
	{
		loading->Nether = false;
	}*/
	
	if(mSoundMgr->Ram32 == true) mWorld->Ram32 = true;

	/*if(mGlobalFun->teleported == true)
	{
		if(mGlobalFun->thisWorld == false)
		{
			mWorld->currentDimension = 1;
			mGlobalFun->teleported = false;
			
			if(mGlobalFun->CreateHell)
			{
				mGlobalFun->CreateHell = false;
				mWorld->createdHell = true;
			}
			
			TeleportLoad = true;
		}
		else
		{
			mGlobalFun->teleported = false;
			mWorld->currentDimension = 0;
			mGlobalFun->CreateHell = false;
			
			TeleportLoad = true;
		}
	}*/

    //load data
    if(compressed)
    {
        mWorld->LoadCompressedWorld(saveFileName);
        //set player pos from map
        playerPosition = mWorld->GetPlayerPos();
        newPlayerPos  = mWorld->GetPlayerPos();
        oldPlayerPos = mWorld->GetPlayerPos();
        mWorld->SetWorldTime(mWorld->worldDayTime);
    }
    else
    {
        mWorld->LoadWorld(saveFileName.c_str());
        if(mWorld->currentDimension == 0) mWorld->SetWorldTime(10);
		if(mWorld->currentDimension == 1) mWorld->SetWorldTime(10);
    }
	
    //player zone size and bbZone
    mWorld->UpdatePlayerZoneBB(playerPosition);
    //create chunks
    mWorld->setTextureSize(256,16,64,16,256,16);
    mWorld->initWorldBlocksLight();
    mWorld->buildMap();
	
    int	curchunkTarget = mWorld->getChunkId(playerPosition);
    dt = mTimer.GetDeltaTime();
    // load textures
    LoadTextures();
	Utils::Logger::Instance()->LogMessage("Load Sprites \n");
    mWorld->GetTexturesIds();

    // build custom mesh
    mWorld->buildblocksVerts();
    mWorld->buildcloudsVerts();
    mWorld->buildmobVerts();

    menuOptions = false;
    optionsMenuPos = 0;
	menuOptionsPag = 0;

    analogLeft = analogRight = analogUp = analogDown = false;

    walkSoundAccu = 0.0f;
    isWalking = false;

    mSoundMgr->playerSounds = mWorld->mainOptions.sounds;
    mWorld->playerZoneSize = Vector3(CHUNK_SIZE*mWorld->mainOptions.horizontalViewDistance,CHUNK_SIZE*mWorld->mainOptions.verticalViewDistance,CHUNK_SIZE*mWorld->mainOptions.horizontalViewDistance);
    mRender->fovv = mWorld->mainOptions.fov;
    RenderManager::InstancePtr()->SetPerspective(0, 480.0f / 272.0f, 0.18f, 1000.f);

	// from creative
	if(mWorld->gameModeWorld == 1) InitCreativeInventory();
	
    loadReady = true;

    mWorld->haveCompass = mWorld->HaveItemInBarSlots(Compass::getID());

    // cancel loading screen
    loading->KillLoadingScreen();
    delete loading;
	
	Utils::Logger::Instance()->LogMessage("Delete Loading Screen \n");
}

void StatePlay::LoadTextures()
{
	// incializar el game mode
	//int gamemode = mGlobalFun->GameMode;
	mGameMode->LoadTextures(mWorld->gameModeWorld);
	
	Utils::Logger::Instance()->LogMessage("Load GameMode Textures \n");
	
    //terrain texure
	barItems = TextureHelper::Instance()->GetTexture(TextureHelper::Items1);
    texture = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain1);
    texture_mips = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain2);
	
    waterAnimation = TextureHelper::Instance()->GetTexture(TextureHelper::WaterAnimation);
	cloudsTex = TextureHelper::Instance()->GetTexture(TextureHelper::clouds);

    invPlayerTex = TextureHelper::Instance()->GetTexture(TextureHelper::Steve);
    
    zombieTex = TextureHelper::Instance()->GetTexture(TextureHelper::zombieTexture);
	skeletonTex = TextureHelper::Instance()->GetTexture(TextureHelper::skeletonTexture);
    spiderTex = TextureHelper::Instance()->GetTexture(TextureHelper::spiderTexture);
    spidercaveTex = TextureHelper::Instance()->GetTexture(TextureHelper::cavespiderTexture);
    cowTex = TextureHelper::Instance()->GetTexture(TextureHelper::cowTexture);
	chickenTex = TextureHelper::Instance()->GetTexture(TextureHelper::chickenTexture);
	pigTex = TextureHelper::Instance()->GetTexture(TextureHelper::pigTexture);

    blue = TextureHelper::Instance()->GetTexture(TextureHelper::Blue);
    red = TextureHelper::Instance()->GetTexture(TextureHelper::Red);
	purple = TextureHelper::Instance()->GetTexture(TextureHelper::Purple);
    black = TextureHelper::Instance()->GetTexture(TextureHelper::Black);

    snowBall4 = TextureHelper::Instance()->GetTexture(TextureHelper::SnowBall3);
	arrow4 = TextureHelper::Instance()->GetTexture(TextureHelper::Arrow3);

    suntex = TextureHelper::Instance()->GetTexture(TextureHelper::Sun);
    moontex = TextureHelper::Instance()->GetTexture(TextureHelper::Moon);
    stars = TextureHelper::Instance()->GetTexture(TextureHelper::Stars);
    rainTex  = TextureHelper::Instance()->GetTexture(TextureHelper::rainTexture);
	
	Utils::Logger::Instance()->LogMessage("Load Textures \n");

    pumpkinMask = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::PumpkinMask));
    pumpkinMask->SetPosition(240,136);
    pumpkinMask->Scale(2.87f,2.84f);

    waterScreen = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Blue));
    waterScreen->SetPosition(240,136);
    waterScreen->Scale(30,17);

    // hud section //ui
    int utilsSize = TextureManager::Instance()->getWidth(TextureHelper::Instance()->GetTexture(TextureHelper::Utils));
    float utilScale = 364.0f/(float)utilsSize;
	
	int iconsSize = TextureManager::Instance()->getWidth(TextureHelper::Instance()->GetTexture(TextureHelper::Icons));
    float iconScale = 364.0f/(float)iconsSize;

    barSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),0*utilsSize/182,0*utilsSize/182,182*utilsSize/182,22*utilsSize/182);
    barSprite->SetPosition(240,230);
    barSprite->Scale(1,1);
	
	// normal ui
    selectSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),0*utilsSize/182,22*utilsSize/182,24*utilsSize/182,24*utilsSize/182);
    selectSprite->SetPosition(160,230);
    selectSprite->Scale(1,1);
	
	slot2Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),33*utilsSize/182,22*utilsSize/182,24*utilsSize/182,24*utilsSize/182);
    slot2Sprite->SetPosition(132,231);
    slot2Sprite->Scale(1,1);

    crossSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24*utilsSize/182,22*utilsSize/182,9*utilsSize/182,9*utilsSize/182);
    crossSprite->SetPosition(240,136);
    crossSprite->Scale(270.0f/utilsSize,270.0f/utilsSize);

	// buttons ui
	lSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Icons),111*iconsSize/182,51*iconsSize/182,16*iconsSize/182,9*iconsSize/182,true);
    lSprite->SetPosition(20,255);
    lSprite->Scale(1,1);
	
	rSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Icons),128*iconsSize/182,51*iconsSize/182,16*iconsSize/182,9*iconsSize/182,true);
    rSprite->SetPosition(70,255);
    rSprite->Scale(1,1);
	
	l2Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Icons),114*iconsSize/182,62*iconsSize/182,13*iconsSize/182,13*iconsSize/182,true);
    l2Sprite->SetPosition(20,255);
    l2Sprite->Scale(1,1);
	
	r2Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Icons),128*iconsSize/182,62*iconsSize/182,13*iconsSize/182,13*iconsSize/182,true);
    r2Sprite->SetPosition(20,255);
    r2Sprite->Scale(1,1);
	
	xIcon = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Icons2),16,34,15,16);
	TriIcon = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Icons2),0,17,15,16);
	SquIcon = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Icons2),16,17,15,16);
	oIcon = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Icons2),0,34,15,16);
	leftIcon = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Icons2),0,0,10,15);
	rightIcon = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Icons2),10,0,10,15);

	// tool point
    for(int j = 13; j >= 0; j--)
    {
        toolPointSprite[j] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),169*utilsSize/182,(49+(13-j)*2)*utilsSize/182,13*utilsSize/182,2*utilsSize/182,true);//200
        toolPointSprite[j]->SetPosition(240,136);
        toolPointSprite[j]->Scale(1,1);
    }
	
    //menu section
    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,0,95,12); // stand
    buttonSprite->SetPosition(240,150);
    buttonSprite->Scale(2,2);

	buttonAchiSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Achievements));
	buttonAchiSprite->SetPosition(402,ya);
	buttonAchiSprite->Scale(1,1);

	ya = -23;

    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,12,95,12); // stand selected
    sbuttonSprite->SetPosition(240,150);
    sbuttonSprite->Scale(2,2);

    nbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,24,95,12); // dark
    nbuttonSprite->SetPosition(240,150);
    nbuttonSprite->Scale(1.5,1.5);

	moverSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,60,6,12);
	moverSprite->Scale(1.5,1.5);
	
    // inventory section

    //int invGuiSize = TextureManager::Instance()->getWidth(TextureHelper::Instance()->GetTexture(TextureHelper::inv));
    //float invGuiScale = 352.0f/(float)invGuiSize;

    int invArrowSize = TextureManager::Instance()->getWidth(TextureHelper::Instance()->GetTexture(TextureHelper::furArrow));
    float invArrowScale = 44.0f/(float)invArrowSize;
	
	int invFireSize = TextureManager::Instance()->getWidth(TextureHelper::Instance()->GetTexture(TextureHelper::furFire));
    float invFireScale = 28.0f/(float)invFireSize;

    for(int j = 0; j <= 21; j++)
    {
        furArrowSprite[j] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::furArrow),0,0,(1*j)*invArrowSize/22.0f,16*invArrowSize/22.0f,true);//200
        furArrowSprite[j]->SetPosition(240,136);
        furArrowSprite[j]->Scale(1,1);
    }

    for(int j = 0; j <= 13; j++)
    {
        furFireSprite[13-j] = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::furFire),0,j*invFireSize/14.0f,14*invFireSize/14.0f,(14-j)*invFireSize/14.0f,true);//200
        furFireSprite[13-j]->SetPosition(240,136);
        furFireSprite[13-j]->Scale(1,1);
    }

    selectInvSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::cursor));//200
    selectInvSprite->SetPosition(168,149);

    invCellSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::invCell));//200
    invCellSprite->SetPosition(240,136);
    invCellSprite->Scale(1,1);
	
	invCraftSelSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::crtSelect));
	invCraftSelSprite->SetPosition(108,100);
	
	invCraftSelPagSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::crtSelectPag));
	invCraftSelPagSprite->SetPosition(110,28);
	
	invCraft2Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::crt2));
	invCraft2Sprite->SetPosition(155,208);
	
	cellRedSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::crtRed));
	cellRedSprite->SetPosition(108,190);
	
	cellRedSprite2 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::crtRed));
	cellRedSprite2->SetPosition(108,190);
	cellRedSprite2->Scale(1.5,1.5);
	
	selectInvVillSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::SelectinvTrad));
	selectInvVillSprite->SetPosition(175,78);
	
	Utils::Logger::Instance()->LogMessage("Finish Textures \n");

    skyLight = new SkyLight();
    skyMoonLight = new SkyLight();
    skyBox = new SkyBox();
    destroyer = new Destroyer();
    starsBox = new StarsBox();
    invPlayer = new InventoryPlayer();
	
	Utils::Logger::Instance()->LogMessage("Load Instances \n");
}

void StatePlay::SetCreativePage(char page)
{

}

void StatePlay::InitCreativeInventory()
{	
	inventoryCoItems.push_back(CobbleStone::getID());
	inventoryCoItems.push_back(StoneBrick::getID());
	inventoryCoItems.push_back(CrackedStoneBrick::getID());
	inventoryCoItems.push_back(CarvedStoneBrick::getID());
	inventoryCoItems.push_back(Diamond::getID());
	inventoryCoItems.push_back(Gold::getID());
	inventoryCoItems.push_back(Iron::getID());
	inventoryCoItems.push_back(LapisBlock::getID());
	inventoryCoItems.push_back(BrickBlock::getID());
	inventoryCoItems.push_back(MossyCobblestone::getID());
	inventoryCoItems.push_back(Slab::getID());
    inventoryCoItems.push_back(StoneSandHalfBlock::getID());
    inventoryCoItems.push_back(OakHalfBlock::getID());
    inventoryCoItems.push_back(BirchHalfBlock::getID());
    inventoryCoItems.push_back(SpruceHalfBlock::getID());
    inventoryCoItems.push_back(CobbleHalfBlock::getID());
    inventoryCoItems.push_back(BrickHalfBlock::getID());
    inventoryCoItems.push_back(HalfStoneBrick::getID());
	inventoryCoItems.push_back(BlockOfQuartz::getID());
	inventoryCoItems.push_back(PillarQuartzBlock::getID());
	inventoryCoItems.push_back(ChiseledQuartzBlock::getID());
	inventoryCoItems.push_back(OakPlanks::getID());
    inventoryCoItems.push_back(BirchPlanks::getID());
    inventoryCoItems.push_back(SprucePlanks::getID());
	inventoryCoItems.push_back(IronBarsItem::getID());
    inventoryCoItems.push_back(GlassPanelItem::getID());
	inventoryCoItems.push_back(GlassBlock::getID());
	inventoryCoItems.push_back(CoalBlock::getID());
    inventoryCoItems.push_back(RedstoneBlock::getID());
	inventoryCoItems.push_back(DoorItem::getID());
	inventoryCoItems.push_back(WoodenFence::getID());
    inventoryCoItems.push_back(BirchFence::getID());
    inventoryCoItems.push_back(SpruceFence::getID());
    inventoryCoItems.push_back(LadderItem::getID());
    inventoryCoItems.push_back(WoodenStair1::getID());
    inventoryCoItems.push_back(BirchStair1::getID());
    inventoryCoItems.push_back(SpruceStair1::getID());
    inventoryCoItems.push_back(CobbleStair1::getID());
    inventoryCoItems.push_back(BrickStair1::getID());
    inventoryCoItems.push_back(TrapdoorClosed1::getID());
	inventoryCoItems.push_back(WhiteTerracotta::getID());
    inventoryCoItems.push_back(OrangeTerracotta::getID());
	inventoryCoItems.push_back(Terracotta::getID());
	inventoryCoItems.push_back(MagnetaTerracotta::getID());
	inventoryCoItems.push_back(LightBlueTerracotta::getID());
    inventoryCoItems.push_back(YellowTerracotta::getID());
	inventoryCoItems.push_back(LimeTerracotta::getID());
	inventoryCoItems.push_back(PinkTerracotta::getID());
    inventoryCoItems.push_back(GrayTerracotta::getID());
    inventoryCoItems.push_back(LightGrayTerracotta::getID());
	inventoryCoItems.push_back(CyanTerracotta::getID());
	inventoryCoItems.push_back(PurpleTerracotta::getID());
	inventoryCoItems.push_back(BlueTerracotta::getID());
	inventoryCoItems.push_back(BrownTerracotta::getID());
	inventoryCoItems.push_back(GreenTerracotta::getID());
    inventoryCoItems.push_back(RedTerracotta::getID());
    inventoryCoItems.push_back(BlackTerracotta::getID());
	for(int i = BlackWoolBlock::getID(); i <= WhiteWoolBlock::getID(); i++)
    {
        inventoryCoItems.push_back(i);
    }
	for(int i = BlackWoolCarpet::getID(); i <= WhiteWoolCarpet::getID(); i++)
    {
        inventoryCoItems.push_back(i);
    }
	
	
	for(int i = WoodenPickaxe::getID(); i <= Scissors::getID(); i++)
    {
        inventoryEqItems.push_back(i);
    }
    inventoryEqItems.push_back(FlintAndSteel::getID());
    for(int i = LeatherHelmet::getID(); i <= GoldenBoots::getID(); i++)
    {
        inventoryEqItems.push_back(i);
    }
	inventoryEqItems.push_back(Bow0::getID());
	inventoryEqItems.push_back(Arrow::getID());
	inventoryEqItems.push_back(Shield::getID());
	inventoryEqItems.push_back(Apple::getID());
    inventoryEqItems.push_back(GoldenApple::getID());
	inventoryEqItems.push_back(Bowl::getID());
    inventoryEqItems.push_back(MooshroomBowl::getID());
    inventoryEqItems.push_back(WhiteBread::getID());
    inventoryEqItems.push_back(RawBeef::getID());
    inventoryEqItems.push_back(Steak::getID());
	inventoryEqItems.push_back(RawPorkchop::getID());
	inventoryEqItems.push_back(CookedPorkchop::getID());
	inventoryEqItems.push_back(RawMutton::getID());
	inventoryEqItems.push_back(CookedMutton::getID());
	inventoryEqItems.push_back(RawChicken::getID());
	inventoryEqItems.push_back(CookedChicken::getID());
	inventoryEqItems.push_back(SnowBallItem::getID());
	inventoryEqItems.push_back(BakedPotato::getID());
	
    inventoryDeItems.push_back(DiamondItem::getID());
    inventoryDeItems.push_back(IronBar::getID());
    inventoryDeItems.push_back(GoldenBar::getID());
	inventoryDeItems.push_back(Emerald::getID());
	inventoryDeItems.push_back(Coal::getID());
    inventoryDeItems.push_back(Clock::getID());
    inventoryDeItems.push_back(Compass::getID());
	inventoryDeItems.push_back(ChestBlock3::getID());
    inventoryDeItems.push_back(CraftingTable::getID());
    inventoryDeItems.push_back(FurnaceOff::getID());
    inventoryDeItems.push_back(TNTBlock::getID());
    inventoryDeItems.push_back(ShelfBlock::getID());
    inventoryDeItems.push_back(NoteBlock::getID());
    inventoryDeItems.push_back(JukeBox::getID());
	inventoryDeItems.push_back(TorchItem::getID());
	inventoryDeItems.push_back(ItemFrameItem::getID());
    inventoryDeItems.push_back(BedItem::getID());
	inventoryDeItems.push_back(Paper::getID());
    inventoryDeItems.push_back(Book::getID());
	inventoryDeItems.push_back(Feather::getID());
	inventoryDeItems.push_back(String::getID());
	inventoryDeItems.push_back(Leather::getID());
    inventoryDeItems.push_back(Brick::getID());
	inventoryDeItems.push_back(Stick::getID());
	inventoryDeItems.push_back(Disk1::getID());
    inventoryDeItems.push_back(Disk2::getID());
    inventoryDeItems.push_back(Disk3::getID());
    inventoryDeItems.push_back(Disk4::getID());
    inventoryDeItems.push_back(Disk5::getID());
    inventoryDeItems.push_back(Disk6::getID());
    inventoryDeItems.push_back(Disk7::getID());
    inventoryDeItems.push_back(Disk8::getID());
    inventoryDeItems.push_back(Disk9::getID());
    inventoryDeItems.push_back(Disk10::getID());
    inventoryDeItems.push_back(Disk11::getID());
    inventoryDeItems.push_back(Disk12::getID());
	

    inventoryNaItems.push_back(RockBlock::getID());
    inventoryNaItems.push_back(DiamondOre::getID());
    inventoryNaItems.push_back(GoldBlock::getID());
    inventoryNaItems.push_back(IronOre::getID());
    inventoryNaItems.push_back(CoalOre::getID());
    inventoryNaItems.push_back(LapisOre::getID());
    inventoryNaItems.push_back(RedstoneOre::getID());
    inventoryNaItems.push_back(ClayBlock::getID());
    inventoryNaItems.push_back(IronBlock::getID()); // bedrock
    inventoryNaItems.push_back(Obsidian::getID());
    inventoryNaItems.push_back(WoodBlock::getID());
    inventoryNaItems.push_back(WhiteWoodBlock::getID()); // birch
    inventoryNaItems.push_back(DarkWoodBlock::getID()); // spruce
    inventoryNaItems.push_back(LeavesBlock::getID());
    inventoryNaItems.push_back(BirchLeaves::getID());
    inventoryNaItems.push_back(SpruceLeaves::getID());
    inventoryNaItems.push_back(DirtBlock::getID());
    inventoryNaItems.push_back(GrassBlock::getID());
    inventoryNaItems.push_back(SandBlock::getID());
    inventoryNaItems.push_back(SandStone::getID());
	inventoryNaItems.push_back(RedSandBlock::getID());
    inventoryNaItems.push_back(Gravel::getID());
    inventoryNaItems.push_back(OakSaplingItem::getID());
    inventoryNaItems.push_back(BirchSaplingItem::getID());
    inventoryNaItems.push_back(SpruceSaplingItem::getID());
    inventoryNaItems.push_back(IceBlock::getID());
	inventoryNaItems.push_back(WaterBlock::getID());
    inventoryNaItems.push_back(Lava::getID());
    inventoryNaItems.push_back(SnowBlock::getID());
    inventoryNaItems.push_back(SnowSoil::getID());
    inventoryNaItems.push_back(Snow2::getID());
    inventoryNaItems.push_back(Flower1Item::getID());
    inventoryNaItems.push_back(Flower2Item::getID());
    inventoryNaItems.push_back(MooshroomItem1::getID());
    inventoryNaItems.push_back(MooshroomItem2::getID());
    inventoryNaItems.push_back(CactusBlock::getID());
    inventoryNaItems.push_back(MelonBlock::getID());
    inventoryNaItems.push_back(Pumpkin3::getID());
    inventoryNaItems.push_back(JackOLantern3::getID());
    inventoryNaItems.push_back(HayBale::getID());
	inventoryNaItems.push_back(Netherrack::getID());
	inventoryNaItems.push_back(QuartzOre::getID());
	inventoryNaItems.push_back(SoilBlock::getID());
	inventoryNaItems.push_back(Glowstone::getID());
	inventoryNaItems.push_back(GlowstoneDust::getID());
	inventoryNaItems.push_back(NetherBrick::getID());
	inventoryNaItems.push_back(NetherBrickFence::getID());
	inventoryNaItems.push_back(NetherQuartz::getID());
    inventoryNaItems.push_back(WheatSeeds::getID());
    inventoryNaItems.push_back(Wheat::getID());
	inventoryNaItems.push_back(SpiderEye::getID());
    inventoryNaItems.push_back(Busket::getID());
    inventoryNaItems.push_back(MilkBusket::getID());
    inventoryNaItems.push_back(Clay::getID());
    inventoryNaItems.push_back(CaneItem::getID());
    inventoryNaItems.push_back(Bone::getID());
    inventoryNaItems.push_back(BoneMeal::getID());
    inventoryNaItems.push_back(Cookie::getID());
    inventoryNaItems.push_back(MelonSeeds::getID());
    inventoryNaItems.push_back(PumpkinSeeds::getID());
    inventoryNaItems.push_back(MelonItem::getID());
    inventoryNaItems.push_back(Potato::getID());
    inventoryNaItems.push_back(PoisonedPotato::getID());
    inventoryNaItems.push_back(Carrot::getID());
    inventoryNaItems.push_back(CowEGG::getID());
    inventoryNaItems.push_back(SheepEGG::getID());
    inventoryNaItems.push_back(ChickenEGG::getID());
    inventoryNaItems.push_back(PigEGG::getID());
    inventoryNaItems.push_back(ZombieEGG::getID());
	inventoryNaItems.push_back(SkeletonEGG::getID());
	inventoryNaItems.push_back(SpidercaveEGG::getID());
	inventoryNaItems.push_back(SpiderEGG::getID());
    inventoryNaItems.push_back(CreeperEGG::getID());
    inventoryNaItems.push_back(PigmanEGG::getID());
    inventoryNaItems.push_back(WitherSkeletonEGG::getID());
    inventoryNaItems.push_back(VillagerEGG::getID());
	inventoryNaItems.push_back(WolfEGG::getID());
    //inventoryItems.push_back(CreeperHead::getID());


    creativePage = 0;
    creativePageMax1 = inventoryCoItems.size() / 27;
	creativePageMax2 = inventoryEqItems.size() / 27;
	creativePageMax3 = inventoryDeItems.size() / 27;
	creativePageMax4 = inventoryNaItems.size() / 27;
}

void StatePlay::SetDayTimeAfterLoad()
{

}

void StatePlay::Enter()
{
    RenderManager::InstancePtr()->SetPerspective(55.0f, 480.0f / 272.0f, 0.18f, 1000.0f);
}

void StatePlay::CleanUp()
{
	Utils::Logger::Instance()->LogMessage("Init Clear StatePlay \n");
	
	mGameMode->CleanUp();
	
	Utils::Logger::Instance()->LogMessage("Clear StatePlay \n");
	
    if(mSnowBalls.empty() == false)
    {
        for(unsigned int i = 0; i < mSnowBalls.size(); i++)
        {
            delete mSnowBalls[i];
        }
        mSnowBalls.clear();
    }
	
	if(mArrowEns.empty() == false)
    {
        for(unsigned int i = 0; i < mArrowEns.size(); i++)
        {
            delete mArrowEns[i];
        }
        mArrowEns.clear();
    }
	
	if(mArrows.empty() == false)
    {
        for(unsigned int i = 0; i < mArrows.size(); i++)
        {
            delete mArrows[i];
        }
        mArrows.clear();
    }
	
	// from creative
	inventoryCoItems.clear();
	inventoryEqItems.clear();
	inventoryDeItems.clear();
	inventoryNaItems.clear();

    delete mRender->mCam;
    mRender->mCam = NULL;

    delete invCellSprite;
    delete buttonSprite;
    delete sbuttonSprite;
    delete nbuttonSprite;
    delete moverSprite;
	delete buttonAchiSprite;
	
	delete xIcon;
	delete TriIcon;
	delete SquIcon;
	delete oIcon;
	
	delete leftIcon;
	delete rightIcon;

	delete selectInvVillSprite;
    delete selectSprite;
	delete slot2Sprite;
    delete crossSprite;
	delete lSprite;
    delete rSprite;
    delete l2Sprite;
    delete r2Sprite;
    delete selectInvSprite;

    delete skyLight;
    delete skyMoonLight;
    delete skyBox;
    delete destroyer;
    delete starsBox;
    delete invPlayer;
	
	delete invCraftSelSprite;
	delete invCraftSelPagSprite;
	delete invCraft2Sprite;
	delete cellRedSprite;
	delete cellRedSprite2;
	
    delete waterScreen;
    delete pumpkinMask;

    for(unsigned int i = 0; i <= 13; i++)
    {
        delete furFireSprite[i];
    }

    for(unsigned int i = 0; i <= 21; i++)
    {
        delete furArrowSprite[i];
    }

    for(unsigned int i = 0; i <= 13; i++)
    {
        delete toolPointSprite[i];
    }
	
    delete mWorld;
}

void StatePlay::Pause()
{

}

void StatePlay::Resume()
{

}

int StatePlay::FindChestId(int x, int y, int z)
{
    int o;
    int address;
    o = -1;
    address = x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_HEIGHT;

    for(unsigned int i = 0; i < mWorld->mChests.size(); i++)
    {
        Chest* NewChest = mWorld->mChests[i];
		if (mSoundMgr->Ram32 == false)
		{
			if(NewChest->chestAddress == address)
			{
				o = i;
				break;
			}
		}
		else
		{
			if(NewChest->chestFatAddress == address)
			{
				o = i;
				break;
			}
		}
    }

    return o;
}

int StatePlay::FindFurnaceId(int x, int y, int z)
{
    int o;
    o = -1;
    for(unsigned int i = 0; i < mWorld->mFurnaces.size(); i++)
    {
        Furnace* NewFurnace = mWorld->mFurnaces[i];
        if(NewFurnace->furnaceX == x && NewFurnace->furnaceY == y && NewFurnace->furnaceZ == z)
        {
            o = i;
            break;
        }
    }

    return o;
}

void StatePlay::CheckForFurnFuel(Furnace* Fur)
{
    int furnItem;

    furnItem = -1;

    if(Fur->furnaceSlotId[0] < 250 && Fur->furnaceSlotId[0] != -1)
    {
        furnItem = mWorld->blockTypes[Fur->furnaceSlotId[0]].furnItem;
    }

    if(Fur->furnaceSlotId[0] >= 250)
    {
        furnItem = mWorld->itemTypes[Fur->furnaceSlotId[0]-250].furnItem;
    }

    if(Fur->fuelTime <= 0 && furnItem != -1)
    {
        if(Fur->furnaceSlotId[1] == -1)
            return;

        bool used = false;

        switch(Fur->furnaceSlotId[1])
        {
        case 8:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 31:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 34:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 296:
            Fur->fuelTime = 5;
            used = true;
        break;
        case 276:
            Fur->fuelTime = 5;
            used = true;
        break;
        case 277:
            Fur->fuelTime = 80;
            used = true;
        break;
        case 292:
            Fur->fuelTime = 1000;
            used = true;
        break;
        case 306:
            Fur->fuelTime = 30;
            used = true;
        break;
        case 59:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 71:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 72:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 100:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 105:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 125:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 155:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 156:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 214:
            Fur->fuelTime = 800;
            used = true;
        break;
        case 250:
            Fur->fuelTime = 10;
            used = true;
        break;
        case 255:
            Fur->fuelTime = 10;
            used = true;
        break;
        case 260:
            Fur->fuelTime = 10;
            used = true;
        break;
        case 265:
            Fur->fuelTime = 10;
            used = true;
        break;
        case 270:
            Fur->fuelTime = 10;
            used = true;
        break;
        }

        if(used == true)
        {
            Fur->furnaceSlotAm[1] -= 1;
            if(Fur->furnaceSlotAm[1] == 0)
            {
                Fur->furnaceSlotAm[1] = -1;
                Fur->furnaceSlotId[1] = -1;
                Fur->furnaceSlotSt[1] = 0;
            }
        }
        else
        {
            Fur->meltingTime = 0.0f;
        }
    }
}

void StatePlay::CheckForFurnWorking(Furnace* Fur)
{
    int furnItem;

    furnItem = -1;

    if(Fur->furnaceSlotId[0] < 250 && Fur->furnaceSlotId[0] != -1)
    {
        furnItem = mWorld->blockTypes[Fur->furnaceSlotId[0]].furnItem;
    }

    if(Fur->furnaceSlotId[0] >= 250)
    {
        furnItem = mWorld->itemTypes[Fur->furnaceSlotId[0]-250].furnItem;
    }

    if(furnItem != -1)
    {
        if(Fur->fuelTime > 0)
        {
            if(Fur->furnaceSlotId[2] == furnItem || Fur->furnaceSlotId[2] == -1)
            {
                if(Fur->furnaceSlotAm[2] <= 63)
                {
                    Fur->working = true;
                }
            }
            if(Fur->furnaceSlotId[2] != furnItem && Fur->furnaceSlotId[2] != -1)
            {
                Fur->working = false;
                Fur->meltingTime = 0;
            }
        }
        else
        {
            Fur->working = false;
            Fur->meltingTime = 0;
        }
        if(Fur->fuelTime == 0)
        {
            Fur->working = false;
            Fur->meltingTime = 0;
        }
    }
    else
    {
        Fur->working = false;
        Fur->meltingTime = 0;
    }
}

void StatePlay::ReadyFurnSmelting(Furnace* Fur)
{
    int furnItem;

    if(Fur->furnaceSlotId[0] < 250)
    {
        furnItem = mWorld->blockTypes[Fur->furnaceSlotId[0]].furnItem;
    }

    if(Fur->furnaceSlotId[0] >= 250)
    {
        furnItem = mWorld->itemTypes[Fur->furnaceSlotId[0]-250].furnItem;
    }

    if(furnItem != -1)
    {
        if(Fur->furnaceSlotId[2] == furnItem)
        {
           Fur->furnaceSlotAm[2] += 1;
        }
        if(Fur->furnaceSlotId[2] == -1)
        {
            Fur->furnaceSlotId[2] = furnItem;
            Fur->furnaceSlotSt[2] = true;
            Fur->furnaceSlotAm[2] = 1;
        }

        Fur->furnaceSlotAm[0] -= 1;
        if(Fur->furnaceSlotAm[0] <= 0)
        {
            Fur->furnaceSlotId[0] = -1;
            Fur->furnaceSlotAm[0] = -1;
            Fur->furnaceSlotSt[0] = 0;
        }
    }
}

int StatePlay::UniInvId(int itemId, int reSlot)
{
	if ((itemId == 34 || itemId == 155 || itemId == 156) && reSlot == 3401) {
        return 3401; // ID unificado para todas las maderas
    }
	else if ((itemId >= 10 && itemId <= 24) && reSlot == 1001) {
        return 1001; // ID unificado para todas las lanas
    }
	else if ((itemId == 7 || itemId == 227) && reSlot == 7001) {
        return 7001; // ID unificado para todas las arenas
    }

    return itemId;
}

void StatePlay::HandleEvents(StateManager* sManager)
{
    //update delta time
    dt = mTimer.GetDeltaTime();

    cameraSpeed = 2.0f * dt;
    cameraMoveSpeed = 4.00f * dt;

    //free memory counter
    freeMemoryTimer += dt;
    if(menuState != 0)
    {
        if(freeMemoryTimer > 3.0f)
        {
            freeMemory = mSystemMgr->ramAvailable();
            freeMemoryTimer = 0.0f;
        }
    }
    else
    {
        if(freeMemoryTimer > 15.0f)
        {
            freeMemory = mSystemMgr->ramAvailable();
            freeMemoryTimer = 0.0f;
        }
    }

    // update input
    mSystemMgr->InputUpdate();

    if(mWorld->HP > 0 && sleepTime <= 0.0f)
    {
		// altura del jugador
        mWorld->playerGrowth = 1.65f;
		
		// game state
        if(menuState == 0) // infierno
        {
			/*if(InHellPortal)
			{
				mSoundMgr->StopHell();
				mSoundMgr->StopAmbient();
				mSoundMgr->StopDiskTrack();
							
				if(mWorld->currentDimension == 0)
				{
					mGlobalFun->filename = saveFileName.c_str();
								
					if(mWorld->createdHell == false)
					{
						mGlobalFun->CreateHell = true;
						mGlobalFun->teleported = true;
					}
					else
					{
						mGlobalFun->CreateHell = false;
						mGlobalFun->teleported = true;
					}
								
					mGlobalFun->thisWorld = false;
					mGlobalFun->GameMode = mWorld->gameModeWorld;
				}
				else
				{
					mGlobalFun->filename = saveFileName.c_str();
					mGlobalFun->thisWorld = true;
					mGlobalFun->CreateHell = false;
					mGlobalFun->teleported = true;
					mGlobalFun->GameMode = mWorld->gameModeWorld;
				}
				
				mWorld->SaveCompressedWorld(saveFileName.c_str(), saveFileName.c_str());
				mGlobalFun->Load = 2;
				TextureHelper::Instance()->LoadConstTexture();				
				sManager->PopState();		
			}*/

            if(invEn == false && craft3xEn == false && chestEn == false && furnaceEn == false && villEn == false)
            {
                if(tickShowSlotName > -0.1f)
                {
                    tickShowSlotName -= dt;
                }
				
				//### from creative ###//
				
				if(mWorld->gameModeWorld == 1)
				{
					// fly mode: message tick
					if(tickShowFlymodeMessage > -0.1f)
					{
						tickShowFlymodeMessage -= dt;
					}
					
					// fly mode: press button -> tick time
					if(keyPressed(InputHelper::Instance()->getButtonToAction(12)) && crouch == false)
					{
						if(tickFlyTime > 0.75f && tickFlyTime < 0.9f)
						{
							canFly = !canFly;
							tickShowFlymodeMessage = 1.2f;
							tickFlyTime = 1.0f;
						}
						else
						{
							tickFlyTime = 1.0f;
						}
					}
					tickFlyTime -= dt;
				}
				
                //switch right
                if(keyPressed(InputHelper::Instance()->getButtonToAction(9)))
                {
                    if (mWorld->invId[27+barPosition] != -1)
                    {
                        changeY = -0.16f;
                        anim[0] = 1;
						
						if(AtackBow == true)
						{
							tickBow = 0.0f;
							AtackBow = false;
							changeX = 0.0f;
							changeY = 0.0f;	
							slowWalk = false;
							
							for(int i = 27; i < 36; i++)
							{
								if(mWorld->invId[i] == Bow1::getID() || mWorld->invId[i] == Bow2::getID() || mWorld->invId[i] == Bow3::getID())
								{
									mWorld->invId[i] = Bow0::getID();
								}
							}
						}
                    }
                    barPosition != 8 ? barPosition ++ : barPosition = 0;

                    selectSprite->SetPosition(160 + (barPosition * 20),230);

                    tickShowSlotName = 1.25f;

                    startDt = 0;
                    dT = 0;
                    dET = 0;
                    dStd = -1;
                }

                //switch left
                if(keyPressed(InputHelper::Instance()->getButtonToAction(8)))
                {
                    if (mWorld->invId[27+barPosition] != -1)
                    {
                        changeY = -0.16f;
                        anim[0] = 1;
						
						if(AtackBow == true)
						{
							tickBow = 0.0f;
							AtackBow = false;
							changeX = 0.0f;
							changeY = 0.0f;	
							slowWalk = false;
							
							for(int i = 27; i < 36; i++)
							{
								if(mWorld->invId[i] == Bow1::getID() || mWorld->invId[i] == Bow2::getID() || mWorld->invId[i] == Bow3::getID())
								{
									mWorld->invId[i] = Bow0::getID();
								}
							}
						}
                    }
                    barPosition != 0 ? barPosition -- : barPosition = 8;

                    selectSprite->SetPosition(160 + (barPosition * 20),230);

                    tickShowSlotName = 1.25f;

                    startDt = 0;
                    dT = 0;
                    dET = 0;
                    dStd = -1;
                }

                // drop 1 item
                if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
                {
                    if(keyPressed(InputHelper::Instance()->getButtonToAction(14)))
                    {
                        if(mWorld->invId[27+barPosition] > 0)
                        {
                            Vector3 dropVelocity = Vector3(0,0,0);

                            dropVelocity.x = (cosf((fppCam->horAngle/180.0f)*PI))*4.0f;
                            dropVelocity.y = 2.0f;
                            dropVelocity.z = (sinf((fppCam->horAngle/180.0f)*PI))*4.0f;
							
							if (mWorld->invId[27+barPosition] == Bow1::getID() || mWorld->invId[27+barPosition] == Bow2::getID() || mWorld->invId[27+barPosition] == Bow3::getID())
							{
								mWorld->invId[27+barPosition] = Bow0::getID();
								tickBow = 0.0f;
								AtackBow = false;
								changeY = 0.0f;
								changeX = 0.0f;
								slowWalk = false;
							}

                            if(mWorld->invSt[27+barPosition] == true)
                            {
                                if(mWorld->invAm[27+barPosition] > 0)
                                {
                                    mWorld->invAm[27+barPosition] -= 1;
                                    mWorld->DropThisNoAlign(mWorld->invId[27+barPosition],1,mWorld->invSt[27+barPosition],Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y-0.25f,fppCam->m_vPosition.z),dropVelocity);

                                    if(mWorld->invAm[27+barPosition] == 0)
                                    {
                                        mWorld->invAm[27+barPosition] = -1;
                                        mWorld->invSt[27+barPosition] = 0;
                                        mWorld->invId[27+barPosition] = -1;
                                    }
                                }
                            }
                            else
                            {
                                mWorld->DropThisNoAlign(mWorld->invId[27+barPosition],mWorld->invAm[27+barPosition],mWorld->invSt[27+barPosition],Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y-0.25f,fppCam->m_vPosition.z),dropVelocity);

                                mWorld->invAm[27+barPosition] = -1;
                                mWorld->invSt[27+barPosition] = 0;
                                mWorld->invId[27+barPosition] = -1;
                            }
                        }
                        return;
                    }
                }

                //open menu
                if(sleepTime == 0.0f)
                {
                    if(keyPressed(InputHelper::Instance()->getButtonToAction(15)))
                    {
                        menuState = 1;
                        menuOptions = false;
                        optionsMenuPos = 0;
						menuOptionsPag = 0;
                    }
                }
				
				//idle animation
				if(jumping == 0)
				{
					float animSpeed = 0.3*PI*dt;
					
					if(bobTipo == 0)
					{
						if (bobCiclo < PI)
						{
							bobCiclo += animSpeed;
						}
						else
						{
							bobTipo = 1;
						}
					}
					else
					{
						if (bobCiclo > 0)
						{
							bobCiclo -= animSpeed;
						}
						else
						{
							bobTipo = 0;
						}
					}
					
					float idleLost = sinf(bobCiclo - (3.14/2) + 3.14)/200;
					idle_y = idleLost;
				}
				
                //camera rotate up
                if(keyHold(InputHelper::Instance()->getButtonToAction(4)))
                {
                    if (startDt == true)	//start destroy
                    {
                        startDt = false;
                        dStd = -1;
                    }
                    fppCam->PitchView(1.0f*dt);
                    fppCam->PitchView(1.0f*dt);
                    shift_y > -0.06f ? shift_y -= 0.24*dt : shift_y = -0.06f;
                }
                else
                {
                    if (shift_y < 0.0f)
                    {
                        shift_y += 0.24*dt;
                    }
                    if(abs(shift_y) <= 0.001f)
                    {
                        shift_y = 0.0f;
                    }
                }

                //camera rotate down
                if(keyHold(InputHelper::Instance()->getButtonToAction(5)))
                {
                    if (startDt == true)
                    {
                        startDt = false;
                        dStd = -1;
                    }
                    fppCam->PitchView(-1.0f*dt);
                    fppCam->PitchView(-1.0f*dt);
                    shift_y < 0.06f ? shift_y += 0.24*dt : shift_y = 0.06f;
                }
                else
                {
                    if (shift_y > 0.0f)
                    {
                        shift_y -= 0.24*dt;
                    }
                    if(abs(shift_y) <= 0.001f)
                    {
                        shift_y = 0.0f;
                    }
                }

                //camera rotate right
                if(keyHold(InputHelper::Instance()->getButtonToAction(7)))
                {
                    if (startDt == true)
                    {
                        startDt = false;
                        dStd = -1;
                    }
                    fppCam->RotateView(-2.0f*dt,0,1,0);
                    shift_x > -0.06f ? shift_x -= 0.24*dt : shift_x = -0.06f;
                }
                else
                {
                    if (shift_x < 0.0f)
                    {
                        shift_x += 0.24*dt;
                    }
                    if(abs(shift_x) <= 0.001f)
                    {
                        shift_x = 0.0f;
                    }
                }

                //camera rotate left
                if(keyHold(InputHelper::Instance()->getButtonToAction(6)))
                {
                    if (startDt == true)
                    {
                        startDt = false;
                        dStd = -1;
                    }
                    fppCam->RotateView(2.0f*dt,0,1,0);
                    shift_x < 0.06f ? shift_x += 0.24*dt : shift_x = 0.06f;
                }
                else
                {
                    if (shift_x > 0.0f)
                    {
                        shift_x -= 0.24*dt;
                    }
                    if(abs(shift_x) <= 0.001f)
                    {
                        shift_x = 0.0f;
                    }
                }

                //camera moving
                moving = false;
                moveForward = false;
                bool diagonleMoving = false;
				
				/* EDT MODE CONTROLS 
				
				*/
				
				// EDIT MODE ENABLE OR DISABLE
				if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
				{
					editMode ? editMode = false : editMode = true;
				}
				
				// EDIT MODE FUNCTIONS	// animaciones
				if(editMode == true)
				{
					// Edit Mode Tipo de Suma
					if(keyPressed(InputHelper::Instance()->getButtonToAction(0)))
					{
						/*if (editModeType) {
							editSum = 0.1f;
							editModeType = false;
						} else {
							editSum = 0.01f;
							editModeType = true;
						}*/
						editModeType ++;
						if (editModeType >= 4) editModeType = 1;
						
						if (editModeType == 1) editSum = 0.1f;
						if (editModeType == 2) editSum = 0.01f;
						if (editModeType == 3) editSum = 0.001f;
					}
					
					// Edit Mode Move's X Axis
					if(keyPressed(InputHelper::Instance()->getButtonToAction(2))){
						//editModeManager == true ? animationSpeed += editSum : animationSpeed -= editSum;
						editModeManager == true ? editModeMoveX += editSum : editModeMoveX -= editSum;
						//editModeManager == true ? swingAnimValueY += editSum : swingAnimValueY -= editSum;
					}
					
					// Edit Mode Move's Y Axis
					if(keyPressed(InputHelper::Instance()->getButtonToAction(1))) editModeManager == true ? editModeMoveY += editSum : editModeMoveY -= editSum;

					// Edit Mode Move's Z Axis
					if(keyPressed(InputHelper::Instance()->getButtonToAction(3))) editModeManager == true ? editModeMoveZ += editSum : editModeMoveZ -= editSum;
					
					// Edit Mode Rotate X Axis
					if(keyPressed(InputHelper::Instance()->getButtonToAction(6))) editModeManager == true ? editModeRotateX += editSum : editModeRotateX -= editSum;
					
					// Edit Mode Rotate Y Axis
					if(keyPressed(InputHelper::Instance()->getButtonToAction(5))) editModeManager == true ? editModeRotateY += editSum : editModeRotateY -= editSum;
					
					// Edit Mode Rotate Z Axis
					if(keyPressed(InputHelper::Instance()->getButtonToAction(7))) editModeManager == true ? editModeRotateZ += editSum : editModeRotateZ -= editSum;
					
					// Edit Mode Manager Scale
					if(keyPressed(InputHelper::Instance()->getButtonToAction(4))) editModeManager == true ? editModeScale += editSum : editModeScale -= editSum;
					
					// Edit Mode Manager Valor
					if(keyPressed(InputHelper::Instance()->getButtonToAction(14))) editModeManager == true ? editModeManager = false : editModeManager = true;
					
					// Animacion | DERECHA
					//if(keyPressed(InputHelper::Instance()->getButtonToAction(9))) editModeManager == true ? swingAmountX += editSum : swingAmountX -= editSum;
					
					// Animacion | IZQUIERDA
					//if(keyPressed(InputHelper::Instance()->getButtonToAction(8))) editModeManager == true ? swingAmountY += editSum : swingAmountY -= editSum;
				}
				
				// moving character
                if(sleepTime == 0.0f)
                {
                    //move forward
                    if(keyHold(InputHelper::Instance()->getButtonToAction(0)))
                    {
                        float slowdown = 0.8f;
                        float slowdown2 = 1.0f;
                        if(startDt == true)
                        {
                            startDt = false;
                            dStd = -1;
                        }
						
                        moving = true;
                        moveForward = true;

                        if(walkingOnGround == false)
                        {
                            slowdown -= 0.2f;
                            slowdown2 -= 0.2f;
                        }
                        if(slowdown < 0.72)
                        {
                            slowdown = 0.72f;
                        }

                        //move right at the same time
                        if(keyHold(InputHelper::Instance()->getButtonToAction(3)))
                        {
                            diagonleMoving = true;
                            fppCam->StrafePhysic(cameraMoveSpeed*slowdown);

                            if(canFly)
                                fppCam->MovePhysic(cameraMoveSpeed*slowdown);
                            else
                                fppCam->MovePhysicNoY(cameraMoveSpeed*slowdown);
                        }

                        //move left at the same time
                        if(keyHold(InputHelper::Instance()->getButtonToAction(2)))
                        {
                            diagonleMoving = true;
                            fppCam->StrafePhysic(-cameraMoveSpeed*slowdown);

                            if(canFly)
                                fppCam->MovePhysic(cameraMoveSpeed*slowdown);
                            else
                                fppCam->MovePhysicNoY(cameraMoveSpeed*slowdown);
                        }

                        if(!diagonleMoving)
                        {
                            if(canFly)
                                fppCam->MovePhysic(cameraMoveSpeed*slowdown2);
                            else
                                fppCam->MovePhysicNoY(cameraMoveSpeed*slowdown2);
                        }

                        if(mWorld->HG > 0)
                        {
                            if(mWorld->gameModeWorld != 1) mWorld->HG -= dt/75.0f;
                        }
                    }

                    //move back
                    if(keyHold(InputHelper::Instance()->getButtonToAction(1)))
                    {
                        float slowdown = 0.8f;
                        float slowdown2 = 1.0f;
                        if (startDt == true)
                        {
                            startDt = false;
                            dStd = -1;
                        }
                        moving = true;
                        moveForward = false;

                        if(walkingOnGround == false)
                        {
                            slowdown -= 0.2f;
                            slowdown2 -= 0.2f;
                        }
                        if(slowdown < 0.72)
                        {
                            slowdown = 0.72f;
                        }
                        //move right at the same time
                        if(keyHold(InputHelper::Instance()->getButtonToAction(3)))
                        {
                            diagonleMoving = true;
                            fppCam->StrafePhysic(cameraMoveSpeed*slowdown);

                            if(canFly)
                                fppCam->MovePhysic(-cameraMoveSpeed*slowdown);
                            else
                                fppCam->MovePhysicNoY(-cameraMoveSpeed*slowdown);
                        }

                        //move left at the same time
                        if(keyHold(InputHelper::Instance()->getButtonToAction(2)))
                        {
                            diagonleMoving = true;
                            fppCam->StrafePhysic(-cameraMoveSpeed*slowdown);

                            if(canFly)
                                fppCam->MovePhysic(-cameraMoveSpeed*slowdown);
                            else
                                fppCam->MovePhysicNoY(-cameraMoveSpeed*slowdown);
                        }

                        if(!diagonleMoving)
                        {
                            if(canFly)
                                fppCam->MovePhysic(-cameraMoveSpeed*slowdown2);
                            else
                                fppCam->MovePhysicNoY(-cameraMoveSpeed*slowdown2);
                        }

                        if(mWorld->HG > 0)
                        {
                            if(mWorld->gameModeWorld != 1) mWorld->HG -= dt/75.0f;
                        }
                    }

                    //move right
                    if(keyHold(InputHelper::Instance()->getButtonToAction(3)))
                    {
                        float slowdown = 1.0f;

                        if(walkingOnGround == false)
                        {
                            slowdown -= 0.2f;
                        }

                        if (startDt == true)
                        {
                            startDt = false;
                            dStd = -1;
                        }
                        if(!diagonleMoving)
                        {
                            fppCam->StrafePhysic(cameraMoveSpeed*slowdown);
                            moving = true;
                        }

                        if(mWorld->HG > 0)
                        {
                            if(mWorld->gameModeWorld != 1) mWorld->HG -= dt/75.0f;
                        }
                    }
					
					//Crouch
					if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
					{
						if(canFly == false) crouch == false ? crouch = true : crouch = false;
					}		
					
					if(slowWalk)
					{
						sprint = false;
					}
					
					if(crouch)
					{
						sprint = false;
						mWorld->playerGrowth = 1.55f;
						
						if(mWorld->invSlot2Id != 0 && recoidShield <= 0)
						{
							shield = true;
						}
					}
					else
					{
						if(shield)
						{
							shield = false;
						}
						
						mWorld->playerGrowth = 1.65f;
					}

					if((shield && recoidShield > 0) || (shield && mWorld->invSlot2Id  == -1))
					{
						shield = false;
					}
					
					//Sprint
					if(keyHold(InputHelper::Instance()->getButtonToAction(0)) && mWorld->HG >= 6 && footInWater == false && footInLava == false)
					{
						if(tickSprintTime > 0.75f && tickSprintTime < 0.9f && crouch == false && slowWalk == false)
						{
							sprint = true;
							tickSprintTime = 1.0f;
						}
						else
						{
							tickSprintTime = 1.0f;
						}							
					}
					else{
						sprint = false;
					}							
					tickSprintTime -= dt;						

					//Sprint
					if(sprint)
					{							
						float slowdown = 0.3f;
						float slowdown2 = 0.5f;

						if(walkingOnGround == false)
						{
							slowdown -= 0.2f;
							slowdown2 -= 0.2f;
						}

						if(slowdown < 0.72)
						{
							slowdown = 0.32f;
						}
						
						moving = true;
						
						//move right at the same time
						if(keyHold(InputHelper::Instance()->getButtonToAction(3)))
						{
							diagonleMoving = true;
							fppCam->StrafePhysic(cameraMoveSpeed*slowdown);

							if(canFly)
								fppCam->MovePhysic(cameraMoveSpeed*slowdown);
							else
								fppCam->MovePhysicNoY(cameraMoveSpeed*slowdown);
						}
						
						//move left at the same time
						if(keyHold(InputHelper::Instance()->getButtonToAction(2)))
						{
							diagonleMoving = true;
							fppCam->StrafePhysic(-cameraMoveSpeed*slowdown);
	
							if(canFly)
							fppCam->MovePhysic(cameraMoveSpeed*slowdown);
							else
							fppCam->MovePhysicNoY(cameraMoveSpeed*slowdown);
						}
						
						if(!diagonleMoving)
						{
							if(canFly)
								fppCam->MovePhysic(cameraMoveSpeed*slowdown2);
							else
								fppCam->MovePhysic(cameraMoveSpeed*slowdown2);
						}

						if(mWorld->HG > 0)
						{
							if(mWorld->gameModeWorld != 1) mWorld->HG -= dt/9.0f;
						}
					}

                    //move left
                    if(keyHold(InputHelper::Instance()->getButtonToAction(2)))
                    {
                        float slowdown = 1.0f;

                        if(walkingOnGround == false)
                        {
                            slowdown -= 0.2f;
                        }

                        if (startDt == true)
                        {
                            startDt = false;
                            dStd = -1;
                        }
                        if(!diagonleMoving)
                        {
                            fppCam->StrafePhysic(-cameraMoveSpeed*slowdown);
                            moving = true;
                        }

                        if(mWorld->HG > 0)
                        {
                            if(mWorld->gameModeWorld != 1) mWorld->HG -= dt/75.0f;
                        }
                    }

                    // jumping/swiming
                    if(keyHold(InputHelper::Instance()->getButtonToAction(12)) && playerInCobweb == false)
                    {
                        dStd = -1;
                        if (headInWater || headInLava || mWorld->BlockAtPoint(Vector3(playerPosition.x,playerPosition.y-0.65f,playerPosition.z)) == WaterBlock::getID() || mWorld->BlockAtPoint(Vector3(playerPosition.x,playerPosition.y-0.65f,playerPosition.z)) == Lava::getID())
                        {
                            if(walkingOnGround == true)
                            {
                                jumping = true;
                            }
                            else
                            {
                                playerVelocity.y = 0.525 * JUMPVELOCITY;
                            }
                        }
                        if (headInWater == false && headInLava == false && walkingOnGround == false && (footInWater == true || footInLava == true))	//Your above he water, so Jump out
                        {
                            /*playerVelocity.y = 1.2 * JUMPVELOCITY;
                            walkingOnGround = false;*/

							playerVelocity.y = 1.2f * JUMPVELOCITY; // Reduce la velocidad vertical para simular densidad del líquido
							walkingOnGround = false;
							
                            if(mWorld->HG > 0.0001)
                            {
                                if(mWorld->gameModeWorld != 1) mWorld->HG -= 0.00001;
                            }
                        }
                        if(walkingOnGround == true)
                        {
                            if(headInWater == false && headInLava == false)
                            {
                                jumping = true;
                            }
                        }
                        else
                        {
                            jumping = false;
                        }
                    }
                }

				// bow
				if(keyHold(InputHelper::Instance()->getButtonToAction(14)))
				{
					if(mWorld->invId[27+barPosition] == Bow0::getID() ||
					mWorld->invId[27+barPosition] == Bow1::getID() ||
					mWorld->invId[27+barPosition] == Bow2::getID() ||
					mWorld->invId[27+barPosition] == Bow3::getID())
					{
						if(shield) shield = false;
						if(!buttonBowPressed){
							tickBow = 0.1f;
							buttonBowPressed = true;
						}
						
						for(int i = 27; i < 36; i++)
						{
							if(mWorld->invId[i] == Arrow::getID())
							{
								if(tickBow >= 0.3f && tickBow <= 0.6f) mWorld->invId[27+barPosition] = Bow1::getID();
								if(tickBow >= 0.7f && tickBow <= 0.8f) mWorld->invId[27+barPosition] = Bow2::getID();
								if(tickBow >= 0.9f) mWorld->invId[27+barPosition] = Bow3::getID();
								
								if(slowWalk == false) slowWalk = true;
								AtackBow = true;
							}
						}
					}
					else
					{
						if(AtackBow)
						{
							tickBow = 0.0f;
							AtackBow = false;
							changeX = 0.0f;
							changeY = 0.0f;	
							slowWalk = false;
							
							for(int i = 27; i < 36; i++)
							{
								if(mWorld->invId[i] == Bow1::getID() ||
								mWorld->invId[i] == Bow2::getID() ||
								mWorld->invId[i] == Bow3::getID())
								{
									mWorld->invId[i] = Bow0::getID();
								}
							}
						}
					}
				}
				else
				{
					buttonBowPressed = false;
					if(AtackBow == true)
					{
						if(mWorld->invId[27+barPosition] == Bow1::getID() ||
						mWorld->invId[27+barPosition] == Bow2::getID() ||
						mWorld->invId[27+barPosition] == Bow3::getID())
						{
							for(int i = 27; i < 36; i++)
							{
								if(mWorld->invId[i] == Arrow::getID())
								{
									if(tickBow >= 0.3f && tickBow <= 0.6f)
										changeYBow = 2.0f;
									else if(tickBow >= 0.7f && tickBow <= 0.8f)
										changeYBow = 1.0f;
									else if(tickBow >= 0.9f)
										changeYBow = 0.3f;
										
									AtackBow = false;
									
									mSoundMgr->PlayBowSound();

									Arrow2* NewARR = new Arrow2(playerPosition.x,playerPosition.y,playerPosition.z);
									NewARR->SetVeloc(fppCam->upDownAngle,(fppCam->horAngle/(float)180 - 20)*PI,changeYBow);	
									mArrows.push_back(NewARR);
									
									tickBow = 0.0f;
									changeX = 0.0f;
									changeY = 0.0f;
									
									slowWalk = false;
									
									mWorld->invAm[i] -= 1;
									mWorld->invId[27+barPosition] = Bow0::getID();
									mWorld->invAm[27+barPosition] -= 1;
									if (mWorld->invAm[27+barPosition] == 0) // [27+barPosition] - selected item/block
									{
										mWorld->invAm[27+barPosition] = -1;
										mWorld->invId[27+barPosition] = -1;
										mWorld->invSt[27+barPosition] = 0;
									}
									if (mWorld->invAm[i] == 0) // [27+barPosition] - selected item/block
									{
										mWorld->invAm[i] = -1;
										mWorld->invId[i] = -1;
										mWorld->invSt[i] = 0;
									}
									return;
								}
							}
						}
						else
						{
							tickBow = 0.0f;
							AtackBow = false;
							changeX = 0.0f;
							changeY = 0.0f;	
							
							slowWalk = false;
							
							for(int i = 27; i < 36; i++)
							{
								if(mWorld->invId[i] == Bow1::getID() || mWorld->invId[i] == Bow2::getID() || mWorld->invId[i] == Bow3::getID())
								{
									mWorld->invId[i] = Bow0::getID();
								}
							}
						}
					}
					tickBow = 0.0f;
				}
				
				// inventory
				if(keyPressed(InputHelper::Instance()->getButtonToAction(14)))
				{
					if(sleepTime == 0.0f)
					{
						if(keyPressed(InputHelper::Instance()->getButtonToAction(13))) //open inventory
						{
							if(craft3xEn == false && chestEn == false && furnaceEn == false && villEn == false)
							{
								//inventory sprite
								if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
								{
									TextureHelper::Instance()->LoadInventory(0);
									
									invSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::inv), true);//200
									invSprite->SetPosition(240,136);
								}
								else
								{
									TextureHelper::Instance()->LoadInventory(1);
									
									invSpriteCreative = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::invCreative), true);
									invSpriteCreative->SetPosition(240,136);
								}
								
								invEn = true;
								dT = 0;
								dET = 0;
								chestId = -1;
								dStd = -1;
								if(AtackBow == true)
								{
									AtackBow = false;
									tickBow = 0.0f;
									changeX = 0.0f;
									changeY = 0.0f;
									
									slowWalk = false;
									
									for(int i = 27; i < 36; i++)
									{
										if(mWorld->invId[i] == Bow1::getID() || mWorld->invId[i] == Bow2::getID() || mWorld->invId[i] == Bow3::getID())
										{
											mWorld->invId[i] = Bow0::getID();
										}
									}
								}
								
								if(shield)
								{
									shield = false;
								}
								
								if(mWorld->gameModeWorld == 1) selectInvSprite->SetPosition(169 + (invXPosition * 18),96+(invYPosition * 18));
								
								return;
							}
						}
					}
				}

				// add cube
				if(keyPressed(InputHelper::Instance()->getButtonToAction(14)) && AtackBow == false && mWorld->invId[27+barPosition] != Bow0::getID())
				{
					if (startDt == true)
					{
						startDt = false; //stop destroying
					}

					if (mWorld->invId[27+barPosition] == 299) ///SNOWBALL THROWING
					{
						changeY = -0.20f;
						anim[0] = 1;

						mSoundMgr->PlayBowSound();

						SnowBall2* NewSB = new SnowBall2(playerPosition.x,playerPosition.y,playerPosition.z);
						NewSB->SetVeloc(fppCam->upDownAngle,(fppCam->horAngle/(float)180)*PI);
						mSnowBalls.push_back(NewSB);

						mWorld->invAm[27+barPosition] -= 1;
						if (mWorld->invAm[27+barPosition] == 0) // [27+barPosition] - selected item/block
						{
							mWorld->invAm[27+barPosition] = -1;
							mWorld->invId[27+barPosition] = -1;
							mWorld->invSt[27+barPosition] = 0;
						}
						return;
					}

					//add cube
					Vector3 rayDir = fppCam->m_vView - fppCam->m_vPosition;
					rayDir.normalize();

					//get position and view vector
					Vector3 testPos;

					BoundingBox collider = mWorld->blockTypes[mWorld->GetBlock(testPos.x,testPos.y,testPos.z)].collideBox;
					BoundingBox testBox = BoundingBox(testPos.x+collider.min.x, testPos.y+collider.min.y, testPos.z+collider.min.z, testPos.x+collider.max.x, testPos.y+collider.max.y, testPos.z+collider.max.z);

					if(mWorld->invId[27+barPosition] == Scissors::getID() || (mWorld->ItemType(mWorld->invId[27+barPosition]) == 'Y' && mWorld->invId[27+barPosition] != BoneMeal::getID())) // shear sheep or dye it
					{
						if(mWorld->mSheeps.empty() == false)
						{
							for(float i = 0; i < 5.25f; i+=0.1f)
							{
								testPos = fppCam->m_vPosition + (rayDir * i);
								for(int f = 0; f < mWorld->mSheeps.size(); f++)
								{
									Sheep *TestSheep = mWorld->mSheeps[f];
									if(TestSheep->DistanceToPlayer() < 2.85 && TestSheep->kicked == false && TestSheep->damaged == false)
									{
										if(TestSheep->bBox.contains(testPos))
										{
											if(mWorld->ItemType(mWorld->invId[27+barPosition]) == 'Y') // dye item
											{
												int newColor = 14;
												switch(mWorld->invId[27+barPosition])
												{
													case 314: // brown
													newColor = 6;
													break;

													case 318: // blue
													newColor = 8;
													break;

													case 322: // white
													newColor = 14;
													break;

													case 365: // lt gray
													newColor = 13;
													break;

													case 366: // gray
													newColor = 1;
													break;

													case 367: // black
													newColor = 0;
													break;

													case 368: // pink
													newColor = 3;
													break;

													case 369: // red
													newColor = 2;
													break;

													case 370: // orange
													newColor = 12;
													break;

													case 371: // yellow
													newColor = 7;
													break;

													case 372: // lime
													newColor = 5;
													break;

													case 373: // lime
													newColor = 4;
													break;

													case 374: // lt blue
													newColor = 9;
													break;

													case 375: // purple
													newColor = 10;
													break;

													case 376: // magneta
													newColor = 11;
													break;
												}

												if(TestSheep->GetFurColor() != newColor)
												{
													TestSheep->SetFurColor(newColor);

													mWorld->invAm[27+barPosition] -= 1;
													if (mWorld->invAm[27+barPosition] == 0)
													{
														mWorld->invAm[27+barPosition] = -1;
														mWorld->invId[27+barPosition] = -1;
														mWorld->invSt[27+barPosition] = 0;
													}

													animGo = true;
													animDest = 0.0f;
													currentState = 0;
												}
												return;
											}

											if(mWorld->invId[27+barPosition] == Scissors::getID())
											{
												if(TestSheep->sheared == false)
												{
													int woolNum = 1+rand()%3;
													for(int i = 0; i < woolNum; i++)
													{
														mWorld->DropThis(BlackWoolBlock::getID()+TestSheep->GetFurColor(),1,true,Vector3(TestSheep->position.x,TestSheep->position.y+0.3f,TestSheep->position.z));
													}

													TestSheep->sheared = true;
													mSoundMgr->PlayShearSound();

													mWorld->invAm[27+barPosition] -= 1;
													if (mWorld->invAm[27+barPosition] == 0)
													{
														mWorld->invAm[27+barPosition] = -1;
														mWorld->invId[27+barPosition] = -1;
														mWorld->invSt[27+barPosition] = 0;
													}

													animGo = true;
													animDest = 0.0f;
													currentState = 0;
													return;
												}
											}
										}
									}
								}
							}
						}
						return;
					}

					//Village INV
					if(villEn == false)
					{
						if(mWorld->mVillagers.empty() == false)
						{	
							for(float i = 0; i < 5.25f; i+=0.1f)
							{
								testPos = fppCam->m_vPosition + (rayDir * i);
								for(int f = 0; f < mWorld->mVillagers.size(); f++)
								{
									Villager *TestVillager = mWorld->mVillagers[f];
									if(TestVillager->DistanceToPlayer() < 2.85 && TestVillager->kicked == false && TestVillager->damaged == false && TestVillager->Profession != 12)
									{
										if(TestVillager->bBox.contains(testPos))
										{
											villEn = true;
											villageId = f;
											villageProfession = TestVillager->Profession;
											villageLvl = TestVillager->LevelProfession;
											villageRandom = TestVillager->randomVillager;

											TestVillager->tradder = true;
											
											tradesManager.Init(TestVillager->Profession, TestVillager->LevelProfession, TestVillager->randomVillager);
											
											SlotEnVillager = 0;
											
											TextureHelper::Instance()->LoadInventory(5);
							
											invVillage = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::invTrad), true);//200
											invVillage->SetPosition(240,136);

											selectInvSprite->SetPosition(218+(invXPosition * 18),152+(invYPosition * 18));
											
											return;
										}
									}
								}
							}
						}
					}

					for(float i = 0; i < 5.25f; i+=0.1f)
					{
						testPos = fppCam->m_vPosition + (rayDir * i);

						collider = mWorld->blockTypes[mWorld->GetBlock(testPos.x,testPos.y,testPos.z)].collideBox;
						testBox = BoundingBox(floorf(testPos.x)+0.5f+collider.min.x, floorf(testPos.y)+0.5f+collider.min.y, floorf(testPos.z)+0.5f+collider.min.z, floorf(testPos.x)+0.5f+collider.max.x, floorf(testPos.y)+0.5f+collider.max.y, floorf(testPos.z)+0.5f+collider.max.z);

						int selectedBlock = mWorld->GetBlock(testPos.x, testPos.y, testPos.z);
						

						if(mWorld->invId[27+barPosition] == WaterBusket::getID())
						{
							if(selectedBlock == Lava::getID())
							{
								int x = (int)testPos.x;
								int y = (int)testPos.y;
								int z = (int)testPos.z;
								BoundingBox blockBox = BoundingBox(Vector3(x,y,z),Vector3(x + 1,y + 1,z + 1));
								BoundingBox playerBox;
								if(walkingOnGround == false)
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.63f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								else
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.59f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								if(!blockBox.intersect(playerBox))
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = Obsidian::getID();

									mSoundMgr->PlayFissSound();

									int	curchunkTarget = mWorld->getChunkId(testPos);
									mWorld->RebuildFullMeshChunk(curchunkTarget);
									fppCam->needUpdate = true;

									mWorld->invId[27+barPosition] = Busket::getID();

									changeY = -0.16f;
									anim[0] = 1;
									return;
								}
							}
						}

						if(mWorld->invId[27+barPosition] == LavaBusket::getID())
						{
							if(selectedBlock == WaterBlock::getID())
							{
								int x = (int)testPos.x;
								int y = (int)testPos.y;
								int z = (int)testPos.z;
								BoundingBox blockBox = BoundingBox(Vector3(x,y,z),Vector3(x + 1,y + 1,z + 1));
								BoundingBox playerBox;
								if(walkingOnGround == false)
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.63f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								else
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.59f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								if(!blockBox.intersect(playerBox))
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = CobbleStone::getID();

									mSoundMgr->PlayFissSound();

									int	curchunkTarget = mWorld->getChunkId(testPos);
									mWorld->RebuildFullMeshChunk(curchunkTarget);
									fppCam->needUpdate = true;

									mWorld->invId[27+barPosition] = Busket::getID();

									changeY = -0.16f;
									anim[0] = 1;
									return;
								}
							}
						}

						if(mWorld->invId[27+barPosition] == 290) //busket
						{
							if (selectedBlock == 4) //if it is WATER
							{
								// well simulation
								if((mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z-1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z-1) == 4) ||
								   (mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z-1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z-1) == 4) ||
								   (mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z+1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z+1) == 4) ||
								   (mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z+1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z+1) == 4))
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 4;
								}
								else
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 0;

									int	curchunkTarget = mWorld->getChunkId(testPos);
									mWorld->RebuildTransparentMeshChunk(curchunkTarget);
									fppCam->needUpdate = true;
								}

								mWorld->invId[27+barPosition] = 291;

								changeY = -0.16f;
								anim[0] = 1;
								return;
							}

							if (selectedBlock == 112) //if it is lava
							{
								// well simulation
								if((mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z) == Lava::getID() && mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z-1) == Lava::getID() && mWorld->GetBlock(testPos.x, testPos.y, testPos.z-1) == Lava::getID()) ||
								   (mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z) == Lava::getID() && mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z-1) == Lava::getID() && mWorld->GetBlock(testPos.x, testPos.y, testPos.z-1) == Lava::getID()) ||
								   (mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z) == Lava::getID() && mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z+1) == Lava::getID() && mWorld->GetBlock(testPos.x, testPos.y, testPos.z+1) == Lava::getID()) ||
								   (mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z) == Lava::getID() && mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z+1) == Lava::getID() && mWorld->GetBlock(testPos.x, testPos.y, testPos.z+1) == Lava::getID()))
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = Lava::getID();
								}
								else
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 0;

									mWorld->RemoveLigtSourceAtPosition(testPos.x,testPos.y,testPos.z,112);
									mWorld->UpdateLightAreaIn(testPos);

									int	curchunkTarget = mWorld->getChunkId(testPos);
									mWorld->RebuildFullMeshChunk(curchunkTarget);
									fppCam->needUpdate = true;
								}
								mWorld->invId[27+barPosition] = 292;

								changeY = -0.16f;
								anim[0] = 1;
								return;
							}
						}

						//check if we are touch something
						if(mWorld->BlockEditable(testPos.x,testPos.y,testPos.z) && testBox.contains(testPos))
						{
							// we use hoes
							if(mWorld->invId[27+barPosition] >= 270 && mWorld->invId[27+barPosition] <= 274)
							{
								if (selectedBlock == 1) //if it is grass
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 2;
									if(rand() % 11 == 0)
									{
										mWorld->DropThis(286,1,true,testPos); //put seed in inventory
									}

									mWorld->invAm[27+barPosition] -= 1; // bit crashing to our hoe
									if(mWorld->invAm[27+barPosition] == 0) //destroy tool if it has 0 durability points
									{
										mWorld->invAm[27+barPosition] = -1;
										mWorld->invId[27+barPosition] = -1;
										mWorld->invSt[27+barPosition] = 0;

										mSoundMgr->PlayBreakSound();
									}
									int	curchunkTarget = mWorld->getChunkId(testPos);

									//Rebuild nearby world
									mWorld->RebuildOpaqueMeshChunk(curchunkTarget);
									fppCam->needUpdate = true;

									mSoundMgr->PlayWalkSound(1);
									changeY = -0.16f;
									anim[0] = 1;
									return;
								}

								if (selectedBlock == 2) //if it is dirt
								{
									mWorld->mainStatistics.soilPlowed += 1;
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 79;

									mWorld->invAm[27+barPosition] -= 1;
									if(mWorld->invAm[27+barPosition] == 0) //destroy tool if it has 0 durability points
									{
										mWorld->invAm[27+barPosition] = -1;
										mWorld->invId[27+barPosition] = -1;
										mWorld->invSt[27+barPosition] = 0;

										mSoundMgr->PlayBreakSound();
									}

									int	curchunkTarget = mWorld->getChunkId(testPos);

									//Rebuild nearby world
									mWorld->RebuildOpaqueMeshChunk(curchunkTarget);
									fppCam->needUpdate = true;

									mSoundMgr->PlayWalkSound(1); // play dirt sound
									changeY = -0.16f;
									anim[0] = 1;
									return;
								}
							}

							if (selectedBlock == NoteBlock::getID())
							{
								int noteBlockId = mWorld->FindNoteBlockID(testPos);

								if(noteBlockId != -1)
								{
									if(mWorld->GetBlock(testPos.x,testPos.y+1,testPos.z) == 0)
									{
										NoteBlockEntity* TestNoteBlock = mWorld->mNoteBlocks[noteBlockId];

										TestNoteBlock->IncreaseNote();
										mSoundMgr->PlayNoteSound(!(mWorld->BlockMaterial(testPos.x,testPos.y-1,testPos.z) == 1 || mWorld->BlockMaterial(testPos.x,testPos.y-1,testPos.z) == 8),TestNoteBlock->GetPitch());

										float red, blue, green;
										if(TestNoteBlock->GetNote() <= 12)
										{
											blue = 1.0 - (TestNoteBlock->GetNote()/12.0f);
											green = (TestNoteBlock->GetNote()/12.0f);
											red = 0.0f;
										}
										else
										{
											blue = 0.0f;
											green = 1.0 - ((TestNoteBlock->GetNote()-12)/12.0f);
											red = ((TestNoteBlock->GetNote()-12)/12.0f);
										}
										Particle* Note = new Particle(mWorld,"note",Vector3((int)testPos.x+0.5f,(int)testPos.y+1.1f,(int)testPos.z+0.5f));
										Note->SetColor(Vector3(red,green,blue));
										mParticles.push_back(Note);
									}

									animGo = true;
									animDest = 0.0f;
									currentState = 0;

									changeY = -0.1f;
									anim[0] = 1;

									return;
								}
							}

							if(selectedBlock >= ItemFrame1::getID() && selectedBlock <= ItemFrame4::getID())
							{
								int itemFrameId = mWorld->FindItemFrameID(testPos);

								if(itemFrameId != -1)  // set item in item frame
								{
									ItemFrameEntity* TestItemFrame = mWorld->mItemFrames[itemFrameId];

									if(mWorld->invId[27+barPosition] != -1)
									{
										if(TestItemFrame->GetItem() == -1)
										{
											TestItemFrame->SetItem(mWorld->invId[27+barPosition]);

											if(mWorld->invSt[27+barPosition] == true)
											{
												mWorld->invAm[27+barPosition] -= 1;
												if(mWorld->invAm[27+barPosition] == 0)
												{
													mWorld->invAm[27+barPosition] = -1;
													mWorld->invSt[27+barPosition] = 0;
													mWorld->invId[27+barPosition] = -1;
												}
											}
											else
											{
												TestItemFrame->SetAmount(mWorld->invAm[27+barPosition]);

												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = 0;
												mWorld->invId[27+barPosition] = -1;
											}

											animGo = true;
											animDest = 0.0f;
											currentState = 0;

											changeY = -0.1f;
											anim[0] = 1;

											return;
										}
									}

									if(TestItemFrame->GetItem() != -1)  // remove item in item frame
									{
										if(TestItemFrame->GetItem() < 250)
										{
											mWorld->DropThis(TestItemFrame->GetItem(), 1, true, Vector3((int)testPos.x+0.5f,(int)testPos.y+0.5f,(int)testPos.z+0.5f));
										}
										else
										{
											if(TestItemFrame->GetAmount() != -1)
											{
												mWorld->DropThis(TestItemFrame->GetItem(), TestItemFrame->GetAmount(), mWorld->StackableItem(TestItemFrame->GetItem()), Vector3((int)testPos.x+0.5f,(int)testPos.y+0.5f,(int)testPos.z+0.5f));
											}
											else
											{
												if(TestItemFrame->GetItem() >= 250)
												{
													mWorld->DropThis(TestItemFrame->GetItem(), 1, mWorld->StackableItem(TestItemFrame->GetItem()), Vector3((int)testPos.x+0.5f,(int)testPos.y+0.5f,(int)testPos.z+0.5f));
												}
												else
												{
													mWorld->DropThis(TestItemFrame->GetItem(), 1, true, Vector3((int)testPos.x+0.5f,(int)testPos.y+0.5f,(int)testPos.z+0.5f));
												}
											}
										}

										TestItemFrame->ResetItem();
										TestItemFrame->SetAmount(-1);

										return;
									}
								}
							}

							if (selectedBlock == JukeBox::getID())
							{
								int jukeboxId = mWorld->FindJukeboxID(testPos);

								if(jukeboxId != -1)
								{
									if(mWorld->GetBlock(testPos.x,testPos.y+1,testPos.z) == 0)
									{
										JukeboxEntity* TestJukebox = mWorld->mJukeboxes[jukeboxId];

										if(TestJukebox->GetRecord() == -1)
										{
											if((mWorld->invId[27+barPosition] >= Disk1::getID() && mWorld->invId[27+barPosition] <= Disk3::getID()) || (mWorld->invId[27+barPosition] >= Disk4::getID() && mWorld->invId[27+barPosition] <= Disk12::getID()))
											{
												TestJukebox->SetRecord(mWorld->invId[27+barPosition]);

												int music_number = 0;
												if(mWorld->invId[27+barPosition] >= Disk1::getID() && mWorld->invId[27+barPosition] <= Disk3::getID())
												{
													music_number = mWorld->invId[27+barPosition]-Disk1::getID();
												}
												if(mWorld->invId[27+barPosition] >= Disk4::getID() && mWorld->invId[27+barPosition] <= Disk12::getID())
												{
													music_number = mWorld->invId[27+barPosition]-Disk4::getID()+3;
												}

												mSoundMgr->StopAmbient();
												mSoundMgr->StopHell();
												mSoundMgr->StopDiskTrack();
												mSoundMgr->PlayDiskTrack(music_number);

												switch(music_number)
												{
													case 0: inputDiskName = "C418 - 13"; break;
													case 1: inputDiskName = "C418 - cat"; break;
													case 2: inputDiskName = "C418 - blocks"; break;
													case 3: inputDiskName = "C418 - chirp"; break;
													case 4: inputDiskName = "C418 - far"; break;
													case 5: inputDiskName = "C418 - mall"; break;
													case 6: inputDiskName = "C418 - mellohi"; break;
													case 7: inputDiskName = "C418 - stal"; break;
													case 8: inputDiskName = "C418 - strad"; break;
													case 9: inputDiskName = "C418 - ward"; break;
													case 10: inputDiskName = "C418 - 11"; break;
													case 11: inputDiskName = "C418 - wait"; break;
												}

												inputDiskNameTimer = 2.4f;

												mWorld->invId[27+barPosition] = -1;
												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = 0;

												musicTime = 360.0f;
											}
										}
										else
										{
											inputDiskName = "";
											inputDiskNameTimer = 0.0f;

											mWorld->DropThis(TestJukebox->GetRecord(), 1, false, Vector3((int)testPos.x+0.5f,(int)testPos.y+1.0f,(int)testPos.z+0.5f) );
											TestJukebox->SetRecord(-1);

											mSoundMgr->StopAmbient();
											mSoundMgr->StopHell();
											mSoundMgr->StopDiskTrack();

											musicTime = 60.0f+rand()%60;
										}

										animGo = true;
										animDest = 0.0f;
										currentState = 0;

										changeY = -0.1f;
										anim[0] = 1;
									}
									return;
								}
							}

							if (selectedBlock == CraftingTable::getID()) // open crafting table menu
							{
								TextureHelper::Instance()->LoadInventory(2);
								
								crtSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::crt), true);//200
								crtSprite->SetPosition(240,136);
	
								craft3xEn = true;
								
								recipesManager.craft2x2 = false;
								recipesManager.Init();
								
								PagCraft = 0;
								IndexCraft = 0;
								SlotEnCraft = 0;
								
								for(int i = 0; i < 5; i++)
								{
									IDDrawRe[i] = 0;
								}
								
								tickReChange = 0.0f;

								selectInvSprite->SetPosition(233+(invXPosition * 18),189+(invYPosition * 18));
								
								return;
							}

							if(mWorld->invId[27+barPosition] == BoneMeal::getID())
							{
								bool used = false;

								if (selectedBlock == GrassBlock::getID())
								{
									for(int xx = testPos.x-2; xx <= testPos.x+2; xx ++)
									{
										for(int zz = testPos.z-2; zz <= testPos.z+2; zz ++)
										{
											for(int yy = testPos.y; yy > 0; yy--)
											{
												if(mWorld->GetBlock(xx,yy,zz) != 0)
												{
													if(mWorld->GetBlock(xx,yy,zz) == GrassBlock::getID())
													{
														if(mWorld->GetBlock(xx,yy+1,zz) == 0)
														{
															if(rand()%10<=5)
															{
																rand() % 2 == 0 ? mWorld->GetBlock(xx,yy+1,zz) = Flower1::getID() : mWorld->GetBlock(xx,yy+1,zz) = Flower2::getID();
																if(rand()%2 == 0)
																{
																	mWorld->GetBlock(xx,yy+1,zz) = TallGrass::getID();
																}
															}
															break;
														}
														else
														{
															break;
														}
													}
													else
													{
														break;
													}
												}
											}
										}
									}
									used = true;
								}
								if (selectedBlock >= WheatBlock1::getID() && selectedBlock <= WheatBlock5::getID())
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = WheatBlock6::getID();
									used = true;
								}
								if (selectedBlock >= MelonPlant1::getID() && selectedBlock <= MelonPlant3::getID())
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = MelonPlant4::getID();
									used = true;
								}
								if (selectedBlock >= PumpkinPlant1::getID() && selectedBlock <= PumpkinPlant3::getID())
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = PumpkinPlant4::getID();
									used = true;
								}
								if (selectedBlock >= PotatoPlant1::getID() && selectedBlock <= PotatoPlant3::getID())
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = PotatoPlant4::getID();
									used = true;
								}
								if (selectedBlock >= CarrotPlant1::getID() && selectedBlock <= CarrotPlant3::getID())
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = CarrotPlant4::getID();
									used = true;
								}

								if(used)
								{
									animGo = true;
									animDest = 0.0f;
									currentState = 0;

									changeY = -0.1f;
									anim[0] = 1;

									mWorld->invAm[27+barPosition] -= 1;
									if(mWorld->invAm[27+barPosition] == 0)
									{
										mWorld->invAm[27+barPosition] = -1;
										mWorld->invSt[27+barPosition] = 0;
										mWorld->invId[27+barPosition] = -1;
									}
									int	curchunkTarget = mWorld->getChunkId(testPos);
									mWorld->RebuildTransparentMeshChunk(curchunkTarget);

									fppCam->needUpdate = true;
									return;
								}
							}

							// half block + half block = full block
							if (mWorld->blockTypes[mWorld->GetBlock(testPos.x, testPos.y, testPos.z)].blockModel == 1 &&
								mWorld->blockTypes[mWorld->invId[27+barPosition]].blockModel == 1  &&
								mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == mWorld->invId[27+barPosition]
							   )
							{
								int x = (int)testPos.x;
								int y = (int)testPos.y;
								int z = (int)testPos.z;

								if(testPos.y - y > 0.4f)
								{
									BoundingBox blockBox = BoundingBox(Vector3(x,y,z),Vector3(x + 1,y + 1,z + 1));
									BoundingBox playerBox;
									if(walkingOnGround == false)
									{
										playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.63f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
									}
									else
									{
										playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.59f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
									}

									if(!blockBox.intersect(playerBox))
									{
										switch(mWorld->invId[27+barPosition])
										{
											case 82 : mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = OakPlanks::getID(); break;
											case 83 : mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = CobbleStone::getID(); break;
											case 84 : mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = BrickBlock::getID(); break;
											case 85 : mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = DoubleSlab::getID(); break;
											case 86 : mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = SandStone::getID(); break;
											case 108 : mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = StoneBrick::getID(); break;
											case 157 : mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = BirchPlanks::getID(); break;
											case 158 : mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = SprucePlanks::getID(); break;
										}

										mSoundMgr->PlayWalkSound(mWorld->blockTypes[mWorld->invId[27+barPosition]].soundType);

										mWorld->invAm[27+barPosition] -= 1;
										if(mWorld->invAm[27+barPosition] == 0)
										{
											mWorld->invAm[27+barPosition] = -1;
											mWorld->invId[27+barPosition] = -1;
											mWorld->invSt[27+barPosition] = 0;
										}

										animGo = true;
										animDest = 0.0f;
										currentState = 0;

										int	curchunkTarget = mWorld->getChunkId(testPos);
										fppCam->needUpdate = true;
										mWorld->RebuildOpaqueMeshChunk(curchunkTarget);
										mWorld->rebuildNearestChunks(curchunkTarget,testPos);
										return;
									}
								}
							}


							if (selectedBlock >= TrapdoorClosed1::getID() && selectedBlock <= TrapdoorClosed4::getID()) //door
							{
								//check if player dont stand inside the door block
								int x = (int)testPos.x;
								int y = (int)testPos.y;
								int z = (int)testPos.z;
								BoundingBox doorBox = BoundingBox(Vector3(x,y,z),Vector3(x + 1,y + 1,z + 1));
								BoundingBox playerBox;
								if(walkingOnGround == false)
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.63f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								else
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.59f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								if(!doorBox.intersect(playerBox))
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = mWorld->GetBlock(testPos.x, testPos.y, testPos.z) - 4;
									mSoundMgr->PlayDoorSound(true);

									int	curchunkTarget = mWorld->getChunkId(testPos);
									fppCam->needUpdate = true;
									mWorld->RebuildTransparentMeshChunk(curchunkTarget);
									return;
								}
							}

							if (selectedBlock >= TrapdoorOpen1::getID() && selectedBlock <= TrapdoorOpen4::getID()) //door
							{
								//check if player dont stand inside the door block
								int x = (int)testPos.x;
								int y = (int)testPos.y;
								int z = (int)testPos.z;
								BoundingBox doorBox = BoundingBox(Vector3(x,y,z),Vector3(x + 1,y + 1,z + 1));
								BoundingBox playerBox;
								if(walkingOnGround == false)
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.63f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								else
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.59f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}

								if(!doorBox.intersect(playerBox))
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = mWorld->GetBlock(testPos.x, testPos.y, testPos.z) + 4;
									mSoundMgr->PlayDoorSound(false);

									int	curchunkTarget = mWorld->getChunkId(testPos);
									fppCam->needUpdate = true;
									mWorld->RebuildTransparentMeshChunk(curchunkTarget);
									return;
								}
							}

							if (selectedBlock >= 49 && selectedBlock <= 52) //door
							{
								//check if player dont stand inside the door block
								int x = (int)testPos.x;
								int y = (int)testPos.y;
								int z = (int)testPos.z;
								BoundingBox doorBox = BoundingBox(Vector3(x,y,z),Vector3(x + 1,y + 2,z + 1));
								BoundingBox playerBox;
								if(walkingOnGround == false)
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.63f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								else
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.59f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								if(!doorBox.intersect(playerBox))
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = mWorld->GetBlock(testPos.x, testPos.y, testPos.z) + 4;
									mWorld->GetBlock(testPos.x, testPos.y+1, testPos.z) = 58;
									mSoundMgr->PlayDoorSound(true);

									int	curchunkTarget = mWorld->getChunkId(testPos);
									fppCam->needUpdate = true;
									mWorld->RebuildTransparentMeshChunk(curchunkTarget);
									return;
								}
							}

							if (selectedBlock >= 53 && selectedBlock <= 56) //door
							{
								//check if player dont stand inside the door block
								int x = (int)testPos.x;
								int y = (int)testPos.y;
								int z = (int)testPos.z;
								BoundingBox doorBox = BoundingBox(Vector3(x,y,z),Vector3(x + 1,y + 2,z + 1));
								BoundingBox playerBox;
								if(walkingOnGround == false)
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.63f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								else
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.59f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								if(!doorBox.intersect(playerBox))
								{
									mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = mWorld->GetBlock(testPos.x, testPos.y, testPos.z) - 4;
									mWorld->GetBlock(testPos.x, testPos.y+1, testPos.z) = 57;
									mSoundMgr->PlayDoorSound(false);

									int	curchunkTarget = mWorld->getChunkId(testPos);
									fppCam->needUpdate = true;
									mWorld->RebuildTransparentMeshChunk(curchunkTarget);
									return;
								}
							}

							if (selectedBlock == 57) //door
							{
								//check if player dont stand inside the door block
								int x = (int)testPos.x;
								int y = (int)testPos.y;
								int z = (int)testPos.z;
								BoundingBox doorBox = BoundingBox(Vector3(x, y-2, z),Vector3(x + 1,y,z + 1));
								BoundingBox playerBox;
								if(walkingOnGround == false)
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.63f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								else
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.59f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								if(!doorBox.intersect(playerBox))
								{
									if (mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) >= 49 && mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) <= 52) //door
									{
										mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) = mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) + 4;
										mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 58;
										mSoundMgr->PlayDoorSound(true);

										int	curchunkTarget = mWorld->getChunkId(Vector3(testPos.x,testPos.y-1,testPos.z));
										fppCam->needUpdate = true;
										mWorld->RebuildTransparentMeshChunk(curchunkTarget);
										return;
									}
								}
							}

							if (selectedBlock == 58) //door
							{
								//check if player dont stand inside the door block
								int x = (int)testPos.x;
								int y = (int)testPos.y;
								int z = (int)testPos.z;
								BoundingBox doorBox = BoundingBox(Vector3(x, y-2, z),Vector3(x + 1,y,z + 1));
								BoundingBox playerBox;
								if(walkingOnGround == false)
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.63f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								else
								{
									playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.59f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
								}
								if(!doorBox.intersect(playerBox))
								{
									if (mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) >= 53 && mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) <= 56) //door
									{
										mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) = mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) - 4;
										mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 57;
										mSoundMgr->PlayDoorSound(false);

										int	curchunkTarget = mWorld->getChunkId(Vector3(testPos.x,testPos.y-1,testPos.z));
										fppCam->needUpdate = true;
										mWorld->RebuildTransparentMeshChunk(curchunkTarget);
										return;
									}
								}
							}

							if (selectedBlock == TNTBlock::getID() && mWorld->invId[27+barPosition] == FlintAndSteel::getID())//TNT explosion
							{
								mWorld->SpawnTNTentity(((int)testPos.x)+0.5f,((int)testPos.y)+0.5f,((int)testPos.z)+0.5f);
								mWorld->GetBlock(testPos.x,testPos.y,testPos.z) = 0;
								mSoundMgr->PlayFuseSound();
								mWorld->RebuildOpaqueMeshChunk(mWorld->getChunkId(testPos));
								fppCam->needUpdate = true;

								mWorld->invAm[27+barPosition] -= 1;
								if(mWorld->invAm[27+barPosition] <= 0)
								{
									mWorld->invId[27+barPosition] = -1;
									mWorld->invAm[27+barPosition] = -1;
									mWorld->invSt[27+barPosition] = 0;
								}

								animGo = true;
								animDest = 0.0f;
								currentState = 0;
								return;
							}
							
							//chest open function
							if (selectedBlock == ChestBlock1::getID() || selectedBlock == ChestBlock2::getID() || selectedBlock == ChestBlock3::getID() || selectedBlock == ChestBlock4::getID())
							{
								mSoundMgr->PlayChestSound();
								chestId = FindChestId(testPos.x,testPos.y,testPos.z);
								if(chestId != -1)
								{
									craft3xEn = false;
									chestEn = true;
									
									TextureHelper::Instance()->LoadInventory(3);
								
									chtSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::cht), true);//200
									chtSprite->SetPosition(240,136);
									
									UseChest = mWorld->mChests[chestId];
									return;
								}
								
							}

							if (selectedBlock == FurnaceOff::getID() || selectedBlock == FurnaceOn::getID())
							{
								furnaceId = FindFurnaceId(testPos.x,testPos.y,testPos.z);
								if(furnaceId != -1)
								{
									craft3xEn = false;
									chestEn = false;
									
									TextureHelper::Instance()->LoadInventory(4);
								
									furSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::fur), true);//200
									furSprite->SetPosition(240,136);
									
									furnaceEn = true;
									UseFurnace = mWorld->mFurnaces[furnaceId];
									return;
								}
							}

							if(selectedBlock >= BedBlock1::getID() && selectedBlock <= BedBlock8::getID())	// camas explotan
							{
								if(mWorld->currentDimension == 0)
								{
									if(sleepMessageTime <= 0.0f)
									{
										if(mWorld->worldDayTime >= 6 && mWorld->worldDayTime <= 21)
										{
											sleepMessageTime = 3.0f;
											sleepMessageType = 1;
											return;
										}
										
										if(mWorld->mZombies.empty() == false)
										{
											for(int f = 0; f < mWorld->mZombies.size(); f++)
											{
												Zombie *TestZombie = mWorld->mZombies[f];
												if(abs(playerPosition.x-TestZombie->position.x) <= 7 && abs(playerPosition.z-TestZombie->position.z) <= 7 && abs(playerPosition.y-TestZombie->position.y) <= 4)
												{
													sleepMessageTime = 3.0f;
													sleepMessageType = 2;
													break;
												}
											}
											if(sleepMessageTime == 3.0f)
											{
												return;
											}
										}
										
										if(mWorld->mSkeletons.empty() == false)
										{
											for(int f = 0; f < mWorld->mSkeletons.size(); f++)
											{
												Skeleton *TestSkeleton = mWorld->mSkeletons[f];
												if(abs(playerPosition.x-TestSkeleton->position.x) <= 7 && abs(playerPosition.z-TestSkeleton->position.z) <= 7 && abs(playerPosition.y-TestSkeleton->position.y) <= 4)
												{
													sleepMessageTime = 3.0f;
													sleepMessageType = 2;
													break;
												}
											}
											if(sleepMessageTime == 3.0f)
											{
												return;
											}
										}
										
										if(mWorld->mSpiders.empty() == false)
										{
											for(int f = 0; f < mWorld->mSpiders.size(); f++)
											{
												Spider *TestSpider = mWorld->mSpiders[f];
												if(abs(playerPosition.x-TestSpider->position.x) <= 7 && abs(playerPosition.z-TestSpider->position.z) <= 7 && abs(playerPosition.y-TestSpider->position.y) <= 4)
												{
													sleepMessageTime = 3.0f;
													sleepMessageType = 2;
													break;
												}
											}
											if(sleepMessageTime == 3.0f)
											{
												return;
											}
										}

										mWorld->playerSpawnPointPosition = Vector3((int)mWorld->playerPos.x+0.5f,mWorld->playerPos.y,(int)mWorld->playerPos.z+0.5f);
										sleepTime = 4.6f;

										if(selectedBlock == BedBlock1::getID() || selectedBlock == BedBlock5::getID())
										{
											Vector3 pillowPosition;
											if(selectedBlock == BedBlock5::getID())
											{
												pillowPosition.x = (int)testPos.x+0.75f;
												pillowPosition.y = (int)testPos.y+0.8f;
												pillowPosition.z = (int)testPos.z+0.5f;
											}
											if(selectedBlock == BedBlock1::getID())
											{
												pillowPosition.x = (int)testPos.x+1.75f;
												pillowPosition.y = (int)testPos.y+0.8f;
												pillowPosition.z = (int)testPos.z+0.5f;
											}

											playerPosition = pillowPosition;

											fppCam->PositionCamera(playerPosition.x,playerPosition.y,playerPosition.z, playerPosition.x-5.0f,playerPosition.y,playerPosition.z, 0.0f,1.0f,0.0f);
											fppCam->RotateView(0,0,0,0);
											fppCam->upDownAngle = 0;
											fppCam->horAngle = 180;
											return;
										}
										if(selectedBlock == BedBlock2::getID() || selectedBlock == BedBlock6::getID())
										{
											Vector3 pillowPosition;
											if(selectedBlock == BedBlock6::getID())
											{
												pillowPosition.x = (int)testPos.x+0.25f;
												pillowPosition.y = (int)testPos.y+0.8f;
												pillowPosition.z = (int)testPos.z+0.5f;
											}
											if(selectedBlock == BedBlock2::getID())
											{
												pillowPosition.x = (int)testPos.x-0.75f;
												pillowPosition.y = (int)testPos.y+0.8f;
												pillowPosition.z = (int)testPos.z+0.5f;
											}

											playerPosition = pillowPosition;

											fppCam->PositionCamera(playerPosition.x,playerPosition.y,playerPosition.z, playerPosition.x+5.0f,playerPosition.y,playerPosition.z, 0.0f,1.0f,0.0f);
											fppCam->RotateView(0,0,180,0);
											fppCam->upDownAngle = 0;
											fppCam->horAngle = 0;
											return;
										}
										if(selectedBlock == BedBlock3::getID() || selectedBlock == BedBlock7::getID())
										{
											Vector3 pillowPosition;
											if(selectedBlock == BedBlock7::getID())
											{
												pillowPosition.x = (int)testPos.x+0.5f;
												pillowPosition.y = (int)testPos.y+0.8f;
												pillowPosition.z = (int)testPos.z+0.75f;
											}
											if(selectedBlock == BedBlock3::getID())
											{
												pillowPosition.x = (int)testPos.x+0.5f;
												pillowPosition.y = (int)testPos.y+0.8f;
												pillowPosition.z = (int)testPos.z+1.75f;
											}

											playerPosition = pillowPosition;

											fppCam->PositionCamera(playerPosition.x,playerPosition.y,playerPosition.z, playerPosition.x,playerPosition.y,playerPosition.z-5.0f, 0.0f,1.0f,0.0f);
											fppCam->RotateView(0,0,90,0);
											fppCam->upDownAngle = 0;
											fppCam->horAngle = 270;
											return;
										}
										if(selectedBlock == BedBlock4::getID() || selectedBlock == BedBlock8::getID())
										{
											Vector3 pillowPosition;
											if(selectedBlock == BedBlock8::getID())
											{
												pillowPosition.x = (int)testPos.x+0.5f;
												pillowPosition.y = (int)testPos.y+0.8f;
												pillowPosition.z = (int)testPos.z+0.25f;
											}
											if(selectedBlock == BedBlock4::getID())
											{
												pillowPosition.x = (int)testPos.x+0.5f;
												pillowPosition.y = (int)testPos.y+0.8f;
												pillowPosition.z = (int)testPos.z-0.75f;
											}

											playerPosition = pillowPosition;

											fppCam->PositionCamera(playerPosition.x,playerPosition.y,playerPosition.z, playerPosition.x,playerPosition.y,playerPosition.z+5.0f, 0.0f,1.0f,0.0f);
											fppCam->RotateView(0,0,270,0);
											fppCam->upDownAngle = 0;
											fppCam->horAngle = 90;
											return;
										}
									}
									
								}
								else
								{
									int explosionRadius = 2.5f;
									
									mWorld->BuildExplodeSphere(explosionRadius,testPos.x,testPos.y,testPos.z);

									mWorld->AddChunkToFastUpdate(mWorld->getChunkId(Vector3(testPos.x+4,testPos.y+4,testPos.z+4)));
									mWorld->AddChunkToFastUpdate(mWorld->getChunkId(Vector3(testPos.x-4,testPos.y+4,testPos.z+4)));
									mWorld->AddChunkToFastUpdate(mWorld->getChunkId(Vector3(testPos.x-4,testPos.y+4,testPos.z-4)));
									mWorld->AddChunkToFastUpdate(mWorld->getChunkId(Vector3(testPos.x+4,testPos.y+4,testPos.z-4)));

									mWorld->AddChunkToFastUpdate(mWorld->getChunkId(Vector3(testPos.x+4,testPos.y-4,testPos.z+4)));
									mWorld->AddChunkToFastUpdate(mWorld->getChunkId(Vector3(testPos.x-4,testPos.y-4,testPos.z+4)));
									mWorld->AddChunkToFastUpdate(mWorld->getChunkId(Vector3(testPos.x-4,testPos.y-4,testPos.z-4)));
									mWorld->AddChunkToFastUpdate(mWorld->getChunkId(Vector3(testPos.x+4,testPos.y-4,testPos.z-4)));
								
									//Vector3 blockCoordinate;
									//blockCoordinate = mWorld->GetBlock(testPos.x, testPos.y, testPos.z);
									for(float verAngle = 0.0f; verAngle <= PI; verAngle += PI/4.0f)
									{
										for(float horAngle = 0.0f; horAngle <= PI*2; horAngle += PI/2.0f)
										{
											if(mParticles.size() > 52)
											{
												continue;
											}
											float radius = 4.5f + (rand() % 100)/10.0f;

											Particle* Smoke = new Particle(mWorld,"smoke",Vector3(testPos.x,testPos.y,testPos.z));
											Smoke->SetVelocity(Vector3(mWorld->LengthDirX(horAngle,verAngle)*radius,mWorld->LengthDirY(horAngle,verAngle)*radius,mWorld->LengthDirZ(horAngle,verAngle)*radius));
											Smoke->SetScale(0.3f+(rand()%25)/100.0f);
											Smoke->friction = 4.25f;

											mParticles.push_back(Smoke);
										}
									}
									if(mParticles.size() < 64)
									{
										Particle* Explosion = new Particle(mWorld,"explosion",Vector3(testPos.x-1.2f,testPos.y-1.2f,testPos.z));
										Particle* Explosion2 = new Particle(mWorld,"explosion",Vector3(testPos.x+1.2f,testPos.y+1.2f,testPos.z));
										Particle* Explosion3 = new Particle(mWorld,"explosion",Vector3(testPos.x,testPos.y-1.2f,testPos.z-1.2f));
										Particle* Explosion4 = new Particle(mWorld,"explosion",Vector3(testPos.x,testPos.y+1.2f,testPos.z+1.2f));
										Particle* Explosion5 = new Particle(mWorld,"explosion",Vector3(testPos.x,testPos.y,testPos.z));
										mParticles.push_back(Explosion);
										mParticles.push_back(Explosion2);
										mParticles.push_back(Explosion3);
										mParticles.push_back(Explosion4);
										mParticles.push_back(Explosion5);
									}
									mSoundMgr->PlayTNTSound();
								}
							}
							
							BoundingBox testBox2 = BoundingBox(Vector3(cubePos.x - 0.5f,cubePos.y - 0.5f,cubePos.z - 0.5f),Vector3(cubePos.x + 0.5f,cubePos.y + 0.5f,cubePos.z + 0.5f));
							Ray tesRay = Ray(fppCam->m_vPosition,rayDir);

							float distance = -1.0f;
							tesRay.hasIntersected(testBox2,distance);

							bool wasUpdated = false;

							if(distance != -1.0f)
							{
								Vector3 hitPos = fppCam->m_vPosition + (rayDir * distance);
								Vector3 normal = (hitPos - cubePos);
								normal.normalize();

								Vector3 testPos2;

								if(normal.x < -0.66f)
									testPos2.x = -1.0f;
								else if(normal.x > 0.66f)
									testPos2.x = 1.0f;
								else
									testPos2.x = 0.0f;

								if(normal.y < -0.66f)
									testPos2.y = -1.0f;
								else if(normal.y > 0.66f)
									testPos2.y = 1.0f;
								else
									testPos2.y = 0.0f;

								if(normal.z < -0.66f)
									testPos2.z = -1.0f;
								else if(normal.z > 0.66f)
									testPos2.z = 1.0f;
								else
									testPos2.z = 0.0f;

								testPos2 += testPos;

								//check if this block is empty
								if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == Lava::getID() ||
								   mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 4 ||
								   mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0 ||
								   mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 93)
								{
									//now check if player is not there ;) we don't want to place cubes where we stand
									int boxX = (int)testPos2.x;
									int boxY = (int)testPos2.y;
									int boxZ = (int)testPos2.z;

									BoundingBox blockBox = BoundingBox(Vector3(boxX,boxY,boxZ),Vector3(boxX + 1,boxY + 1,boxZ + 1));
									BoundingBox playerBox;
									if(walkingOnGround == false)
									{
										playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.63f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
									}
									else
									{
										playerBox = BoundingBox(Vector3(playerPosition.x - (mWorld->playerCollisionSize-0.03f),playerPosition.y - 1.59f,playerPosition.z - (mWorld->playerCollisionSize-0.03)),Vector3(playerPosition.x + (mWorld->playerCollisionSize-0.03),playerPosition.y + 0.2f,playerPosition.z + (mWorld->playerCollisionSize-0.03)));
									}

									if(!blockBox.intersect(playerBox) ||
									   mWorld->invId[27+barPosition] == TorchItem::getID()    ||
									   mWorld->invId[27+barPosition] == LadderItem::getID()   ||
									   mWorld->invId[27+barPosition] == WheatSeeds::getID()   ||
									   mWorld->invId[27+barPosition] == MelonSeeds::getID()   ||
									   mWorld->invId[27+barPosition] == PumpkinSeeds::getID() ||
									   mWorld->invId[27+barPosition] == Carrot::getID()       ||
									   mWorld->invId[27+barPosition] == Potato::getID())
									{
										//check if you want put light source or normal block
										if(mWorld->CanPutBlockHere(testPos2.x,testPos2.y,testPos2.z,mWorld->invId[27+barPosition]))
										{
											bool wasLight = false;
											int oldBlock = mWorld->invId[27+barPosition];

											if(mWorld->LightSourceBlock(mWorld->invId[27+barPosition]))
											{
												wasLight = true;
												mWorld->SetLigtSourcePosition(testPos2.x,testPos2.y,testPos2.z,mWorld->invId[27+barPosition]);
											}

											if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == Lava::getID())
											{
												wasLight = true;
												mWorld->RemoveLigtSourceAtPosition(testPos2.x,testPos2.y,testPos2.z,112);
												mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 0;
											}

											if (mWorld->invId[27+barPosition]<250) // if block in our hands
											{
												if (mWorld->invId[27+barPosition] >= BlackWoolCarpet::getID() && mWorld->invId[27+barPosition] <= WhiteWoolCarpet::getID()) // if carpet in our hands
												{
													if(mWorld->BlockSpecial(testPos2.x,testPos2.y-1,testPos2.z) != 2)
													{
														if(mWorld->BlockSpecial(testPos2.x,testPos2.y-1,testPos2.z) != 0 || mWorld->BlockSolid(testPos2.x,testPos2.y-1,testPos2.z) == false)
														{
															return;
														}
													}
												}

												if(mWorld->invId[27+barPosition] == NoteBlock::getID()) // if we are putting note block
												{
													NoteBlockEntity* NewNoteBlockEntity = new NoteBlockEntity(testPos2.x,testPos2.y,testPos2.z,12);
													mWorld->mNoteBlocks.push_back(NewNoteBlockEntity);
												}

												if(mWorld->invId[27+barPosition] == JukeBox::getID()) // if we are putting jukebox
												{
													JukeboxEntity* NewJukeboxEntity = new JukeboxEntity(testPos2.x,testPos2.y,testPos2.z,-1);
													mWorld->mJukeboxes.push_back(NewJukeboxEntity);
												}

												if(mWorld->invId[27+barPosition] == ChestBlock3::getID()) // if we are putting chest
												{
													Chest* NewChest =  new Chest(testPos2.x,testPos2.y,testPos2.z);
													mWorld->mChests.push_back(NewChest);
												}

												if(mWorld->invId[27+barPosition] == FurnaceOff::getID()) // if we are putting chest
												{
													Furnace* NewFurnace =  new Furnace(testPos2.x,testPos2.y,testPos2.z);

													NewFurnace->SetSide(0);
													if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
													{
														NewFurnace->SetSide(3);
													}
													if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
													{
														NewFurnace->SetSide(0);
													}
													if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
													{
														NewFurnace->SetSide(2);
													}
													if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
													{
														NewFurnace->SetSide(1);
													}

													mWorld->mFurnaces.push_back(NewFurnace);
												}

												if(mWorld->invId[27+barPosition]!=-1) //multi-texturing blocks
												{
													bool placed = true;

													switch(mWorld->invId[27+barPosition])
													{
														case 75:
														if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 75;
														}
														if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 76;
														}
														if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 73;
														}
														if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 74;
														}
														if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 73;
														}
														break;

														case 145:
														if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 145;
														}
														if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 146;
														}
														if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 143;
														}
														if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 144;
														}
														if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 143;
														}
														break;

														case 96:
														if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 96; // 3
														}
														if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 97; // 4
														}
														if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 94; // 1
														}
														if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 95; // 2
														}
														if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 94;
														}
														break;

														case 125:
														if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 125; // 3
														}
														if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 126; // 4
														}
														if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 127; // 1
														}
														if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 128; // 2
														}
														if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 125;
														}
														break;

														case 161: // birch stair
														if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 161; // 3
														}
														if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 162; // 4
														}
														if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 163; // 1
														}
														if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 164; // 2
														}
														if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 161;
														}
														break;

														case 165: // spruce stair
														if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 165; // 3
														}
														if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 166; // 4
														}
														if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 167; // 1
														}
														if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 168; // 2
														}
														if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 165;
														}
														break;

														case 60:
														if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 60; // 3
														}
														if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 61; // 4
														}
														if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 62; // 1
														}
														if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 63; // 2
														}
														if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 60;
														}
														break;

														case 67:
														if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 67; // 3
														}
														if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 68; // 4
														}
														if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 69; // 1
														}
														if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 70; // 2
														}
														if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 67;
														}
														break;

														case 151:
														if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
														{
															if(mWorld->BlockSolid(testPos2.x,testPos2.y,testPos2.z+1))
															{
																mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 154; // 3
															}
															else
															{
																placed = false;
															}
														}
														if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
														{
															if(mWorld->BlockSolid(testPos2.x,testPos2.y,testPos2.z-1))
															{
																mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 153; // 4
															}
															else
															{
																placed = false;
															}
														}
														if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
														{
															if(mWorld->BlockSolid(testPos2.x+1,testPos2.y,testPos2.z))
															{
																mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 152; // 1
															}
															else
															{
																placed = false;
															}
														}
														if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
														{
															if(mWorld->BlockSolid(testPos2.x-1,testPos2.y,testPos2.z))
															{
																mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 151; // 2
															}
															else
															{
																placed = false;
															}
														}
														if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
														{
															if(mWorld->BlockSolid(testPos2.x-1,testPos2.y,testPos2.z))
															{
																mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 151;
															}
															else
															{
																placed = false;
															}
														}
														break;


														default:
														mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = mWorld->invId[27+barPosition];
														break;
													}

													if(placed)
													{
														if(mWorld->invAm[27+barPosition]==1)
														{
															mWorld->invAm[27+barPosition]= -1;
															mWorld->invId[27+barPosition]= -1;
															mWorld->invSt[27+barPosition]= 0;
														}
														else
														{
															mWorld->invAm[27+barPosition]-= 1;
														}
													}
													else
													{
														return;
													}
												}
											}
											else //if it is item in our hand
											{
												if(mWorld->invId[27+barPosition] == TorchItem::getID()) // if it is torch
												{
													if(mWorld->BlockSolid(testPos2.x+1,testPos2.y,testPos2.z) == true || mWorld->BlockSolid(testPos2.x-1,testPos2.y,testPos2.z) == true || mWorld->BlockSolid(testPos2.x,testPos2.y,testPos2.z-1) == true || mWorld->BlockSolid(testPos2.x,testPos2.y,testPos2.z+1) == true || mWorld->BlockSolid(testPos2.x,testPos2.y-1,testPos2.z) == true)
													{
														mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 48;
														fppCam->needUpdate = true;

														mWorld->invAm[27+barPosition] -= 1;
														if(mWorld->invAm[27+barPosition] == 0)
														{
														   mWorld->invAm[27+barPosition] = -1;
														   mWorld->invSt[27+barPosition] = 0;
														   mWorld->invId[27+barPosition] = -1;
														}
														wasLight = true;
														mWorld->SetLigtSourcePosition(testPos2.x,testPos2.y,testPos2.z,mWorld->invId[27+barPosition]);
													}
													else
													{
														return;
													}
												}

												if(mWorld->invId[27+barPosition] == WheatSeeds::getID()) // if it is seeds
												{
													if( mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 79 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 80) // planting seeds
													{
														mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 134;
														fppCam->needUpdate = true;

														mWorld->invAm[27+barPosition] -= 1;
														if(mWorld->invAm[27+barPosition] == 0)
														{
														   mWorld->invAm[27+barPosition] = -1;
														   mWorld->invSt[27+barPosition] = 0;
														   mWorld->invId[27+barPosition] = -1;
														}
													}
													else
													{
														return;
													}
												}

												if(mWorld->invId[27+barPosition] == MelonSeeds::getID()) // if it is melon seeds
												{
													if( mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == Soil::getID() || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == WateredSoil::getID()) // planting seeds
													{
														mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = MelonPlant1::getID();
														fppCam->needUpdate = true;

														mWorld->invAm[27+barPosition] -= 1;
														if(mWorld->invAm[27+barPosition] == 0)
														{
														   mWorld->invAm[27+barPosition] = -1;
														   mWorld->invSt[27+barPosition] = 0;
														   mWorld->invId[27+barPosition] = -1;
														}
													}
													else
													{
														return;
													}
												}

												if(mWorld->invId[27+barPosition] == PumpkinSeeds::getID()) // if it is pumpkin seeds
												{
													if( mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == Soil::getID() || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == WateredSoil::getID()) // planting seeds
													{
														mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = PumpkinPlant1::getID();
														fppCam->needUpdate = true;

														mWorld->invAm[27+barPosition] -= 1;
														if(mWorld->invAm[27+barPosition] == 0)
														{
														   mWorld->invAm[27+barPosition] = -1;
														   mWorld->invSt[27+barPosition] = 0;
														   mWorld->invId[27+barPosition] = -1;
														}
													}
													else
													{
														return;
													}
												}

												if(mWorld->invId[27+barPosition] == Potato::getID())
												{
													if( mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == Soil::getID() || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == WateredSoil::getID()) // planting seeds
													{
														mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = PotatoPlant1::getID();
														fppCam->needUpdate = true;

														mWorld->invAm[27+barPosition] -= 1;
														if(mWorld->invAm[27+barPosition] == 0)
														{
														   mWorld->invAm[27+barPosition] = -1;
														   mWorld->invSt[27+barPosition] = 0;
														   mWorld->invId[27+barPosition] = -1;
														}
														mWorld->RebuildTransparentMeshChunk(mWorld->getChunkId(testPos2));

														animGo = true;
														animDest = 0.0f;
														currentState = 0;

														changeY = -0.1f;
														anim[0] = 1;
													}
													return;
												}

												if(mWorld->invId[27+barPosition] == Carrot::getID())
												{
													if( mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == Soil::getID() || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == WateredSoil::getID()) // planting seeds
													{
														mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = CarrotPlant1::getID();
														fppCam->needUpdate = true;

														mWorld->invAm[27+barPosition] -= 1;
														if(mWorld->invAm[27+barPosition] == 0)
														{
														   mWorld->invAm[27+barPosition] = -1;
														   mWorld->invSt[27+barPosition] = 0;
														   mWorld->invId[27+barPosition] = -1;
														}
														mWorld->RebuildTransparentMeshChunk(mWorld->getChunkId(testPos2));

														animGo = true;
														animDest = 0.0f;
														currentState = 0;

														changeY = -0.1f;
														anim[0] = 1;
													}
													return;
												}

												if(mWorld->invId[27+barPosition] == GlassPanelItem::getID()) // if it is glass panel
												{
													mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = GlassPanel::getID();

													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);

													mWorld->invAm[27+barPosition] -= 1;
													if(mWorld->invAm[27+barPosition] == 0)
													{
													   mWorld->invAm[27+barPosition] = -1;
													   mWorld->invSt[27+barPosition] = 0;
													   mWorld->invId[27+barPosition] = -1;
													}

													wasUpdated = true;
												}

												if(mWorld->invId[27+barPosition] == IronBarsItem::getID()) // if it is iron bars,kw
												{
													mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = IronBars::getID();

													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);

													mWorld->invAm[27+barPosition] -= 1;
													if(mWorld->invAm[27+barPosition] == 0)
													{
													   mWorld->invAm[27+barPosition] = -1;
													   mWorld->invSt[27+barPosition] = 0;
													   mWorld->invId[27+barPosition] = -1;
													}

													wasUpdated = true;
												}

												if(mWorld->invId[27+barPosition] >= 300 && mWorld->invId[27+barPosition] <= 301) // if it is moshrooms
												{
													mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 77 + (mWorld->invId[27+barPosition] - 300);
													fppCam->needUpdate = true;

													mWorld->invAm[27+barPosition] -= 1;
													if(mWorld->invAm[27+barPosition] == 0)
													{
														mWorld->invAm[27+barPosition] = -1;
														mWorld->invSt[27+barPosition] = 0;
														mWorld->invId[27+barPosition] = -1;
													}
												}

												if(mWorld->invId[27+barPosition] >= 294 && mWorld->invId[27+barPosition] <= 296) // if it is flowers or saplings
												{
													if(mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 1 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 2) // if under is dirt or grass
													{
														mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 119 + (mWorld->invId[27+barPosition] - 294); //very difficult expression >:
														fppCam->needUpdate = true;

														mWorld->invAm[27+barPosition] -= 1;
														if(mWorld->invAm[27+barPosition] == 0)
														{
														   mWorld->invAm[27+barPosition] = -1;
														   mWorld->invSt[27+barPosition] = 0;
														   mWorld->invId[27+barPosition] = -1;
														}
													}
													else
													{
														return;
													}
												}
												
												// generador del portal
												if(mWorld->invId[27+barPosition] == FlintAndSteel::getID())
												{
													if(selectedBlock == Obsidian::getID())
													{
														int created1 = false;
														if(mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 46)
														{
															if(mWorld->GetBlock(testPos2.x-1,testPos2.y-1,testPos2.z) == 46)
															{
																if(mWorld->GetBlock(testPos2.x+1,testPos2.y,testPos2.z) == 46 && mWorld->GetBlock(testPos2.x+1,testPos2.y+1,testPos2.z) == 46 && mWorld->GetBlock(testPos2.x+1,testPos2.y+2,testPos2.z) == 46)
																{
																	if(mWorld->GetBlock(testPos2.x-2,testPos2.y,testPos2.z) == 46 && mWorld->GetBlock(testPos2.x-2,testPos2.y+1,testPos2.z) == 46 && mWorld->GetBlock(testPos2.x-2,testPos2.y+2,testPos2.z) == 46)
																	{
																		if(mWorld->GetBlock(testPos2.x,testPos2.y+3,testPos2.z) == 46 && mWorld->GetBlock(testPos2.x-1,testPos2.y+3,testPos2.z) == 46)
																		{
																			mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x,testPos2.y+2,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x-1,testPos2.y,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x-1,testPos2.y+1,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x-1,testPos2.y+2,testPos2.z) = 222;
																			
																			mWorld->UpdateLightAreaIn(testPos2);
																			created1 = true;
																		}
																	}
																}
															}
															if(mWorld->GetBlock(testPos2.x+1,testPos2.y-1,testPos2.z) == 46)
															{
																if(mWorld->GetBlock(testPos2.x-1,testPos2.y,testPos2.z) == 46 && mWorld->GetBlock(testPos2.x-1,testPos2.y+1,testPos2.z) == 46 && mWorld->GetBlock(testPos2.x-1,testPos2.y+2,testPos2.z) == 46)
																{
																	if(mWorld->GetBlock(testPos2.x+2,testPos2.y,testPos2.z) == 46 && mWorld->GetBlock(testPos2.x+2,testPos2.y+1,testPos2.z) == 46 && mWorld->GetBlock(testPos2.x+2,testPos2.y+2,testPos2.z) == 46)
																	{
																		if(mWorld->GetBlock(testPos2.x,testPos2.y+3,testPos2.z) == 46 && mWorld->GetBlock(testPos2.x+1,testPos2.y+3,testPos2.z) == 46)
																		{
																			mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x,testPos2.y+2,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x+1,testPos2.y,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x+1,testPos2.y+1,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x+1,testPos2.y+2,testPos2.z) = 222;
																			
																			mWorld->UpdateLightAreaIn(testPos2);
																			created1 = true;
																		}
																	}
																}
															}

															if(mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z-1) == 46)
															{
																if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z+1) == 46 && mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z+1) == 46 && mWorld->GetBlock(testPos2.x,testPos2.y+2,testPos2.z+1) == 46)
																{
																	if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z-2) == 46 && mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z-2) == 46 && mWorld->GetBlock(testPos2.x,testPos2.y+2,testPos2.z-2) == 46)
																	{
																		if(mWorld->GetBlock(testPos2.x,testPos2.y+3,testPos2.z) == 46 && mWorld->GetBlock(testPos2.x,testPos2.y+3,testPos2.z-1) == 46)
																		{
																			mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x,testPos2.y+2,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z-1) = 222;
																			mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z-1) = 222;
																			mWorld->GetBlock(testPos2.x,testPos2.y+2,testPos2.z-1) = 222;
																			
																			mWorld->UpdateLightAreaIn(testPos2);
																			created1 = true;
																		}
																	}
																}
															}

															if(mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z+1) == 46)
															{
																if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z-1) == 46 && mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z-1) == 46 && mWorld->GetBlock(testPos2.x,testPos2.y+2,testPos2.z-1) == 46)
																{
																	if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z+2) == 46 && mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z+2) == 46 && mWorld->GetBlock(testPos2.x,testPos2.y+2,testPos2.z+2) == 46)
																	{
																		if(mWorld->GetBlock(testPos2.x,testPos2.y+3,testPos2.z) == 46 && mWorld->GetBlock(testPos2.x,testPos2.y+3,testPos2.z+1) == 46)
																		{
																			mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x,testPos2.y+2,testPos2.z) = 222;
																			mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z+1) = 222;
																			mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z+1) = 222;
																			mWorld->GetBlock(testPos2.x,testPos2.y+2,testPos2.z+1) = 222;
																			
																			mWorld->UpdateLightAreaIn(testPos2);
																			created1 = true;
																		}
																	}
																}
															}
														}
														else
														{
															return;
														}
														if(created1 == true)
														{
															mSoundMgr->PlayIgniteSound();
															fppCam->needUpdate = true;

															mWorld->invAm[27+barPosition] -= 1;
															if(mWorld->invAm[27+barPosition] <= 0)
															{
																mWorld->invAm[27+barPosition] = -1;
																mWorld->invSt[27+barPosition] = 0;
																mWorld->invId[27+barPosition] = -1;
															}
														}
													}
													else if(mWorld->BlockSolid(testPos2.x,testPos2.y-1,testPos2.z) == true)
													{
														mSoundMgr->PlayIgniteSound();
														mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = FireBlock::getID();
														fppCam->needUpdate = true;;

														mWorld->invAm[27+barPosition] -= 1;
														if(mWorld->invAm[27+barPosition] == 0)
														{
															mWorld->invAm[27+barPosition] = -1;
															mWorld->invSt[27+barPosition] = 0;
															mWorld->invId[27+barPosition] = -1;
														}
														wasLight = true;
														mWorld->SetLigtSourcePosition(testPos2.x,testPos2.y,testPos2.z,FireBlock::getID());
													}
													else 
													{
														return;
													}
												}
												
												/// SPAWN EGGS
												
												/*if(mWorld->invId[27+barPosition] == Stick::getID())
												{
														mWorld->SpawnSpider(testPos2.x,testPos2.y,testPos2.z);
														
														fppCam->needUpdate = true;
														int chunkTarget = mWorld->getChunkId(testPos2);
														mWorld->RebuildTransparentMeshChunk(chunkTarget);
														mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}
												
												if(mWorld->invId[27+barPosition] == Feather::getID())
												{
														mWorld->SpawnSpidercave(testPos2.x,testPos2.y,testPos2.z);
														
														fppCam->needUpdate = true;
														int chunkTarget = mWorld->getChunkId(testPos2);
														mWorld->RebuildTransparentMeshChunk(chunkTarget);
														mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}*/
												
												if(mWorld->invId[27+barPosition] == CowEGG::getID())
												{
													mWorld->SpawnCow(testPos2.x,testPos2.y,testPos2.z);
													
													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}
												
												if(mWorld->invId[27+barPosition] == SpiderEGG::getID())
												{
													mWorld->SpawnSpider(testPos2.x,testPos2.y,testPos2.z);
													
													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}
												
												if(mWorld->invId[27+barPosition] == SpidercaveEGG::getID())
												{
													mWorld->SpawnSpidercave(testPos2.x,testPos2.y,testPos2.z);
													
													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}
												
												if(mWorld->invId[27+barPosition] == SheepEGG::getID())
												{
													mWorld->SpawnSheep(testPos2.x,testPos2.y,testPos2.z);
													
													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}
												
												if(mWorld->invId[27+barPosition] == ChickenEGG::getID())
												{
													mWorld->SpawnChicken(testPos2.x,testPos2.y,testPos2.z);
													
													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}
												
												if(mWorld->invId[27+barPosition] == PigEGG::getID())
												{
													mWorld->SpawnPig(testPos2.x,testPos2.y,testPos2.z);
													
													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}
												
												if(mWorld->invId[27+barPosition] == ZombieEGG::getID())
												{
													mWorld->SpawnZombie(testPos2.x,testPos2.y,testPos2.z);
													
													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}
												
												if(mWorld->invId[27+barPosition] == SkeletonEGG::getID())
												{
													mWorld->SpawnSkeleton(testPos2.x,testPos2.y,testPos2.z);
													
													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}
												
												if(mWorld->invId[27+barPosition] == PigmanEGG::getID())
												{
													mWorld->SpawnPigman(testPos2.x,testPos2.y,testPos2.z);
													
													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}
												
												if(mWorld->invId[27+barPosition] == WitherSkeletonEGG::getID())
												{
													mWorld->SpawnWitherSkeleton(testPos2.x,testPos2.y,testPos2.z);
													
													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}
												
												if(mWorld->invId[27+barPosition] == VillagerEGG::getID())
												{
													mWorld->SpawnVillager(testPos2.x,testPos2.y,testPos2.z);
													
													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}
												
												if(mWorld->invId[27+barPosition] == WolfEGG::getID())
												{
													mWorld->SpawnWolf(testPos2.x,testPos2.y,testPos2.z);
													
													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}
												
												if(mWorld->invId[27+barPosition] == CreeperEGG::getID())
												{
													mWorld->SpawnCreeper(testPos2.x,testPos2.y,testPos2.z);
													
													fppCam->needUpdate = true;
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->RebuildTransparentMeshChunk(chunkTarget);
													mWorld->rebuildNearestChunks(chunkTarget,testPos2);
												}
												
												/// END

												if(mWorld->invId[27+barPosition] == 309 || mWorld->invId[27+barPosition] == 310) // if it is another sapling
												{
													if(mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 1 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 2 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 29) // if under is dirt or grass
													{
														mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 122 + (mWorld->invId[27+barPosition] - 309); //very difficult expression >:
														fppCam->needUpdate = true;

														mWorld->invAm[27+barPosition] -= 1;
														if(mWorld->invAm[27+barPosition] == 0)
														{
														   mWorld->invAm[27+barPosition] = -1;
														   mWorld->invSt[27+barPosition] = 0;
														   mWorld->invId[27+barPosition] = -1;
														}
													}
													else
													{
														return;
													}
												}

												if(mWorld->invId[27+barPosition] == 306) // if it is door item
												{
													if(mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) == 0)
													{
														if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 49; // 3
															mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
														}
														if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 50; // 4
															mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
														}
														if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 51; // 1
															mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
														}
														if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 52; // 2
															mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
														}
														if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 49;
															mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
														}

														fppCam->needUpdate = true;
														int chunkTarget = mWorld->getChunkId(testPos2);
														mWorld->RebuildTransparentMeshChunk(chunkTarget);
														mWorld->rebuildNearestChunks(chunkTarget,testPos2);

														wasUpdated = true;

														mWorld->invAm[27+barPosition] -= 1;
														if(mWorld->invAm[27+barPosition] == 0)
														{
															mWorld->invAm[27+barPosition] = -1;
															mWorld->invSt[27+barPosition] = 0;
															mWorld->invId[27+barPosition] = -1;
														}

														animGo = true;
														animDest = 0.0f;
														currentState = 0;
													}
													else
													{
														return;
													}
												}


												if(mWorld->invId[27+barPosition] == BedItem::getID()) // if it is door item
												{
													bool placed = false;
													if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
													{

														if(mWorld->GetBlock(testPos2.x+1,testPos2.y,testPos2.z) == 0)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = BedBlock1::getID(); // 3
															mWorld->GetBlock(testPos2.x+1,testPos2.y,testPos2.z) = BedBlock5::getID();

															placed = true;
														}
													}
													if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
													{

														if(mWorld->GetBlock(testPos2.x-1,testPos2.y,testPos2.z) == 0)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = BedBlock2::getID(); // 3
															mWorld->GetBlock(testPos2.x-1,testPos2.y,testPos2.z) = BedBlock6::getID();

															placed = true;
														}
													}
													if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
													{
														if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z+1) == 0)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = BedBlock3::getID(); // 3
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z+1) = BedBlock7::getID();

															placed = true;
														}
													}
													if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
													{
														if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z-1) == 0)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = BedBlock4::getID(); // 3
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z-1) = BedBlock8::getID();

															placed = true;
														}
													}


													if(placed)
													{
														fppCam->needUpdate = true;
														int chunkTarget = mWorld->getChunkId(testPos2);
														mWorld->RebuildTransparentMeshChunk(chunkTarget);
														mWorld->rebuildNearestChunks(chunkTarget,testPos2);

														wasUpdated = true;

														mWorld->invAm[27+barPosition] -= 1;
														if(mWorld->invAm[27+barPosition] == 0)
														{
															mWorld->invAm[27+barPosition] = -1;
															mWorld->invSt[27+barPosition] = 0;
															mWorld->invId[27+barPosition] = -1;
														}

														animGo = true;
														animDest = 0.0f;
														currentState = 0;

														return;
													}
												}


												if(mWorld->invId[27+barPosition] == ItemFrameItem::getID()) // if it is door item
												{
													bool placed = false;
													unsigned int facing = 0;

													if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
													{
														if(mWorld->BlockSolid(testPos2.x,testPos2.y,testPos2.z+1))
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = ItemFrame4::getID();

															facing = 4;
															placed = true;
														}
													}
													if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
													{
														if(mWorld->BlockSolid(testPos2.x,testPos2.y,testPos2.z-1))
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = ItemFrame3::getID();

															facing = 3;
															placed = true;
														}
													}
													if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
													{
														if(mWorld->BlockSolid(testPos2.x+1,testPos2.y,testPos2.z))
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = ItemFrame2::getID();

															facing = 2;
															placed = true;
														}
													}
													if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
													{
														if(mWorld->BlockSolid(testPos2.x-1,testPos2.y,testPos2.z))
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = ItemFrame1::getID();

															facing = 1;
															placed = true;
														}
													}

													if(placed)
													{
														ItemFrameEntity* NewItemFrameEntity = new ItemFrameEntity(testPos2.x,testPos2.y,testPos2.z,facing);
														mWorld->mItemFrames.push_back(NewItemFrameEntity);

														fppCam->needUpdate = true;
														int chunkTarget = mWorld->getChunkId(testPos2);

														mWorld->RebuildTransparentMeshChunk(chunkTarget);

														mWorld->invAm[27+barPosition] -= 1;
														if(mWorld->invAm[27+barPosition] == 0)
														{
															mWorld->invAm[27+barPosition] = -1;
															mWorld->invSt[27+barPosition] = 0;
															mWorld->invId[27+barPosition] = -1;
														}

														wasUpdated = true;
													}
													else
													{
														return;
													}
												}


												if(mWorld->invId[27+barPosition] == 307) // if it is ladder item
												{
													bool placed = false;
													if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
													{
														if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z+1) != 0 && mWorld->BlockSolid(testPos2.x,testPos2.y,testPos2.z+1) == true)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 90; // 3
															placed = true;
														}
													}
													if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
													{
														if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z-1) != 0 && mWorld->BlockSolid(testPos2.x,testPos2.y,testPos2.z-1) == true)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 89;
															placed = true;
														}
													}
													if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
													{
														if(mWorld->GetBlock(testPos2.x+1,testPos2.y,testPos2.z) != 0 && mWorld->BlockSolid(testPos2.x+1,testPos2.y,testPos2.z) == true)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 88;
															placed = true;
														}
													}
													if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
													{
														if(mWorld->GetBlock(testPos2.x-1,testPos2.y,testPos2.z) != 0 && mWorld->BlockSolid(testPos2.x-1,testPos2.y,testPos2.z) == true)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 87;
															placed = true;
														}
													}

													if(placed == true)
													{
														fppCam->needUpdate = true;
														int chunkTarget = mWorld->getChunkId(testPos2);

														mWorld->RebuildTransparentMeshChunk(chunkTarget);
														mWorld->rebuildNearestChunks(chunkTarget,testPos2);

														wasUpdated = true;

														mWorld->invAm[27+barPosition] -= 1;
														if(mWorld->invAm[27+barPosition] == 0)
														{
															mWorld->invAm[27+barPosition] = -1;
															mWorld->invSt[27+barPosition] = 0;
															mWorld->invId[27+barPosition] = -1;
														}
													}
													else
													{
														return;
													}
												}


												if(mWorld->invId[27+barPosition] == 293) // if it is cane item
												{
													if(mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 7) //check if under is sand
													{
														if(mWorld->GetBlock(testPos2.x-1,testPos2.y-1,testPos2.z) == 4 || mWorld->GetBlock(testPos2.x+1,testPos2.y-1,testPos2.z) == 4 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z+1) == 4 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z-1) == 4)
														{
															mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 33;
															fppCam->needUpdate = true;

															mWorld->invAm[27+barPosition] -= 1;
															if(mWorld->invAm[27+barPosition] == 0)
															{
																mWorld->invAm[27+barPosition] = -1;
																mWorld->invSt[27+barPosition] = 0;
																mWorld->invId[27+barPosition] = -1;
															}
														}
													}
													else
													{
														return;
													}
												}

												if(mWorld->invId[27+barPosition] == 291) // if it is water busket
												{
													int chunkTarget = mWorld->getChunkId(testPos2);
													mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 4;
													mWorld->invId[27+barPosition] = 290;

													//mWorld->rebuildChunk(chunkTarget);
													//mWorld->rebuildTransparentChunk(chunkTarget);
													fppCam->needUpdate = true;
												}
												if(mWorld->invId[27+barPosition] == 292) // if it is lava busket//lava
												{
													int chunkTarget = mWorld->getChunkId(testPos2);

													mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 112;
													mWorld->invId[27+barPosition] = 290;

													if(mWorld->mChunks[chunkTarget]->periodicallyUpadted == false)
													{
														mWorld->updatingChunks.push_back(chunkTarget);
														mWorld->mChunks[chunkTarget]->periodicallyUpadted = true;
													}

													wasLight = true;
													mWorld->SetLigtSourcePosition(testPos2.x,testPos2.y,testPos2.z,mWorld->invId[27+barPosition]);
													fppCam->needUpdate = true;
												}
											}

											// some animation stuff
											animGo = true;
											animDest = 0.0f;
											currentState = 0;

											changeY = -0.1f;
											anim[0] = 1;


											int chunkTarget = mWorld->getChunkId(testPos2);

											if(oldBlock < 250 && oldBlock != -1)
											{
												mSoundMgr->PlayWalkSound(mWorld->blockTypes[oldBlock].soundType);
											}

											//rebuild
											if(wasLight == true)
											{
												mWorld->UpdateLightAreaIn(testPos2);
												mWorld->RebuildFullMeshChunk(chunkTarget);
												mWorld->rebuildNearestChunksForLight(chunkTarget,testPos2);
											}
											else
											{
												mWorld->initPutBlocksLight(testPos2.x, testPos2.y+2, testPos2.z);

												if(!wasUpdated)
												{
													if(mWorld->GetLightLevel(testPos2.x,testPos2.y,testPos2.z) != 0)
													{
														mWorld->UpdateLightAreaIn(testPos2);
													}

													mWorld->RebuildFullMeshChunk(chunkTarget);

													if(mWorld->BlockTransparent(testPos2.x,testPos2.y,testPos2.z) || mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == WoodenFence::getID())
													{
														mWorld->rebuildNearestChunks(chunkTarget,testPos2);
													}
												}
											}
										}
										fppCam->needUpdate = true;
									}
								}
							}
							break;
						}
					}
				}

				// comida
				if(keyHold(InputHelper::Instance()->getButtonToAction(14)) && ceilf(mWorld->HG) < 20.0f)
				{
					// food ID
					int ID = mWorld->invId[27+barPosition];
					
					if(ID == 288 || ID == 315 || ID == 348 || ID == 379 || ID == 381 || ID == 380 || ID == 382 || ID == 311 
					|| ID == 317 || ID == 393 || ID == 395 || ID == 397 || ID == 316 || ID == 406 || ID == 396 || ID == 396 
					|| ID == 394 || ID == 392 || ID == 284 || ID == 285 || ID == 303)
					{
						if(canEatAgain == true) foodBool = true;
					}
					else
					{
						canEatAgain = true;
						eatingTick = 0.0f;
						eatSoundTimer = 0.5f;
						return;
					}
					
					if(foodBool == true)
					{
						eatingTick = 1.7f;
						foodBool = false;
						canEatAgain = false;
					}
					
					if(foodEaten2 == true)
					{
						// ### FOOD VALUES ### //
						
						// bread
						if(ID == 288) mWorld->HG += 5;
						
						// cookies
						if(ID == 315){
							mWorld->HG += 1;
							mWorld->HP += 1;
						}

						// rotten flesh
						if(ID == 348){
							mWorld->HG += 1;
							if(rand() % 100 < 45){
								if(mWorld->gameModeWorld != 1) HGP = 20;
								if(mWorld->gameModeWorld != 1) HungerPoisoned = true;
							}
						}

						// potato
						if(ID == 379) mWorld->HG += 1;

						// poisoned potato
						if(ID == 381){
							mWorld->HG += 1;
							if(mWorld->gameModeWorld != 1) HurtPlayer(1);
							if(mWorld->gameModeWorld != 1) HPE = 5;
							if(mWorld->gameModeWorld != 1) HPPoisoned = true;
						}

						// baked potato
						if(ID == 380) mWorld->HG += 5;

						// steak |cooked porkchop | cooked mutton | cooked chicken
						if(ID == 317 || ID == 393 || ID == 395 || ID == 397) mWorld->HG += 8;
						
						// melon | raw mutton
						if(ID == 311 || ID == 394) mWorld->HG += 2;
						
						// carrot | raw beef | raw porkchop
						if(ID == 382 || ID == 316 || ID == 392) mWorld->HG += 3;
						
						// raw chicken
						if(ID == 396){
							mWorld->HG += 2;						
							if(rand() % 100 < 20){
								if(mWorld->gameModeWorld != 1) HGP = 13;
								if(mWorld->gameModeWorld != 1) HungerPoisoned = true;
							}
						}
						
						// spider eye
						if(ID == 406){
							mWorld->HG += 2;
							if(mWorld->gameModeWorld != 1) HurtPlayer(1);
							if(mWorld->gameModeWorld != 1) HPE = 5;
							if(mWorld->gameModeWorld != 1) HPPoisoned = true;
						}

						// apple
						if(ID == 284) mWorld->HG += 4;

						// golden apple
						if(ID == 285){
							mWorld->HG = 20;
							mWorld->HP = 20;
						}

						// mooshroom bowl
						if(ID == 303) mWorld->HG += 6;
						
						if(mWorld->invId[27+barPosition] == MooshroomBowl::getID())
						{
							mWorld->invId[27+barPosition] = 302;
							mWorld->invSt[27+barPosition] = 1;
						}
						else
						{
							mWorld->invAm[27+barPosition] -= 1;
							if (mWorld->invAm[27+barPosition] == 0)
							{
								mWorld->invAm[27+barPosition] = -1;
								mWorld->invId[27+barPosition] = -1;
								mWorld->invSt[27+barPosition] = 0;
							}
						}
						
						// ### END FOOD VALUES ### //
						
						canEatAgain = true;
						foodEaten2 = false;
						
						mSoundMgr->PlayBurpSound();
						
						if(mWorld->HG >= 20) mWorld->HG = 19.999f;
						eatingTick = 1.7f;		
						return;
					}
				}
				else
				{
					canEatAgain = true;
					eatingTick = 0.0f;
					eatSoundTimer = 0.5f;
				}
				
				// creativo
				if(keyPressed(InputHelper::Instance()->getButtonToAction(13)) && mWorld->gameModeWorld == 1) //remove cube
				{
					mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
					int chunkTarget = mWorld->getChunkId(testPos1);

					Vector3 rayDir = fppCam->m_vView - fppCam->m_vPosition;
					rayDir.normalize();

					//we are takin our position and view vector
					Vector3 testPos2;
					testPos2 = Vector3(-1,-1,-1);

					BoundingBox collider = mWorld->blockTypes[mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z)].collideBox;
					BoundingBox testBox = BoundingBox(testPos2.x+collider.min.x, testPos2.y+collider.min.y, testPos2.z+collider.min.z, testPos2.x+collider.max.x, testPos2.y+collider.max.y, testPos2.z+collider.max.z);

					//we are moving slowly to the target +=0.5
					for(float i = 0; i < 5.25f; i+=0.15f)
					{
						testPos2 = fppCam->m_vPosition + (rayDir * i);

						collider = mWorld->blockTypes[mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z)].collideBox;
						testBox = BoundingBox(floorf(testPos2.x)+0.5f+collider.min.x, floorf(testPos2.y)+0.5f+collider.min.y, floorf(testPos2.z)+0.5f+collider.min.z, floorf(testPos2.x)+0.5f+collider.max.x, floorf(testPos2.y)+0.5f+collider.max.y, floorf(testPos2.z)+0.5f+collider.max.z);
						
						if(mWorld->BlockEditable(testPos2.x,testPos2.y,testPos2.z) && testBox.contains(testPos2))
						{
							testPos1.x  = testPos2.x;
							testPos1.y  = testPos2.y;
							testPos1.z  = testPos2.z;

							dT = 0;
							startDt = true;
							bool wasLight = false;
							int oldBlock = 0;
							oldBlock = mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z);

							// if it's light block
							if(mWorld->LightSourceBlock(oldBlock)) wasLight = true;
							
							 // if it is chest
							if(oldBlock >= ChestBlock1::getID() && oldBlock <= ChestBlock4::getID())
							{
								chestId = FindChestId(testPos1.x,testPos1.y,testPos1.z);
								if(chestId != -1)
								{
									// drop all items in chest
									Chest* TestChest = mWorld->mChests[chestId];
									for(int i = 0; i <= 27; i++)
									{
										if(TestChest->chestSlotId[i] > 0)
										{
											Vector3 dropVelocity = Vector3(0,0,0);

											dropVelocity.x = (-15+rand()%30)*0.1f;
											dropVelocity.y = 3.0f;
											dropVelocity.z = (-15+rand()%30)*0.1f;

											if(TestChest->chestSlotAm[i] > 0)
											{
												mWorld->DropThisNoAlign(TestChest->chestSlotId[i],TestChest->chestSlotAm[i],TestChest->chestSlotSt[i],Vector3(testPos1.x+0.5f,testPos1.y+0.25f,testPos1.z+0.5f),dropVelocity);

												TestChest->chestSlotAm[i] = -1;
												TestChest->chestSlotSt[i] = 0;
												TestChest->chestSlotId[i] = -1;
											}
										}
									}
									delete mWorld->mChests[chestId];
									mWorld->mChests.erase(mWorld->mChests.begin()+chestId);
								}
							}

							if(oldBlock == FurnaceOff::getID() || oldBlock == FurnaceOn::getID())
							{
								furnaceId = FindFurnaceId(testPos1.x,testPos1.y,testPos1.z);
								if(furnaceId != -1)
								{
									// drop all items in furnace
									Furnace* TestFurnace = mWorld->mFurnaces[furnaceId];
									for(int i = 0; i <= 2; i++)
									{
										if(TestFurnace->furnaceSlotId[i] > 0)
										{
											Vector3 dropVelocity = Vector3(0,0,0);

											dropVelocity.x = (-15+rand()%30)*0.1f;
											dropVelocity.y = 3.0f;
											dropVelocity.z = (-15+rand()%30)*0.1f;

											if(TestFurnace->furnaceSlotAm[i] > 0)
											{
												mWorld->DropThisNoAlign(TestFurnace->furnaceSlotId[i],TestFurnace->furnaceSlotAm[i],TestFurnace->furnaceSlotSt[i],Vector3(testPos1.x+0.5f,testPos1.y+0.25f,testPos1.z+0.5f),dropVelocity);

												TestFurnace->furnaceSlotAm[i] = -1;
												TestFurnace->furnaceSlotSt[i] = 0;
												TestFurnace->furnaceSlotId[i] = -1;
											}
										}
									}
									delete mWorld->mFurnaces[furnaceId];
									mWorld->mFurnaces.erase(mWorld->mFurnaces.begin()+furnaceId);
								}
							}

							if(oldBlock == NoteBlock::getID())
							{
								int noteBlockId = mWorld->FindNoteBlockID(testPos1);

								if(noteBlockId != -1)
								{
									delete mWorld->mNoteBlocks[noteBlockId];
									mWorld->mNoteBlocks.erase(mWorld->mNoteBlocks.begin()+noteBlockId);
								}
							}

							if(oldBlock == JukeBox::getID())
							{
								int jukeboxId = mWorld->FindJukeboxID(testPos1);

								if(jukeboxId != -1)
								{
									if(mWorld->mJukeboxes[jukeboxId]->GetRecord() != -1)
									{
										mWorld->DropThis(mWorld->mJukeboxes[jukeboxId]->GetRecord(), 1, false, Vector3((int)testPos1.x+0.5f,(int)testPos1.y+0.5f,(int)testPos1.z+0.5f) );
									}

									delete mWorld->mJukeboxes[jukeboxId];
									mWorld->mJukeboxes.erase(mWorld->mJukeboxes.begin()+jukeboxId);
									mSoundMgr->StopDiskTrack();
								}
							}

							if(oldBlock == Spawner::getID())
							{
								int MonsterSpawnerId = mWorld->FindMonsterSpawnerID(testPos1);

								if(MonsterSpawnerId != -1)
								{
									delete mWorld->mMonsterSpawners[MonsterSpawnerId];
									mWorld->mMonsterSpawners.erase(mWorld->mMonsterSpawners.begin()+MonsterSpawnerId);
								}
							}

							if(oldBlock >= ItemFrame1::getID() && oldBlock <= ItemFrame4::getID()) mWorld->DestroyItemFrameEntity(testPos1);

							if(mWorld->invId[27+barPosition] >= 250 && mWorld->invId[27+barPosition] <= 275)
							{
								/*mWorld->invAm[27+barPosition] -= 1;*/ //infinito

								if(mWorld->invAm[27+barPosition] == 0)
								{
									Vector3 rayParticleDir = fppCam->m_vView - fppCam->m_vPosition;
									rayParticleDir.normalize();

									Vector3 particlePos = fppCam->m_vPosition + (rayParticleDir * 0.38f);

									if(mParticles.size() <= 52)
									{
										for(int k = 0; k <= 5; k++) // 5 particles
										{
											Particle* ToolPart = new Particle(mWorld,"item crack",Vector3(particlePos.x,particlePos.y-0.18f,particlePos.z));
											ToolPart->var1 = mWorld->invId[27+barPosition]-250;
											mParticles.push_back(ToolPart);
										}
									}

									mWorld->invId[27+barPosition] = -1;
									mWorld->invAm[27+barPosition] = -1;
									mWorld->invSt[27+barPosition] = 0;
									mSoundMgr->PlayBreakSound();
								}
							}

							if(oldBlock >= 57 && oldBlock <= 58) // if it is door
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x,testPos1.y-1,testPos1.z) = 0;
							}

							if(oldBlock >= 49 && oldBlock <= 56) // if it is door
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x,testPos1.y+1,testPos1.z) = 0;
							}

							if(oldBlock == BedBlock1::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x+1,testPos1.y,testPos1.z) = 0;
							}
							if(oldBlock == BedBlock2::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x-1,testPos1.y,testPos1.z) = 0;
							}
							if(oldBlock == BedBlock3::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z+1) = 0;
							}
							if(oldBlock == BedBlock4::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z-1) = 0;
							}

							if(oldBlock == BedBlock5::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x-1,testPos1.y,testPos1.z) = 0;
							}
							if(oldBlock == BedBlock6::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x+1,testPos1.y,testPos1.z) = 0;
							}
							if(oldBlock == BedBlock7::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z-1) = 0;
							}
							if(oldBlock == BedBlock8::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z+1) = 0;
							}

							if(oldBlock == 32) // if it is ice
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 4;
							}
							else
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;

								int upper_block = mWorld->GetBlock(testPos1.x,testPos1.y+1,testPos1.z);

								if(upper_block != 0)
								{
									if(mWorld->BlockSolid(testPos1.x,testPos1.y+1,testPos1.z) == false &&
									   !(upper_block >= Door1::getID() && upper_block <= Door8::getID()) &&
									   !(upper_block >= ItemFrame1::getID() && upper_block <= ItemFrame4::getID()) &&
									   upper_block != Torch::getID() &&
									   upper_block != WaterBlock::getID() &&
									   upper_block != Lava::getID() &&
									   upper_block != CaneBlock::getID() &&
									   !(upper_block >= Ladder1::getID() && upper_block <= Ladder4::getID()) &&
									   !(upper_block >= TrapdoorOpen1::getID() && upper_block <= TrapdoorClosed4::getID()) &&
									   upper_block != HellPortal::getID())
									{
										Vector3 testPos2 = Vector3(testPos1.x,testPos1.y+1,testPos1.z);

										mWorld->DropThis(mWorld->BlockLoot(testPos2.x,testPos2.y,testPos2.z),testPos2);
										mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 0;

										if(mWorld->ChunksEqual(testPos1,testPos2) == false)
										{
											int chunkTarget = mWorld->getChunkId(testPos2);
											mWorld->RebuildTransparentMeshChunk(chunkTarget);
										}
									}

									for(int checkY = testPos1.y+1; checkY <= testPos1.y+5; checkY++)
									{
										Vector3 testPos2 = Vector3(testPos1.x,checkY,testPos1.z);
										if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) != CaneBlock::getID() && mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) != CactusBlock::getID())
										{
											if(mWorld->ChunksEqual(testPos1, testPos2) == false)
											{
												int chunkTarget = mWorld->getChunkId(testPos2);
												mWorld->RebuildTransparentMeshChunk(chunkTarget);
											}
											break;
										}

										mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 0;
									}
								}
							}

							if(oldBlock == GlassBlock::getID() || oldBlock == IceBlock::getID())
							{
								mSoundMgr->PlayGlassSound();
							}
							else
							{
								mSoundMgr->PlayEndDigSound(mWorld->blockTypes[oldBlock].soundType);
							}

							if(mParticles.size() <= 52)
							{
								for(int k = 0; k <= 6; k++) // 9 particles
								{
									Particle* Smoke2 = new Particle(mWorld,"block crack",Vector3((int)testPos1.x + 0.5f + (-0.3+(rand() % 7)*0.1f),(int)testPos1.y + 0.5f + (-0.2+(rand() % 5)*0.1f),(int)testPos1.z + 0.5f + (-0.3+(rand() % 7)*0.1f)));
									Smoke2->var1 = oldBlock;
									mParticles.push_back(Smoke2);
								}
							}

							animGo = true;
							animDest = 0.0f;
							currentState = 0;

							//check if this block is a support for light block or ladder
							mWorld->CheckForTorchSupport(testPos1.x,testPos1.y,testPos1.z,0);
							mWorld->CheckForLadderSupport(testPos1.x,testPos1.y,testPos1.z);
							mWorld->DestroyAroundTrapdoors(testPos1.x,testPos1.y,testPos1.z);
							mWorld->DestroyAroundItemFrames(testPos1.x,testPos1.y,testPos1.z);

							int chunkTarget = mWorld->getChunkId(testPos1);

							if(chunkTarget != -1)
							{
								if(wasLight == true)
								{
									mWorld->RemoveLigtSourceAtPosition(testPos1.x,testPos1.y,testPos1.z,Torch::getID());
									mWorld->UpdateLightAreaIn(testPos1);

									mWorld->RebuildFullMeshChunk(chunkTarget);
									mWorld->rebuildNearestChunksForLight(chunkTarget,testPos1);
								}
								else
								{
									mWorld->initPutBlocksLight(testPos1.x, testPos1.y+1, testPos1.z);
									if(mWorld->GetLightLevel(testPos1.x-1,testPos1.y,testPos1.z) != 0 ||
									   mWorld->GetLightLevel(testPos1.x+1,testPos1.y,testPos1.z) != 0 ||
									   mWorld->GetLightLevel(testPos1.x,testPos1.y-1,testPos1.z) != 0 ||
									   mWorld->GetLightLevel(testPos1.x,testPos1.y+1,testPos1.z) != 0 ||
									   mWorld->GetLightLevel(testPos1.x,testPos1.y,testPos1.z-1) != 0 ||
									   mWorld->GetLightLevel(testPos1.x,testPos1.y,testPos1.z+1) != 0)
									{
										mWorld->UpdateLightAreaIn(testPos1);
									}

									mWorld->RebuildFullMeshChunk(chunkTarget);
									mWorld->rebuildNearestChunks(chunkTarget,testPos1);
								}
							}

							fppCam->needUpdate = true;
							testPos1 = Vector3(-1,-1,-1);
							startDt = false;
							chestId = -1;
							villageId = -1;
							villageProfession = 0;
							villageLvl = 0;
							villageRandom = 0;
							break;
						}
					}
				}
				// creativo
				if((keyPressed(InputHelper::Instance()->getButtonToAction(13)) || tryToDt == true))
				{
					tryToDt = false;

					//remove cube
					Vector3 rayDir = fppCam->m_vView - fppCam->m_vPosition;
					rayDir.normalize();

					//we are takin our positiona and view vector
					Vector3 testPos2;
					testPos2 = Vector3(-1,-1,-1);

					BoundingBox collider = mWorld->blockTypes[mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z)].collideBox;
					BoundingBox testBox = BoundingBox(testPos2.x+collider.min.x, testPos2.y+collider.min.y, testPos2.z+collider.min.z, testPos2.x+collider.max.x, testPos2.y+collider.max.y, testPos2.z+collider.max.z);

					//we are moving slowly to the target +=0.5
					for(float i = 0; i < 5.25f; i+=0.1f)
					{
						testPos2 = fppCam->m_vPosition + (rayDir * i);

						collider = mWorld->blockTypes[mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z)].collideBox;
						testBox = BoundingBox(floorf(testPos2.x)+0.5f+collider.min.x, floorf(testPos2.y)+0.5f+collider.min.y, floorf(testPos2.z)+0.5f+collider.min.z, floorf(testPos2.x)+0.5f+collider.max.x, floorf(testPos2.y)+0.5f+collider.max.y, floorf(testPos2.z)+0.5f+collider.max.z);

						bool kick = false;
						
						// zombie
						if(mWorld->mZombies.empty() == false)
						{
							for(int f = 0; f < mWorld->mZombies.size(); f++)
							{
								Zombie *TestZombie = mWorld->mZombies[f];
								if(TestZombie->DistanceToPlayer() < 3.16f && TestZombie->kicked == false && TestZombie->damaged == false)
								{
									if(TestZombie->bBox.contains(testPos2))
									{
										if(shield)
										{
											shield = false;
											recoidShield = 0.25f;
										}
										
										float damage = 1.0f;
										bool weapon = false;

										damage = mWorld->FetchDamagePoints(mWorld->invId[27+barPosition], weapon);

										if(weapon == true)
										{
											mWorld->invAm[27+barPosition] -= 1+rand()%2;

											if(mWorld->invAm[27+barPosition] <= 0)
											{
												mWorld->invId[27+barPosition] = -1;
												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = false;

												mSoundMgr->PlayBreakSound();
											}
										}
										TestZombie->TakeDamage(damage,0.75f,dt);
										if(TestZombie->HP <= 0)
										{
											if(mWorld->mainAchievements.MonsterHunter == 0) mGameMode->ArchievementsValues(0,6,0,0,mWorld);
										}
										kick = true;

										animGo = true;
										animDest = 0.0f;
										currentState = 0;

										changeY = -0.1f;
										anim[0] = 1;
										break;
									}
								}
							}
							if(kick == true)
							{
								return;
							}
						}
						
						// Wolf
						if(mWorld->mWolfs.empty() == false)
						{
							for(int f = 0; f < mWorld->mWolfs.size(); f++)
							{
								Wolf *TestWolf = mWorld->mWolfs[f];
								if(TestWolf->DistanceToPlayer() < 3.16f && TestWolf->kicked == false && TestWolf->damaged == false)
								{
									if(TestWolf->bBox.contains(testPos2))
									{
										if(shield)
										{
											shield = false;
											recoidShield = 0.25f;
										}
										
										float damage = 1.0f;
										bool weapon = false;

										damage = mWorld->FetchDamagePoints(mWorld->invId[27+barPosition], weapon);

										if(weapon == true)
										{
											mWorld->invAm[27+barPosition] -= 1+rand()%2;

											if(mWorld->invAm[27+barPosition] <= 0)
											{
												mWorld->invId[27+barPosition] = -1;
												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = false;

												mSoundMgr->PlayBreakSound();
											}
										}

										TestWolf->TakeDamage(damage,0.75f,dt);
										
										if(TestWolf->HP <= 0)
										{
											if(mWorld->mainAchievements.MonsterHunter == 0) mGameMode->ArchievementsValues(0,6,0,0,mWorld);
										}
										
										
										kick = true;

										animGo = true;
										animDest = 0.0f;
										currentState = 0;

										changeY = -0.1f;
										anim[0] = 1;
										break;
									}
								}
							}
							if(kick == true)
							{
								return;
							}
						}
						
						// pigman zombie
						if(mWorld->mPigmans.empty() == false)
						{
							for(int f = 0; f < mWorld->mPigmans.size(); f++)
							{
								Pigman *TestPigman = mWorld->mPigmans[f];
								if(TestPigman->DistanceToPlayer() < 3.16f && TestPigman->kicked == false && TestPigman->damaged == false)
								{
									if(TestPigman->bBox.contains(testPos2))
									{
										if(shield)
										{
											shield = false;
											recoidShield = 0.25f;
										}
										
										float damage = 1.0f;
										bool weapon = false;

										damage = mWorld->FetchDamagePoints(mWorld->invId[27+barPosition], weapon);

										if(weapon == true)
										{
											mWorld->invAm[27+barPosition] -= 1+rand()%2;

											if(mWorld->invAm[27+barPosition] <= 0)
											{
												mWorld->invId[27+barPosition] = -1;
												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = false;

												mSoundMgr->PlayBreakSound();
											}
										}

										TestPigman->TakeDamage(damage,0.75f,dt);
										
										if(TestPigman->HP <= 0)
										{
											if(mWorld->mainAchievements.MonsterHunter == 0) mGameMode->ArchievementsValues(0,6,0,0,mWorld);
										}
										
										
										kick = true;

										animGo = true;
										animDest = 0.0f;
										currentState = 0;

										changeY = -0.1f;
										anim[0] = 1;
										break;
									}
								}
							}
							if(kick == true)
							{
								return;
							}
						}
						
						// wither skeleton
						if(mWorld->mWitherSkeletons.empty() == false)
						{
							for(int f = 0; f < mWorld->mWitherSkeletons.size(); f++)
							{
								WitherSkeleton *TestWitherSkeleton = mWorld->mWitherSkeletons[f];
								if(TestWitherSkeleton->DistanceToPlayer() < 3.16f && TestWitherSkeleton->kicked == false && TestWitherSkeleton->damaged == false)
								{
									if(TestWitherSkeleton->bBox.contains(testPos2))
									{
										if(shield)
										{
											shield = false;
											recoidShield = 0.25f;
										}
										
										float damage = 1.0f;
										bool weapon = false;

										damage = mWorld->FetchDamagePoints(mWorld->invId[27+barPosition], weapon);

										if(weapon == true)
										{
											mWorld->invAm[27+barPosition] -= 1+rand()%2;

											if(mWorld->invAm[27+barPosition] <= 0)
											{
												mWorld->invId[27+barPosition] = -1;
												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = false;

												mSoundMgr->PlayBreakSound();
											}
										}

										TestWitherSkeleton->TakeDamage(damage,0.75f,dt);
										
										if(TestWitherSkeleton->HP <= 0)
										{
											if(mWorld->mainAchievements.MonsterHunter == 0) mGameMode->ArchievementsValues(0,6,0,0,mWorld);
										}
										
										kick = true;

										animGo = true;
										animDest = 0.0f;
										currentState = 0;

										changeY = -0.1f;
										anim[0] = 1;
										break;
									}
								}
							}
							if(kick == true)
							{
								return;
							}
						}
						
						// skeleton
						if(mWorld->mSkeletons.empty() == false)
						{
							for(int f = 0; f < mWorld->mSkeletons.size(); f++)
							{
								Skeleton *TestSkeleton = mWorld->mSkeletons[f];
								if(TestSkeleton->DistanceToPlayer() < 3.16f && TestSkeleton->kicked == false && TestSkeleton->damaged == false)
								{
									if(TestSkeleton->bBox.contains(testPos2))
									{
										if(shield){
											shield = false;
											recoidShield = 0.25f;
										}
										
										float damage = 1.0f;
										bool weapon = false;

										damage = mWorld->FetchDamagePoints(mWorld->invId[27+barPosition], weapon);

										if(weapon == true)
										{
											mWorld->invAm[27+barPosition] -= 1+rand()%2;

											if(mWorld->invAm[27+barPosition] <= 0)
											{
												mWorld->invId[27+barPosition] = -1;
												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = false;

												mSoundMgr->PlayBreakSound();
											}
										}

										TestSkeleton->TakeDamage(damage,0.75f,dt);
										if(TestSkeleton->HP <= 0)
										{
											if(mWorld->mainAchievements.MonsterHunter == 0) mGameMode->ArchievementsValues(0,6,0,0,mWorld);
										}
										kick = true;

										animGo = true;
										animDest = 0.0f;
										currentState = 0;

										changeY = -0.1f;
										anim[0] = 1;
										break;
									}
								}
							}
							if(kick == true)
							{
								return;
							}
						}
						
						// spider						
						if(mWorld->mSpiders.empty() == false)
						{
							for(int f = 0; f < mWorld->mSpiders.size(); f++)
							{
								Spider *TestSpider = mWorld->mSpiders[f];
								if(TestSpider->DistanceToPlayer() < 4.16f && TestSpider->kicked == false && TestSpider->damaged == false)
								{
									if(TestSpider->bBox.contains(testPos2))
									{
										if(shield)
										{
											shield = false;
											recoidShield = 0.25f;
										}
										
										float damage = 1.0f;
										bool weapon = false;

										damage = mWorld->FetchDamagePoints(mWorld->invId[27+barPosition], weapon);

										if(weapon == true)
										{
											mWorld->invAm[27+barPosition] -= 1+rand()%2;

											if(mWorld->invAm[27+barPosition] <= 0)
											{
												mWorld->invId[27+barPosition] = -1;
												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = false;

												mSoundMgr->PlayBreakSound();
											}
										}

										TestSpider->TakeDamage(damage,0.75f,dt);
										if(TestSpider->HP <= 0)
										{
											if(mWorld->mainAchievements.MonsterHunter == 0) mGameMode->ArchievementsValues(0,6,0,0,mWorld);
										}
										kick = true;

										animGo = true;
										animDest = 0.0f;
										currentState = 0;

										changeY = -0.1f;
										anim[0] = 1;
										break;
									}
								}
							}
							if(kick == true)
							{
								return;
							}
						}
						
						// spider cave					
						if(mWorld->mSpidercaves.empty() == false)
						{
							for(int f = 0; f < mWorld->mSpidercaves.size(); f++)
							{
								Spidercave *TestSpidercave = mWorld->mSpidercaves[f];
								if(TestSpidercave->DistanceToPlayer() < 4.16f && TestSpidercave->kicked == false && TestSpidercave->damaged == false)
								{
									if(TestSpidercave->bBox.contains(testPos2))
									{
										if(shield)
										{
											shield = false;
											recoidShield = 0.25f;
										}
										
										float damage = 1.0f;
										bool weapon = false;

										damage = mWorld->FetchDamagePoints(mWorld->invId[27+barPosition], weapon);

										if(weapon == true)
										{
											mWorld->invAm[27+barPosition] -= 1+rand()%2;

											if(mWorld->invAm[27+barPosition] <= 0)
											{
												mWorld->invId[27+barPosition] = -1;
												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = false;

												mSoundMgr->PlayBreakSound();
											}
										}

										TestSpidercave->TakeDamage(damage,0.75f,dt);
										if(TestSpidercave->HP <= 0)
										{
											if(mWorld->mainAchievements.MonsterHunter == 0) mGameMode->ArchievementsValues(0,6,0,0,mWorld);
										}
										kick = true;

										animGo = true;
										animDest = 0.0f;
										currentState = 0;

										changeY = -0.1f;
										anim[0] = 1;
										break;
									}
								}
							}
							if(kick == true)
							{
								return;
							}
						}

						// cows
						if(mWorld->mCows.empty() == false)
						{
							for(int f = 0; f < mWorld->mCows.size(); f++)
							{
								Cow *TestCow = mWorld->mCows[f];
								if(TestCow->DistanceToPlayer() < 2.75 && TestCow->kicked == false && TestCow->damaged == false)
								{
									if(TestCow->bBox.contains(testPos2))
									{
										if(shield)
										{
											shield = false;
											recoidShield = 0.25f;
										}
										
										float damage = 1.0f;
										bool weapon = false;

										damage = mWorld->FetchDamagePoints(mWorld->invId[27+barPosition], weapon);

										if(weapon == true)
										{
											mWorld->invAm[27+barPosition] -= 1+rand()%2;

											if(mWorld->invAm[27+barPosition] <= 0)
											{
												mWorld->invId[27+barPosition] = -1;
												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = false;

												mSoundMgr->PlayBreakSound();
											}
										}

										TestCow->TakeDamage(damage,0.7f,dt);
										kick = true;

										animGo = true;
										animDest = 0.0f;
										currentState = 0;
										break;
									}
								}
							}
							if(kick == true)
							{
								return;
							}
						}
						
						// chicken
						if(mWorld->mChickens.empty() == false)
						{
							for(int f = 0; f < mWorld->mChickens.size(); f++)
							{
								Chicken *TestChicken = mWorld->mChickens[f];
								if(TestChicken->DistanceToPlayer() < 2.75 && TestChicken->kicked == false && TestChicken->damaged == false)
								{
									if(TestChicken->bBox.contains(testPos2))
									{
										if(shield)
										{
											shield = false;
											recoidShield = 0.25f;
										}
										
										float damage = 1.0f;
										bool weapon = false;

										damage = mWorld->FetchDamagePoints(mWorld->invId[27+barPosition], weapon);

										if(weapon == true)
										{
											mWorld->invAm[27+barPosition] -= 1+rand()%2;

											if(mWorld->invAm[27+barPosition] <= 0)
											{
												mWorld->invId[27+barPosition] = -1;
												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = false;

												mSoundMgr->PlayBreakSound();
											}
										}

										TestChicken->TakeDamage(damage,0.7f,dt);
										kick = true;

										animGo = true;
										animDest = 0.0f;
										currentState = 0;
										break;
									}
								}
							}
							if(kick == true)
							{
								return;
							}
						}//end//
						
						// pig
						if(mWorld->mPigs.empty() == false)
						{
							for(int f = 0; f < mWorld->mPigs.size(); f++)
							{
								Pig *TestPig = mWorld->mPigs[f];
								if(TestPig->DistanceToPlayer() < 2.75 && TestPig->kicked == false && TestPig->damaged == false)
								{
									if(TestPig->bBox.contains(testPos2))
									{
										if(shield)
										{
											shield = false;
											recoidShield = 0.25f;
										}
										
										float damage = 1.0f;
										bool weapon = false;

										damage = mWorld->FetchDamagePoints(mWorld->invId[27+barPosition], weapon);

										if(weapon == true)
										{
											mWorld->invAm[27+barPosition] -= 1+rand()%2;

											if(mWorld->invAm[27+barPosition] <= 0)
											{
												mWorld->invId[27+barPosition] = -1;
												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = false;

												mSoundMgr->PlayBreakSound();
											}
										}

										TestPig->TakeDamage(damage,0.7f,dt);
										kick = true;

										animGo = true;
										animDest = 0.0f;
										currentState = 0;
										break;
									}
								}
							}
							if(kick == true)
							{
								return;
							}
						}
						
						// villager
						if(mWorld->mVillagers.empty() == false)
						{
							for(int f = 0; f < mWorld->mVillagers.size(); f++)
							{
								Villager *TestVillager = mWorld->mVillagers[f];
								if(TestVillager->DistanceToPlayer() < 2.75 && TestVillager->kicked == false && TestVillager->damaged == false)
								{
									if(TestVillager->bBox.contains(testPos2))
									{
										if(shield)
										{
											shield = false;
											recoidShield = 0.25f;
										}
										
										float damage = 1.0f;
										bool weapon = false;

										damage = mWorld->FetchDamagePoints(mWorld->invId[27+barPosition], weapon);

										if(weapon == true)
										{
											mWorld->invAm[27+barPosition] -= 1+rand()%2;

											if(mWorld->invAm[27+barPosition] <= 0)
											{
												mWorld->invId[27+barPosition] = -1;
												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = false;

												mSoundMgr->PlayBreakSound();
											}
										}

										TestVillager->TakeDamage(damage,0.7f,dt);
										if(TestVillager->randomVillager < 20) TestVillager->randomVillager += rand() % 3; 
										
										kick = true;

										animGo = true;
										animDest = 0.0f;
										currentState = 0;
										break;
									}
								}
							}
							if(kick == true)
							{
								return;
							}
						}

						// sheep
						if(mWorld->mSheeps.empty() == false)
						{
							for(int f = 0; f < mWorld->mSheeps.size(); f++)
							{
								Sheep *TestSheep = mWorld->mSheeps[f];
								if(TestSheep->DistanceToPlayer() < 2.75 && TestSheep->kicked == false && TestSheep->damaged == false)
								{
									if(TestSheep->bBox.contains(testPos2))
									{
										if(shield)
										{
											shield = false;
											recoidShield = 0.25f;
										}
										
										float damage = 1.0f;
										bool weapon = false;

										damage = mWorld->FetchDamagePoints(mWorld->invId[27+barPosition], weapon);

										if(weapon == true)
										{
											mWorld->invAm[27+barPosition] -= 1+rand()%2;

											if(mWorld->invAm[27+barPosition] <= 0)
											{
												mWorld->invId[27+barPosition] = -1;
												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = false;

												mSoundMgr->PlayBreakSound();
											}
										}

										TestSheep->TakeDamage(damage,0.7f,dt);
										kick = true;

										animGo = true;
										animDest = 0.0f;
										currentState = 0;
										break;
									}
								}
							}
							if(kick == true)
							{
								return;
							}
						}

						// creeper
						if(mWorld->mCreepers.empty() == false)
						{
							for(int f = 0; f < mWorld->mCreepers.size(); f++)
							{
								Creeper *TestCreeper = mWorld->mCreepers[f];
								if(mWorld->FastDistance2d(abs(TestCreeper->position.x-playerPosition.x)*10,abs(TestCreeper->position.z-playerPosition.z)*10)/10.0f + abs(TestCreeper->position.y-(playerPosition.y-0.7))/2.0f < 2.18 && TestCreeper->kicked == false && TestCreeper->damaged == false)
								{
									if(TestCreeper->bBox.contains(testPos2))
									{
										if(shield)
										{
											shield = false;
											recoidShield = 0.25f;
										}
										
										float damage = 1.0f;
										bool weapon = false;

										damage = mWorld->FetchDamagePoints(mWorld->invId[27+barPosition], weapon);

										if(weapon == true)
										{
											mWorld->invAm[27+barPosition] -= 1+rand()%2;

											if(mWorld->invAm[27+barPosition] <= 0)
											{
												mWorld->invId[27+barPosition] = -1;
												mWorld->invAm[27+barPosition] = -1;
												mWorld->invSt[27+barPosition] = false;

												mSoundMgr->PlayBreakSound();
											}
										}

										TestCreeper->TakeDamage(damage,0.7f,dt);
										if(TestCreeper->HP <= 0)
										{
											if(mWorld->mainAchievements.MonsterHunter == 0) mGameMode->ArchievementsValues(0,6,0,0,mWorld);
										}
										kick = true;

										animGo = true;
										animDest = 0.0f;
										currentState = 0;
										break;
									}
								}
							}
							if(kick == true)
							{
								return;
							}
						}

						//check if we touch something
						if(mWorld->BlockEditable(testPos2.x,testPos2.y,testPos2.z) && testBox.contains(testPos2) && mWorld->gameModeWorld != 1)
						{
							if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == NoteBlock::getID())
							{
								unsigned int noteBlockId = mWorld->FindNoteBlockID(testPos2);

								if(noteBlockId != -1)
								{
									if(mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) == 0)
									{
										NoteBlockEntity* TestNoteBlock = mWorld->mNoteBlocks[noteBlockId];
										mSoundMgr->PlayNoteSound(!(mWorld->BlockMaterial(testPos2.x,testPos2.y-1,testPos2.z) == 1 || mWorld->BlockMaterial(testPos2.x,testPos2.y-1,testPos2.z) == 8),TestNoteBlock->GetPitch());

										float red, blue, green;
										if(TestNoteBlock->GetNote() <= 12)
										{
											blue = 1.0 - (TestNoteBlock->GetNote()/12.0f);
											green = (TestNoteBlock->GetNote()/12.0f);
											red = 0.0f;
										}
										else
										{
											blue = 0.0f;
											green = 1.0 - ((TestNoteBlock->GetNote()-12)/12.0f);
											red = ((TestNoteBlock->GetNote()-12)/12.0f);
										}
										Particle* Note = new Particle(mWorld,"note",Vector3((int)testPos2.x+0.5f,(int)testPos2.y+1.1f,(int)testPos2.z+0.5f));
										Note->SetColor(Vector3(red,green,blue));
										mParticles.push_back(Note);
									}
								}
							}
							
							if(startDt == false)
							{
								testPos1.x  = testPos2.x;
								testPos1.y  = testPos2.y;
								testPos1.z  = testPos2.z;
								dET = 1.0f;
								dT = 0.0f;
								switch(mWorld->BlockMaterial(testPos1.x,testPos1.y,testPos1.z)) // fetch time of block breaking
								{
									case 1: // wood
									if(mWorld->invId[27+barPosition] == WoodenAxe::getID()) // wooden axe
									{
										dET = 1.5f; // 1.5 СЃРµРєСѓРЅРґС‹
									}
									else if(mWorld->invId[27+barPosition] == StoneAxe::getID()) // stone axe
									{
										dET = 0.75f;
									}
									else if(mWorld->invId[27+barPosition] == IronAxe::getID()) // iron axe
									{
										dET = 0.5f;
									}
									else if(mWorld->invId[27+barPosition] == DiamondAxe::getID()) // diamond axe
									{
										dET = 0.4f;
									}
									else if(mWorld->invId[27+barPosition] == GoldenAxe::getID()) // golden axe
									{
										dET = 0.25f;
									}
									else
									{
										dET = 3.0f;
									}
									break;

									case 2: // stone
									if(mWorld->invId[27+barPosition] == WoodenPickaxe::getID())
									{
										dET = 1.5f;
									}
									else if(mWorld->invId[27+barPosition] == StonePickaxe::getID())
									{
										dET = 0.75f;
									}
									else if(mWorld->invId[27+barPosition] == IronPickaxe::getID())
									{
										dET = 0.5f;
									}
									else if(mWorld->invId[27+barPosition] == DiamondPickaxe::getID())
									{
										dET = 0.4f;
									}
									else if(mWorld->invId[27+barPosition] == GoldenPickaxe::getID())
									{
										dET = 0.25f;
									}
									else
									{
										dET = 10.0f;
									}
									break;

									case 3: // soil
									if(mWorld->invId[27+barPosition] == 260)
									{
										dET = 0.45f;
									}
									else if(mWorld->invId[27+barPosition] == 261)
									{
										dET = 0.25f;
									}
									else if(mWorld->invId[27+barPosition] == 262)
									{
										dET = 0.15f;
									}
									else if(mWorld->invId[27+barPosition] == 263)
									{
										dET = 0.15f;
									}
									else if(mWorld->invId[27+barPosition] == 264)
									{
										dET = 0.1f;
									}
									else
									{
										dET = 0.9f;
									}
									break;

									case 4: // leaves
									if(mWorld->invId[27+barPosition] == 275)
									{
										dET = 0.1f;
									}
									else
									{
										dET = 0.4f;
									}
									break;

									case 5: // obsidian
									if(mWorld->invId[27+barPosition] == 253)
									{
										dET = 15.0f;
									}
									else
									{
										dET = 250.0f;
									}
									break;

									case 6: // bedrock
									dET = 36000.0f;
									break;

									break;

									case 7: // ores
									if(mWorld->invId[27+barPosition] == 250)
									{
										dET = 2.25f;
									}
									else if(mWorld->invId[27+barPosition] == 251)
									{
										dET = 1.15f;
									}
									else if(mWorld->invId[27+barPosition] == 252)
									{
										dET = 0.75f;
									}
									else if(mWorld->invId[27+barPosition] == 253)
									{
										dET = 0.6f;
									}
									else if(mWorld->invId[27+barPosition] == 254)
									{
										dET = 0.4f;
									}
									else
									{
										dET = 15.0f;
									}
									break;

									case 8: // strong wood
									if(mWorld->invId[27+barPosition] == 265) // wooden axe
									{
										dET = 1.9f; //
									}
									else if(mWorld->invId[27+barPosition] == 266) // stone axe
									{
										dET = 0.95f;
									}
									else if(mWorld->invId[27+barPosition] == 267) // iron axe
									{
										dET = 0.65f;
									}
									else if(mWorld->invId[27+barPosition] == 268) // diamond axe
									{
										dET = 0.5f;
									}
									else if(mWorld->invId[27+barPosition] == 269) // golden axe
									{
										dET = 0.35f;
									}
									else
									{
										dET = 3.75f;
									}
									break;

									case 9: // strong stone
									if(mWorld->invId[27+barPosition] == 250)
									{
										dET = 2.65f;
									}
									else if(mWorld->invId[27+barPosition] == 251)
									{
										dET = 1.35f;
									}
									else if(mWorld->invId[27+barPosition] == 252)
									{
										dET = 0.9f;
									}
									else if(mWorld->invId[27+barPosition] == 253)
									{
										dET = 0.7f;
									}
									else if(mWorld->invId[27+barPosition] == 254)
									{
										dET = 0.45f;
									}
									else
									{
										dET = 17.5f;
									}
									break;

									case 10: // metal
									if(mWorld->invId[27+barPosition] == 250)
									{
										dET = 25.0f;
									}
									else if(mWorld->invId[27+barPosition] == 251)
									{
										dET = 10.0f;
									}
									else if(mWorld->invId[27+barPosition] == 252)
									{
										dET = 5.0f;
									}
									else if(mWorld->invId[27+barPosition] == 253)
									{
										dET = 2.5f;
									}
									else if(mWorld->invId[27+barPosition] == 254)
									{
										dET = 25.0f;
									}
									else
									{
										dET = 25.0f;
									}
									break;

									default:
									dET = 0.3f;
									break;

								}
								dT = 0;
								startDt = true;
							}
							break;
						}
					}
				}

				// remove cube	// creativo
				if(keyHold(InputHelper::Instance()->getButtonToAction(13)) && mWorld->gameModeWorld != 1)
				{
					if(startDt == true)
					{
						if(animGo == false)
						{
							mSoundMgr->PlayDigSound(mWorld->BlockSoundAtPos(Vector3(testPos1.x,testPos1.y,testPos1.z)));

							animGo = true;
							animDest = 0.0f;
							currentState = 0;
						}

						if(headInWater) // slow removing under water
						{
							dT < dET ? dT += dt*0.2 : dT = 0;
						}
						else
						{
							dT < dET ? dT += dt : dT = 0;
						}

						dStd = ceilf(dT*(100/(float)dET))/10.0f;
						//remove block
						if(dT >= dET)
						{
							bool wasLight = false;
							int oldBlock = 0;
							oldBlock = mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z);
							if(oldBlock != -1)//if it's light block
							{
								if(mWorld->LightSourceBlock(oldBlock))
								{
									wasLight = true;
								}
							}

							if(oldBlock >= ChestBlock1::getID() && oldBlock <= ChestBlock4::getID()) // chest destroying
							{
								chestId = FindChestId(testPos1.x,testPos1.y,testPos1.z);
								if(chestId != -1)
								{
									// drop all items in chest
									Chest* TestChest = mWorld->mChests[chestId];
									for(int i = 0; i <= 27; i++)
									{
										if(TestChest->chestSlotId[i] > 0)
										{
											Vector3 dropVelocity = Vector3(0,0,0);

											dropVelocity.x = (-15+rand()%30)*0.1f;
											dropVelocity.y = 3.0f;
											dropVelocity.z = (-15+rand()%30)*0.1f;

											if(TestChest->chestSlotAm[i] > 0)
											{
												mWorld->DropThisNoAlign(TestChest->chestSlotId[i],TestChest->chestSlotAm[i],TestChest->chestSlotSt[i],Vector3(testPos1.x+0.5f,testPos1.y+0.25f,testPos1.z+0.5f),dropVelocity);

												TestChest->chestSlotAm[i] = -1;
												TestChest->chestSlotSt[i] = 0;
												TestChest->chestSlotId[i] = -1;
											}
										}
									}

									delete mWorld->mChests[chestId];
									mWorld->mChests.erase(mWorld->mChests.begin()+chestId);
								}
							}

							if(oldBlock == NoteBlock::getID())
							{
								int noteBlockId = mWorld->FindNoteBlockID(testPos1);

								if(noteBlockId != -1)
								{
									delete mWorld->mNoteBlocks[noteBlockId];
									mWorld->mNoteBlocks.erase(mWorld->mNoteBlocks.begin()+noteBlockId);
								}
							}

							if(oldBlock == JukeBox::getID())
							{
								int jukeboxId = mWorld->FindJukeboxID(testPos1);

								if(jukeboxId != -1)
								{
									if(mWorld->mJukeboxes[jukeboxId]->GetRecord() != -1)
									{
										mWorld->DropThis(mWorld->mJukeboxes[jukeboxId]->GetRecord(), 1, false, Vector3((int)testPos1.x+0.5f,(int)testPos1.y+0.5f,(int)testPos1.z+0.5f) );
									}

									delete mWorld->mJukeboxes[jukeboxId];
									mWorld->mJukeboxes.erase(mWorld->mJukeboxes.begin()+jukeboxId);
									mSoundMgr->StopDiskTrack();
								}
							}

							if(oldBlock == Spawner::getID())
							{
								int MonsterSpawnerId = mWorld->FindMonsterSpawnerID(testPos1);

								if(MonsterSpawnerId != -1)
								{
									ExperienceSystem(35,40);
									delete mWorld->mMonsterSpawners[MonsterSpawnerId];
									mWorld->mMonsterSpawners.erase(mWorld->mMonsterSpawners.begin()+MonsterSpawnerId);
								}
							}

							if(oldBlock >= ItemFrame1::getID() && oldBlock <= ItemFrame4::getID())
							{
								mWorld->DestroyItemFrameEntity(testPos1);
							}

							if(oldBlock == FurnaceOff::getID() || oldBlock == FurnaceOn::getID()) // furnace destroying
							{
								furnaceId = FindFurnaceId(testPos1.x,testPos1.y,testPos1.z);
								if(furnaceId != -1)
								{
									// drop all items in furnace
									Furnace* TestFurnace = mWorld->mFurnaces[furnaceId];
									for(int i = 0; i <= 2; i++)
									{
										if(TestFurnace->furnaceSlotId[i] > 0)
										{
											Vector3 dropVelocity = Vector3(0,0,0);

											dropVelocity.x = (-15+rand()%30)*0.1f;
											dropVelocity.y = 3.0f;
											dropVelocity.z = (-15+rand()%30)*0.1f;

											if(TestFurnace->furnaceSlotAm[i] > 0)
											{
												mWorld->DropThisNoAlign(TestFurnace->furnaceSlotId[i],TestFurnace->furnaceSlotAm[i],TestFurnace->furnaceSlotSt[i],Vector3(testPos1.x+0.5f,testPos1.y+0.25f,testPos1.z+0.5f),dropVelocity);

												TestFurnace->furnaceSlotAm[i] = -1;
												TestFurnace->furnaceSlotSt[i] = 0;
												TestFurnace->furnaceSlotId[i] = -1;
											}
										}
									}
									delete mWorld->mFurnaces[furnaceId];
									mWorld->mFurnaces.erase(mWorld->mFurnaces.begin()+furnaceId);
								}
							}

							if(oldBlock >= 57 && oldBlock <= 58)
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x,testPos1.y-1,testPos1.z) = 0;
							}

							if(oldBlock >= 49 && oldBlock <= 56)
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x,testPos1.y+1,testPos1.z) = 0;
							}

							if(oldBlock == BedBlock1::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x+1,testPos1.y,testPos1.z) = 0;
							}
							if(oldBlock == BedBlock2::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x-1,testPos1.y,testPos1.z) = 0;
							}
							if(oldBlock == BedBlock3::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z+1) = 0;
							}
							if(oldBlock == BedBlock4::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z-1) = 0;
							}

							if(oldBlock == BedBlock5::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x-1,testPos1.y,testPos1.z) = 0;
							}
							if(oldBlock == BedBlock6::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x+1,testPos1.y,testPos1.z) = 0;
							}
							if(oldBlock == BedBlock7::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z-1) = 0;
							}
							if(oldBlock == BedBlock8::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z+1) = 0;
							}

							if(oldBlock == IceBlock::getID())
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = WaterBlock::getID();
							}
							else
							{
								mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;

								int upper_block = mWorld->GetBlock(testPos1.x,testPos1.y+1,testPos1.z);

								if(upper_block != 0)
								{
									if(mWorld->BlockSolid(testPos1.x,testPos1.y+1,testPos1.z) == false &&
									   !(upper_block >= Door1::getID() && upper_block <= Door8::getID()) &&
									   !(upper_block >= ItemFrame1::getID() && upper_block <= ItemFrame4::getID()) &&
									   upper_block != Torch::getID() &&
									   upper_block != WaterBlock::getID() &&
									   upper_block != Lava::getID() &&
									   upper_block != CaneBlock::getID() &&
									   !(upper_block >= Ladder1::getID() && upper_block <= Ladder4::getID()) &&
									   !(upper_block >= TrapdoorOpen1::getID() && upper_block <= TrapdoorClosed4::getID()) &&
									   upper_block != HellPortal::getID())
									{
										Vector3 testPos2 = Vector3(testPos1.x,testPos1.y+1,testPos1.z);

										mWorld->DropThis(mWorld->BlockLoot(testPos2.x,testPos2.y,testPos2.z),testPos2);
										mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 0;

										if(mWorld->ChunksEqual(testPos1,testPos2) == false)
										{
											int chunkTarget = mWorld->getChunkId(testPos2);
											mWorld->RebuildTransparentMeshChunk(chunkTarget);
										}
									}

									for(int checkY = testPos1.y+1; checkY <= testPos1.y+5; checkY++)
									{
										Vector3 testPos2 = Vector3(testPos1.x,checkY,testPos1.z);
										if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) != CaneBlock::getID() && mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) != CactusBlock::getID())
										{
											if(mWorld->ChunksEqual(testPos1, testPos2) == false)
											{
												int chunkTarget = mWorld->getChunkId(testPos2);
												mWorld->RebuildTransparentMeshChunk(chunkTarget);
											}
											break;
										}

										if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == CaneBlock::getID())
										{
											mWorld->DropThis(CaneItem::getID(),testPos2);
										}
										if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == CactusBlock::getID())
										{
											mWorld->DropThis(CactusBlock::getID(),testPos2);
										}
										mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 0;
									}
								}
							}

							if(mWorld->invId[27+barPosition] >= 250 && mWorld->invId[27+barPosition] <= 275) // tool breaking
							{
								mWorld->invAm[27+barPosition] -= 1;
								if(mWorld->invAm[27+barPosition] <= 0)
								{
									Vector3 rayParticleDir = fppCam->m_vView - fppCam->m_vPosition;
									rayParticleDir.normalize();

									Vector3 particlePos = fppCam->m_vPosition + (rayParticleDir * 0.38f);

									if(mParticles.size() <= 52)
									{
										for(int k = 0; k <= 5; k++) // 5 particles
										{
											Particle* ToolPart = new Particle(mWorld,"item crack",Vector3(particlePos.x,particlePos.y-0.18f,particlePos.z));
											ToolPart->var1 = mWorld->invId[27+barPosition]-250;
											mParticles.push_back(ToolPart);
										}
									}

									mWorld->invId[27+barPosition] = -1;
									mWorld->invAm[27+barPosition] = -1;
									mWorld->invSt[27+barPosition] = 0;
									mSoundMgr->PlayBreakSound();
								}
							}

							switch(oldBlock)
							{
							case 9: // oak leaves
								if(mWorld->invId[27+barPosition] != 275)
								{
									if ((rand() % 50) == 0)
									{
										mWorld->DropThis(284,testPos1);
									}

									if ((rand() % 15) == 0)
									{
										mWorld->DropThis(296,testPos1);
									}
								}
								else
								{
									mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
								}
							break;

							case 37: // spruce leaves
								if(mWorld->invId[27+barPosition] != 275)
								{
									if (rand() % 10 == 1)
									{
										mWorld->DropThis(309,testPos1);
									}
								}
								else
								{
									mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
								}
							break;

							case 38: // birch leaves
								if(mWorld->invId[27+barPosition] != 275)
								{
									if (rand() % 16 == 1)
									{
										mWorld->DropThis(310,testPos1);
									}
								}
								else
								{
									mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
								}
							break;

							case 139: // wheat
								mWorld->DropThis(Wheat::getID(),testPos1);
								mWorld->DropThis(WheatSeeds::getID(),1+rand()%2,testPos1);
							break;

							case 93: // snow cover
								if(mWorld->invId[27+barPosition] >= 260 && mWorld->invId[27+barPosition] <= 264)
								{
									mWorld->DropThis(299,4,testPos1);
								}
							break;

							// ore digging with special tools
							case 3: // stone
								if(mWorld->invId[27+barPosition] >= WoodenPickaxe::getID() && mWorld->invId[27+barPosition] <= GoldenPickaxe::getID())
								{
									//ExperienceSystem(6,8);
									mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
								}
							break;

							case 36: // cobblestone
								if(mWorld->invId[27+barPosition] >= WoodenPickaxe::getID() && mWorld->invId[27+barPosition] <= GoldenPickaxe::getID())
								{
									mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
								}
							break;

							case 41: // iron ore
								if(mWorld->invId[27+barPosition] >= StonePickaxe::getID() && mWorld->invId[27+barPosition] <= GoldenPickaxe::getID())
								{
									mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
								}
							break;

							case 42: // coal ore
								if(mWorld->invId[27+barPosition] >= WoodenPickaxe::getID() && mWorld->invId[27+barPosition] <= GoldenPickaxe::getID())
								{
									if(rand() % 10 < 8)ExperienceSystem(6,8);
									mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
								}
							break;
						
							case 43: // diamond ore
								if(mWorld->invId[27+barPosition] >= IronPickaxe::getID() && mWorld->invId[27+barPosition] <= GoldenPickaxe::getID())
								{
									ExperienceSystem(13,17);						
									mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
								}
								
							break;

							case 44: // redstone ore
								if(mWorld->invId[27+barPosition] >= IronPickaxe::getID() && mWorld->invId[27+barPosition] <= GoldenPickaxe::getID())
								{
									ExperienceSystem(8,13);	
									mWorld->DropThis(mWorld->LootBlock(oldBlock),3,testPos1);
									mWorld->DropThis(mWorld->LootBlock(oldBlock),1+rand()%2,testPos1);
								}
							break;
							
							case 226: // quartz ore
								if(mWorld->invId[27+barPosition] >= IronPickaxe::getID() && mWorld->invId[27+barPosition] <= GoldenPickaxe::getID())
								{
									ExperienceSystem(5,8);	
									mWorld->DropThis(mWorld->LootBlock(oldBlock),1+rand()%1,testPos1);
								}
							break;

							case 45: // lapis ore
								if(mWorld->invId[27+barPosition] >= StonePickaxe::getID() && mWorld->invId[27+barPosition] <= GoldenPickaxe::getID())
								{
									ExperienceSystem(8,11);	
									mWorld->DropThis(mWorld->LootBlock(oldBlock),3,testPos1);
									mWorld->DropThis(mWorld->LootBlock(oldBlock),1+rand()%5,testPos1);
								}
							break;

							case 46: // obsidian
								if(mWorld->invId[27+barPosition] == DiamondPickaxe::getID() )
								{
									mWorld->DropThis(mWorld->LootBlock(oldBlock),3,testPos1);
									mWorld->DropThis(mWorld->LootBlock(oldBlock),1+rand()%5,testPos1);
								}
							break;

							case 5: // golden ore
								if(mWorld->invId[27+barPosition] >= IronPickaxe::getID() && mWorld->invId[27+barPosition] <= GoldenPickaxe::getID())
								{
									mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
								}
							break;
							
							case 225: // glowstone block
								mWorld->DropThis(mWorld->LootBlock(oldBlock),1+rand()%4,testPos1);
							break;
							//

							case 99: // clay block
								mWorld->DropThis(mWorld->LootBlock(oldBlock),2,testPos1);
								mWorld->DropThis(mWorld->LootBlock(oldBlock),2,testPos1);
							break;

							case 81: // melon block
								mWorld->DropThis(mWorld->LootBlock(oldBlock),2,testPos1);

								mWorld->DropThis(mWorld->LootBlock(oldBlock),1+rand()%5,testPos1);
							break;

							case 133: // final melon plant
								mWorld->DropThis(MelonSeeds::getID(),1+rand()%3,testPos1);
							break;

							case 181: // final pumpkin plant
								mWorld->DropThis(PumpkinSeeds::getID(),1+rand()%3,testPos1);
							break;

							case 185: // matrue potato
								mWorld->DropThis(Potato::getID(),1,testPos1);
								mWorld->DropThis(Potato::getID(),rand() % 4,testPos1);

								if(rand() % 100 <= 1)
								{
									mWorld->DropThis(PoisonedPotato::getID(),1,testPos1);
								}
							break;

							case 189: // matrue carrot
								mWorld->DropThis(Carrot::getID(),1,testPos1);
								mWorld->DropThis(Carrot::getID(),rand() % 4,testPos1);
							break;

							case 33: // cane
								mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
								for(int checkY = testPos1.y+1; checkY <= testPos1.y+5; checkY++)
								{
									Vector3 testPos2 = Vector3(testPos1.x,checkY,testPos1.z);
									if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) != 33)
									{
										if(mWorld->ChunksEqual(testPos1, testPos2) == false)
										{
											int chunkTarget = mWorld->getChunkId(testPos2);
											mWorld->RebuildTransparentMeshChunk(chunkTarget);
										}
										break;
									}

									mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 0;
									mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos2);
								}
							break;

							case 116: // tall grass
							if (rand() % 8 == 1)
							{
								mWorld->DropThis(WheatSeeds::getID(),testPos1);
							}
							break;

							case 113: // gravel
							if (rand() % 12 == 0)
							{
								mWorld->DropThis(Flint::getID(),testPos1);
							}
							else
							{
								mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
							}
							break;

							default: // all other blocks
								mWorld->DropThis(mWorld->LootBlock(oldBlock),testPos1);
							break;
							}

							if(oldBlock == GlassBlock::getID() || oldBlock == IceBlock::getID())
							{
								mSoundMgr->PlayGlassSound();
							}
							else
							{
								if(oldBlock >= 0 && oldBlock < mWorld->blockTypes.size())
								{
									mSoundMgr->PlayEndDigSound(mWorld->blockTypes[oldBlock].soundType);
								}
							}

							if(mParticles.size() <= 52 && oldBlock >= 0)
							{
								for(int k = 0; k <= 8; k++) // 9 particles
								{
									Particle* Smoke2 = new Particle(mWorld,"block crack",Vector3((int)testPos1.x + 0.5f + (-0.3+(rand() % 7)*0.1f),(int)testPos1.y + 0.5f + (-0.2+(rand() % 5)*0.1f),(int)testPos1.z + 0.5f + (-0.3+(rand() % 7)*0.1f)));
									Smoke2->var1 = oldBlock;
									mParticles.push_back(Smoke2);
								}
							}
							
							mGameMode->ArchievementsValues(oldBlock,0,0,0,mWorld);

							//check if this block is a support for light block or ladder
							mWorld->CheckForTorchSupport(testPos1.x,testPos1.y,testPos1.z,mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z));
							mWorld->CheckForLadderSupport(testPos1.x,testPos1.y,testPos1.z);
							mWorld->DestroyAroundTrapdoors(testPos1.x,testPos1.y,testPos1.z);
							mWorld->DestroyAroundItemFrames(testPos1.x,testPos1.y,testPos1.z);

							int chunkTarget = mWorld->getChunkId(testPos1);

							if(chunkTarget != -1)
							{
								if(wasLight == true)
								{
									mWorld->RemoveLigtSourceAtPosition(testPos1.x,testPos1.y,testPos1.z,Torch::getID());
									mWorld->UpdateLightAreaIn(testPos1);

									mWorld->RebuildFullMeshChunk(chunkTarget);
									mWorld->rebuildNearestChunksForLight(chunkTarget,testPos1);
								}
								else
								{
									mWorld->initPutBlocksLight(testPos1.x, testPos1.y+2, testPos1.z);
									
									if(mWorld->GetLightLevel(testPos1.x-1,testPos1.y,testPos1.z) != 0 ||
									   mWorld->GetLightLevel(testPos1.x+1,testPos1.y,testPos1.z) != 0 ||
									   mWorld->GetLightLevel(testPos1.x,testPos1.y-1,testPos1.z) != 0 ||
									   mWorld->GetLightLevel(testPos1.x,testPos1.y+1,testPos1.z) != 0 ||
									   mWorld->GetLightLevel(testPos1.x,testPos1.y,testPos1.z-1) != 0 ||
									   mWorld->GetLightLevel(testPos1.x,testPos1.y,testPos1.z+1) != 0)
									{
										mWorld->UpdateLightAreaIn(testPos1);
									}

									mWorld->RebuildFullMeshChunk(chunkTarget);
									mWorld->rebuildNearestChunks(chunkTarget,testPos1);
								}
							}

							if(mWorld->HG > 0.01)
							{
								if(mWorld->gameModeWorld != 1) mWorld->HG -= (1.0f)/64.0f;
							}

							fppCam->needUpdate = true;
							testPos1 = Vector3(-1,-1,-1);
							startDt = false;
							tryToDt = true;
							dT = 0;
							dET = 0;
							chestId = -1;
							dStd = -1;
						}
					}
				}
				else
				{
					if (startDt != false)
					{
						dT = 0;
						dStd = -1;
						startDt = false;
						chestId = -1;
					}

				}
            }

            /// INVENTORY
            if(invEn == true || craft3xEn == true || chestEn == true || furnaceEn == true || villEn == true)
            {
				if(mWorld->mainAchievements.TakingInventory == 0)
				{
					mGameMode->ArchievementsValues(0,1,0,0,mWorld);
				}
				
				// comida
				if(eatingTick > 0.1)
				{
					canEatAgain = true;
					eatingTick = 0.0f;
					eatSoundTimer = 0.5f;
				}
				
                //Craft item
                if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
                {
					if(craft3xEn && !upEn && invEn)
					{
						//inventory sprite

						TextureHelper::Instance()->LoadInventory(0);
						
						invSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::inv), true);//200
						invSprite->SetPosition(240,136);

						selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));
								
						craft3xEn = false;
						recipesManager.craft2x2 = false;
						
						PagCraft = 0;
						IndexCraft = 0;
						SlotEnCraft = 0;
						
						for(int i = 0; i < 5; i++)
						{
							IDDrawRe[i] = 0;
						}
						
						tickReChange = 0.0f;
						recipesManager.craft2x2 = false;
						recipesManager.CleanUp();

					}
					else
					{

						if(craft3xEn == true)
						{
							PagCraft = 0;
							IndexCraft = 0;
							SlotEnCraft = 0;
							
							for(int i = 0; i < 5; i++)
							{
								IDDrawRe[i] = 0;
							}
							
							tickReChange = 0.0f;
							recipesManager.craft2x2 = false;
							recipesManager.CleanUp();
						}

						if(upEn == true || mWorld->gameModeWorld == 1)
						{
							invXPosition = 0;
							invYPosition = 0;
						}
						
						if(villEn == true)
						{
							tradesManager.CleanUp();
							
							Villager* TestVillager = mWorld->mVillagers[villageId];
							
							TestVillager->tradder = false;
							TestVillager->LevelProfession = villageLvl;
							SlotEnVillager = 0;
						}
						
						selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));

	
						if((mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2) && invEn == true && craft3xEn == false)  
						{
							delete invSprite;
						}
						else if((mWorld->gameModeWorld == 1) && invEn == true) 
						{
							delete invSpriteCreative;
						}
						else if(chestEn == true) 
						{
							delete chtSprite;
						}
						else if(craft3xEn == true) 
						{
							delete crtSprite;
						}
						else if(furnaceEn == true) 
						{
							delete furSprite;
						}
						else if(villEn == true)
						{
							delete invVillage;
						}
						
						TextureHelper::Instance()->UnLoadInventory();
		
						invEn = false;
						villEn = false;
						craft3xEn = false;
						furnaceEn = false;
						
						if(chestEn == true)
						{
							mSoundMgr->PlayChestClosedSound();
						}
						
						chestEn = false;
						upEn = false;
						slot2En = false;
						furnaceEn = false;
						chestId = -1;
						villageId = -1;
						villageProfession = 0;
						villageLvl = 0;
						villageRandom = 0;
						armorEn = false;
						
						if(mWorld->mId != -1)
						{
							Vector3 dropVelocity = Vector3(0,0,0);

							dropVelocity.x = (-15+rand()%30)*0.1f;
							dropVelocity.y = 3.0f;
							dropVelocity.z = (-15+rand()%30)*0.1f;

							mWorld->DropThisNoAlign(mWorld->mId,mWorld->mAm,mWorld->mSt,Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y-0.25f,fppCam->m_vPosition.z),dropVelocity);

							mWorld->mId = -1;
							mWorld->mAm = 0;
							mWorld->mSt= -1;
						}

						UseChest = 0;
						UseFurnace = 0;

						mWorld->haveCompass = mWorld->HaveItemInBarSlots(Compass::getID());
					}
                    return;
                }

				if(mSystemMgr->KeyPressed(PSP_CTRL_TRIANGLE)) // if you press R
				{
					if(craft3xEn == true && mWorld->mId == -1 && upEn == false)
					{
						upEn = 1;
					}
					else if(craft3xEn == true && upEn == true)
					{
						upEn = 0;
					}
					
					if(villEn == true)
					{
						//Comprobar Tradeo
						int ItemRe = -1;
						int IgredientAm[2];
						bool TradeSpace = false;
						
						IgredientAm[0] = 0;
						IgredientAm[1] = 0;
						IgredientAm[2] = 0;
						
						// Buscar si el ítem ya existe en el inventario y agregarlo hasta el límite de 64
						bool itemAdded2 = false;
						int SlotAmRes2 = tradesManager.TradeAm[SlotEnVillager]; 
						
						for (int j = 0; j < 36; j++) // Recorremos los slots del inventario
						{
							if (mWorld->invId[j] == tradesManager.TradeId[SlotEnVillager]) // Si el ítem ya existe
							{
								// Verificar si podemos añadir más al slot existente
								if (mWorld->invAm[j] < 64 && mWorld->invSt[j] == true)
								{
									int spaceLeft = 64 - mWorld->invAm[j]; // Cantidad que podemos agregar
									int amountToAdd = tradesManager.TradeAm[SlotEnVillager];

									if(SlotAmRes2 <= 0)
									{
										itemAdded2 = true;
										TradeSpace = true;
										break;
									}

									if (amountToAdd <= spaceLeft && SlotAmRes2 > 0) // Si la cantidad cabe
									{
										itemAdded2 = true;
										TradeSpace = true;
										break;
									}
									else if(SlotAmRes2 > 0) // Si no cabe todo, agregar lo que queda
									{
										SlotAmRes2 -= spaceLeft; // Restamos la cantidad añadida
									}
								}
							}
						}
						
						if (!itemAdded2)
						{
							for (int j = 0; j < 36; j++)
							{
								if (mWorld->invId[j] == -1) // Slot vacío encontrado
								{
									TradeSpace = true;
								}
							}
						}
						
						for (int i = 0; i < tradesManager.TradeReId.size(); i++)
						{
							for (int j = 0; j < 36; j++)
							{
								int invItemId = UniInvId(mWorld->invId[j], tradesManager.TradeReId[i]);
								
								if (invItemId == tradesManager.TradeReId[i]) // Si el slot tiene el ingrediente
								{
									if (IgredientAm[i] == 0) // Si es la primera vez que se encuentra este ingrediente
									{
										ItemRe++; // Se ha encontrado un ingrediente necesario
									}
									IgredientAm[i] += mWorld->invAm[j]; // Sumar cantidad de ingredientes en el inventario
								}
								
							}
						}
						
						Utils::Logger::Instance()->LogMessage("Comprobado Que si hay el item \n");
						
						if(ItemRe == tradesManager.TradeReId.size() - 1 && TradeSpace)
						{
							bool Trade = true;
							
							for(int i = 0; i < tradesManager.TradeReId.size(); i ++)
							{
								if(IgredientAm[i] < tradesManager.TradeReAm[i])
								{
									Trade = false;
									
									break;
								}
							}
							
							Utils::Logger::Instance()->LogMessage("Comprobado Que si hay la cantidad del item \n");
							
							if (Trade)
							{
								mSoundMgr->PlayCraftSound();
								
								int RestantCraft[2]; // Inicializar array
								
								RestantCraft[0] = 0;
								RestantCraft[1] = 0;
								RestantCraft[2] = 0;

								// Restar los ingredientes usados
								for (int i = 0; i < tradesManager.TradeReId.size(); i++)
								{
									RestantCraft[i] = tradesManager.TradeReAm[i]; // Cantidad requerida a restar

									for (int k = 0; k < 36; k++) // Buscar ingredientes en el inventario
									{							
										int invItemId = UniInvId(mWorld->invId[k], tradesManager.TradeReId[i]);
										
										if (RestantCraft[i] > 0 && invItemId == tradesManager.TradeReId[i] && mWorld->invAm[k] > 0)
										{
											int Restantinv = mWorld->invAm[k];

											for (int d = 0; d < Restantinv && RestantCraft[i] > 0; d++)
											{
												if (mWorld->invAm[k] == 1)
												{
													mWorld->invId[k] = -1;
													mWorld->invAm[k] = 0;
													mWorld->invSt[k] = 0;
													RestantCraft[i]--;
												}
												else if (mWorld->invAm[k] > 1)
												{
													mWorld->invAm[k]--;
													RestantCraft[i]--;
												}
											}
										}
										
									}
								}
								
								Utils::Logger::Instance()->LogMessage("Resta los items\n");
								
								// Buscar si el ítem ya existe en el inventario y agregarlo hasta el límite de 64
								bool itemAdded = false;
								int SlotAmRes = tradesManager.TradeAm[SlotEnVillager];
								
								for (int j = 0; j < 36; j++) // Recorremos los slots del inventario
								{
									if (mWorld->invId[j] == tradesManager.TradeId[SlotEnVillager]) // Si el ítem ya existe
									{
										// Verificar si podemos añadir más al slot existente
										if (mWorld->invAm[j] < 64 && mWorld->invSt[j] == true)
										{
											int spaceLeft = 64 - mWorld->invAm[j]; // Cantidad que podemos agregar
											int amountToAdd = tradesManager.TradeAm[SlotEnVillager];
											
											if(SlotAmRes <= 0)
											{
												itemAdded = true;
												break;
											}

											if (amountToAdd <= spaceLeft && SlotAmRes > 0) // Si la cantidad cabe
											{
												mWorld->invAm[j] += SlotAmRes; // Agregar la cantidad
												itemAdded = true;
												break;
											}
											else if(SlotAmRes > 0) // Si no cabe todo, agregar lo que queda
											{
												mWorld->invAm[j] = 64; // Llenamos el slot
												SlotAmRes -= spaceLeft; // Restamos la cantidad añadida
											}
										}
									}
								}
								Utils::Logger::Instance()->LogMessage("Se va crear un item por que no hay\n");
								// Si no encontramos un slot con el ítem o no había espacio, buscamos un slot vacío
								if (!itemAdded)
								{
									for (int j = 0; j < 36; j++)
									{
										if (mWorld->invId[j] == -1) // Slot vacío encontrado
										{
											mWorld->invId[j] = tradesManager.TradeId[SlotEnVillager];
											
											if(SlotAmRes == tradesManager.TradeAm[SlotEnVillager]) mWorld->invAm[j] = tradesManager.TradeAm[SlotEnVillager];
											else mWorld->invAm[j] = SlotAmRes;
											
											mWorld->invSt[j] = tradesManager.TradeSt[SlotEnVillager];
											break;
										}
									}
								}
								
								if(villageLvl < 10)
								{
									villageLvl = villageLvl + 1;
									
									if (villageLvl % 10 == 0 && villageLvl != 0) 
									{
										mSoundMgr->PlayExpSound();
										
										tradesManager.CleanUp();
										tradesManager.Init(villageProfession, villageLvl, villageRandom);
										tradesManager.Update(SlotEnVillager, villageProfession, villageRandom);
									}
								}
							}
							else
							{
								mSoundMgr->PlayFailCraftSound();
							}
						}
						else
						{
							mSoundMgr->PlayFailCraftSound();
						}
					}
				}
			

				if(mSystemMgr->KeyHold(PSP_CTRL_TRIANGLE) && mWorld->gameModeWorld == 1) // if you press R
				{
					if(invEn == true)
					{
						if(usingSlider == false)
						{
							usingSlider = true;
						}
					}
				}
				else
				{
					if(usingSlider == true)
					{
						usingSlider = false;
					}
				}
				
				if(keyPressed(InputHelper::Instance()->getButtonToAction(13))) // if you press L
				{
					if(mWorld->gameModeWorld == 1)
					{
						creativePage = 0;
						creativePlace --;
						if(creativePlace < 0)
						{
							creativePlace = 0;
						}
					}
					
					if(craft3xEn == true)
                    {
                        if(PagCraft > 0)
						{
							mSoundMgr->PlayMenuSound();
							
							if(PagCraft == 5 && invEn) PagCraft = 2;
							else PagCraft --;
							
							SlotEnCraft = 0;
							IndexCraft = 0;
							
							recipesManager.UpdatePag(PagCraft);
						}
						else
						{
							mSoundMgr->PlayMenuSound();
							PagCraft = 5;
							SlotEnCraft = 0;
							IndexCraft = 0;
							
							recipesManager.UpdatePag(PagCraft);
						}
                    }
					
					if(villEn == true)
					{
						if(SlotEnVillager > 0)
						{
							mSoundMgr->PlayMenuSound();
							
							SlotEnVillager --;
							
							tradesManager.Update(SlotEnVillager, villageProfession, villageRandom);
						}
						else
						{
							mSoundMgr->PlayMenuSound();
							SlotEnVillager = tradesManager.TradeId.size() - 1;
							
							tradesManager.Update(SlotEnVillager, villageProfession, villageRandom);
						}
					}
					
					if(invEn == true && craft3xEn == false && (mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2))
					{
						delete invSprite;
						
						TextureHelper::Instance()->LoadInventory(2);
						
						crtSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::crt), true);//200
						crtSprite->SetPosition(240,136);

						craft3xEn = true;
						
						if(slot2En == 1)
						{
							invXPosition = 0;
							invYPosition = 0;
							slot2En = false;
						}
						if(armorEn == 1)
						{
							invXPosition = 0;
							invYPosition = 0;
							armorEn = false;
						}
						
						recipesManager.craft2x2 = true;
						recipesManager.Init();
						
						PagCraft = 0;
						IndexCraft = 0;
						SlotEnCraft = 0;
						
						for(int i = 0; i < 5; i++)
						{
							IDDrawRe[i] = 0;
						}
						
						tickReChange = 0.0f;

						selectInvSprite->SetPosition(233+(invXPosition * 18),189+(invYPosition * 18));
					}
				}

                if(keyPressed(InputHelper::Instance()->getButtonToAction(14))) // if you press R
                {
					if(mWorld->gameModeWorld == 1)
					{
						creativePage = 0;
						creativePlace ++;
						if(creativePlace > 3)
						{
							creativePlace = 3;
						}
					}
					
					if(villEn == true)
					{
						if(SlotEnVillager < tradesManager.TradeId.size() - 1)
						{
							mSoundMgr->PlayMenuSound();
							
							SlotEnVillager ++;
							
							tradesManager.Update(SlotEnVillager, villageProfession, villageRandom);
						}
						else
						{
							mSoundMgr->PlayMenuSound();
							SlotEnVillager = 0;
							
							tradesManager.Update(SlotEnVillager, villageProfession, villageRandom);
						}
					}

                    if(furnaceEn == true)
                    {
                        if(UseFurnace->furnaceSlotId[2] != -1)
                        {
                            if(mWorld->mId == UseFurnace->furnaceSlotId[2])
                            {
                                if(UseFurnace->furnaceSlotSt[2] == 1)
                                {
                                    if(mWorld->mAm+UseFurnace->furnaceSlotAm[2] <= 64)
                                    {
										mGameMode->ArchievementsValues(0,0,UseFurnace->furnaceSlotId[2],0,mWorld);
										
                                        mWorld->mAm += UseFurnace->furnaceSlotAm[2];

                                        UseFurnace->furnaceSlotAm[2] = -1;
                                        UseFurnace->furnaceSlotId[2] = -1;
                                        UseFurnace->furnaceSlotSt[2] = 0;
                                    }
                                }
                            }

                            if(mWorld->mId == -1) //if you haven't mouse item
                            {
								/// CONTADORES DE EXPERIENCIA POR FUNDIR ITEMS U BLOQUES
								
								int ExpId = UseFurnace->furnaceSlotId[2];
								int ExpAm = UseFurnace->furnaceSlotAm[2];
								
								if(ExpId == IronBar::getID()
								|| ExpId == GoldenBar::getID()
								|| ExpId == RockBlock::getID()
								|| ExpId == Steak::getID()
								|| ExpId == CookedChicken::getID()
								|| ExpId == CookedMutton::getID()
								|| ExpId == Brick::getID()
								|| ExpId == BakedPotato::getID()
								|| ExpId == CactusGreen::getID())
								{
									if(ExpAm <= 20)
									{
										int Divisor = ExpAm/2;
										int Multiplicador = 10 * Divisor;
										
										if(rand()%100 <= Multiplicador)
										{
											ExperienceSystem(3,5);	
										}
									}
									else if(ExpAm > 20 && ExpAm <= 30)
									{
										ExperienceSystem(5,7);
									}
									else
									{
										ExperienceSystem(7,9);
									}
									
								}
								/// FIN-END

                                mWorld->mId = UseFurnace->furnaceSlotId[2];
                                mWorld->mAm = UseFurnace->furnaceSlotAm[2];
                                mWorld->mSt = UseFurnace->furnaceSlotSt[2];

                                UseFurnace->furnaceSlotId[2] = -1;
                                UseFurnace->furnaceSlotAm[2] = -1;
                                UseFurnace->furnaceSlotSt[2] = 0;
                            }
                        }
                    }


                    if(craft3xEn == true)
                    {
                        if(PagCraft < 5)
						{
							mSoundMgr->PlayMenuSound();
							
							if(PagCraft == 2 && invEn) PagCraft = 5;
							else PagCraft ++;
							
							SlotEnCraft = 0;
							IndexCraft = 0;
							
							recipesManager.UpdatePag(PagCraft);
						}
						else
						{
							mSoundMgr->PlayMenuSound();
							PagCraft = 0;
							SlotEnCraft = 0;
							IndexCraft = 0;
							
							recipesManager.UpdatePag(PagCraft);
						}
                    }
                }

                //switch right
                if(keyPressed(InputHelper::Instance()->getButtonToAction(9)))
                {
					if(armorEn == true)
                    {
						return;
					}
					
					if(slot2En == true)
                    {
						return;
					}
					
                    if (upEn == 0) // if your mouse in neither of craft menus
                    {
						if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
						{
							if(craft3xEn)
							{
								invXPosition != 8 ? invXPosition ++ : invXPosition = 8;
								selectInvSprite->SetPosition(233+(invXPosition * 18),189+(invYPosition * 18));
							}
							else if(villEn)
							{
								invXPosition != 8 ? invXPosition ++ : invXPosition = 8;
								selectInvSprite->SetPosition(218+(invXPosition * 18),152+(invYPosition * 18));
							}
							else
							{
								invXPosition != 8 ? invXPosition ++ : invXPosition = 8;
								selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));
							}
						}
						else
						{
							if(invXPosition == 8 && invYPosition == 6) // move to destroy slot
							{
								if(invEn == true)
								{
									selectInvSprite->SetPosition(331,204);
									onDestroySlot = true;
									return;
								}
							}

							invXPosition != 8 ? invXPosition ++ : invXPosition = 8;
							if(invEn == false)
							{
								if(craft3xEn)
								{
									selectInvSprite->SetPosition(233+(invXPosition * 18),189+(invYPosition * 18));
								}
								else if(villEn)
								{
									selectInvSprite->SetPosition(218+(invXPosition * 18),152+(invYPosition * 18));
								}
								else 
								{
									selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));
								}
							}
							else
							{
								if(onDestroySlot)
								{
									return;
								}
								selectInvSprite->SetPosition(169 + (invXPosition * 18),96+(invYPosition * 18));
							}
						}
                    }
                    else
                    {
						/*
                        if(invEn == 1)
                        {
                            invXPosition != 1 ? invXPosition ++ : invXPosition = 1;
                            selectInvSprite->SetPosition(258 + (invXPosition * 18),82+(invYPosition * 18));
                        }
						*/
						
                        if(craft3xEn == 1)
                        {
                            if(IndexCraft < recipesManager.IndexId.size() - 1)
							{
								IndexCraft ++;
								SlotEnCraft = 0;
								mSoundMgr->PlayMenuSound();
								
								switch(PagCraft)
								{
									case 0: 
										recipesManager.UpdateIndex(recipesManager.IndexId[IndexCraft]); 
									break;
									case 1: 
										recipesManager.UpdateIndex2(recipesManager.IndexId[IndexCraft]); 
									break;
									case 2: 
										recipesManager.UpdateIndex3(recipesManager.IndexId[IndexCraft]); 
									break;
									case 3: 
										recipesManager.UpdateIndex4(recipesManager.IndexId[IndexCraft]); 
									break;
									case 4: 
										recipesManager.UpdateIndex5(recipesManager.IndexId[IndexCraft]); 
									break;
									case 5: 
										recipesManager.UpdateIndex6(recipesManager.IndexId[IndexCraft]); 
									break;
								}
							}
							else
							{
								IndexCraft = 0;
								SlotEnCraft = 0;
								mSoundMgr->PlayMenuSound();
								
								switch(PagCraft)
								{
									case 0: 
										recipesManager.UpdateIndex(recipesManager.IndexId[IndexCraft]); 
									break;
									case 1: 
										recipesManager.UpdateIndex2(recipesManager.IndexId[IndexCraft]); 
									break;
									case 2: 
										recipesManager.UpdateIndex3(recipesManager.IndexId[IndexCraft]); 
									break;
									case 3: 
										recipesManager.UpdateIndex4(recipesManager.IndexId[IndexCraft]); 
									break;
									case 4: 
										recipesManager.UpdateIndex5(recipesManager.IndexId[IndexCraft]); 
									break;
									case 5: 
										recipesManager.UpdateIndex6(recipesManager.IndexId[IndexCraft]); 
									break;
								}
							}
                        }
                        if(chestEn == 1) // if it is in chest
                        {
                            invXPosition != 8 ? invXPosition ++ : invXPosition = 8;
                            selectInvSprite->SetPosition(168 + (invXPosition * 18),78+(invYPosition * 18));
                        }
                    }
                }

                //switch left
                if(keyPressed(InputHelper::Instance()->getButtonToAction(8)))
                {
					if(armorEn == true)
                    {
						return;
					}
					
					if(slot2En == true)
                    {
						return;
					}
					
                    if (upEn == 0) // not only craft but chest too
                    {
						if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
						{
							if(craft3xEn)
							{
								invXPosition != 0 ? invXPosition -- : invXPosition = 0;
								selectInvSprite->SetPosition(233+(invXPosition * 18),189+(invYPosition * 18));
							}
							else if(villEn)
							{
								invXPosition != 0 ? invXPosition -- : invXPosition = 0;
								selectInvSprite->SetPosition(218+(invXPosition * 18),152+(invYPosition * 18));
							}
							else
							{
								invXPosition != 0 ? invXPosition -- : invXPosition = 0;
								selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));
							}
						}
						else
						{
							if(onDestroySlot)
							{
								if(invEn == true)
								{
									onDestroySlot = false;
									//selectInvSprite->SetPosition(80 + (invXPosition * 36),28+(invYPosition * 36));
									selectInvSprite->SetPosition(313,204);
									return;
								}
							}
							invXPosition != 0 ? invXPosition -- : invXPosition = 0;
							if(invEn == false)
							{
								if(craft3xEn)
								{
									selectInvSprite->SetPosition(233+(invXPosition * 18),189+(invYPosition * 18));
								}
								else if(villEn)
								{
									selectInvSprite->SetPosition(218+(invXPosition * 18),152+(invYPosition * 18));
								}
								else
								{
									selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));
								}
								//selectInvSprite->SetPosition(248+(invXPosition * 18),138+(invYPosition * 36));
							}
							else
							{
								selectInvSprite->SetPosition(169 + (invXPosition * 18),96+(invYPosition * 18));
								//selectInvSprite->SetPosition(248 + (invXPosition * 18),28+(invYPosition * 36));
							}
						}
                    }
                    else
                    {
                        invXPosition != 0 ? invXPosition -- : invXPosition = 0;
						/*
                        if(invEn == 1)
                        {
                            selectInvSprite->SetPosition(258 + (invXPosition * 18),82+(invYPosition * 18));
                        }
						*/
                        if(craft3xEn == 1)
                        {
                            if(IndexCraft > 0)
							{
								IndexCraft --;
								SlotEnCraft = 0;
								mSoundMgr->PlayMenuSound();
								
								switch(PagCraft)
								{
									case 0: 
										recipesManager.UpdateIndex(recipesManager.IndexId[IndexCraft]); 
									break;
									case 1: 
										recipesManager.UpdateIndex2(recipesManager.IndexId[IndexCraft]); 
									break;
									case 2: 
										recipesManager.UpdateIndex3(recipesManager.IndexId[IndexCraft]); 
									break;
									case 3: 
										recipesManager.UpdateIndex4(recipesManager.IndexId[IndexCraft]); 
									break;
									case 4: 
										recipesManager.UpdateIndex5(recipesManager.IndexId[IndexCraft]); 
									break;
									case 5: 
										recipesManager.UpdateIndex6(recipesManager.IndexId[IndexCraft]); 
									break;
								}
							}
							else
							{
								mSoundMgr->PlayMenuSound();
								
								IndexCraft = recipesManager.IndexId.size() - 1;
								SlotEnCraft = 0;
								
								switch(PagCraft)
								{
									case 0: 
										recipesManager.UpdateIndex(recipesManager.IndexId[IndexCraft]); 
									break;
									case 1: 
										recipesManager.UpdateIndex2(recipesManager.IndexId[IndexCraft]); 
									break;
									case 2: 
										recipesManager.UpdateIndex3(recipesManager.IndexId[IndexCraft]); 
									break;
									case 3: 
										recipesManager.UpdateIndex4(recipesManager.IndexId[IndexCraft]); 
									break;
									case 4: 
										recipesManager.UpdateIndex5(recipesManager.IndexId[IndexCraft]); 
									break;
									case 5: 
										recipesManager.UpdateIndex6(recipesManager.IndexId[IndexCraft]); 
									break;
								}
							}
                        }
                        if(chestEn == 1)
                        {
                            selectInvSprite->SetPosition(168 + (invXPosition * 18),78+(invYPosition * 18));
                        }
                    }
                }

                //switch down
                if(keyPressed(InputHelper::Instance()->getButtonToAction(11)))
                {
					//Slider
					if(usingSlider)
					{
						creativePage ++;
						switch(creativePlace)
						{
							case 0:
								if(creativePage > creativePageMax1)
								{
									creativePage = creativePageMax1;
								}
							break;
							case 1:
								if(creativePage > creativePageMax2)
								{
									creativePage = creativePageMax2;
								}
							break;
							case 2:
								if(creativePage > creativePageMax3)
								{
									creativePage = creativePageMax3;
								}
							break;
							case 3:
								if(creativePage > creativePageMax4)
								{
									creativePage = creativePageMax4;
								}
							break;
						}
						return;
					}
					///Inventory
                    if (upEn == 0 && slot2En == 0)
                    {
                        if(armorEn == true)
                        {
							if(invXPosition == 0 && invYPosition == 0)
                            {
								invXPosition = 1;
                                invYPosition = 0;
                                selectInvSprite->SetPosition(204, 87);
								return;
                            }
							if(invXPosition == 1 && invYPosition == 0)
                            {
								invXPosition = 0;
                                invYPosition = 1;
                                selectInvSprite->SetPosition(204, 105);
								return;
                            }
							if(invXPosition == 0 && invYPosition == 1)
                            {
								invXPosition = 1;
                                invYPosition = 1;
                                selectInvSprite->SetPosition(204, 123);
								return;
                            }			
                            if(invXPosition == 1 && invYPosition == 1)
                            {
								invXPosition = 2;
                                invYPosition = 0;
                                armorEn = false;
                                selectInvSprite->SetPosition(168 +(invXPosition * 18), 149);
								return;
                            }
                        }
                        else
                        {
							if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
							{
								if(craft3xEn)
								{
									invYPosition != 3 ? invYPosition ++ : invYPosition = 3;
									selectInvSprite->SetPosition(233+(invXPosition * 18),189+(invYPosition * 18));
								}
								else if(villEn)
								{
									invYPosition != 3 ? invYPosition ++ : invYPosition = 3;
									selectInvSprite->SetPosition(218+(invXPosition * 18),152+(invYPosition * 18));
								}
								else
								{
									invYPosition != 3 ? invYPosition ++ : invYPosition = 3;
									selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));
								}
							}
							else
							{
								if(invEn == false)
								{
									invYPosition != 3 ? invYPosition ++ : invYPosition = 3;
									
									if(craft3xEn)
									{
										selectInvSprite->SetPosition(233+(invXPosition * 18),189+(invYPosition * 18));
									}
									else if(villEn)
									{
										selectInvSprite->SetPosition(218+(invXPosition * 18),152+(invYPosition * 18));
									}
									else
									{
										selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));
									}
									//selectInvSprite->SetPosition(96+(invXPosition * 36),138+(invYPosition * 36));
								}
								else
								{
									if(onDestroySlot)
									{
										return;
									}
									invYPosition != 6 ? invYPosition ++ : invYPosition = 6;
									selectInvSprite->SetPosition(169 + (invXPosition * 18),96+(invYPosition * 18));
									//selectInvSprite->SetPosition(80 + (invXPosition * 36),28+(invYPosition * 36));
								}	
							}
                        }
                    }
					else if(slot2En == 1)
					{
						if(invXPosition == 0 && invYPosition == 0)
                        {
							invXPosition = 6;
                            invYPosition = 0;
							slot2En = false;
                            selectInvSprite->SetPosition(168 + (invXPosition * 18), 149);
							return;
                        }
					}
                    else
                    {
						/*
                        if (invEn == 1) //if mouse in the down of menu
                        {
                            if (invYPosition == 1)
                            {
                                upEn = 0; // we go to standart inv menu
                                invYPosition = 0;
                                invXPosition = 5 + invXPosition;
                                selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));
                                return;
                            }
                            invYPosition != 1 ? invYPosition ++ : invYPosition = 1;
                            selectInvSprite->SetPosition(258 + (invXPosition * 18),82+(invYPosition * 18));
                        }
						*/

                        if (craft3xEn == 1)
                        {
                            if(SlotEnCraft < recipesManager.SlotId.size() - 1)
							{
								SlotEnCraft ++;
								mSoundMgr->PlayMenuSound();

								switch(PagCraft)
								{
									case 0: 
										recipesManager.UpdateSlot(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 1: 
										recipesManager.UpdateSlot2(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 2: 
										recipesManager.UpdateSlot3(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 3: 
										recipesManager.UpdateSlot4(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 4: 
										recipesManager.UpdateSlot5(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 5: 
										recipesManager.UpdateSlot6(recipesManager.SlotId[SlotEnCraft]);
									break;
								}
							}
							else
							{
								SlotEnCraft = 0;
								mSoundMgr->PlayMenuSound();
								
								switch(PagCraft)
								{
									case 0: 
										recipesManager.UpdateSlot(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 1: 
										recipesManager.UpdateSlot2(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 2: 
										recipesManager.UpdateSlot3(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 3: 
										recipesManager.UpdateSlot4(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 4: 
										recipesManager.UpdateSlot5(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 5: 
										recipesManager.UpdateSlot6(recipesManager.SlotId[SlotEnCraft]);
									break;
								}
							}
                        }

                        if (chestEn == 1)
                        {
                            if (invYPosition == 2)
                            {
                                upEn = 0;
                                invYPosition = 0;
                                selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));
                                return;
                            }
                            invYPosition != 1 ? invYPosition ++ : invYPosition = 2;
                            selectInvSprite->SetPosition(168 + (invXPosition * 18),78+(invYPosition * 18));
                        }

                        if (furnaceEn == 1)
                        {
                            if (invYPosition == 1)
                            {
                                upEn = 0;
                                invYPosition = 0;
                                invXPosition = 3;
                                selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));
                                return;
                            }
                            invYPosition != 1 ? invYPosition ++ : invYPosition = 1;
                            selectInvSprite->SetPosition(222,78+(invYPosition * 36));
                        }
                    }
                }

                //switch up
                if(keyPressed(InputHelper::Instance()->getButtonToAction(10)))
                {
					if(usingSlider)
					{
						creativePage --;
						if(creativePage < 0)
						{
							creativePage = 0;
						}
						return;
					}
					
                    if (upEn == 0)
                    {
						if(armorEn == true)
                        {
							if(invXPosition == 1 && invYPosition == 1)
							{
								invXPosition = 0;
								invYPosition = 1;
								selectInvSprite->SetPosition(204,105);
								return;
							}
							if(invXPosition == 0 && invYPosition == 1)
							{
								invXPosition = 1;
								invYPosition = 0;
								selectInvSprite->SetPosition(204,87);
								return;
							}
							if(invXPosition == 1 && invYPosition == 0)
							{
								invXPosition = 0;
								invYPosition = 0;
								selectInvSprite->SetPosition(204,69);
								return;
							}
                        }
						
                        if (invYPosition == 0)
                        {
                            if(invEn == 1 && (mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2))
                            {
								/*
                                if((invXPosition == 5 || invXPosition == 6) && armorEn == false && slot2En == false)
                                {
                                    invXPosition -= 5;
                                    invYPosition = 1;
                                    selectInvSprite->SetPosition(258 + (invXPosition * 18),82+(invYPosition * 18));
                                    upEn = true;
                                }
								*/
								
								if(invXPosition == 6 && slot2En == false && craft3xEn == false)
                                {
                                    invXPosition -= 6;
                                    invYPosition = 0;
                                    selectInvSprite->SetPosition(276,123);
                                    slot2En = true;
                                }
								
                                if((invXPosition == 2) && armorEn == false && upEn == false && slot2En == false && craft3xEn == false)
                                {
									invXPosition = 1;
                                    invYPosition = 1;
                                    selectInvSprite->SetPosition(204,123);
                                    armorEn = true;
                                }
                            }
                            if(chestEn == 1)
                            {
                                invYPosition = 2;
                                selectInvSprite->SetPosition(168 + (invXPosition * 18),78+(invYPosition * 18));
                                upEn = 1;
                            }
                            if(furnaceEn == 1)
                            {
                                if(invXPosition == 3)
                                {
                                    invYPosition = 1;
                                    selectInvSprite->SetPosition(222,78+(invYPosition * 36));
                                    upEn = 1;
                                }
                            }
                            return;
                        }					

						if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
						{    						
							if(craft3xEn)
							{
								invYPosition != 0 ? invYPosition -- : invYPosition = 0;
								selectInvSprite->SetPosition(233+(invXPosition * 18),189+(invYPosition * 18));
							}
							else if(villEn)
							{
								invYPosition != 0 ? invYPosition -- : invYPosition = 0;
								selectInvSprite->SetPosition(218+(invXPosition * 18),152+(invYPosition * 18));
							}
							else
							{
								invYPosition != 0 ? invYPosition -- : invYPosition = 0;
								selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));
							}
						}
						else
						{
							if(onDestroySlot)
							{
								if(invEn == true)
								{
									return;
								}
							}

							invYPosition != 0 ? invYPosition -- : invYPosition = 0;

							if(invEn == false)
							{
								if(craft3xEn)
								{
									selectInvSprite->SetPosition(233+(invXPosition * 18),189+(invYPosition * 18));
								}
								else if(villEn)
								{
									selectInvSprite->SetPosition(218+(invXPosition * 18),152+(invYPosition * 18));
								}
								else
								{
									selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));
								}
								//selectInvSprite->SetPosition(96+(invXPosition * 36),138+(invYPosition * 36));
							}
							else
							{
								selectInvSprite->SetPosition(169 + (invXPosition * 18),96+(invYPosition * 18));
								//selectInvSprite->SetPosition(80 + (invXPosition * 36),28+(invYPosition * 36));
							}
						}
                    }
                    else
                    {
						if(craft3xEn)
						{
							if(SlotEnCraft > 0)
							{
								mSoundMgr->PlayMenuSound();
								SlotEnCraft --;
								
								switch(PagCraft)
								{
									case 0: 
										recipesManager.UpdateSlot(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 1: 
										recipesManager.UpdateSlot2(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 2: 
										recipesManager.UpdateSlot3(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 3: 
										recipesManager.UpdateSlot4(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 4: 
										recipesManager.UpdateSlot5(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 5: 
										recipesManager.UpdateSlot6(recipesManager.SlotId[SlotEnCraft]);
									break;
								}
							}
							else
							{
								mSoundMgr->PlayMenuSound();
								
								SlotEnCraft = recipesManager.SlotId.size() - 1;
								
								switch(PagCraft)
								{
									case 0: 
										recipesManager.UpdateSlot(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 1: 
										recipesManager.UpdateSlot2(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 2: 
										recipesManager.UpdateSlot3(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 3: 
										recipesManager.UpdateSlot4(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 4: 
										recipesManager.UpdateSlot5(recipesManager.SlotId[SlotEnCraft]);
									break;
									case 5: 
										recipesManager.UpdateSlot6(recipesManager.SlotId[SlotEnCraft]);
									break;
								}
							}
						}
						else
						{
							invYPosition != 0 ? invYPosition -- : invYPosition = 0;

							/*
							if(invEn == 1)
							{
								selectInvSprite->SetPosition(258 + (invXPosition * 18),82+(invYPosition * 18));
							}
							*/
							if(chestEn == 1)
							{
								selectInvSprite->SetPosition(168 + (invXPosition * 18),78+(invYPosition * 18));
							}
							if(furnaceEn == 1)
							{
								selectInvSprite->SetPosition(222,78+(invYPosition * 36));
							}
						}
                    }
                }


                if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
                {
                    if (upEn == 0)
                    {
						if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
						{
							if(slot2En)
							{
								if (mWorld->mId == -1)
								{
									if (mWorld->invSlot2Id == 415) // 324+invYPosition*2+invXPosition is an id of sample armor item
									{
										mWorld->mId = mWorld->invSlot2Id;
										mWorld->mAm = mWorld->invSlot2Am;
										mWorld->mSt = mWorld->invSlot2St;
										mWorld->invSlot2Id = -1;
										mWorld->invSlot2Am = -1;
										mWorld->invSlot2St = false;
									}
								}
								else
								{
									if (mWorld->invSlot2Id == -1)
									{
										if(mWorld->mId == 415) // crazy code monkey skill
										{
											mWorld->invSlot2Id = mWorld->mId;
											mWorld->invSlot2Am = mWorld->mAm;
											mWorld->invSlot2St = mWorld->mSt;
											mWorld->mId = -1;
											mWorld->mAm = -1;
											mWorld->mSt = false;
										}
									}
								}
							}
							else if(armorEn == false)
							{
								if (mWorld->mId == -1)
								{
									if (mWorld->invId[invYPosition*9 + invXPosition] != -1)
									{
										mWorld->mId = mWorld->invId[invYPosition*9 + invXPosition];
										mWorld->mAm = mWorld->invAm[invYPosition*9 + invXPosition];
										mWorld->mSt = mWorld->invSt[invYPosition*9 + invXPosition];
										mWorld->invId[invYPosition*9 + invXPosition] = -1;
										mWorld->invAm[invYPosition*9 + invXPosition] = -1;
										mWorld->invSt[invYPosition*9 + invXPosition] = 0;
									}
								}
								else
								{
									if (mWorld->invId[invYPosition*9 + invXPosition] == -1)
									{
										mWorld->invId[invYPosition*9 + invXPosition]=mWorld->mId;
										mWorld->invAm[invYPosition*9 + invXPosition]=mWorld->mAm;
										mWorld->invSt[invYPosition*9 + invXPosition]=mWorld->mSt;
										mWorld->mId = -1;
										mWorld->mAm = -1;
										mWorld->mSt = 0;
									}
									else if (mWorld->invId[invYPosition*9 + invXPosition] == mWorld->mId)
									{
										if(mWorld->invSt[invYPosition*9 + invXPosition] == 1)
										{
											if (mWorld->invAm[invYPosition*9 + invXPosition]+mWorld->mAm < 64)
											{
												mWorld->invAm[invYPosition*9 + invXPosition]+=mWorld->mAm;
												mWorld->mId = -1;
												mWorld->mAm = -1;
												mWorld->mSt = 0;
											}
											else
											{
												mWorld->mAm = (mWorld->invAm[invYPosition*9 + invXPosition] + mWorld->mAm) - 64;
												mWorld->invAm[invYPosition*9 + invXPosition]=64;

												if(mWorld->mAm == 0)
												{
													mWorld->mAm = -1;
													mWorld->mId = -1;
													mWorld->mSt = 0;
												}
											}
										}
									}
									else 
									{
										short mId2 = mWorld->mId;
										short mAm2 = mWorld->mAm;
										bool mSt2 = mWorld->mSt;
										
										mWorld->mId = mWorld->invId[invYPosition*9 + invXPosition];
										mWorld->mAm = mWorld->invAm[invYPosition*9 + invXPosition];
										mWorld->mSt = mWorld->invSt[invYPosition*9 + invXPosition];
										
										mWorld->invId[invYPosition*9 + invXPosition] = mId2;
										mWorld->invAm[invYPosition*9 + invXPosition] = mAm2;
										mWorld->invSt[invYPosition*9 + invXPosition] = mSt2;
									}
								}
							}
							else
							{
								if (mWorld->mId == -1)
								{
									if (mWorld->armorId[invYPosition*2 + invXPosition] != 324+invYPosition*2+invXPosition) // 324+invYPosition*2+invXPosition is an id of sample armor item
									{
										mWorld->mId = mWorld->armorId[invYPosition*2 + invXPosition];
										mWorld->mAm = mWorld->armorAm[invYPosition*2 + invXPosition];
										mWorld->mSt = mWorld->armorSt[invYPosition*2 + invXPosition];
										mWorld->armorId[invYPosition*2 + invXPosition] = 324+invYPosition*2+invXPosition;
										mWorld->armorAm[invYPosition*2 + invXPosition] = -1;
										mWorld->armorSt[invYPosition*2 + invXPosition] = false;
									}
								}
								else
								{
									if (mWorld->armorId[invYPosition*2 + invXPosition] == 324+invYPosition*2+invXPosition)
									{
										if(mWorld->mId == 324+invYPosition*2+invXPosition+4 || /* all leather armor */
										   mWorld->mId == 324+invYPosition*2+invXPosition+8 || /* all chain armor */
										   mWorld->mId == 324+invYPosition*2+invXPosition+12|| /* all iron armor */
										   mWorld->mId == 324+invYPosition*2+invXPosition+16|| /* all diamond armor */
										   mWorld->mId == 324+invYPosition*2+invXPosition+20|| /* all golde armor */
										   (invXPosition == 0 && invYPosition == 0 && mWorld->mId == Pumpkin3::getID()) /** it is pumpkin and cursor on helmet slot **/
										  ) // crazy code monkey skill
										{
											mWorld->armorId[invYPosition*2 + invXPosition]=mWorld->mId;
											mWorld->armorAm[invYPosition*2 + invXPosition]=mWorld->mAm;
											mWorld->armorSt[invYPosition*2 + invXPosition]=mWorld->mSt;
											mWorld->mId = -1;
											mWorld->mAm = -1;
											mWorld->mSt = false;
										}
									}
								}
							}
						}
						else
						{
							if(invEn == false)
							{
								if (mWorld->mId == -1)
								{
									if (mWorld->invId[invYPosition*9 + invXPosition] != -1)
									{
										mWorld->mId = mWorld->invId[invYPosition*9 + invXPosition];
										mWorld->mAm = mWorld->invAm[invYPosition*9 + invXPosition];
										mWorld->mSt = mWorld->invSt[invYPosition*9 + invXPosition];
										mWorld->invId[invYPosition*9 + invXPosition] = -1;
										mWorld->invAm[invYPosition*9 + invXPosition] = -1;
										mWorld->invSt[invYPosition*9 + invXPosition] = 0;
									}
								}
								else
								{
									if (mWorld->invId[invYPosition*9 + invXPosition] == -1)
									{
										mWorld->invId[invYPosition*9 + invXPosition]=mWorld->mId;
										mWorld->invAm[invYPosition*9 + invXPosition]=mWorld->mAm;
										mWorld->invSt[invYPosition*9 + invXPosition]=mWorld->mSt;
										mWorld->mId = -1;
										mWorld->mAm = -1;
										mWorld->mSt = 0;
									}
									else if (mWorld->invId[invYPosition*9 + invXPosition] == mWorld->mId)
									{
										if(mWorld->invSt[invYPosition*9 + invXPosition] == 1)
										{
											if (mWorld->invAm[invYPosition*9 + invXPosition]+mWorld->mAm < 64)
											{
												mWorld->invAm[invYPosition*9 + invXPosition]+=mWorld->mAm;
												mWorld->mId = -1;
												mWorld->mAm = -1;
												mWorld->mSt = 0;
											}
											else
											{
												mWorld->mAm = (mWorld->invAm[invYPosition*9 + invXPosition] + mWorld->mAm) - 64;
												mWorld->invAm[invYPosition*9 + invXPosition]=64;

												if(mWorld->mAm == 0)
												{
													mWorld->mAm = -1;
													mWorld->mId = -1;
													mWorld->mSt = 0;
												}
											}
										}
									}
									else 
									{
										short mId2 = mWorld->mId;
										short mAm2 = mWorld->mAm;
										bool mSt2 = mWorld->mSt;
										
										mWorld->mId = mWorld->invId[invYPosition*9 + invXPosition];
										mWorld->mAm = mWorld->invAm[invYPosition*9 + invXPosition];
										mWorld->mSt = mWorld->invSt[invYPosition*9 + invXPosition];
										
										mWorld->invId[invYPosition*9 + invXPosition] = mId2;
										mWorld->invAm[invYPosition*9 + invXPosition] = mAm2;
										mWorld->invSt[invYPosition*9 + invXPosition] = mSt2;
									}
								}
							}
							else
							{
								if(onDestroySlot)
								{
									if(mWorld->mId != -1)
									{
										mWorld->mId = -1;
										mWorld->mAm = -1;
										mWorld->mSt = 0;

										mSoundMgr->PlayBreakSound();
									}
									return;
								}
								else if (invYPosition == 6)
								{
									if (mWorld->mId == -1)
									{
										if (mWorld->invId[27 + invXPosition] != -1)
										{
											mWorld->mId = mWorld->invId[27 + invXPosition];
											mWorld->mAm = mWorld->invAm[27 + invXPosition];
											mWorld->mSt = mWorld->invSt[27 + invXPosition];
											mWorld->invId[27 + invXPosition] = -1;
											mWorld->invAm[27 + invXPosition] = -1;
											mWorld->invSt[27 + invXPosition] = 0;
										}
									}
									else
									{
										if (mWorld->invId[27 + invXPosition] == -1)
										{
											mWorld->invId[27 + invXPosition]=mWorld->mId;
											mWorld->invAm[27 + invXPosition]=mWorld->mAm;
											mWorld->invSt[27 + invXPosition]=mWorld->mSt;
											mWorld->mId = -1;
											mWorld->mAm = -1;
											mWorld->mSt = 0;
										}

										if (mWorld->invId[27 + invXPosition] == mWorld->mId)
										{
											if(mWorld->invSt[27 + invXPosition] == 1)
											{
												if (mWorld->invAm[27 + invXPosition]+mWorld->mAm < 64)
												{
													mWorld->invAm[27 + invXPosition]+=mWorld->mAm;
													mWorld->mId = -1;
													mWorld->mAm = -1;
													mWorld->mSt = 0;
												}
												else
												{
													mWorld->mAm = (mWorld->invAm[27 + invXPosition] + mWorld->mAm) - 64;
													mWorld->invAm[27 + invXPosition]=64;

													if(mWorld->mAm == 0)
													{
														mWorld->mAm = -1;
														mWorld->mId = -1;
														mWorld->mSt = 0;
													}
												}
											}
										}
									}
								}
								else
								{
									if (mWorld->mId == -1)
									{
										switch(creativePlace)
										{
											case 0:
												if (creativePage*27 + invYPosition*9 + invXPosition < inventoryCoItems.size()) // creativePage*53 + invYPosition*9 + invXPosition - выбранный слот в инветаре с учетом страницы
												{
													mWorld->mId = inventoryCoItems[creativePage*27 + invYPosition*9 + invXPosition];

													if(inventoryCoItems[creativePage*27 + invYPosition*9 + invXPosition] >= 250)
													{
														if(mWorld->DurabilityPointsItem(inventoryCoItems[creativePage*27 + invYPosition*9 + invXPosition]) != -1)
														{
															mWorld->mAm = mWorld->DurabilityPointsItem(inventoryCoItems[creativePage*27 + invYPosition*9 + invXPosition]);
															mWorld->mSt = 0;
														}
														else
														{
															if(mWorld->StackableItem(inventoryCoItems[creativePage*27 + invYPosition*9 + invXPosition]))
															{
																mWorld->mAm = 64;
																mWorld->mSt = true;
															}
															else
															{
																mWorld->mAm = 1;
																mWorld->mSt = false;
															}
														}
													}
													else
													{
														mWorld->mAm = 64;
														mWorld->mSt = 1;
													}
												}
											break;
											case 1:
												if (creativePage*27 + invYPosition*9 + invXPosition < inventoryEqItems.size()) // creativePage*53 + invYPosition*9 + invXPosition - выбранный слот в инветаре с учетом страницы
												{
													mWorld->mId = inventoryEqItems[creativePage*27 + invYPosition*9 + invXPosition];

													if(inventoryEqItems[creativePage*27 + invYPosition*9 + invXPosition] >= 250)
													{
														if(mWorld->DurabilityPointsItem(inventoryEqItems[creativePage*27 + invYPosition*9 + invXPosition]) != -1)
														{
															mWorld->mAm = mWorld->DurabilityPointsItem(inventoryEqItems[creativePage*27 + invYPosition*9 + invXPosition]);
															mWorld->mSt = 0;
														}
														else
														{
															if(mWorld->StackableItem(inventoryEqItems[creativePage*27 + invYPosition*9 + invXPosition]))
															{
																mWorld->mAm = 64;
																mWorld->mSt = true;
															}
															else
															{
																mWorld->mAm = 1;
																mWorld->mSt = false;
															}
														}
													}
													else
													{
														mWorld->mAm = 64;
														mWorld->mSt = 1;
													}
												}
											break;
											case 2:
												if (creativePage*27 + invYPosition*9 + invXPosition < inventoryDeItems.size()) // creativePage*53 + invYPosition*9 + invXPosition - выбранный слот в инветаре с учетом страницы
												{
													mWorld->mId = inventoryDeItems[creativePage*27 + invYPosition*9 + invXPosition];

													if(inventoryDeItems[creativePage*27 + invYPosition*9 + invXPosition] >= 250)
													{
														if(mWorld->DurabilityPointsItem(inventoryDeItems[creativePage*27 + invYPosition*9 + invXPosition]) != -1)
														{
															mWorld->mAm = mWorld->DurabilityPointsItem(inventoryDeItems[creativePage*27 + invYPosition*9 + invXPosition]);
															mWorld->mSt = 0;
														}
														else
														{
															if(mWorld->StackableItem(inventoryDeItems[creativePage*27 + invYPosition*9 + invXPosition]))
															{
																mWorld->mAm = 64;
																mWorld->mSt = true;
															}
															else
															{
																mWorld->mAm = 1;
																mWorld->mSt = false;
															}
														}
													}
													else
													{
														mWorld->mAm = 64;
														mWorld->mSt = 1;
													}
												}
											break;
											case 3:
												if (creativePage*27 + invYPosition*9 + invXPosition < inventoryNaItems.size()) // creativePage*53 + invYPosition*9 + invXPosition - выбранный слот в инветаре с учетом страницы
												{
													mWorld->mId = inventoryNaItems[creativePage*27 + invYPosition*9 + invXPosition];

													if(inventoryNaItems[creativePage*27 + invYPosition*9 + invXPosition] >= 250)
													{
														if(mWorld->DurabilityPointsItem(inventoryNaItems[creativePage*27 + invYPosition*9 + invXPosition]) != -1)
														{
															mWorld->mAm = mWorld->DurabilityPointsItem(inventoryNaItems[creativePage*27 + invYPosition*9 + invXPosition]);
															mWorld->mSt = 0;
														}
														else
														{
															if(mWorld->StackableItem(inventoryNaItems[creativePage*27 + invYPosition*9 + invXPosition]))
															{
																mWorld->mAm = 64;
																mWorld->mSt = true;
															}
															else
															{
																mWorld->mAm = 1;
																mWorld->mSt = false;
															}
														}
													}
													else
													{
														mWorld->mAm = 64;
														mWorld->mSt = 1;
													}
												}
											break;
										}
									}
								}
							}
						}
                    }
                    else
                    {

                        if (craft3xEn == 1)
                        {
							//Comprobar Ingredientes
							int ItemRe = -1;
							int IgredientAm[5];
							bool CraftSpace = false;

							IgredientAm[0] = 0;
							IgredientAm[1] = 0;
							IgredientAm[2] = 0;
							IgredientAm[3] = 0;
							IgredientAm[4] = 0;
							IgredientAm[5] = 0;
							
							// Buscar si existe espacio libre
							bool itemAdded2 = false;
							int SlotAmRes2 = recipesManager.SlotAm[SlotEnCraft];
							
							for (int j = 0; j < 36; j++) // Recorremos los slots del inventario
							{
								if (mWorld->invId[j] == recipesManager.SlotId[SlotEnCraft]) // Si el ítem ya existe
								{
									// Verificar si podemos añadir más al slot existente
									if (mWorld->invAm[j] < 64 && mWorld->invSt[j] == true)
									{
										int spaceLeft = 64 - mWorld->invAm[j]; // Cantidad que podemos agregar
										int amountToAdd = recipesManager.SlotAm[SlotEnCraft];

										if(SlotAmRes2 <= 0)
										{
											itemAdded2 = true;
											CraftSpace = true;
											break;
										}

										if (amountToAdd <= spaceLeft && SlotAmRes2 > 0) // Si la cantidad cabe
										{
											itemAdded2 = true;
											CraftSpace = true;
											break;
										}
										else if(SlotAmRes2 > 0) // Si no cabe todo, agregar lo que queda
										{
											SlotAmRes2 -= spaceLeft; // Restamos la cantidad añadida
										}
									}
								}
							}
							
							if (!itemAdded2)
							{
								for (int j = 0; j < 36; j++)
								{
									if (mWorld->invId[j] == -1) // Slot vacío encontrado
									{
										CraftSpace = true;
									}
								}
							}
							
							for (int i = 0; i < recipesManager.ReSlotId.size(); i++)
							{
								for (int j = 0; j < 36; j++)
								{
									int invItemId = UniInvId(mWorld->invId[j], recipesManager.ReSlotId[i]);
									
									if (invItemId == recipesManager.ReSlotId[i]) // Si el slot tiene el ingrediente
									{
										if (IgredientAm[i] == 0) // Si es la primera vez que se encuentra este ingrediente
										{
											ItemRe++; // Se ha encontrado un ingrediente necesario
										}
										IgredientAm[i] += mWorld->invAm[j]; // Sumar cantidad de ingredientes en el inventario
									}
									
								}
							}
							
							if(ItemRe == recipesManager.ReSlotId.size() - 1 && CraftSpace == true)
							{
								bool Craft = true;
								
								for(int i = 0; i < recipesManager.ReSlotId.size(); i ++)
								{
									if(IgredientAm[i] < recipesManager.ReSlotAm[i])
									{
										Craft = false;
										
										break;
									}
								}
								
								if (Craft)
								{
									mSoundMgr->PlayCraftSound();
									
									int RestantCraft[5]; // Inicializar array
									
									RestantCraft[0] = 0;
									RestantCraft[1] = 0;
									RestantCraft[2] = 0;
									RestantCraft[3] = 0;
									RestantCraft[4] = 0;
									RestantCraft[5] = 0;

									// Restar los ingredientes usados
									for (int i = 0; i < recipesManager.ReSlotId.size(); i++)
									{
										RestantCraft[i] = recipesManager.ReSlotAm[i]; // Cantidad requerida a restar

										for (int k = 0; k < 36; k++) // Buscar ingredientes en el inventario
										{							
											int invItemId = UniInvId(mWorld->invId[k], recipesManager.ReSlotId[i]);
											
											if (RestantCraft[i] > 0 && invItemId == recipesManager.ReSlotId[i] && mWorld->invAm[k] > 0)
											{
												int Restantinv = mWorld->invAm[k];

												for (int d = 0; d < Restantinv && RestantCraft[i] > 0; d++)
												{
													if (mWorld->invAm[k] == 1)
													{
														mWorld->invId[k] = -1;
														mWorld->invAm[k] = 0;
														mWorld->invSt[k] = 0;
														RestantCraft[i]--;
													}
													else if (mWorld->invAm[k] > 1)
													{
														mWorld->invAm[k]--;
														RestantCraft[i]--;
													}
												}
											}
											
										}
									}
									
									// Buscar si el ítem ya existe en el inventario y agregarlo hasta el límite de 64
									bool itemAdded = false;
									int SlotAmRes = recipesManager.SlotAm[SlotEnCraft];
									
									for (int j = 0; j < 36; j++) // Recorremos los slots del inventario
									{
										if (mWorld->invId[j] == recipesManager.SlotId[SlotEnCraft]) // Si el ítem ya existe
										{
											// Verificar si podemos añadir más al slot existente
											if (mWorld->invAm[j] < 64 && mWorld->invSt[j] == true)
											{
												int spaceLeft = 64 - mWorld->invAm[j]; // Cantidad que podemos agregar
												int amountToAdd = recipesManager.SlotAm[SlotEnCraft];
												
												if(SlotAmRes <= 0)
												{
													itemAdded = true;
													break;
												}

												if (amountToAdd <= spaceLeft && SlotAmRes > 0) // Si la cantidad cabe
												{
													mWorld->invAm[j] += SlotAmRes; // Agregar la cantidad
													itemAdded = true;
													break;
												}
												else if(SlotAmRes > 0) // Si no cabe todo, agregar lo que queda
												{
													mWorld->invAm[j] = 64; // Llenamos el slot
													SlotAmRes -= spaceLeft; // Restamos la cantidad añadida
												}
											}
										}
									}

									// Si no encontramos un slot con el ítem o no había espacio, buscamos un slot vacío
									if (!itemAdded)
									{
										for (int j = 0; j < 36; j++)
										{
											if (mWorld->invId[j] == -1) // Slot vacío encontrado
											{
												mWorld->invId[j] = recipesManager.SlotId[SlotEnCraft];
												
												if(SlotAmRes == recipesManager.SlotAm[SlotEnCraft]) mWorld->invAm[j] = recipesManager.SlotAm[SlotEnCraft];
												else mWorld->invAm[j] = SlotAmRes;
												
												mWorld->invSt[j] = recipesManager.SlotSt[SlotEnCraft];
												break;
											}
										}
									}
									
									mGameMode->ArchievementsValues(0,0,0,recipesManager.SlotId[SlotEnCraft],mWorld);
								}
								else
								{
									mSoundMgr->PlayFailCraftSound();
								}
							}
							else
							{
								mSoundMgr->PlayFailCraftSound();
							}
                        }
                        //Chest => action when put a item into a chest
                        if (chestEn == 1)
                        {
							
                            if (mWorld->mId == -1)
                            {
                                if (UseChest->chestSlotId[invYPosition*9 + invXPosition] != -1)
                                {
                                    mWorld->mId = UseChest->chestSlotId[invYPosition*9 + invXPosition];
                                    mWorld->mAm = UseChest->chestSlotAm[invYPosition*9 + invXPosition];
                                    mWorld->mSt = UseChest->chestSlotSt[invYPosition*9 + invXPosition];
                                    UseChest->chestSlotId[invYPosition*9 + invXPosition] = -1;
                                    UseChest->chestSlotAm[invYPosition*9 + invXPosition] = -1;
                                    UseChest->chestSlotSt[invYPosition*9 + invXPosition] = 0;
                                }
                            }
                            else
                            {
                                if (UseChest->chestSlotId[invYPosition*9 + invXPosition] == -1)
                                {
                                    UseChest->chestSlotId[invYPosition*9 + invXPosition]=mWorld->mId;
                                    UseChest->chestSlotAm[invYPosition*9 + invXPosition]=mWorld->mAm;
                                    UseChest->chestSlotSt[invYPosition*9 + invXPosition]=mWorld->mSt;
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                    mWorld->mSt = 0;
                                }
								else if (UseChest->chestSlotId[invYPosition*9 + invXPosition] == mWorld->mId)
                                {
                                    if(UseChest->chestSlotSt[invYPosition*9 + invXPosition] == 1)
                                    {
                                        if (UseChest->chestSlotAm[+invYPosition*9 + invXPosition]+mWorld->mAm < 64)
                                        {
                                            UseChest->chestSlotAm[invYPosition*9 + invXPosition]+=mWorld->mAm;
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                            mWorld->mSt = 0;
                                        }
                                        else
                                        {
                                            mWorld->mAm = (UseChest->chestSlotAm[invYPosition*9 + invXPosition] + mWorld->mAm) - 64;
                                            UseChest->chestSlotAm[invYPosition*9 + invXPosition]=64;

                                            if(mWorld->mAm == 0)
                                            {
                                                mWorld->mAm = -1;
                                                mWorld->mId = -1;
                                                mWorld->mSt = 0;
                                            }
                                        }
                                    }
                                }
								else 
								{
									short mId2 = mWorld->mId;
									short mAm2 = mWorld->mAm;
									bool mSt2 = mWorld->mSt;
									
									mWorld->mId = UseChest->chestSlotId[invYPosition*9 + invXPosition];
									mWorld->mAm = UseChest->chestSlotAm[invYPosition*9 + invXPosition];
									mWorld->mSt = UseChest->chestSlotSt[invYPosition*9 + invXPosition];
									
									UseChest->chestSlotId[invYPosition*9 + invXPosition] = mId2;
									UseChest->chestSlotAm[invYPosition*9 + invXPosition] = mAm2;
									UseChest->chestSlotSt[invYPosition*9 + invXPosition] = mSt2;
								}
                            }
                        }
                        //furnace
                        if(furnaceEn == true)
                        {
                            if (mWorld->mId == -1)
                            {
                                if (UseFurnace->furnaceSlotId[invYPosition] != -1)
                                {
                                    mWorld->mId = UseFurnace->furnaceSlotId[invYPosition];
                                    mWorld->mAm = UseFurnace->furnaceSlotAm[invYPosition];
                                    mWorld->mSt = UseFurnace->furnaceSlotSt[invYPosition];
                                    UseFurnace->furnaceSlotId[invYPosition] = -1;
                                    UseFurnace->furnaceSlotAm[invYPosition] = -1;
                                    UseFurnace->furnaceSlotSt[invYPosition] = 0;
                                }
                            }
                            else
                            {
                                if (UseFurnace->furnaceSlotId[invYPosition] == -1)
                                {
                                    UseFurnace->furnaceSlotId[invYPosition]=mWorld->mId;
                                    UseFurnace->furnaceSlotAm[invYPosition]=mWorld->mAm;
                                    UseFurnace->furnaceSlotSt[invYPosition]=mWorld->mSt;
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                    mWorld->mSt = 0;
                                }
								else if (UseFurnace->furnaceSlotId[invYPosition] == mWorld->mId)
                                {
                                    if(UseFurnace->furnaceSlotSt[invYPosition] == 1)
                                    {
                                        if (UseFurnace->furnaceSlotAm[invYPosition]+mWorld->mAm < 64)
                                        {
                                            UseFurnace->furnaceSlotAm[invYPosition]+=mWorld->mAm;
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                            mWorld->mSt = 0;
                                        }
                                        else
                                        {
                                            mWorld->mAm = (UseFurnace->furnaceSlotAm[invYPosition] + mWorld->mAm) - 64;
                                            UseFurnace->furnaceSlotAm[invYPosition]=64;

                                            if(mWorld->mAm == 0)
                                            {
                                                mWorld->mAm = -1;
                                                mWorld->mId = -1;
                                                mWorld->mSt = 0;
                                            }
                                        }
                                    }
                                }
								else 
								{
									short mId2 = mWorld->mId;
									short mAm2 = mWorld->mAm;
									bool mSt2 = mWorld->mSt;
									
									mWorld->mId = UseFurnace->furnaceSlotId[invYPosition];
									mWorld->mAm = UseFurnace->furnaceSlotAm[invYPosition];
									mWorld->mSt = UseFurnace->furnaceSlotSt[invYPosition];
									
									UseFurnace->furnaceSlotId[invYPosition] = mId2;
									UseFurnace->furnaceSlotAm[invYPosition] = mAm2;
									UseFurnace->furnaceSlotSt[invYPosition] = mSt2;
								}
                            }
                            CheckForFurnFuel(UseFurnace);
                            CheckForFurnWorking(UseFurnace);
                        }
                    }
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_SQUARE))
                {
                    if (upEn == 0 && armorEn == 0 && slot2En == 0)
                    {
						if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
						{
							if (mWorld->invId[invYPosition*9 + invXPosition] == mWorld->mId)
							{
								if(mWorld->mSt == true)
								{
									if (mWorld->invAm[invYPosition*9 + invXPosition] != 64)
									{
										mWorld->invAm[invYPosition*9 + invXPosition] += 1;

										mWorld->mAm -= 1;

										if(mWorld->mAm == 0)
										{
											mWorld->mId = -1;
											mWorld->mAm = -1;
										}
										return;
									}
								}
							}

							if (mWorld->mId != -1)
							{
								if(mWorld->mSt == true)
								{
								   if (mWorld->invId[invYPosition*9 + invXPosition] == -1)
								   {
										mWorld->invId[invYPosition*9 + invXPosition] = mWorld->mId;
										mWorld->invAm[invYPosition*9 + invXPosition] = 1;
										mWorld->invSt[invYPosition*9 + invXPosition] = 1;

										mWorld->mAm -= 1;

										if(mWorld->mAm == 0)
										{
											mWorld->mId = -1;
											mWorld->mAm = -1;
											mWorld->mSt = 0;
										}
										return;
									}
								}
							}
							else
							{
							   if (mWorld->invId[invYPosition*9 + invXPosition] != -1 && mWorld->invSt[invYPosition*9 + invXPosition] == 1)
							   {
								   if(mWorld->invAm[invYPosition*9 + invXPosition] == 1)
								   {
									   mWorld->mId = mWorld->invId[invYPosition*9 + invXPosition];
									   mWorld->mAm = 1;
									   mWorld->mSt = mWorld->invSt[invYPosition*9 + invXPosition];

									   mWorld->invId[invYPosition*9 + invXPosition] = -1;
									   mWorld->invAm[invYPosition*9 + invXPosition] = -1;
									   mWorld->invSt[invYPosition*9 + invXPosition] = 0;
								   }
								   if(mWorld->invAm[invYPosition*9 + invXPosition] > 1)
								   {
									   mWorld->mId = mWorld->invId[invYPosition*9 + invXPosition];
									   mWorld->mAm = ceilf((float)(mWorld->invAm[invYPosition*9 + invXPosition]/2.0f));
									   mWorld->mSt = mWorld->invSt[invYPosition*9 + invXPosition];

									   mWorld->invAm[invYPosition*9 + invXPosition] = mWorld->invAm[invYPosition*9 + invXPosition]-mWorld->mAm;
								   }
								}
							}
						}
						else
						{
							if(invEn == false)
							{
								if (mWorld->invId[invYPosition*9 + invXPosition] == mWorld->mId)
								{
									if(mWorld->mSt == true)
									{
										if (mWorld->invAm[invYPosition*9 + invXPosition] != 64)
										{
											mWorld->invAm[invYPosition*9 + invXPosition] += 1;

											mWorld->mAm -= 1;

											if(mWorld->mAm == 0)
											{
												mWorld->mId = -1;
												mWorld->mAm = -1;
											}
											return;
										}
									}
								}

								if (mWorld->mId != -1)
								{
									if(mWorld->mSt == true)
									{
									   if (mWorld->invId[invYPosition*9 + invXPosition] == -1)
									   {
											mWorld->invId[invYPosition*9 + invXPosition] = mWorld->mId;
											mWorld->invAm[invYPosition*9 + invXPosition] = 1;
											mWorld->invSt[invYPosition*9 + invXPosition] = 1;

											mWorld->mAm -= 1;

											if(mWorld->mAm == 0)
											{
												mWorld->mId = -1;
												mWorld->mAm = -1;
												mWorld->mSt = 0;
											}

											return;
										}
									}
								}
								else
								{
								   if (mWorld->invId[invYPosition*9 + invXPosition] != -1 && mWorld->invSt[invYPosition*9 + invXPosition] == 1)
								   {
									   if(mWorld->invAm[invYPosition*9 + invXPosition] == 1)
									   {
										   mWorld->mId = mWorld->invId[invYPosition*9 + invXPosition];
										   mWorld->mAm = 1;
										   mWorld->mSt = mWorld->invSt[invYPosition*9 + invXPosition];

										   mWorld->invId[invYPosition*9 + invXPosition] = -1;
										   mWorld->invAm[invYPosition*9 + invXPosition] = -1;
										   mWorld->invSt[invYPosition*9 + invXPosition] = 0;
									   }
									   if(mWorld->invAm[invYPosition*9 + invXPosition] > 1)
									   {
										   mWorld->mId = mWorld->invId[invYPosition*9 + invXPosition];
										   mWorld->mAm = ceilf((float)(mWorld->invAm[invYPosition*9 + invXPosition]/2.0f));
										   mWorld->mSt = mWorld->invSt[invYPosition*9 + invXPosition];

										   mWorld->invAm[invYPosition*9 + invXPosition] = mWorld->invAm[invYPosition*9 + invXPosition]-mWorld->mAm;
									   }
									}
								}
							}
							else
							{
								if(invYPosition == 6)
								{
									if (mWorld->invId[27 + invXPosition] == mWorld->mId)
									{
										if(mWorld->mSt == true)
										{
											if (mWorld->invAm[27 + invXPosition] != 64)
											{
												mWorld->invAm[27 + invXPosition] += 1;

												mWorld->mAm -= 1;

												if(mWorld->mAm == 0)
												{
													mWorld->mId = -1;
													mWorld->mAm = -1;
												}
												return;
											}
										}
									}

									if (mWorld->mId != -1)
									{
										if(mWorld->mSt == true)
										{
										   if (mWorld->invId[27 + invXPosition] == -1)
										   {
												mWorld->invId[27 + invXPosition] = mWorld->mId;
												mWorld->invAm[27 + invXPosition] = 1;
												mWorld->invSt[27 + invXPosition] = 1;

												mWorld->mAm -= 1;

												if(mWorld->mAm == 0)
												{
													mWorld->mId = -1;
													mWorld->mAm = -1;
													mWorld->mSt = 0;
												}
												return;
											}
										}
									}
									else
									{
									   if (mWorld->invId[27 + invXPosition] != -1 && mWorld->invSt[27 + invXPosition] == 1)
									   {
										   if(mWorld->invAm[27 + invXPosition] == 1)
										   {
											   mWorld->mId = mWorld->invId[27 + invXPosition];
											   mWorld->mAm = 1;
											   mWorld->mSt = mWorld->invSt[27 + invXPosition];

											   mWorld->invId[27 + invXPosition] = -1;
											   mWorld->invAm[27 + invXPosition] = -1;
											   mWorld->invSt[27 + invXPosition] = 0;
										   }
										   if(mWorld->invAm[27 + invXPosition] > 1)
										   {
											   mWorld->mId = mWorld->invId[27 + invXPosition];
											   mWorld->mAm = ceilf((float)(mWorld->invAm[27 + invXPosition]/2.0f));
											   mWorld->mSt = mWorld->invSt[27 + invXPosition];

											   mWorld->invAm[27 + invXPosition] = mWorld->invAm[27 + invXPosition]-mWorld->mAm;
										   }
										}
									}
								}
							}
						}
                    }
                    else
                    {

                        ///CHEST
                        if (chestEn == 1)
                        {
                            if (UseChest->chestSlotId[invYPosition*9 + invXPosition] == mWorld->mId)
                            {
                                if(mWorld->mSt == true)
                                {
                                    if (UseChest->chestSlotAm[invYPosition*9 + invXPosition] != 64)
                                    {
                                        UseChest->chestSlotAm[invYPosition*9 + invXPosition] += 1;

                                        mWorld->mAm -= 1;
                                        if(mWorld->mAm == 0)
                                        {
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                        }
                                        return;
                                    }
                                }
                            }

                            if (mWorld->mId != -1)
                            {
                                if(mWorld->mSt == true)
                                {
                                    if (UseChest->chestSlotId[invYPosition*9 + invXPosition] == -1)
                                    {
                                        UseChest->chestSlotId[invYPosition*9 + invXPosition] = mWorld->mId;
                                        UseChest->chestSlotAm[invYPosition*9 + invXPosition] = 1;
                                        UseChest->chestSlotSt[invYPosition*9 + invXPosition] = 1;

                                        mWorld->mAm -= 1;

                                        if(mWorld->mAm == 0)
                                        {
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                            mWorld->mSt = 0;
                                        }
                                        return;
                                    }
                                }
                            }
                            else
                            {
                               if (UseChest->chestSlotId[invYPosition*9 + invXPosition] != -1 && UseChest->chestSlotSt[invYPosition*9 + invXPosition] == 1)
                               {
                                   if(UseChest->chestSlotAm[invYPosition*9 + invXPosition] == 1)
                                   {
                                       mWorld->mId = UseChest->chestSlotId[invYPosition*9 + invXPosition];
                                       mWorld->mAm = 1;
                                       mWorld->mSt = UseChest->chestSlotSt[invYPosition*9 + invXPosition];

                                       UseChest->chestSlotId[invYPosition*9 + invXPosition] = -1;
                                       UseChest->chestSlotAm[invYPosition*9 + invXPosition] = -1;
                                       UseChest->chestSlotSt[invYPosition*9 + invXPosition] = 0;
                                   }
                                   if(UseChest->chestSlotAm[invYPosition*9 + invXPosition] > 1)
                                   {
                                       mWorld->mId = UseChest->chestSlotId[invYPosition*9 + invXPosition];
                                       mWorld->mAm = ceilf((float)(UseChest->chestSlotAm[invYPosition*9 + invXPosition]/2.0f));
                                       mWorld->mSt = UseChest->chestSlotSt[invYPosition*9 + invXPosition];

                                       UseChest->chestSlotAm[invYPosition*9 + invXPosition] = UseChest->chestSlotAm[invYPosition*9 + invXPosition]-mWorld->mAm;
                                   }
                                }
                            }
                        }
                        ///FURNACE
                        if (furnaceEn == 1)
                        {
                            if (UseFurnace->furnaceSlotId[invYPosition] == mWorld->mId)
                            {
                                if(mWorld->mSt == true)
                                {
                                    if (UseFurnace->furnaceSlotAm[invYPosition] != 64)
                                    {
                                        UseFurnace->furnaceSlotAm[invYPosition] += 1;

                                        mWorld->mAm -= 1;
                                        if(mWorld->mAm == 0)
                                        {
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                        }
                                        CheckForFurnFuel(UseFurnace);
                                        CheckForFurnWorking(UseFurnace);
                                        return;
                                    }
                                }
                            }

                            if (mWorld->mId != -1)
                            {
                                if(mWorld->mSt == true)
                                {
                                    if (UseFurnace->furnaceSlotId[invYPosition] == -1)
                                    {
                                        UseFurnace->furnaceSlotId[invYPosition] = mWorld->mId;
                                        UseFurnace->furnaceSlotAm[invYPosition] = 1;
                                        UseFurnace->furnaceSlotSt[invYPosition] = 1;

                                        mWorld->mAm -= 1;

                                        if(mWorld->mAm == 0)
                                        {
                                            mWorld->mId = -1;
                                            mWorld->mAm = -1;
                                            mWorld->mSt = 0;
                                        }
                                        CheckForFurnFuel(UseFurnace);
                                        CheckForFurnWorking(UseFurnace);
                                        return;
                                    }
                                }
                            }
                            else
                            {
                               if (UseFurnace->furnaceSlotId[invYPosition] != -1 && UseFurnace->furnaceSlotSt[invYPosition] == 1)
                               {
                                   if(UseFurnace->furnaceSlotAm[invYPosition] == 1)
                                   {
                                       mWorld->mId = UseFurnace->furnaceSlotId[invYPosition];
                                       mWorld->mAm = 1;
                                       mWorld->mSt = UseFurnace->furnaceSlotSt[invYPosition];

                                       UseFurnace->furnaceSlotId[invYPosition] = -1;
                                       UseFurnace->furnaceSlotAm[invYPosition] = -1;
                                       UseFurnace->furnaceSlotSt[invYPosition] = 0;
                                   }
                                   if(UseFurnace->furnaceSlotAm[invYPosition] > 1)
                                   {
                                       mWorld->mId = UseFurnace->furnaceSlotId[invYPosition];
                                       mWorld->mAm = ceilf((float)(UseFurnace->furnaceSlotAm[invYPosition]/2.0f));
                                       mWorld->mSt = UseFurnace->furnaceSlotSt[invYPosition];

                                       UseFurnace->furnaceSlotAm[invYPosition] = UseFurnace->furnaceSlotAm[invYPosition]-mWorld->mAm;
                                   }
                                }
                            }
                            CheckForFurnFuel(UseFurnace);
                            CheckForFurnWorking(UseFurnace);
                        }
                    }
                }
            }
        }
        else 
		if(menuState == 1) //menu state
        {
            //turn off menu with the same key
            if(keyPressed(InputHelper::Instance()->getButtonToAction(15)))
            {
                menuState = 0;
                menuOptions = false;
                optionsMenuPos = 0;
				menuOptionsPag = 0;
                selectPos = 0;
            }
			
			if(menuOptions)
            {
                //up, down
                if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
                {
					if(optionsMenuPos == 0)
					{
						return;
					}
					optionsMenuPos--;
					mSoundMgr->PlayMenuSound();
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
                {
					switch(menuOptionsPag)
					{
						case 0:
							if(optionsMenuPos == 8)
							{
								return;
							}
							optionsMenuPos++;
							mSoundMgr->PlayMenuSound();
						break;
						case 1:
							if(optionsMenuPos == 5)
							{
								return;
							}
							optionsMenuPos++;
							mSoundMgr->PlayMenuSound();
						break;
					}
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
                {
                    menuOptionsPag = 1;
					optionsMenuPos = 0;
                    mSoundMgr->PlayMenuSound();
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
                {
                    menuOptionsPag = 0;
					optionsMenuPos = 0;
                    mSoundMgr->PlayMenuSound();
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_RIGHT))
                {
					if(menuOptionsPag == 0)
					{
						if(optionsMenuPos == 0)
						{
							if (mWorld->mainOptions.fov <= 95)
							{
								mWorld->mainOptions.fov += 5;
								mSoundMgr->PlayMenuSound();
								mRender->fovv = mWorld->mainOptions.fov;
								RenderManager::InstancePtr()->SetPerspective(0, 480.0f / 272.0f, 0.18f, 1000.f);
								skyLight->UpdateLightSource(mWorld->skyTime);
								skyMoonLight->UpdateLightSource(mWorld->skyTime);
							}
						}
						if(optionsMenuPos == 1)
						{
							if (mWorld->mainOptions.horizontalViewDistance != 4)
							{
								mWorld->mainOptions.horizontalViewDistance += 1;
								mSoundMgr->PlayMenuSound();
								mWorld->playerZoneSize = Vector3(CHUNK_SIZE*mWorld->mainOptions.horizontalViewDistance,CHUNK_SIZE*mWorld->mainOptions.verticalViewDistance,CHUNK_SIZE*mWorld->mainOptions.horizontalViewDistance);
								mWorld->UpdatePlayerZoneBB(fppCam->m_vPosition);
								fppCam->needUpdate = true;
							}
						}
						if(optionsMenuPos == 2)
						{
							if (mWorld->mainOptions.verticalViewDistance != 2)
							{
								mWorld->mainOptions.verticalViewDistance += 1;
								mSoundMgr->PlayMenuSound();
								mWorld->playerZoneSize = Vector3(CHUNK_SIZE*mWorld->mainOptions.horizontalViewDistance,CHUNK_SIZE*mWorld->mainOptions.verticalViewDistance,CHUNK_SIZE*mWorld->mainOptions.horizontalViewDistance);
								mWorld->UpdatePlayerZoneBB(fppCam->m_vPosition);
								fppCam->needUpdate = true;
							}
						}
						if(optionsMenuPos == 3)
						{
							mWorld->mainOptions.difficult += 1;
							mSoundMgr->PlayMenuSound();

							if(mWorld->mainOptions.difficult > 3)
							{
								mWorld->mainOptions.difficult = 3;
							}
						}
						
						if(optionsMenuPos == 4)
						{
							mWorld->mainOptions.sounds = true;
							mSoundMgr->PlayMenuSound();
							mSoundMgr->playerSounds = mWorld->mainOptions.sounds;
						}

						if(optionsMenuPos == 5)
						{
							mWorld->mainOptions.music = true;
							mSoundMgr->PlayMenuSound();
							mSoundMgr->StopAmbient();
							mSoundMgr->StopHell();
						}
					}
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_LEFT))
                {
					if(menuOptionsPag == 0)
					{
						if(optionsMenuPos == 0)
						{
							if (mWorld->mainOptions.fov >= 45)
							{
								mWorld->mainOptions.fov -= 5;
								mSoundMgr->PlayMenuSound();
								mRender->fovv = mWorld->mainOptions.fov;
								RenderManager::InstancePtr()->SetPerspective(0, 480.0f / 272.0f, 0.18f, 1000.f);
								skyLight->UpdateLightSource(mWorld->skyTime);
								skyMoonLight->UpdateLightSource(mWorld->skyTime);
							}
						}
						if(optionsMenuPos == 1)
						{
							if (mWorld->mainOptions.horizontalViewDistance != 1)
							{
								mWorld->mainOptions.horizontalViewDistance -= 1;
								mSoundMgr->PlayMenuSound();
								mWorld->playerZoneSize = Vector3(CHUNK_SIZE*mWorld->mainOptions.horizontalViewDistance,CHUNK_SIZE*mWorld->mainOptions.verticalViewDistance,CHUNK_SIZE*mWorld->mainOptions.horizontalViewDistance);
								fppCam->needUpdate = true;
							}
						}
						if(optionsMenuPos == 2)
						{
							if (mWorld->mainOptions.verticalViewDistance != 1)
							{
								mWorld->mainOptions.verticalViewDistance -= 1;
								mSoundMgr->PlayMenuSound();
								mWorld->playerZoneSize = Vector3(CHUNK_SIZE*mWorld->mainOptions.horizontalViewDistance,CHUNK_SIZE*mWorld->mainOptions.verticalViewDistance,CHUNK_SIZE*mWorld->mainOptions.horizontalViewDistance);
								fppCam->needUpdate = true;
							}
						}
						if(optionsMenuPos == 3)
						{
							mWorld->mainOptions.difficult -= 1;
							mSoundMgr->PlayMenuSound();

							if(mWorld->mainOptions.difficult < 0)
							{
								mWorld->mainOptions.difficult = 0;
							}
						}
					
						if(optionsMenuPos == 4)
						{
							mWorld->mainOptions.sounds = false;
							mSoundMgr->PlayMenuSound();
							mSoundMgr->playerSounds = mWorld->mainOptions.sounds;
						}

						if(optionsMenuPos == 5)
						{
							mWorld->mainOptions.music = false;
							mSoundMgr->PlayMenuSound();
							mSoundMgr->StopAmbient();
							mSoundMgr->StopHell();
						}
					}
                }

                //back
                if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
                {
                    if (mWorld->mainOptions.difficult == 0)
                    {
                        mWorld->DestroyAllZombies();
						mWorld->DestroyAllSkeletons();
                        mWorld->DestroyAllSpiders();
                        mWorld->DestroyAllSpidercaves();
                        mWorld->DestroyAllCreepers();
                    }
                    selectPos = 1;
                    menuOptions = false;
					
					delete menuOptionsSprite;
					delete menuOptionsSpriteFo;
					delete Check;
					delete CheckFo;
					delete sbuttonSprite2;
					delete LogoMenu;
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
                {
					switch(menuOptionsPag)
					{
						case 0:
							//smooth lighting
							if(optionsMenuPos == 6)
							{
								mWorld->mainOptions.smoothLighting = !mWorld->mainOptions.smoothLighting;
								mSoundMgr->PlayMenuSound();

								mWorld->RebuildVisibleChunks();
							}
						
							//fog rendering
							if(optionsMenuPos == 7)
							{
								 mWorld->mainOptions.fogRendering = !mWorld->mainOptions.fogRendering;
								 mSoundMgr->PlayMenuSound();
							}

							//clouds rendering
							if(optionsMenuPos == 8)
							{
								 mWorld->mainOptions.detailedSky = !mWorld->mainOptions.detailedSky;
								 mSoundMgr->PlayMenuSound();
							}
						break;
						case 1:
							//fast rendering
							if(optionsMenuPos == 0)
							{
								mWorld->mainOptions.newSprintOption = !mWorld->mainOptions.newSprintOption;
								mSoundMgr->PlayMenuSound();

								//mWorld->RebuildVisibleChunks();
							}

							//block animation
							if(optionsMenuPos == 1)
							{
								mWorld->mainOptions.worldBlockAnimation = !mWorld->mainOptions.worldBlockAnimation;
								mSoundMgr->PlayMenuSound();
							}

							//auto jump
							if(optionsMenuPos == 2)
							{
								mWorld->mainOptions.autoJump = !mWorld->mainOptions.autoJump;
								bobCycle = 0.0f;
								mSoundMgr->PlayMenuSound();
							}

							if(optionsMenuPos == 3)
							{
								mWorld->mainOptions.buttonsDrawing = !mWorld->mainOptions.buttonsDrawing;
								mSoundMgr->PlayMenuSound();
							}

							if(optionsMenuPos == 4)
							{
								mWorld->mainOptions.guiDrawing = !mWorld->mainOptions.guiDrawing;
								mSoundMgr->PlayMenuSound();
							}


							//take screen
							if(optionsMenuPos == 14)
							{
								makeScreen = true;
								/*unsigned short test[128];
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

									sprintf(mWorld->worldName,"%s",newWorldName.c_str());
								}*/
							}

							if(optionsMenuPos == 5)
							{
								devMode = !devMode;
							}
						break;
					}
                }
            }
            else
            {
                //up, down
                if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
                {
                    selectPos--;
                    if(selectPos < 0)
                        selectPos = 5;

                    mSoundMgr->PlayMenuSound();
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
                {
                    selectPos++;
                    if(selectPos > 5)
                        selectPos = 0;

                    mSoundMgr->PlayMenuSound();
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
                {
                    menuState = 0;
                    selectPos = 0;
                    optionsMenuPos = 0;
					menuOptionsPag = 0;
                    menuOptions = false;
                }

                if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
                {
                    if(selectPos == 0)//resume
                    {
                        menuState = 0;
                    }
                    if(selectPos == 1)//options
                    {
                        optionsMenuPos = 0;
						menuOptionsPag = 0;
                        menuOptions = true;
						
						//Textures
						menuOptionsSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::MOptions));
						menuOptionsSprite->SetPosition(240,139);
						
						menuOptionsSpriteFo = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::About2));
						menuOptionsSpriteFo->SetPosition(240,139);
						menuOptionsSpriteFo->Scale(2.7,1.9);
						
						sbuttonSprite2 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,12,95,12);
						sbuttonSprite2->SetPosition(240,139);
						sbuttonSprite2->Scale(1.5,1.5);
						
						LogoMenu = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::lameCraft));
						LogoMenu->SetPosition(240,139);
						LogoMenu->Scale(0.5,0.5);
						
						CheckFo = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),60,60,12,12);
						CheckFo->SetPosition(240,139);
						CheckFo->Scale(1.5,1.5);
						
						Check = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),72,60,12,12);
						Check->SetPosition(240,139);
						Check->Scale(1.5,1.5);
                    }
                    if(selectPos == 2)//stats
                    {
						AchiBoxSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::About));
						AchiBoxSprite->SetPosition(240,139);
						
						LogoMenu = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::lameCraft));
						LogoMenu->SetPosition(240,139);
						LogoMenu->Scale(0.5,0.5);
						
                        menuState = 3;
                        selectPos = 0;
                    }
                    if(selectPos == 3)//save
                    {
                        mWorld->SaveCompressedWorld(saveFileName.c_str());
                        menuState = 0;
                    }
                    if(selectPos == 4)//Test Nether Esto he cambiado
                    {
						mSoundMgr->PlayRandomMenu(); //menu
						mSoundMgr->StopHell();
                        mSoundMgr->StopAmbient();
                        mSoundMgr->StopDiskTrack();
						
						Utils::Logger::Instance()->LogMessage("Sounds Stop \n");
						
                        mWorld->SaveCompressedWorld(saveFileName.c_str());
						
						Utils::Logger::Instance()->LogMessage("Guardando Juego \n");
						
						mGlobalFun->CreateHell = false;
						mGlobalFun->teleported = false;
						mGlobalFun->thisWorld = false;
						mGlobalFun->Load = 1;
						//langManager.clean_memory();
						
						Utils::Logger::Instance()->LogMessage("Restart Variables \n");
						
						TextureHelper::Instance()->LoadConstTexture();
						
						Utils::Logger::Instance()->LogMessage("Cargar Texturas StateLoad \n");
					
                        sManager->PopState();
						
						Utils::Logger::Instance()->LogMessage("Cambiar de State \n");
                    }
                    if(selectPos == 5)//exit Esto he cambiado
                    {
						mSoundMgr->PlayRandomMenu(); //menu
						mSoundMgr->StopHell();
                        mSoundMgr->StopAmbient();
                        mSoundMgr->StopDiskTrack();
						
						Utils::Logger::Instance()->LogMessage("Sounds Stop \n");
						
						mGlobalFun->CreateHell = false;
						mGlobalFun->teleported = false;
						mGlobalFun->thisWorld = false;
						mGlobalFun->Load = 1;
						//langManager.clean_memory();
						
						Utils::Logger::Instance()->LogMessage("Reinicio de Variables \n");
						
						TextureHelper::Instance()->LoadConstTexture();
						
						Utils::Logger::Instance()->LogMessage("Load Textures StateLoad \n");
						
                        sManager->PopState();
						
						Utils::Logger::Instance()->LogMessage("Cambio de State \n");
                    }
                }
            }
        }
        
		if (menuState == 3)
        {
            if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
            {
                selectPos = 2;
                menuState = 1;
            }
            if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
            {
                statisticsPage += 1;
                if(statisticsPage == 2)
                {
                    statisticsPage = 0;
                }
            }
            if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
            {
                statisticsPage -= 1;
                if(statisticsPage == -1)
                {
                    statisticsPage = 1;
                }
            }
        }
    }
	
		//New Die Screen!!! //muerte
		if(mWorld->HP <=0)
		{
			if(invEn == true || craft3xEn == true || chestEn == true || furnaceEn == true || villEn == true) //Closed Dead Inventory
            {

				if(craft3xEn == true)
				{
					PagCraft = 0;
					IndexCraft = 0;
					SlotEnCraft = 0;
					
					for(int i = 0; i < 5; i++)
					{
						IDDrawRe[i] = 0;
					}
					
					tickReChange = 0.0f;
					
					recipesManager.CleanUp();
				}

				if(upEn == true)
				{
					invXPosition = 0;
					invYPosition = 0;
				}
				
				if(villEn == true)
				{
					tradesManager.CleanUp();
					
					Villager* TestVillager = mWorld->mVillagers[villageId];
					
					TestVillager->tradder = false;
					TestVillager->LevelProfession = villageLvl;
					
					SlotEnVillager = 0;
				}
				
				selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));
				
				if((mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2) && invEn == true && craft3xEn == false) 
				{
					delete invSprite;
				}
				else if((mWorld->gameModeWorld == 1) && invEn == true) 
				{
					delete invSpriteCreative;
				}
				else if(chestEn == true) 
				{
					delete chtSprite;
				}
				else if(craft3xEn == true) 
				{
					delete crtSprite;
				}
				else if(furnaceEn == true) 
				{
					delete furSprite;
				}
				else if(villEn == true)
				{
					delete invVillage;
				}
				
				TextureHelper::Instance()->UnLoadInventory();

				invEn = false;
				villEn = false;
				craft3xEn = false;
				furnaceEn = false;
				
				if(chestEn == true)
				{
					mSoundMgr->PlayChestClosedSound();
				}
				
				chestEn = false;
				upEn = false;
				slot2En = false;
				furnaceEn = false;
				chestId = -1;
				villageId = -1;
				villageProfession = 0;
				villageLvl = 0;
				villageRandom = 0;
				armorEn = false;
				
				UseChest = 0;
				UseFurnace = 0;

				mWorld->haveCompass = mWorld->HaveItemInBarSlots(Compass::getID());
			}
			
			if(mWorld->gameModeWorld == 2)
			{
				if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
				{
					if(diePos == 0);
					{
						mWorld->gameLocked = true;
						mWorld->SaveCompressedWorld(saveFileName.c_str());

						std::string fileName = saveFileName;
						remove(fileName.c_str());
						fileName = fileName + "c";
						remove(fileName.c_str());
							
						mSoundMgr->PlayRandomMenu();
						mSoundMgr->StopAmbient();
						mSoundMgr->StopHell();
						mSoundMgr->StopDiskTrack();
						mGlobalFun->Load = 1;
						TextureHelper::Instance()->LoadConstTexture();
						sManager->PopState();
					}
				}
			}
			else
			{
				if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
					{
						diePos--;
						if(diePos < 0)
						diePos = 1;
						mSoundMgr->PlayMenuSound();
					}
					
					if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
					{
						diePos++;
						if(diePos > 1)
						diePos = 0;

						mSoundMgr->PlayMenuSound();
					}
				
				if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
				{
					if(diePos == 0)
					{
						mWorld->playerGrowth = 1.65f;

						Vector3 newPosition = mWorld->playerSpawnPointPosition;
						if(mWorld->BlockSolid(newPosition.x,newPosition.y-1.2f,newPosition.z) || mWorld->BlockSolid(newPosition.x,newPosition.y,newPosition.z))
						{
							if(mWorld->currentDimension == 0) newPosition.y = mWorld->groundHeight(newPosition.x,newPosition.z)+mWorld->playerGrowth-0.05f+1;
						}

						playerPosition.x = newPosition.x;
						playerPosition.y = newPosition.y;
						playerPosition.z = newPosition.z;

						mWorld->UpdatePlayerZoneBB(playerPosition);	//Move player back to original spawn point
						fppCam->PositionCamera(playerPosition.x,playerPosition.y,playerPosition.z, playerPosition.x,playerPosition.y,playerPosition.z-5.0f, 0.0f,1.0f,0.0f);
						fppCam->RotateView(0,0,90,0);
						fppCam->upDownAngle = 0;
						fppCam->horAngle = 270;
						mWorld->HP = 20;
						mWorld->HG = 20;
						mWorld->OS = 10;
						mWorld->FR = 0;
						HGP = 0;
						HPE = 0;
						mWorld->EXPcount = 0;
						mWorld->EXP = 0;
						
						HungerPoisoned = false;
						HPPoisoned = false;
						crouch = false;
						sprint = false;
						shield = false;
						slowWalk = false;
						burning = false;
						invEn = false;
						slot2En = false;
						craft3xEn = false;
						furnaceEn = false;
						chestEn = false;
						upEn = false;
						slot2En = false;
						furnaceEn = false;
						chestId = -1;
						villageId = -1;
						villageProfession = 0;
						villageLvl = 0;
						villageRandom = 0;
						villEn = false;
						armorEn = false;

						UseChest = NULL;
						UseFurnace = NULL;
						
						int chunkTarget = mWorld->getChunkId(playerPosition-Vector3(0, -1.75, 0));

						//Rebuild the world around
						mWorld->RebuildFullMeshChunk(chunkTarget);
						mWorld->rebuildNearestChunks(chunkTarget,playerPosition);
						//mWorld->rebuildVisibleChunks();
					   // mWorld->rebuildVisibleTransperentChunks();

						dieFactor = 1;
						
					}
					
					if(diePos == 1)
					{
						mSoundMgr->PlayRandomMenu();
						mSoundMgr->StopAmbient();
						mSoundMgr->StopHell();
						mSoundMgr->StopDiskTrack();
						mGlobalFun->Load = 1;
						TextureHelper::Instance()->LoadConstTexture();
						sManager->PopState();
					}
				}
			}
		}
	
    if(mWorld->HP <= 0)
    {
        mWorld->playerGrowth = 0.65f;
        if(dieFactor == 1) // drop your loot
        {
            for(int i = 0; i < 36; i++)
            {
                if(i <= 3) // drop armor items
                {
                    if(mWorld->armorId[i] != 324 + i)
                    {
                        Vector3 dropVelocity = Vector3(0,0,0);

                        dropVelocity.x = (-15+rand()%30)*0.1f;
                        dropVelocity.y = 3.0f;
                        dropVelocity.z = (-15+rand()%30)*0.1f;

                        mWorld->DropThisNoAlign(mWorld->armorId[i],mWorld->armorAm[i],mWorld->armorSt[i],Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y-0.25f,fppCam->m_vPosition.z),dropVelocity);

                        mWorld->armorAm[i] = -1;
                        mWorld->armorSt[i] = 0;
                        mWorld->armorId[i] = -1;
                    }
                }
                if(mWorld->invId[i] > 0)
                {
                    Vector3 dropVelocity = Vector3(0,0,0);

                    dropVelocity.x = (-15+rand()%30)*0.1f;
                    dropVelocity.y = 3.0f;
                    dropVelocity.z = (-15+rand()%30)*0.1f;
					
					if(mWorld->invId[i] == Bow1::getID() || mWorld->invId[i] == Bow2::getID() || mWorld->invId[i] == Bow3::getID())
					{
						mWorld->invId[i] = Bow0::getID();
						tickBow = 0.0f;
						AtackBow = false;
						changeY = 0.0f;
						changeX = 0.0f;
						slowWalk = false;
					}

                    if(mWorld->invAm[i] > 0)
                    {
                        mWorld->DropThisNoAlign(mWorld->invId[i],mWorld->invAm[i],mWorld->invSt[i],Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y-0.25f,fppCam->m_vPosition.z),dropVelocity);

                        mWorld->invAm[i] = -1;
                        mWorld->invSt[i] = 0;
                        mWorld->invId[i] = -1;
                    }
                }
            }
			
			if(mWorld->mId != -1)
            {
                Vector3 dropVelocity = Vector3(0,0,0);

                dropVelocity.x = (-15+rand()%30)*0.1f;
                dropVelocity.y = 3.0f;
                dropVelocity.z = (-15+rand()%30)*0.1f;

                mWorld->DropThisNoAlign(mWorld->mId,mWorld->mAm,mWorld->mSt,Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y-0.25f,fppCam->m_vPosition.z),dropVelocity);

                mWorld->mId = -1;
                mWorld->mAm = 0;
                mWorld->mSt= -1;
            }
			
			if(mWorld->invSlot2Id != -1)
            {
                Vector3 dropVelocity = Vector3(0,0,0);

                dropVelocity.x = (-15+rand()%30)*0.1f;
                dropVelocity.y = 3.0f;
                dropVelocity.z = (-15+rand()%30)*0.1f;

                mWorld->DropThisNoAlign(mWorld->invSlot2Id,mWorld->invSlot2Am,mWorld->invSlot2St,Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y-0.25f,fppCam->m_vPosition.z),dropVelocity);

                mWorld->invSlot2Id = -1;
                mWorld->invSlot2St = 0;
                mWorld->invSlot2Am = -1;
            }

            dieFactor = 0;
        }
    }
}


void StatePlay::Update(StateManager* sManager)
{
    if(mWorld->armorAm[0] <= 0)
    {
        mWorld->armorId[0] = 324;
        mWorld->armorAm[0] = -1;
        mWorld->armorSt[0] = false;
    }
    if(mWorld->armorAm[1] <= 0)
    {
        mWorld->armorId[1] = 325;
        mWorld->armorAm[1] = -1;
        mWorld->armorSt[1] = false;
    }
    if(mWorld->armorAm[2] <= 0)
    {
        mWorld->armorId[2] = 326;
        mWorld->armorAm[2] = -1;
        mWorld->armorSt[2] = false;
    }
    if(mWorld->armorAm[3] <= 0)
    {
        mWorld->armorId[3] = 327;
        mWorld->armorAm[3] = -1;
        mWorld->armorSt[3] = false;
    }
    mWorld->AP = mWorld->FetchArmorPoints(mWorld->armorId[3],mWorld->armorId[2],mWorld->armorId[1],mWorld->armorId[0]);

    if(menuState == 0)//game state
    {
		// arrow conditions
		if(tickBow >= 0.1f)
		{
			if(tickBow <= 1.4f) tickBow += dt;
			if(tickBow >= 0.9f)
			{
				// animation bow
				float speedMultiplier = 25.0f;
				float bowAnimGo = cosf((bobCiclo * speedMultiplier) - (PI / 2.0f) + PI) / 170;
				bowAnim = bowAnimGo;
			}
		}
		
		// comida
		if(eatingTick >= 0.1f)
		{
			eatingTick -= dt;
			eatSoundTimer -= dt;
			
			// condition
			if(eatingTick < 0.3f) foodEaten2 = true;
			
			// sound and particles
			if(eatSoundTimer < 0.3f)
			{
				mSoundMgr->PlayEatSound();
				eatSoundTimer = 0.5f;
				
				Vector3 rayParticleDir = fppCam->m_vView - fppCam->m_vPosition;
				rayParticleDir.normalize();

				Vector3 particlePos = fppCam->m_vPosition + (rayParticleDir * 0.38f);

				if(mParticles.size() <= 52)
				{
					for(int k = 0; k <= 5; k++) // 5 particles
					{
						Particle* FoodPart = new Particle(mWorld,"item crack",Vector3(particlePos.x,particlePos.y-0.18f,particlePos.z));
						FoodPart->var1 = mWorld->invId[27+barPosition]-250;
						mParticles.push_back(FoodPart);
					}
				}
			}
			
			// animation
			float speedMultiplier = 30.0f;
			float foodAnimFloat = cosf((bobCiclo * speedMultiplier) - (PI / 2.0f) + PI) / 30;		
			foodAnim = foodAnimFloat;
		}
		
		cubeLight = mWorld->BlockFinalLight(playerPosition.x,playerPosition.y-1,playerPosition.z) * 1.2f;
        if(cubeLight > 1.0f)
        {
            cubeLight = 1.0f;
        }

        furnaceTimes += dt;
        if(furnaceTimes >= 0.5f)
        {
            if(mWorld->mFurnaces.size() > 0)
            {
                vector<Furnace*>::iterator it;
                for(it = mWorld->mFurnaces.begin(); it != mWorld->mFurnaces.end(); ++it)
                {
                    if((*it)->fuelTime > 0)
                    {
                        (*it)->fuelTime -= 0.5f;
                        if(mWorld->GetBlock((*it)->furnaceX, (*it)->furnaceY, (*it)->furnaceZ) == FurnaceOff::getID())
                        {
                            Vector3 testPos5 = Vector3(-1,-1,-1);
                            int chunkTarget2 = -1;

                            testPos5.x = (*it)->furnaceX;
                            testPos5.y = (*it)->furnaceY;
                            testPos5.z = (*it)->furnaceZ;
                            chunkTarget2 = mWorld->getChunkId(testPos5);

                            mWorld->GetBlock((*it)->furnaceX, (*it)->furnaceY, (*it)->furnaceZ) = FurnaceOn::getID();

                            //mWorld->SetLigtSourcePosition(WorkingFurance->furnaceX,WorkingFurance->furnaceY,WorkingFurance->furnaceZ,107);
                            mWorld->UpdateLightAreaIn(testPos5);

                            mWorld->RebuildFullMeshChunk(chunkTarget2);
                            mWorld->rebuildNearestChunksForLight(chunkTarget2,testPos5);

                            fppCam->needUpdate = true;
                        }
                    }

                    if((*it)->fuelTime <= 0)
                    {
                        (*it)->fuelTime = 0.0f;
                        CheckForFurnFuel((*it));
                    }

                    if((*it)->fuelTime <= 0)
                    {
                        if(mWorld->GetBlock((*it)->furnaceX,(*it)->furnaceY,(*it)->furnaceZ) == 107)
                        {
                            Vector3 testPos5 = Vector3(-1,-1,-1);
                            int chunkTarget2 = -1;

                            testPos5.x = (*it)->furnaceX;
                            testPos5.y = (*it)->furnaceY;
                            testPos5.z = (*it)->furnaceZ;
                            chunkTarget2 = mWorld->getChunkId(testPos5);

                            mWorld->GetBlock((*it)->furnaceX,(*it)->furnaceY,(*it)->furnaceZ) = 106;

                            mWorld->RemoveLigtSourceAtPosition((*it)->furnaceX,(*it)->furnaceY,(*it)->furnaceZ,107);

                            mWorld->UpdateLightAreaIn(testPos5);

                            mWorld->RebuildFullMeshChunk(chunkTarget2);
                            mWorld->rebuildNearestChunksForLight(chunkTarget2,testPos5);

                            fppCam->needUpdate = true;
                        }
                    }

                    if((*it)->fuelTime > 0 && (*it)->working == 1)
                    {
                        (*it)->meltingTime += 0.5f;
                        if((*it)->meltingTime >= 10)
                        {
                            (*it)->meltingTime = 0;
                            (*it)->working = 0;

                            ReadyFurnSmelting((*it));
                            CheckForFurnWorking((*it));
                        }
                    }
                }
            }
            furnaceTimes -= 0.5f;
        }
		
		if(mWorld->mainAchievements.TakingInventory == 0 && tutorialTimer == -1)
        {
            tutorialTimer = 1;
        }
		
		
	
        if(mWorld->mMonsterSpawners.size() > 0)
        {
            BoundingBox playerBox = BoundingBox(Vector3(playerPosition.x - 0.15f,playerPosition.y - 1.60f,playerPosition.z - 0.15f),Vector3(playerPosition.x + 0.15f,playerPosition.y + 0.2f,playerPosition.z + 0.15f));

            vector<MonsterSpawnerEntity*>::iterator it;
            for(it = mWorld->mMonsterSpawners.begin(); it != mWorld->mMonsterSpawners.end(); ++it)
            {
                if(playerBox.intersect((*it)->actArea))
                {
                    (*it)->Update(dt);

                    if((*it)->particleDelay1 <= 0)
                    {
                         (*it)->particleDelay1 = 0.5f+(rand() % 500)/1000.0f;

                         for(int i = 0; i < 4; i++)
                         {
                            float particle_x = (*it)->GetX()+(rand()%(11)/10.0f);
                            float particle_y = (*it)->GetY()+(rand()%(11)/10.0f);
                            float particle_z = (*it)->GetZ()+(rand()%(11)/10.0f);

                            Particle* Smoke = new Particle(mWorld, "black smoke",Vector3(particle_x,particle_y,particle_z));
                            Particle* Flame = new Particle(mWorld, "flame",Vector3(particle_x,particle_y,particle_z));
                            mParticles.push_back(Smoke);
                            mParticles.push_back(Flame);
                         }
                    }
                    if((*it)->particleDelay2 <= 0)
                    {
                         (*it)->particleDelay2 = 0.5f+(rand() % 500)/1000.0f;

                         for(int i = 0; i < 6; i++)
                         {
                            float particle_x = (*it)->GetX()+(rand()%(11)/10.0f);
                            float particle_y = (*it)->GetY()+(rand()%(11)/10.0f);
                            float particle_z = (*it)->GetZ()+(rand()%(11)/10.0f);

                            Particle* Smoke = new Particle(mWorld, "black smoke",Vector3(particle_x,particle_y,particle_z));
                            Particle* Flame = new Particle(mWorld, "flame",Vector3(particle_x,particle_y,particle_z));
                            mParticles.push_back(Smoke);
                            mParticles.push_back(Flame);
                         }
                    }

                    if((*it)->ItIsTimeToSpawn() && mWorld->BlockFinalLight((*it)->GetX(),(*it)->GetY()+1,(*it)->GetZ()) < 0.6f && mWorld->mainOptions.difficult != 0)
                    {
                        (*it)->forceSpawn = false;
                        int nearbyEntityAmount = 0;

                        if((*it)->MobToSpawn() == "zombie")
                        {
                            if(mWorld->mZombies.empty() == false)
                            {
                                for(int i = 0; i < mWorld->mZombies.size(); i++)
                                {
                                    if(nearbyEntityAmount == 4)
                                    {
                                        break;
                                    }
                                    Zombie* TestMob = mWorld->mZombies[i];
                                    if(TestMob->bBox.intersect((*it)->actArea))
                                    {
                                        nearbyEntityAmount ++;
                                    }
                                }
                            }

                            if(nearbyEntityAmount < 4)
                            {
                                int count0 = (*it)->MobCountToSpawn();
                                for(int i = 0; i < count0; i++)
                                {
                                    float spawn_x = (*it)->GetX()-2+(rand()%2)*4;
                                    float spawn_z = (*it)->GetZ()-2+(rand()%2)*4;
                                    spawn_x += 0.5f;
                                    spawn_z += 0.5f;

                                    float spawn_y = mWorld->groundHeight(spawn_x+0.5f,(*it)->GetY()+1,spawn_z+0.5f)+1.2f;

                                    mWorld->SpawnZombie((*it)->GetX()-1+rand()%3,(*it)->GetY()+1,(*it)->GetZ()-1+rand()%3);
                                }
                            }
                        }
						
						/*if((*it)->MobToSpawn() == "cavespider")
                        {
                            if(mWorld->mSpidercaves.empty() == false)
                            {
                                for(int i = 0; i < mWorld->mSpidercaves.size(); i++)
                                {
                                    if(nearbyEntityAmount == 4)
                                    {
                                        break;
                                    }
                                    Spidercave* TestMob = mWorld->mSpidercaves[i];
                                    if(TestMob->bBox.intersect((*it)->actArea))
                                    {
                                        nearbyEntityAmount ++;
                                    }
                                }
                            }

                            if(nearbyEntityAmount < 4)
                            {
                                int count0 = (*it)->MobCountToSpawn();
                                for(int i = 0; i < count0; i++)
                                {
                                    float spawn_x = (*it)->GetX()+1;
                                    float spawn_z = (*it)->GetZ()+1;
                                    spawn_x += 0.5f;
                                    spawn_z += 0.5f;

                                    float spawn_y = mWorld->groundHeight(spawn_x+0.5f,(*it)->GetY()+1,spawn_z+0.5f)+1.2f;

                                    mWorld->SpawnSpidercave((*it)->GetX()+1,(*it)->GetY()+1,(*it)->GetZ()+1);
                                }
                            }
                        }*/
                    }
                }
            }
        }

        if(sleepTime > 0.0f) sleepTime -= dt;
        if(sleepTime < 0.1f && sleepTime > 0.0f)
        {
            Vector3 previousPosition = mWorld->playerSpawnPointPosition;

            playerPosition.x = previousPosition.x;
            playerPosition.y = previousPosition.y;
            playerPosition.z = previousPosition.z;

            mWorld->UpdatePlayerZoneBB(playerPosition);
            mWorld->updatePlayerPosition(playerPosition);
            fppCam->PositionCamera(playerPosition.x,playerPosition.y,playerPosition.z, playerPosition.x,playerPosition.y,playerPosition.z-5.0f, 0.0f,1.0f,0.0f);
            fppCam->RotateView(0,0,90,0);
            fppCam->upDownAngle = 0;
            fppCam->horAngle = 270;
			
            sleepTime = 0.0f;
            sleepMessageType = 0;
            mWorld->SetWorldTime(9);
            mWorld->brightFactor = 0.0f;
            mWorld->mainStatistics.daysInGame++;
            mWorld->RebuildVisibleChunks();
			
			if(mWorld->worldWeather->GetWeatherType() == 1)
			{
				mWorld->worldWeather->SetWeatherType(0);
				mWorld->worldWeather->SetWeatherDuration(500+rand()%5500);
			}
        }

		if(mWorld->currentDimension == 0)
		{
			if (mWorld->skyTime >= 100 && mWorld->skyTime <= 150) // morning
			{
				mWorld->brightFactor = (mWorld->skyTime - 100.0f)/50.0f;
			}
			if (mWorld->skyTime >= 146 && mWorld->skyTime <= 249) // noon
			{
				mWorld->brightFactor = 1.0f;
			}
			if (mWorld->skyTime >= 250 && mWorld->skyTime <= 300) // sunset
			{
				mWorld->brightFactor = (300.0f - mWorld->skyTime)/50.0f;
			}
			if (mWorld->skyTime >= 300 && mWorld->skyTime <= 460) // night
			{
				mWorld->brightFactor = 0.0f;
			}

			if (mWorld->skyTime >= 101 && mWorld->skyTime <= 116)
			{
				mWorld->dawnSunsetFactor = (mWorld->skyTime - 101)/18.0f;
			}
			if (mWorld->skyTime >= 125 && mWorld->skyTime <= 139)
			{
				mWorld->dawnSunsetFactor = (139 - mWorld->skyTime)/18.0f;
			}
			if (mWorld->skyTime > 134 && mWorld->skyTime < 240)
			{
				mWorld->dawnSunsetFactor = 0.0f;
			}

			if (mWorld->skyTime >= 265 && mWorld->skyTime <= 288)
			{
				mWorld->dawnSunsetFactor = (mWorld->skyTime - 265)/18.0f;
			}
			if (mWorld->skyTime >= 291 && mWorld->skyTime <= 306)
			{
				mWorld->dawnSunsetFactor = (306 - mWorld->skyTime)/18.0f;
			}
			if (mWorld->skyTime > 306)
			{
				mWorld->dawnSunsetFactor = 0.0f;
			}

			if(mWorld->dawnSunsetFactor > 1.0f)
			{
				mWorld->dawnSunsetFactor = 1.0f;
			}
		}else{
			mWorld->SetWorldTime(10);
		}

        if (anim[0] == 1)
        {
            if (changeY < 0.2f)
            {
                changeY += dt*0.9f;
            }
            if (changeY >= 0.0f)
            {
                anim[0] = 0;
                changeY = 0.0f;
				changeX = 0.0f;
            }
        }
		
        animSpeed = dt*3.7*PI;
        if(animGo == true)
        {
            /*if(animDest < PI)
            {
                animDest += animSpeed;
            }
            if(animDest >= PI)
            {
                animGo = false;
                animDest = 0;
            }*/
			{
				animationTime += dt * animationSpeed;
				if (animationTime >= 1.0f) {
					animationTime = 0.0f;// animaciones
					currentState++;
					
					// Si llegamos al final, volvemos a idle y detenemos la animación
					if (currentState >= 8) {
						currentState = 0;
						animGo = false;
					}
				}
			}
        }

        if(playerVelocity.y != 0.0f)
        {
            fppCam->needUpdate = true;
        }

        if(fppCam->needUpdate)
        {
            showCube = false;

            //show pick cube
            Vector3 rayDir = fppCam->m_vView - fppCam->m_vPosition;
            rayDir.normalize();

            //we take position and view vector
            Vector3 testPos ;

            // collider
            BoundingBox collider = mWorld->blockTypes[mWorld->GetBlock(testPos.x,testPos.y,testPos.z)].collideBox;
            BoundingBox testBox = BoundingBox(testPos.x+collider.min.x, testPos.y+collider.min.y, testPos.z+collider.min.z, testPos.x+collider.max.x, testPos.y+collider.max.y, testPos.z+collider.max.z);

            //moving slowly to the target
            for(float i = 0; i < 5.25f; i+=0.1f)
            {
                testPos = fppCam->m_vPosition + (rayDir * i);

                collider = mWorld->blockTypes[mWorld->GetBlock(testPos.x,testPos.y,testPos.z)].collideBox;
                testBox = BoundingBox(floorf(testPos.x)+0.5f+collider.min.x, floorf(testPos.y)+0.5f+collider.min.y, floorf(testPos.z)+0.5f+collider.min.z, floorf(testPos.x)+0.5f+collider.max.x, floorf(testPos.y)+0.5f+collider.max.y, floorf(testPos.z)+0.5f+collider.max.z);

                //check if we touching something
                if(mWorld->BlockEditable(testPos.x,testPos.y,testPos.z) && testBox.contains(testPos) == true)
                {
                    //if yes then show pick cube
                    cubePos.x = (int)testPos.x + 0.5f;
                    cubePos.y = (int)testPos.y + 0.5f;
                    cubePos.z = (int)testPos.z + 0.5f;

                    showCube = true;
                    break;
                }
            }
        }

        int soundBlockType = -1;

        //RenderManager::InstancePtr()

        //update player position
        if(dt < 0.1f)
        {
            /// player timers
            musicTime -= dt;
            if (musicTime < 0.0f)
            {
                musicTime = 300.0f;
                if(mWorld->mainOptions.music == true)
                {
					if(mWorld->currentDimension == 0)
					{
						musicTime = mSoundMgr->PlayRandomAmbient();
					}
					else
					{
						musicTime = mSoundMgr->PlayRandomHell();
					}
                }
            }

            cloudsOffset += dt/1500.0f;
            if(cloudsOffset >= 2.0f)
            {
                cloudsOffset -= 2.0f;
            }

            { // nearest chunk update
                tickChunk += dt;

                if (tickChunk >= 10.0f)
                {
                    chunkId = mWorld->getChunkId(playerPosition);
                    mWorld->UpdateChunkBlocks(chunkId);

                    mWorld->RebuildFullMeshChunk(chunkId);
                    tickChunk -= 10.0f;
                }
            }
			
			// ### creative ### //

			if(mWorld->gameModeWorld != 1)
			{
				{
					// tick by wither skeleton
					
					/*tickWitherSkeletonEffect -= dt;
					if(tickWitherSkeletonEffect >= 0.1f)
					{
						
					}*/
					
					tickHunger += dt;
					if(tickHunger >= 75)
					{
						HungerTime();
						tickHunger -= 75;
					}

					tickHealth += dt;
					if(tickHealth >= 5.0f)
					{
						HealthTime();
						tickHealth -= 5.0f;
					}
					
					if(HPPoisoned == true)
					{
						tickHPveneno += dt;
						if(tickHPveneno >= 1.0f)
						{
							if(HPE <= 0) HPPoisoned = false;
							if(HPE > 0) HPE -= 1;
							if(mWorld->HP > 1) HurtPlayer(1);
							tickHPveneno -= 1.0f;
						}
					}
					else
					{
						tickHPveneno = 0.0f;
						HPPoisoned = false;
					}
					
					
					if(HungerPoisoned == true)
					{
						if(mWorld->gameModeWorld != 1) mWorld->HG -= dt/4.0f;
					}
					
					if(HungerPoisoned == true)
					{
						tickHungerPoisoned += dt;
						if(tickHungerPoisoned >= 0.0f)
						{
							if(HGP <= 0)
							{
								HungerPoisoned = false;
							}
								
							if(HGP > 0)
							{
								HGP -= 1;
							}
							tickHungerPoisoned -= 1.0f;
						}
					}
					else
					{
						HungerPoisoned = false;
					}

					tickLavaDamage += dt;
					if(tickLavaDamage >= 0.5f)
					{
						if(headInLava || footInLava)
						{
							HurtPlayer(4.0f);
							if(mWorld->armorId[0] != 324)
							{
								mWorld->armorAm[0] -= 8+rand()%8;
							}
							if(mWorld->armorId[1] != 325)
							{
								mWorld->armorAm[1] -= 8+rand()%8;
							}
							if(mWorld->armorId[2] != 326)
							{
								mWorld->armorAm[2] -= 8+rand()%8;
							}
							if(mWorld->armorId[3] != 327)
							{
								mWorld->armorAm[3] -= 8+rand()%8;
							}
						}
						tickLavaDamage -= 0.5f;
					}

					if(footInFire)
					{
						burning = true;
						mWorld->FR = 2;
					}
					
					tickFireDamage += dt;
					if(tickFireDamage >= 0.0f)
					{
						if(burning == true)
						{	
							HurtPlayer(2);
							if(mWorld->armorId[0] != 324)
							{
								mWorld->armorAm[0] -= 4+rand()%4;
							}
							if(mWorld->armorId[1] != 325)
							{
								mWorld->armorAm[1] -= 4+rand()%4;
							}
							if(mWorld->armorId[2] != 326)
							{
								mWorld->armorAm[2] -= 4+rand()%4;
							}
							if(mWorld->armorId[3] != 327)
							{
								mWorld->armorAm[3] -= 4+rand()%4;
							}
						}
						tickFireDamage -= 0.8f;
					}
					
					if(headInWater || footInWater)
					{
						burning = false;
						mWorld->FR = 0;
					}
					
					if(burning == true)
					{
						FireBurning();
					}

					//end

					if(touchingCactus)
					{
						tickCactusDamage += dt;
					}
					else
					{
						tickCactusDamage = 0.4f;
					}
					
					if(tickCactusDamage >= 0.5f)
					{
						HurtPlayer(1);

						tickCactusDamage -= 0.5f;
					}
					
					if(tickOS >= 1.0f && headInWater == 1)
					{
						OxygenTime();
						tickOS = 0;
					}

					if (headInWater == 0)
					{
						if (mWorld->OS != 10)
						{
							mWorld->OS = 10;
						}
						tickOS = 0;
					}
					else
					{
						tickOS += dt;
					}
				}
			}
			
			{
				if(hurt_time > 0) hurt_time -= dt;
				if(hurt_time <= 0) hurt = false;
			}

            /// player physics
            playerPosition = fppCam->m_vPosition;

            //gravity
            Vector3 footPosition = playerPosition + Vector3(0.0f, -mWorld->playerGrowth, 0.0f);
            Vector3 legsPosition = playerPosition + Vector3(0.0f, -mWorld->playerGrowth+0.65f, 0.0f);
            Vector3 headPosition = playerPosition + Vector3(0.0f, 0.2f, 0.0f);

            if(sleepTime <= 0.0f)
            {
				//player in portals
				if(mWorld->PlayerInHellPortal(legsPosition) && loadReady)
				{
					tickTp += dt;
					
					if(tickTp >= 6)
					{
						InHellPortal = true;
					}
				}
				else
				{
					tickTp = 0.0f;
					InHellPortal = false;
				}
				
				if(recoidShield > 0)
				{
					recoidShield -= dt;
				}
				
                //foot in water
                if(mWorld->PlayerInWater(legsPosition))
                {
                    if(footInWater == false)
                    {
                        mSoundMgr->PlaySplashSound();
                        footInWater = true;
                    }

                }
                else
                {
                    footInWater = false;
                }

                //check if head is is in the water
                if(mWorld->PlayerInWater(headPosition))
                {
                    //change gravity
                    if (playerVelocity.y > -3)
                    {
                        playerVelocity.y += (GRAVITY/3.0f) * dt;
                    }
                    else
                    {
                        playerVelocity.y = -3;
                    }
                    /*if(headInWater == false)
                    {
                        mSoundMgr->PlaySplashSound();
                        headInWater = true;
                    }*/
                    headInWater = true;
                }
                else
                {
                    headInWater = false;
                }

				//fire
                if(mWorld->PlayerInFire(legsPosition))
                {
                    footInFire = true;
                }
                else
                {
                    footInFire = false;
                }
				//CobWeb
                if(mWorld->PlayerInCobweb(legsPosition) || mWorld->PlayerInCobweb(headPosition))
                {
                    playerInCobweb = true;
                }
                else
                {
                    playerInCobweb = false;
                }
				
				if(mWorld->PlayerInLava(legsPosition))
                {
                    footInLava = true;
                }
                else
                {
                    footInLava = false;
                }
                //check if head is is in the Lava
                if(mWorld->PlayerInLava(headPosition))
                {
                    //change gravity
                    playerVelocity.y += (GRAVITY/3.0f) * dt;
                    headInLava = true;
                }
                else
                {
                    headInLava = false;
                }

                if(!headInLava && !headInWater)
                {
                    playerVelocity.y += GRAVITY * 3.4f * dt;
                }

                if(mWorld->PlayerCollisionWithLadder(playerPosition) && moving == false)
                {
                    playerVelocity.y = -CLIMBVELOCITY;
                }

                touchingCactus = false;
                if(mWorld->PlayerCollisionWithCactus(playerPosition) || mWorld->PlayerCollisionWithCactus(Vector3(playerPosition.x,playerPosition.y-1.5f,playerPosition.z)))
                {
                    touchingCactus = true;
                }

                //check if we will stand on ground
                Vector3 futureFootPosition = Vector3(footPosition.x,footPosition.y+playerVelocity.y*dt,footPosition.z);
                if(mWorld->SolidAtPointForPlayer(futureFootPosition))
                {
                    walkingOnGround = true;
                    soundBlockType = mWorld->BlockSoundAtPos(futureFootPosition);

                    // If the player is stuck in the ground, bring them out.
                    // This happens because we're standing on a block at -1.5, but stuck in it at -1.4, so -1.45 is the sweet spot.
                    if (mWorld->SolidAtPointForPlayer(futureFootPosition))
                    {
                        int blockOn = (int)(futureFootPosition.y);

                        if(mWorld->GetBlock(futureFootPosition.x,futureFootPosition.y,futureFootPosition.z) == CactusBlock::getID())
                        {
                            touchingCactus = true;
                        }

                        if(mWorld->PlayerOnHalfBlock(futureFootPosition))
                        {
                            playerPosition.y = (float)(blockOn + 1 + mWorld->playerGrowth-0.55f);
                        }
                        else if(mWorld->PlayerOnStairsBlock(futureFootPosition))
                        {
                            if(mWorld->PlayerOnHighStair(futureFootPosition))
                            {
                                playerPosition.y = (float)(blockOn + 1 + mWorld->playerGrowth-0.05f);
                            }
                            else
                            {
                                playerPosition.y = (float)(blockOn + 1 + mWorld->playerGrowth-0.55f);
                            }
                        }
                        else
                        {
                            playerPosition.y = (float)(blockOn + 1 + mWorld->playerGrowth-0.05f);
                        }
                    }

                    if(playerVelocity.y != 0.0f) /// FALL DAMAGE
                    {
                        if (!mWorld->PlayerInWater(Vector3(futureFootPosition.x,futureFootPosition.y+0.45f,futureFootPosition.z)) &&
                            !(mWorld->GetBlock(playerPosition.x,playerPosition.y-1.3f,playerPosition.z) >= Ladder1::getID() && mWorld->GetBlock(playerPosition.x,playerPosition.y-1.3f,playerPosition.z) <= Ladder4::getID()))
                        {
                            if(playerVelocity.y < -6 && rand() % 10 >= 7) // destroy soil
                            {
                                if(mWorld->GetBlock(futureFootPosition.x, futureFootPosition.y-0.25f, futureFootPosition.z) == Soil::getID() || mWorld->GetBlock(futureFootPosition.x, futureFootPosition.y-0.25f, futureFootPosition.z) == WateredSoil::getID())
                                {
                                    mWorld->GetBlock(futureFootPosition.x, futureFootPosition.y-0.25f, futureFootPosition.z) = DirtBlock::getID();
                                    if(mWorld->GetBlock(futureFootPosition.x, futureFootPosition.y+0.25f, futureFootPosition.z) != 0)
                                    {
                                        mWorld->DropThis(mWorld->BlockLoot(futureFootPosition.x, futureFootPosition.y+0.25f, futureFootPosition.z),1,true,Vector3(futureFootPosition.x, futureFootPosition.y+0.25f, futureFootPosition.z));
                                        mWorld->GetBlock(futureFootPosition.x, futureFootPosition.y+0.25f, futureFootPosition.z) = 0;
                                    }
                                    if(!mWorld->ChunksEqual(Vector3(futureFootPosition.x, futureFootPosition.y-0.25f, futureFootPosition.z), Vector3(futureFootPosition.x, futureFootPosition.y+0.25f, futureFootPosition.z)))
                                    {
                                        mWorld->RebuildFullMeshChunk(mWorld->getChunkId(Vector3(futureFootPosition.x, futureFootPosition.y-0.25f, futureFootPosition.z)));
                                        mWorld->RebuildFullMeshChunk(mWorld->getChunkId(Vector3(futureFootPosition.x, futureFootPosition.y+0.25f, futureFootPosition.z)));
                                    }
                                    else
                                    {
                                        mWorld->RebuildFullMeshChunk(mWorld->getChunkId(Vector3(futureFootPosition.x, futureFootPosition.y-0.25f, futureFootPosition.z)));
                                    }
                                }
                            }
							
							// ## creative ## //
                            if(playerVelocity.y < -12.8 && playerVelocity.y > -19)
                            {
                                mSoundMgr->PlayFallSound(playerVelocity.y);
								if(mWorld->gameModeWorld != 1)
								{
									if(mWorld->GetBlock(futureFootPosition.x, futureFootPosition.y-0.25f, futureFootPosition.z) == HayBale::getID())
									{
										HurtPlayer((playerVelocity.y*-1 - 11) / 1.4 * 0.3f);
									}
									else
									{
										HurtPlayer((playerVelocity.y*-1 - 11) / 1.4);
									}

									if(mWorld->HG > 0.2)
									{
										if(mWorld->gameModeWorld != 1) mWorld->HG -= 0.2;
									}

									if(mWorld->armorId[3] != 327) // if we have boots
									{
										mWorld->armorAm[3] -= 2;
									}
								}
                            }
                            if(playerVelocity.y < -19)
                            {
                                mSoundMgr->PlayFallSound(playerVelocity.y);
								if(mWorld->gameModeWorld != 1)
								{
									if(mWorld->GetBlock(futureFootPosition.x, futureFootPosition.y-0.25f, futureFootPosition.z) == HayBale::getID())
									{
										HurtPlayer((playerVelocity.y*-1 - 11) * 1.3f * 0.3f);
									}
									else
									{
										HurtPlayer((playerVelocity.y*-1 - 11) * 1.3f);
									}

									if(mWorld->HG > 0.3)
									{
										if(mWorld->gameModeWorld != 1) mWorld->HG -= 0.3;
									}

									if(mWorld->armorId[3] != 327) // if we have boots
									{
										mWorld->armorAm[3] -= 6;
									}
								}
                            }
                        }
                    }
                    playerVelocity.y = 0.0f;

                    //dodatkowa logika podczas stania na klocku
                    //jump
                    if(jumping)
                    {
                        if(!mWorld->SolidAtPointForPlayerHead(headPosition))
                        {
                            playerVelocity.y = 1.575f * JUMPVELOCITY;
                            walkingOnGround = false;
                            if(mWorld->gameModeWorld != 1) mWorld->HG -= (1.0f)/55.0f;
                        }
                        jumping = false;
                    }
                }
                else
                {
                    walkingOnGround = false;
                }

                // If the player has their head stuck in a block, push them down.
                Vector3 futureHeadPosition = Vector3(headPosition.x,headPosition.y+playerVelocity.y*dt,headPosition.z);
                if(mWorld->SolidAtPointForPlayerHead(futureHeadPosition))
                {
                    int blockIn = (int)(futureHeadPosition.y);
                    playerPosition.y = (float)(blockIn-0.2f); //0.15
                    playerVelocity.y = 0.0f;
                }
            }

            if(mWorld->kickedStart)
            {
				if(mWorld->gameModeWorld == 1)
				{
					mWorld->kickedStart = false;
					mWorld->kickedVeneno = 0;
					mWorld->kickedBy = 0;
					mWorld->kickedinCamara = false;
					mWorld->kickedDamage = 0;
				}
				else
				{
					if(mWorld->kickedBy == 1) // if you damaged by zombie
					{
						if(mWorld->kickedVeneno == 1)
						{
							switch(mWorld->mainOptions.difficult)
							{
								case 0:
									HPPoisoned = false;
									HPE = 0;
								break;
								case 1:
									HPPoisoned = true;
									HPE = 7;
								break;
								case 2:
									HPPoisoned = true;
									HPE = 7;
								break;
								case 3:
									HPPoisoned = true;
									HPE = 15;
								break;
							}
						}
						
						if(!shield)
						{
							walkingOnGround = false;
							playerVelocity.y = 0.9f * JUMPVELOCITY;
						}
						mWorld->kickedTimer = 0.5f;
						fppCam->needUpdate = true;
						
						if(shield == false)
						{
							switch(mWorld->mainOptions.difficult)
							{
							case 0: // peaceful
								HurtPlayerConsiderArmor(0, mWorld->kickedinCamara);
							break;
							case 1: // easy
								HurtPlayerConsiderArmor(mWorld->kickedDamage-1, mWorld->kickedinCamara);
							break;
							case 2: // normal
								HurtPlayerConsiderArmor(mWorld->kickedDamage,mWorld->kickedinCamara);
							break;
							case 3: // hard
								HurtPlayerConsiderArmor(mWorld->kickedDamage, mWorld->kickedinCamara);
							break;
							}
							
							if(mWorld->armorId[0] != 324)
							{
								mWorld->armorAm[0] -= 1+rand()%3;
							}
							if(mWorld->armorId[1] != 325)
							{
								mWorld->armorAm[1] -= 1+rand()%4;
							}
							if(mWorld->armorId[2] != 326)
							{
								mWorld->armorAm[2] -= 1+rand()%3;
							}
							if(mWorld->armorId[3] != 327)
							{
								mWorld->armorAm[3] -= rand()%3;
							}
						}
						else
						{
							switch(mWorld->mainOptions.difficult)
							{
							case 0: // peaceful
								HurtPlayerConsiderArmor(0, mWorld->kickedinCamara);
							break;
							case 1: // easy
								HurtPlayerConsiderArmor(mWorld->kickedDamage-1, mWorld->kickedinCamara);
							break;
							case 2: // normal
								HurtPlayerConsiderArmor(mWorld->kickedDamage, mWorld->kickedinCamara);
							break;
							case 3: // hard
								HurtPlayerConsiderArmor(mWorld->kickedDamage+1, mWorld->kickedinCamara);
							break;
							}
							
						}

					}
					if(mWorld->kickedBy == 2) // creeper or TNT
					{
						walkingOnGround = false;
						playerVelocity.y = 1.2f * JUMPVELOCITY;
						mWorld->kickedTimer = 0.6f;
						fppCam->needUpdate = true;
						
						if(shield == false)
						{
							switch(mWorld->mainOptions.difficult)
							{
							case 0: // peaceful
								HurtPlayerConsiderArmor(mWorld->kickedDamage*0.5f, mWorld->kickedinCamara);
							break;
							case 1: // easy
								HurtPlayerConsiderArmor(mWorld->kickedDamage*0.66f, mWorld->kickedinCamara);
							break;
							case 2: // normal
								HurtPlayerConsiderArmor(mWorld->kickedDamage, mWorld->kickedinCamara);
							break;
							case 3: // hard
								HurtPlayerConsiderArmor(mWorld->kickedDamage*1.33f, mWorld->kickedinCamara);
							break;
							}
						
							if(mWorld->armorId[0] != 324)
							{
								mWorld->armorAm[0] -= (mWorld->kickedDamage/2.0f)+rand()%6;
							}
							if(mWorld->armorId[1] != 325)
							{
								mWorld->armorAm[1] -= (mWorld->kickedDamage/1.5f)+rand()%6;
							}
							if(mWorld->armorId[2] != 326)
							{
								mWorld->armorAm[2] -= (mWorld->kickedDamage/2.0f)+rand()%4;
							}
							if(mWorld->armorId[3] != 327)
							{
								mWorld->armorAm[3] -= (mWorld->kickedDamage/2.0f)+rand()%3;
							}
						}
						else
						{
							switch(mWorld->mainOptions.difficult)
							{
							case 0: // peaceful
								HurtPlayerConsiderArmor(mWorld->kickedDamage*0.5f, mWorld->kickedinCamara);
							break;
							case 1: // easy
								HurtPlayerConsiderArmor(mWorld->kickedDamage*0.66f, mWorld->kickedinCamara);
							break;
							case 2: // normal
								HurtPlayerConsiderArmor(mWorld->kickedDamage, mWorld->kickedinCamara);
							break;
							case 3: // hard
								HurtPlayerConsiderArmor(mWorld->kickedDamage*1.33f, mWorld->kickedinCamara);
							break;
							}
						}
					}
					if(mWorld->kickedBy == 3) // Arrow
					{
						if(!shield)
						{
							walkingOnGround = false;
							playerVelocity.y = 1.2f * JUMPVELOCITY;
						}
						
						mWorld->kickedTimer = 0.6f;
						fppCam->needUpdate = true;

						if(shield == false)
						{
							switch(mWorld->mainOptions.difficult)
							{
							case 0: // peaceful
								HurtPlayerConsiderArmor(0, mWorld->kickedinCamara);
							break;
							case 1: // easy
								HurtPlayerConsiderArmor(mWorld->kickedDamage-1, mWorld->kickedinCamara);
							break;
							case 2: // normal
								HurtPlayerConsiderArmor(mWorld->kickedDamage, mWorld->kickedinCamara);
							break;
							case 3: // hard
								HurtPlayerConsiderArmor(mWorld->kickedDamage+1, mWorld->kickedinCamara);
							break;
							}
							
							if(mWorld->armorId[0] != 324)
							{
								mWorld->armorAm[0] -= (mWorld->kickedDamage/2.0f)+rand()%6;
							}
							if(mWorld->armorId[1] != 325)
							{
								mWorld->armorAm[1] -= (mWorld->kickedDamage/1.5f)+rand()%6;
							}
							if(mWorld->armorId[2] != 326)
							{
								mWorld->armorAm[2] -= (mWorld->kickedDamage/2.0f)+rand()%4;
							}
							if(mWorld->armorId[3] != 327)
							{
								mWorld->armorAm[3] -= (mWorld->kickedDamage/2.0f)+rand()%3;
							}
						}
						else
						{
							switch(mWorld->mainOptions.difficult)
							{
							case 0: // peaceful
								HurtPlayerConsiderArmor(0, mWorld->kickedinCamara);
							break;
							case 1: // easy
								HurtPlayerConsiderArmor(mWorld->kickedDamage-1, mWorld->kickedinCamara);
							break;
							case 2: // normal
								HurtPlayerConsiderArmor(mWorld->kickedDamage, mWorld->kickedinCamara);
							break;
							case 3: // hard
								HurtPlayerConsiderArmor(mWorld->kickedDamage+1, mWorld->kickedinCamara);
							break;
							}
						
							if(mWorld->kickedinCamara == true)
							{
								Arrow2* NewARR = new Arrow2(playerPosition.x,playerPosition.y,playerPosition.z);
								NewARR->SetVeloc(fppCam->upDownAngle,(fppCam->horAngle/(float)180 - 20)*PI,2.0f);	
								mArrows.push_back(NewARR);
							}
						}
					}
					mWorld->kickedStart = false;
					mWorld->kickedVeneno = 0;
					mWorld->kickedBy = 0;
					mWorld->kickedinCamara = false;
					mWorld->kickedDamage = 0;
				}
            }

			//### from creative ##//
            //update position
            if(sleepTime <= 0.0f)
            {
                if(!canFly)
                {
                    playerPosition += playerVelocity * dt;
                    // Update chunk manager with new player position
                    mWorld->updatePlayerPosition(playerPosition);
                }
                else
                {
                    playerVelocity.y = 0.0f;
                }
            }

            //collision with walls
            isWalking = false;
            Vector3 moveVector = fppCam->m_vVelocity;

            jumping = false;
			
            if(moveVector.x != 0.0f || moveVector.z != 0.0f)
            {
				if(!canFly)
				{
					if(TryToMove(Vector3(0,0,moveVector.z),dt))
					{
						isWalking = true;
					}
					else
					{
						if(mWorld->mainOptions.autoJump && !crouch)
						{
							if(jumping == false)
							{
								jumping = true;
							}
						}
					}
					if(TryToMove(Vector3(moveVector.x,0,0),dt))
					{
						isWalking = true;
					}
					else
					{
						if(mWorld->mainOptions.autoJump && !crouch)
						{
							if(jumping == false)
							{
								jumping = true;
							}
						}
					}
				}
				else
				{
					if(TryToMove(Vector3(0,moveVector.y,moveVector.z),dt))
                    {
                        isWalking = true;
                    }
                    else
                    {
                        if(mWorld->mainOptions.autoJump)
                        {
                            if(jumping == false)
                            {
                                jumping = true;
                            }
                        }
                    }
                    if(TryToMove(Vector3(moveVector.x,moveVector.y,0),dt))
                    {
                        isWalking = true;
                    }
                    else
                    {
                        if(mWorld->mainOptions.autoJump && !crouch)
                        {
                            if(jumping == false)
                            {
                                jumping = true;
                            }
                        }
                    }
				}
                
            }

            if(mWorld->kickedTimer > 0.0f)
            {
                mWorld->kickedTimer -= dt;
				
				if(!shield)
				{
					TryToMove(Vector3(sinf(mWorld->kickedAngle+PI)*0.1,0,cosf(mWorld->kickedAngle+PI)*0.1),dt);
				}
            }
            else
            {
                mWorld->kickedTimer = 0.0f;
                mWorld->kickedAngle = 0.0f;

                fppCam->needUpdate = true;
            }

            //update camera
            Vector3 delta = fppCam->m_vView - fppCam->m_vPosition;
            fppCam->m_vPosition = playerPosition;
            fppCam->m_vView = fppCam->m_vPosition + delta;
            fppCam->m_vVelocity = Vector3(0,0,0);
            fppCam->needUpdate = true;

            mWorld->UpdateWorldTime(dt);
            skyLight->UpdateLightSource(mWorld->skyTime);
            mWorld->UpdateWorldProcesses(dt);
        }

        if(fppCam->needUpdate)
        {
            mWorld->UpdatePlayerZoneBB(fppCam->m_vPosition);
        }
		
		// transicion de camara: sprint & bow
		{
			// FOV base
			float originalFov = mWorld->mainOptions.fov;
			
			// Valores de modificación
			float bowFov = originalFov - 25;   // El arco reduce el FOV
			float sprintFov = originalFov + 20; // El sprint aumenta el FOV

			// Velocidades de transición
			float fovTransitionSpeedBow = 0.05f;   // Entrada del arco (1s)
			float fovTransitionSpeedSprint = 0.2f; // Salida (0.2s)

			float targetFov = originalFov; // FOV final a aplicar
			float transitionSpeed = 0.0f;  // Me arreche de que no funcione >:c (psdt: ya funciona la solucion era tan simple :D)

			// Determinar el FOV objetivo y la velocidad de transición correcta
			if (tickBow >= 0.3f)
			{
				targetFov = bowFov;
				transitionSpeed = fovTransitionSpeedBow;
			}
			else if (sprint)
			{
				targetFov = sprintFov;
				transitionSpeed = fovTransitionSpeedSprint;
			}
			else
			{
				targetFov = originalFov;
				transitionSpeed = fovTransitionSpeedSprint; // Toda salida usa la velocidad del sprint
			}

			// Aplicar interpolación suave
			if (mRender->fovv < targetFov)
			{
				mRender->fovv += (targetFov - mRender->fovv) * transitionSpeed;
				if (mRender->fovv > targetFov) mRender->fovv = targetFov;
			}
			else if (mRender->fovv > targetFov)
			{
				mRender->fovv -= (mRender->fovv - targetFov) * transitionSpeed;
				if (mRender->fovv < targetFov) mRender->fovv = targetFov;
			}

			// Aplicar el nuevo FOV
			mRender->SetPerspective(mRender->fovv, 480.0f / 272.0f, 0.18f, 1000.0f);
		}


		// Movimiento de cámara
		float bobFactor = cosf(fppCam->upDownAngle);
		float bobSineX = (sinf(bobCycle - (PI / 2.0f) + PI) / 50) * bobFactor;
		float bobSineY = (cosf(bobCycle - (PI / 2.0f) + PI) / 30) * bobFactor;

		// Mantener el movimiento en un plano horizontal
		Vector3 localOffset(bobSineX, bobSineY, 0.0f);

		// Obtener la dirección de la vista y normalizar
		Vector3 viewDirection = fppCam->m_vView - fppCam->m_vPosition;
		viewDirection.normalize();

		// Definir un vector 'up' constante para el plano horizontal
		Vector3 fixedUp(0.0f, 1.0f, 0.0f); // Mantener el desplazamiento vertical fijo

		// Calcular el vector 'right' usando el nuevo 'fixedUp'
		Vector3 right = Vector3::cross(viewDirection, fixedUp);
		right.normalize();

		// Mantener el offset global en el plano horizontal constante
		globalOffset = right * localOffset.x + fixedUp * localOffset.y;

		if(moving) fppCam->m_vOffset = globalOffset;
		
		//walking sound & walking animation animaciones
        if(isWalking && walkingOnGround && (!footInWater || !footInLava))
        {
            float walkSoundSpeed = dt;
			if(eatingTick > 0.1f) walkSoundSpeed *= 0.2f;
			if(sprint) walkSoundSpeed *= 1.4f;		
            if(footInLava || footInWater) walkSoundSpeed *= 0.7f;
			if(headInLava || headInWater) walkSoundSpeed *= 0.5f;
			if(playerInCobweb) walkSoundSpeed *= 0.2f;
			if(crouch) walkSoundSpeed *= 0.3f;
			if(slowWalk) walkSoundSpeed *= 0.3f;
		    walkSoundAccu += walkSoundSpeed;

			if(walkSoundAccu > 0.428f || walkSoundAccu == 0.0f)
			{
				mSoundMgr->PlayWalkSound(soundBlockType);
				walkSoundAccu = 0.0f;
			}

			float animSpeed = 2.621*PI*dt;
			if(eatingTick > 0.1f) animSpeed *= 0.0f;
			if(sprint) animSpeed *= 1.4f;
			if(footInLava || footInWater) animSpeed *= 0.7f;
			if(headInLava || headInWater) animSpeed *= 0.5f;
			if(playerInCobweb) animSpeed *= 0.2f;
			if(crouch) animSpeed *= 0.0f;
			if(slowWalk) animSpeed *= 0.0f;
			
            if(bobType == 0)
            {
                if(bobCycle < PI)
                    bobCycle += animSpeed;
                else
                    bobType = 1;
            }
            else
            {
                if(bobCycle > 0)
                    bobCycle -= animSpeed;
                else
                    bobType = 0;
            }
			
			float shift_editor_y = -0.06f;
			if (crouch == false)
			{ 
				swingAnimY > shift_editor_y ? swingAnimY -= 0.30*dt : swingAnimY = shift_editor_y;
			}
			else
			{
				if (swingAnimY < 0.0f) swingAnimY += 0.10*dt;
				if (abs(swingAnimY) <= 0.001f)  swingAnimY = 0.0f;
			}
			
		}
		else
		{
			if (swingAnimY < 0.0f) swingAnimY += 0.10*dt;
			if (abs(swingAnimY) <= 0.001f)  swingAnimY = 0.0f;
			
			walkSoundAccu = 0.45f;
			
            if(bobCycle > PI/2.0f)
                bobCycle -= (bobCycle-(PI/2.0f))/3.0f;
            else
                bobCycle += ((PI/2.0f) - bobCycle)/3.0f;
			
            fppCam->m_vOffset = Vector3(0.0f,0.0,0.0f);
		}

        if(invEn == true || craft3xEn == true || chestEn == true || furnaceEn == true)
        {
            mWorld->UpdateCompassTexture((fppCam->horAngle/180.0f)*PI);
        }
        else
        {
            if(mWorld->haveCompass) // only if you have compass in bar slots, compass texture should be updated
            {
                mWorld->UpdateCompassTexture((fppCam->horAngle/180.0f)*PI);
            }
        }
    }
}


void StatePlay::Draw(StateManager* sManager)
{
    mWorld->startSkyColor = mWorld->startClearSkyColor*(1.0-mWorld->rainyColorAlpha)+mWorld->startRainySkyColor*mWorld->rainyColorAlpha;
    mWorld->endSkyColor = mWorld->endClearSkyColor*(1.0-mWorld->rainyColorAlpha)+mWorld->endRainySkyColor*mWorld->rainyColorAlpha;
    mWorld->dawnSunsetSkyColor = mWorld->dawnSunsetClearSkyColor*(1.0-mWorld->rainyColorAlpha)+mWorld->dawnSunsetRainySkyColor*mWorld->rainyColorAlpha;
    (mWorld->startSkyColor).saturate();
    (mWorld->endSkyColor).saturate();
    (mWorld->dawnSunsetSkyColor).saturate();

    mRender->SetFontStyle(0.345f,0xFFFFFFFF,0,0x00000200);

    if (mWorld->skyTime < 180)
    {
        if(fppCam->horAngle < 360 && fppCam->horAngle >= 239)
        {
            angleFactor = (fppCam->horAngle - 239)/120.0f;
        }
        else if(fppCam->horAngle >= 0 && fppCam->horAngle <= 120)
        {
            angleFactor = (120 - fppCam->horAngle)/120.0f;
        }
        else
        {
            angleFactor = 0;
        }
    }
    else
    {
        if(fppCam->horAngle < 180 && fppCam->horAngle >= 60)
        {
            angleFactor = (fppCam->horAngle - 60)/120.0f;
        }
        else if(fppCam->horAngle >= 180 && fppCam->horAngle <= 300)
        {
            angleFactor = (300 - fppCam->horAngle)/120.0f;
        }
        else
        {
            angleFactor = 0;
        }
    }
    if(angleFactor < 0.0f)
    {
        angleFactor = 0.0f;
    }
    if(angleFactor > 1.0f)
    {
        angleFactor = 1.0f;
    }

	bool needUpdate = fppCam->needUpdate;
	float nullFactor = (1.0f-mWorld->dawnSunsetFactor)+(1.0f-angleFactor);
	if(nullFactor > 1.0f)
    {
        nullFactor = 1.0f;
    }

	if(mWorld->currentDimension == 1)
	{
		mRender->StartFrame(0.51,0.08,0.08);
	}
    else if(playerPosition.y <= 48)
    {
        Vector3 color = ((mWorld->startSkyColor*mWorld->brightFactor)*nullFactor+(mWorld->dawnSunsetSkyColor*mWorld->dawnSunsetFactor*angleFactor))*(playerPosition.y/48.0f)*(playerPosition.y/48.0f);
        mRender->StartFrame(color.x,color.y,color.z);
    }
    else
    {
        Vector3 color = (mWorld->startSkyColor*mWorld->brightFactor)*nullFactor+(mWorld->dawnSunsetSkyColor*mWorld->dawnSunsetFactor*angleFactor);
        mRender->StartFrame(color.x,color.y,color.z);
    }

    if(mWorld->mainOptions.smoothLighting == 1)
    {
        sceGuShadeModel(GU_SMOOTH);
    }
    else
    {
        sceGuShadeModel(GU_FLAT);
    }
	
    if(mWorld->mainOptions.detailedSky == 1 && mWorld->currentDimension == 0)
    {
        if(playerPosition.y <= 48)
        {
            Vector3 color = ((mWorld->startSkyColor*mWorld->brightFactor)*nullFactor+(mWorld->dawnSunsetSkyColor*mWorld->dawnSunsetFactor*angleFactor))*(playerPosition.y/48.0f)*(playerPosition.y/48.0f);
            sceGuFog(mWorld->mainOptions.horizontalViewDistance * 7, mWorld->mainOptions.horizontalViewDistance * 14 + 168.0f, GU_COLOR(color.x,color.y,color.z,1.0));
        }
        else
        {
            Vector3 color = (mWorld->startSkyColor*mWorld->brightFactor)*nullFactor+(mWorld->dawnSunsetSkyColor*mWorld->dawnSunsetFactor*angleFactor);
            sceGuFog(mWorld->mainOptions.horizontalViewDistance * 7, mWorld->mainOptions.horizontalViewDistance * 14 + 168.0f, GU_COLOR(color.x,color.y,color.z,1.0));
        }
        sceGuEnable(GU_FOG);

        /// Skybox rendering
        {
            MatrixPush();
            MatrixTranslation(Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y+44,fppCam->m_vPosition.z));
            MatrixScale(Vector3(1.0f,1.0f,1.0f));

            if(playerPosition.y <= 45)
            {
                skyBox->Render(mWorld->endSkyColor*mWorld->brightFactor*(playerPosition.y/45.0f),playerPosition,fppCam->horAngle/180.0f*PI);
            }
            else
            {
                skyBox->Render(mWorld->endSkyColor*mWorld->brightFactor,playerPosition,fppCam->horAngle/180.0f*PI);
            }
            MatrixPop();
        }
        sceGuDisable(GU_FOG);

        /// StarsBox rendering
       if(mWorld->rainyColorAlpha != 1.0f)
        {
            if(mWorld->worldDayTime < 10 || mWorld->worldDayTime >= 21)
            {
                TextureManager::Instance()->SetTextureModeulate(stars);

                MatrixPush();
				
                //MatrixTranslation(Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y+fppCam->m_vOffset.y,fppCam->m_vPosition.z)); ORIGINAL
                //MatrixTranslation(Vector3(0.0f, 0.0f, 0.0f));
				//MatrixTranslation(Vector3(fppCam->m_vPosition.x - (-bobSineX),fppCam->m_vPosition.y - (-bobSineY),fppCam->m_vPosition.z - (-bobSineY))); may be
				if(moving)
				{
					MatrixTranslation(Vector3(fppCam->m_vPosition.x+globalOffset.x,fppCam->m_vPosition.y+globalOffset.y,fppCam->m_vPosition.z+globalOffset.z));
				}else{
					MatrixTranslation(Vector3(fppCam->m_vPosition.x, fppCam->m_vPosition.y, fppCam->m_vPosition.z));
				}
                MatrixScale(Vector3(1.0f,1.0f,1.0f));
				MatrixAngle(Vector3(0.0f, 0.0f, mWorld->skyTime * 1.0f));

                if(mWorld->brightFactor <= 0.05f)
                {
                    if(mWorld->starsFactor < 0.3f)
                    {
                        mWorld->starsFactor += dt*0.03f;
                    }
                    if(mWorld->starsFactor > 0.3f)
                    {
                        mWorld->starsFactor = 0.3f;
                    }
                }
                else
                {
                    if(mWorld->starsFactor > 0.0f)
                    {
                        mWorld->starsFactor -= dt*0.03f;
                    }
                    if(mWorld->starsFactor < 0.0f)
                    {
                        mWorld->starsFactor = 0.0f;
                    }
                }
				
                starsBox->Render((1.0f-mWorld->brightFactor-0.4+mWorld->starsFactor)*(1-mWorld->rainyColorAlpha));

                MatrixPop();
            }
        }


        /// Sun/moon rendering
        if(mWorld->rainyColorAlpha != 1)
        {
            MatrixColor(GU_COLOR(1.0f-mWorld->rainyColorAlpha,1.0f-mWorld->rainyColorAlpha,1.0f-mWorld->rainyColorAlpha,1.0f-mWorld->rainyColorAlpha));

            // sun
            MatrixPush();
            MatrixTranslation(Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y,fppCam->m_vPosition.z));

            TextureManager::Instance()->SetTextureModeulate(suntex);

            skyLight->Render();
            MatrixPop();

            // moon
            MatrixPush();
            MatrixTranslation(Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y,fppCam->m_vPosition.z));

            TextureManager::Instance()->SetTextureModeulate(moontex);

            skyMoonLight->UpdateLightSource(mWorld->skyTime+180.0f);
            skyMoonLight->Render();
            MatrixPop();
        }

        if(mWorld->rainyColorAlpha != 1.0f)
        {
            if(mWorld->mainOptions.fogRendering == 1) /// FOG FOR CLOUDS
            {
                if(headInWater == true)
                {
                    sceGuFog(0.0f, 15.0f, GU_COLOR(74.0f/255.0f*mWorld->brightFactor*0.6,130.0f/255.0f*mWorld->brightFactor*0.6,158.0f/255.0f*mWorld->brightFactor*0.6, 1.0f));
                }
                else
                {
                    if(playerPosition.y <= 48)
                    {
                        Vector3 color = (( mWorld->startSkyColor*mWorld->brightFactor)*nullFactor+(mWorld->dawnSunsetSkyColor*mWorld->dawnSunsetFactor*angleFactor))*(playerPosition.y/48.0f)*(playerPosition.y/48.0f);
                        sceGuFog(mWorld->mainOptions.horizontalViewDistance * 7 + 48.0f, mWorld->mainOptions.horizontalViewDistance * 14 + 122.0f, GU_COLOR(color.x,color.y,color.z,1.0));
                    }
                    else
                    {
                        Vector3 color = (mWorld->startSkyColor*mWorld->brightFactor)*nullFactor+(mWorld->dawnSunsetSkyColor*mWorld->dawnSunsetFactor*angleFactor);
                        sceGuFog(mWorld->mainOptions.horizontalViewDistance * 7 + 48.0f, mWorld->mainOptions.horizontalViewDistance * 14 + 122.0f, GU_COLOR(color.x,color.y,color.z,1.0));
                    }
                }
                sceGuEnable(GU_FOG);
            }

            // Clouds rendering
			TextureManager::Instance()->SetTextureModeulate(cloudsTex);
			MatrixColor(GU_COLOR(mWorld->brightFactor, mWorld->brightFactor, mWorld->brightFactor, 1 - mWorld->rainyColorAlpha));
			
			MatrixPush();
			MatrixTranslation(Vector3(-114, 115, -114));

			sceGuTexWrap(GU_REPEAT, GU_REPEAT);
			sceGuTexOffset(cloudsOffset, 0.0f);
			mWorld->drawClouds();
			sceGuTexWrap(GU_CLAMP, GU_CLAMP);

			MatrixPop();
			
			// Layer 2
			MatrixPush();
			MatrixTranslation(Vector3(-114, 114.75f, -114));

			sceGuTexWrap(GU_REPEAT, GU_REPEAT);
			sceGuTexOffset(cloudsOffset, 0.0f);
			mWorld->drawClouds();
			sceGuTexWrap(GU_CLAMP, GU_CLAMP);

			MatrixPop();
			
			// Layer 3
			MatrixPush();
			MatrixTranslation(Vector3(-114, 114.5f, -114));

			sceGuTexWrap(GU_REPEAT, GU_REPEAT);
			sceGuTexOffset(cloudsOffset, 0.0f);
			mWorld->drawClouds();
			sceGuTexWrap(GU_CLAMP, GU_CLAMP);

			MatrixPop();
			
			// Layer 4
			MatrixPush();
			MatrixTranslation(Vector3(-114, 114.25f, -114));

			sceGuTexWrap(GU_REPEAT, GU_REPEAT);
			sceGuTexOffset(cloudsOffset, 0.0f);
			mWorld->drawClouds();
			sceGuTexWrap(GU_CLAMP, GU_CLAMP);

			MatrixPop();
			
			// Layer 5
			MatrixPush();
			MatrixTranslation(Vector3(-114, 114, -114));

			sceGuTexWrap(GU_REPEAT, GU_REPEAT);
			sceGuTexOffset(cloudsOffset, 0.0f);
			mWorld->drawClouds();
			sceGuTexWrap(GU_CLAMP, GU_CLAMP);

			MatrixPop();
			
			// Layer 6
			MatrixPush();
			MatrixTranslation(Vector3(-114, 113.75f, -114));

			sceGuTexWrap(GU_REPEAT, GU_REPEAT);
			sceGuTexOffset(cloudsOffset, 0.0f);
			mWorld->drawClouds();
			sceGuTexWrap(GU_CLAMP, GU_CLAMP);

			MatrixPop();
			
			// Layer 7
			MatrixPush();
			MatrixTranslation(Vector3(-114, 113.5f, -114));

			sceGuTexWrap(GU_REPEAT, GU_REPEAT);
			sceGuTexOffset(cloudsOffset, 0.0f);
			mWorld->drawClouds();
			sceGuTexWrap(GU_CLAMP, GU_CLAMP);

			MatrixPop();
			
			// Layer 8
			MatrixPush();
			MatrixTranslation(Vector3(-114, 113.25f, -114));

			sceGuTexWrap(GU_REPEAT, GU_REPEAT);
			sceGuTexOffset(cloudsOffset, 0.0f);
			mWorld->drawClouds();
			sceGuTexWrap(GU_CLAMP, GU_CLAMP);

			MatrixPop();
			
			// Layer 9
			MatrixColor(GU_COLOR(mWorld->brightFactor * 0.67, mWorld->brightFactor * 0.72, mWorld->brightFactor * 0.82, 1 - mWorld->rainyColorAlpha));
			MatrixPush();		
			MatrixTranslation(Vector3(-114, 112.75, -114));

			sceGuTexWrap(GU_REPEAT, GU_REPEAT);
			sceGuTexOffset(cloudsOffset, 0.0f);
			mWorld->drawClouds();
			sceGuTexWrap(GU_CLAMP, GU_CLAMP);

			MatrixPop();
			MatrixColor(0xFFFFFFFF);
        }
    }

    if(mWorld->mainOptions.fogRendering == 1) /// FOG FOR WORLD
    {
		if(mWorld->currentDimension == 1)
		{
			float fog_start = 0.0f;
            float fog_end = mWorld->mainOptions.horizontalViewDistance * 4 + 54.75f;
            if(fog_start < 0.0f)
            {
                fog_start = 0.0f;
            }

            sceGuFog(fog_start, fog_end, GU_COLOR(0.51,0.08,0.08,1.0));
		}
        else if(headInWater == true)
        {
            sceGuFog(0.0f, 15.0f, GU_COLOR(74.0f/255.0f*mWorld->brightFactor*0.6,130.0f/255.0f*mWorld->brightFactor*0.6,158.0f/255.0f*mWorld->brightFactor*0.6, 1.0f));
        }
        else
        {
            float fog_start = 0.0f;
            float fog_end = mWorld->mainOptions.horizontalViewDistance * 14 + 54.75f;
            if(fog_start < 0.0f)
            {
                fog_start = 0.0f;
            }
            if(playerPosition.y <= 48)
            {
                Vector3 color = ((Vector3(0.8f-(mWorld->rainyColorAlpha/10.0f)*3,0.8f-(mWorld->rainyColorAlpha/10.0f)*3,0.8f-(mWorld->rainyColorAlpha/10.0f)*3)*mWorld->brightFactor)*nullFactor+(mWorld->dawnSunsetSkyColor*mWorld->dawnSunsetFactor*angleFactor))*(playerPosition.y/48.0f)*(playerPosition.y/48.0f);
                sceGuFog(fog_start, fog_end, GU_COLOR(color.x,color.y,color.z,1.0));
            }
            else
            {
                Vector3 color = (Vector3(0.8f-(mWorld->rainyColorAlpha/10.0f)*3,0.8f-(mWorld->rainyColorAlpha/10.0f)*3,0.8f-(mWorld->rainyColorAlpha/10.0f)*3)*mWorld->brightFactor)*nullFactor+(mWorld->dawnSunsetSkyColor*mWorld->dawnSunsetFactor*angleFactor);
                sceGuFog(fog_start, fog_end, GU_COLOR(color.x,color.y,color.z,1.0));
            }
        }
        sceGuEnable(GU_FOG);	// Enable fog
    }

    /// Draw world
    {
        sceGuEnable(GU_TEXTURE_2D);
        /*if(mWorld->mainOptions.newSprintOption)
        {
            TextureManager::Instance()->SetMipMaps2Textures(texture, texture_mips);
        }
        else
        {
            TextureManager::Instance()->SetTextureModeulate(texture);
        }*/	
		TextureManager::Instance()->SetTextureModeulate(texture);
        sceGumPushMatrix();
        mWorld->drawWorld(fppCam->mFrustum,needUpdate);
        sceGumPopMatrix();
        sceGuDisable(GU_TEXTURE_2D);
    }

    /// DROP
    if(mWorld->mDrops.empty() == false)
    {
        for(int d = 0; d < mWorld->mDrops.size(); d++)
        {
            if(d < mWorld->mDrops.size() && mWorld->mDrops.empty() == false)
            {
                Drop* TestDrop = mWorld->mDrops[d];

                if(menuState == 0)//game state
                {
                    TestDrop->Update(dt);
                }

                if(TestDrop->GetId() < 250)
                {
                    TextureManager::Instance()->SetTextureModeulate(texture);
                }
                else
                {
                    mWorld->ItemHaveTerrainTexture(TestDrop->GetId()) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
                }

                TestDrop->Render(fppCam->mFrustum, playerPosition, fppCam->horAngle/180.0f*PI);

                if(TestDrop->toDestroy == true)
                {
                    mWorld->DestroyDrop(d);
                    d -= 1;
                    continue;
                }

                if(TestDrop->getMe == true)
                {
                    mWorld->PutInInventory(TestDrop->GetId(),TestDrop->GetAmount(),TestDrop->GetStackable(), slotForChangeScale);
                    mSoundMgr->PlayPlopSound();
                    mWorld->DestroyDrop(d);
                    d -= 1.0;

                    if(slotForChangeScale != -1)
                    {
                        changeScale = 1.0f;
                    }
                    continue;
                }
            }
        }
    }

    if(mWorld->mTNTs.empty() == false)
    {
        TextureManager::Instance()->SetTextureModeulate(texture);
        for(int k = mWorld->mTNTs.size()-1; k >= 0; k--)
        {
            if(mWorld->mTNTs.empty() == true)
            {
                return;
            }

            TNT* TestTNT = mWorld->mTNTs[k];

            if(TestTNT != NULL) // if this TNT exists
            {
                if(TestTNT->toDestroy == false)
                {
                    if(menuState == 0)//game state
                    {
                        TestTNT->Update(dt);
                        int time = TestTNT->timeToExplode*100;
                        if(time % 4 == 0 && rand()%10 <= 6 && time > 40 && TestTNT->ignitedByPlayer)
                        {

                            Particle* Smoke = new Particle(mWorld,"smoke",Vector3(TestTNT->position.x+(-0.1f+(rand()%10)/100.0f),TestTNT->position.y+0.60f,TestTNT->position.z+(-0.1f+(rand()%10)/100.0f)));
                            Smoke->SetVelocity(Vector3(0,1.5f+(rand()%10)/10.0f,0));
                            Smoke->SetScale(0.1f+(rand()%10)/100.0f);
                            Smoke->SetMaxLiveTime(1000);
                            Smoke->SetLiveTime(500,1250);
                            Smoke->SetBrightness(0.15,0.25);
                            Smoke->friction = 4.0f;

                            mParticles.push_back(Smoke);
                        }
                    }

                    TestTNT->Render();
                }

                if(TestTNT->toDestroy == true)
                {
                    for(float verAngle = 0.0f; verAngle <= PI; verAngle += PI/4.0f)
                    {
                        for(float horAngle = 0.0f; horAngle <= PI*2; horAngle += PI/2.0f)
                        {
                            if(mParticles.size() > 52)
                            {
                                continue;
                            }
                            float radius = 4.5f + (rand() % 100)/10.0f;

                            Particle* Smoke = new Particle(mWorld,"smoke",Vector3(TestTNT->position.x,TestTNT->position.y,TestTNT->position.z));
                            Smoke->SetVelocity(Vector3(mWorld->LengthDirX(horAngle,verAngle)*radius,mWorld->LengthDirY(horAngle,verAngle)*radius,mWorld->LengthDirZ(horAngle,verAngle)*radius));
                            Smoke->SetScale(0.3f+(rand()%25)/100.0f);
                            Smoke->friction = 4.25f;

                            mParticles.push_back(Smoke);
                        }
                    }
                    if(mParticles.size() < 64)
                    {
                        Particle* Explosion = new Particle(mWorld,"explosion",Vector3(TestTNT->position.x-1.2f,TestTNT->position.y-1.2f,TestTNT->position.z));
                        Particle* Explosion2 = new Particle(mWorld,"explosion",Vector3(TestTNT->position.x+1.2f,TestTNT->position.y+1.2f,TestTNT->position.z));
                        Particle* Explosion3 = new Particle(mWorld,"explosion",Vector3(TestTNT->position.x,TestTNT->position.y-1.2f,TestTNT->position.z-1.2f));
                        Particle* Explosion4 = new Particle(mWorld,"explosion",Vector3(TestTNT->position.x,TestTNT->position.y+1.2f,TestTNT->position.z+1.2f));
                        Particle* Explosion5 = new Particle(mWorld,"explosion",Vector3(TestTNT->position.x,TestTNT->position.y,TestTNT->position.z));
                        mParticles.push_back(Explosion);
                        mParticles.push_back(Explosion2);
                        mParticles.push_back(Explosion3);
                        mParticles.push_back(Explosion4);
                        mParticles.push_back(Explosion5);
                    }

                    mWorld->DestroyTNTentity(k);
                    if(mWorld->mTNTs.size() <= 16)
                    {
                        mSoundMgr->PlayTNTSound();
                    }
                }
            }
        }
    }

    /// ZOMBIE
    if(mWorld->mZombies.empty() == false)
    {
        for(int d = 0; d < mWorld->mZombies.size(); d++)
        {
            if(d < mWorld->mZombies.size() && mWorld->mZombies.empty() == false)
            {
                Zombie* TestZombie = mWorld->mZombies[d];

                if(menuState == 0)//game state
                {
                    TestZombie->Update(mWorld, playerPosition, dt);
                }
                TestZombie->Render(fppCam->mFrustum, dt);

                if(TestZombie->playHurtSound)
                {
                    mSoundMgr->PlayZombieHurtSound(TestZombie->FastDistanceToPlayer());
                    TestZombie->playHurtSound = false;
                }

                if(TestZombie->playSaySound)
                {
                    mSoundMgr->PlayZombieSaySound(TestZombie->FastDistanceToPlayer());
                    TestZombie->playSaySound = false;
                }

                if(TestZombie->killed == true)
                {
                    if(TestZombie->playDieSound)
                    {
                        mSoundMgr->PlayZombieDieSound(TestZombie->FastDistanceToPlayer());
                        TestZombie->playDieSound = false;
                    }
                }

                if(TestZombie->toDestroy == true || (TestZombie->killed == true && TestZombie->deathTimer <= 0.0f))
                {
                    if(TestZombie->killed == true)
                    {
                        if(TestZombie->lastKickType != 2) // kicked by player or other death
                        {
                            int rfAmount = rand() % 3;
                            if(rfAmount != 0)
                            {
                                mWorld->DropThis(RottenFlesh::getID(),rfAmount,true,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }

                            // rare drop
                            if(rand() % 100 <= 2)
                            {
                                mWorld->DropThis(IronBar::getID(),1,true,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }
                            if(rand() % 100 <= 3)
                            {
                                mWorld->DropThis(Potato::getID(),1,true,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }
                            if(rand() % 100 <= 3)
                            {
                                mWorld->DropThis(Carrot::getID(),1,true,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }
                            // end

                            if(TestZombie->helmetId != -1 && rand() % 4 <= 2)
                            {
                                mWorld->DropThis(TestZombie->helmetId,30+rand()%20,false,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }
                            if(TestZombie->chestplateId != -1 && rand() % 4 <= 2)
                            {
                                mWorld->DropThis(TestZombie->chestplateId,30+rand()%20,false,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }
                            if(TestZombie->leggingsId != -1 && rand() % 4 <= 2)
                            {
                                mWorld->DropThis(TestZombie->leggingsId,30+rand()%20,false,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }
                            if(TestZombie->bootsId != -1 && rand() % 4 <= 2)
                            {
                                mWorld->DropThis(TestZombie->bootsId,30+rand()%20,false,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }
                        }
                        else // killed by explosion
                        {
                            mWorld->DropThis(Bone::getID(),1,true,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            mWorld->DropThis(Bone::getID(),1,true,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            if(rand()%3 == 0)
                            {
                                mWorld->DropThis(Bone::getID(),1,true,Vector3(TestZombie->position.x,TestZombie->position.y+0.3f,TestZombie->position.z));
                            }
                        }
                    }

                    for(int k = 0; k <= 7; k++)
                    {
                        Particle* Smoke = new Particle(mWorld, "smoke",Vector3(TestZombie->position.x-0.4+(rand()%9/10.0f),TestZombie->position.y+0.2f+(rand()%7/5.0f),TestZombie->position.z-0.4+(rand()%9/10.0f)));
                        mParticles.push_back(Smoke);
                    }


                    mWorld->DestroyZombie(d);
					if(TestZombie->killed == true && TestZombie->lastKickType == 1)
					{
						if(TestZombie->helmetId != -1 || TestZombie->chestplateId != -1 || TestZombie->leggingsId != -1 || TestZombie->bootsId != -1)
						{
							ExperienceSystem(5,8);
						}
						else
						{
							ExperienceSystem(2,5);
						}
					}
                    d --;
                }
            }
        }
    }
	
	// Wolf
    if(mWorld->mWolfs.empty() == false)
    {
        for(int d = 0; d < mWorld->mWolfs.size(); d++)
        {
            if(d < mWorld->mWolfs.size() && mWorld->mWolfs.empty() == false)
            {
                Wolf* TestWolf = mWorld->mWolfs[d];

                if(menuState == 0)//game state
                {
                    TestWolf->Update(mWorld, playerPosition, dt);
                }
                TestWolf->Render(fppCam->mFrustum, dt);

                if(TestWolf->playHurtSound)
                {
                    //mSoundMgr->PlayWolfHurtSound(TestWolf->FastDistanceToPlayer());
                    TestWolf->playHurtSound = false;
                }

                if(TestWolf->playSaySound)
                {
                    //mSoundMgr->PlayWolfSaySound(TestWolf->FastDistanceToPlayer());
                    TestWolf->playSaySound = false;
                }

                if(TestWolf->killed == true)
                {
                    if(TestWolf->playDieSound)
                    {
                        //mSoundMgr->PlayWolfDieSound(TestWolf->FastDistanceToPlayer());
                        TestWolf->playDieSound = false;
                    }
                }

                if(TestWolf->toDestroy == true || (TestWolf->killed == true && TestWolf->deathTimer <= 0.0f))
                {
                    if(TestWolf->killed == true)
                    {
                        if(TestWolf->lastKickType != 2) // kicked by player or other death
                        {
                            int amountOne = rand() % 2;
                            if(amountOne != 0) mWorld->DropThis(RottenFlesh::getID(),amountOne,true,Vector3(TestWolf->position.x,TestWolf->position.y+0.3f,TestWolf->position.z));
							
							int amountTwo = rand() % 2;
                            if(amountTwo != 0) mWorld->DropThis(GoldenBar::getID(),amountTwo,true,Vector3(TestWolf->position.x,TestWolf->position.y+0.3f,TestWolf->position.z));
							
							int amountThr = rand() % 1;
                            if(amountThr != 0) mWorld->DropThis(GoldenSword::getID(),amountThr,true,Vector3(TestWolf->position.x,TestWolf->position.y+0.3f,TestWolf->position.z));
                        }
                    }

                    for(int k = 0; k <= 7; k++)
                    {
                        Particle* Smoke = new Particle(mWorld, "smoke",Vector3(TestWolf->position.x-0.4+(rand()%9/10.0f),TestWolf->position.y+0.2f+(rand()%7/5.0f),TestWolf->position.z-0.4+(rand()%9/10.0f)));
                        mParticles.push_back(Smoke);
                    }

                    mWorld->DestroyWolf(d);
					if(TestWolf->killed == true && TestWolf->lastKickType == 1) ExperienceSystem(2,5);
                    d --;
                }
            }
        }
    }
	
	// Pigman Zombie
    if(mWorld->mPigmans.empty() == false)
    {
        for(int d = 0; d < mWorld->mPigmans.size(); d++)
        {
            if(d < mWorld->mPigmans.size() && mWorld->mPigmans.empty() == false)
            {
                Pigman* TestPigman = mWorld->mPigmans[d];

                if(menuState == 0)//game state
                {
                    TestPigman->Update(mWorld, playerPosition, dt);
                }
                TestPigman->Render(fppCam->mFrustum, dt);

                if(TestPigman->playHurtSound)
                {
                    mSoundMgr->PlayPigmanHurtSound(TestPigman->FastDistanceToPlayer());
                    TestPigman->playHurtSound = false;
                }

                if(TestPigman->playSaySound)
                {
                    mSoundMgr->PlayPigmanSaySound(TestPigman->FastDistanceToPlayer());
                    TestPigman->playSaySound = false;
                }

                if(TestPigman->killed == true)
                {
                    if(TestPigman->playDieSound)
                    {
                        mSoundMgr->PlayPigmanDieSound(TestPigman->FastDistanceToPlayer());
                        TestPigman->playDieSound = false;
                    }
                }

                if(TestPigman->toDestroy == true || (TestPigman->killed == true && TestPigman->deathTimer <= 0.0f))
                {
                    if(TestPigman->killed == true)
                    {
                        if(TestPigman->lastKickType != 2) // kicked by player or other death
                        {
                            int amountOne = rand() % 2;
                            if(amountOne != 0) mWorld->DropThis(RottenFlesh::getID(),amountOne,true,Vector3(TestPigman->position.x,TestPigman->position.y+0.3f,TestPigman->position.z));
							
							int amountTwo = rand() % 2;
                            if(amountTwo != 0) mWorld->DropThis(GoldenBar::getID(),amountTwo,true,Vector3(TestPigman->position.x,TestPigman->position.y+0.3f,TestPigman->position.z));
							
							int amountThr = rand() % 1;
                            if(amountThr != 0) mWorld->DropThis(GoldenSword::getID(),amountThr,true,Vector3(TestPigman->position.x,TestPigman->position.y+0.3f,TestPigman->position.z));
                        }
                    }

                    for(int k = 0; k <= 7; k++)
                    {
                        Particle* Smoke = new Particle(mWorld, "smoke",Vector3(TestPigman->position.x-0.4+(rand()%9/10.0f),TestPigman->position.y+0.2f+(rand()%7/5.0f),TestPigman->position.z-0.4+(rand()%9/10.0f)));
                        mParticles.push_back(Smoke);
                    }

                    mWorld->DestroyPigman(d);
					if(TestPigman->killed == true && TestPigman->lastKickType == 1) ExperienceSystem(2,5);
                    d --;
                }
            }
        }
    }
	
	// Wither Skeleton
    if(mWorld->mWitherSkeletons.empty() == false)
    {
        for(int d = 0; d < mWorld->mWitherSkeletons.size(); d++)
        {
            if(d < mWorld->mWitherSkeletons.size() && mWorld->mWitherSkeletons.empty() == false)
            {
                WitherSkeleton* TestWitherSkeleton = mWorld->mWitherSkeletons[d];

                if(menuState == 0)//game state
                {
                    TestWitherSkeleton->Update(mWorld, playerPosition, dt);
                }
                TestWitherSkeleton->Render(fppCam->mFrustum, dt);

                if(TestWitherSkeleton->playHurtSound)
                {
                    mSoundMgr->PlayWitherSkeletonHurtSound(TestWitherSkeleton->FastDistanceToPlayer());
                    TestWitherSkeleton->playHurtSound = false;
                }

                if(TestWitherSkeleton->killed == true)
                {
                   if(TestWitherSkeleton->playDieSound)
                    {
                        mSoundMgr->PlayWitherSkeletonHurtSound(TestWitherSkeleton->FastDistanceToPlayer());
                        TestWitherSkeleton->playDieSound = false;
                    }
                }

                if(TestWitherSkeleton->toDestroy == true || (TestWitherSkeleton->killed == true && TestWitherSkeleton->deathTimer <= 0.0f))
                {
                    if(TestWitherSkeleton->killed == true)
                    {
                        if(TestWitherSkeleton->lastKickType != 2) // kicked by player or other death
                        {
                            int amountOne = 1 + rand() % 2;
                            if(amountOne != 0) mWorld->DropThis(Coal::getID(),amountOne,true,Vector3(TestWitherSkeleton->position.x,TestWitherSkeleton->position.y+0.3f,TestWitherSkeleton->position.z));
							
							int amountTwo = rand() % 2;
                            if(amountTwo != 0) mWorld->DropThis(Bone::getID(),amountTwo,true,Vector3(TestWitherSkeleton->position.x,TestWitherSkeleton->position.y+0.3f,TestWitherSkeleton->position.z));
                        }
                    }

                    for(int k = 0; k <= 7; k++)
                    {
                        Particle* Smoke = new Particle(mWorld, "smoke",Vector3(TestWitherSkeleton->position.x-0.4+(rand()%9/10.0f),TestWitherSkeleton->position.y+0.2f+(rand()%7/5.0f),TestWitherSkeleton->position.z-0.4+(rand()%9/10.0f)));
                        mParticles.push_back(Smoke);
                    }

                    mWorld->DestroyWitherSkeleton(d);
					if(TestWitherSkeleton->killed == true && TestWitherSkeleton->lastKickType == 1) ExperienceSystem(2,5);
                    d --;
                }
            }
        }
    }
	
	
    /// Skeleton
    if(mWorld->mSkeletons.empty() == false)
    {
        for(int d = 0; d < mWorld->mSkeletons.size(); d++)
        {
            if(d < mWorld->mSkeletons.size() && mWorld->mSkeletons.empty() == false)
            {
                Skeleton* TestSkeleton = mWorld->mSkeletons[d];

                if(menuState == 0)//game state
                {
                    TestSkeleton->Update(mWorld, playerPosition, dt);
						
					if (TestSkeleton->lanzar == true)
					{
						
						TestSkeleton->lanzar = false;
						
						mSoundMgr->PlayBowSound();
						
						ArrowEn2* NewAE = new ArrowEn2(TestSkeleton->position.x,TestSkeleton->position.y,TestSkeleton->position.z);
						NewAE->SetVeloc(playerPosition.x,playerPosition.y,playerPosition.z,TestSkeleton->headAngleZ);	
						NewAE->InCamara = TestSkeleton->InCamara;
					
						mArrowEns.push_back(NewAE);
					}
                }
                TestSkeleton->Render(fppCam->mFrustum, dt);

                if(TestSkeleton->playHurtSound)
                {
                    mSoundMgr->PlaySkeletonHurtSound(TestSkeleton->FastDistanceToPlayer());
                    TestSkeleton->playHurtSound = false;
                }

                if(TestSkeleton->playSaySound)
                {
                    mSoundMgr->PlaySkeletonHurtSound(TestSkeleton->FastDistanceToPlayer());
                    TestSkeleton->playSaySound = false;
                }

                if(TestSkeleton->killed == true)
                {
                    if(TestSkeleton->playDieSound)
                    {
                        mSoundMgr->PlaySkeletonDieSound(TestSkeleton->FastDistanceToPlayer());
                        TestSkeleton->playDieSound = false;
                    }
                }

                if(TestSkeleton->toDestroy == true || (TestSkeleton->killed == true && TestSkeleton->deathTimer <= 0.0f))
                {
                    if(TestSkeleton->killed == true)
                    {
                        if(TestSkeleton->lastKickType != 2) // kicked by player or other death
                        {
							mWorld->DropThis(Bone::getID(),1+rand()%2,true,Vector3(TestSkeleton->position.x,TestSkeleton->position.y+0.3f,TestSkeleton->position.z));
							if(rand()%1 == 0)
                            {
								mWorld->DropThis(Arrow::getID(),1+rand()%2,true,Vector3(TestSkeleton->position.x,TestSkeleton->position.y+0.3f,TestSkeleton->position.z));
							}
							if(rand() % 100 <= 2)
                            {
                                mWorld->DropThis(Bow0::getID(),10+rand()%10,false,Vector3(TestSkeleton->position.x,TestSkeleton->position.y+0.3f,TestSkeleton->position.z));
                            }
                        }
                        else // killed by explosion
                        {
                            mWorld->DropThis(Bone::getID(),1,true,Vector3(TestSkeleton->position.x,TestSkeleton->position.y+0.3f,TestSkeleton->position.z));
                            if(rand() % 100 <= 2)
                            {
                                mWorld->DropThis(Bow0::getID(),1+rand()%10,false,Vector3(TestSkeleton->position.x,TestSkeleton->position.y+0.3f,TestSkeleton->position.z));
                            }
                        }
                    }

                    for(int k = 0; k <= 7; k++)
                    {
                        Particle* Smoke = new Particle(mWorld, "smoke",Vector3(TestSkeleton->position.x-0.4+(rand()%9/10.0f),TestSkeleton->position.y+0.2f+(rand()%7/5.0f),TestSkeleton->position.z-0.4+(rand()%9/10.0f)));
                        mParticles.push_back(Smoke);
                    }


                    mWorld->DestroySkeleton(d);
					if(TestSkeleton->killed == true && TestSkeleton->lastKickType == 1)
					{
						ExperienceSystem(2,5);
						mSoundMgr->PlayOrbSound();
					}
                    d --;
                }
            }
        }
    }
	
	/// SPIDER
    if(mWorld->mSpiders.empty() == false)
    {
        for(int d = 0; d < mWorld->mSpiders.size(); d++)
        {
            if(d < mWorld->mSpiders.size() && mWorld->mSpiders.empty() == false)
            {
                Spider* TestSpider = mWorld->mSpiders[d];

                if(menuState == 0)//game state
                {
                    TestSpider->Update(mWorld, playerPosition, dt);
                }
                TestSpider->Render(fppCam->mFrustum, dt);

                if(TestSpider->playHurtSound)
                {
                    mSoundMgr->PlaySpiderHurtSound(TestSpider->FastDistanceToPlayer());
                    TestSpider->playHurtSound = false;
                }

                if(TestSpider->playSaySound)
                {
                    mSoundMgr->PlaySpiderHurtSound(TestSpider->FastDistanceToPlayer());
                    TestSpider->playSaySound = false;
                }

                if(TestSpider->killed == true)
                {
                    if(TestSpider->playDieSound)
                    {
                        mSoundMgr->PlaySpiderDieSound(TestSpider->FastDistanceToPlayer());
                        TestSpider->playDieSound = false;
                    }
                }

                if(TestSpider->toDestroy == true || (TestSpider->killed == true && TestSpider->deathTimer <= 0.0f))
                {
                    if(TestSpider->killed == true)
                    {
                        if(TestSpider->lastKickType != 2) // kicked by player or other death
                        {
							mWorld->DropThis(SpiderEye::getID(),1+rand()%2,true,Vector3(TestSpider->position.x,TestSpider->position.y+0.3f,TestSpider->position.z));
							mWorld->DropThis(String::getID(),1+rand()%2,true,Vector3(TestSpider->position.x,TestSpider->position.y+0.3f,TestSpider->position.z));
                        }
                        else // killed by explosion
                        {
                            mWorld->DropThis(Bone::getID(),1,true,Vector3(TestSpider->position.x,TestSpider->position.y+0.3f,TestSpider->position.z));
                            mWorld->DropThis(Bone::getID(),1,true,Vector3(TestSpider->position.x,TestSpider->position.y+0.3f,TestSpider->position.z));
                            if(rand()%3 == 0)
                            {
                                mWorld->DropThis(Bone::getID(),1,true,Vector3(TestSpider->position.x,TestSpider->position.y+0.3f,TestSpider->position.z));
                            }
                        }
                    }

                    for(int k = 0; k <= 7; k++)
                    {
                        Particle* Smoke = new Particle(mWorld, "smoke",Vector3(TestSpider->position.x-0.4+(rand()%9/10.0f),TestSpider->position.y+0.2f+(rand()%7/5.0f),TestSpider->position.z-0.4+(rand()%9/10.0f)));
                        mParticles.push_back(Smoke);
                    }


                    mWorld->DestroySpider(d);
					if(TestSpider->killed == true && TestSpider->lastKickType == 1)
					{
						ExperienceSystem(2,5);
					}
                    d --;
                }
            }
        }
    }
	
	/// SPIDERCAVE
    if(mWorld->mSpidercaves.empty() == false)
    {
        for(int d = 0; d < mWorld->mSpidercaves.size(); d++)
        {
            if(d < mWorld->mSpidercaves.size() && mWorld->mSpidercaves.empty() == false)
            {
                Spidercave* TestSpidercave = mWorld->mSpidercaves[d];

                if(menuState == 0)//game state
                {
                    TestSpidercave->Update(mWorld, playerPosition, dt);
                }
                TestSpidercave->Render(fppCam->mFrustum, dt);

                if(TestSpidercave->playHurtSound)
                {
                    mSoundMgr->PlaySpiderHurtSound(TestSpidercave->FastDistanceToPlayer());
                    TestSpidercave->playHurtSound = false;
                }

                if(TestSpidercave->playSaySound)
                {
                    mSoundMgr->PlaySpiderHurtSound(TestSpidercave->FastDistanceToPlayer());
                    TestSpidercave->playSaySound = false;
                }

                if(TestSpidercave->killed == true)
                {
                    if(TestSpidercave->playDieSound)
                    {
                        mSoundMgr->PlaySpiderDieSound(TestSpidercave->FastDistanceToPlayer());
                        TestSpidercave->playDieSound = false;
                    }
                }

                if(TestSpidercave->toDestroy == true || (TestSpidercave->killed == true && TestSpidercave->deathTimer <= 0.0f))
                {
                    if(TestSpidercave->killed == true)
                    {
                        mWorld->DropThis(SpiderEye::getID(),1+rand()%2,true,Vector3(TestSpidercave->position.x,TestSpidercave->position.y+0.3f,TestSpidercave->position.z));
                        mWorld->DropThis(String::getID(),1+rand()%2,true,Vector3(TestSpidercave->position.x,TestSpidercave->position.y+0.3f,TestSpidercave->position.z));
                    }

                    for(int k = 0; k <= 7; k++)
                    {
                        Particle* Smoke = new Particle(mWorld, "smoke",Vector3(TestSpidercave->position.x-0.4+(rand()%9/10.0f),TestSpidercave->position.y+0.2f+(rand()%7/5.0f),TestSpidercave->position.z-0.4+(rand()%9/10.0f)));
                        mParticles.push_back(Smoke);
                    }


                    mWorld->DestroySpidercave(d);
					if(TestSpidercave->killed == true && TestSpidercave->lastKickType == 1)
					{
						ExperienceSystem(2,5);
					}
                    d --;
                }
            }
        }
    }

    /// COWS
    if(mWorld->mCows.empty() == false)
    {			
        for(int d = 0; d < mWorld->mCows.size(); d++)
        {
            if(d < mWorld->mCows.size() && mWorld->mCows.empty() == false)
            {
                Cow* TestCow = mWorld->mCows[d];

                if(menuState == 0)//game state
                {
                    TestCow->handItemId = mWorld->invId[27+barPosition];
                    TestCow->Update(mWorld, playerPosition, dt);
                }
                TestCow->Render(fppCam->mFrustum, dt);

                if(TestCow->playHurtSound)
                {
                    mSoundMgr->PlayCowHurtSound(TestCow->FastDistanceToPlayer());
                    TestCow->playHurtSound = false;
                }

                if(TestCow->playSaySound)
                {
                    mSoundMgr->PlayCowSaySound(TestCow->FastDistanceToPlayer());
                    TestCow->playSaySound = false;
                }

                if(TestCow->toDestroy == true || (TestCow->killed == true && TestCow->deathTimer < 0.0f))
                {
					
                    if(TestCow->killed == true)
                    {
                        mWorld->DropThis(RawBeef::getID(),1+rand()%2,true,Vector3(TestCow->position.x,TestCow->position.y+0.3f,TestCow->position.z));
                        mWorld->DropThis(Leather::getID(),1+rand()%2,true,Vector3(TestCow->position.x,TestCow->position.y+0.3f,TestCow->position.z));
                    }

                    for(int k = 0; k <= 7; k++)
                    {
                        Particle* Smoke = new Particle(mWorld, "smoke",Vector3(TestCow->position.x-0.5+(rand()%11/10.0f),TestCow->position.y+0.2+(rand()%4/5.0f),TestCow->position.z-0.5+(rand()%11/10.0f)));
                        k % 2 == 0 ? Smoke->SetVelocity(Vector3(-3*rand()%2,0,-3*rand()%2)) : Smoke->SetVelocity(Vector3(3*rand()%2,0,3*rand()%2));
                        mParticles.push_back(Smoke);
                    }

                    mWorld->DestroyCow(d);
					if(TestCow->killed == true && TestCow->lastKickType == 1)
					{
						ExperienceSystem(2,5);
					}
                    d --;
                }			
            }
        }
    }
	
	/// CHICKENS
    if(mWorld->mChickens.empty() == false)
    {
        for(int d = 0; d < mWorld->mChickens.size(); d++)
        {
            if(d < mWorld->mChickens.size() && mWorld->mChickens.empty() == false)
            {
                Chicken* TestChicken = mWorld->mChickens[d];

                if(menuState == 0)//game state
                {
                    TestChicken->handItemId = mWorld->invId[27+barPosition];
                    TestChicken->Update(mWorld, playerPosition, dt);
                }
                TestChicken->Render(fppCam->mFrustum, dt);

                if(TestChicken->playHurtSound)
                {
                    mSoundMgr->PlayChickenHurtSound(TestChicken->FastDistanceToPlayer());
                    TestChicken->playHurtSound = false;
                }

                if(TestChicken->playSaySound)
                {
                    mSoundMgr->PlayChickenSaySound(TestChicken->FastDistanceToPlayer());
                    TestChicken->playSaySound = false;
                }
				
                if(TestChicken->toDestroy == true || (TestChicken->killed == true && TestChicken->deathTimer < 0.0f))
                {
                    if(TestChicken->killed == true)
                    {
                        mWorld->DropThis(RawChicken::getID(),1+rand()%2,true,Vector3(TestChicken->position.x,TestChicken->position.y+0.3f,TestChicken->position.z));
						mWorld->DropThis(Feather::getID(),rand() % 2,true,Vector3(TestChicken->position.x,TestChicken->position.y+0.3f,TestChicken->position.z));
                    }

                    for(int k = 0; k <= 7; k++)
                    {
                        Particle* Smoke = new Particle(mWorld, "smoke",Vector3(TestChicken->position.x-0.5+(rand()%11/10.0f),TestChicken->position.y+0.2+(rand()%4/5.0f),TestChicken->position.z-0.5+(rand()%11/10.0f)));
                        k % 2 == 0 ? Smoke->SetVelocity(Vector3(-3*rand()%2,0,-3*rand()%2)) : Smoke->SetVelocity(Vector3(3*rand()%2,0,3*rand()%2));
                        mParticles.push_back(Smoke);
                    }

                    mWorld->DestroyChicken(d);
					if(TestChicken->killed == true && TestChicken->lastKickType == 1)
					{
						ExperienceSystem(2,5);
					}
                    d --;
                }
            }
        }
    }

    /// PIGS
    if(mWorld->mPigs.empty() == false)
    {
        for(int d = 0; d < mWorld->mPigs.size(); d++)
        {
            if(d < mWorld->mPigs.size() && mWorld->mPigs.empty() == false)
            {
                Pig* TestPig = mWorld->mPigs[d];

                if(menuState == 0)//game state
                {
                    TestPig->handItemId = mWorld->invId[27+barPosition];
                    TestPig->Update(mWorld, playerPosition, dt);
                }
                TestPig->Render(fppCam->mFrustum, dt);

                if(TestPig->playHurtSound)
                {
                    mSoundMgr->PlayPigHurtSound(TestPig->FastDistanceToPlayer());
                    TestPig->playHurtSound = false;
                }

                if(TestPig->playSaySound)
                {
                    mSoundMgr->PlayPigHurtSound(TestPig->FastDistanceToPlayer());
                    TestPig->playSaySound = false;
                }
				///PigDieSound///
				if(TestPig->killed == true)
                {
                    if(TestPig->playDieSound)
                    {
                        mSoundMgr->PlayPigDieSound(TestPig->FastDistanceToPlayer());
                        TestPig->playDieSound = false;
                    }
                }
				///end///
                if(TestPig->toDestroy == true || (TestPig->killed == true && TestPig->deathTimer < 0.0f))
                {
					
                    if(TestPig->killed == true)
                   {
                        if(TestPig->colorpig == 1){
						mWorld->DropThis(RawPorkchop::getID(),1+rand() % 2,true,Vector3(TestPig->position.x,TestPig->position.y+0.3f,TestPig->position.z));
						mWorld->DropThis(Emerald::getID(),1+rand() % 2,true,Vector3(TestPig->position.x,TestPig->position.y+0.3f,TestPig->position.z));
						}
						else{
						mWorld->DropThis(RawPorkchop::getID(),1+rand() % 2,true,Vector3(TestPig->position.x,TestPig->position.y+0.3f,TestPig->position.z));
						}
                    }

                    for(int k = 0; k <= 7; k++)
                    {
                        Particle* Smoke = new Particle(mWorld, "smoke",Vector3(TestPig->position.x-0.5+(rand()%11/10.0f),TestPig->position.y+0.2+(rand()%4/5.0f),TestPig->position.z-0.5+(rand()%11/10.0f)));
                        k % 2 == 0 ? Smoke->SetVelocity(Vector3(-3*rand()%2,0,-3*rand()%2)) : Smoke->SetVelocity(Vector3(3*rand()%2,0,3*rand()%2));
                        mParticles.push_back(Smoke);
                    }

                    mWorld->DestroyPig(d);
					if(TestPig->killed == true && TestPig->lastKickType == 1)
					{
						ExperienceSystem(2,5);
					}
                    d --;
                }
            }
        }
    }
	
	/// VILLAGERS sonido
    if(mWorld->mVillagers.empty() == false)
    {
        for(int d = 0; d < mWorld->mVillagers.size(); d++)
        {
            if(d < mWorld->mVillagers.size() && mWorld->mVillagers.empty() == false)
            {
                Villager* TestVillager = mWorld->mVillagers[d];

                if(menuState == 0)//game state
                {
                    TestVillager->handItemId = mWorld->invId[27+barPosition];
                    TestVillager->Update(mWorld, playerPosition, dt);
                }
                TestVillager->Render(fppCam->mFrustum, dt);

                if(TestVillager->playHurtSound)
                {
                    //mSoundMgr->PlayVillagerHurtSound(TestVillager->FastDistanceToPlayer());
                    TestVillager->playHurtSound = false;
                }

                if(TestVillager->playSaySound)
                {
                    //mSoundMgr->PlayVillagerHurtSound(TestVillager->FastDistanceToPlayer());
                    TestVillager->playSaySound = false;
                }
				///VillagerDieSound///
				if(TestVillager->killed == true)
                {
                    if(TestVillager->playDieSound)
                    {
                        //mSoundMgr->PlayVillagerDieSound(TestVillager->FastDistanceToPlayer());
                        TestVillager->playDieSound = false;
                    }
                }
				///end///
                if(TestVillager->toDestroy == true || (TestVillager->killed == true && TestVillager->deathTimer < 0.0f))
                {
					
                    if(TestVillager->killed == true)
					{
                      //no suelta nada lol
                    }

                    for(int k = 0; k <= 7; k++)
                    {
                        Particle* Smoke = new Particle(mWorld, "smoke",Vector3(TestVillager->position.x-0.5+(rand()%11/10.0f),TestVillager->position.y+0.2+(rand()%4/5.0f),TestVillager->position.z-0.5+(rand()%11/10.0f)));
                        k % 2 == 0 ? Smoke->SetVelocity(Vector3(-3*rand()%2,0,-3*rand()%2)) : Smoke->SetVelocity(Vector3(3*rand()%2,0,3*rand()%2));
                        mParticles.push_back(Smoke);
                    }
					
					if(TestVillager->tradder == true)
					{
						if(upEn == true)
						{
							invXPosition = 0;
							invYPosition = 0;
						}
						
						selectInvSprite->SetPosition(168+(invXPosition * 18),149+(invYPosition * 18));
						
						tradesManager.CleanUp();

						delete invVillage;
						
						TextureHelper::Instance()->UnLoadInventory();
		
						invEn = false;
						villEn = false;
						craft3xEn = false;
						furnaceEn = false;
						chestEn = false;
						upEn = false;
						slot2En = false;
						furnaceEn = false;
						chestId = -1;
						villageId = -1;
						villageProfession = 0;
						villageLvl = 0;
						villageRandom = 0;
						armorEn = false;
						
						if(mWorld->mId != -1)
						{
							Vector3 dropVelocity = Vector3(0,0,0);

							dropVelocity.x = (-15+rand()%30)*0.1f;
							dropVelocity.y = 3.0f;
							dropVelocity.z = (-15+rand()%30)*0.1f;

							mWorld->DropThisNoAlign(mWorld->mId,mWorld->mAm,mWorld->mSt,Vector3(fppCam->m_vPosition.x,fppCam->m_vPosition.y-0.25f,fppCam->m_vPosition.z),dropVelocity);

							mWorld->mId = -1;
							mWorld->mAm = 0;
							mWorld->mSt= -1;
						}

						UseChest = 0;
						UseFurnace = 0;

						mWorld->haveCompass = mWorld->HaveItemInBarSlots(Compass::getID());
					}
					
                    mWorld->DestroyVillager(d);
					if(TestVillager->killed == true && TestVillager->lastKickType == 1)
					{
						ExperienceSystem(2,5);
					}
                    d --;
                }
            }
        }
    }

    /// SHEEP
    if(mWorld->mSheeps.empty() == false)
    {
        for(int d = 0; d < mWorld->mSheeps.size(); d++)
        {
            if(d < mWorld->mSheeps.size() && mWorld->mSheeps.empty() == false)
            {
                Sheep* TestSheep = mWorld->mSheeps[d];

                if(menuState == 0)//game state
                {
                    TestSheep->handItemId = mWorld->invId[27+barPosition];
                    TestSheep->Update(mWorld, playerPosition, dt);
                }
                TestSheep->Render(fppCam->mFrustum, dt);

                if(TestSheep->playHurtSound)
                {
                    mSoundMgr->PlaySheepHurtSound(TestSheep->FastDistanceToPlayer());
                    TestSheep->playHurtSound = false;
                }

                if(TestSheep->playSaySound)
                {
                    mSoundMgr->PlaySheepHurtSound(TestSheep->FastDistanceToPlayer());
                    TestSheep->playSaySound = false;
                }

                if(TestSheep->toDestroy == true || (TestSheep->killed == true && TestSheep->deathTimer < 0.0f))
                {
                    if(TestSheep->killed == true && TestSheep->sheared == false)
                    {
                        mWorld->DropThis(BlackWoolBlock::getID()+TestSheep->GetFurColor(),1,true,Vector3(TestSheep->position.x,TestSheep->position.y+0.3f,TestSheep->position.z));
						mWorld->DropThis(RawMutton::getID(),1+rand()%2,true,Vector3(TestSheep->position.x,TestSheep->position.y+0.3f,TestSheep->position.z));
                    }

                    for(int k = 0; k <= 7; k++)
                    {
                        Particle* Smoke = new Particle(mWorld, "smoke",Vector3(TestSheep->position.x-0.5+(rand()%11/10.0f),TestSheep->position.y+0.2+(rand()%4/5.0f),TestSheep->position.z-0.5+(rand()%11/10.0f)));
                        k % 2 == 0 ? Smoke->SetVelocity(Vector3(-3*rand()%2,0,-3*rand()%2)) : Smoke->SetVelocity(Vector3(3*rand()%2,0,3*rand()%2));
                        mParticles.push_back(Smoke);
                    }

                    mWorld->DestroySheep(d);
					if(TestSheep->killed == true && TestSheep->lastKickType == 1)
					{
						ExperienceSystem(2,5);
					}
                    d --;
                }
            }
        }
    }

    /// CREEPER
    if(mWorld->mCreepers.empty() == false)
    {
        for(int d = 0; d < mWorld->mCreepers.size(); d++)
        {
            if(d < mWorld->mCreepers.size() && mWorld->mCreepers.empty() == false)
            {
                Creeper* TestCreeper = mWorld->mCreepers[d];

                if(menuState == 0)//game state
                {
                    TestCreeper->Update(mWorld, playerPosition, dt);
                }
                TestCreeper->Render(fppCam->mFrustum, dt);

                if(TestCreeper->playHurtSound)
                {
                    mSoundMgr->PlayCreeperHurtSound(TestCreeper->DistanceToPlayer());
                    TestCreeper->playHurtSound = false;
                }

                if(TestCreeper->playFuseSound)
                {
                    mSoundMgr->PlayFuseSound();
                    TestCreeper->playFuseSound = false;
                }

                if(TestCreeper->toDestroy == true || (TestCreeper->killed == true && TestCreeper->deathTimer < 0.0f))
                {
                    if(TestCreeper->killed == true)
                    {
                        if(TestCreeper->lastKickType != 2) // killed by player or other death
                        {
                            mWorld->DropThis(Gunpowder::getID(),1,true,Vector3(TestCreeper->position.x,TestCreeper->position.y+0.3f,TestCreeper->position.z));
                            mWorld->DropThis(Gunpowder::getID(),rand()%3,true,Vector3(TestCreeper->position.x,TestCreeper->position.y+0.3f,TestCreeper->position.z));
                        }
                        else
                        {
                            int drop_id = 1;
                            int disk_number = rand()%12;
                            if(disk_number <= 2)
                            {
                                drop_id = Disk1::getID() + disk_number;
                            }
                            else
                            {
                                drop_id = Disk4::getID() + disk_number-3;
                            }
                            mWorld->DropThis(drop_id,1,false,Vector3(TestCreeper->position.x,TestCreeper->position.y+0.3f,TestCreeper->position.z));
                        }
                    }

                    for(int k = 0; k <= 7; k++)
                    {
                        Particle* Smoke = new Particle(mWorld, "smoke",Vector3(TestCreeper->position.x-0.5+(rand()%11/10.0f),TestCreeper->position.y+0.2+(rand()%4/5.0f),TestCreeper->position.z-0.5+(rand()%11/10.0f)));
                        k % 2 == 0 ? Smoke->SetVelocity(Vector3(-3*rand()%2,0,-3*rand()%2)) : Smoke->SetVelocity(Vector3(3*rand()%2,0,3*rand()%2));
                        mParticles.push_back(Smoke);
                    }

                    mWorld->DestroyCreeper(d);
					if(TestCreeper->killed == true && TestCreeper->lastKickType == 1)
					{
						ExperienceSystem(2,5);
					}
                    d --;
                }
                if(TestCreeper->exploded == true)
                {
                    for(float verAngle = 0.0f; verAngle <= PI; verAngle += PI/4.0f)
                    {
                        for(float horAngle = 0.0f; horAngle <= PI*2; horAngle += PI/2.0f)
                        {
                            if(mParticles.size() > 52)
                            {
                                continue;
                            }
                            float radius = 4.5f + (rand() % 100)/10.0f;

                            Particle* Smoke = new Particle(mWorld,"smoke",Vector3(TestCreeper->position.x,TestCreeper->position.y,TestCreeper->position.z));
                            Smoke->SetVelocity(Vector3(mWorld->LengthDirX(horAngle,verAngle)*radius,mWorld->LengthDirY(horAngle,verAngle)*radius,mWorld->LengthDirZ(horAngle,verAngle)*radius));
                            Smoke->SetScale(0.3f+(rand()%25)/100.0f);
                            Smoke->friction = 4.25f;

                            mParticles.push_back(Smoke);
                        }
                    }
                    if(mParticles.size() < 64)
                    {
                        Particle* Explosion = new Particle(mWorld,"explosion",Vector3(TestCreeper->position.x-1.2f,TestCreeper->position.y-1.2f,TestCreeper->position.z));
                        Particle* Explosion2 = new Particle(mWorld,"explosion",Vector3(TestCreeper->position.x+1.2f,TestCreeper->position.y+1.2f,TestCreeper->position.z));
                        Particle* Explosion3 = new Particle(mWorld,"explosion",Vector3(TestCreeper->position.x,TestCreeper->position.y-1.2f,TestCreeper->position.z-1.2f));
                        Particle* Explosion4 = new Particle(mWorld,"explosion",Vector3(TestCreeper->position.x,TestCreeper->position.y+1.2f,TestCreeper->position.z+1.2f));
                        Particle* Explosion5 = new Particle(mWorld,"explosion",Vector3(TestCreeper->position.x,TestCreeper->position.y,TestCreeper->position.z));
                        mParticles.push_back(Explosion);
                        mParticles.push_back(Explosion2);
                        mParticles.push_back(Explosion3);
                        mParticles.push_back(Explosion4);
                        mParticles.push_back(Explosion5);
                    }

                    mSoundMgr->PlayTNTSound();

                    mWorld->DestroyCreeper(d);
                    d --;
                }
            }
        }
    }

    /// render snowballs
    if (mSnowBalls.empty() == false)
    {
        for(unsigned int i = 0; i < mSnowBalls.size(); i++)
        {
            if(i < mSnowBalls.size() && mSnowBalls.empty() == false)
            {
                TextureManager::Instance()->SetTextureModeulate(snowBall4);
                SnowBall2* UseSnowBall = mSnowBalls[i];

                if(menuState == 0)//game state
                {
                    UseSnowBall->Update(mWorld, dt);
                }

                MatrixPush();
                MatrixTranslation(Vector3(0,0,0));
                DrawSetDepthTest(true);
                DrawSetAlphaTest(true);

                UseSnowBall->Render();

                DrawSetAlphaTest(false);
                DrawSetDepthTest(false);
                MatrixPop();

                if(UseSnowBall->CheckCollision(mWorld) == true)
                {
                    if(mParticles.size() <= 52)
                    {
                        for(int k = 0; k <= 3; k++) // 4 particles
                        {
                            Particle* SnowballPart = new Particle(mWorld,"item crack",Vector3(UseSnowBall->position.x,UseSnowBall->position.y+0.1f,UseSnowBall->position.z));
                            SnowballPart->var1 = SnowBallItem::getID()-250;
                            SnowballPart->SetScale(0.06f, 0.12f);
                            mParticles.push_back(SnowballPart);
                        }
                    }

                    delete mSnowBalls[i];
                    mSnowBalls.erase(mSnowBalls.begin()+i);
                    i --;
                }
            }
        }
    }
	
	/// render ArrowEn
    if (mArrowEns.empty() == false)
    {
        for(unsigned int i = 0; i < mArrowEns.size(); i++)
        {
            if(i < mArrowEns.size() && mArrowEns.empty() == false)
            {
                TextureManager::Instance()->SetTextureModeulate(arrow4);
                ArrowEn2* UseArrowEn = mArrowEns[i];

                if(menuState == 0)//game state
                {
                    UseArrowEn->Update(mWorld, dt);
                }

                MatrixPush();
                MatrixTranslation(Vector3(0,0,0));
                DrawSetDepthTest(true);
                DrawSetAlphaTest(true);

                UseArrowEn->Render();

                DrawSetAlphaTest(false);
                DrawSetDepthTest(false);
                MatrixPop();
	
                if(UseArrowEn->CheckCollision(mWorld) == true)
                {
                    delete mArrowEns[i];
                    mArrowEns.erase(mArrowEns.begin()+i);
                    i --;
                }
				else if(UseArrowEn->Kick == true)
                {
                    delete mArrowEns[i];
                    mArrowEns.erase(mArrowEns.begin()+i);
                    i --;
                }
            }
        }
    }
	/// render arrows
    if (mArrows.empty() == false)
    {
        for(unsigned int i = 0; i < mArrows.size(); i++)
        {
            if(i < mArrows.size() && mArrows.empty() == false)
            {
                TextureManager::Instance()->SetTextureModeulate(arrow4);
                Arrow2* UseArrow = mArrows[i];

                if(menuState == 0)//game state
                {
                    UseArrow->Update(mWorld, dt);
                }

                MatrixPush();
                MatrixTranslation(Vector3(0,0,0));
                DrawSetDepthTest(true);
                DrawSetAlphaTest(true);

                UseArrow->Render();

                DrawSetAlphaTest(false);
                DrawSetDepthTest(false);
                MatrixPop();

                if(UseArrow->CheckCollision(mWorld) == true)
                {
                    if (rand() % 4 == 0)
					{
						mWorld->DropThis(Arrow::getID(),1,true,Vector3(UseArrow->position.x,UseArrow->position.y+0.3f,UseArrow->position.z));
					}
					
                    delete mArrows[i];
                    mArrows.erase(mArrows.begin()+i);
                    i --;
                }
				else if (UseArrow->CheckCollisionMob() == true)
				{
					delete mArrows[i];
                    mArrows.erase(mArrows.begin()+i);
                    i --;
				}
            }
        }
    }

    /// render particles
    if (mParticles.empty() == false)
    {
        for(unsigned int i = 0; i < mParticles.size(); i++)
        {
            if(i < mParticles.size() && mParticles.empty() == false)
            {
                Particle* TestParticle = mParticles[i];
                if(menuState == 0)//game state
                {
                    TestParticle->Update(mWorld, dt);
                }

                TestParticle->Render(fppCam->mFrustum);

                if(TestParticle->toDestroy == true)
                {
                    delete mParticles[i];
                    mParticles.erase(mParticles.begin()+i);
                    i --;
                }
            }
        }
    }

    /// render items in item frames
    if (mWorld->mItemFrames.empty() == false)
    {
        for(std::vector<ItemFrameEntity*>::size_type i = 0; i < mWorld->mItemFrames.size(); i++)
        {
            ItemFrameEntity* TestItemFrame = mWorld->mItemFrames[i];

            if(TestItemFrame->GetItem() != -1)
            {
                TestItemFrame->Render(mWorld,fppCam->mFrustum,dt);
            }
        }
    }

    if(mWorld->mainOptions.fogRendering == 1)
    {
        sceGuDisable(GU_FOG); // disable fog
    }

    /// weather effects rendering
    if(menuState == 0 || makeScreen == true)
    {
        if(mWorld->worldWeather->GetWeatherType() == 1) // if it is rain
        {
            if(mWorld->rainyColorAlpha < 1.0f)
            {
                mWorld->rainyColorAlpha += dt/3.0f;
            }
            if(mWorld->rainyColorAlpha > 1.0f)
            {
                mWorld->rainyColorAlpha = 1.0f;
            }
			
			/*tormenta -= dt;
			if(tormenta < 0.0f)
			{
				tormenta = 20+rand()%30/1.0f;
				mSoundMgr->PlayThunderSound();
			}*/

            rainSoundFrequency -= dt;
            if(rainSoundFrequency <= 0.0f)
            {
                int raindropsCount = mWorld->worldWeather->raindropsCount;
                if(raindropsCount > 18)
                {
                    raindropsCount = 18;
                }
                if(raindropsCount > 0)
                {
                    mSoundMgr->PlayRainSound((raindropsCount/20.0f)*45);
                }
                rainSoundFrequency = 1.2 + (rand()%6)/10.0f;
            }
        }
        else // clear weather
        {
            if(mWorld->rainyColorAlpha > 0.0f)
            {
                mWorld->rainyColorAlpha -= dt/8.0f;
            }
            if(mWorld->rainyColorAlpha < 0.0f)
            {
                mWorld->rainyColorAlpha = 0.0f;
            }
        }
        mWorld->worldWeather->Update(mWorld, dt);
        mWorld->worldWeather->Render(mWorld, fppCam->mFrustum, fppCam->upDownAngle, playerPosition, dt);
    }

    /// render destroy model
    if (((startDt == 1 && dStd >= 0 && dStd <= 9) || showCube == true) && makeScreen == false && sleepTime <= 0.0f)
	{
		MatrixPush();

        DrawSetDepthTest(true);
        DrawSetAlphaTest(true);
		DrawSetBlend(true);

		sceGuDepthMask(1);

		MatrixTranslation(Vector3(cubePos.x,cubePos.y,cubePos.z));
		MatrixColor(0xFFFFFFFF);

        sceGuTexFilter(GU_NEAREST,GU_NEAREST);
        TextureManager::Instance()->SetTextureModeulate(texture);

		destroyer->Update(dStd, mWorld, mWorld->GetBlock(cubePos.x,cubePos.y,cubePos.z));
		destroyer->Render(dStd);

		sceGuDepthMask(0);

		DrawSetBlend(false);
        DrawSetAlphaTest(false);
        DrawSetDepthTest(false);

		MatrixPop();
	}

	if(mWorld->mainOptions.guiDrawing == 1 && mWorld->HP > 0)
	{
		float cubeBobX = sinf(bobCycle - (PI / 2) + PI) * swingAmountX;
		float cubeBobY = cosf(bobCycle + (PI / 2) - PI) * swingAmountY;

		sceGuColor(GU_COLOR(cubeLight,cubeLight,cubeLight,1));
		
        if (sleepTime <= 0.0f)
        {
			int nextState = (currentState + 1) % 9;
			float originalFov = mWorld->mainOptions.fov;
			float fixedFov = 65.0f;
			
            if(mWorld->invId[27+barPosition] == -1)	// Render hand on the screen	//animaciones
            {
                TextureManager::Instance()->SetTextureModeulate(TextureHelper::Instance()->GetTexture(TextureHelper::Steve));
				
				sceGumMatrixMode(GU_PROJECTION);
				sceGumLoadIdentity();
				sceGumPerspective(fixedFov, 480.0f / 272.0f, 0.18f, 1000.0f);
				sceGumMatrixMode(GU_VIEW);
				sceGumLoadIdentity();
				
				// Interpolacion entre estados
				ScePspFVector3 vectorPosHand;
				vectorPosHand.x = lerp(animHandPos[currentState].x, animHandPos[nextState].x, animationTime);
				vectorPosHand.y = lerp(animHandPos[currentState].y, animHandPos[nextState].y, animationTime);
				vectorPosHand.z = lerp(animHandPos[currentState].z, animHandPos[nextState].z, animationTime);
				
				ScePspFVector3 vectorRotHand;
				vectorRotHand.x = lerp(animHandRot[currentState].x, animHandRot[nextState].x, animationTime);
				vectorRotHand.y = lerp(animHandRot[currentState].y, animHandRot[nextState].y, animationTime);
				vectorRotHand.z = lerp(animHandRot[currentState].z, animHandRot[nextState].z, animationTime);
				
				// Aplicar posicion
				ScePspFVector3 move = { 
					vectorPosHand.x + shift_x + cubeBobX, 
					vectorPosHand.y + shift_y + cubeBobY + changeY + swingAnimY + swingAnimValueY + idle_y, 
					vectorPosHand.z 
				};
				sceGumTranslate(&move);
				
				// Aplicar rotaciones interpoladas
				sceGumRotateX(vectorRotHand.x);
				sceGumRotateY(vectorRotHand.y);
				sceGumRotateZ(vectorRotHand.z);
				
				// Aplicar escala
				ScePspFVector3 scale = { 0.50f, 0.50f, 0.50f };
				sceGumScale(&scale);

				// Dibujar
				sceGuDisable(GU_DEPTH_TEST);
				sceGuDepthMask(1);
				mWorld->drawHand();
				sceGuEnable(GU_DEPTH_TEST);
				sceGuDepthMask(0);

				// Restaurar el FOV original
				sceGumMatrixMode(GU_PROJECTION);
				sceGumLoadIdentity();
				sceGumPerspective(originalFov, 480.0f / 272.0f, 0.18f, 1000.0f);

				// Volver a la matriz de modelo
				sceGumMatrixMode(GU_MODEL);
				
            }

            if(mWorld->invId[27+barPosition] < 250 && mWorld->invId[27+barPosition] != -1)	// Render blocks on the screen
            {
                TextureManager::Instance()->SetTextureModeulate(texture);
				
				sceGumMatrixMode(GU_PROJECTION);
				sceGumLoadIdentity();
				sceGumPerspective(fixedFov, 480.0f / 272.0f, 0.18f, 1000.0f);
				sceGumMatrixMode(GU_VIEW);
				sceGumLoadIdentity();
				
				// Interpolacion entre estados
				ScePspFVector3 vectorPosBlock;
				vectorPosBlock.x = lerp(animBlockPos[currentState].x, animBlockPos[nextState].x, animationTime);
				vectorPosBlock.y = lerp(animBlockPos[currentState].y, animBlockPos[nextState].y, animationTime);
				vectorPosBlock.z = lerp(animBlockPos[currentState].z, animBlockPos[nextState].z, animationTime);
				
				ScePspFVector3 vectorRotBlock;
				vectorRotBlock.x = lerp(animBlockRot[currentState].x, animBlockRot[nextState].x, animationTime);
				vectorRotBlock.y = lerp(animBlockRot[currentState].y, animBlockRot[nextState].y, animationTime);
				vectorRotBlock.z = lerp(animBlockRot[currentState].z, animBlockRot[nextState].z, animationTime);
				
				// Aplicar posicion
				ScePspFVector3 move = { 
					vectorPosBlock.x + shift_x + cubeBobX, 
					vectorPosBlock.y + shift_y + cubeBobY + changeY + swingAnimY + swingAnimValueY + idle_y, 
					vectorPosBlock.z 
				};
				sceGumTranslate(&move);
    
				// Aplicar rotaciones interpoladas
				sceGumRotateX(vectorRotBlock.x);
				sceGumRotateY(vectorRotBlock.y);
				sceGumRotateZ(vectorRotBlock.z);
				
				// Aplicar escala
				ScePspFVector3 scale = { 0.50f, 0.50f, 0.50f };
				sceGumScale(&scale);
				
				// Dibujar
				sceGuDisable(GU_DEPTH_TEST);
				sceGuDepthMask(1);
				mWorld->drawCubes(mWorld->invId[27+barPosition],cubeLight);
				sceGuEnable(GU_DEPTH_TEST);
				sceGuDepthMask(0);

				// Restaurar el FOV original
				sceGumMatrixMode(GU_PROJECTION);
				sceGumLoadIdentity();
				sceGumPerspective(originalFov, 480.0f / 272.0f, 0.18f, 1000.0f);

				// Volver a la matriz de modelo
				sceGumMatrixMode(GU_MODEL);
            }
			
            if(mWorld->invId[27+barPosition] >= 250)	// Render items on the screen
            {
                mWorld->ItemHaveTerrainTexture(mWorld->invId[27+barPosition]) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
				
				sceGumMatrixMode(GU_PROJECTION);
				sceGumLoadIdentity();
				sceGumPerspective(fixedFov, 480.0f / 272.0f, 0.18f, 1000.0f);
				sceGumMatrixMode(GU_VIEW);
				sceGumLoadIdentity();
				
				// Interpolacion entre estados
				ScePspFVector3 vectorPosItem;
				vectorPosItem.x = lerp(animItemPos[currentState].x, animItemPos[nextState].x, animationTime);
				vectorPosItem.y = lerp(animItemPos[currentState].y, animItemPos[nextState].y, animationTime);
				vectorPosItem.z = lerp(animItemPos[currentState].z, animItemPos[nextState].z, animationTime);
				
				ScePspFVector3 vectorRotItem;
				vectorRotItem.x = lerp(animItemRot[currentState].x, animItemRot[nextState].x, animationTime);
				vectorRotItem.y = lerp(animItemRot[currentState].y, animItemRot[nextState].y, animationTime);
				vectorRotItem.z = lerp(animItemRot[currentState].z, animItemRot[nextState].z, animationTime);
				
				// BOW
				if(mWorld->invId[27 + barPosition] >= 412 && mWorld->invId[27 + barPosition] <= 414)
				{
					// Aplicar posicion
					ScePspFVector3 move = { 0.204f + shift_x, -0.050f + shift_y + bowAnim, -0.380f };
					sceGumTranslate(&move);
		
					// Aplicar rotaciones interpoladas
					sceGumRotateX(0.600f);
					sceGumRotateY(-1.690f);
					sceGumRotateZ(1.400f);
				}
				else
				{
					// FOOD
					if(eatingTick > 0.3f)
					{					
						// Aplicar posicion
						ScePspFVector3 move = { 0.026f + shift_x, -0.300f + shift_y + foodAnim, -0.583f };
						sceGumTranslate(&move);
			
						// Aplicar rotaciones interpoladas
						sceGumRotateX(0.498f);
						sceGumRotateY(-0.100f);
						sceGumRotateZ(0.280f);
					}
					else
					{
						// ITEMS
						// Aplicar posicion
						ScePspFVector3 move = { 
							vectorPosItem.x + shift_x + cubeBobX, 
							vectorPosItem.y + shift_y + cubeBobY + changeY + swingAnimY + swingAnimValueY + idle_y, 
							vectorPosItem.z 
						};
						sceGumTranslate(&move);
			
						// Aplicar rotaciones interpoladas
						sceGumRotateX(vectorRotItem.x);
						sceGumRotateY(vectorRotItem.y);
						sceGumRotateZ(vectorRotItem.z);
					}
				}
				
				// Aplicar escala
				ScePspFVector3 scale = { 0.50f, 0.50f, 0.50f };
				sceGumScale(&scale);
				
				// Dibujar la mano
				sceGuDisable(GU_DEPTH_TEST);
				sceGuDepthMask(1);
				mWorld->drawHandItems(mWorld->invId[27+barPosition],cubeLight);	
				sceGuEnable(GU_DEPTH_TEST);
				sceGuDepthMask(0);

				// Restaurar el FOV original
				sceGumMatrixMode(GU_PROJECTION);
				sceGumLoadIdentity();
				sceGumPerspective(originalFov, 480.0f / 272.0f, 0.18f, 1000.0f);

				// Volver a la matriz de modelo
				sceGumMatrixMode(GU_MODEL);
            }

			if((mWorld->invSlot2Id != -1) && tickBow < 0.2f)	// Render shield
            {
                mWorld->ItemHaveTerrainTexture(mWorld->invSlot2Id) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);

                sceGumMatrixMode(GU_PROJECTION);
				sceGumLoadIdentity();
				sceGumPerspective(fixedFov, 480.0f / 272.0f, 0.18f, 1000.0f);
				sceGumMatrixMode(GU_VIEW);
				sceGumLoadIdentity();

				if(shield){
					
					// Aplicar posicion
					ScePspFVector3 move = {
						-0.109f + shift_x, 
						-0.260f + shift_y, 
						-0.406f
					};
					sceGumTranslate(&move);
					
					// Aplicar rotaciones interpoladas
					sceGumRotateX(-0.010f);
					sceGumRotateY(-0.020f);
					sceGumRotateZ(3.054f);
					
				}else{
					
					// Aplicar posicion
					ScePspFVector3 move = {
						-0.205f + cubeBobX + shift_x, 
						-0.339f + cubeBobY + shift_y + swingAnimY + swingAnimValueY + idle_y, 
						-0.372f
					};
					sceGumTranslate(&move);
					
					// Aplicar rotaciones interpoladas
					sceGumRotateX(-0.010f);
					sceGumRotateY(-0.020f);
					sceGumRotateZ(3.224f);
				}
				
                ScePspFVector3 scale = {0.5f,0.5f,0.5f};
				sceGumScale(&scale);
				
				// Dibujar la mano
				sceGuDisable(GU_DEPTH_TEST);
				sceGuDepthMask(1);
				mWorld->drawFull3DItemFixed(mWorld->invSlot2Id, true, cubeLight);
				sceGuEnable(GU_DEPTH_TEST);
				sceGuDepthMask(0);

				// Restaurar el FOV original
				sceGumMatrixMode(GU_PROJECTION);
				sceGumLoadIdentity();
				sceGumPerspective(originalFov, 480.0f / 272.0f, 0.18f, 1000.0f);

				// Volver a la matriz de modelo
				sceGumMatrixMode(GU_MODEL);
            }	
        }
		MatrixColor(0xFFFFFFFF);
	}
	MatrixColor(0xFFFFFFFF);

	/// GUI
	mRender->SetOrtho(0,0,0,0,0,0);

    if(mWorld->HP <= 0)
	{
        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);

		MatrixColor(GU_COLOR(1,1,1,0.5f));

		TextureManager::Instance()->SetTextureModeulate(red);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);

        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
	}
	
	if(tickTp > 0)
	{
        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);

		MatrixColor(GU_COLOR(1,1,1,tickTp / 6));

		TextureManager::Instance()->SetTextureModeulate(purple);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);

        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
	}

    if(hurt == true)
	{
        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);

        MatrixColor(GU_COLOR(1,1,1,hurt_time));

		TextureManager::Instance()->SetTextureModeulate(red);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);

        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
	}

	if(headInLava == 1 || footInLava == 1)
	{
        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);

        MatrixColor(GU_COLOR(1,1,1,0.7));

		TextureManager::Instance()->SetTextureModeulate(red);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);

        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
	}
	// draw dark mask
    if((invEn == 1 || craft3xEn == 1 || chestEn == 1 || menuState != 0 || furnaceEn == 1) && makeScreen == false)
    {
        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);

        MatrixColor(GU_COLOR(1,1,1,0.7));

        TextureManager::Instance()->SetTextureModeulate(black);
        advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);

        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
    }

    /*if(mWorld->rainyColorAlpha != 0.0f) // dark mask again
    {
        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);

        MatrixColor(GU_COLOR(1,1,1,mWorld->rainyColorAlpha/9.0f));

        TextureManager::Instance()->SetTextureModeulate(black);
        advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);

        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
    }*/

    if(sleepTime > 0.0f) // dark mask again
    {
        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);

        MatrixColor(GU_COLOR(1,1,1,(4.7-sleepTime)/4.8f));

        TextureManager::Instance()->SetTextureModeulate(black);
        advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);

        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
    }

    /*if(mWorld->BlockSolid(playerPosition.x,playerPosition.y,playerPosition.z))  // dark mask again
    {
        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);

        MatrixColor(GU_COLOR(1,1,1,0.9));

        TextureManager::Instance()->SetTextureModeulate(black);
        advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);

        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
    }*/

    // draw water mask
	if(headInWater)
	{
        if (GRAVITY != -4.0f)
        {
            GRAVITY = -4.0f;
        }

        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);

        MatrixColor(GU_COLOR(1,1,1,0.8));

		waterScreen->Draw();

        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
	}
	else
    {
        if (GRAVITY != -6.8f)
        {
            GRAVITY = -6.8f;
        }
    }
    // draw pumpkin mask
    if(mWorld->armorId[0] == Pumpkin3::getID())
    {
        DrawSetDepthTest(false);
        DrawSetDepthMask(true);
        DrawSetBlend(true);
        DrawPlaceTexture(true);
     //   sceGuTexFilter( GU_LINEAR, GU_LINEAR );

        MatrixColor(GU_COLOR(1,1,1,1));

		pumpkinMask->Draw();

       // sceGuTexFilter( GU_NEAREST, GU_NEAREST );
        DrawPlaceTexture(false);
        DrawSetBlend(false);
        DrawSetDepthMask(false);
        DrawSetDepthTest(true);
    }

	/// GUI
	DrawSetDepthTest(false);
	DrawSetDepthMask(true);

	DrawSetBlend(true);
	MatrixColor(GU_COLOR(1,1,1,1.0f));

	if ((invEn == false && craft3xEn == false && chestEn == false && furnaceEn == false && villEn == false && menuState == 0 && mWorld->mainOptions.guiDrawing == 1) || (makeScreen == true && mWorld->mainOptions.guiDrawing == 1))
    {
        hpAnim += dt * 5.9 * PI;
        if(hpAnim >= 10 * PI)
        {
            hpAnim = 0.0f;
        }
		
		if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
		{
			mGameMode->XPbarSprite->Draw();
			
			int EXPbarra = mWorld->EXPcount;
			mGameMode->XPprogressSprite[EXPbarra]->Draw();
		}
		
		//XPbarSprite->Draw();

		barSprite->Draw();
		
		if(mWorld->invSlot2Id != -1)
		{
			slot2Sprite->Draw();
		}
		
		//XPprogressSprite[EXPbarra]->Draw();
		
        if (menuState != 1 || makeScreen == true)
        {
            /// HP and HG RENDERING
            // draw cells
			if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
			{
				mGameMode->hpCellSpriteW->SetPosition(190,206);	//193
				mGameMode->hpCellSprite->SetPosition(190,206);
				
				if(HungerPoisoned == true)
				{
					mGameMode->hg2CellSprite->SetPosition(291,206);
				}
				else
				{
					mGameMode->hgCellSprite->SetPosition(291,206);
				}
				
				mGameMode->arCellSprite->SetPosition(190,195);
				if(hurt == true && sinf(hpAnim) > 0)
				{
					mGameMode->hpCellSpriteW->Draw();
				}
				if(hurt == false || sinf(hpAnim) <= 0)
				{
					mGameMode->hpCellSprite->Draw();
				}
				
				if(HungerPoisoned == true)
				{
					mGameMode->hg2CellSprite->Draw();
				}
				else
				{
					mGameMode->hgCellSprite->Draw();
				}
				
				if(mWorld->AP > 0)
				{
					mGameMode->arCellSprite->Draw();
				}

				for(int i = 1; i <= 10; i++)
				{
					// hearts (hp) sprites conditions
					mGameMode->hpSprite->SetPosition(146+i*8,206);
					mGameMode->hpSpriteW->SetPosition(146+i*8,206);
					mGameMode->hpHalfSprite->SetPosition(146+i*8,206);
					mGameMode->hpHalfSpriteW->SetPosition(146+i*8,206);
					
					mGameMode->hpVenenoSprite->SetPosition(146+i*8,206);
					mGameMode->hpVenenoSpriteW->SetPosition(146+i*8,206);
					mGameMode->hpVenenoHalfSprite->SetPosition(146+i*8,206);
					mGameMode->hpVenenoHalfSpriteW->SetPosition(146+i*8,206);

					mGameMode->hpHardSprite->SetPosition(146+i*8,206);
					mGameMode->hpHardHalfSprite->SetPosition(146+i*8,206);

					if(hurt == true && sinf(hpAnim) > 0)
					{
						if(last_HP > mWorld->HP)
						{
							if(i*2 >= floorf(mWorld->HP/2.0f)*2)
							{
								if(i * 2 <= ceilf(last_HP)) HPPoisoned ? mGameMode->hpVenenoSpriteW->Draw() : mGameMode->hpSpriteW->Draw();
								if(i * 2 - ceilf(last_HP) == 1) HPPoisoned ? mGameMode->hpVenenoHalfSpriteW->Draw() : mGameMode->hpHalfSpriteW->Draw();
							}
						}
					}

					if(i * 2 <= ceilf(mWorld->HP) && mWorld->HP >= 0)
					{
						if(mWorld->gameModeWorld == 2)
							HPPoisoned ? mGameMode->hpVenenoSprite->Draw() : mGameMode->hpHardSprite->Draw();
						else
							HPPoisoned ? mGameMode->hpVenenoSprite->Draw() : mGameMode->hpSprite->Draw();
					}
					if(i * 2 - ceilf(mWorld->HP) == 1 && mWorld->HP >= 0)
					{
						if(mWorld->gameModeWorld == 2)
							HPPoisoned ? mGameMode->hpVenenoHalfSprite->Draw() : mGameMode->hpHardHalfSprite->Draw();
						else
							HPPoisoned ? mGameMode->hpVenenoHalfSprite->Draw() : mGameMode->hpHalfSprite->Draw();
					}

					// hunger sprite conditions
					mGameMode->hg2Sprite->SetPosition(335-i*8,206);
					mGameMode->hg2HalfSprite->SetPosition(335-i*8,206);
					mGameMode->hgSprite->SetPosition(335-i*8,206);
					mGameMode->hgHalfSprite->SetPosition(335-i*8,206);

					if(i * 2 <= ceilf(mWorld->HG))
					{
						HungerPoisoned ? mGameMode->hg2Sprite->Draw() : mGameMode->hgSprite->Draw();
					}
					if(i * 2 - ceilf(mWorld->HG) == 1)
					{
						HungerPoisoned ? mGameMode->hg2HalfSprite->Draw() : mGameMode->hgHalfSprite->Draw();
					}

					// bubbles sprites conditions
					mGameMode->arSprite->SetPosition(146+i*8,195);
					mGameMode->arHalfSprite->SetPosition(146+i*8,195);

					if(mWorld->AP > 0)
					{
						if(i * 2 <= ceilf(mWorld->AP)) mGameMode->arSprite->Draw();
						if(i * 2 - ceilf(mWorld->AP) == 1) mGameMode->arHalfSprite->Draw();
					}

					if(headInWater)
					{
						mGameMode->bubbleSprite->SetPosition(335-i*8,195);
						if(i <= mWorld->OS) mGameMode->bubbleSprite->Draw();
					}
				}
			}

            if(mWorld->HP > 0)
            {
                DrawSetInverseColors();
                crossSprite->Draw();
                DrawSetDefaultColors();
            }

            selectSprite->Draw();
			
			/// BUTTONS
			if(mWorld->mainOptions.buttonsDrawing)
			{
				lSprite->SetPosition(10,260);
				lSprite->Draw();
				rSprite->SetPosition(40,260);
				rSprite->Draw();
				
				l2Sprite->SetPosition(175,258);
				l2Sprite->Draw();
				
				if(mWorld->invId[27+barPosition] != -1)
				{
					if(mWorld->invId[27+barPosition] < 250)
					{
						if(showCube == true)
						{
							r2Sprite->SetPosition(250,258);
							r2Sprite->Draw();
						}
					}
				}
				
				mRender->SetFontStyle(default_size,GU_COLOR(1,1,1,1),GU_COLOR(0.0f,0.0f,0.0f,1),0x00000000);
				mRender->DebugPrint(30,274,"+");
				mRender->DebugPrint(60,272,"inventory");
				
				if(mWorld->invId[27+barPosition] >= 255 && mWorld->invId[27+barPosition] <= 259)
				{
					mRender->DebugPrint(193,272,"mine & attack");
				}
				else
				{
					mRender->DebugPrint(193,272,"mine");
				}
				if(mWorld->invId[27+barPosition] != -1)
				{
					if(mWorld->invId[27+barPosition] < 250)
					{
						if(showCube == true)
						{
							mRender->DebugPrint(267,272,"place");
						}
					}
				}
			}
        }
    }
    else
    {
        if (invEn == true && craft3xEn == false)
        {
            if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
			{				
				invSprite->ConstDraw();
				/// BUTTONINV
				if(mWorld->mainOptions.buttonsDrawing)
				{
					lSprite->SetPosition(10,260);
					lSprite->Draw();

					mRender->SetFontStyle(default_size,GU_COLOR(1,1,1,1),GU_COLOR(0.0f,0.0f,0.0f,1),0x00000000);
					mRender->DebugPrint(35,272,"Crafting");

				}
			
			}
			
			if(mWorld->gameModeWorld == 1) 
			{	
				invSpriteCreative->ConstDraw();
				
				mGameMode->tapSe->SetPosition(167+creativePlace*30,70);
				mGameMode->tapSe->Draw();
			}
        }
		
		if(villEn == true)
		{
			invVillage->ConstDraw();
			
			int iSlotVilla = 0;
			
			if(SlotEnVillager >= 6) iSlotVilla = 6;
			
			selectInvVillSprite->SetPosition(175 + (26 * (SlotEnVillager - iSlotVilla)),85);
			selectInvVillSprite->Draw();
			
			int TotalTradeId[2];
			
			TotalTradeId[0] = 0;
			TotalTradeId[1] = 0;
			TotalTradeId[2] = 0;
			
			bool DrawCellRed = false;

			for(int i = 0; i < tradesManager.TradeReId.size(); i ++)
			{
				int TotalTradeAm = 0;
				for (int j = 0; j < 36; j++)
				{
					if (UniInvId(mWorld->invId[j], tradesManager.TradeReId[i]) == tradesManager.TradeReId[i])
					{
						TotalTradeAm += mWorld->invAm[j];
						TotalTradeId[i] = i + 1; 
					}
				}
				
				if(TotalTradeId[i] == 0 || TotalTradeAm < tradesManager.TradeReAm[i])
				{
					cellRedSprite2->SetPosition(123, 171  + (30 * i));
					cellRedSprite2->Draw();
					
					DrawCellRed = true;
				}
			}
			
			if(DrawCellRed)
			{
				cellRedSprite2->SetPosition(175, 186);
				cellRedSprite2->Draw();
			}
			
			/// BUTTONSVILLAGER
			if(mWorld->mainOptions.buttonsDrawing)
			{

				oIcon->SetPosition(10, 234);
				oIcon->Draw();
				
				SquIcon->SetPosition(10, 218);
				SquIcon->Draw();
				
				lSprite->SetPosition(10,260);
				lSprite->Draw();
				rSprite->SetPosition(28,260);
				rSprite->Draw();
				
				leftIcon->SetPosition(154,84);
				if(SlotEnVillager > 0)leftIcon->Draw();
				
				rightIcon->SetPosition(326,84);
				if(SlotEnVillager < tradesManager.TradeId.size() - 1)rightIcon->Draw();
				
				mRender->SetFontStyle(default_size,GU_COLOR(1,1,1,1),GU_COLOR(0.0f,0.0f,0.0f,1),0x00000000);

				mRender->DebugPrint(22,226,"Trade");
				
				mRender->DebugPrint(22,242,"Exit");
				
				mRender->DebugPrint(46,272,"Group");
				
				mRender->SetFontStyle(default_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00000200|0x00000000);
				

				std::string tradeName = mWorld->NameBlock(tradesManager.TradeId[SlotEnVillager]);
				mRender->DebugPrint(240,63,"%s offers %s",tradesManager.tradeName.c_str(), tradeName.c_str());


				sceGuDisable(GU_DEPTH_TEST);
				sceGuEnable(GU_BLEND);		
			}
		}
		
        if (craft3xEn == true)
        {
            crtSprite->ConstDraw();
			
			if(!invEn) invCraft2Sprite->Draw();
			
			/// BUTTONSCRAFT
			if(mWorld->mainOptions.buttonsDrawing)
			{

				xIcon->SetPosition(10, 250);
				if(upEn) xIcon->Draw();
				oIcon->SetPosition(10, 234);
				oIcon->Draw();
				
				SquIcon->SetPosition(10, 218);
				SquIcon->Draw();
				
				lSprite->SetPosition(10,260);
				lSprite->Draw();
				rSprite->SetPosition(28,260);
				rSprite->Draw();
				
				mRender->SetFontStyle(default_size,GU_COLOR(1,1,1,1),GU_COLOR(0.0f,0.0f,0.0f,1),0x00000000);
				
				if(upEn) mRender->DebugPrint(22,257,"Craft");
				
				if(!upEn) mRender->DebugPrint(22,226,"Craft");
				else mRender->DebugPrint(22,226,"Exit Craft");
				
				if(invEn) mRender->DebugPrint(22,242,"Inventory");
				else mRender->DebugPrint(22,242,"Exit");
				
				mRender->DebugPrint(46,272,"Group");

				mRender->SetFontStyle(default_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00000200|0x00000000);
				
				if(upEn)
				{
					std::string craftName = mWorld->NameBlock(recipesManager.SlotId[SlotEnCraft]);
					mRender->DebugPrint(152,175,"%s",craftName.c_str());
				}
				
				switch(PagCraft)
				{
					case 0:
						mRender->DebugPrint(240,69,"Structures");
					break;
					case 1:
						mRender->DebugPrint(240,69,"Tools");
					break;
					case 2:
						mRender->DebugPrint(240,69,"Food");
					break;
					case 3:
						mRender->DebugPrint(240,69,"Mechanisms");
					break;
					case 4:
						mRender->DebugPrint(240,69,"Armor");
					break;
					case 5:
						mRender->DebugPrint(240,69,"Decorations");
					break;
				}
				sceGuDisable(GU_DEPTH_TEST);
				sceGuEnable(GU_BLEND);		
			}
			
			if(upEn)
			{
				invCraftSelSprite->SetPosition(108 + (24 * IndexCraft), 100);
				invCraftSelSprite->Draw();

				invCraftSelPagSprite->SetPosition(110 + (52 * PagCraft), 28);
				invCraftSelPagSprite->Draw();

				// Preview
				int xPR = 0, yPR = 0;
				int RepeatSlotPre[5]; // Ahora correctamente de tamaño 5
				int PreAm[5];
				
				RepeatSlotPre[0] = 0;
				RepeatSlotPre[1] = 0;
				RepeatSlotPre[2] = 0;
				RepeatSlotPre[3] = 0;
				RepeatSlotPre[4] = 0;
				RepeatSlotPre[5] = 0;
				
				PreAm[0] = 0;
				PreAm[1] = 0;
				PreAm[2] = 0;
				PreAm[3] = 0;
				PreAm[4] = 0;
				PreAm[5] = 0;
				
				for(int p = 0; p < recipesManager.ReSlotPreview.size(); p++)
				{
					int IgredientAm = 0;
					int xPreDraw = 108;
					int yPreDraw = 190;

					if(invEn)
					{
						if (xPR > 1)
						{
							xPR = 0;
							yPR++;
						}
						xPreDraw = 115;
						yPreDraw = 200;
					}
					else
					{
						if (xPR > 2)
						{
							xPR = 0;
							yPR++;
						}
					}

					if (recipesManager.ReSlotPreview[p] != 0)
					{
						// Contar cuántos ingredientes hay en el inventario
						for (int j = 0; j < 36; j++)
						{
							if (UniInvId(mWorld->invId[j], recipesManager.ReSlotPreview[p]) == recipesManager.ReSlotPreview[p])
							{
								IgredientAm += mWorld->invAm[j];
							}
						}

						// Verificar si el ingrediente ya está en `RepeatSlotPre`
						bool found = false;
						int foundIndex = -1;

						for(int r = 0; r < 5; r++)
						{
							if (RepeatSlotPre[r] == recipesManager.ReSlotPreview[p])
							{
								found = true;
								foundIndex = r;
								break;
							}
							else if (RepeatSlotPre[r] == 0 && foundIndex == -1) // Guardar el primer índice vacío
							{
								foundIndex = r;
							}
						}

						// Si el ingrediente no está en la lista, lo añadimos
						if (!found && foundIndex != -1)
						{
							RepeatSlotPre[foundIndex] = recipesManager.ReSlotPreview[p];
						}

						// Incrementar la cantidad de veces que este ingrediente es necesario
						PreAm[foundIndex]++;

						// Verificar si falta este ingrediente
						if (IgredientAm < PreAm[foundIndex])
						{
							cellRedSprite->SetPosition(xPreDraw + (18 * xPR), yPreDraw + (18 * yPR));
							cellRedSprite->Draw();

							cellRedSprite2->SetPosition(198, 209);
							cellRedSprite2->Draw();
						}
					}
					
					if(((recipesManager.ReSlotPreview[2] != 0 && p == 2) || p != 2) && invEn == true) xPR++;
					else if(invEn == false) xPR++;
				}
			}

        }
        if (chestEn == true)
        {
            chtSprite->ConstDraw();
        }
        if (furnaceEn == true)
        {
            furSprite->ConstDraw();

            int furFireStage = 0;

            if(UseFurnace->fuelTime >= 10.0f)
            {
                furFireStage = 13;
            }
            if(UseFurnace->fuelTime < 10.0f)
            {
                furFireStage = ((int)(UseFurnace->fuelTime/10.0f*14.0f));
            }

            if(UseFurnace->fuelTime != 0.0f)
            {
                if(furFireStage >= 0 && furFireStage <= 13)
                {
                    furFireSprite[furFireStage]->SetPosition(215,90-((furFireStage-13)*1));
                    furFireSprite[furFireStage]->Draw();
                }
                if(furFireStage == 14)
                {
                    furFireSprite[13]->SetPosition(215,90-((13-4)*6));
                    furFireSprite[13]->Draw();
                }
            }

            if(UseFurnace->meltingTime != 0.0f)
            {
                int furArrowStage = 0;
                furArrowStage = ((int)(UseFurnace->meltingTime/10.0f*22.0f));

                if(furArrowStage >= 0 && furArrowStage <= 21)
                {
                    furArrowSprite[furArrowStage]->SetPosition(238,88);
                    furArrowSprite[furArrowStage]->Draw();
                }
                if(furArrowStage == 22)
                {
                    furArrowSprite[21]->SetPosition(238,88);
                    furArrowSprite[21]->Draw();
                }
            }
        }
    }
	DrawSetBlend(false);

    /// 3D BLOCKS AND ITEMS ON 2D PANEL //ui
    if ((invEn == false && craft3xEn == false && chestEn == false && villEn == false && menuState == 0 && mWorld->mainOptions.guiDrawing == 1 && furnaceEn == false) || (makeScreen == true && mWorld->mainOptions.guiDrawing == 1))
    {
		/*if(sprint || shield)
		{
			MatrixPush();

			MatrixTranslation(Vector3(35,32, 0));
			MatrixScale(Vector3(15,15,15));
			MatrixAngle(Vector3(-14,(8/8.0f*48-invSteveAngle)*0.05,180));// 24

			TextureManager::Instance()->SetTextureModeulate(invPlayerTex);

			invPlayer->mainAngle = 0.45f;

			DrawSetDepthMask(false);
			DrawSetCulling(true);
			
			invPlayer->Render(mWorld, dt, invSteveAngle, invPlayerTex, mWorld->invId[27+barPosition], mWorld->invSlot2Id, sprint, shield, moving, shift_x, animDest);
			
			DrawSetCulling(false);
			DrawSetDepthMask(true);

			MatrixPop();
		}*/
			
		/*if(mWorld->invSlot2Id != -1)
		{
			MatrixPush();
			MatrixTranslation(Vector3(131,231,0));
            mWorld->ItemHaveTerrainTexture(mWorld->invSlot2Id) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);

            MatrixAngle(Vector3(0,0,0));

            MatrixScale(Vector3(16,16,16));

            DrawSetCulling(true);
            mWorld->drawItems(mWorld->invSlot2Id);
            DrawSetCulling(false);
			
            MatrixPop();
		}*/
		
		
        for(int k = 0; k <= 8; k++)
        {
            if(mWorld->invId[27+k] != -1)
            {
                MatrixPush();

                if(mWorld->invId[27+k] < 250)
                {
                    MatrixTranslation(Vector3(160+k*20,230,0));
                    TextureManager::Instance()->SetTextureModeulate(texture);

                    sceGuDisable(GU_DEPTH_TEST);
                    DrawSetDepthMask(true);

                    if(k == slotForChangeScale)
                    {
                        MatrixScale(Vector3(10-changeScale*5,10+changeScale*10,10-changeScale*5));

                        changeScale -= dt*3.4f;
                        if(changeScale < 0.0f)
                        {
                            changeScale = 0.0f;
                            slotForChangeScale = -1;
                        }
                    }
                    else
                    {
                        MatrixScale(Vector3(10,10,10));
                    }

                    MatrixAngle(Vector3(150,44.6f,0));

                    DrawSetCulling(true);
                    mWorld->drawCubes(mWorld->invId[27+k],1.0f);
                    DrawSetCulling(false);

                    DrawSetDepthMask(false);
                    sceGuEnable(GU_DEPTH_TEST);
                }

                if(mWorld->invId[27+k] >= 250)
                {
                    MatrixTranslation(Vector3(160+k*20,230,0));
                    mWorld->ItemHaveTerrainTexture(mWorld->invId[27+k]) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);

                    MatrixAngle(Vector3(0,0,0));
                    if(k == slotForChangeScale)
                    {
                        MatrixScale(Vector3(16-changeScale*5,16+changeScale*10,16-changeScale*5));

                        changeScale -= dt*3.4f;
                        if(changeScale < 0.0f)
                        {
                            changeScale = 0.0f;
                            slotForChangeScale = -1;
                        }
                    }
                    else
                    {
                        MatrixScale(Vector3(16,16,16));
                    }

                    DrawSetCulling(true);
                    mWorld->drawItems(mWorld->invId[27+k]);
                    DrawSetCulling(false);
                }
                MatrixPop();
            }
        }
    }


	// ## creative ## //
    /// INVENTORY CRAFT MENU
    if(invEn == true && craft3xEn == false)
    {
		if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
		{
			if(mWorld->invSlot2Id != -1)
			{
				MatrixPush();

				MatrixTranslation(Vector3(276,123,0.0f));

				if(mWorld->invSlot2Id >= 250)
				{
					mWorld->ItemHaveTerrainTexture(mWorld->invSlot2Id) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
					MatrixScale(Vector3(0.5,0.5,0.5));

					 mWorld->drawHudItems(mWorld->invSlot2Id);
				}
				
				MatrixPop();
			}

			for(int i = 0; i <= 1; i++)
			{
				for(int j = 0; j <= 1; j++)
				{
					if(mWorld->armorId[i*2+j] != -1)
					{
						MatrixPush();
		
						if(i == 0 && j == 0)MatrixTranslation(Vector3(204,69,0.0f));
						if(i == 0 && j == 1)MatrixTranslation(Vector3(204,87,0.0f));
						if(i == 1 && j == 0)MatrixTranslation(Vector3(204,105,0.0f));
						if(i == 1 && j == 1)MatrixTranslation(Vector3(204,123,0.0f));

						if(mWorld->armorId[i*2+j] < 250)
						{
							TextureManager::Instance()->SetTextureModeulate(texture);
							MatrixScale(Vector3(0.55,0.55,0.55));
							mWorld->drawHudCubes(mWorld->armorId[i*2+j]);
						}

						if(mWorld->armorId[i*2+j] >= 250)
						{
							mWorld->ItemHaveTerrainTexture(mWorld->armorId[i*2+j]) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
							MatrixScale(Vector3(0.5,0.5,0.5));
							mWorld->drawHudItems(mWorld->armorId[i*2+j]);
						}
						MatrixPop();
					}
				}
			}
		}
		
		if(mWorld->gameModeWorld == 1)
		{
			for(int i = 0; i <= 5; i++)
			{
				for(int j = 0; j <= 8; j++)
				{
					switch(creativePlace)
					{
						case 0:
							if(creativePage*27 + i*9 + j < inventoryCoItems.size())
							{
								if(inventoryCoItems[creativePage*27 + i*9 + j] != -1)
								{
									sceGumPushMatrix();
									ScePspFVector3 loc = {169+j*18,96+i*18,0.0f};
									sceGumTranslate(&loc);

									if(inventoryCoItems[creativePage*27 + i*9 + j] < 250)
									{
										TextureManager::Instance()->SetTextureModeulate(texture);
										MatrixScale(Vector3(0.55,0.55,0.55));
										mWorld->drawHudCubes(inventoryCoItems[creativePage*27 + i*9 + j]);
									}

									if(inventoryCoItems[creativePage*27 + i*9 + j] >= 250)
									{
										mWorld->ItemHaveTerrainTexture(inventoryCoItems[creativePage*27+i*9+j]) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
										MatrixScale(Vector3(0.5,0.5,0.5));
										mWorld->drawHudItems(inventoryCoItems[creativePage*27 + i*9 + j]);
									}
									sceGumPopMatrix();
								}
							}
						break;
						case 1:
							if(creativePage*27 + i*9 + j < inventoryEqItems.size())
							{
								if(inventoryEqItems[creativePage*27 + i*9 + j] != -1)
								{
									sceGumPushMatrix();
									ScePspFVector3 loc = {169+j*18,96+i*18,0.0f};
									sceGumTranslate(&loc);

									if(inventoryEqItems[creativePage*27 + i*9 + j] < 250)
									{
										TextureManager::Instance()->SetTextureModeulate(texture);
										MatrixScale(Vector3(0.55,0.55,0.55));
										mWorld->drawHudCubes(inventoryEqItems[creativePage*27 + i*9 + j]);
									}

									if(inventoryEqItems[creativePage*27 + i*9 + j] >= 250)
									{
										mWorld->ItemHaveTerrainTexture(inventoryEqItems[creativePage*27+i*9+j]) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
										MatrixScale(Vector3(0.5,0.5,0.5));
										mWorld->drawHudItems(inventoryEqItems[creativePage*27 + i*9 + j]);
									}
									sceGumPopMatrix();
								}
							}
						break;
						case 2:
							if(creativePage*27 + i*9 + j < inventoryDeItems.size())
							{
								if(inventoryDeItems[creativePage*27 + i*9 + j] != -1)
								{
									sceGumPushMatrix();
									ScePspFVector3 loc = {169+j*18,96+i*18,0.0f};
									sceGumTranslate(&loc);

									if(inventoryDeItems[creativePage*27 + i*9 + j] < 250)
									{
										TextureManager::Instance()->SetTextureModeulate(texture);
										MatrixScale(Vector3(0.55,0.55,0.55));
										mWorld->drawHudCubes(inventoryDeItems[creativePage*27 + i*9 + j]);
									}

									if(inventoryDeItems[creativePage*27 + i*9 + j] >= 250)
									{
										mWorld->ItemHaveTerrainTexture(inventoryDeItems[creativePage*27+i*9+j]) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
										MatrixScale(Vector3(0.5,0.5,0.5));
										mWorld->drawHudItems(inventoryDeItems[creativePage*27 + i*9 + j]);
									}
									sceGumPopMatrix();
								}
							}
						break;
						case 3:
							if(creativePage*27 + i*9 + j < inventoryNaItems.size())
							{
								if(inventoryNaItems[creativePage*27 + i*9 + j] != -1)
								{
									sceGumPushMatrix();
									ScePspFVector3 loc = {169+j*18,96+i*18,0.0f};
									sceGumTranslate(&loc);

									if(inventoryNaItems[creativePage*27 + i*9 + j] < 250)
									{
										TextureManager::Instance()->SetTextureModeulate(texture);
										MatrixScale(Vector3(0.55,0.55,0.55));
										mWorld->drawHudCubes(inventoryNaItems[creativePage*27 + i*9 + j]);
									}

									if(inventoryNaItems[creativePage*27 + i*9 + j] >= 250)
									{
										mWorld->ItemHaveTerrainTexture(inventoryNaItems[creativePage*27+i*9+j]) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
										MatrixScale(Vector3(0.5,0.5,0.5));
										mWorld->drawHudItems(inventoryNaItems[creativePage*27 + i*9 + j]);
									}
									sceGumPopMatrix();
								}
							}
						break;
					}
				}
			}
		}
        //End

        //Item which we are crafting //probable

        if(upEn == false && armorEn == false)
        {
            if(invSteveAngle < invXPosition/8.0f*48)
            {
                invSteveAngle += (invXPosition/8.0f*48-invSteveAngle)*0.05;
            }
            if(invSteveAngle > invXPosition/8.0f*48)
            {
                invSteveAngle -= (invSteveAngle-invXPosition/8.0f*48)*0.05;
            }
        }

        MatrixPush();

        MatrixTranslation(Vector3(241,93,-14));
		MatrixScale(Vector3(29,29,29));
        MatrixAngle(Vector3(-14,invSteveAngle,180));// 24

        TextureManager::Instance()->SetTextureModeulate(invPlayerTex);

        invPlayer->mainAngle = 0.45f;

        DrawSetDepthMask(false);
        DrawSetCulling(true);
        if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2) invPlayer->Render(mWorld, dt, invSteveAngle, invPlayerTex, mWorld->invId[27+barPosition], mWorld->invSlot2Id, false, false, false, 0.0f, 0.0f);
        DrawSetCulling(false);
        DrawSetDepthMask(true);

        MatrixPop();
    }


    ///CRAFTING TABLE Slots Craft
    if(craft3xEn == true)
    {
		//Index
		for(int i = 0; i < recipesManager.IndexId.size(); i++)
		{
			if(IndexCraft != i && upEn)
			{
				MatrixPush();

				MatrixTranslation(Vector3(108+(i*24),100,0.0f));

				if(recipesManager.IndexId[i] < 250)
				{
					TextureManager::Instance()->SetTextureModeulate(texture);
					MatrixScale(Vector3(0.70,0.70,0.70));
					mWorld->drawHudCubes(recipesManager.IndexId[i]);
				}

				if(recipesManager.IndexId[i] >= 250)
				{
					mWorld->ItemHaveTerrainTexture(recipesManager.IndexId[i] ) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
					MatrixScale(Vector3(0.7,0.7,0.7));
					mWorld->drawHudItems(recipesManager.IndexId[i]);
				}
				MatrixPop();
			}
			else if(!upEn)
			{
				MatrixPush();

				MatrixTranslation(Vector3(108+(i*24),100,0.0f));

				if(recipesManager.IndexId[i] < 250)
				{
					TextureManager::Instance()->SetTextureModeulate(texture);
					MatrixScale(Vector3(0.70,0.70,0.70));
					mWorld->drawHudCubes(recipesManager.IndexId[i]);
				}

				if(recipesManager.IndexId[i] >= 250)
				{
					mWorld->ItemHaveTerrainTexture(recipesManager.IndexId[i] ) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
					MatrixScale(Vector3(0.7,0.7,0.7));
					mWorld->drawHudItems(recipesManager.IndexId[i]);
				}
				MatrixPop();
			}
		}
		
		if(upEn)
		{
			//Preview
			int xP = 0;
			int yP = 0;
			bool ChangeIDReWood = false;
			bool ChangeIDReWool = false;
			bool ChangeIDReSand = false;
			
			
			tickReChange += 0.02f;
			
			if(tickReChange >= 0.8f)
			{
				ChangeIDReWood = true;
				ChangeIDReWool = true;
				ChangeIDReSand = true;
				tickReChange = 0.0f;
			}
			
			for(int p = 0; p < recipesManager.ReSlotPreview.size(); p ++)
			{
				int xPreDraw = 108;
				int yPreDraw = 190;

				if(invEn)
				{
					if (xP > 1)
					{
						xP = 0;
						yP++;
					}
					xPreDraw = 115;
					yPreDraw = 200;
				}
				else
				{
					if (xP > 2)
					{
						xP = 0;
						yP++;
					}
				}
				

				if(recipesManager.ReSlotPreview[p] == 3401)
				{
					int woodID = 34;
					
					if(ChangeIDReWood)
					{
						ChangeIDReWood = false;
						
						IDDrawRe[0] ++;
						
						if(IDDrawRe[0] > 2) IDDrawRe[0] = 0;
					}
					
					switch(IDDrawRe[0])
					{
						case 0: 
							woodID = 34;
						break;
						case 1: 
							woodID = 155;
						break;
						case 2: 
							woodID = 156;
						break;
					}

					MatrixPush();

					MatrixTranslation(Vector3(xPreDraw+(xP*18),yPreDraw + (yP * 18),0.0f));


					TextureManager::Instance()->SetTextureModeulate(texture);
					MatrixScale(Vector3(0.55,0.55,0.55));
					mWorld->drawHudCubes(woodID);

					MatrixPop();
				}
				else if(recipesManager.ReSlotPreview[p] == 7001)
				{
					int sandID = 7;
					
					if(ChangeIDReSand)
					{
						ChangeIDReSand = false;
						
						IDDrawRe[1] ++;
						
						if(IDDrawRe[1] > 1) IDDrawRe[1] = 0;
					}

					switch(IDDrawRe[1])
					{
						case 0: 
							sandID = 7;
						break;
						case 1: 
							sandID = 227;
						break;
					}

					MatrixPush();

					MatrixTranslation(Vector3(xPreDraw+(xP*18),yPreDraw + (yP * 18),0.0f));


					TextureManager::Instance()->SetTextureModeulate(texture);
					MatrixScale(Vector3(0.55,0.55,0.55));
					mWorld->drawHudCubes(sandID);

					MatrixPop();
				}
				else if(recipesManager.ReSlotPreview[p] == 1001)
				{
					int woolID = 10;
					
					if(ChangeIDReWool)
					{
						ChangeIDReWool = false;
						
						IDDrawRe[2] ++;
						
						if(IDDrawRe[2] > 14) IDDrawRe[2] = 0;
					}


					woolID = 10 + IDDrawRe[2];

					MatrixPush();

					MatrixTranslation(Vector3(xPreDraw+(xP*18),yPreDraw + (yP * 18),0.0f));


					TextureManager::Instance()->SetTextureModeulate(texture);
					MatrixScale(Vector3(0.55,0.55,0.55));
					mWorld->drawHudCubes(woolID);

					MatrixPop();
				}
				else if(recipesManager.ReSlotPreview[p] != 0)
				{
					MatrixPush();

					MatrixTranslation(Vector3(xPreDraw+(xP*18),yPreDraw + (yP * 18),0.0f));

					if(recipesManager.ReSlotPreview[p] < 250)
					{
						TextureManager::Instance()->SetTextureModeulate(texture);
						MatrixScale(Vector3(0.55,0.55,0.55));
						mWorld->drawHudCubes(recipesManager.ReSlotPreview[p]);
					}

					if(recipesManager.ReSlotPreview[p] >= 250)
					{
						mWorld->ItemHaveTerrainTexture(recipesManager.ReSlotPreview[p] ) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
						MatrixScale(Vector3(0.5,0.5,0.5));
						mWorld->drawHudItems(recipesManager.ReSlotPreview[p]);
					}
					MatrixPop();
				}
				
				if(((recipesManager.ReSlotPreview[2] != 0 && p == 2) || p != 2) && invEn == true) xP++;
				else if(invEn == false) xP++;
			}
			
			//Crafting View
			

			MatrixPush();

			MatrixTranslation(Vector3(197,209,0.0f));

			if(recipesManager.SlotId[SlotEnCraft] < 250)
			{
				TextureManager::Instance()->SetTextureModeulate(texture);
				MatrixScale(Vector3(0.55,0.55,0.55));
				mWorld->drawHudCubes(recipesManager.SlotId[SlotEnCraft]);
			}

			if(recipesManager.SlotId[SlotEnCraft] >= 250)
			{
				mWorld->ItemHaveTerrainTexture(recipesManager.SlotId[SlotEnCraft] ) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
				MatrixScale(Vector3(0.5,0.5,0.5));
				mWorld->drawHudItems(recipesManager.SlotId[SlotEnCraft]);
			}
			MatrixPop();
		
			
			
			
			//Slot
			for(int i = 0; i < 3; i++)
			{
				if(i == 0 && SlotEnCraft == 0 && (recipesManager.SlotId.size() - 1) != -1)
				{
					MatrixPush();

					MatrixTranslation(Vector3(108+(IndexCraft*24),76,0.0f));

					if(recipesManager.SlotId[recipesManager.SlotId.size() - 1] < 250)
					{
						TextureManager::Instance()->SetTextureModeulate(texture);
						MatrixScale(Vector3(0.70,0.70,0.70));
						mWorld->drawHudCubes(recipesManager.SlotId[recipesManager.SlotId.size() - 1]);
					}

					if(recipesManager.SlotId[recipesManager.SlotId.size() - 1] >= 250)
					{
						mWorld->ItemHaveTerrainTexture(recipesManager.SlotId[recipesManager.SlotId.size() - 1] ) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
						MatrixScale(Vector3(0.7,0.7,0.7));
						mWorld->drawHudItems(recipesManager.SlotId[recipesManager.SlotId.size() - 1]);
					}
					MatrixPop();
				}
				else if(i == 2 && SlotEnCraft == (recipesManager.SlotId.size() - 1))
				{
					MatrixPush();

					MatrixTranslation(Vector3(108+(IndexCraft*24),124,0.0f));

					if(recipesManager.SlotId[0] < 250)
					{
						TextureManager::Instance()->SetTextureModeulate(texture);
						MatrixScale(Vector3(0.70,0.70,0.70));
						mWorld->drawHudCubes(recipesManager.SlotId[0]);
					}

					if(recipesManager.SlotId[0] >= 250)
					{
						mWorld->ItemHaveTerrainTexture(recipesManager.SlotId[0] ) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
						MatrixScale(Vector3(0.7,0.7,0.7));
						mWorld->drawHudItems(recipesManager.SlotId[0]);
					}
					MatrixPop();
				}
				else if(i == 0)
				{
					MatrixPush();

					MatrixTranslation(Vector3(108+(IndexCraft*24),76,0.0f));

					if(recipesManager.SlotId[SlotEnCraft - 1] < 250)
					{
						TextureManager::Instance()->SetTextureModeulate(texture);
						MatrixScale(Vector3(0.70,0.70,0.70));
						mWorld->drawHudCubes(recipesManager.SlotId[SlotEnCraft - 1]);
					}

					if(recipesManager.SlotId[SlotEnCraft - 1] >= 250)
					{
						mWorld->ItemHaveTerrainTexture(recipesManager.SlotId[SlotEnCraft - 1] ) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
						MatrixScale(Vector3(0.7,0.7,0.7));
						mWorld->drawHudItems(recipesManager.SlotId[SlotEnCraft - 1]);
					}
					MatrixPop();
				}
				else if(i == 2)
				{
					MatrixPush();

					MatrixTranslation(Vector3(108+(IndexCraft*24),124,0.0f));

					if(recipesManager.SlotId[SlotEnCraft + 1] < 250)
					{
						TextureManager::Instance()->SetTextureModeulate(texture);
						MatrixScale(Vector3(0.70,0.70,0.70));
						mWorld->drawHudCubes(recipesManager.SlotId[SlotEnCraft + 1]);
					}

					if(recipesManager.SlotId[SlotEnCraft + 1] >= 250)
					{
						mWorld->ItemHaveTerrainTexture(recipesManager.SlotId[SlotEnCraft + 1] ) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
						MatrixScale(Vector3(0.7,0.7,0.7));
						mWorld->drawHudItems(recipesManager.SlotId[SlotEnCraft + 1]);
					}
					MatrixPop();
				}
				else
				{
					MatrixPush();

					MatrixTranslation(Vector3(108+(IndexCraft*24),100,0.0f));

					if(recipesManager.SlotId[SlotEnCraft] < 250)
					{
						TextureManager::Instance()->SetTextureModeulate(texture);
						MatrixScale(Vector3(0.70,0.70,0.70));
						mWorld->drawHudCubes(recipesManager.SlotId[SlotEnCraft]);
					}

					if(recipesManager.SlotId[SlotEnCraft] >= 250)
					{
						mWorld->ItemHaveTerrainTexture(recipesManager.SlotId[SlotEnCraft] ) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
						MatrixScale(Vector3(0.7,0.7,0.7));
						mWorld->drawHudItems(recipesManager.SlotId[SlotEnCraft]);
					}
					MatrixPop();
				}
			}
		}
		
    }

	if(villEn == true)
	{
		int iVillager = 0;
		
		if(SlotEnVillager >= 6 && SlotEnVillager <= 11) iVillager = 6;
		
		// Limitar el número de elementos a 6
		int maxItems = 6;
		int tradeSize = tradesManager.TradeId.size();
		
		// Nos aseguramos de que no se exceda el número de elementos disponibles
		int end = std::min(iVillager + maxItems, tradeSize);
		
 		//Index
		for(int i = iVillager; i < end; i++)
		{
			MatrixPush();

			MatrixTranslation(Vector3(175+((i - iVillager)*26),85,0.0f));

			if(tradesManager.TradeId[i] < 250)
			{
				TextureManager::Instance()->SetTextureModeulate(texture);
				MatrixScale(Vector3(0.55,0.55,0.55));
				mWorld->drawHudCubes(tradesManager.TradeId[i]);
			}

			if(tradesManager.TradeId[i] >= 250)
			{
				mWorld->ItemHaveTerrainTexture(tradesManager.TradeId[i] ) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
				MatrixScale(Vector3(0.5,0.5,0.5));
				mWorld->drawHudItems(tradesManager.TradeId[i]);
			}
			MatrixPop();
		}		

		//Preview
		for(int i = 0; i < tradesManager.TradeReId.size(); i++)
		{
			MatrixPush();

			MatrixTranslation(Vector3(123,171 + (30 * i),0.0f));

			if(tradesManager.TradeReId[i] < 250)
			{
				TextureManager::Instance()->SetTextureModeulate(texture);
				MatrixScale(Vector3(0.55,0.55,0.55));
				mWorld->drawHudCubes(tradesManager.TradeReId[i]);
			}

			if(tradesManager.TradeReId[i] >= 250)
			{
				mWorld->ItemHaveTerrainTexture(tradesManager.TradeReId[i] ) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
				MatrixScale(Vector3(0.5,0.5,0.5));
				mWorld->drawHudItems(tradesManager.TradeReId[i]);
			}
			MatrixPop();
		}
		
		MatrixPush();

		MatrixTranslation(Vector3(175,186,0.0f));

		if(tradesManager.TradeId[SlotEnVillager] < 250)
		{
			TextureManager::Instance()->SetTextureModeulate(texture);
			MatrixScale(Vector3(0.55,0.55,0.55));
			mWorld->drawHudCubes(tradesManager.TradeId[SlotEnVillager]);
		}

		if(tradesManager.TradeId[SlotEnVillager] >= 250)
		{
			mWorld->ItemHaveTerrainTexture(tradesManager.TradeId[SlotEnVillager] ) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
			MatrixScale(Vector3(0.5,0.5,0.5));
			mWorld->drawHudItems(tradesManager.TradeId[SlotEnVillager]);
		}
		
		MatrixPop();
		
	}
	
    ///CHEST
    if(chestEn == true)
    {
        for(int i = 0; i <= 2; i++)
        {
            for(int j = 0; j <= 8; j++)
            {
                if(UseChest->chestSlotId[i*9+j] != -1)
                {
                    MatrixPush();

                    MatrixTranslation(Vector3(168+j*18,78+i*18,0.0f));

                    if(UseChest->chestSlotId[i*9+j] < 250)
                    {
                        TextureManager::Instance()->SetTextureModeulate(texture);
						MatrixScale(Vector3(0.55,0.55,0.55));
                        mWorld->drawHudCubes(UseChest->chestSlotId[i*9+j]);
                    }

                    if(UseChest->chestSlotId[i*9+j] >= 250)
                    {
                        mWorld->ItemHaveTerrainTexture(UseChest->chestSlotId[i*9+j]) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
						MatrixScale(Vector3(0.5,0.5,0.5));
                        mWorld->drawHudItems(UseChest->chestSlotId[i*9+j]);
                    }
                    MatrixPop();
                }
            }
        }				
    }

    ///FURNACE
    if(furnaceEn == true)
    {
        if(UseFurnace->furnaceSlotId[0] != -1)
        {
            sceGumPushMatrix();
            ScePspFVector3 loc = {222,78,0.0f};
            sceGumTranslate(&loc);

            if(UseFurnace->furnaceSlotId[0] < 250)
            {
                TextureManager::Instance()->SetTextureModeulate(texture);		
				ScePspFVector3 scale = {0.55,0.55,0.55};
				sceGumScale(&scale);
                mWorld->drawHudCubes(UseFurnace->furnaceSlotId[0]);
            }

            if(UseFurnace->furnaceSlotId[0] >= 250)
            {
                mWorld->ItemHaveTerrainTexture(UseFurnace->furnaceSlotId[0]) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
				ScePspFVector3 scale = {0.5,0.5,0.5};
				sceGumScale(&scale);
                mWorld->drawHudItems(UseFurnace->furnaceSlotId[0]);
            }
            sceGumPopMatrix();
        }

        if(UseFurnace->furnaceSlotId[1] != -1)
        {
            sceGumPushMatrix();
            ScePspFVector3 loc = {222,114,0.0f};
            sceGumTranslate(&loc);

            if(UseFurnace->furnaceSlotId[1] < 250)
            {
                TextureManager::Instance()->SetTextureModeulate(texture);
				ScePspFVector3 scale = {0.55,0.55,0.55};
				sceGumScale(&scale);
                mWorld->drawHudCubes(UseFurnace->furnaceSlotId[1]);
            }

            if(UseFurnace->furnaceSlotId[1] >= 250)
            {
                mWorld->ItemHaveTerrainTexture(UseFurnace->furnaceSlotId[1]) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
				ScePspFVector3 scale = {0.5,0.5,0.5};
				sceGumScale(&scale);
                mWorld->drawHudItems(UseFurnace->furnaceSlotId[1]);
            }
            sceGumPopMatrix();
        }

        if(UseFurnace->furnaceSlotId[2] != -1)
        {
            sceGumPushMatrix();
            ScePspFVector3 loc = {282,96,0.0f};
            sceGumTranslate(&loc);

            if(UseFurnace->furnaceSlotId[2] < 250)
            {
                TextureManager::Instance()->SetTextureModeulate(texture);
				ScePspFVector3 scale = {0.55,0.55,0.55};
				sceGumScale(&scale);
                mWorld->drawHudCubes(UseFurnace->furnaceSlotId[2]);
            }

            if(UseFurnace->furnaceSlotId[2] >= 250)
            {
                mWorld->ItemHaveTerrainTexture(UseFurnace->furnaceSlotId[2]) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
				ScePspFVector3 scale = {0.5,0.5,0.5};
				sceGumScale(&scale);
                mWorld->drawHudItems(UseFurnace->furnaceSlotId[2]);
            }
            sceGumPopMatrix();
        }
    }
	//Inv Items Slots Draw
    if (invEn == true || craft3xEn == true || chestEn == true || furnaceEn == true || villEn == true)
    {
		if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2 || (mWorld->gameModeWorld == 1 && invEn == false))
		{
			for(int i = 0; i <= 3; i++)
			{
				for(int j = 0; j <= 8; j++)
				{
					if(mWorld->invId[i*9+j] != -1)
					{
						MatrixPush();
						
						if(craft3xEn)
						{
							MatrixTranslation(Vector3(233+j*18,189+i*18,0.0f));
						}
						else if(villEn)
						{
							MatrixTranslation(Vector3(218+j*18,152+i*18,0.0f));
						}
						else
						{
							MatrixTranslation(Vector3(168+j*18,149+i*18,0.0f));
						}

						if(mWorld->invId[i*9+j] < 250)
						{
							TextureManager::Instance()->SetTextureModeulate(texture);
							MatrixScale(Vector3(0.55,0.55,0.55));

							mWorld->drawHudCubes(mWorld->invId[i*9+j]);
						}

						if(mWorld->invId[i*9+j] >= 250)
						{
							mWorld->ItemHaveTerrainTexture(mWorld->invId[i*9+j]) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
							MatrixScale(Vector3(0.5,0.5,0.5));

							mWorld->drawHudItems(mWorld->invId[i*9+j]);
						}
						MatrixPop();
					}
				}
			}
		}
		else
		{
			for(int k = 0; k <= 8; k++)
			{
				if(mWorld->invId[27+k] != -1)
				{
					sceGumPushMatrix();
					

					ScePspFVector3 loc = {169+k*18,204,0.0f};
					sceGumTranslate(&loc);


					if(mWorld->invId[27+k] < 250)
					{
						TextureManager::Instance()->SetTextureModeulate(texture);
						MatrixScale(Vector3(0.55,0.55,0.55));
						mWorld->drawHudCubes(mWorld->invId[27+k]);
					}

					if(mWorld->invId[27+k] >= 250)
					{
						mWorld->ItemHaveTerrainTexture(mWorld->invId[27+k]) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
						MatrixScale(Vector3(0.5,0.5,0.5));
						mWorld->drawHudItems(mWorld->invId[27+k]);
					}

					sceGumPopMatrix();
				}
			}
		}
		
        DrawSetBlend(true);

		if(!usingSlider)
        {
			invCellSprite->SetPosition(selectInvSprite->GetPositionX(),selectInvSprite->GetPositionY());
			invCellSprite->Draw();
		}

        if (mWorld->mId != -1) //MOUSE ITEM
        {
            MatrixPush();
            if (upEn == 1)
            {
                if (invEn == 1)
                {
                    MatrixTranslation(Vector3(258+invXPosition*18,78+invYPosition*18,0.0f));
                }
                if (craft3xEn == 1)
                {
                    MatrixTranslation(Vector3(204+invXPosition*18,74+invYPosition*18,0.0f));
                }
                if (chestEn == 1)
                {
                    MatrixTranslation(Vector3(168+invXPosition*18,74+invYPosition*18,0.0f));
                }
                if (furnaceEn == 1)
                {
                    MatrixTranslation(Vector3(222,74+(invYPosition * 36),0.0f));
                }
            }
            else
            {
				if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
				{
					if(slot2En == true)
					{
						MatrixTranslation(Vector3(276,119,0.0f));
					}
					else if(armorEn == false)
					{
						if(craft3xEn)
						{
							MatrixTranslation(Vector3(233 + (invXPosition * 18),185+(invYPosition * 18),0.0f)); // 8 upper
						}
						else if(villEn)
						{
							MatrixTranslation(Vector3(218 + (invXPosition * 18),148+(invYPosition * 18),0.0f)); // 8 upper
						}
						else
						{
							MatrixTranslation(Vector3(168 + (invXPosition * 18),145+(invYPosition * 18),0.0f)); // 8 upper
						}
					}
					else
					{
						if(invXPosition == 0 && invYPosition == 0)MatrixTranslation(Vector3(204,65,0.0f));
						if(invXPosition == 1 && invYPosition == 0)MatrixTranslation(Vector3(204,83,0.0f));
						if(invXPosition == 0 && invYPosition == 1)MatrixTranslation(Vector3(204,101,0.0f));
						if(invXPosition == 1 && invYPosition == 1)MatrixTranslation(Vector3(204,119,0.0f));
					}
				}
				else
				{
					if(invEn == false)
					{
						if(craft3xEn)
						{
							ScePspFVector3 loc = {233 + (invXPosition * 18),185+(invYPosition*18),0.0f};
							sceGumTranslate(&loc);
						}
						else if(villEn)
						{
							ScePspFVector3 loc = {218 + (invXPosition * 18),148+(invYPosition*18),0.0f};
							sceGumTranslate(&loc);
						}
						else
						{
							ScePspFVector3 loc = {168 + (invXPosition * 18),145+(invYPosition*18),0.0f}; // 8 upper
							sceGumTranslate(&loc);
						}
					}
					else
					{
						if(onDestroySlot)
						{
							ScePspFVector3 loc = {331,204,0.0f};
							sceGumTranslate(&loc);
						}
						else
						{
							ScePspFVector3 loc = {169 + (invXPosition * 18),96+(invYPosition*18),0.0f};
							sceGumTranslate(&loc);
						}
					}
				}
            }

            if (mWorld->mId < 250)
            {
                TextureManager::Instance()->SetTextureModeulate(texture);
				MatrixScale(Vector3(0.55,0.55,0.55));
                mWorld->drawHudCubes(mWorld->mId);
            }

            if (mWorld->mId >= 250)
            {
                mWorld->ItemHaveTerrainTexture(mWorld->mId) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);
				MatrixScale(Vector3(0.5,0.5,0.5));
                mWorld->drawHudItems(mWorld->mId);
            }
            MatrixPop();
        }
    }

	DrawSetDepthTest(false);
	DrawSetDepthMask(true);
	DrawSetBlend(true);
	MatrixColor(GU_COLOR(1,1,1,1.0f));
	
    // durability strip drawing //ui // Barra Items 
    if ((invEn == false && craft3xEn == false && chestEn == false && furnaceEn == false && villEn == false && menuState == 0 && mWorld->mainOptions.guiDrawing == 1) || (makeScreen == true && mWorld->mainOptions.guiDrawing == 1))
    {
        for(int k = 0; k <= 8; k++)
        {
            if(mWorld->invId[27+k] >= 250)
            {
                if(mWorld->DurabilityPointsItem(mWorld->invId[27+k]) != -1) // if it is tool
                {
                    if(mWorld->invAm[27+k] != mWorld->DurabilityPointsItem(mWorld->invId[27+k])) // checking durability
                    {
                        unsigned int toolPointStd = roundf((float)(mWorld->invAm[27+k]) / (float)(mWorld->DurabilityPointsItem(mWorld->invId[27+k])) * 13);

                        toolPointSprite[toolPointStd]->SetPosition(154+k*20,235);
                        toolPointSprite[toolPointStd]->Draw();
                    }
                }
            }
        }
		
		if(mWorld->invSlot2Id >= 250 && mWorld->DurabilityPointsItem(mWorld->invSlot2Id) != -1)
        {
            if(mWorld->invSlot2Am != mWorld->DurabilityPointsItem(mWorld->invSlot2Am)) // checking durability
            {
                unsigned int toolPointStd = roundf((float)(mWorld->invSlot2Am) / (float)(mWorld->DurabilityPointsItem(mWorld->invSlot2Id)) * 13);		
				toolPointSprite[toolPointStd]->SetPosition(125,236);
				toolPointSprite[toolPointStd]->Draw();
            }
        }
    }

    if(invEn == true && craft3xEn == false)
    {

		if(mWorld->invSlot2Id >= 250 && mWorld->DurabilityPointsItem(mWorld->invSlot2Id) != -1)
        {
            if(mWorld->invSlot2Am != mWorld->DurabilityPointsItem(mWorld->invSlot2Am)) // checking durability
            {
                 unsigned int toolPointStd = roundf((float)(mWorld->invSlot2Am) / (float)(mWorld->DurabilityPointsItem(mWorld->invSlot2Id)) * 13);
						
				toolPointSprite[toolPointStd]->SetPosition(270,128);
						
				toolPointSprite[toolPointStd]->Draw();
            }
        }


        for(int i = 0; i <= 1; i++)
        {
            for(int j = 0; j <= 1; j++)
            {
                if(mWorld->armorId[i*2+j] >= 250 && mWorld->DurabilityPointsItem(mWorld->armorId[i*2+j]) != -1)
                {
                    if(mWorld->armorAm[i*2+j] != mWorld->DurabilityPointsItem(mWorld->armorId[i*2+j])) // checking durability
                    {
                        unsigned int toolPointStd = roundf((float)(mWorld->armorAm[i*2+j]) / (float)(mWorld->DurabilityPointsItem(mWorld->armorId[i*2+j])) * 13);
						
						if(i == 0 && j == 0)toolPointSprite[toolPointStd]->SetPosition(198,74);
						if(i == 0 && j == 1)toolPointSprite[toolPointStd]->SetPosition(198,92);
						if(i == 1 && j == 0)toolPointSprite[toolPointStd]->SetPosition(198,110);
						if(i == 1 && j == 1)toolPointSprite[toolPointStd]->SetPosition(198,128);
						
						toolPointSprite[toolPointStd]->Draw();
                    }
                }
            }
        }
    }



    if(chestEn == true) //chest
    {
        for(int i = 0; i <= 2; i++)
        {
            for(int j = 0; j <= 8; j++)
            {
                if(UseChest->chestSlotId[i*9+j] >= 250 && mWorld->DurabilityPointsItem(UseChest->chestSlotId[i*9+j]) != -1)
                {
                    if(UseChest->chestSlotAm[i*9+j] != mWorld->DurabilityPointsItem(UseChest->chestSlotId[i*9+j])) // checking durability
                    {
                        unsigned int toolPointStd = roundf((float)(UseChest->chestSlotAm[i*9+j]) / (float)(mWorld->DurabilityPointsItem(UseChest->chestSlotId[i*9+j])) * 13);

                        toolPointSprite[toolPointStd]->SetPosition(162+j*18,83+i*18);
                        toolPointSprite[toolPointStd]->Draw();
                    }
                }
            }
        }
    }

    if(furnaceEn == true)
    {
        if(UseFurnace->furnaceSlotId[0] >= 250 && mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[0]) != -1) // it is item and it have durability points
        {
            if(UseFurnace->furnaceSlotAm[0] != mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[0]) != -1)
            {
                unsigned int toolPointStd = roundf((float)(UseFurnace->furnaceSlotAm[0]) / (float)(mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[0])) * 13);

                toolPointSprite[toolPointStd]->SetPosition(216,83);
                toolPointSprite[toolPointStd]->Draw();
            }
        }

        if(UseFurnace->furnaceSlotId[1] >= 250 && mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[1]) != -1) // it is item and it have durability points
        {
            if(UseFurnace->furnaceSlotAm[1] != mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[1]) != -1)
            {
                unsigned int toolPointStd = roundf((float)(UseFurnace->furnaceSlotAm[1]) / (float)(mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[1])) * 13);

                toolPointSprite[toolPointStd]->SetPosition(216,119);
                toolPointSprite[toolPointStd]->Draw();
            }
        }
    }

    if (invEn == true || craft3xEn == true || chestEn == true || furnaceEn == true || villEn == true)
    {
		if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2 || (mWorld->gameModeWorld == 1 && invEn == false))
		{
			for(int i = 0; i <= 3; i++)
			{
				for(int j = 0; j <= 8; j++)
				{
					if(mWorld->invId[i*9+j] >= 250)
					{
						if(mWorld->DurabilityPointsItem(mWorld->invId[i*9+j]) != -1) // if it is tool
						{
							if(mWorld->invAm[i*9+j] != mWorld->DurabilityPointsItem(mWorld->invId[i*9+j])) // checking durability
							{
								unsigned int toolPointStd = roundf((float)(mWorld->invAm[i*9+j]) / (float)(mWorld->DurabilityPointsItem(mWorld->invId[i*9+j])) * 13);
								
								if(craft3xEn)
								{				
									toolPointSprite[toolPointStd]->SetPosition(227+j*18,194+i*18);
								}
								else if(villEn)
								{				
									toolPointSprite[toolPointStd]->SetPosition(212+j*18,157+i*18);
								}
								else
								{		
									toolPointSprite[toolPointStd]->SetPosition(162+j*18,154+i*18);
								}
								
								toolPointSprite[toolPointStd]->Draw();
							}
						}
					}
				}
			}
		}
		else
		{
			for(int k = 0; k <= 8; k++)
            {
                if(mWorld->invId[27+k] >= 250)
                {
                    if(mWorld->DurabilityPointsItem(mWorld->invId[27+k]) != -1) // if it is tool
                    {
                        if(mWorld->invAm[27+k] != mWorld->DurabilityPointsItem(mWorld->invId[27+k])) // checking durability
                        {
                            unsigned int toolPointStd = roundf((float)(mWorld->invAm[27+k]) / (float)(mWorld->DurabilityPointsItem(mWorld->invId[27+k])) * 13);

                            toolPointSprite[toolPointStd]->SetPosition(163+k*18,209);
                            toolPointSprite[toolPointStd]->Draw();
                        }
                    }
                }
            }
		}
		
        if (mWorld->mId >= 250 && mWorld->DurabilityPointsItem(mWorld->mId) != -1)
        {
            if(mWorld->mAm != mWorld->DurabilityPointsItem(mWorld->mId))
            {
                unsigned int toolPointStd = roundf((float)(mWorld->mAm) / (float)(mWorld->DurabilityPointsItem(mWorld->mId)) * 13);
                if (upEn == 1)
                {
                    if (chestEn == 1)
                    {
                        toolPointSprite[toolPointStd]->SetPosition(162+invXPosition*18,79+invYPosition*18);

                    }
                    if (furnaceEn == 1)
                    {
                        toolPointSprite[toolPointStd]->SetPosition(216,79+invYPosition*36);
                    }
                }
                else
                {
					if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
					{
						if(slot2En == true)
						{
							toolPointSprite[toolPointStd]->SetPosition(270,124);
						}
						else if(armorEn == false)
						{
							if(craft3xEn)
							{
								toolPointSprite[toolPointStd]->SetPosition(227+invXPosition*18,190+invYPosition*18);
							}
							else if(villEn)
							{				
								toolPointSprite[toolPointStd]->SetPosition(212+invXPosition*18,153+invYPosition*18);
							}
							else
							{
								toolPointSprite[toolPointStd]->SetPosition(162+invXPosition*18,150+invYPosition*18);
							}
							
						}
						else
						{
							if(invXPosition == 0 && invYPosition == 0)toolPointSprite[toolPointStd]->SetPosition(198,70);
							if(invXPosition == 1 && invYPosition == 0)toolPointSprite[toolPointStd]->SetPosition(198,88);
							if(invXPosition == 0 && invYPosition == 1)toolPointSprite[toolPointStd]->SetPosition(198,106);
							if(invXPosition == 1 && invYPosition == 1)toolPointSprite[toolPointStd]->SetPosition(198,124);
						}
					}
					else
					{
						if(invEn == false)
						{
							if(craft3xEn)
							{
								toolPointSprite[toolPointStd]->SetPosition(227+invXPosition*18,190+invYPosition*18);
							}
							else if(villEn)
							{				
								toolPointSprite[toolPointStd]->SetPosition(212+invXPosition*18,153+invYPosition*18);
							}
							else
							{
								toolPointSprite[toolPointStd]->SetPosition(162+invXPosition*18,150+invYPosition*18);
							}
						}
						else
						{
							if(onDestroySlot)
							{
								toolPointSprite[toolPointStd]->SetPosition(163+9*18,101+7*18);
							}
							else
							{
								toolPointSprite[toolPointStd]->SetPosition(163+invXPosition*18,101+invYPosition*18);
							}
						}
					}
                }
                toolPointSprite[toolPointStd]->Draw();
            }
        }
    }

    DrawSetBlend(false);


	sceGuEnable(GU_DEPTH_TEST);
	sceGuDepthMask(0);

    //text
    if(mWorld->HP <= 0)//muerte
    {
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        if(mRender->GetFontLanguage() == ENGLISH)
        {
            if(mWorld->gameModeWorld == 2)
            {
				//check for update
				sbuttonSprite->SetPosition(240,135);
				sbuttonSprite->Draw();
				
                mRender->SetFontStyle(default_big_size,GU_COLOR(0.25f,0.25f,0.25f,1),0,0x00000200);
				mRender->DebugPrint(242,52,"Game over!");
				
				mRender->SetFontStyle(0.5,GU_COLOR(0.25f,0.25f,0.25f,1),0,0x00000200);
                mRender->DebugPrint(242,122,"You cannot respawn in hardcore mode!");
				
				mRender->SetFontStyle(default_big_size,GU_COLOR(1,0,0,1),0,0x00000200);
				mRender->DebugPrint(240,50,"Game over!");
				
				int NumeroExperiencia = mWorld->EXP + mWorld->mainStatistics.minutesPlayed + mWorld->mainStatistics.daysInGame + mWorld->mainStatistics.soilPlowed + mWorld->mainStatistics.cropsGrowned * 100 / 7;
				mRender->SetFontStyle(0.4,GU_COLOR(1,1,1,1),0,0x00000200);
                mRender->DebugPrint(242,85,"Score: %i",NumeroExperiencia);	//mmvrg
				
				mRender->SetFontStyle(0.5,GU_COLOR(1,1,1,1),0,0x00000200);
                mRender->DebugPrint(240,120,"You cannot respawn in hardcore mode!");
				
				diePos == 0 ? DrawText(240,143,GU_COLOR(1,1,0.25,1) ,default_size,"Delete world") : DrawText(240,143,GU_COLOR(1,1,1,1) ,default_size,"Delete world");
				

            }
            else
            {	
				//check for update
				buttonSprite->SetPosition(240,120);
				buttonSprite->Draw();

				buttonSprite->SetPosition(240,150);
				buttonSprite->Draw();

				//back
				sbuttonSprite->SetPosition(240,(diePos * 30) + 120);
				sbuttonSprite->Draw();
				
                mRender->SetFontStyle(default_big_size,GU_COLOR(0.25f,0.25f,0.25f,1),0,0x00000200);
                mRender->DebugPrint(242,52,"You died!");

                mRender->SetFontStyle(default_big_size,GU_COLOR(1,0,0,1),0,0x00000200);
                mRender->DebugPrint(240,50,"You died!");
				
				int NumeroExperiencia = mWorld->EXP + mWorld->mainStatistics.minutesPlayed + mWorld->mainStatistics.daysInGame + mWorld->mainStatistics.soilPlowed + mWorld->mainStatistics.cropsGrowned * 100 / 7;
				mRender->SetFontStyle(0.4,GU_COLOR(1,1,1,1),0,0x00000200);
                mRender->DebugPrint(242,85,"Score: %i",NumeroExperiencia);
				
				diePos == 0 ? DrawText(240,128,GU_COLOR(1,1,0.25,1) ,default_size,"Respawn") : DrawText(240,128,GU_COLOR(1,1,1,1) ,default_size,"Respawn");
				diePos == 1 ? DrawText(240,158,GU_COLOR(1,1,0.25,1) ,default_size,"Title screen") : DrawText(240,158,GU_COLOR(1,1,1,1) ,default_size,"Title screen");
				
				sceGuDisable(GU_DEPTH_TEST);
				sceGuEnable(GU_BLEND);
				sceGuColor(GU_COLOR(1,1,1,1.0f));


            }
        }
        if(mRender->GetFontLanguage() == RUSSIAN)
        {
            if(mWorld->gameModeWorld == 2)
            {
				//check for update
				sbuttonSprite->SetPosition(240,135);
				sbuttonSprite->Draw();
				
                mRender->SetFontStyle(default_big_size,GU_COLOR(0.25f,0.25f,0.25f,1),0,0x00000200);
				mRender->DebugPrint(242,52,"Juego perdido!");
				
				mRender->SetFontStyle(0.5,GU_COLOR(0.25f,0.25f,0.25f,1),0,0x00000200);
                mRender->DebugPrint(242,122,"No puedes reaparecer en modo hardcore!");
				
				mRender->SetFontStyle(default_big_size,GU_COLOR(1,0,0,1),0,0x00000200);
				mRender->DebugPrint(240,50,"Juego perdido!");
				
				int NumeroExperiencia = mWorld->EXP + mWorld->mainStatistics.minutesPlayed + mWorld->mainStatistics.daysInGame + mWorld->mainStatistics.soilPlowed + mWorld->mainStatistics.cropsGrowned * 100 / 7;
				mRender->SetFontStyle(0.4,GU_COLOR(1,1,1,1),0,0x00000200);
                mRender->DebugPrint(242,85,"Puntaje: %i",NumeroExperiencia);	//mmvrg
				
				mRender->SetFontStyle(0.5,GU_COLOR(1,1,1,1),0,0x00000200);
                mRender->DebugPrint(240,120,"No puedes reaparecer en modo hardcore!");
				
				diePos == 0 ? DrawText(240,143,GU_COLOR(1,1,0.25,1) ,default_size,"Borrar mundo") : DrawText(240,143,GU_COLOR(1,1,1,1) ,default_size,"Borrar mundo");
				

            }
            else
            {	
				//check for update
				buttonSprite->SetPosition(240,120);
				buttonSprite->Draw();

				buttonSprite->SetPosition(240,150);
				buttonSprite->Draw();

				//back
				sbuttonSprite->SetPosition(240,(diePos * 30) + 120);
				sbuttonSprite->Draw();
				
                mRender->SetFontStyle(default_big_size,GU_COLOR(0.25f,0.25f,0.25f,1),0,0x00000200);
                mRender->DebugPrint(242,52,"Moriste!");

                mRender->SetFontStyle(default_big_size,GU_COLOR(1,0,0,1),0,0x00000200);
                mRender->DebugPrint(240,50,"Moriste!");
				
				int NumeroExperiencia = mWorld->EXP + mWorld->mainStatistics.minutesPlayed + mWorld->mainStatistics.daysInGame + mWorld->mainStatistics.soilPlowed + mWorld->mainStatistics.cropsGrowned * 100 / 7;
				mRender->SetFontStyle(0.4,GU_COLOR(1,1,1,1),0,0x00000200);
                mRender->DebugPrint(242,85,"Puntaje: %i",NumeroExperiencia);
				
				diePos == 0 ? DrawText(240,128,GU_COLOR(1,1,0.25,1) ,default_size,"Reaparecer") : DrawText(240,128,GU_COLOR(1,1,1,1) ,default_size,"Reaparecer");
				diePos == 1 ? DrawText(240,158,GU_COLOR(1,1,0.25,1) ,default_size,"Menu principal") : DrawText(240,158,GU_COLOR(1,1,1,1) ,default_size,"Menu principal");
				
				sceGuDisable(GU_DEPTH_TEST);
				sceGuEnable(GU_BLEND);
				sceGuColor(GU_COLOR(1,1,1,1.0f));


            }
        }
    }

    if(sleepMessageTime > 0.0f)
    {
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        if(sleepMessageType == 1)
        {
            if(mRender->GetFontLanguage() == ENGLISH)
            {
                mRender->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00000200);
                mRender->DebugPrint(242,158,"You can only sleep at night!");
            }
            if(mRender->GetFontLanguage() == RUSSIAN)
            {
                mRender->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00000200);
                mRender->DebugPrint(242,158,"Solo puedes dormir en la noche!");
            }
        }
        else
        {
            if(mRender->GetFontLanguage() == ENGLISH)
            {
                mRender->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00000200);
                mRender->DebugPrint(242,158,"You can’t sleep yet, there are monsters nearby");
            }
            if(mRender->GetFontLanguage() == RUSSIAN)
            {
                mRender->SetFontStyle(default_size,GU_COLOR(1,1,1,1),0,0x00000200);
                mRender->DebugPrint(242,158,"No puedes dormir ahora! hay monstruos cerca");
            }
        }
    }

    sleepMessageTime -= dt;
    if(sleepMessageTime < 0.1f && sleepMessageTime > 0.0f)
    {
        sleepMessageTime = 0.0f;
    }

    mRender->SetFontStyle(default_size,0xFFFFFFFF,0,0x00000200);

    if((freeMemory/1024)/1024 <= 3 && mWorld->mainStatistics.minutesPlayed > 2)
    {
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));
        mRender->SetFontStyle(default_size,GU_COLOR(1,0,0,1),0,0x00000000);
        //mRender->DebugPrint(5,15,"You have few free ram! Please, reduce the settings or restart the game!");
        mRender->SetFontStyle(default_size,0xFFFFFFFF,0,0x00000200);
    }

    mRender->SetFontStyle(default_size,0xFFFFFFFF,0xFF000000,0x00000200);

    if(invEn == true || craft3xEn == true || chestEn == true || furnaceEn == true || villEn == true)
    {	
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

		if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2 || (mWorld->gameModeWorld == 1 && invEn == false))
		{
			if(craft3xEn && upEn)
			{
				if(recipesManager.SlotId[SlotEnCraft] >= 250)
				{
					if(mWorld->DurabilityPointsItem(recipesManager.SlotId[SlotEnCraft] ) == -1)
					{
						DrawAmount(202,222,recipesManager.SlotAm[SlotEnCraft]);
					}
				}
				else
				{
					DrawAmount(202,222,recipesManager.SlotAm[SlotEnCraft]);
				}
			}
			
			if(villEn == true)
			{
				if(tradesManager.TradeId[SlotEnVillager] >= 250)
				{
					if(mWorld->DurabilityPointsItem(tradesManager.TradeId[SlotEnVillager] ) == -1)
					{
						DrawAmount(180,199,tradesManager.TradeAm[SlotEnVillager]);
					}
				}
				else
				{
					DrawAmount(180,199,tradesManager.TradeAm[SlotEnVillager]);
				}
				
				for(int i = 0; i < tradesManager.TradeReId.size(); i++)
				{
					if(tradesManager.TradeReId[i] >= 250)
					{
						if(mWorld->DurabilityPointsItem(tradesManager.TradeReId[i] ) == -1)
						{
							DrawAmount(128,184 + (30 * i),tradesManager.TradeReAm[i]);
						}
					}
					else
					{
						DrawAmount(128,184 + (30 * i),tradesManager.TradeReAm[i]);
					}
				}
			}
			
			for(int i = 0; i <= 3; i++)
			{
				for(int j = 0; j <= 8; j++)
				{
					if(mWorld->invId[i*9+j] != -1 && mWorld->invAm[i*9+j] > 1)
					{
						if(mWorld->invId[i*9+j] >= 250)
						{
							if(mWorld->DurabilityPointsItem(mWorld->invId[i*9+j]) == -1)
							{
								if(craft3xEn)
								{
									DrawAmount(238+j*18,202+i*18,mWorld->invAm[i*9+j]);
								}
								else if(villEn)
								{
									DrawAmount(223+j*18,165+i*18,mWorld->invAm[i*9+j]);
								}
								else
								{
									DrawAmount(173+j*18,162+i*18,mWorld->invAm[i*9+j]);
								}
							}
						}
						else
						{
							if(craft3xEn)
							{
								DrawAmount(238+j*18,202+i*18,mWorld->invAm[i*9+j]);
							}
							else if(villEn)
							{
								DrawAmount(223+j*18,165+i*18,mWorld->invAm[i*9+j]);
							}
							else
							{
								DrawAmount(173+j*18,162+i*18,mWorld->invAm[i*9+j]);
							}
						}
					}
				}
			}
		}
		else
		{
			for(int k = 0; k <= 8; k++)
            {
                if (mWorld->invId[27+k] != -1 && mWorld->invAm[27+k] > 1)
                {
                    if(mWorld->invId[27+k] >= 250)
                    {
                        if(mWorld->DurabilityPointsItem(mWorld->invId[27+k]) == -1)
                        {
                            DrawAmount(174+k*18,217,mWorld->invAm[27+k]);
                        }
                    }
                    else
                    {
                        DrawAmount(174+k*18,217,mWorld->invAm[27+k]);
                    }
                }
            }
		}
		
        if (mWorld->mId != -1)
        {
            bool canDraw = false;

            if(mWorld->mId >= 250)
            {
                if(mWorld->DurabilityPointsItem(mWorld->mId) == -1)
                {
                    canDraw = true;
                }
            }
            else
            {
                canDraw = true;
            }

            if(canDraw == true)
            {
                if (upEn == 0)
                {
					if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
					{
						if(slot2En == true)
						{
							DrawAmount(281,132,mWorld->mAm);
						}
						else if(armorEn == false)
						{
							if(craft3xEn)
							{
								DrawAmount(238+(invXPosition * 18),198+(invYPosition * 18),mWorld->mAm);
							}
							else if(villEn)
							{
								DrawAmount(223+(invXPosition * 18),161+(invYPosition * 18),mWorld->mAm);
							}
							else
							{
								DrawAmount(173+(invXPosition * 18),158+(invYPosition * 18),mWorld->mAm);
							}
						}
						else
						{
							if(invXPosition == 0 && invYPosition == 0)DrawAmount(209,78,mWorld->mAm);
							if(invXPosition == 1 && invYPosition == 0)DrawAmount(209,96,mWorld->mAm);
							if(invXPosition == 0 && invYPosition == 1)DrawAmount(209,114,mWorld->mAm);
							if(invXPosition == 1 && invYPosition == 1)DrawAmount(209,132,mWorld->mAm);
						}
					}
					else
					{
						if(invEn == 1)
						{
							if(onDestroySlot)
							{
								DrawAmount(174+(9 * 18),108+(6 * 18),mWorld->mAm);
							}
							else
							{
								DrawAmount(174+(invXPosition * 18),108+(invYPosition * 18),mWorld->mAm);
							}
						}
						else
						{
							if(craft3xEn)
							{
								DrawAmount(238+(invXPosition * 18),198+(invYPosition * 18),mWorld->mAm);
							}
							else if(villEn)
							{
								DrawAmount(223+(invXPosition * 18),161+(invYPosition * 18),mWorld->mAm);
							}
							else
							{
								DrawAmount(173+(invXPosition * 18),158+(invYPosition * 18),mWorld->mAm);
								
							}
						}
					}
                }
                else
                {
                    if(invEn == 1)
                    {
                        DrawAmount(263+(invXPosition * 18),91+(invYPosition * 18),mWorld->mAm);
                    }
                    if(chestEn == 1)
                    {
                        DrawAmount(173+(invXPosition * 18),87+(invYPosition * 18),mWorld->mAm);
                    }
                    if(furnaceEn == 1)
                    {
                        DrawAmount(227,87+(invYPosition * 36),mWorld->mAm);
                    }
                }
            }
        }
		
		if(mWorld->gameModeWorld == 1)
		{
			int slide_y = 95+((float)creativePage/(float)creativePageMax1)*60;

			mGameMode->sliderSprite->SetPosition(332,slide_y);
			mGameMode->sliderLightedSprite->SetPosition(332,slide_y);
			
			if(invEn)
			{
				if(usingSlider)
				{
					mGameMode->sliderLightedSprite->Draw();
				}
				else
				{
					mGameMode->sliderSprite->Draw();
				}
			}
		}
		
		sceGuEnable(GU_BLEND);

		if(mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2)
		{
			if(!(craft3xEn && upEn)) selectInvSprite->Draw();
		}
		else
		{
			if(invEn)
			{
				if(!usingSlider)
				{
					selectInvSprite->Draw();
				}
			}
			else
			{
				selectInvSprite->Draw();
			}
		}
    }

    if((invEn == false && craft3xEn == false && chestEn == false && furnaceEn == false && villEn == false && menuState == 0 && mWorld->mainOptions.guiDrawing == 1) || (makeScreen == true && mWorld->mainOptions.guiDrawing == 1))
    { //ui
        for(int k = 0; k <= 8; k++)
        {
            if (mWorld->invAm[27+k] > 1)
            {
                if(mWorld->invId[27+k] >= 250) // if it is item but not a tool
                {
                    if(mWorld->DurabilityPointsItem(mWorld->invId[27+k]) == -1)
                    {
                        DrawAmount(165+k*20,243,mWorld->invAm[27+k]);
                    }
                }
                else
                {
                    DrawAmount(165+k*20,243,mWorld->invAm[27+k]);
                }
            }
        }
    }

    if(chestEn == true) //chest
    {
        for(int i = 0; i <= 2; i++)
        {
            for(int j = 0; j <= 8; j++)
            {
                if(UseChest->chestSlotId[i*9+j] != -1 && UseChest->chestSlotAm[i*9+j] > 1)
                {
                    if(UseChest->chestSlotId[i*9+j] >= 250)
                    {
                        if(mWorld->DurabilityPointsItem(UseChest->chestSlotId[i*9+j]) == -1)
                        {
                            DrawAmount(173+j*18,91+i*18,UseChest->chestSlotAm[i*9+j]);
                        }
                    }
                    else
                    {
                        DrawAmount(173+j*18,91+i*18,UseChest->chestSlotAm[i*9+j]);
                    }
                }
            }
        }
    }

    if(furnaceEn == true)
    {
        if(UseFurnace->furnaceSlotId[0] != -1 && UseFurnace->furnaceSlotAm[0] > 1)
        {
            if(UseFurnace->furnaceSlotId[0] >= 250)
            {
                if(mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[0]) == -1)
                {
                    DrawAmount(227,91,UseFurnace->furnaceSlotAm[0]);
                }
            }
            else
            {
                 DrawAmount(227,91,UseFurnace->furnaceSlotAm[0]);
            }
        }
        if(UseFurnace->furnaceSlotId[1] != -1 && UseFurnace->furnaceSlotAm[1] > 1)
        {
            if(UseFurnace->furnaceSlotId[1] >= 250)
            {
                if(mWorld->DurabilityPointsItem(UseFurnace->furnaceSlotId[1]) == -1)
                {
                    DrawAmount(227,127,UseFurnace->furnaceSlotAm[1]);
                }
            }
            else
            {
                DrawAmount(227,127,UseFurnace->furnaceSlotAm[1]);
            }
        }
        if(UseFurnace->furnaceSlotId[2] != -1 && UseFurnace->furnaceSlotAm[2] > 1)
        {
            DrawAmount(287,109,UseFurnace->furnaceSlotAm[2]);
        }
    }
	
	int language2 = mRender->GetFontLanguage();
	
	if(tutorialTimer >= 1)
	{
		if(tutorialTimer == 4 && mWorld->mainAchievements.TakingInventory == 1)
		{
			mGameMode->ArchievementsValues(0,1,0,0, mWorld);
			
			tutorialTimer = -1;
			ya = -23;
			tickAchie = 0.0f;
		}
		else
		{
			mWorld->mainAchievements.TakingInventory = 0;
			mWorld->mainAchievements.GettingWo = 0;
			mWorld->mainAchievements.Benchmarking = 0;
			mWorld->mainAchievements.TimeS = 0;
			mWorld->mainAchievements.TimeM = 0;
			mWorld->mainAchievements.MonsterHunter = 0;
			mWorld->mainAchievements.GettingUp = 0;
			mWorld->mainAchievements.HotTopic = 0;
			mWorld->mainAchievements.TimeF = 0;
			mWorld->mainAchievements.BakeBread = 0;
			mWorld->mainAchievements.Acquire = 0;
			mWorld->mainAchievements.Diamond = 0;
			
			mGameMode->DrawAchievement = false;
		}
		
		if (ya < 15 && tickAchie < 10.0f)
		{
			ya += 1;
		}
		else
		{
			if(ya == 15 && tickAchie == 0.0f)
			{
				mSoundMgr->PlayExpSound();
			}
			
			if(tickAchie < 15.0f)
			{
				tickAchie += dt;
			}
			else
			{
				ya -= 1;
				if(ya < -23)
				{
					if(tutorialTimer < 4)
					{
						ya = -23;
						tickAchie = 0.0f;
						tutorialTimer += 1;
					}
					else
					{
						ya = -23;
						tickAchie = 0.0f;
						tutorialTimer = -2;
					}
				}
			}

		}
		
		sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));
		
        buttonAchiSprite->SetPosition(390,ya);
		buttonAchiSprite->Draw();

		sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);
		
		switch(tutorialTimer)
		{
			case 1:
				if(language2 == ENGLISH)
				{
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
					mRender->DebugPrint(305,ya + 3,"First Steps");
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
					mRender->DebugPrint(305,ya + 13,"Move with the Joystick!");
				}
				
				if(language2 == RUSSIAN)
				{
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
					mRender->DebugPrint(305,ya + 3,"Primeros Pasos");
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
					mRender->DebugPrint(305,ya + 13,"Muévete con el Joystick!");
				}
			break;
			case 2:
				if(language2 == ENGLISH)
				{
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
					mRender->DebugPrint(305,ya + 3,"First Steps");
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
					mRender->DebugPrint(305,ya + 13,"You destroy a block with L");
				}
				
				if(language2 == RUSSIAN)
				{
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
					mRender->DebugPrint(305,ya + 3,"Primeros Pasos");
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
					mRender->DebugPrint(305,ya + 13,"Destruyes un bloque con L");
				}
			break;
			case 3:
				if(language2 == ENGLISH)
				{
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
					mRender->DebugPrint(305,ya + 3,"First Steps");
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
					mRender->DebugPrint(305,ya + 13,"Place Blocks with R");
				}
				
				if(language2 == RUSSIAN)
				{
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
					mRender->DebugPrint(305,ya + 3,"Primeros Pasos");
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
					mRender->DebugPrint(305,ya + 13,"Coloca Bloques con R");
				}
			break;
			case 4:
				if(language2 == ENGLISH)
				{
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
					mRender->DebugPrint(305,ya + 3,"First Steps");
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
					mRender->DebugPrint(305,ya + 13,"Open inventory with L+R");
				}
				
				if(language2 == RUSSIAN)
				{
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
					mRender->DebugPrint(305,ya + 3,"Primeros Pasos");
					mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
					mRender->DebugPrint(305,ya + 13,"Abre el inventario con L+R");
				}
			break;
		}
	}
	else if(mGameMode->DrawAchievement)
	{
		sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));
		
        buttonAchiSprite->SetPosition(390,ya);
		buttonAchiSprite->Draw();

		sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

		mRender->SetFontStyle(0.4f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
		mRender->DebugPrint(338,ya + 3,"Achievement Get!!");
		
		switch(mGameMode->AchievementItem)
		{
			case 298:
				mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
				mRender->DebugPrint(338,ya + 13,"Taking Inventory");
			break;
			case 8:
				mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
				mRender->DebugPrint(338,ya + 13,"Getting Wood");
			break;
			case 105:
				mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
				mRender->DebugPrint(338,ya + 13,"Benchmarking");
			break;
			case 255:
				mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
				mRender->DebugPrint(338,ya + 13,"Time to Strike!");
			break;
			case 250:
				mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
				mRender->DebugPrint(338,ya + 13,"Time to Mine!");
			break;
			case 321:
				mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
				mRender->DebugPrint(338,ya + 13,"Monster Hunter");
			break;
			case 251:
				mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
				mRender->DebugPrint(338,ya + 13,"Getting an Upgrade");
			break;
			case 106:
				mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
				mRender->DebugPrint(338,ya + 13,"Hot Topic");
			break;
			case 270:
				mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
				mRender->DebugPrint(338,ya + 13,"Time To Farm!");
			break;
			case 288:
				mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
				mRender->DebugPrint(338,ya + 13,"Bake Bread");
			break;
			case 278:
				mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
				mRender->DebugPrint(338,ya + 13,"Acquire Hardware");
			break;
			case 279:
				mRender->SetFontStyle(0.4f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
				mRender->DebugPrint(338,ya + 13,"DIAMONDS!");
			break;
		}
		
		if(mGameMode->AchievementItem == 105
		|| mGameMode->AchievementItem == 106
		|| mGameMode->AchievementItem == 8)
		{
			DrawBlockAc(mGameMode->AchievementItem,320,ya,15);
		}
		else
		{
			DrawItemAc(mGameMode->AchievementItem,320,ya,24);
		}
		
		//Tick
		
		if (ya < 15 && tickAchie < 5.0f)
		{
			ya += 1;
		}
		else
		{
			if(ya == 15 && tickAchie == 0.0f) mSoundMgr->PlayExpSound();
		
			if(tickAchie < 5.0f)
			{
				tickAchie += dt;
			}
			else
			{
				ya -= 1;
				if(ya < -23)
				{
					ya = -23;
					tickAchie = 0.0f;
					mGameMode->DrawAchievement = false;
					mGameMode->AchievementItem = 0;
				}
			}

		}
	}
	
    sceGuDisable(GU_BLEND);
    sceGuEnable(GU_DEPTH_TEST);

    if(makeScreen)
	{
		//end frame now to update frame buffer
		mRender->EndFrame();
		//make screenshot
		mRender->TakeNextScreenshot();
		makeScreen = false;
	}

    int language = mRender->GetFontLanguage();
    mRender->SetFontStyle(0.345f,0xFFFFFFFF,0,0x00000200);


    if(invEn == false && craft3xEn == false && chestEn == false && furnaceEn == false && villEn == false && menuState == 0) //ui
    {
		if(tickShowFlymodeMessage > 0.0f)
        {
            if(tickShowFlymodeMessage > 1.0f)
            {
                mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),GU_COLOR(0.15f,0.15f,0.15f,1),0x00000200);
            }
            else
            {
                mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,tickShowFlymodeMessage),GU_COLOR(0.15f,0.15f,0.15f,tickShowSlotName),0x00000200);
            }
            if(language == ENGLISH)
            {
                canFly == true ? mRender->DebugPrint(240,30,"Fly mode: on") : mRender->DebugPrint(240,30,"Fly mode: off");
            }
            if(language == RUSSIAN)
            {
                canFly == true ? mRender->DebugPrint(240,30,"Modo vuelo: on") : mRender->DebugPrint(240,30,"Modo vuelo : off");
            }
        }
		
        if(tickShowSlotName > 0.0f)
        {
            if(tickShowSlotName > 1.0f)
            {
                mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),GU_COLOR(0.15f,0.15f,0.15f,1),0x00000200);
            }
            else
            {
                mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,tickShowSlotName),GU_COLOR(0.15f,0.15f,0.15f,tickShowSlotName),0x00000200);
            }
            if(mWorld->invId[27+barPosition] != -1)
            {
                std::string slotName = mWorld->NameBlock(mWorld->invId[27+barPosition]);
                mRender->DebugPrint(240,190,"%s",slotName.c_str());
            }
        }

        inputDiskNameTimer -= dt;
        if(inputDiskNameTimer > 0.0f)
        {
            float red, blue, green, alpha;
            if(inputDiskNameTimer > 1.8f && inputDiskNameTimer <= 2.4f)
            {
                red = 1.0f;
                green = 1.0f - (2.4f-inputDiskNameTimer)/0.6f;
                blue = 0.0f;
                alpha = 1.0f;
            }
            if(inputDiskNameTimer > 1.2f && inputDiskNameTimer <= 1.8f)
            {
                red = 1.0f - (1.8f-inputDiskNameTimer)/0.6f;
                green = 0.0f;
                blue = (1.8f-inputDiskNameTimer)/0.6f;
                alpha = 1.0f;
            }
            if(inputDiskNameTimer > 0.6f && inputDiskNameTimer <= 1.2f)
            {
                red = 0.0f;
                green = (1.2f-inputDiskNameTimer)/0.6f;
                blue = 1.0f - (1.2f-inputDiskNameTimer)/0.6f;
                alpha = 1.0f;
            }
            if(inputDiskNameTimer > 0.0f && inputDiskNameTimer <= 0.6f)
            {
                red = (0.6f-inputDiskNameTimer)/0.6f;
                green = 1.0f;
                blue = 0.0f;
                alpha = 1.0f-(0.6f-inputDiskNameTimer)/0.6f;
            }
            if(alpha < 0.0f)
            {
                alpha = 0.0f;
            }

            mRender->SetFontStyle(0.5f,GU_COLOR(red,green,blue,alpha),999,0x00000200);

            mRender->SetFont(ENGLISH);
            mRender->DebugPrint(240,50,"%s",inputDiskName.c_str());
            mRender->SetDefaultFont();
        }
    }

    //Experience Render Numbers
	if(invEn == false && craft3xEn == false && chestEn == false && furnaceEn == false && villEn == false && menuState == 0 && mWorld->mainOptions.guiDrawing == 1 && (mWorld->gameModeWorld == 0 || mWorld->gameModeWorld == 2))
	{
		int CurrentEXP = mWorld->EXP;
		int FirstDigit = CurrentEXP / pow(10, (int)log10(CurrentEXP));
		int LastDigit = CurrentEXP % 10;
		
		sceGuDisable(GU_DEPTH_TEST);
		sceGuEnable(GU_BLEND);
		sceGuColor(GU_COLOR(1,1,1,1.0f));
		
		if(CurrentEXP > 0)
		{
			if(CurrentEXP > 9)
			{
				switch(FirstDigit)
				{
					case 0:
						mGameMode->num0Sprite->SetPosition(232,205);
						mGameMode->num0Sprite->Draw();
					break;
					case 1:
						mGameMode->num1Sprite->SetPosition(232,205);
						mGameMode->num1Sprite->Draw();
					break;
					case 2:
						mGameMode->num2Sprite->SetPosition(232,205);
						mGameMode->num2Sprite->Draw();
					break;
					case 3:
						mGameMode->num3Sprite->SetPosition(232,205);
						mGameMode->num3Sprite->Draw();
					break;
					case 4:
						mGameMode->num4Sprite->SetPosition(232,205);
						mGameMode->num4Sprite->Draw();
					break;
					case 5:
						mGameMode->num5Sprite->SetPosition(232,205);
						mGameMode->num5Sprite->Draw();
					break;
					case 6:
						mGameMode->num6Sprite->SetPosition(232,205);
						mGameMode->num6Sprite->Draw();
					break;
					case 7:
						mGameMode->num7Sprite->SetPosition(232,205);
						mGameMode->num7Sprite->Draw();
					break;
					case 8:
						mGameMode->num8Sprite->SetPosition(232,205);
						mGameMode->num8Sprite->Draw();
					break;
					case 9:
						mGameMode->num9Sprite->SetPosition(232,205);
						mGameMode->num9Sprite->Draw();
					break;
				}
				
				switch(LastDigit)
				{
					case 0:
						mGameMode->num0Sprite->SetPosition(238,205);
						mGameMode->num0Sprite->Draw();
					break;
					case 1:
						mGameMode->num1Sprite->SetPosition(238,205);
						mGameMode->num1Sprite->Draw();
					break;
					case 2:
						mGameMode->num2Sprite->SetPosition(238,205);
						mGameMode->num2Sprite->Draw();
					break;
					case 3:
						mGameMode->num3Sprite->SetPosition(238,205);
						mGameMode->num3Sprite->Draw();
					break;
					case 4:
						mGameMode->num4Sprite->SetPosition(238,205);
						mGameMode->num4Sprite->Draw();
					break;
					case 5:
						mGameMode->num5Sprite->SetPosition(238,205);
						mGameMode->num5Sprite->Draw();
					break;
					case 6:
						mGameMode->num6Sprite->SetPosition(238,205);
						mGameMode->num6Sprite->Draw();
					break;
					case 7:
						mGameMode->num7Sprite->SetPosition(238,205);
						mGameMode->num7Sprite->Draw();
					break;
					case 8:
						mGameMode->num8Sprite->SetPosition(238,205);
						mGameMode->num8Sprite->Draw();
					break;
					case 9:
						mGameMode->num9Sprite->SetPosition(238,205);
						mGameMode->num9Sprite->Draw();
					break;
				}
			}
			else
			{
				switch(CurrentEXP)
				{
					case 0:
						mGameMode->num0Sprite->SetPosition(235,205);
						mGameMode->num0Sprite->Draw();
					break;
					case 1:
						mGameMode->num1Sprite->SetPosition(235,205);
						mGameMode->num1Sprite->Draw();
					break;
					case 2:
						mGameMode->num2Sprite->SetPosition(235,205);
						mGameMode->num2Sprite->Draw();
					break;
					case 3:
						mGameMode->num3Sprite->SetPosition(235,205);
						mGameMode->num3Sprite->Draw();
					break;
					case 4:
						mGameMode->num4Sprite->SetPosition(235,205);
						mGameMode->num4Sprite->Draw();
					break;
					case 5:
						mGameMode->num5Sprite->SetPosition(235,205);
						mGameMode->num5Sprite->Draw();
					break;
					case 6:
						mGameMode->num6Sprite->SetPosition(235,205);
						mGameMode->num6Sprite->Draw();
					break;
					case 7:
						mGameMode->num7Sprite->SetPosition(235,205);
						mGameMode->num7Sprite->Draw();
					break;
					case 8:
						mGameMode->num8Sprite->SetPosition(235,205);
						mGameMode->num8Sprite->Draw();
					break;
					case 9:
						mGameMode->num9Sprite->SetPosition(235,205);
						mGameMode->num9Sprite->Draw();
					break;
				}
			}	
		}	
		sceGuDisable(GU_BLEND);
		sceGuEnable(GU_DEPTH_TEST);
	}		
	
    if(menuState == 1)  
    {
        if(menuOptions)
        {
            sceGuDisable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);
            sceGuColor(GU_COLOR(1,1,1,1.0f));
			
			LogoMenu->Draw(); //Logo
			LogoMenu->SetPosition(240,33);
			
			menuOptionsSprite->Draw(); //Menu Options
			menuOptionsSprite->SetPosition(238,159);
			
			if(menuOptionsPag == 0)
			{
				menuOptionsSpriteFo->Draw(); //Marco
				menuOptionsSpriteFo->SetPosition(240,143);
				
				for(int j = 0; j <= 5; j++) //B
				{
					nbuttonSprite->Draw();
					nbuttonSprite->SetPosition(240,93 + (20 * j));
				}
				
				if (optionsMenuPos < 6)
				{
					sbuttonSprite2->SetPosition(240,(optionsMenuPos * 20) + 93);
					sbuttonSprite2->Draw();
				}


				if(mWorld->mainOptions.fov == 40) moverSprite->SetPosition(170,93);
				else moverSprite->SetPosition((mWorld->mainOptions.fov - 40)*2.3f+170,93);
				
				moverSprite->Draw();

				if(mWorld->mainOptions.horizontalViewDistance == 1) moverSprite->SetPosition(170,113);
				else moverSprite->SetPosition((mWorld->mainOptions.horizontalViewDistance - 1)*46.0f+170,113);
				
				moverSprite->Draw();

				if(mWorld->mainOptions.verticalViewDistance == 1) moverSprite->SetPosition(170,133);
				else moverSprite->SetPosition((mWorld->mainOptions.verticalViewDistance - 1)*139.0f+170,133);

				moverSprite->Draw();

				if(mWorld->mainOptions.difficult != 3) moverSprite->SetPosition((mWorld->mainOptions.difficult)*(139.0f/3.0f)+170,153);
				else moverSprite->SetPosition((mWorld->mainOptions.difficult)*(139.0f/3.0f)+170,153);
				
				moverSprite->Draw();
				
				mWorld->mainOptions.sounds== true ? moverSprite->SetPosition(309,173): moverSprite->SetPosition(170,173);
				moverSprite->Draw();
				
				mWorld->mainOptions.music== true ? moverSprite->SetPosition(309,193): moverSprite->SetPosition(170,193);
				moverSprite->Draw();

				//Vistos
				if(mWorld->mainOptions.smoothLighting)
				{
					Check->SetPosition(166,218);
					Check->Draw();
				}
				else
				{
					CheckFo->Draw(); //Check
					CheckFo->SetPosition(166,218);	
				}
				
				if(mWorld->mainOptions.fogRendering) 
				{
					Check->SetPosition(166,237);
					Check->Draw();
				}
				else
				{
					CheckFo->Draw(); //Check
					CheckFo->SetPosition(166,237);	
				}
				
				if(mWorld->mainOptions.detailedSky) 
				{
					Check->SetPosition(166,256);
					Check->Draw();
				}
				else
				{
					CheckFo->Draw(); //Check
					CheckFo->SetPosition(166,256);	
				}
				
					
				

				sceGuDisable(GU_BLEND);
				sceGuEnable(GU_DEPTH_TEST);

				//draw subtitles on buttons
				if(mWorld->mainOptions.fov == 65)
				{
					optionsMenuPos == 0 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00004000|0x00000200);
					mRender->DebugPrint(240,100,"FOV: %f",mWorld->mainOptions.fov); //"FOV: Normal"
				}
				else
				{
					optionsMenuPos == 0 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00004000|0x00000200);
					mRender->DebugPrint(240,100,"FOV: %f",mWorld->mainOptions.fov);
				}

				if(mWorld->mainOptions.horizontalViewDistance == 1)
				{
					optionsMenuPos == 1 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00004000|0x00000200);
					mRender->DebugPrint(240,120,"H View Distance: %i",mWorld->mainOptions.horizontalViewDistance);
				}
				else
				{
					optionsMenuPos == 1 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00004000|0x00000200);
					mRender->DebugPrint(240,120,"H View Distance: %i",mWorld->mainOptions.horizontalViewDistance);
				}

				if(mWorld->mainOptions.verticalViewDistance == 1)
				{
					optionsMenuPos == 2 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00004000|0x00000200);
					mRender->DebugPrint(240,140,"V View Distance: %i",mWorld->mainOptions.verticalViewDistance);
				}
				else
				{
					optionsMenuPos == 2 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00004000|0x00000200);
					mRender->DebugPrint(240,140,"V View Distance: %i",mWorld->mainOptions.verticalViewDistance);
				}


				switch(mWorld->mainOptions.difficult)
				{
				case 0:
					optionsMenuPos == 3 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00004000|0x00000200);
					mRender->DebugPrint(240,160,"Difficult: Peaceful");
				break;
				case 1:
					optionsMenuPos == 3 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00004000|0x00000200);
					mRender->DebugPrint(240,160,"Difficult: Easy");
				break;
				case 2:
					optionsMenuPos == 3 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00004000|0x00000200);
					mRender->DebugPrint(240,160,"Difficult: Normal");
				break;
				case 3:
					optionsMenuPos == 3 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00004000|0x00000200);
					mRender->DebugPrint(240,160,"Difficult: Hard");
				break;
				}

				optionsMenuPos == 4 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00004000|0x00000200);
				mWorld->mainOptions.sounds == true ? mRender->DebugPrint(240,180,getGeneneralTranslation(64)): mRender->DebugPrint(240,180,getGeneneralTranslation(64)); //Sounds: On - OfF

				optionsMenuPos == 5 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00004000|0x00000200);
				mWorld->mainOptions.music == true ? mRender->DebugPrint(240,200,getGeneneralTranslation(65)) : mRender->DebugPrint(240,200,getGeneneralTranslation(65)); //Music: On- Off
				
				optionsMenuPos == 6 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
				mRender->DebugPrint(240,225,getGeneneralTranslation(66)); //"Smooth Lighting"
				
				optionsMenuPos == 7 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
				mRender->DebugPrint(240,244,getGeneneralTranslation(67)); //"Fog Rendering"

				optionsMenuPos == 8 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
				mRender->DebugPrint(240,263,getGeneneralTranslation(68)); //"Detailed Sky"

				DrawText(306,269,GU_COLOR(1,1,1,1),default_tiny_size,"1");
				DrawText(318,269,GU_COLOR(1,1,1,1),default_tiny_size,"2");
			}
			else
			{
				//Vistos
				if(mWorld->mainOptions.newSprintOption)
				{
					Check->SetPosition(166,97);
					Check->Draw();
				}
				else
				{
					CheckFo->Draw(); //Check
					CheckFo->SetPosition(166,97);	
				}
				
				if(mWorld->mainOptions.worldBlockAnimation) 
				{
					Check->SetPosition(166,116);
					Check->Draw();
				}
				else
				{
					CheckFo->Draw(); //Check
					CheckFo->SetPosition(166,116);	
				}
				
				if(mWorld->mainOptions.autoJump) 
				{
					Check->SetPosition(166,135);
					Check->Draw();
				}
				else
				{
					CheckFo->Draw(); //Check
					CheckFo->SetPosition(166,135);	
				}
				
				if(mWorld->mainOptions.buttonsDrawing) 
				{
					Check->SetPosition(166,154);
					Check->Draw();
				}
				else
				{
					CheckFo->Draw(); //Check
					CheckFo->SetPosition(166,154);	
				}
				
				if(mWorld->mainOptions.guiDrawing) 
				{
					Check->SetPosition(166,173);
					Check->Draw();
				}
				else
				{
					CheckFo->Draw(); //Check
					CheckFo->SetPosition(166,173);	
				}
				
				if(devMode) 
				{
					Check->SetPosition(166,192);
					Check->Draw();
				}
				else
				{
					CheckFo->Draw(); //Check
					CheckFo->SetPosition(166,192);	
				}
				
				sceGuDisable(GU_BLEND);
				sceGuEnable(GU_DEPTH_TEST);
				
				//draw subtitles on buttons
				optionsMenuPos == 0 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
				mRender->DebugPrint(240,104,getGeneneralTranslation(69)); //New-Sprint

				optionsMenuPos == 1 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
				mRender->DebugPrint(240,123,getGeneneralTranslation(70)); //"Animated Blocks"

				optionsMenuPos == 2 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
				mRender->DebugPrint(240,142,getGeneneralTranslation(71)); //"Auto-jump"

				optionsMenuPos == 3 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
				mRender->DebugPrint(240,161,getGeneneralTranslation(72)); //"Help-buttons"

				optionsMenuPos == 4 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
				mRender->DebugPrint(240,180,getGeneneralTranslation(73)); //"GUI Rendering"

				optionsMenuPos == 5 ? RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,0,1),0,0x00004000|0x00000200) : RenderManager::InstancePtr()->SetFontStyle(default_tiny_size,GU_COLOR(1,1,1,1),0,0x00004000|0x00000200);
				mRender->DebugPrint(240,199,getGeneneralTranslation(74)); //"Dev Mode"

				DrawText(306,269,GU_COLOR(1,1,1,1),default_tiny_size,"2");
				DrawText(318,269,GU_COLOR(1,1,1,1),default_tiny_size,"2");
			}
        }
        else
        {
            sceGuDisable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);
            sceGuColor(GU_COLOR(1,1,1,1.0f));

            buttonSprite->SetPosition(240,50);
            buttonSprite->Draw();

            //resume
            buttonSprite->SetPosition(240,80);
            buttonSprite->Draw();

            //options
            buttonSprite->SetPosition(240,110);
            buttonSprite->Draw();

            //save
            buttonSprite->SetPosition(240,160);
            buttonSprite->Draw();

            //quit
            buttonSprite->SetPosition(240,190);
            buttonSprite->Draw();

            //quit and save
            buttonSprite->SetPosition(240,220);
            buttonSprite->Draw();

            //selected button
            if(selectPos <= 2)
            {
                sbuttonSprite->SetPosition(240,(selectPos * 30) + 50);
            }
            if(selectPos > 2)
            {
                sbuttonSprite->SetPosition(240,(selectPos * 30) + 70);
            }
            sbuttonSprite->Draw();

            sceGuDisable(GU_BLEND);
            sceGuEnable(GU_DEPTH_TEST);

            mRender->SetFontStyle(default_size ,GU_COLOR(1,1,1,1),0,0x00000000|0x00004000);

			selectPos == 0 ? DrawText(240,59,GU_COLOR(1,1,1,1),default_size,getGeneneralTranslation(52)) : DrawText(240,59,GU_COLOR(0.25,0.25,0.25,1),default_size,getGeneneralTranslation(52)); //Back to game
			selectPos == 1 ? DrawText(240,89,GU_COLOR(1,1,1,1),default_size,getGeneneralTranslation(53)) : DrawText(240,89,GU_COLOR(0.25,0.25,0.25,1),default_size,getGeneneralTranslation(53)); //Options...
			selectPos == 2 ? DrawText(240,119,GU_COLOR(1,1,1,1),default_size,getGeneneralTranslation(54)) : DrawText(240,119,GU_COLOR(0.25,0.25,0.25,1),default_size,getGeneneralTranslation(54)); //Achievements
			selectPos == 3 ? DrawText(240,169,GU_COLOR(1,1,1,1),default_size,getGeneneralTranslation(55)) : DrawText(240,169,GU_COLOR(0.25,0.25,0.25,1),default_size,getGeneneralTranslation(55)); //Save
			selectPos == 4 ? DrawText(240,199,GU_COLOR(1,1,1,1),default_size,getGeneneralTranslation(56)) : DrawText(240,199,GU_COLOR(0.25,0.25,0.25,1),default_size,getGeneneralTranslation(56)); //Save and exit
			selectPos == 5 ? DrawText(240,229,GU_COLOR(1,1,1,1),default_size,getGeneneralTranslation(57)) : DrawText(240,229,GU_COLOR(0.25,0.25,0.25,1),default_size,getGeneneralTranslation(57)); //Exit
			DrawText(240,29,GU_COLOR(1,1,1,1),default_size,getGeneneralTranslation(51)); //Game menu
        }
    }
    if (menuState == 3)
    {
		sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));
		
		AchiBoxSprite->SetPosition(238,159);
        AchiBoxSprite->Draw();
		
		LogoMenu->Draw(); //Logo
		LogoMenu->SetPosition(240,33);
		
		sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);
		
		DrawPagAc();
		
		statisticsPage == 0 ? DrawText(301,269,GU_COLOR(1,1,1,1),default_tiny_size,"1"): DrawText(301,269,GU_COLOR(1,1,1,1),default_tiny_size,"2");
		DrawText(313,269,GU_COLOR(1,1,1,1),default_tiny_size,"2");

		
    }
    //debug info
    if(devMode)
    {
        mRender->SetFontStyle(default_size,0xFFFFFFFF,0,0x00000000);

       /* mRender->DebugPrint(240,34,"world iron ore %i",mWorld->mainWorldVariables.worldIronOre);
        mRender->DebugPrint(240,44,"world coal ore %i",mWorld->mainWorldVariables.worldCoalOre);
        mRender->DebugPrint(240,54,"world golden ore %i",mWorld->mainWorldVariables.worldGoldenOre);
        mRender->DebugPrint(240,64,"world diamond ore %i",mWorld->mainWorldVariables.worldDiamondOre);
        mRender->DebugPrint(240,74,"world redstone ore %i",mWorld->mainWorldVariables.worldRedstoneOre);
        mRender->DebugPrint(240,84,"world lapis ore %i",mWorld->mainWorldVariables.worldLapisOre);
        mRender->DebugPrint(240,94,"world clay %i",mWorld->mainWorldVariables.worldClay); */

        if(dt > 0.0f)
        {
            tick_fps += dt;
            if(tick_fps > dt/500.0f) // each 2 ms
            {
                pre_fps += (1.0f/dt);
                tick_fps - dt/500.0f;
                ticks ++;
            }

            if(ticks == 50)
            {
                average_fps = pre_fps/ticks;
                tick_fps = 0;
                pre_fps = 0;
                ticks = 0;
            }
        }
        mRender->DebugPrint(20,20,"FPS: %d",average_fps+1);
        //mRender->DebugPrint(20,34,"cpu: %d%%",mRender->GetCpuUsage());
        //mRender->DebugPrint(20,44,"gpu: %d%%",mRender->GetGpuUsage());
		//mRender->DebugPrint(20,35,"pos x: %d%%",invXPosition);
        //mRender->DebugPrint(20,45,"pos y: %d%%",invYPosition);
		
		/*
        mRender->DebugPrint(20,35,"free memory: %d kb (%d mb)",freeMemory/1024,(freeMemory/1024)/1024);
		mRender->DebugPrint(20,45,"experience: %d", mWorld->EXP);
        mRender->DebugPrint(20,55,"world: %d",mWorld->currentDimension);
        mRender->DebugPrint(20,65,"skyTime: %f",mWorld->skyTime);
		
		mRender->DebugPrint(20,85,"player x: %f",playerPosition.x);
        mRender->DebugPrint(20,95,"player y: %f",playerPosition.y);
        mRender->DebugPrint(20,105,"player z: %f",playerPosition.z);
		
		mRender->DebugPrint(20,125,"camera horAngle: %f",fppCam->horAngle);
		mRender->DebugPrint(20,135,"camera verAngle: %f",fppCam->upDownAngle);
		
		mRender->DebugPrint(20,155,"food tick: %f",eatingTick);
		mRender->DebugPrint(20,165,"bow tick: %f",tickBow);
		mRender->DebugPrint(20,185,"bool A.B: %d",AtackBow);
		mRender->DebugPrint(20,195,"gamemode: %d",mWorld->gameModeWorld);
		mRender->DebugPrint(20,205,"current world: %d",mWorld->currentDimension);
		*/
		
		/*mRender->DebugPrint(20,215,"foot in liquid: %d",footInLava);
		mRender->DebugPrint(20,225,"head in liquid: %d",headInLava);
		mRender->DebugPrint(20,235,"jumping: %d",jumping);
		mRender->DebugPrint(20,245,"playerVelocity y: %d",playerVelocity.y);*/
		/*mRender->DebugPrint(20,64,"polygons: %d",(mWorld->GetDrawntTrianglesCount() / 3));
        mRender->DebugPrint(20,84,"world time: %f",mWorld->worldDayTime);
        mRender->DebugPrint(20,94,"camera angle: %f",fppCam->horAngle);

        mRender->DebugPrint(20,104,"player.x: %f",playerPosition.x);
        mRender->DebugPrint(20,114,"player.y: %f",playerPosition.y);
        mRender->DebugPrint(20,124,"player.z: %f",playerPosition.z);

        mRender->DebugPrint(20,134,"walkingonground: %d",walkingOnGround);
        mRender->DebugPrint(20,144,"veloc.y: %f",playerVelocity.y);

        mRender->DebugPrint(20,164,"skyTime: %f",mWorld->skyTime);

       // mRender->DebugPrint(20,154,"Chunks in process : %d",mWorld->toUpdate.size());

        if(mWorld->mZombies.size() > 0)
        {
            mRender->DebugPrint(20,184,"size of vector zombies : %d",mWorld->mZombies.size());
        }
        if(mWorld->mCows.size() > 0)
        {
            mRender->DebugPrint(20,194,"size of vector cows : %d",mWorld->mCows.size());
        }

        if(mWorld->mPigs.size() > 0)
        {
            mRender->DebugPrint(20,204,"size of vector pigs : %d",mWorld->mPigs.size());
        }

        if(mWorld->mDrops.size() > 0)
        {
            mRender->DebugPrint(20,214," size of vector Drops : %i", mWorld->mDrops.size());
        }
        if(mWorld->updatingChunks.size() > 0)
        {
            mRender->DebugPrint(20,224," size of vector updatingChunks : %i", mWorld->updatingChunks.size());
        }*/
		
		
		// EDIT MODE DEBUG PRINT	// animaciones
		
		/*Vector3 testPos100 = animHandPos[1];
		Vector3 testRot100 = animHandRot[1];
		
		mRender->DebugPrint(20,30,"Anim Pos: %.2f, %.2f, %.2f", testPos100.x, testPos100.y, testPos100.z);
		mRender->DebugPrint(20,40,"Anim Rot: %.2f, %.2f, %.2f", testRot100.x, testRot100.y, testRot100.z);*/
		
		mRender->DebugPrint(20,30,"Editor Pos: %.3f, %.3f, %.3f", editModeMoveX, editModeMoveY, editModeMoveZ);
		mRender->DebugPrint(20,40,"Editor Rot: %.3f, %.3f, %.3f",editModeRotateX, editModeRotateY, editModeRotateZ);
        mRender->DebugPrint(20,50,"Editor Scale: %.2f",editModeScale);

		if(editModeType == 1) mRender->DebugPrint(20,70,"Mode: Decima");
		if(editModeType == 2) mRender->DebugPrint(20,70,"Mode: Centesima");
		if(editModeType == 3) mRender->DebugPrint(20,70,"Mode: Milesima");
		editModeManager ? mRender->DebugPrint(20,80,"Mode: Sumar") :  mRender->DebugPrint(20,80,"Mode: Restar");
		editMode ? mRender->DebugPrint(20,90,"Editor Mode: enabled") :  mRender->DebugPrint(20,90,"Editor Mode: disable");
		
		mRender->DebugPrint(20,100,"Anim Speed: %.2f", animationSpeed);
		mRender->DebugPrint(20,120,"Free Memory: %d kb (%d mb)",freeMemory/1024,(freeMemory/1024)/1024);
		
		//mRender->DebugPrint(20,140,"Bob Velocidad: %.2f",swingSpeed);
		mRender->DebugPrint(20,150,"Bob BalanceoX: %.2f",swingAmountX);
		mRender->DebugPrint(20,160,"Bob BalanceoY: %.2f",swingAmountY);
		mRender->DebugPrint(20,180,"Extra Pos Y: %.2f",swingAnimY);
		mRender->DebugPrint(20,190,"Extra Pos Y Value: %.2f",swingAnimValueY);

        mRender->SetFontStyle(default_size,0xFFFFFFFF,0,0x00000200);
    }

    //end frame
    mRender->EndFrame();
}

//additional functions
void StatePlay::advancedBlit(int sx, int sy, int sw, int sh, int dx, int dy, int slice)
{
    int start, end;

    // blit maximizing the use of the texture-cache

    for (start = sx, end = sx+sw; start < end; start += slice, dx += slice)
    {
        TexturesPSPVertex16* vertices = (TexturesPSPVertex16*)sceGuGetMemory(2 * sizeof(TexturesPSPVertex16));
        int width = (start + slice) < end ? slice : end-start;

        vertices[0].u = start;
        vertices[0].v = sy;
        vertices[0].x = dx;
        vertices[0].y = dy;
        vertices[0].z = 0;

        vertices[1].u = start + width;
        vertices[1].v = sy + sh;
        vertices[1].x = dx + width;
        vertices[1].y = dy + sh;
        vertices[1].z = 0;

        sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices);
    }
}

bool StatePlay::TryToMove(Vector3 moveVector,float dt)
{
    // Build a "test vector" that is a little longer than the move vector.
    float moveLength = moveVector.magnitude();
    Vector3 testVector = moveVector;
    testVector.normalize();
    testVector = testVector * (moveLength + 0.2f);

    // Apply this test vector.
    Vector3 movePosition = playerPosition + testVector;
    Vector3 midBodyPoint = movePosition + Vector3(0, -mWorld->playerGrowth+1.1f, 0);
    Vector3 midLowBodyPoint = movePosition + Vector3(0, -mWorld->playerGrowth+0.6f, 0);
    Vector3 lowerBodyPoint = movePosition + Vector3(0, -mWorld->playerGrowth+0.1f, 0);
	Vector3 footPosition2 = movePosition + Vector3(0.0f, -1.65f, 0.0f); 

    float slowDown = 1.0f;
    if(footInLava || footInWater)
    {
		if(sprint) sprint = false;
        slowDown = 0.89f;
    }
	//comida
	if(eatingTick > 0.1f)
	{
		if(sprint == true) sprint = false;
        slowDown = 0.2f;
	}
    if(headInLava || headInWater )
    {
		if(sprint == true) sprint = false;
        slowDown = 0.66f;
    }
	if(playerInCobweb)
	{
		slowDown = 0.1f;
	}
	if(crouch)
	{
		slowDown = 0.4f;
	}
	if(slowWalk)
	{
		slowDown = 0.4f;
	}

	if(crouch && mWorld->kickedAngle == 0.0f)
	{
		if (!mWorld->SolidAtPointForPlayer(movePosition) && !mWorld->SolidAtPointForPlayer(lowerBodyPoint) && !mWorld->SolidAtPointForPlayer(midBodyPoint) && mWorld->SolidAtPointForPlayer(footPosition2))
		{
			playerPosition = playerPosition + moveVector*slowDown;

			return true;
		}
	}
	else
	{
		if (!mWorld->SolidAtPointForPlayer(movePosition) && !mWorld->SolidAtPointForPlayer(lowerBodyPoint) && !mWorld->SolidAtPointForPlayer(midBodyPoint))
		{
			playerPosition = playerPosition + moveVector*slowDown;

			return true;
		}
	}
    //teraz mo¿na robiæ ciekawe rzeczy

    testVector = moveVector;
    testVector.normalize();
    testVector = testVector * (moveLength + 0.42f);
    movePosition = playerPosition + testVector;
    midBodyPoint = movePosition + Vector3(0, -mWorld->playerGrowth+1.1f, 0);
    midLowBodyPoint = movePosition + Vector3(0, -mWorld->playerGrowth+0.6f, 0);
    lowerBodyPoint = movePosition + Vector3(0, -mWorld->playerGrowth+0.1f, 0);

    Vector3 footPosition = playerPosition + Vector3(0.0f, -1.65f, 0.0f);

    unsigned char lowerBlock = mWorld->BlockAtPoint(lowerBodyPoint);
    unsigned char midLowBlock = mWorld->BlockAtPoint(midLowBodyPoint);
    unsigned char midBlock = mWorld->BlockAtPoint(midBodyPoint);
    unsigned char upperBlock = mWorld->BlockAtPoint(movePosition);

    if ((mWorld->blockTypes[lowerBlock].blockModel == 1 || (mWorld->blockTypes[lowerBlock].blockModel >= 6 && mWorld->blockTypes[lowerBlock].blockModel <= 9)) &&
        mWorld->blockTypes[midLowBlock].solid == false &&
        mWorld->blockTypes[midBlock].solid == false &&
        mWorld->blockTypes[upperBlock].solid == false)
    {
        playerVelocity.y = CLIMBVELOCITY*1.29f;
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.13f;
        return true;
    }

    unsigned char footBlock = mWorld->GetBlock(footPosition.x,footPosition.y,footPosition.z);
    if (mWorld->blockTypes[footBlock].blockModel == 1 &&
        mWorld->blockTypes[lowerBlock].solid == true &&
        mWorld->blockTypes[midLowBlock].solid == false &&
        mWorld->blockTypes[midBlock].solid == false &&
        mWorld->blockTypes[upperBlock].solid == false)
    {
        playerVelocity.y = CLIMBVELOCITY*1.29f;
        if(mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.13f;
        return true;
    }

    int cameraAngle = (int)fppCam->horAngle;
    if(moveForward)
    {
        if(mWorld->GetBlock(playerPosition.x,playerPosition.y-1.55f,playerPosition.z) == Ladder1::getID())
        {
            if(cameraAngle > 125 && cameraAngle < 235)
            {
                if (upperBlock != 0 || lowerBlock != 0 || midBlock != 0)
                {
                    playerVelocity.y = CLIMBVELOCITY;
                    if (mWorld->SolidAtPointForPlayer(footPosition))
                        playerPosition.y += 0.1f;
                    return true;
                }
            }
        }

        if(mWorld->GetBlock(playerPosition.x,playerPosition.y-1.55f,playerPosition.z) == Ladder2::getID())	//ladder
        {
            if(cameraAngle < 55 || cameraAngle > 305)
            {
                if (upperBlock != 0 || lowerBlock != 0 || midBlock != 0)
                {
                    playerVelocity.y = CLIMBVELOCITY;
                    if (mWorld->SolidAtPointForPlayer(footPosition))
                        playerPosition.y += 0.1f;
                    return true;
                }
            }
        }

        if(mWorld->GetBlock(playerPosition.x,playerPosition.y-1.55f,playerPosition.z) == Ladder3::getID())
        {
            if(cameraAngle > 215 && cameraAngle < 325)
            {
                if (upperBlock != 0 || lowerBlock != 0 || midBlock != 0)
                {
                    playerVelocity.y = CLIMBVELOCITY;
                    if (mWorld->SolidAtPointForPlayer(footPosition))
                        playerPosition.y += 0.1f;
                    return true;
                }
            }
        }

        if(mWorld->GetBlock(playerPosition.x,playerPosition.y-1.55f,playerPosition.z) == Ladder4::getID())
        {
            if(cameraAngle > 35 && cameraAngle < 145)
            {
                if (upperBlock != 0 || lowerBlock != 0 || midBlock != 0)
                {
                    playerVelocity.y = CLIMBVELOCITY;
                    if (mWorld->SolidAtPointForPlayer(footPosition))
                        playerPosition.y += 0.1f;
                    return true;
                }
            }
        }
    }

    return false;
}

bool StatePlay::keyPressed(int currentKey)
{
    //analog reset
    if(analogUp)
    {
        if(mSystemMgr->GetAnalogY() < InputHelper::Instance()->analogYup)
            analogUp = false;
    }
    if(analogDown)
    {
        if(mSystemMgr->GetAnalogY() > InputHelper::Instance()->analogYdown)
            analogDown = false;
    }
    if(analogLeft)
    {
        if(mSystemMgr->GetAnalogX() > InputHelper::Instance()->analogXleft)
            analogLeft = false;
    }
    if(analogRight)
    {
        if(mSystemMgr->GetAnalogX() < InputHelper::Instance()->analogXright)
            analogRight = false;
    }

    //keys
    if(currentKey == 0)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_UP);
    if(currentKey == 1)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_DOWN);
    if(currentKey == 2)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_LEFT);
    if(currentKey == 3)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_RIGHT);

    if(currentKey == 4)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_TRIANGLE);
    if(currentKey == 5)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_CROSS);
    if(currentKey == 6)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_SQUARE);
    if(currentKey == 7)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE);

    if(currentKey == 8)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER);
    if(currentKey == 9)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER);
    if(currentKey == 10)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_SELECT);
    if(currentKey == 15)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_START);

    //analog stick....
    if(currentKey == 12)//cross
    {
        if(!analogUp)
        {
            if(mSystemMgr->GetAnalogY() > InputHelper::Instance()->analogYup)
            {
                analogUp = true;
                return true;//analog up
            }
        }
    }
    if(currentKey == 11)//cross
    {
        if(!analogDown)
        {
            if(mSystemMgr->GetAnalogY() < InputHelper::Instance()->analogYdown)
            {
                analogDown = true;
                return true;//analog down
            }
        }
    }
    if(currentKey == 13)//cross
    {
        if(!analogLeft)
        {
            if(mSystemMgr->GetAnalogX() < InputHelper::Instance()->analogXleft)
            {
                analogLeft = true;
                return true;//analog left
            }
        }
    }
    if(currentKey == 14)//cross
    {
        if(!analogRight)
        {
            if(mSystemMgr->GetAnalogX() > InputHelper::Instance()->analogXright)
            {
                analogRight = true;
                return true;//analog right
            }
        }
    }

    return false;
}

bool StatePlay::keyHold(int currentKey)
{
    if(currentKey == 0)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_UP);
    if(currentKey == 1)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_DOWN);
    if(currentKey == 2)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_LEFT);
    if(currentKey == 3)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_RIGHT);

    if(currentKey == 4)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_TRIANGLE);
    if(currentKey == 5)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_CROSS);
    if(currentKey == 6)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_SQUARE);
    if(currentKey == 7)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_CIRCLE);

    if(currentKey == 8)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_LTRIGGER);
    if(currentKey == 9)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_RTRIGGER);
    if(currentKey == 10)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_SELECT);
    if(currentKey == 15)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_START);

    //analog stick....
    if(currentKey == 12)//cross
        return (mSystemMgr->GetAnalogY() > InputHelper::Instance()->analogYup);//analog up
    if(currentKey == 11)//cross
        return (mSystemMgr->GetAnalogY() < InputHelper::Instance()->analogYdown);//analog down
    if(currentKey == 13)//cross
        return (mSystemMgr->GetAnalogX() < InputHelper::Instance()->analogXleft);//analog left
    if(currentKey == 14)//cross
        return (mSystemMgr->GetAnalogX() > InputHelper::Instance()->analogXright);//analog right

    return false;
}

void StatePlay::HungerTime()
{
    if(mWorld->HG >= 16)
    {
        if (rand() % 4 == 0)
        {
            mWorld->HG -= 1;
        }
    }
    else
    {
        mWorld->HG -= 1;
    }
    if(mWorld->HG < 0)
    {
        mWorld->HG = 0;
    }
}

void StatePlay::FireBurning()
{
	tickFR += dt;
	if(tickFR >= 0.0f)
	{
		if(mWorld->HP > 0)
		{
			if(mWorld->FR <= 0)
			{
				burning = false;
			}
			if(mWorld->FR > 0)
			{
				mWorld->FR -= 1;
			}
		}
		tickFR -= 1.0f;
	}
}

void StatePlay::HealthTime()
{
    if(mWorld->HG <= 0 && mWorld->HP > 0)
    {
        if(mWorld->mainOptions.difficult == 0)
        {
            if(mWorld->HP > 1)
            {
                if(mWorld->HP == 2)
                {
                    HurtPlayer(1);
                }
                else
                {
                    HurtPlayer(2);
                }
            }
        }
        else
        {
            HurtPlayer(2);
        }
    }

    if(mWorld->HG >= 18)
    {
        if(mWorld->HP > 0)
        {
            mWorld->HP += 1;
        }
    }

    if(mWorld->HP > 20)
    {
        mWorld->HP = 20;
    }
}

void StatePlay::OxygenTime()
{
    if(mWorld->HP > 0)
    {
        if(mWorld->OS <= 0)
        {
            HurtPlayer(2);
        }
        if(mWorld->OS > 0)
        {
            mWorld->OS -= 1;
        }
    }
}

void StatePlay::HurtPlayer(float damage) 
{
	mSoundMgr->PlayHitSound();
	last_HP = mWorld->HP;
	mWorld->HP -= damage;

	if(mWorld->HP > 0)
	{
		hurt = true;
		hurt_time = 1.0f;
		hpAnim = 0.0f;
	}
}


void StatePlay::HurtPlayerConsiderArmor(float damage, bool InCamaraAtack)
{	
	if(shield && InCamaraAtack)
	{
		mSoundMgr->PlayShieldSound();
			
		mWorld->invSlot2Am -= damage;
		if (mWorld->invSlot2Am <= 0) // [27+barPosition] - selected item/block
		{
			mWorld->invSlot2Am = -1;
			mWorld->invSlot2Id = -1;
			mWorld->invSlot2St = 0;
		}
			
		recoidShield = 0.25f;

	}
	else
	{
		if(hurt == false)
		{
			mSoundMgr->PlayHitSound();
			last_HP = mWorld->HP;
			mWorld->HP -= damage*(1.0f-(mWorld->AP/25.0f));

			if(mWorld->HP > 0)
			{
				hurt = true;
				hurt_time = 1.0f;
				hpAnim = 0.0f;
			}
		}
	}
}

void StatePlay::ExperienceSystem(int a, int b) //a: min value, b: max value
{
	int CurrentExp = mWorld->EXP+1;
	int Progress = (a+rand()%b)*15/CurrentExp;
	int CurrentCount;
	int Restante;
	int LastDigit;
	
	mSoundMgr->PlayOrbSound();
	CurrentCount = mWorld->EXPcount;
	CurrentCount += Progress;
	
	if(CurrentCount >= 180)
	{
		Restante = CurrentCount - 180;
		mWorld->EXPcount = Restante;
		mWorld->EXP += 1;
		LastDigit = mWorld->EXP % 10;
		
		if(LastDigit == 0 || LastDigit == 5)mSoundMgr->PlayExpSound();	
		return;
	}
	
	mWorld->EXPcount += Progress;
}

void StatePlay::PutInInventory(int id, int num, bool st)
{
    bool ok;
    ok = false;
    for(int j = 27; j <= 35; j++)
    {
        if (mWorld->invSt[j]==1)
        {
            if (mWorld->invId[j]== id)
            {
                if(mWorld->invAm[j] + num <= 64)
                {
                    mWorld->invAm[j] += num;
                    chestId = -1;
                    ok = true;
                    break;
                }
                else
                {
                    continue;
                }
            }
        }

        if (mWorld->invId[j]== -1)
        {
            mWorld->invSt[j] = st;
            mWorld->invId[j] = id;
            mWorld->invAm[j] = num;
            ok = true;
            break;
        }
    }

    if(ok == false)
    {
        for(int j = 0; j <= 26; j++)
        {
            if (mWorld->invSt[j]==1)
            {
                if (mWorld->invId[j]== id)
                {
                    if(mWorld->invAm[j] + num <= 64)
                    {
                        mWorld->invAm[j] += num;
                        chestId = -1;
                        break;
                        return;
                    }
                    else
                    {
                        continue;
                    }
                }
            }

            if (mWorld->invId[j]== -1)
            {
                mWorld->invSt[j] = st;
                mWorld->invId[j] = id;
                mWorld->invAm[j] = num;
                break;
                return;
            }
        }
    }
}

void StatePlay::DrawText(int x,int y, unsigned int color, float size, const char *message, ...)
{
    RenderManager::InstancePtr()->SetFontStyle(size,color,0,0x00000200|0x00000000);
    RenderManager::InstancePtr()->DebugPrint(x,y,message);
}

void StatePlay::DrawText2(int x,int y, unsigned int color, float size, const char *message, ...)
{
    RenderManager::InstancePtr()->SetFontStyle(size,color,0,0x00004000|0x00000000);
    RenderManager::InstancePtr()->DebugPrint(x,y,message);
}

void StatePlay::DrawPagAc()
{
	if(statisticsPage == 0)
	{
		if(mWorld->mainAchievements.TakingInventory == 1)
		{
			mRender->SetFontStyle(0.5f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
			mRender->DebugPrint(177,116,"Achievement Get!!");
		}
		mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
		mRender->DebugPrint(177,106,"Taking Inventory");
		
		if(mWorld->mainAchievements.GettingWo == 1)
		{
			mRender->SetFontStyle(0.5f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
			mRender->DebugPrint(177,139,"Achievement Get!!");
		}
		mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
		mRender->DebugPrint(177,129,"Getting Wood");
		
		if(mWorld->mainAchievements.Benchmarking == 1)
		{
			mRender->SetFontStyle(0.5f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
			mRender->DebugPrint(177,162,"Achievement Get!!");
		}
		mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
		mRender->DebugPrint(177,152,"Benchmarking");
		
		if(mWorld->mainAchievements.TimeS == 1)
		{
			mRender->SetFontStyle(0.5f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
			mRender->DebugPrint(177,185,"Achievement Get!!");
		}
		mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
		mRender->DebugPrint(177,175,"Time to Strike!");
		
		if(mWorld->mainAchievements.TimeM == 1)
		{
			mRender->SetFontStyle(0.5f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
			mRender->DebugPrint(177,208,"Achievement Get!!");
		}
		mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
		mRender->DebugPrint(177,198,"Time to Mine!");
		
		if(mWorld->mainAchievements.MonsterHunter == 1)
		{
			mRender->SetFontStyle(0.5f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
			mRender->DebugPrint(177,184,"Achievement Get!!");
		}
		mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
		mRender->DebugPrint(177,221,"Monster Hunter");
		
		if(mWorld->mainAchievements.GettingUp == 1)
		{
			mRender->SetFontStyle(0.5f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
			mRender->DebugPrint(177,254,"Achievement Get!!");
		}
		mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
		mRender->DebugPrint(177,244,"Getting an Upgrade");
		
		for(int j = 0; j <= 8; j++)
		{
			switch(j)
			{
				case 1: 
				{
					DrawItemAc(298,159,101,16);
				}
				break;
				case 2: 
				{
					DrawBlockAc(8,159,102+23*(j - 1),10);
				}
				break;			
				case 3: 
				{
					DrawBlockAc(105,159,102+23*(j - 1),10);
				}
				break;	
				case 4: 
				{
					DrawItemAc(255,159,101+23*(j - 1),16);
				}
				break;		
				case 5: 
				{
					DrawItemAc(250,159,101+23*(j - 1),16);
				}
				break;
				case 6: 
				{
					DrawItemAc(321,159,101+23*(j - 1),16);
				}
				break;
				case 7: 
				{
					DrawItemAc(251,159,101+23*(j - 1),16);
				}
				break;			
			}
		}
	}
	else
	{
		if(mWorld->mainAchievements.HotTopic == 1)
		{
			mRender->SetFontStyle(0.5f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
			mRender->DebugPrint(177,116,"Achievement Get!!");
		}
		mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
		mRender->DebugPrint(177,106,"Hot Topic");
		
		if(mWorld->mainAchievements.TimeF == 1)
		{
			mRender->SetFontStyle(0.5f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
			mRender->DebugPrint(177,139,"Achievement Get!!");
		}
		mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
		mRender->DebugPrint(177,129,"Time To Farm!");					
		
		if(mWorld->mainAchievements.BakeBread == 1)
		{
			mRender->SetFontStyle(0.5f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
			mRender->DebugPrint(177,162,"Achievement Get!!");
		}
		mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
		mRender->DebugPrint(177,152,"Bake Bread");
		
		if(mWorld->mainAchievements.Acquire == 1)
		{
			mRender->SetFontStyle(0.5f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
			mRender->DebugPrint(177,185,"Achievement Get!!");
		}
		mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
		mRender->DebugPrint(177,175,"Acquire Hardware");			
		
		if(mWorld->mainAchievements.Diamond == 1)
		{
			mRender->SetFontStyle(0.5f,GU_COLOR(1,1,0,1),GU_COLOR(1,1,0,1),0x00000000);
			mRender->DebugPrint(177,208,"Achievement Get!!");
		}
		mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),GU_COLOR(1,1,1,1),0x00000000);
		mRender->DebugPrint(177,198,"DIAMONDS!");

		for(int j = 0; j <= 5; j++)
		{
			switch(j)
			{
				case 1: 
				{
					DrawBlockAc(106,159,102,10);
				}
				break;
				case 2: 
				{
					DrawItemAc(270,159,101+23*(j - 1),16);
				}
				break;
				case 3: 
				{
					DrawItemAc(288,159,101+23*(j - 1),16);
				}
				break;			
				case 4: 
				{
					DrawItemAc(278,159,101+23*(j - 1),16);
				}
				break;	
				case 5: 
				{
					DrawItemAc(279,159,101+23*(j - 1),16);
				}		
			}
		}
	}
}

void StatePlay::DrawItemAc(int id,int x,int y, int Scale)
{
	MatrixPush();
	MatrixTranslation(Vector3(x,y,0));
    mWorld->ItemHaveTerrainTexture(id) ? TextureManager::Instance()->SetTextureModeulate(texture) : TextureManager::Instance()->SetTextureModeulate(barItems);

    MatrixAngle(Vector3(0,0,0));
	MatrixScale(Vector3(Scale,Scale,Scale));

    DrawSetCulling(true);
    mWorld->drawItems(id);
    DrawSetCulling(false);
                
    MatrixPop();
	sceGuDisable(GU_BLEND);
	sceGuEnable(GU_DEPTH_TEST);
}

void StatePlay::DrawBlockAc(int id,int x,int y, int Scale)
{
	MatrixPush();
    MatrixTranslation(Vector3(x,y,0));
	TextureManager::Instance()->SetTextureModeulate(texture);
	sceGuDisable(GU_DEPTH_TEST);
	DrawSetDepthMask(true);
	MatrixAngle(Vector3(150,44.6f,0));
	MatrixScale(Vector3(Scale,Scale,Scale));

	DrawSetCulling(true);
	mWorld->drawCubes(id,1.0f);
    DrawSetCulling(false);

    DrawSetDepthMask(false);				
	MatrixPop();			
	sceGuDisable(GU_BLEND);
	sceGuEnable(GU_DEPTH_TEST);
}

void StatePlay::DrawAmount(int x,int y, int amount)
{
	int dozens, units;

	dozens = floorf(amount / 10.0f);
	units = amount % 10;

	RenderManager::InstancePtr()->SetFont(0);
	if(dozens != 0)
	{
		RenderManager::InstancePtr()->SetFontStyle(0.343,GU_COLOR(0.25f,0.25f,0.25f,1.0f),0,0x00000400|0x00004000);
		RenderManager::InstancePtr()->DebugPrint(x+1,y+1,"%i",dozens);
		RenderManager::InstancePtr()->SetFontStyle(0.343,GU_COLOR(1.0f,1.0f,1.0f,1.0f),0,0x00000400|0x00004000);
		RenderManager::InstancePtr()->DebugPrint(x,y,"%i",dozens);
	}

	RenderManager::InstancePtr()->SetFontStyle(0.343,GU_COLOR(0.25f,0.25f,0.25f,1.0f),0,0x00000400|0x00004000);
	RenderManager::InstancePtr()->DebugPrint(x+7,y+1,"%i",units);
	RenderManager::InstancePtr()->SetFontStyle(0.343,GU_COLOR(1.0f,1.0f,1.0f,1.0f),0,0x00000400|0x00004000);
	RenderManager::InstancePtr()->DebugPrint(x+6,y,"%i",units);
	RenderManager::InstancePtr()->SetDefaultFont();
}

const char* StatePlay::getGeneneralTranslation(int id)
{
	return langManager.getGeneralTranslation(id);
}

//animaciones
float StatePlay::lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

///	### --- HOLA BUSCA CODIGOS :D SALUDOS DESDE ECUADOR --- ###	///

