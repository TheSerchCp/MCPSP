#ifndef TEXTUREHELPER_H_
#define TEXTUREHELPER_H_

#include <string>
#include <pspiofilemgr.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

class TextureHelper
{
private:

	std::string defaulPatch;
	std::string fileName;

public:
	
	std::string defaultSkin;
	std::string selectSkin;
	
	enum Textures
	{
		Genesis,
		Logo,
		Utils,
		Icons,
		Icons2,
		Dirt,
		Nether,
		Terrain1,
		Terrain2,
		WaterAnimation,
		LavaAnimation,
		FireAnimation,
		Items1,
		Blue,
		Sun,
		Moon,
		Stars,
		SnowBall3,
		Arrow3,
		zombieTexture,
		pigmanTexture,
		witherskeletonTexture,
		skeletonTexture,
		spiderTexture,
		cavespiderTexture,
		Steve,
		Skin1,
		Skin2,
		Skin3,
		Skin4,
		Skin5,
		skinselectButtons,
		lameCraft,
		Buttons,
		Buttons2,
		NewButtons,
		World,
		DeselectedWorld,
		selectworldBox,
		sselectworld,
		skinselector,
		worldinfo,
		sworldinfo,
		Rectangles,
		Load,
		LoadBlack,
		About,
		About2,
		MOptions,
		Red,
		Purple,
		Black,
		PumpkinMask,
		clouds,
		inv,
		invCreative,
		crt,
		crtSelect,
		crtSelectPag,
		crtRed,
		crt2,
		cht,
		fur,
		cursor,
		invSlider,
		furFire,
		furArrow,
		invCell,
		tapsSel,
		leatherArmor1,
		leatherArmor2,
		chainmailArmor1,
		chainmailArmor2,
		ironArmor1,
		ironArmor2,
		diamondArmor1,
		diamondArmor2,
		goldenArmor1,
		goldenArmor2,
		cowTexture,
		chickenTexture,
		pigTexture,
		villagerTexture,
		butcherTexture,
		farmerTexture,
		librarianTexture,
		priestTexture,
		smithTexture,
		wolfTexture,
		juanalbertoTexture,
		smokeTexture,
		flameTexture,
		noteTexture,
		bubbleTexture,
		explosionTexture,
		heartTexture,
		vegetationColorMap,
		clockTexture,
		compassTexture,
		skyColorTexture,
		rainTexture,
		snowTexture,
		creeperTexture,
		sheepTexture,
		sheepFurTexture,
		HellPortalAnimation,
		Achievements,
		Panorama0,
		Panorama1,
		Panorama2,
		Panorama3,
		Panorama4,
		Panorama5,
		infLoad,
		steveLoad,
		steveLoad2,
		sheepLoad,
		sheepLoad2,
		sheepLoad3,
		sheepLoad4,
		sheepLoad5,
		LoadingCycle,
		LoadingCycle2,
		LoadingCycle3,
		LoadingCycle4,
		LoadingCycle5,
		LoadingCycle6,
		LoadingCycle7,
		LoadingCycle8,
		LoadingCycle9,
		menuOptions,
		menuTexture,
		langBoxTexture,
		invTrad,
		SelectinvTrad,
	};
    
	std::string texturePatch;
    std::string defaultFolder;

	static TextureHelper m_TextureHelper;
	static TextureHelper* Instance();


	TextureHelper();
	~TextureHelper();

	int GetTexture(Textures texture);
	
	bool LoadTex;
	int staLoad;
	
    void Init();
	
	void LoadTextureStatePlay();
	void LoadTextureMenu();
	void LoadTextureOptions();
	
	void LoadInventory(int Inv);
	void UnLoadInventory();
	
	void LoadConstTexture();
	void LoadConstTextureMenu();
	
	void FastLoadConstTexture(std::string name);
	
    void FastRemoveTexture(std::string name);
    void FastLoadTexture(std::string name);
	void SetTextureFolderName(std::string name);
	void SetTexturePack(std::string name);
	void SetSkin(std::string name);
	void SetSkinSelection(std::string name);

    void RemoveConstTextures();

    void LoadTexturePackPath();
	void LoadSkinPath();
    void SaveTexturePackPath();
	void SaveSkinSelection();
	
	// Lang Manager properties
	void SetLangPath(std::string folderName);
	void LoadLangPath();
	void SaveLangPath();
	std::string defaultLangFolder;
	std::string langPath;
	
    inline bool fileExists(const std::string& name);
};

#endif
