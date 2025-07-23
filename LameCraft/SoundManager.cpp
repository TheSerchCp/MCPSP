#include "SoundManager.h"

using namespace Aurora;

SoundManager SoundManager::m_SoundManager;

SoundManager* SoundManager::Instance()
{
	return &m_SoundManager;
}

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
    pgeWavStopAll();

    pgeWavUnload(buttonSound);
	pgeWavUnload(openchestSound);
	pgeWavUnload(closedchestSound);
	pgeWavUnload(igniteSound);
    pgeWavUnload(doorOpen);
    pgeWavUnload(doorClose);
    pgeWavUnload(breakSound);
    pgeWavUnload(bow);
    pgeWavUnload(plopSound);
    pgeWavUnload(spiderDieSound);
	pgeWavUnload(pigDieSound);
    pgeWavUnload(cowSaySound);
	pgeWavUnload(chickenSaySound);
    pgeWavUnload(fuse);
    pgeWavUnload(fiss);
    pgeWavUnload(splash);
    pgeWavUnload(glass);
    pgeWavUnload(shear);
	pgeWavUnload(rainSound);
	pgeWavUnload(expSound);
	pgeWavUnload(orbSound);
	pgeWavUnload(tntSounds);
	pgeWavUnload(zombieSaySound);
	pgeWavUnload(zombieDieSound);
	pgeWavUnload(pigmanSaySound);
	pgeWavUnload(pigmanDieSound);
	pgeWavUnload(burpSound);
	
	pgeWavUnload(craftSound);
	pgeWavUnload(craftFailSound);

    for(int i = 0; i <= 3; i++)
    {	
        pgeWavUnload(grassSounds[i]);
        pgeWavUnload(grawelSounds[i]);
        pgeWavUnload(stoneSounds[i]);
        pgeWavUnload(woodSounds[i]);
        pgeWavUnload(sandSounds[i]);
        pgeWavUnload(snowSounds[i]);
    }
    for(int i = 0; i <= 2; i++)
    {
        pgeWavUnload(eatSounds[i]);
        pgeWavUnload(hitSounds[i]);
        pgeWavUnload(digSounds[i]);
        //pgeWavUnload(thunderSounds[i]);
    }
    for(int i = 0; i <= 1; i++)
    {
        pgeWavUnload(fallSounds[i]);
        pgeWavUnload(cowHurtSounds[i]);
		pgeWavUnload(chickenHurtSounds[i]);
		pgeWavUnload(pigHurtSounds[i]);
        pgeWavUnload(creeperHurtSounds[i]);
        pgeWavUnload(zombieHurtSounds[i]);
        pgeWavUnload(spiderHurtSounds[i]);
        pgeWavUnload(sheepHurtSounds[i]);
        pgeWavUnload(pigHurtSounds[i]);
		pgeWavUnload(witherSkeletonHurtSound[i]);
        pgeWavUnload(noteSounds[i]);
    }
	Ram32 = false;
}

void SoundManager::Init()
{
    //first of all init audio engine
    VirtualFileInit();
   // oslInitAudioME(OSL_FMT_MP3);
	oslInitAudio();
	pgeWavInit();

    //set default values
	currentWalkSound = 0;
	lastWalkSound = 0;
	playerSounds = true;
	lastAmbientSound = 0;
	currentAmbientSound = 0;
	ambientSoundsEnabled = true;
	srand(time(NULL));
	
	//button sound
	buttonSound = pgeWavLoad("Assets/Sounds/other/button1.wav");
	
	openchestSound = pgeWavLoad("Assets/Sounds/other/chest_open.wav");
	closedchestSound = pgeWavLoad("Assets/Sounds/other/chest_closed.wav");
	igniteSound = pgeWavLoad("Assets/Sounds/fire/ignite.wav");

	//TNT
	tntSounds = pgeWavLoad("Assets/Sounds/other/tnt.wav");
	
	fuse = pgeWavLoad("Assets/Sounds/other/fuse.wav");
    fiss = pgeWavLoad("Assets/Sounds/other/fizz.wav");
	splash = pgeWavLoad("Assets/Sounds/other/splash.wav");
	
	expSound = pgeWavLoad("Assets/Sounds/other/exp.wav");
	orbSound = pgeWavLoad("Assets/Sounds/other/orb.wav");

	doorOpen = pgeWavLoad("Assets/Sounds/other/door_open.wav");
	doorClose = pgeWavLoad("Assets/Sounds/other/door_close.wav");

	breakSound = pgeWavLoad("Assets/Sounds/other/break.wav");

	//rain sounds
	rainSound = pgeWavLoad("Assets/Sounds/ambient/weather/rain.wav");

	bow = pgeWavLoad("Assets/Sounds/other/bow.wav");

	shear = pgeWavLoad("Assets/Sounds/mobs/sheep/shear.wav");

	//plop sound
	plopSound = pgeWavLoad("Assets/Sounds/other/plop.wav");
	pgeWavVolume(plopSound,50,50);

    //fall sounds
    fallSounds[0] = pgeWavLoad("Assets/Sounds/Damage/fallbig.wav");
    fallSounds[1] = pgeWavLoad("Assets/Sounds/Damage/fallsmall.wav");

    //note sounds
    noteSounds[0] = pgeWavLoad("Assets/Sounds/notes/bass.wav");
    noteSounds[1] = pgeWavLoad("Assets/Sounds/notes/pling.wav");
    pgeWavVolume(noteSounds[0],85,85);
    pgeWavVolume(noteSounds[1],85,85);

    //zombie sounds
    zombieHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/zombie/hurt1.wav");
    zombieHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/zombie/hurt2.wav");
    zombieSaySound = pgeWavLoad("Assets/Sounds/mobs/zombie/say.wav");
    zombieDieSound = pgeWavLoad("Assets/Sounds/mobs/zombie/death.wav");
	
	//pigman sounds
	pigmanHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/pigman/hurt1.wav");
    pigmanHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/pigman/hurt2.wav");
    pigmanSaySound = pgeWavLoad("Assets/Sounds/mobs/pigman/say.wav");
    pigmanDieSound = pgeWavLoad("Assets/Sounds/mobs/pigman/death.wav");
	
	//wither skeleton
	witherSkeletonHurtSound[0] = pgeWavLoad("Assets/Sounds/mobs/wither_skeleton/hurt1.wav");
	witherSkeletonHurtSound[1] = pgeWavLoad("Assets/Sounds/mobs/wither_skeleton/hurt2.wav");
	
	//skeleton sounds
    skeletonHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/skeleton/hurt1.wav");
    skeletonHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/skeleton/hurt2.wav");
    skeletonSaySound = pgeWavLoad("Assets/Sounds/mobs/skeleton/say.wav");
    skeletonDieSound = pgeWavLoad("Assets/Sounds/mobs/skeleton/death.wav");
	
	//spider sounds
    spiderHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/spider/hurt1.wav");
    spiderHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/spider/hurt2.wav");
    spiderDieSound = pgeWavLoad("Assets/Sounds/mobs/spider/death.wav");

    //cow sounds
    cowHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/cow/hurt1.wav");
    cowHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/cow/hurt2.wav");
    cowSaySound = pgeWavLoad("Assets/Sounds/mobs/cow/say1.wav");
	
	//chicken sounds
    chickenHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/chicken/hurt1.wav");
    chickenHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/chicken/hurt2.wav");
    chickenSaySound = pgeWavLoad("Assets/Sounds/mobs/chicken/say1.wav");

    //pig sounds
    pigHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/pig/hurt1.wav");
    pigHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/pig/hurt2.wav");
	pigDieSound = pgeWavLoad("Assets/Sounds/mobs/pig/death.wav");

    //creeper sounds
    creeperHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/creeper/hurt1.wav");
    creeperHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/creeper/hurt2.wav");

    //sheep sounds
    sheepHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/sheep/say1.wav");
    sheepHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/sheep/say2.wav");

	//grass sounds
	grassSounds[0] = pgeWavLoad("Assets/Sounds/walking/grass/grass1.wav");
	grassSounds[1] = pgeWavLoad("Assets/Sounds/walking/grass/grass2.wav");
	grassSounds[2] = pgeWavLoad("Assets/Sounds/walking/grass/grass3.wav");
	grassSounds[3] = pgeWavLoad("Assets/Sounds/walking/grass/grass4.wav");

	//gravel
	grawelSounds[0] = pgeWavLoad("Assets/Sounds/walking/gravel/gravel1.wav");
	grawelSounds[1] = pgeWavLoad("Assets/Sounds/walking/gravel/gravel2.wav");
	grawelSounds[2] = pgeWavLoad("Assets/Sounds/walking/gravel/gravel3.wav");
	grawelSounds[3] = pgeWavLoad("Assets/Sounds/walking/gravel/gravel4.wav");

	//stone
	stoneSounds[0] = pgeWavLoad("Assets/Sounds/walking/stone/stone1.wav");
	stoneSounds[1] = pgeWavLoad("Assets/Sounds/walking/stone/stone2.wav");
	stoneSounds[2] = pgeWavLoad("Assets/Sounds/walking/stone/stone3.wav");
	stoneSounds[3] = pgeWavLoad("Assets/Sounds/walking/stone/stone4.wav");

	//wood
	woodSounds[0] = pgeWavLoad("Assets/Sounds/walking/wood/wood1.wav");
	woodSounds[1] = pgeWavLoad("Assets/Sounds/walking/wood/wood2.wav");
	woodSounds[2] = pgeWavLoad("Assets/Sounds/walking/wood/wood3.wav");
	woodSounds[3] = pgeWavLoad("Assets/Sounds/walking/wood/wood4.wav");

    //sand
    sandSounds[0] = pgeWavLoad("Assets/Sounds/walking/sand/sand1.wav");
	sandSounds[1] = pgeWavLoad("Assets/Sounds/walking/sand/sand2.wav");
	sandSounds[2] = pgeWavLoad("Assets/Sounds/walking/sand/sand3.wav");
	sandSounds[3] = pgeWavLoad("Assets/Sounds/walking/sand/sand4.wav");

    //snow
    snowSounds[0] = pgeWavLoad("Assets/Sounds/walking/snow/snow1.wav");
	snowSounds[1] = pgeWavLoad("Assets/Sounds/walking/snow/snow2.wav");
	snowSounds[2] = pgeWavLoad("Assets/Sounds/walking/snow/snow3.wav");
	snowSounds[3] = pgeWavLoad("Assets/Sounds/walking/snow/snow4.wav");

	//glass
	glass = pgeWavLoad("Assets/Sounds/dig/glass1.wav");

	digSounds[0] = pgeWavLoad("Assets/Sounds/dig/grass1.wav");
	digSounds[1] = pgeWavLoad("Assets/Sounds/dig/gravel1.wav");
	digSounds[2] = pgeWavLoad("Assets/Sounds/dig/stone1.wav");

    // Eat sounds
	eatSounds[0] = pgeWavLoad("Assets/Sounds/eat/eat1.wav");
	eatSounds[1] = pgeWavLoad("Assets/Sounds/eat/eat2.wav");
	eatSounds[2] = pgeWavLoad("Assets/Sounds/eat/eat3.wav");
	burpSound = pgeWavLoad("Assets/Sounds/eat/burp.wav");
	
	// Thunder sounds
	/*thunderSounds[0] = pgeWavLoad("Assets/Sounds/ambient/weather/thunder1.wav");
	thunderSounds[1] = pgeWavLoad("Assets/Sounds/ambient/weather/thunder2.wav");
	thunderSounds[2] = pgeWavLoad("Assets/Sounds/ambient/weather/thunder3.wav");**/

    // Hit sounds
    hitSounds[0] = pgeWavLoad("Assets/Sounds/Damage/hit1.wav");
    hitSounds[1] = pgeWavLoad("Assets/Sounds/Damage/hit2.wav");
    hitSounds[2] = pgeWavLoad("Assets/Sounds/Damage/hit3.wav");
	
	// Shield sound
	shieldSound = pgeWavLoad("Assets/Sounds/Damage/shield.wav");

	craftSound = pgeWavLoad("Assets/Sounds/interface/craft.wav");
	craftFailSound = pgeWavLoad("Assets/Sounds/interface/craftfail.wav");

    ambientTrack = NULL;
    ambientTrackName = " ";
	
	//menu
    menuTrack = NULL;
    menuTrackName = " ";
	
	//Hell
    HellTrack = NULL;
    HellTrackName = " ";

    diskTrack = NULL;
    diskTrackName = " ";

    delayAmbient = false;
	
	Ram32 = false;
}

void SoundManager::LoadSonds()
{
	//button sound
	buttonSound = pgeWavLoad("Assets/Sounds/other/button1.wav");
	
	// chest sound
	openchestSound = pgeWavLoad("Assets/Sounds/other/chest_open.wav");
	closedchestSound = pgeWavLoad("Assets/Sounds/other/chest_closed.wav");
	igniteSound = pgeWavLoad("Assets/Sounds/fire/ignite.wav");

	// tnt
	tntSounds = pgeWavLoad("Assets/Sounds/other/tnt.wav");
	
	fuse = pgeWavLoad("Assets/Sounds/other/fuse.wav");
    fiss = pgeWavLoad("Assets/Sounds/other/fizz.wav");
	splash = pgeWavLoad("Assets/Sounds/other/splash.wav");
	
	expSound = pgeWavLoad("Assets/Sounds/other/exp.wav");
	orbSound = pgeWavLoad("Assets/Sounds/other/orb.wav");

	doorOpen = pgeWavLoad("Assets/Sounds/other/door_open.wav");
	doorClose = pgeWavLoad("Assets/Sounds/other/door_close.wav");

	breakSound = pgeWavLoad("Assets/Sounds/other/break.wav");

	// rain sounds
	rainSound = pgeWavLoad("Assets/Sounds/ambient/weather/rain.wav");

	// bow sounds
	bow = pgeWavLoad("Assets/Sounds/other/bow.wav");

	// shear sound
	shear = pgeWavLoad("Assets/Sounds/mobs/sheep/shear.wav");

	// plop sound
	plopSound = pgeWavLoad("Assets/Sounds/other/plop.wav");
	pgeWavVolume(plopSound,50,50);

    // fall sounds
    fallSounds[0] = pgeWavLoad("Assets/Sounds/Damage/fallbig.wav");
    fallSounds[1] = pgeWavLoad("Assets/Sounds/Damage/fallsmall.wav");

    // note sounds
    noteSounds[0] = pgeWavLoad("Assets/Sounds/notes/bass.wav");
    noteSounds[1] = pgeWavLoad("Assets/Sounds/notes/pling.wav");
    pgeWavVolume(noteSounds[0],85,85);
    pgeWavVolume(noteSounds[1],85,85);

    // skeleton sounds
    skeletonHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/skeleton/hurt1.wav");
    skeletonHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/skeleton/hurt2.wav");
    skeletonSaySound = pgeWavLoad("Assets/Sounds/mobs/skeleton/say.wav");
    skeletonDieSound = pgeWavLoad("Assets/Sounds/mobs/skeleton/death.wav");
	
	// zombie sounds
    zombieHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/zombie/hurt1.wav");
    zombieHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/zombie/hurt2.wav");
    zombieSaySound = pgeWavLoad("Assets/Sounds/mobs/zombie/say.wav");
    zombieDieSound = pgeWavLoad("Assets/Sounds/mobs/zombie/death.wav");
	
	// pigman sounds
	pigmanHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/pigman/hurt1.wav");
    pigmanHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/pigman/hurt2.wav");
    pigmanSaySound = pgeWavLoad("Assets/Sounds/mobs/pigman/say.wav");
    pigmanDieSound = pgeWavLoad("Assets/Sounds/mobs/pigman/death.wav");
	
	// wither skeleton sounds
	witherSkeletonHurtSound[0] = pgeWavLoad("Assets/Sounds/mobs/wither_skeleton/hurt1.wav");
    witherSkeletonHurtSound[1] = pgeWavLoad("Assets/Sounds/mobs/wither_skeleton/hurt2.wav");
	
	// spider sounds
    spiderHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/spider/hurt1.wav");
    spiderHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/spider/hurt2.wav");
    spiderDieSound = pgeWavLoad("Assets/Sounds/mobs/spider/death.wav");

    // cow sounds
    cowHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/cow/hurt1.wav");
    cowHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/cow/hurt2.wav");
    cowSaySound = pgeWavLoad("Assets/Sounds/mobs/cow/say1.wav");
	
	// chicken sounds
    chickenHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/chicken/hurt1.wav");
    chickenHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/chicken/hurt2.wav");
    chickenSaySound = pgeWavLoad("Assets/Sounds/mobs/chicken/say1.wav");

    // pig sounds
    pigHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/pig/hurt1.wav");
    pigHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/pig/hurt2.wav");
	pigDieSound = pgeWavLoad("Assets/Sounds/mobs/pig/death.wav");

    // creeper sounds
    creeperHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/creeper/hurt1.wav");
    creeperHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/creeper/hurt2.wav");

    // sheep sounds
    sheepHurtSounds[0] = pgeWavLoad("Assets/Sounds/mobs/sheep/say1.wav");
    sheepHurtSounds[1] = pgeWavLoad("Assets/Sounds/mobs/sheep/say2.wav");

	// grass sounds
	grassSounds[0] = pgeWavLoad("Assets/Sounds/walking/grass/grass1.wav");
	grassSounds[1] = pgeWavLoad("Assets/Sounds/walking/grass/grass2.wav");
	grassSounds[2] = pgeWavLoad("Assets/Sounds/walking/grass/grass3.wav");
	grassSounds[3] = pgeWavLoad("Assets/Sounds/walking/grass/grass4.wav");

	// gravel
	grawelSounds[0] = pgeWavLoad("Assets/Sounds/walking/gravel/gravel1.wav");
	grawelSounds[1] = pgeWavLoad("Assets/Sounds/walking/gravel/gravel2.wav");
	grawelSounds[2] = pgeWavLoad("Assets/Sounds/walking/gravel/gravel3.wav");
	grawelSounds[3] = pgeWavLoad("Assets/Sounds/walking/gravel/gravel4.wav");

	// stone
	stoneSounds[0] = pgeWavLoad("Assets/Sounds/walking/stone/stone1.wav");
	stoneSounds[1] = pgeWavLoad("Assets/Sounds/walking/stone/stone2.wav");
	stoneSounds[2] = pgeWavLoad("Assets/Sounds/walking/stone/stone3.wav");
	stoneSounds[3] = pgeWavLoad("Assets/Sounds/walking/stone/stone4.wav");

	// wood
	woodSounds[0] = pgeWavLoad("Assets/Sounds/walking/wood/wood1.wav");
	woodSounds[1] = pgeWavLoad("Assets/Sounds/walking/wood/wood2.wav");
	woodSounds[2] = pgeWavLoad("Assets/Sounds/walking/wood/wood3.wav");
	woodSounds[3] = pgeWavLoad("Assets/Sounds/walking/wood/wood4.wav");

    // sand
    sandSounds[0] = pgeWavLoad("Assets/Sounds/walking/sand/sand1.wav");
	sandSounds[1] = pgeWavLoad("Assets/Sounds/walking/sand/sand2.wav");
	sandSounds[2] = pgeWavLoad("Assets/Sounds/walking/sand/sand3.wav");
	sandSounds[3] = pgeWavLoad("Assets/Sounds/walking/sand/sand4.wav");

    // snow
    snowSounds[0] = pgeWavLoad("Assets/Sounds/walking/snow/snow1.wav");
	snowSounds[1] = pgeWavLoad("Assets/Sounds/walking/snow/snow2.wav");
	snowSounds[2] = pgeWavLoad("Assets/Sounds/walking/snow/snow3.wav");
	snowSounds[3] = pgeWavLoad("Assets/Sounds/walking/snow/snow4.wav");

	// glass
	glass = pgeWavLoad("Assets/Sounds/dig/glass1.wav");

	// Dig sounds
	digSounds[0] = pgeWavLoad("Assets/Sounds/dig/grass1.wav");
	digSounds[1] = pgeWavLoad("Assets/Sounds/dig/gravel1.wav");
	digSounds[2] = pgeWavLoad("Assets/Sounds/dig/stone1.wav");

    // Eat sounds
	eatSounds[0] = pgeWavLoad("Assets/Sounds/eat/eat1.wav");
	eatSounds[1] = pgeWavLoad("Assets/Sounds/eat/eat2.wav");
	eatSounds[2] = pgeWavLoad("Assets/Sounds/eat/eat3.wav");
	burpSound = pgeWavLoad("Assets/Sounds/eat/burp.wav");

    // Hit sounds
    hitSounds[0] = pgeWavLoad("Assets/Sounds/Damage/hit1.wav");
    hitSounds[1] = pgeWavLoad("Assets/Sounds/Damage/hit2.wav");
    hitSounds[2] = pgeWavLoad("Assets/Sounds/Damage/hit3.wav");
}

void SoundManager::AudioSync()
{
    // не в том проблема надо оставить
    oslAudioVSync();
}

void SoundManager::PlayChestSound()
{
	if(playerSounds && Ram32 == false)
		pgeWavPlay(openchestSound);
}

void SoundManager::PlayChestClosedSound()
{
	if(playerSounds && Ram32 == false)
		pgeWavPlay(closedchestSound);
}

void SoundManager::PlayOrbSound()
{
	if(playerSounds && Ram32 == false)
		pgeWavPlay(orbSound);
}

void SoundManager::PlayExpSound()
{
	if(playerSounds && Ram32 == false)
		pgeWavPlay(expSound);
}

void SoundManager::PlayIgniteSound()
{
	if(playerSounds && Ram32 == false)
		pgeWavPlay(igniteSound);
}

void SoundManager::PlayMenuSound()
{
	if(playerSounds && Ram32 == false)
		pgeWavPlay(buttonSound);
}

void SoundManager::PlayPlopSound()
{
	if(playerSounds && Ram32 == false)
		pgeWavPlay(plopSound);
}

void SoundManager::PlayTNTSound()
{
	if(playerSounds && Ram32 == false)
	{
		pgeWavPlay(tntSounds);
	}
}

void SoundManager::PlayFuseSound()
{
	if(playerSounds && Ram32 == false)
		pgeWavPlay(fuse);
}

void SoundManager::PlayFissSound()
{
	if(playerSounds && Ram32 == false)
		pgeWavPlay(fiss);
}

void SoundManager::PlayShearSound()
{
	if(playerSounds && Ram32 == false)
		pgeWavPlay(shear);
}

void SoundManager::PlaySplashSound()
{
	if(playerSounds && Ram32 == false)
    {
        int volume = 88+rand()%10;
        pgeWavVolume(splash,volume,volume);
		pgeWavPlay(splash);
    }
}

void SoundManager::PlayNoteSound(unsigned int noteType, float pitch)
{
	if(playerSounds && Ram32 == false)
    {
        pgeWavPitch(noteSounds[noteType],pitch);
        pgeWavPlay(noteSounds[noteType]);
        pgeWavPitch(noteSounds[noteType],1.0f);
    }
}

void SoundManager::PlayDoorSound(bool open)
{
	if(playerSounds && Ram32 == false)
    {
        open == true ? pgeWavPlay(doorOpen) : pgeWavPlay(doorClose);
    }
}

void SoundManager::PlayGlassSound()
{
	if(playerSounds && Ram32 == false)
		pgeWavPlay(glass);
}

/*void SoundManager::PlayThunderSound()
{
	if(playerSounds)
    {
		pgeWavPlay(thunderSounds[rand() % 3]);
    }
}*/

void SoundManager::PlayRainSound(int volume)
{
	if(playerSounds && Ram32 == false)
    {
        pgeWavVolume(rainSound, volume, volume);
        pgeWavPlay(rainSound);
        pgeWavVolume(rainSound, 100, 100);
    }
}

void SoundManager::PlayEndDigSound(int type)
{
	if(playerSounds && Ram32 == false)
	{
		switch(type)
		{
			case 0://grass
			{
				pgeWavPlay(digSounds[0]);
			}
			break;
			case 1://gravel
			{
				pgeWavPlay(digSounds[1]);
			}
			break;
			case 2://stone
			{
				pgeWavPlay(digSounds[2]);
			}
			break;
			case 3://wood
			{
				pgeWavPlay(woodSounds[rand() % 4]);
			}
			break;
            case 4://cloth
			{
			    pgeWavPlay(snowSounds[rand() % 4]);
			}
			break;
            case 5://sand
			{
				pgeWavPlay(sandSounds[rand() % 4]);
			}
			break;
            case 6://snow
			{
				pgeWavPlay(snowSounds[rand() % 4]);
			}
			break;
		}
	}
}

void SoundManager::PlayBreakSound()
{
	if(playerSounds && Ram32 == false)
		pgeWavPlay(breakSound);
}

void SoundManager::PlayBowSound()
{
	if(playerSounds && Ram32 == false)
		pgeWavPlay(bow);
}

// Zombie Sounds
void SoundManager::PlayZombieHurtSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        int i = rand() % 2;
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(zombieHurtSounds[i],volume,volume);
            pgeWavPlay(zombieHurtSounds[i]);
        }
    }
}

void SoundManager::PlayZombieDieSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(zombieDieSound,volume,volume);
            pgeWavPlay(zombieDieSound);
        }
    }
}

void SoundManager::PlayZombieSaySound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        if(distanceToPlayer < 22.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (22.0f-distanceToPlayer)/22.0f*100.0f;
            pgeWavVolume(zombieSaySound,volume,volume);
            pgeWavPlay(zombieSaySound);
        }
    }
}

// Pigman Sounds
void SoundManager::PlayPigmanHurtSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        int i = rand() % 2;
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(pigmanHurtSounds[i],volume,volume);
            pgeWavPlay(pigmanHurtSounds[i]);
        }
    }
}

void SoundManager::PlayPigmanDieSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(pigmanDieSound,volume,volume);
            pgeWavPlay(pigmanDieSound);
        }
    }
}

void SoundManager::PlayPigmanSaySound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        if(distanceToPlayer < 22.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (22.0f-distanceToPlayer)/22.0f*100.0f;
            pgeWavVolume(pigmanSaySound,volume,volume);
            pgeWavPlay(pigmanSaySound);
        }
    }
}

// Wither Skeleton Sounds
void SoundManager::PlayWitherSkeletonHurtSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        int i = rand() % 2;
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(witherSkeletonHurtSound[i],volume,volume);
            pgeWavPlay(witherSkeletonHurtSound[i]);
        }
    }
}

// Skeleton Sounds
void SoundManager::PlaySkeletonHurtSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        int i = rand() % 2;
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(skeletonHurtSounds[i],volume,volume);
            pgeWavPlay(skeletonHurtSounds[i]);
        }
    }
}

void SoundManager::PlaySkeletonSaySound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        if(distanceToPlayer < 22.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (22.0f-distanceToPlayer)/22.0f*100.0f;
            pgeWavVolume(skeletonSaySound,volume,volume);
            pgeWavPlay(skeletonSaySound);
        }
    }
}

void SoundManager::PlaySkeletonDieSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(skeletonDieSound,volume,volume);
            pgeWavPlay(skeletonDieSound);
        }
    }
}


// Spider Sounds
void SoundManager::PlaySpiderHurtSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        int i = rand() % 2;
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(spiderHurtSounds[i],volume,volume);
            pgeWavPlay(spiderHurtSounds[i]);
        }
    }
}

void SoundManager::PlaySpiderDieSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(spiderDieSound,volume,volume);
            pgeWavPlay(spiderDieSound);
        }
    }
}


// Pig Sounds
void SoundManager::PlayPigDieSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(pigDieSound,volume,volume);
            pgeWavPlay(pigDieSound);
        }
    }
}

void SoundManager::PlayPigHurtSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        int i = rand()%2;
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(pigHurtSounds[i],volume,volume);
            pgeWavPlay(pigHurtSounds[i]);
        }
    }
}

// Cow Sounds
void SoundManager::PlayCowHurtSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        int i = rand()%2;
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(cowHurtSounds[i],volume,volume);
            pgeWavPlay(cowHurtSounds[i]);
        }
    }
}

void SoundManager::PlayCowSaySound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        if(distanceToPlayer < 20.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (20.0f-distanceToPlayer)/20.0f*100.0f;
            pgeWavVolume(cowSaySound,volume,volume);
            pgeWavPlay(cowSaySound);
        }
    }
}

// Chicken Sounds
void SoundManager::PlayChickenHurtSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        int i = rand()%2;
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(chickenHurtSounds[i],volume,volume);
            pgeWavPlay(chickenHurtSounds[i]);
        }
    }
}

void SoundManager::PlayChickenSaySound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        if(distanceToPlayer < 20.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (20.0f-distanceToPlayer)/20.0f*100.0f;
            pgeWavVolume(chickenSaySound,volume,volume);
            pgeWavPlay(chickenSaySound);
        }
    }
}

// Creeper Sounds
void SoundManager::PlayCreeperHurtSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        int i = rand()%2;
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(creeperHurtSounds[i],volume,volume);
            pgeWavPlay(creeperHurtSounds[i]);
        }
    }
}

// Sheep Sounds
void SoundManager::PlaySheepHurtSound(float distanceToPlayer)
{
	if(playerSounds && Ram32 == false)
    {
        int i = rand()%2;
        if(distanceToPlayer < 15.0f)
        {
            distanceToPlayer -= 2.0f;
            if(distanceToPlayer < 0)
            {
                distanceToPlayer = 0.0f;
            }
            float volume = (15.0f-distanceToPlayer)/15.0f*100.0f;
            pgeWavVolume(sheepHurtSounds[i],volume,volume);
            pgeWavPlay(sheepHurtSounds[i]);
        }
    }
}

// Player Sounds
void SoundManager::PlayShieldSound()
{
	if(playerSounds && Ram32 == false)
    {
		pgeWavPlay(shieldSound);
    }
}

void SoundManager::PlayCraftSound()
{
	if(playerSounds && Ram32 == false)
    {
		pgeWavPlay(craftSound);
    }
}

void SoundManager::PlayFailCraftSound()
{
	if(playerSounds && Ram32 == false)
    {
		pgeWavPlay(craftFailSound);
    }
}

void SoundManager::PlayHitSound()
{
	if(playerSounds && Ram32 == false)
    {
		pgeWavPlay(hitSounds[rand() % 3]);
    }
}

void SoundManager::PlayEatSound()
{
	if(playerSounds && Ram32 == false)
    {
		pgeWavPlay(eatSounds[rand() % 3]);
    }
}

void SoundManager::PlayBurpSound()
{
	if(playerSounds && Ram32 == false)
    {
		pgeWavPlay(burpSound);
    }
}


void SoundManager::PlayFallSound(float i)
{
	if(playerSounds && Ram32 == false)
    {
        if (i < -9 && i > -21)
        {
            pgeWavPlay(fallSounds[1]);
        }
        if (i < -21)
        {
            pgeWavPlay(fallSounds[0]);
        }
    }
}

void SoundManager::PlayWalkSound(int type)
{
	if(playerSounds && Ram32 == false)
	{
		switch(type)
		{
			case 0://grass
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(grassSounds[lastWalkSound]);

				//play new sound
				pgeWavPlay(grassSounds[currentWalkSound]);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
			case 1://gravel
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(grawelSounds[lastWalkSound]);

				//play new sound
				pgeWavPlay(grawelSounds[currentWalkSound]);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
			case 2://stone
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(stoneSounds[lastWalkSound]);

				//play new sound
				pgeWavPlay(stoneSounds[currentWalkSound]);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
			case 3://wood
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(woodSounds[lastWalkSound]);

				//play new sound
				pgeWavPlay(woodSounds[currentWalkSound]);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
            case 4://cloth
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(snowSounds[lastWalkSound]);

				//play new sound
				pgeWavPlay(snowSounds[currentWalkSound]);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
            case 5://sand
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(sandSounds[lastWalkSound]);

				//play new sound
				pgeWavPlay(sandSounds[currentWalkSound]);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
            case 6://snow
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(snowSounds[lastWalkSound]);

				//play new sound
				pgeWavPlay(snowSounds[currentWalkSound]);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
		}
	}
}

void SoundManager::PlayDigSound(int type)
{
	if(playerSounds && Ram32 == false)
	{
		switch(type)
		{
			case 0://grass
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(grassSounds[lastWalkSound]);
				pgeWavVolume(grassSounds[lastWalkSound],100,100);

				//play new sound
				pgeWavVolume(grassSounds[currentWalkSound],25,25);
				pgeWavPlay(grassSounds[currentWalkSound]);
				pgeWavVolume(grassSounds[currentWalkSound],100,100);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
			case 1://gravel
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(grawelSounds[lastWalkSound]);
				pgeWavVolume(grawelSounds[lastWalkSound],100,100);

				//play new sound
				pgeWavVolume(grawelSounds[currentWalkSound],25,25);
				pgeWavPlay(grawelSounds[currentWalkSound]);
				pgeWavVolume(grawelSounds[currentWalkSound],100,100);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
			case 2://stone
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(stoneSounds[lastWalkSound]);
				pgeWavVolume(stoneSounds[lastWalkSound],100,100);

				//play new sound
				pgeWavVolume(stoneSounds[currentWalkSound],25,25);
				pgeWavPlay(stoneSounds[currentWalkSound]);
				pgeWavVolume(stoneSounds[currentWalkSound],100,100);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
			case 3://wood
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(woodSounds[lastWalkSound]);
				pgeWavVolume(woodSounds[lastWalkSound],100,100);

				//play new sound
				pgeWavVolume(woodSounds[currentWalkSound],25,25);
				pgeWavPlay(woodSounds[currentWalkSound]);
				pgeWavVolume(woodSounds[currentWalkSound],100,100);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
            case 4://cloth
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(snowSounds[lastWalkSound]);
				pgeWavVolume(snowSounds[lastWalkSound],100,100);

				//play new sound
				pgeWavVolume(snowSounds[currentWalkSound],25,25);
				pgeWavPlay(snowSounds[currentWalkSound]);
				pgeWavVolume(snowSounds[currentWalkSound],100,100);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
            case 5://sand
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(sandSounds[lastWalkSound]);
				pgeWavVolume(sandSounds[lastWalkSound],100,100);

				//play new sound
				pgeWavVolume(sandSounds[currentWalkSound],25,25);
				pgeWavPlay(sandSounds[currentWalkSound]);
				pgeWavVolume(sandSounds[currentWalkSound],100,100);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
            case 6://snow
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				pgeWavStop(snowSounds[lastWalkSound]);
				pgeWavVolume(snowSounds[lastWalkSound],100,100);

				//play new sound
				pgeWavVolume(snowSounds[currentWalkSound],25,25);
				pgeWavPlay(snowSounds[currentWalkSound]);
				pgeWavVolume(snowSounds[currentWalkSound],100,100);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
		}
	}
}

void SoundManager::StopAmbient()
{
    if(ambientTrack != NULL)
    {
        oslStopSound(ambientTrack);
        oslDeleteSound(ambientTrack);
        ambientTrack = NULL;

        ambientTrackName = " ";
    }
}

int SoundManager::PlayRandomAmbient()
{
	if(Ram32 == false)
	{
		switch(rand() % 12)
		{
			case 0: PlayAmbient("calm1"); break;
			case 1: PlayAmbient("calm2"); break;
			case 2: PlayAmbient("calm3"); break;
			case 3: PlayAmbient("piano1"); break;
			case 4: PlayAmbient("piano2"); break;
			case 5: PlayAmbient("piano3"); break;
			case 6: PlayAmbient("nuance1"); break;
			case 7: PlayAmbient("nuance2"); break;
			case 8: PlayAmbient("hal1"); break;
			case 9: PlayAmbient("hal2"); break;
			case 10: PlayAmbient("hal3"); break;
			case 11: PlayAmbient("hal4"); break;
		}
		int delay = 540+rand()%121;
		return delay;
	}
}

void SoundManager::PlayAmbient(std::string name)
{
	if(Ram32 == false)
	{
		StopAmbient();

		ambientTrackName = name;
		std::string trackPath = "Assets/Sounds/ambient/"+name+".bgm";
		ambientTrack = oslLoadSoundFile(trackPath.c_str(),OSL_FMT_STREAM);

		oslPlaySound(ambientTrack,2);
	}
}

//menu
void SoundManager::StopMenu()
{
    if(menuTrack != NULL)
    {
        oslStopSound(menuTrack);
        oslDeleteSound(menuTrack);
        menuTrack = NULL;

        menuTrackName = " ";
    }
}
//menu
int SoundManager::PlayRandomMenu()
{
	if(Ram32 == false)
	{
		switch(rand() % 2)
		{
			case 0: PlayMenu("menu1"); break;
			case 1: PlayMenu("menu2"); break;
		}
	}
}

void SoundManager::PlayMenu(std::string name)
{
	if(Ram32 == false)
	{
		StopMenu();

		menuTrackName = name;
		std::string trackPath = "Assets/Sounds/ambient/menu/"+name+".bgm";
		menuTrack = oslLoadSoundFile(trackPath.c_str(),OSL_FMT_STREAM);

		oslPlaySound(menuTrack,2);
	}
}
//end menu

/// Hell
void SoundManager::StopHell()
{
    if(HellTrack != NULL)
    {
        oslStopSound(HellTrack);
        oslDeleteSound(HellTrack);
        HellTrack = NULL;

        HellTrackName = " ";
    }
}

int SoundManager::PlayRandomHell()
{
 	switch((rand() % 3) + 1)
 	{
 	    case 1: PlayHell("hell1"); break;
 	    case 2: PlayHell("hell2"); break;
 	    case 3: PlayHell("hell3"); break;
 	}
    int delay = 540+rand()%121;
	return delay;
}

void SoundManager::PlayHell(std::string name)
{
    StopHell();

    HellTrackName = name;
    std::string trackPath = "Assets/Sounds/ambient/nether/"+name+".bgm";
    HellTrack = oslLoadSoundFile(trackPath.c_str(),OSL_FMT_STREAM);

    oslPlaySound(HellTrack,2);
}

/// END

void SoundManager::StopDiskTrack()
{
    if(diskTrack != NULL)
    {
        oslStopSound(diskTrack);
        oslDeleteSound(diskTrack);
        diskTrack = NULL;

        diskTrackName = " ";
    }
}

void SoundManager::PlayDiskTrack(int diskNumber)
{
	if(Ram32 == false)
	{
		StopAmbient();
		StopDiskTrack();

		std::string name = " ";
		switch(diskNumber)
		{
			case 0: name = "13"; break;
			case 1: name = "cat"; break;
			case 2: name = "blocks"; break;
			case 3: name = "chirp"; break;
			case 4: name = "far"; break;
			case 5: name = "mall"; break;
			case 6: name = "mellohi"; break;
			case 7: name = "stal"; break;
			case 8: name = "strad"; break;
			case 9: name = "ward"; break;
			case 10: name = "11"; break;
			case 11: name = "wait"; break;
		}
		diskTrackName = name;
		std::string trackPath = "Assets/Sounds/disk/"+name+".bgm";
		diskTrack = oslLoadSoundFile(trackPath.c_str(),OSL_FMT_STREAM);

		oslPlaySound(diskTrack,2);
	}
}

void SoundManager::UnLoadSonds()
{
	pgeWavStopAll();

    pgeWavUnload(buttonSound);
	pgeWavUnload(openchestSound);
	pgeWavUnload(closedchestSound);
	pgeWavUnload(igniteSound);
    pgeWavUnload(doorOpen);
    pgeWavUnload(doorClose);
    pgeWavUnload(breakSound);
    pgeWavUnload(bow);
    pgeWavUnload(plopSound);
    pgeWavUnload(zombieDieSound);
	pgeWavUnload(skeletonDieSound);
    pgeWavUnload(spiderDieSound);
	pgeWavUnload(pigDieSound);
    pgeWavUnload(cowSaySound);
	pgeWavUnload(chickenSaySound);
    pgeWavUnload(fuse);
    pgeWavUnload(fiss);
    pgeWavUnload(splash);
    pgeWavUnload(glass);
    pgeWavUnload(zombieSaySound);
    pgeWavUnload(shear);
	pgeWavUnload(rainSound);
	pgeWavUnload(expSound);
	pgeWavUnload(orbSound);
	pgeWavUnload(tntSounds);
	pgeWavUnload(pigmanSaySound);
	pgeWavUnload(pigmanDieSound);
	pgeWavUnload(shieldSound);
	pgeWavUnload(burpSound);

    for(int i = 0; i <= 3; i++)
    {	
        pgeWavUnload(grassSounds[i]);
        pgeWavUnload(grawelSounds[i]);
        pgeWavUnload(stoneSounds[i]);
        pgeWavUnload(woodSounds[i]);
        pgeWavUnload(sandSounds[i]);
        pgeWavUnload(snowSounds[i]);
    }
    for(int i = 0; i <= 2; i++)
    {
        pgeWavUnload(eatSounds[i]);
        pgeWavUnload(hitSounds[i]);
        pgeWavUnload(digSounds[i]);
        //pgeWavUnload(thunderSounds[i]);
    }
    for(int i = 0; i <= 1; i++)
    {
        pgeWavUnload(fallSounds[i]);
        pgeWavUnload(cowHurtSounds[i]);
		pgeWavUnload(chickenHurtSounds[i]);
		pgeWavUnload(pigHurtSounds[i]);
        pgeWavUnload(creeperHurtSounds[i]);
        pgeWavUnload(zombieHurtSounds[i]);
		pgeWavUnload(skeletonHurtSounds[i]);
        pgeWavUnload(spiderHurtSounds[i]);
        pgeWavUnload(sheepHurtSounds[i]);
        pgeWavUnload(pigmanHurtSounds[i]);
        pgeWavUnload(noteSounds[i]);
        pgeWavUnload(witherSkeletonHurtSound[i]);
    }
}

