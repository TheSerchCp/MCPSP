#include "TextureHelper.h"
#include <Aurora/Graphics/RenderManager.h>

TextureHelper::TextureHelper()
{
	defaulPatch = "Assets/Textures/";
	defaultFolder = "Default/";
	texturePatch = defaulPatch+defaultFolder;
	
	defaultSkin = "skin1.png";
	selectSkin = defaultSkin;
	
	// LangManager, carpeta por defecto
	defaultLangFolder = "en_us";
	langPath = defaultLangFolder;
}

TextureHelper::~TextureHelper()
{

}

void TextureHelper::Init()
{
    LoadTexturePackPath();
	LoadSkinPath();
	LoadLangPath();
    texturePatch = defaulPatch+defaultFolder;
	selectSkin = defaultSkin;
	langPath = defaultLangFolder;

    FastLoadTexture("title/genesis.png");
	
	LoadTex = false;
	staLoad = 0;
}

void TextureHelper::LoadConstTexture()
{
	TextureManager::Instance()->RemoveConstTextures();
	
	FastLoadConstTexture("Error.png");
	
	FastLoadConstTexture("title/background/panorama_0.png");
	FastLoadConstTexture("title/background/panorama_1.png");
	FastLoadConstTexture("title/background/panorama_2.png");
	FastLoadConstTexture("title/background/panorama_3.png");
	FastLoadConstTexture("title/background/panorama_4.png");
	FastLoadConstTexture("title/background/panorama_5.png");
	
	FastLoadConstTexture("Load/infoLoad.png");
	FastLoadConstTexture("Load/steveLoad.png");
	FastLoadConstTexture("Load/steveLoad2.png");
	FastLoadConstTexture("Load/sheepLoad.png");
	FastLoadConstTexture("Load/sheepLoad2.png");
	FastLoadConstTexture("Load/sheepLoad3.png");
	FastLoadConstTexture("Load/sheepLoad4.png");
	FastLoadConstTexture("Load/sheepLoad5.png");
	FastLoadConstTexture("Load/LoadingCycle.png");
	FastLoadConstTexture("Load/LoadingCycle2.png");
	FastLoadConstTexture("Load/LoadingCycle3.png");
	FastLoadConstTexture("Load/LoadingCycle4.png");
	FastLoadConstTexture("Load/LoadingCycle5.png");
	FastLoadConstTexture("Load/LoadingCycle6.png");
	FastLoadConstTexture("Load/LoadingCycle7.png");
	FastLoadConstTexture("Load/LoadingCycle8.png");
	FastLoadConstTexture("Load/LoadingCycle9.png");
}

void TextureHelper::LoadConstTextureMenu()
{
	TextureManager::Instance()->RemoveConstTextures();
	
	FastLoadConstTexture("Error.png");
	
	FastLoadConstTexture("title/background/panorama_0.png");
	FastLoadConstTexture("title/background/panorama_1.png");
	FastLoadConstTexture("title/background/panorama_2.png");
	FastLoadConstTexture("title/background/panorama_3.png");
	FastLoadConstTexture("title/background/panorama_4.png");
	FastLoadConstTexture("title/background/panorama_5.png");
}

void TextureHelper::LoadTextureMenu()
{
	TextureManager::Instance()->RemoveTextures();
	
	FastLoadTexture("Error.png");
	
	FastLoadTexture("title/dirt.png");
	FastLoadTexture("hud/icons2.png");
	

	//FastLoadTexture("skin/" + defaultSkin);

	FastLoadTexture("skin/skin1.png");
	FastLoadTexture("skin/skin2.png");
	FastLoadTexture("skin/skin3.png");
	FastLoadTexture("skin/skin4.png");
	FastLoadTexture("skin/skin5.png");
	
    FastLoadTexture("title/logo.png");
	FastLoadTexture("title/load.png");
    FastLoadTexture("title/choose_rectangles.png");
    FastLoadTexture("title/menu_elements.png");
	FastLoadTexture("title/menu_elements2.png");
	FastLoadTexture("title/menu_buttons.png");
	FastLoadTexture("title/menu/selected_world.png");
	FastLoadTexture("title/menu/deselected_world.png");
	FastLoadTexture("title/menu/selectworldBox.png");
	FastLoadTexture("title/menu/sselectworld.png");
	FastLoadTexture("title/menu/worldinfo.png");
	FastLoadTexture("title/menu/sworldinfo.png");
	FastLoadTexture("title/menu/choose_rectangles.png");
	FastLoadTexture("title/menu/skinselector.png");
	FastLoadTexture("title/nether.png");
	FastLoadTexture("environment/moon.png");
	FastLoadTexture("title/menu/TexturePack.png");
	FastLoadTexture("title/menu/lang_box.png");
	
	staLoad = 0;
	LoadTex = true;
}

void TextureHelper::LoadTextureOptions()
{
	TextureManager::Instance()->RemoveTextures();
	
	FastLoadTexture("Error.png");
	
	FastLoadTexture("title/menu_elements.png");
	FastLoadTexture("title/optionsMenu.png");
	
	staLoad = 0;
	LoadTex = true;
}

void TextureHelper::LoadInventory(int Inv)
{
	TextureManager::Instance()->RemoveConstTextures();
	
	FastLoadConstTexture("Error.png");
	switch(Inv)
	{
		case 0: //Inv
			FastLoadConstTexture("gui/inventory.png");
		break;
		case 1: //Inv Creative
			FastLoadConstTexture("gui/inventory_creative.png");
		break;
		case 2: //Inv Crafting
			FastLoadConstTexture("gui/crafting_table.png");
		break;
		case 3: //Inv Chest
			FastLoadConstTexture("gui/chest.png");
		break;
		case 4: //Inv Fundace
			FastLoadConstTexture("gui/furnace.png");
		break;
		case 5:
			FastLoadConstTexture("gui/inventory_Village.png");
		break;
	}
}

void TextureHelper::UnLoadInventory()
{
	TextureManager::Instance()->RemoveConstTextures();
	
	FastLoadConstTexture("Error.png");
}

void TextureHelper::LoadTextureStatePlay()
{
	TextureManager::Instance()->RemoveTextures();
	
	FastLoadTexture("Error.png");

	FastLoadTexture("title/load.png");
	FastLoadTexture("skin/" + defaultSkin);
	FastLoadTexture("title/nether.png");
	FastLoadTexture("title/menu_elements.png");
	FastLoadTexture("title/menu_options.png");
	FastLoadTexture("title/About.png");
	FastLoadTexture("title/About_2.png");
	FastLoadTexture("title/logo.png");
	FastLoadTexture("title/dirt.png");
	FastLoadTexture("environment/moon.png");
    FastLoadTexture("hud/utils.png");
    FastLoadTexture("hud/icons.png");
	FastLoadTexture("hud/icons2.png");
    FastLoadTexture("terrain.png");
    FastLoadTexture("terrain_mips.png");
    FastLoadTexture("water_still.png");
    FastLoadTexture("lava_still.png");
	FastLoadTexture("fire_still.png");
    FastLoadTexture("items.png");
    FastLoadTexture("hud/blue.png");
    FastLoadTexture("environment/sun.png");
    FastLoadTexture("environment/moon.png");
    FastLoadTexture("environment/stars.png");
    FastLoadTexture("entity/snowball.png");
	FastLoadTexture("entity/arrow.png");
    FastLoadTexture("entity/zombie.png");
    FastLoadTexture("entity/pigman.png");
    FastLoadTexture("entity/wither_skeleton.png");
	FastLoadTexture("entity/skeleton.png");
    FastLoadTexture("entity/spider.png");
    FastLoadTexture("entity/cave_spider.png");
    FastLoadTexture("hud/red.png");
	FastLoadTexture("hud/purple.png");
    FastLoadTexture("hud/black.png");
    FastLoadTexture("hud/pumpkinblur.png");
    FastLoadTexture("environment/clouds.png");
    //FastLoadTexture("gui/inventory.png");
    //FastLoadTexture("gui/inventory_creative.png");
    //FastLoadTexture("gui/crafting_table.png");
	FastLoadTexture("gui/select_inventory_Village.png");
	FastLoadTexture("gui/craftingSelection.png");
	FastLoadTexture("gui/craftingPagSelection.png");
	FastLoadTexture("gui/cell_red.png");
	FastLoadTexture("gui/crafting_table2.png");
    //FastLoadTexture("gui/chest.png");
    //FastLoadTexture("gui/furnace.png");
    FastLoadTexture("gui/cursor.png");
    FastLoadTexture("gui/slider.png");
    FastLoadTexture("gui/fire.png");
	FastLoadTexture("gui/arrow.png");
	FastLoadTexture("gui/cell.png");
	FastLoadTexture("gui/tabsSe.png");
	FastLoadTexture("armor/cloth_1.png");
	FastLoadTexture("armor/cloth_2.png");
	FastLoadTexture("armor/chain_1.png");
	FastLoadTexture("armor/chain_2.png");
	FastLoadTexture("armor/iron_1.png");
	FastLoadTexture("armor/iron_2.png");
	FastLoadTexture("armor/diamond_1.png");
	FastLoadTexture("armor/diamond_2.png");
	FastLoadTexture("armor/gold_1.png");
	FastLoadTexture("armor/gold_2.png");
	FastLoadTexture("entity/cow.png");
	FastLoadTexture("entity/chicken.png");
	FastLoadTexture("entity/pig.png");
	FastLoadTexture("entity/thepig.png");
	//Villagers
	FastLoadTexture("entity/villager/villager.png");
	FastLoadTexture("entity/villager/butcher.png");
	FastLoadTexture("entity/villager/farmer.png");
	FastLoadTexture("entity/villager/librarian.png");
	FastLoadTexture("entity/villager/priest.png");
	FastLoadTexture("entity/villager/smith.png");
	
	//Wolf
	FastLoadTexture("entity/wolf/wolf.png");
	
    FastLoadTexture("particle/smoke.png");
	FastLoadTexture("particle/flame.png");
	FastLoadTexture("particle/note.png");
	FastLoadTexture("particle/bubble.png");
	FastLoadTexture("particle/explosion.png");
	FastLoadTexture("particle/heart.png");
	FastLoadTexture("colormap/grass.png");
	FastLoadTexture("item/clock.png");
	FastLoadTexture("item/compass.png");
	FastLoadTexture("environment/sky_color.png");
	FastLoadTexture("environment/rain.png");
	FastLoadTexture("environment/snow.png");
	FastLoadTexture("entity/creeper.png");
	FastLoadTexture("entity/sheep.png");
	FastLoadTexture("entity/sheep_fur.png");
	FastLoadTexture("hell_portal.png");
	FastLoadTexture("gui/Achievements.png");
	
	staLoad = 0;
	LoadTex = true;
}

int TextureHelper::GetTexture(Textures texture)
{
	int LoadTrue  = 0;
	switch(texture)
	{
		case Genesis:
		{
			fileName = texturePatch + "title/genesis.png";
			
		}
		break;
		case SelectinvTrad:
		{
			fileName = texturePatch + "gui/select_inventory_Village.png";
		}
		break;
		case Logo:
		{
			fileName = texturePatch + "environment/moon.png";
			
		}
		break;
		case Utils:
		{
			fileName = texturePatch + "hud/utils.png";
			
		}
		break;
		case Icons:
		{
			fileName = texturePatch + "hud/icons.png";
			
		}
		break;
		case Icons2:
		{
			fileName = texturePatch + "hud/icons2.png";
			
		}
		break;
		case Dirt:
		{
			fileName = texturePatch + "title/dirt.png";
			
		}
		break;
		case Nether:
		{
			fileName = texturePatch + "title/nether.png";
			
		}
		break;
		case Terrain1:
		{
			fileName = texturePatch + "terrain.png";
			
		}
		break;
		case Terrain2:
		{
			fileName = texturePatch + "terrain_mips.png";
			
		}
		break;
		case WaterAnimation:
		{
			fileName = texturePatch + "water_still.png";
			
		}
		break;
		case LavaAnimation:
		{
			fileName = texturePatch + "lava_still.png";
			
		}
		break;
		case FireAnimation:
		{
			fileName = texturePatch + "fire_still.png";
			
		}
		break;
		case Items1:
		{
			fileName = texturePatch + "items.png";
			
		}
		break;
		case Blue:
		{
			fileName = texturePatch + "hud/blue.png";
			
		}
		break;
		case Sun:
		{
			fileName = texturePatch + "environment/sun.png";
			
		}
		break;
		case Moon:
		{
			fileName = texturePatch + "environment/moon.png";
			
		}
		break;
		case Stars:
		{
			fileName = texturePatch + "environment/stars.png";
			
		}
		break;
		case SnowBall3:
		{
			fileName = texturePatch + "entity/snowball.png";
			
		}
		break;
		case Arrow3:
		{
			fileName = texturePatch + "entity/arrow.png";
			
		}
		break;
		case zombieTexture:
		{
			fileName = texturePatch + "entity/zombie.png";
			
		}
		break;
		case pigmanTexture:
		{
			fileName = texturePatch + "entity/pigman.png";
			
		}
		break;
		case witherskeletonTexture:
		{
			fileName = texturePatch + "entity/wither_skeleton.png";
			
		}
		break;
		case skeletonTexture:
		{
			fileName = texturePatch + "entity/skeleton.png";
			
		}
		break;
		case spiderTexture:
		{
			fileName = texturePatch + "entity/spider.png";
			
		}
		break;
		case cavespiderTexture:
		{
			fileName = texturePatch + "entity/cave_spider.png";
			
		}
		break;
		case Steve:
		{
			fileName = texturePatch + "skin/" + defaultSkin;
			
		}
		break;
		case Skin1:
		{
			fileName = texturePatch + "skin/skin1.png";
			
		}
		break;
		case Skin2:
		{
			fileName = texturePatch + "skin/skin2.png";
			
		}
		break;
		case Skin3:
		{
			fileName = texturePatch + "skin/skin3.png";
			
		}
		break;
		case Skin4:
		{
			fileName = texturePatch + "skin/skin4.png";
			
		}
		break;
		case Skin5:
		{
			fileName = texturePatch + "skin/skin5.png";
			
		}
		break;
		case lameCraft:
		{
			fileName = texturePatch + "title/logo.png";
			
		}
		break;
		case Buttons:
		{
			fileName = texturePatch + "title/menu_elements.png";
			
		}
		break;
		case Buttons2:
		{
			fileName = texturePatch + "title/menu_elements2.png";
			
		}
		break;
		case NewButtons:
		{
			fileName = texturePatch + "title/menu_buttons.png";
			
		}
		break;
		//menu
		case World:
		{
			fileName = texturePatch + "title/menu/selected_world.png";
			
		}
		break;
		case DeselectedWorld:
		{
			fileName = texturePatch + "title/menu/deselected_world.png";
			
		}
		break;
		case selectworldBox:
		{
			fileName = texturePatch + "title/menu/selectworldBox.png";
			
		}
		break;
		case sselectworld:
		{
			fileName = texturePatch + "title/menu/sselectworld.png";
			
		}
		break;
		case worldinfo:
		{
			fileName = texturePatch + "title/menu/worldinfo.png";
			
		}
		break;
		case sworldinfo:
		{
			fileName = texturePatch + "title/menu/sworldinfo.png";
			
		}
		break;
		case skinselectButtons:
		{
			fileName = texturePatch + "title/menu/choose_rectangles.png";
			
		}
		break;
		case skinselector:
		{
			fileName = texturePatch + "title/menu/skinselector.png";
			
		}
		break;
		case Rectangles:
		{
			fileName = texturePatch + "title/choose_rectangles.png";
			
		}
		break;
		case Load:
		{
			fileName = texturePatch + "title/load.png";
			
		}
		break;
		case About:
		{
			fileName = texturePatch + "title/About.png";
			
		}
		break;
		case About2:
		{
			fileName = texturePatch + "title/About_2.png";
			
		}
		break;
		case MOptions:
		{
			fileName = texturePatch + "title/menu_options.png";
			
		}
		break;
		case Red:
		{
			fileName = texturePatch + "hud/red.png";
			
		}
		break;
		case Purple:
		{
			fileName = texturePatch + "hud/purple.png";
			
		}
		break;
		case Black:
		{
			fileName = texturePatch + "hud/black.png";
			
		}
		break;
		case PumpkinMask:
		{
			fileName = texturePatch + "hud/pumpkinblur.png";
			
		}
		break;
		case clouds:
		{
			fileName = texturePatch + "environment/clouds.png";
			
		}
		break;
		case inv:
		{
			fileName = texturePatch + "gui/inventory.png";
			
		}
		break;
		case invCreative:
		{
			fileName = texturePatch + "gui/inventory_creative.png";
			
		}
		break;
		case invTrad:
		{
			fileName = texturePatch + "gui/inventory_Village.png";
		}
		break;
		case crt:
		{
			fileName = texturePatch + "gui/crafting_table.png";
			
		}
		break;
		case crtSelect:
		{
			fileName = texturePatch + "gui/craftingSelection.png";
			
		}
		break;
		case crtSelectPag:
		{
			fileName = texturePatch + "gui/craftingPagSelection.png";
			
		}
		break;
		case crtRed:
		{
			fileName = texturePatch + "gui/cell_red.png";
			
		}
		break;
		case crt2:
		{
			fileName = texturePatch + "gui/crafting_table2.png";
			
		}
		break;
		case cht:
		{
			fileName = texturePatch + "gui/chest.png";
			
		}
		break;
		case fur:
		{
			fileName = texturePatch + "gui/furnace.png";
			
		}
		break;
		case cursor:
		{
			fileName = texturePatch + "gui/cursor.png";
			
		}
		break;
		case invSlider:
		{
			fileName = texturePatch + "gui/slider.png";
			
		}
		break;
		case furFire:
		{
			fileName = texturePatch + "gui/fire.png";
			
		}
		break;
		case furArrow:
		{
			fileName = texturePatch + "gui/arrow.png";
			
		}
		break;
		case invCell:
		{
			fileName = texturePatch + "gui/cell.png";
			
		}
		break;
		case tapsSel:
		{
			fileName = texturePatch + "gui/tabsSe.png";
			
		}
		break;
		case leatherArmor1:
		{
			fileName = texturePatch + "armor/cloth_1.png";
			
		}
		break;
		case leatherArmor2:
		{
			fileName = texturePatch + "armor/cloth_2.png";
			
		}
		break;
		case chainmailArmor1:
		{
			fileName = texturePatch + "armor/chain_1.png";
			
		}
		break;
		case chainmailArmor2:
		{
			fileName = texturePatch + "armor/chain_2.png";
			
		}
		break;
		case ironArmor1:
		{
			fileName = texturePatch + "armor/iron_1.png";
			
		}
		break;
		case ironArmor2:
		{
			fileName = texturePatch + "armor/iron_2.png";
			
		}
		break;
		case diamondArmor1:
		{
			fileName = texturePatch + "armor/diamond_1.png";
			
		}
		break;
		case diamondArmor2:
		{
			fileName = texturePatch + "armor/diamond_2.png";
			
		}
		break;
		case goldenArmor1:
		{
			fileName = texturePatch + "armor/gold_1.png";
			
		}
		break;
		case goldenArmor2:
		{
			fileName = texturePatch + "armor/gold_2.png";
			
		}
		break;
		case cowTexture:
		{
			fileName = texturePatch + "entity/cow.png";
			
		}
		break;
		case chickenTexture:
		{
			fileName = texturePatch + "entity/chicken.png";
			
		}
		break;
		case pigTexture:
		{
			fileName = texturePatch + "entity/pig.png";
			
		}
		break;
		case villagerTexture:
		{
			fileName = texturePatch + "entity/villager/villager.png";
			
		}
		break;
		case butcherTexture:
		{
			fileName = texturePatch + "entity/villager/butcher.png";
		}
		break;
		case farmerTexture:
		{
			fileName = texturePatch + "entity/villager/farmer.png";
		}
		break;
		case librarianTexture:
		{
			fileName = texturePatch + "entity/villager/librarian.png";
		}
		break;
		case priestTexture:
		{
			fileName = texturePatch + "entity/villager/priest.png";
		}
		break;
		case smithTexture:
		{
			fileName = texturePatch + "entity/villager/smith.png";
		}
		break;
		case wolfTexture:
		{
			fileName = texturePatch + "entity/wolf/wolf.png";
		}
		break;
		case juanalbertoTexture:
		{
			fileName = texturePatch + "entity/thepig.png";
		}
		break;
		case smokeTexture:
		{
			fileName = texturePatch + "particle/smoke.png";
			
		}
		break;
		case flameTexture:
		{
			fileName = texturePatch + "particle/flame.png";
			
		}
		break;
		case noteTexture:
		{
			fileName = texturePatch + "particle/note.png";
			
		}
		break;
		case bubbleTexture:
		{
			fileName = texturePatch + "particle/flame.png";
			
		}
		break;
		case explosionTexture:
		{
			fileName = texturePatch + "particle/explosion.png";
			
		}
		break;
		case heartTexture:
		{
			fileName = texturePatch + "particle/heart.png";
			
		}
		break;
		case vegetationColorMap:
		{
			fileName = texturePatch + "colormap/grass.png";
			
		}
		break;
		case clockTexture:
		{
			fileName = texturePatch + "item/clock.png";
			
		}
		break;
		case compassTexture:
		{
			fileName = texturePatch + "item/compass.png";
			
		}
		break;
		case skyColorTexture:
		{
			fileName = texturePatch + "environment/sky_color.png";
			
		}
		break;
		case rainTexture:
		{
			fileName = texturePatch + "environment/rain.png";
			
		}
		break;
		case snowTexture:
		{
			fileName = texturePatch + "environment/snow.png";
			
		}
		break;
		case creeperTexture:
		{
			fileName = texturePatch + "entity/creeper.png";
			
		}
		break;
		case sheepTexture:
		{
			fileName = texturePatch + "entity/sheep.png";
			
		}
		break;
		case sheepFurTexture:
		{
			fileName = texturePatch + "entity/sheep_fur.png";
			
		}
		break;
		case HellPortalAnimation:
		{
			fileName = texturePatch + "hell_portal.png";
			
		}
		break;
		case Achievements:
		{
			fileName = texturePatch + "gui/Achievements.png";
			
		}
		break;
		case menuOptions:
		{
			fileName = texturePatch + "title/optionsMenu.png";
			
		}
		break;
		case menuTexture:
		{
			fileName = texturePatch + "title/menu/TexturePack.png";
			
		}
		break;
		case langBoxTexture:
		{
			fileName = texturePatch + "title/menu/lang_box.png";
			
		}
		break;
		case Panorama0:
		{
			fileName = texturePatch + "title/background/panorama_0.png";
		}
		break;
		case Panorama1:
		{
			fileName = texturePatch + "title/background/panorama_1.png";
		}
		break;
		case Panorama2:
		{
			fileName = texturePatch + "title/background/panorama_2.png";
		}
		break;
		case Panorama3:
		{
			fileName = texturePatch + "title/background/panorama_3.png";
		}
		break;
		case Panorama4:
		{
			fileName = texturePatch + "title/background/panorama_4.png";
		}
		break;
		case Panorama5:
		{
			fileName = texturePatch + "title/background/panorama_5.png";
		}
		break;
		case infLoad:
		{
			fileName = texturePatch + "Load/infoLoad.png";
		}
		break;
		case steveLoad:
		{
			fileName = texturePatch + "Load/steveLoad.png";
		}
		break;
		case steveLoad2:
		{
			fileName = texturePatch + "Load/steveLoad2.png";
		}
		break;
		case sheepLoad:
		{
			fileName = texturePatch + "Load/sheepLoad.png";
		}
		break;
		case sheepLoad2:
		{
			fileName = texturePatch + "Load/sheepLoad2.png";
		}
		break;
		case sheepLoad3:
		{
			fileName = texturePatch + "Load/sheepLoad3.png";
		}
		break;
		case sheepLoad4:
		{
			fileName = texturePatch + "Load/sheepLoad4.png";
		}
		break;
		case sheepLoad5:
		{
			fileName = texturePatch + "Load/sheepLoad5.png";
		}
		break;
		case LoadingCycle:
		{
			fileName = texturePatch + "Load/LoadingCycle.png";
		}
		break;
		case LoadingCycle2:
		{
			fileName = texturePatch + "Load/LoadingCycle2.png";
		}
		break;
		case LoadingCycle3:
		{
			fileName = texturePatch + "Load/LoadingCycle3.png";
		}
		break;
		case LoadingCycle4:
		{
			fileName = texturePatch + "Load/LoadingCycle4.png";
		}
		break;
		case LoadingCycle5:
		{
			fileName = texturePatch + "Load/LoadingCycle5.png";
		}
		break;
		case LoadingCycle6:
		{
			fileName = texturePatch + "Load/LoadingCycle6.png";
		}
		break;
		case LoadingCycle7:
		{
			fileName = texturePatch + "Load/LoadingCycle7.png";
		}
		break;
		case LoadingCycle8:
		{
			fileName = texturePatch + "Load/LoadingCycle8.png";
		}
		break;
		case LoadingCycle9:
		{
			fileName = texturePatch + "Load/LoadingCycle9.png";
		}
		break;
	}
	
	
	if(texture == Panorama0
	|| texture == Panorama1
	|| texture == Panorama2
	|| texture == Panorama3
	|| texture == Panorama4
	|| texture == Panorama5
	|| texture == infLoad
	|| texture == steveLoad
	|| texture == steveLoad2
	|| texture == sheepLoad
	|| texture == sheepLoad2
	|| texture == sheepLoad3
	|| texture == sheepLoad4
	|| texture == sheepLoad5
	|| texture == LoadingCycle
	|| texture == LoadingCycle2
	|| texture == LoadingCycle3
	|| texture == LoadingCycle4
	|| texture == LoadingCycle5
	|| texture == LoadingCycle6
	|| texture == LoadingCycle7
	|| texture == LoadingCycle8
	|| texture == LoadingCycle9
	|| texture == fur
	|| texture == inv
	|| texture == invCreative
	|| texture == cht
	|| texture == invTrad
	|| texture == crt)
	{
		LoadTrue = TextureManager::Instance()->GetConstTextureNumber(fileName);
			
		if(LoadTrue == -1) return TextureManager::Instance()->GetConstTextureNumber(texturePatch + "Error.png");
		else return TextureManager::Instance()->GetConstTextureNumber(fileName);
	}
	else
	{
		LoadTrue = TextureManager::Instance()->GetTextureNumber(fileName);
			
		if(LoadTrue == -1) return TextureManager::Instance()->GetTextureNumber(texturePatch + "Error.png");
		else return TextureManager::Instance()->GetTextureNumber(fileName);
	}
	
	return 0;
}

void TextureHelper::SetSkin(std::string name)
{
	TextureManager::Instance()->RemoveTextures();
	SetSkinSelection(name);
	
	FastLoadTexture("Error.png");
	
	FastLoadTexture("title/dirt.png");
	FastLoadTexture("hud/icons2.png");
	

	//FastLoadTexture("skin/" + defaultSkin);

	FastLoadTexture("skin/skin1.png");
	FastLoadTexture("skin/skin2.png");
	FastLoadTexture("skin/skin3.png");
	FastLoadTexture("skin/skin4.png");
	FastLoadTexture("skin/skin5.png");
	
    FastLoadTexture("title/logo.png");
	FastLoadTexture("title/load.png");
    FastLoadTexture("title/choose_rectangles.png");
    FastLoadTexture("title/menu_elements.png");
	FastLoadTexture("title/menu_elements2.png");
	FastLoadTexture("title/menu_buttons.png");
	FastLoadTexture("title/menu/selected_world.png");
	FastLoadTexture("title/menu/deselected_world.png");
	FastLoadTexture("title/menu/selectworldBox.png");
	FastLoadTexture("title/menu/sselectworld.png");
	FastLoadTexture("title/menu/worldinfo.png");
	FastLoadTexture("title/menu/sworldinfo.png");
	FastLoadTexture("title/menu/choose_rectangles.png");
	FastLoadTexture("title/menu/skinselector.png");
	FastLoadTexture("title/nether.png");
	FastLoadTexture("environment/moon.png");
	FastLoadTexture("title/menu/TexturePack.png");
	FastLoadTexture("title/menu/lang_box.png");
	
	TextureManager::Instance()->RemoveConstTextures();
	
	FastLoadConstTexture("Error.png");
	
	FastLoadConstTexture("title/background/panorama_0.png");
	FastLoadConstTexture("title/background/panorama_1.png");
	FastLoadConstTexture("title/background/panorama_2.png");
	FastLoadConstTexture("title/background/panorama_3.png");
	FastLoadConstTexture("title/background/panorama_4.png");
	FastLoadConstTexture("title/background/panorama_5.png");
}

void TextureHelper::SetTexturePack(std::string name)
{
    TextureManager::Instance()->RemoveTextures();

	SetTextureFolderName(name+"/");
	
	FastLoadTexture("Error.png");
		
	FastLoadTexture("title/dirt.png");
	FastLoadTexture("hud/icons2.png");
	

	//FastLoadTexture("skin/" + defaultSkin);

	FastLoadTexture("skin/skin1.png");
	FastLoadTexture("skin/skin2.png");
	FastLoadTexture("skin/skin3.png");
	FastLoadTexture("skin/skin4.png");
	FastLoadTexture("skin/skin5.png");
	
    FastLoadTexture("title/logo.png");
	FastLoadTexture("title/load.png");
    FastLoadTexture("title/choose_rectangles.png");
    FastLoadTexture("title/menu_elements.png");
	FastLoadTexture("title/menu_elements2.png");
	FastLoadTexture("title/menu_buttons.png");
	FastLoadTexture("title/menu/selected_world.png");
	FastLoadTexture("title/menu/deselected_world.png");
	FastLoadTexture("title/menu/selectworldBox.png");
	FastLoadTexture("title/menu/sselectworld.png");
	FastLoadTexture("title/menu/worldinfo.png");
	FastLoadTexture("title/menu/sworldinfo.png");
	FastLoadTexture("title/menu/choose_rectangles.png");
	FastLoadTexture("title/menu/skinselector.png");
	FastLoadTexture("title/nether.png");
	FastLoadTexture("environment/moon.png");
	FastLoadTexture("title/menu/TexturePack.png");
	FastLoadTexture("title/menu/lang_box.png");

	TextureManager::Instance()->RemoveConstTextures();
	
	FastLoadConstTexture("Error.png");
	
	FastLoadConstTexture("title/background/panorama_0.png");
	FastLoadConstTexture("title/background/panorama_1.png");
	FastLoadConstTexture("title/background/panorama_2.png");
	FastLoadConstTexture("title/background/panorama_3.png");
	FastLoadConstTexture("title/background/panorama_4.png");
	FastLoadConstTexture("title/background/panorama_5.png");
}

void TextureHelper::FastRemoveTexture(std::string name)
{
	std::string endName = texturePatch+name;
	
	int removeimg = TextureManager::Instance()->GetTextureNumber(endName);
	
	TextureManager::Instance()->RemoveTexture(removeimg);
}

void TextureHelper::RemoveConstTextures()
{
    TextureManager::Instance()->RemoveConstTextures();
}

void TextureHelper::FastLoadTexture(std::string name)
{
    std::string endName = texturePatch+name;
    TextureManager::Instance()->LoadTexture(endName);
}

void TextureHelper::FastLoadConstTexture(std::string name)
{
    std::string endName = texturePatch+name;
    TextureManager::Instance()->LoadConstTexture(endName);
}

void TextureHelper::SetTextureFolderName(std::string name)
{
	defaultFolder = name;
	texturePatch = defaulPatch + defaultFolder;
	SaveTexturePackPath();
}

void TextureHelper::SetSkinSelection(std::string name)
{
	defaultSkin = name;
	SaveSkinSelection();
}

void TextureHelper::SaveSkinSelection()
{
	unsigned int pathLength = defaultSkin.size();

	FILE * pFile;
	pFile = fopen("Config/skin.cf","wb");
	
	if(pFile == NULL)
		return;

    fwrite(&pathLength,sizeof(unsigned int),1,pFile);
	fwrite(defaultSkin.c_str(),1,pathLength,pFile);

	//close file
	fclose(pFile);
}

void TextureHelper::SaveTexturePackPath()
{
	unsigned int pathLength = defaultFolder.size();

	FILE * pFile;
	pFile = fopen("Config/texturepack.cf","wb");

	if(pFile == NULL)
		return;

    fwrite(&pathLength,sizeof(unsigned int),1,pFile);
	fwrite(defaultFolder.c_str(),1,pathLength,pFile);

	//close file
	fclose(pFile);
}

void TextureHelper::LoadTexturePackPath()
{
	unsigned int pathLength = 0;

	FILE * pFile;
	pFile = fopen("Config/texturepack.cf","rb");

    if(pFile == NULL)
    {
        defaultFolder = "Default/";
        return;
    }

    fread(&pathLength,sizeof(unsigned int),1,pFile);
	char* c = new char[pathLength+1];
    fread(c,1,pathLength,pFile);
    c[pathLength] = '\0';
    defaultFolder = c;
    delete[] c;

	//close file
	fclose(pFile);

	if(fileExists(defaulPatch+defaultFolder+"terrain.png") == false) // if this texture pack doesn't exist at the moment
    {
        defaultFolder = "Default/"; // return to default one
    }
}

void TextureHelper::LoadSkinPath()
{
	unsigned int pathLengthSkin = 0;

	FILE * pFile;
	pFile = fopen("Config/skin.cf","rb");

    if(pFile == NULL)
    {
        defaultSkin = "skin1.png";
        return;
    }

    fread(&pathLengthSkin,sizeof(unsigned int),1,pFile);
	char* d = new char[pathLengthSkin+1];
    fread(d,1,pathLengthSkin,pFile);
    d[pathLengthSkin] = '\0';
    defaultSkin = d;
    delete[] d;

	//close file
	fclose(pFile);
}

// Establecer la direccion de la carpeta para el selector de idiomas (path: Assets/Lang/<folder name>)
void TextureHelper::SetLangPath(std::string folderName)
{
	// Establecemos el nombre de la carpeta
	defaultLangFolder = folderName;
	SaveLangPath();
}

// Obtener el directorio de la carpeta
void TextureHelper::LoadLangPath()
{
	unsigned int pathLangFolderName = 0;

	FILE * pFile;
	pFile = fopen("Config/langManager.cf","rb");

    if(pFile == NULL)
    {
        defaultLangFolder = "en_us";
        return;
    }

    fread(&pathLangFolderName,sizeof(unsigned int),1,pFile);
	char* d = new char[pathLangFolderName+1];
    fread(d,1,pathLangFolderName,pFile);
    d[pathLangFolderName] = '\0';
    defaultLangFolder = d;
    delete[] d;
	
	fclose(pFile);
}

// Guardar el directorio (folder name) a langManager.cf (path: Config/langManager.cf)
void TextureHelper::SaveLangPath()
{
	unsigned int pathLangLength = defaultLangFolder.size();

	FILE * pFile;
	pFile = fopen("Config/langManager.cf","wb");

	if(pFile == NULL) return;
	
    fwrite(&pathLangLength,sizeof(unsigned int),1,pFile);
	fwrite(defaultLangFolder.c_str(),1,pathLangLength,pFile);

	//close file
	fclose(pFile);
}

inline bool TextureHelper::fileExists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}


TextureHelper TextureHelper::m_TextureHelper;

TextureHelper* TextureHelper::Instance()
{
	return &m_TextureHelper;
}
