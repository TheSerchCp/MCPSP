#include "Recipes.h"

#define ENGLISH 1
#define RUSSIAN 2

Recipes Recipes::m_Recipes;

Recipes* Recipes::Instance()
{
	return &m_Recipes;
}

Recipes::Recipes()
{
	craft2x2 = false;
}

Recipes::~Recipes()
{

}

void Recipes::Init()
{
	//Index
	if(IndexId.empty())
	{
		IndexId.push_back(34); //Oak
		IndexId.push_back(276); //Stick
		IndexId.push_back(216); //Quears
		IndexId.push_back(26); //SandStone
		IndexId.push_back(105); //Crafting
		
		if(!craft2x2)
		{
			IndexId.push_back(96); //Chest
			IndexId.push_back(361); //Bed
			IndexId.push_back(159); //Fence
			IndexId.push_back(306); //Door
			IndexId.push_back(67); //Stair
			IndexId.push_back(83); //Slab
		}
		
		//Slot Oak
		SlotId.push_back(34);
		SlotAm.push_back(4);
		SlotSt.push_back(1);
		
		//Requisitos
		ReSlotId.push_back(8);
		ReSlotAm.push_back(1);
		//Preview
		ReSlotPreview.push_back(8);
		
		//Slot birch
		SlotId.push_back(155);
		SlotAm.push_back(4);
		SlotSt.push_back(1);
		
		//Slot Supruce
		SlotId.push_back(156);
		SlotAm.push_back(4);
		SlotSt.push_back(1);
	}
}
//Para ocupar distintas maderas para un solo crafteo se utiliza 3401 y si es es con la lana 1001, si es con arena 7001
void Recipes::UpdateIndex(int Index)
{
	SlotId.clear();
	SlotAm.clear();
	SlotSt.clear();
			
	switch(Index)
	{
		case 34: //Planks
		{
			//Slot Oak - Inicio
			SlotId.push_back(34);
			SlotAm.push_back(4);
			SlotSt.push_back(1);
			
			//Slot birch
			SlotId.push_back(155);
			SlotAm.push_back(4);
			SlotSt.push_back(1);
		
			//Slot Supruce
			SlotId.push_back(156);
			SlotAm.push_back(4);
			SlotSt.push_back(1);
			
			UpdateSlot(Index);
		}
		break;
		case 276: //Sticks
		{
			//Slot Stick - Inicio
			SlotId.push_back(276);
			SlotAm.push_back(4);
			SlotSt.push_back(1);
			
			if(!craft2x2) //Crafteo 2x2
			{
				//Slot Leader
				SlotId.push_back(307);
				SlotAm.push_back(3);
				SlotSt.push_back(1);
			}
			
			UpdateSlot(Index);
		}
		break;
		case 216: //Quartz
		{
			//Slot Quartz - Inicio
			SlotId.push_back(216);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Pillar Quartz
			SlotId.push_back(217);
			SlotAm.push_back(2);
			SlotSt.push_back(1);
			
			//Slot Stone Bricks
			SlotId.push_back(102);
			SlotAm.push_back(4);
			SlotSt.push_back(1);
			
			//Slot Stone Chiseled Stone
			SlotId.push_back(104);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			UpdateSlot(Index);
		}
		break;
		case 26: //SandStone
		{
			//Slot SandStone - Inicio
			SlotId.push_back(26);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Snow
			SlotId.push_back(47);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Clay
			SlotId.push_back(99);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Bricks
			SlotId.push_back(27);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			if(!craft2x2) //Crafteo 2x2
			{
				//Slot Snow Top
				SlotId.push_back(93);
				SlotAm.push_back(6);
				SlotSt.push_back(1);
			}
			
			UpdateSlot(Index);
		}
		break;
		case 105: //Crafting Table
		{
			//Slot Crafting Table - Inicio
			SlotId.push_back(105);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			if(!craft2x2) //Crafteo 2x2
			{
				//Slot Furnace
				SlotId.push_back(106);
				SlotAm.push_back(1);
				SlotSt.push_back(1);
			}
			
			UpdateSlot(Index);
		}
		break;
		case 96: //Chest
		{
			//Slot Chest - Inicio
			SlotId.push_back(96);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			UpdateSlot(Index);
		}
		break;
		case 361: //Bed
		{
			//Slot Bed - Inicio
			SlotId.push_back(361);
			SlotAm.push_back(1);
			SlotSt.push_back(0);
			
			UpdateSlot(Index);
		}
		break;
		case 159: //Fence
		{
			//Slot Fence Oak - Inicio
			//Fence Birch
			SlotId.push_back(159);
			SlotAm.push_back(3);
			SlotSt.push_back(1);
			
			SlotId.push_back(59);
			SlotAm.push_back(3);
			SlotSt.push_back(1);	
			//Fence Birch
			SlotId.push_back(160);
			SlotAm.push_back(3);
			SlotSt.push_back(1);
			//Iron Bar
			SlotId.push_back(350);
			SlotAm.push_back(16);
			SlotSt.push_back(1);
			
			UpdateSlot(Index);
		}
		break;
		case 306: //Door
		{
			//Slot Door - Inicio
			SlotId.push_back(306);
			SlotAm.push_back(3);
			SlotSt.push_back(1);
			
			//TrapDoor
			SlotId.push_back(151);
			SlotAm.push_back(2);
			SlotSt.push_back(1);
			
			UpdateSlot(Index);
		}
		break;
		case 67: //Stair
		{
			//Slot Door - Inicio
			SlotId.push_back(67);
			SlotAm.push_back(4);
			SlotSt.push_back(1);
			
			//Oak Stair
			SlotId.push_back(125);
			SlotAm.push_back(4);
			SlotSt.push_back(1);
			
			//Birch Stair
			SlotId.push_back(161);
			SlotAm.push_back(4);
			SlotSt.push_back(1);
			
			//Surpruce Stair
			SlotId.push_back(165);
			SlotAm.push_back(4);
			SlotSt.push_back(1);
			
			//Cobblestone Stair
			SlotId.push_back(60);
			SlotAm.push_back(4);
			SlotSt.push_back(1);
			
			UpdateSlot(Index);
		}
		break;
		case 83: //Slab
		{
			//Slot Cobblestone Slab - Inicio
			SlotId.push_back(83);
			SlotAm.push_back(6);
			SlotSt.push_back(1);
			
			//Oak Slab
			SlotId.push_back(82);
			SlotAm.push_back(6);
			SlotSt.push_back(1);
			
			//Birch Slab
			SlotId.push_back(157);
			SlotAm.push_back(6);
			SlotSt.push_back(1);
			
			//Surpruce Slab
			SlotId.push_back(158);
			SlotAm.push_back(6);
			SlotSt.push_back(1);
			
			//Brick Slab
			SlotId.push_back(84);
			SlotAm.push_back(6);
			SlotSt.push_back(1);
			
			//Brick Slab
			SlotId.push_back(86);
			SlotAm.push_back(6);
			SlotSt.push_back(1);
			
			//Stone Slab
			SlotId.push_back(108);
			SlotAm.push_back(6);
			SlotSt.push_back(1);
			
			//Stone Slab
			SlotId.push_back(85);
			SlotAm.push_back(6);
			SlotSt.push_back(1);
			
			UpdateSlot(Index);
		}
		break;
	}
}
//Update Slot - Actualizar los Slots!
void Recipes::UpdateSlot(int Slot)
{
	
	ReSlotId.clear();
	ReSlotAm.clear();
	ReSlotPreview.clear();
	
	switch(Slot)
	{
		case 34: //Planks Oak
		{
			//Requisitos
			ReSlotId.push_back(8);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(8);
		}
		break;
		case 155: //Planks Birch
		{
			//Requisitos
			ReSlotId.push_back(31);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(31);
		}
		break;
		case 156: //Planks Supruce
		{
			//Requisitos
			ReSlotId.push_back(30);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(30);
		}
		break;
		case 276:
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 307:
		{
			//Requisitos
			ReSlotId.push_back(276);
			ReSlotAm.push_back(7);
			//Preview
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
		}
		break;
		case 216: //Quartz Block
		{
			//Requisitos
			ReSlotId.push_back(416);
			ReSlotAm.push_back(4);
			//Preview
			ReSlotPreview.push_back(416);
			
			ReSlotPreview.push_back(416);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(416);
			
			ReSlotPreview.push_back(416);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 217: //Quartz Pillar
		{
			//Requisitos
			ReSlotId.push_back(216);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(216);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(216);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 102: //Brick Stone
		{
			//Requisitos
			ReSlotId.push_back(3);
			ReSlotAm.push_back(4);
			//Preview
			ReSlotPreview.push_back(3);
			
			ReSlotPreview.push_back(3);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(3);
			
			ReSlotPreview.push_back(3);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 26:
		{
			//Requisitos
			ReSlotId.push_back(7);
			ReSlotAm.push_back(4);
			//Preview
			ReSlotPreview.push_back(7);
			
			ReSlotPreview.push_back(7);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(7);
			
			ReSlotPreview.push_back(7);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 104: //Chiseled Stone Blocks
		{
			//Requisitos
			ReSlotId.push_back(108);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(108);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(108);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 47: //Snow
		{
			//Requisitos
			ReSlotId.push_back(299);
			ReSlotAm.push_back(4);
			//Preview
			ReSlotPreview.push_back(299);
			
			ReSlotPreview.push_back(299);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(299);
			
			ReSlotPreview.push_back(299);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 93: //Top Snow
		{
			//Requisitos
			ReSlotId.push_back(47);
			ReSlotAm.push_back(3);
			//Preview
			ReSlotPreview.push_back(47);
			
			ReSlotPreview.push_back(47);
			
			ReSlotPreview.push_back(47);
		}	
		break;
		case 99: //Clay
		{
			//Requisitos
			ReSlotId.push_back(283);
			ReSlotAm.push_back(4);
			//Preview
			ReSlotPreview.push_back(283);
			
			ReSlotPreview.push_back(283);
			
			ReSlotPreview.push_back(0);
			//Preview
			ReSlotPreview.push_back(283);
			
			ReSlotPreview.push_back(283);
		}
		break;
		case 27: //Bricks
		{
			//Requisitos
			ReSlotId.push_back(289);
			ReSlotAm.push_back(4);
			//Preview
			ReSlotPreview.push_back(289);
			
			ReSlotPreview.push_back(289);
			
			ReSlotPreview.push_back(0);
			//Preview
			ReSlotPreview.push_back(289);
			
			ReSlotPreview.push_back(289);
		}
		break;
		case 105: //Crafting Table
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(4);
			//Preview
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 106: //Furnace
		{
			//Requisitos
			ReSlotId.push_back(36);
			ReSlotAm.push_back(8);
			//Preview
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
		}
		break;
		case 96: //Chest
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(8);
			//Preview
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
		}
		break;
		case 361: //Bed
		{
			//Requisitos
			ReSlotId.push_back(1001); //Para ocupar cualquier lana en la receta
			ReSlotAm.push_back(3); //Cantidad Requirida para la receta
			
			ReSlotId.push_back(3401); //Para utilizar cualquier madera en la receta
			ReSlotAm.push_back(3);
			//Preview Con esto hago la preview del crafteo
			ReSlotPreview.push_back(1001);
			
			ReSlotPreview.push_back(1001);
			
			ReSlotPreview.push_back(1001);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
		}
		break;
		case 59: //Oak Fence
		{
			//Requisitos
			ReSlotId.push_back(34);
			ReSlotAm.push_back(4);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(34);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(34);
			
			ReSlotPreview.push_back(34);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(34);
		}
		break;
		case 159: //Birch Fence
		{
			//Requisitos
			ReSlotId.push_back(155);
			ReSlotAm.push_back(4);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(155);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(155);
			
			ReSlotPreview.push_back(155);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(155);
		}
		break;
		case 160: //Supruce Fence
		{
			//Requisitos
			ReSlotId.push_back(156);
			ReSlotAm.push_back(4);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(156);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(156);
			
			ReSlotPreview.push_back(156);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(156);
		}
		break;
		case 350: //Iron Bars
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(6);
			//Preview
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
		}
		break;
		case 306: //Door
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(6);

			//Preview
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
		}
		break;
		case 151: //TrapDoor
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(6);
			//Preview
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
		}
		break;
		case 67:
		{
			//Requisitos
			ReSlotId.push_back(27);
			ReSlotAm.push_back(6);

			//Preview
			ReSlotPreview.push_back(27);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(27);
			
			ReSlotPreview.push_back(27);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(27);
			
			ReSlotPreview.push_back(27);
			
			ReSlotPreview.push_back(27);
		}
		break;
		case 125: //Stair Oak
		{
			//Requisitos
			ReSlotId.push_back(34);
			ReSlotAm.push_back(6);

			//Preview
			ReSlotPreview.push_back(34);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(34);
			
			ReSlotPreview.push_back(34);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(34);
			
			ReSlotPreview.push_back(34);
			
			ReSlotPreview.push_back(34);
			
		}
		break;
		case 161: //Stair Birch
		{
			//Requisitos
			ReSlotId.push_back(155);
			ReSlotAm.push_back(6);

			//Preview
			ReSlotPreview.push_back(155);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(155);
			
			ReSlotPreview.push_back(155);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(155);
			
			ReSlotPreview.push_back(155);
			
			ReSlotPreview.push_back(155);
			
		}
		break;
		case 165: //Stair Surpruce
		{
			//Requisitos
			ReSlotId.push_back(156);
			ReSlotAm.push_back(6);

			//Preview
			ReSlotPreview.push_back(156);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(156);
			
			ReSlotPreview.push_back(156);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(156);
			
			ReSlotPreview.push_back(156);
			
			ReSlotPreview.push_back(156);
			
		}
		break;
		case 60: //Stair Cobblestone
		{
			//Requisitos
			ReSlotId.push_back(36);
			ReSlotAm.push_back(6);

			//Preview
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
			
		}
		break;
		case 83: //Slab Cobblestone
		{
			//Requisitos
			ReSlotId.push_back(36);
			ReSlotAm.push_back(3);

			//Preview
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
		}
		break;
		case 82: //Slab Oak
		{
			//Requisitos
			ReSlotId.push_back(34);
			ReSlotAm.push_back(3);

			//Preview
			ReSlotPreview.push_back(34);
			
			ReSlotPreview.push_back(34);
			
			ReSlotPreview.push_back(34);
		}
		break;
		case 157: //Slab Birch
		{
			//Requisitos
			ReSlotId.push_back(155);
			ReSlotAm.push_back(3);

			//Preview
			ReSlotPreview.push_back(155);
			
			ReSlotPreview.push_back(155);
			
			ReSlotPreview.push_back(155);
		}
		break;
		case 158: //Slab Surpruce
		{
			//Requisitos
			ReSlotId.push_back(156);
			ReSlotAm.push_back(3);

			//Preview
			ReSlotPreview.push_back(156);
			
			ReSlotPreview.push_back(156);
			
			ReSlotPreview.push_back(156);
		}
		break;
		case 84: //Slab Brick
		{
			//Requisitos
			ReSlotId.push_back(27);
			ReSlotAm.push_back(3);

			//Preview
			ReSlotPreview.push_back(27);
			
			ReSlotPreview.push_back(27);
			
			ReSlotPreview.push_back(27);
		}
		break;
		case 86: //Slab SandStone
		{
			//Requisitos
			ReSlotId.push_back(26);
			ReSlotAm.push_back(3);

			//Preview
			ReSlotPreview.push_back(26);
			
			ReSlotPreview.push_back(26);
			
			ReSlotPreview.push_back(26);
		}
		break;
		case 85: //Slab Stone
		{
			//Requisitos
			ReSlotId.push_back(3);
			ReSlotAm.push_back(3);

			//Preview
			ReSlotPreview.push_back(3);
			
			ReSlotPreview.push_back(3);
			
			ReSlotPreview.push_back(3);
		}
		break;
		case 108: //Slab Stone Brick
		{
			//Requisitos
			ReSlotId.push_back(102);
			ReSlotAm.push_back(3);

			//Preview
			ReSlotPreview.push_back(102);
			
			ReSlotPreview.push_back(102);
			
			ReSlotPreview.push_back(102);
		}
		break;
	}
}
//Update Index Pag2
void Recipes::UpdateIndex2(int Index)
{
	SlotId.clear();
	SlotAm.clear();
	SlotSt.clear();
			
	switch(Index)
	{
		case 250: //Pickaxe
		{
			//Slot Pickaxe Wood
			SlotId.push_back(250);
			SlotAm.push_back(60);
			SlotSt.push_back(0);
			
			//Slot Pickaxe Stone
			SlotId.push_back(251);
			SlotAm.push_back(132);
			SlotSt.push_back(0);
			
			//Slot Pickaxe Iron
			SlotId.push_back(252);
			SlotAm.push_back(251);
			SlotSt.push_back(0);
			
			//Slot Pickaxe Diamond
			SlotId.push_back(253);
			SlotAm.push_back(1562);
			SlotSt.push_back(0);
			
			//Slot Pickaxe Gold
			SlotId.push_back(254);
			SlotAm.push_back(33);
			SlotSt.push_back(0);
			
			UpdateSlot2(Index);
		}
		break;
		case 260: //Shovel
		{
			//Slot Shovel Wood
			SlotId.push_back(260);
			SlotAm.push_back(60);
			SlotSt.push_back(0);
			
			//Slot Shovel Stone
			SlotId.push_back(261);
			SlotAm.push_back(132);
			SlotSt.push_back(0);
			
			//Slot Shovel Iron
			SlotId.push_back(262);
			SlotAm.push_back(251);
			SlotSt.push_back(0);
			
			//Slot Shovel Diamond
			SlotId.push_back(263);
			SlotAm.push_back(1562);
			SlotSt.push_back(0);
			
			//Slot Shovel Gold
			SlotId.push_back(264);
			SlotAm.push_back(33);
			SlotSt.push_back(0);
			
			UpdateSlot2(Index);
		}
		break;
		case 265: //Axe
		{
			//Slot Axe Wood
			SlotId.push_back(265);
			SlotAm.push_back(60);
			SlotSt.push_back(0);
			
			//Slot Axe Stone
			SlotId.push_back(266);
			SlotAm.push_back(132);
			SlotSt.push_back(0);
			
			//Slot Axe Iron
			SlotId.push_back(267);
			SlotAm.push_back(251);
			SlotSt.push_back(0);
			
			//Slot Axe Diamond
			SlotId.push_back(268);
			SlotAm.push_back(1562);
			SlotSt.push_back(0);
			
			//Slot Axe Gold
			SlotId.push_back(269);
			SlotAm.push_back(33);
			SlotSt.push_back(0);
			
			UpdateSlot2(Index);
		}
		break;
		case 270: //Hoe
		{
			//Slot Hoe Wood
			SlotId.push_back(270);
			SlotAm.push_back(60);
			SlotSt.push_back(0);
			
			//Slot Hoe Stone
			SlotId.push_back(271);
			SlotAm.push_back(132);
			SlotSt.push_back(0);
			
			//Slot Hoe Iron
			SlotId.push_back(272);
			SlotAm.push_back(251);
			SlotSt.push_back(0);
			
			//Slot Hoe Diamond
			SlotId.push_back(273);
			SlotAm.push_back(1562);
			SlotSt.push_back(0);
			
			//Slot Hoe Gold
			SlotId.push_back(274);
			SlotAm.push_back(33);
			SlotSt.push_back(0);
			
			UpdateSlot2(Index);
		}
		break;
		case 275: //Scissors
		{
			//Slot Scissors
			SlotId.push_back(275);
			SlotAm.push_back(239);
			SlotSt.push_back(0);
			
			//Slot Flint
			SlotId.push_back(378);
			SlotAm.push_back(65);
			SlotSt.push_back(0);
			
			if(!craft2x2)
			{
				//Slot TNT
				SlotId.push_back(110);
				SlotAm.push_back(1);
				SlotSt.push_back(1);
			}
			
			UpdateSlot2(Index);
		}
		break;
		case 408: //Bow
		{
			//Slot Bow
			SlotId.push_back(408);
			SlotAm.push_back(50);
			SlotSt.push_back(0);
			
			//Slot Arrow
			SlotId.push_back(409);
			SlotAm.push_back(4);
			SlotSt.push_back(1);
			
			UpdateSlot2(Index);
		}
		break;
		case 255: //Sword
		{
			//Slot Sword Wood
			SlotId.push_back(255);
			SlotAm.push_back(60);
			SlotSt.push_back(0);
			
			//Slot Sword Stone
			SlotId.push_back(256);
			SlotAm.push_back(132);
			SlotSt.push_back(0);
			
			//Slot Sword Iron
			SlotId.push_back(257);
			SlotAm.push_back(251);
			SlotSt.push_back(0);
			
			//Slot Sword Diamond
			SlotId.push_back(258);
			SlotAm.push_back(1562);
			SlotSt.push_back(0);
			
			//Slot Sword Gold
			SlotId.push_back(259);
			SlotAm.push_back(33);
			SlotSt.push_back(0);
			
			UpdateSlot2(Index);
		}
		break;
		case 415: //Shield
		{
			//Slot Shield Wood
			SlotId.push_back(415);
			SlotAm.push_back(150);
			SlotSt.push_back(0);
			
			UpdateSlot2(Index);
		}
		break;
		case 290: //Bucket
		{
			//Slot Bucket
			SlotId.push_back(290);
			SlotAm.push_back(1);
			SlotSt.push_back(0);
			
			//Slot Bowl
			SlotId.push_back(302);
			SlotAm.push_back(4);
			SlotSt.push_back(1);
			
			UpdateSlot2(Index);
		}
		break;
		case 308: //Torch
		{
			//Slot Bucket
			SlotId.push_back(308);
			SlotAm.push_back(4);
			SlotSt.push_back(1);
			
			//Slot GlowStone
			SlotId.push_back(225);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Jack
			SlotId.push_back(145);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			UpdateSlot2(Index);
		}
		break;
		case 354: //Clock
		{
			//Slot Bucket
			SlotId.push_back(354);
			SlotAm.push_back(1);
			SlotSt.push_back(0);
			
			//Slot Compass
			SlotId.push_back(355);
			SlotAm.push_back(1);
			SlotSt.push_back(0);
			
			UpdateSlot2(Index);
		}
		break;
	}
}
//Update Slot2 - Actualizar los Slots!
void Recipes::UpdateSlot2(int Slot)
{
	//SlotId.clear();
	//SlotAm.clear();
	//SlotSt.clear();
	
	ReSlotId.clear();
	ReSlotAm.clear();
	ReSlotPreview.clear();
	
	switch(Slot)
	{
		case 250: //Pickaxe Wood
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(3);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 251: //Pickaxe Stone
		{
			//Requisitos
			ReSlotId.push_back(36);
			ReSlotAm.push_back(3);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 252: //Pickaxe Iron
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(3);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 253: //Pickaxe Diamond
		{
			//Requisitos
			ReSlotId.push_back(279);
			ReSlotAm.push_back(3);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 254: //Pickaxe Gold
		{
			//Requisitos
			ReSlotId.push_back(280);
			ReSlotAm.push_back(3);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 260: //Shovel Wood
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 261: //Shovel Stone
		{
			//Requisitos
			ReSlotId.push_back(36);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
	
		}
		break;
		case 262: //Shovel Iron
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
		}
		break;
		case 263: //Shovel Diamond
		{
			//Requisitos
			ReSlotId.push_back(279);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
		}
		break;
		case 264: //Shovel Gold
		{
			
			//Requisitos
			ReSlotId.push_back(280);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 265: //Axe Wood
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(3);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}	
		break;
		case 266: //Axe Stone
		{
			//Requisitos
			ReSlotId.push_back(36);
			ReSlotAm.push_back(3);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 267: //Axe Iron
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(3);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 268: //Axe Diamond
		{
			//Requisitos
			ReSlotId.push_back(279);
			ReSlotAm.push_back(3);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
		}
		break;
		case 269: //Axe Gold
		{
			
			//Requisitos
			ReSlotId.push_back(280);
			ReSlotAm.push_back(3);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 270: //Hoe Wood
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(2);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 271: //Hoe Stone
		{
			//Requisitos
			ReSlotId.push_back(36);
			ReSlotAm.push_back(2);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 272: //Hoe Iron
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(2);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 273: //Hoe Diamond
		{
			//Requisitos
			ReSlotId.push_back(279);
			ReSlotAm.push_back(2);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 274: //Hoe Gold
		{
			//Requisitos
			ReSlotId.push_back(280);
			ReSlotAm.push_back(2);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 275: //Scissors
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(2);

			//Preview
			ReSlotPreview.push_back(0);

			ReSlotPreview.push_back(278);

			ReSlotPreview.push_back(0);

			ReSlotPreview.push_back(278);
		}
		break;
		case 110: //TNT
		{
			//Requisitos
			ReSlotId.push_back(7001);
			ReSlotAm.push_back(4);
			
			ReSlotId.push_back(352);
			ReSlotAm.push_back(5);

			//Preview
			ReSlotPreview.push_back(352);

			ReSlotPreview.push_back(7001);

			ReSlotPreview.push_back(352);

			ReSlotPreview.push_back(7001);

			ReSlotPreview.push_back(352);

			ReSlotPreview.push_back(7001);
			
			ReSlotPreview.push_back(352);

			ReSlotPreview.push_back(7001);

			ReSlotPreview.push_back(352);
		}
		break;
		case 378: //Flint
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(351);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(351);

			ReSlotPreview.push_back(278);
		}
		break;
		case 408: //Bow
		{
			//Requisitos
			ReSlotId.push_back(407);
			ReSlotAm.push_back(3);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(3);
			
			//Preview
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(407);

			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(407);

			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(407);
		}
		break;
		case 409: //Arrow
		{
			//Requisitos
			ReSlotId.push_back(351);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(398);
			ReSlotAm.push_back(1);
			
			//Preview
			ReSlotPreview.push_back(351);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);

			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);

			ReSlotPreview.push_back(398);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 255: //Sword Wood
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(2);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 256: //Sword Stone
		{
			//Requisitos
			ReSlotId.push_back(36);
			ReSlotAm.push_back(2);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(36);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 257: //Sword Iron
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(2);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 258: //Sword Diamond
		{
			//Requisitos
			ReSlotId.push_back(279);
			ReSlotAm.push_back(2);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 259: //Sword Gold
		{
			//Requisitos
			ReSlotId.push_back(280);
			ReSlotAm.push_back(2);
			
			ReSlotId.push_back(276);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 415: //Shield
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(6);
			
			ReSlotId.push_back(278);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
		}	
		break;
		case 290: //Bucket
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(3);
			//Preview
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
		}
		break;
		case 302: //Bowl
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(3);
			//Preview
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(3401);
		}
		break;
		case 308: //Torch
		{
			//Requisitos
			ReSlotId.push_back(276);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(277);
			ReSlotAm.push_back(1);
			
			//Preview
			ReSlotPreview.push_back(277);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(276);
		}
		break;
		case 225: //GlowStone
		{
			//Requisitos
			ReSlotId.push_back(418);
			ReSlotAm.push_back(4);
			
			//Preview
			ReSlotPreview.push_back(418);
			
			ReSlotPreview.push_back(418);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(418);
			
			ReSlotPreview.push_back(418);
		}
		break;
		case 145: //Jack
		{
			//Requisitos
			ReSlotId.push_back(75);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(308);
			ReSlotAm.push_back(1);
			
			//Preview
			ReSlotPreview.push_back(75);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(308);
		}
		break;
		case 354: //Clock
		{
			//Requisitos
			ReSlotId.push_back(280);
			ReSlotAm.push_back(4);
			
			ReSlotId.push_back(353);
			ReSlotAm.push_back(1);
			
			//Preview
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(353);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
		}
		break;
		case 355: //Compass
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(4);
			
			ReSlotId.push_back(353);
			ReSlotAm.push_back(1);
			
			//Preview
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(353);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
		}
		break;
	}

}
//Update Index Pag3
void Recipes::UpdateIndex3(int Index)
{
	SlotId.clear();
	SlotAm.clear();
	SlotSt.clear();
			
	switch(Index)
	{
		case 285: //Golden Apple
		{
			//Slot Golden Apple
			SlotId.push_back(285);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			UpdateSlot3(Index);
		}
		break;
		case 303: //Mushroom Stew
		{
			//Slot Golden Apple
			SlotId.push_back(303);
			SlotAm.push_back(1);
			SlotSt.push_back(0);
			
			UpdateSlot3(Index);
		}
		break;
		case 314: //Cookie
		{
			//Cocoa
			SlotId.push_back(314);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			if(!craft2x2)
			{
				//Slot Cookie
				SlotId.push_back(315);
				SlotAm.push_back(8);
				SlotSt.push_back(1);
			}
			
			UpdateSlot3(Index);
		}
		break;
		case 81: //Melon
		{
			//Slot Melon
			SlotId.push_back(81);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			UpdateSlot3(Index);
		}
		break;
		case 312: //Melon Seeds
		{
			//Slot Melon Seeds
			SlotId.push_back(312);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Pumpkin Seeds
			SlotId.push_back(377);
			SlotAm.push_back(4);
			SlotSt.push_back(1);
			
			UpdateSlot3(Index);
		}
		break;
		case 313: //Sugar
		{
			//Slot Melon Seeds
			SlotId.push_back(313);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			UpdateSlot3(Index);
		}
		break;
		case 288: //Bread
		{
			//Slot Bread
			SlotId.push_back(288);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			UpdateSlot3(Index);
		}
		break;
	}
}
//Update Slot3 - Actualizar los Slots!
void Recipes::UpdateSlot3(int Slot)
{
	//SlotId.clear();
	//SlotAm.clear();
	//SlotSt.clear();
	
	ReSlotId.clear();
	ReSlotAm.clear();
	ReSlotPreview.clear();
	
	switch(Slot)
	{
		case 285: //Golden Apple
		{
			//Requisitos
			ReSlotId.push_back(280);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(284);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(284);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
		
		}
		break;
		case 303: //Mushroom Stew
		{
			//Requisitos
			ReSlotId.push_back(302);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(300);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(301);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(300);
			
			ReSlotPreview.push_back(301);
			
			ReSlotPreview.push_back(302);
		}
		break;
		case 315: //Cookie
		{
			//Requisitos
			ReSlotId.push_back(287);
			ReSlotAm.push_back(2);
			
			ReSlotId.push_back(314);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(287);
			
			ReSlotPreview.push_back(314);
			
			ReSlotPreview.push_back(287);
		}
		break;
		case 314: //Cocoa
		{
			//Requisitos
			ReSlotId.push_back(370);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(286);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(287);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(370);
			
			ReSlotPreview.push_back(286);
			
			ReSlotPreview.push_back(287);
		}
		break;
		case 81: //Melon
		{
			//Requisitos
			ReSlotId.push_back(311);
			ReSlotAm.push_back(9);
			//Preview
			ReSlotPreview.push_back(311);
			
			ReSlotPreview.push_back(311);
			
			ReSlotPreview.push_back(311);
			
			ReSlotPreview.push_back(311);
			
			ReSlotPreview.push_back(311);
			
			ReSlotPreview.push_back(311);
			
			ReSlotPreview.push_back(311);
			
			ReSlotPreview.push_back(311);
			
			ReSlotPreview.push_back(311);
		}
		break;
		case 312: //Melon Seeds
		{
			//Requisitos
			ReSlotId.push_back(311);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(311);
		}
		break;
		case 377: //Pumpkin Seeds
		{
			//Requisitos
			ReSlotId.push_back(75);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(75);
		}
		break;
		case 313: //Sugar
		{
			//Requisitos
			ReSlotId.push_back(293);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(293);
		}
		break;
		case 288: //Bread
		{
			//Requisitos
			ReSlotId.push_back(287);
			ReSlotAm.push_back(3);
			//Preview
			ReSlotPreview.push_back(287);
			
			ReSlotPreview.push_back(287);
			
			ReSlotPreview.push_back(287);
		}
		break;
	}
}
//Update Index Pag4
void Recipes::UpdateIndex4(int Index)
{
	SlotId.clear();
	SlotAm.clear();
	SlotSt.clear();
			
	switch(Index)
	{
		case 71: //NoteBox
		{
			//Slot NoteBox
			SlotId.push_back(71);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			UpdateSlot4(Index);
		}
		break;
	}
}
//Update Slot4 - Actualizar los Slots!
void Recipes::UpdateSlot4(int Slot)
{
	//SlotId.clear();
	//SlotAm.clear();
	//SlotSt.clear();
	
	ReSlotId.clear();
	ReSlotAm.clear();
	ReSlotPreview.clear();
	
	switch(Slot)
	{
		case 71: //NoteBox
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(353);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(353);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(3401);
		}
		break;
	}
}
//Update Index Pag5
void Recipes::UpdateIndex5(int Index)
{
	SlotId.clear();
	SlotAm.clear();
	SlotSt.clear();
			
	switch(Index)
	{
		case 328: //Helmet
		{
			//Slot Helmet Leader - Inicio
			SlotId.push_back(328);
			SlotAm.push_back(55);
			SlotSt.push_back(0);
			
			//Slot Helmet Iron
			SlotId.push_back(336);
			SlotAm.push_back(165);
			SlotSt.push_back(0);
			
			//Slot Helmet Diamond
			SlotId.push_back(340);
			SlotAm.push_back(363);
			SlotSt.push_back(0);
			
			//Slot Helmet Gold
			SlotId.push_back(344);
			SlotAm.push_back(77);
			SlotSt.push_back(0);
			
			UpdateSlot5(Index);
		}
		break;
		case 329: //Chestplace
		{
			//Slot Chestplace Leader - Inicio
			SlotId.push_back(329);
			SlotAm.push_back(80);
			SlotSt.push_back(0);
			
			//Slot Chestplace Iron
			SlotId.push_back(337);
			SlotAm.push_back(240);
			SlotSt.push_back(0);
			
			//Slot Chestplace Diamond
			SlotId.push_back(341);
			SlotAm.push_back(528);
			SlotSt.push_back(0);
			
			//Slot Chestplace Gold
			SlotId.push_back(345);
			SlotAm.push_back(112);
			SlotSt.push_back(0);
			
			UpdateSlot5(Index);
		}
		break;
		case 330: //Leggings
		{
			//Slot //Leggings Leader - Inicio
			SlotId.push_back(330);
			SlotAm.push_back(75);
			SlotSt.push_back(0);
			
			//Slot Leggings Iron
			SlotId.push_back(338);
			SlotAm.push_back(225);
			SlotSt.push_back(0);
			
			//Slot Leggings Diamond
			SlotId.push_back(342);
			SlotAm.push_back(495);
			SlotSt.push_back(0);
			
			//Slot Leggings Gold
			SlotId.push_back(346);
			SlotAm.push_back(105);
			SlotSt.push_back(0);
			
			UpdateSlot5(Index);
		}
		break;
		case 331: //Boots
		{
			//Slot Boots Leader - Inicio
			SlotId.push_back(331);
			SlotAm.push_back(65);
			SlotSt.push_back(0);
			
			//Slot Boots Iron
			SlotId.push_back(339);
			SlotAm.push_back(195);
			SlotSt.push_back(0);
			
			//Slot Boots Diamond
			SlotId.push_back(343);
			SlotAm.push_back(429);
			SlotSt.push_back(0);
			
			//Slot Boots Gold
			SlotId.push_back(347);
			SlotAm.push_back(91);
			SlotSt.push_back(0);
			
			UpdateSlot5(Index);
		}
		break;
	}
}
//Update Slot5 - Actualizar los Slots!
void Recipes::UpdateSlot5(int Slot)
{
	//SlotId.clear();
	//SlotAm.clear();
	//SlotSt.clear();
	
	ReSlotId.clear();
	ReSlotAm.clear();
	ReSlotPreview.clear();
	
	switch(Slot)
	{
		case 328: //Helmet Leader
		{
			//Requisitos
			ReSlotId.push_back(323);
			ReSlotAm.push_back(5);
			//Preview
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(323);
		}
		break;
		case 329: //Chestplace Leader
		{
			//Requisitos
			ReSlotId.push_back(323);
			ReSlotAm.push_back(8);
			//Preview
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(323);
		}
		break;
		case 330: //Leggings Leader
		{
			//Requisitos
			ReSlotId.push_back(323);
			ReSlotAm.push_back(7);
			//Preview
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(323);
		}
		break;
		case 331: //Boots Leader
		{
			//Requisitos
			ReSlotId.push_back(323);
			ReSlotAm.push_back(4);
			//Preview
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(323);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(323);
		}
		break;
		case 336: //Helmet Iron
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(5);
			//Preview
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
		}
		break;
		case 337: //Chestplace Iron
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(8);
			//Preview
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
		}
		break;
		case 338: //Leggings Iron
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(7);
			//Preview
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
		}
		break;
		case 339: //Boots Iron
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(4);
			//Preview
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(278);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(278);
		}
		break;
		case 340: //Helmet Diamond
		{
			//Requisitos
			ReSlotId.push_back(279);
			ReSlotAm.push_back(5);
			//Preview
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(279);
		}
		break;
		case 341: //Chestplace Diamond
		{
			//Requisitos
			ReSlotId.push_back(279);
			ReSlotAm.push_back(8);
			//Preview
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
		}
		break;
		case 342: //Leggings Diamond
		{
			//Requisitos
			ReSlotId.push_back(279);
			ReSlotAm.push_back(7);
			//Preview
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(279);
		}
		break;
		case 343: //Boots Diamond
		{
			//Requisitos
			ReSlotId.push_back(279);
			ReSlotAm.push_back(4);
			//Preview
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(279);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(279);
		}
		break;
		case 344: //Helmet Gold
		{
			//Requisitos
			ReSlotId.push_back(280);
			ReSlotAm.push_back(5);
			//Preview
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(280);
		}
		break;
		case 345: //Chestplace Gold
		{
			//Requisitos
			ReSlotId.push_back(280);
			ReSlotAm.push_back(8);
			//Preview
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
		}
		break;
		case 346: //Leggings Gold
		{
			//Requisitos
			ReSlotId.push_back(280);
			ReSlotAm.push_back(7);
			//Preview
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(280);
		}
		break;
		case 347: //Boots Gold
		{
			//Requisitos
			ReSlotId.push_back(280);
			ReSlotAm.push_back(4);
			//Preview
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(280);
			
			ReSlotPreview.push_back(0);
			
			ReSlotPreview.push_back(280);
		}
		break;
	}
}

//Update Index Pag6
void Recipes::UpdateIndex6(int Index)
{
	SlotId.clear();
	SlotAm.clear();
	SlotSt.clear();

	switch(Index)
	{
		case 349: //GlassPanel
		{
			//Slot GlassPanel
			SlotId.push_back(349);
			SlotAm.push_back(16);
			SlotSt.push_back(1);
			
			UpdateSlot6(Index);
		}
		break;
		case 64: //DiamondBlock
		{
			//Slot DiamondBlock
			SlotId.push_back(64);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Iron Block
			SlotId.push_back(66);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Gold Block
			SlotId.push_back(65);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Lapis Block
			SlotId.push_back(101);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot RedStone Block
			SlotId.push_back(215);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Coal Block
			SlotId.push_back(214);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot HayBale Block
			SlotId.push_back(213);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			UpdateSlot6(Index);
		}
		break;
		case 228: //Terracotta
		{
			//Slot Terracota
			SlotId.push_back(228);
			SlotAm.push_back(1);
			SlotSt.push_back(1);

			for(int t = 0; t < 16; t ++)
			{
				//Slot Terracota
				if(t != 2)
				{
					SlotId.push_back(229 + t);
					SlotAm.push_back(8);
					SlotSt.push_back(1);
				}
			}
			
			UpdateSlot6(Index);
		}
		break;
		case 10: //Wool
		{
			//Slot Black Wool
			SlotId.push_back(10);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			
			for(int t = 0; t < 14; t ++)
			{
				//Slot Wool
				SlotId.push_back(11 + t);
				SlotAm.push_back(1);
				SlotSt.push_back(1);
			}
			
			UpdateSlot6(Index);
		}
		break;
		case 371: //Yellow
		{
			//Slot Yellow Dye
			SlotId.push_back(371);
			SlotAm.push_back(1);
			SlotSt.push_back(1);

			//Slot Red Dye
			SlotId.push_back(369);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Pink Dye
			SlotId.push_back(368);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Orange Dye
			SlotId.push_back(370);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Purple
			SlotId.push_back(375);
			SlotAm.push_back(2);
			SlotSt.push_back(1);
			
			//Slot Lime
			SlotId.push_back(372);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Black
			SlotId.push_back(367);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Gray
			SlotId.push_back(366);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Light Gray
			SlotId.push_back(365);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Light Blue
			SlotId.push_back(374);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Green
			SlotId.push_back(373);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Magneta
			SlotId.push_back(376);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			UpdateSlot6(Index);
		}
		break;
		case 198: //Wool Carpet
		{
			//Slot Black Wool
			SlotId.push_back(198);
			SlotAm.push_back(3);
			SlotSt.push_back(1);
			
			for(int t = 0; t < 14; t ++)
			{
				//Slot Wool
				SlotId.push_back(199 + t);
				SlotAm.push_back(1);
				SlotSt.push_back(1);
			}
			
			UpdateSlot6(Index);
		}
		break;
		case 72: //JukeBox
		{
			//Slot JukeBox
			SlotId.push_back(72);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			UpdateSlot6(Index);
		}
		break;
		case 358: //Frame
		{
			//Slot Frame
			SlotId.push_back(358);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			UpdateSlot6(Index);
		}
		break;
		case 297: //Paper
		{
			//Slot Paper
			SlotId.push_back(297);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			//Slot Book
			SlotId.push_back(298);
			SlotAm.push_back(1);
			SlotSt.push_back(1);
			
			if(!craft2x2)
			{
				//Slot Bookshelf
				SlotId.push_back(35);
				SlotAm.push_back(1);
				SlotSt.push_back(1);
			}
			
			UpdateSlot6(Index);
		}
		break;
		case 280: //Gold
		{
			//Slot Gold
			SlotId.push_back(280);
			SlotAm.push_back(9);
			SlotSt.push_back(1);
			
			//Slot Iron
			SlotId.push_back(278);
			SlotAm.push_back(9);
			SlotSt.push_back(1);
			
			//Slot Diamond
			SlotId.push_back(279);
			SlotAm.push_back(9);
			SlotSt.push_back(1);
			
			//Slot Lapis
			SlotId.push_back(318);
			SlotAm.push_back(9);
			SlotSt.push_back(1);
			
			//Slot RedStone
			SlotId.push_back(353);
			SlotAm.push_back(9);
			SlotSt.push_back(1);
			
			//Slot Coal
			SlotId.push_back(277);
			SlotAm.push_back(9);
			SlotSt.push_back(1);
			
			//Slot Wheat
			SlotId.push_back(287);
			SlotAm.push_back(9);
			SlotSt.push_back(1);
			
			//Slot BoneMeal
			SlotId.push_back(322);
			SlotAm.push_back(3);
			SlotSt.push_back(1);
			
			UpdateSlot6(Index);
		}
		break;
	}
}
//Update Slot6 - Actualizar los Slots!
void Recipes::UpdateSlot6(int Slot)
{
	//SlotId.clear();
	//SlotAm.clear();
	//SlotSt.clear();
	
	ReSlotId.clear();
	ReSlotAm.clear();
	ReSlotPreview.clear();
	
	switch(Slot)
	{
		case 349: //GlassPanel
		{
			//Requisitos
			ReSlotId.push_back(40);
			ReSlotAm.push_back(6);
			//Preview
			ReSlotPreview.push_back(40);
			
			ReSlotPreview.push_back(40);
			
			ReSlotPreview.push_back(40);
			
			ReSlotPreview.push_back(40);
			
			ReSlotPreview.push_back(40);
			
			ReSlotPreview.push_back(40);
		}
		break;
		case 64: //DiamondBlock
		{
			//Requisitos
			ReSlotId.push_back(279);
			ReSlotAm.push_back(9);
			//Preview

			for(int b = 0; b < 9; b ++)
			{
				ReSlotPreview.push_back(279);
			}
		}
		break;
		case 66: //IronBlock
		{
			//Requisitos
			ReSlotId.push_back(278);
			ReSlotAm.push_back(9);
			//Preview

			for(int b = 0; b < 9; b ++)
			{
				ReSlotPreview.push_back(278);
			}
		}
		break;
		case 65: //GoldBlock
		{
			//Requisitos
			ReSlotId.push_back(280);
			ReSlotAm.push_back(9);
			//Preview

			for(int b = 0; b < 9; b ++)
			{
				ReSlotPreview.push_back(280);
			}
		}
		break;
		case 101: //LapisBlock
		{
			//Requisitos
			ReSlotId.push_back(318);
			ReSlotAm.push_back(9);
			//Preview

			for(int b = 0; b < 9; b ++)
			{
				ReSlotPreview.push_back(318);
			}
		}
		break;
		case 215: //RedstoneBlock
		{
			//Requisitos
			ReSlotId.push_back(353);
			ReSlotAm.push_back(9);
			//Preview

			for(int b = 0; b < 9; b ++)
			{
				ReSlotPreview.push_back(353);
			}
		}
		break;
		case 214: //CoalBlock
		{
			//Requisitos
			ReSlotId.push_back(277);
			ReSlotAm.push_back(9);
			//Preview

			for(int b = 0; b < 9; b ++)
			{
				ReSlotPreview.push_back(277);
			}
		}
		break;
		case 213: //HayBaleBlock
		{
			//Requisitos
			ReSlotId.push_back(287);
			ReSlotAm.push_back(9);
			//Preview

			for(int b = 0; b < 9; b ++)
			{
				ReSlotPreview.push_back(287);
			}
		}
		break;
		case 228: //White Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(322);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(322);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 24: //White Wool
		{
			//Requisitos
			ReSlotId.push_back(407);
			ReSlotAm.push_back(4);

			//Preview
			ReSlotPreview.push_back(407);
			ReSlotPreview.push_back(407);
			ReSlotPreview.push_back(0);
			ReSlotPreview.push_back(407);
			ReSlotPreview.push_back(407);
		}
		break;
		case 229: //Orange Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(370);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(370);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 22: //Orange Wool
		{
			//Requisitos
			ReSlotId.push_back(1001);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(370);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(1001);
			ReSlotPreview.push_back(370);
		}
		break;
		case 230: //Yellow Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(371);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(371);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 17: //Yellow Wool
		{
			//Requisitos
			ReSlotId.push_back(1001);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(371);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(1001);
			ReSlotPreview.push_back(371);
		}
		break;
		case 232: //LightGray Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(365);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(365);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 23: //LightGray Wool
		{
			//Requisitos
			ReSlotId.push_back(1001);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(365);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(1001);
			ReSlotPreview.push_back(365);
		}
		break;
		case 233: //Red Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(369);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(369);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 12: //Red Wool
		{
			//Requisitos
			ReSlotId.push_back(1001);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(369);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(1001);
			ReSlotPreview.push_back(369);
		}
		break;
		case 234: //Brown Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(314);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(314);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 16: //Brown Wool
		{
			//Requisitos
			ReSlotId.push_back(1001);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(314);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(1001);
			ReSlotPreview.push_back(314);
		}
		break;
		case 235: //Blue Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(318);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(318);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 18: //Blue Wool
		{
			//Requisitos
			ReSlotId.push_back(1001);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(318);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(1001);
			ReSlotPreview.push_back(318);
		}
		break;
		case 236: //LightBlue Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(374);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(374);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 19: //LightBlue Wool
		{
			//Requisitos
			ReSlotId.push_back(1001);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(374);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(1001);
			ReSlotPreview.push_back(374);
		}
		break;
		case 237: //Cyan Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(0);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 14: //DarkGreen Wool
		{
			//Requisitos
			ReSlotId.push_back(1001);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(373);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(1001);
			ReSlotPreview.push_back(373);
		}
		break;
		case 238: //Green Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(373);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(373);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 239: //Magneta Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(376);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(376);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 21: //Magneta Wool
		{
			//Requisitos
			ReSlotId.push_back(1001);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(376);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(1001);
			ReSlotPreview.push_back(376);
		}
		break;
		case 240: //Purple Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(375);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(375);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 20: //Purple Wool
		{
			//Requisitos
			ReSlotId.push_back(1001);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(375);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(1001);
			ReSlotPreview.push_back(375);
		}
		break;
		case 241: //Lime Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(372);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(372);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 15: //Green Wool
		{
			//Requisitos
			ReSlotId.push_back(1001);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(372);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(1001);
			ReSlotPreview.push_back(372);
		}
		break;
		case 242: //Pink Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(368);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(368);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 13: //Pink Wool
		{
			//Requisitos
			ReSlotId.push_back(1001);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(368);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(1001);
			ReSlotPreview.push_back(368);
		}
		break;
		case 243: //Gray Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(366);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(366);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 11: //Gray Wool
		{
			//Requisitos
			ReSlotId.push_back(1001);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(366);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(1001);
			ReSlotPreview.push_back(366);
		}
		break;
		case 244: //Black Terracotta
		{
			//Requisitos
			ReSlotId.push_back(231);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(367);
			ReSlotAm.push_back(1);
			//Preview
			
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(367);
				else ReSlotPreview.push_back(231);
			}
		}
		break;
		case 10: //Black Wool
		{
			//Requisitos
			ReSlotId.push_back(1001);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(367);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(1001);
			ReSlotPreview.push_back(367);
		}
		break;
		case 371: // Yellow Dye
		{
			//Requisitos
			ReSlotId.push_back(295);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(295);
		}
		break;
		case 369: // Red Dye
		{
			//Requisitos
			ReSlotId.push_back(294);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(294);
		}
		break;
		case 368: // Pink Dye
		{
			//Requisitos
			ReSlotId.push_back(369);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(322);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(369);
			ReSlotPreview.push_back(322);
		}
		break;
		case 370: // Orange Dye
		{
			//Requisitos
			ReSlotId.push_back(369);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(371);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(369);
			ReSlotPreview.push_back(371);
		}
		break;
		case 372: // Lime Dye
		{
			//Requisitos
			ReSlotId.push_back(373);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(322);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(373);
			ReSlotPreview.push_back(322);
		}
		break;
		case 375: // Purple Dye
		{
			//Requisitos
			ReSlotId.push_back(318);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(369);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(318);
			ReSlotPreview.push_back(369);
		}
		break;
		case 367: // Black Dye
		{
			//Requisitos
			ReSlotId.push_back(371);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(369);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(318);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(371);
			ReSlotPreview.push_back(322);
			ReSlotPreview.push_back(318);
		}
		break;
		case 366: // Gray Dye
		{
			//Requisitos
			ReSlotId.push_back(367);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(322);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(367);
			ReSlotPreview.push_back(322);
		}
		break;
		case 365: // Light Gray Dye
		{
			//Requisitos
			ReSlotId.push_back(366);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(322);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(366);
			ReSlotPreview.push_back(322);
		}
		break;
		case 374: // Light Blue Dye
		{
			//Requisitos
			ReSlotId.push_back(318);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(322);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(318);
			ReSlotPreview.push_back(322);
		}
		break;
		case 373: // Green Dye
		{
			//Requisitos
			ReSlotId.push_back(25);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(25);
		}
		break;
		case 376: // Magneta Dye
		{
			//Requisitos
			ReSlotId.push_back(375);
			ReSlotAm.push_back(1);
			
			ReSlotId.push_back(368);
			ReSlotAm.push_back(1);
			//Preview
			ReSlotPreview.push_back(375);
			ReSlotPreview.push_back(368);
		}
		break;
		case 198: //BlackCarpet
		{
			//Requisitos
			ReSlotId.push_back(10);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(10);
			ReSlotPreview.push_back(10);
		}
		break;
		case 199: //GrayCarpet
		{
			//Requisitos
			ReSlotId.push_back(11);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(11);
			ReSlotPreview.push_back(11);
		}
		break;
		case 200: //RedCarpet
		{
			//Requisitos
			ReSlotId.push_back(12);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(12);
			ReSlotPreview.push_back(12);
		}
		break;
		case 201: //PinkCarpet
		{
			//Requisitos
			ReSlotId.push_back(13);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(13);
			ReSlotPreview.push_back(13);
		}
		break;
		case 202: //DarkGreenCarpet
		{
			//Requisitos
			ReSlotId.push_back(14);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(14);
			ReSlotPreview.push_back(14);
		}
		break;
		case 203: //GreenCarpet
		{
			//Requisitos
			ReSlotId.push_back(15);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(15);
			ReSlotPreview.push_back(15);
		}
		break;
		case 204: //BrownCarpet
		{
			//Requisitos
			ReSlotId.push_back(16);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(16);
			ReSlotPreview.push_back(16);
		}
		break;
		case 205: //YellowCarpet
		{
			//Requisitos
			ReSlotId.push_back(17);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(17);
			ReSlotPreview.push_back(17);
		}
		break;
		case 206: //BlueCarpet
		{
			//Requisitos
			ReSlotId.push_back(18);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(18);
			ReSlotPreview.push_back(18);
		}
		break;
		case 207: //LightBlueCarpet
		{
			//Requisitos
			ReSlotId.push_back(19);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(19);
			ReSlotPreview.push_back(19);
		}
		break;
		case 208: //PurpleCarpet
		{
			//Requisitos
			ReSlotId.push_back(20);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(20);
			ReSlotPreview.push_back(20);
		}
		break;
		case 209: //MagnetaCarpet
		{
			//Requisitos
			ReSlotId.push_back(21);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(21);
			ReSlotPreview.push_back(21);
		}
		break;
		case 210: //OrangeCarpet
		{
			//Requisitos
			ReSlotId.push_back(22);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(22);
			ReSlotPreview.push_back(22);
		}
		break;
		case 211: //LightGrayCarpet
		{
			//Requisitos
			ReSlotId.push_back(23);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(23);
			ReSlotPreview.push_back(23);
		}
		break;
		case 212: //WhiteCarpet
		{
			//Requisitos
			ReSlotId.push_back(24);
			ReSlotAm.push_back(2);
			//Preview
			ReSlotPreview.push_back(24);
			ReSlotPreview.push_back(24);
		}
		break;
		case 72: //JukeBox
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(279);
			ReSlotAm.push_back(1);
			//Preview
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(279);
				else ReSlotPreview.push_back(3401);
			}
		}
		break;
		case 358: //Frame
		{
			//Requisitos
			ReSlotId.push_back(276);
			ReSlotAm.push_back(8);
			
			ReSlotId.push_back(323);
			ReSlotAm.push_back(1);
			//Preview
			for(int b = 0; b < 9; b ++)
			{
				if(b == 4) ReSlotPreview.push_back(276);
				else ReSlotPreview.push_back(323);
			}
		}
		break;
		case 297: //Paper
		{
			//Requisitos
			ReSlotId.push_back(293);
			ReSlotAm.push_back(3);

			//Preview
			ReSlotPreview.push_back(293);
			ReSlotPreview.push_back(293);
			ReSlotPreview.push_back(293);
		}
		break;
		case 298: //Book
		{
			//Requisitos
			ReSlotId.push_back(297);
			ReSlotAm.push_back(3);
			
			ReSlotId.push_back(323);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(297);
			ReSlotPreview.push_back(297);
			ReSlotPreview.push_back(297);
			ReSlotPreview.push_back(323);
		}
		break;
		case 35: //Bookshelf
		{
			//Requisitos
			ReSlotId.push_back(3401);
			ReSlotAm.push_back(6);
			
			ReSlotId.push_back(298);
			ReSlotAm.push_back(3);

			//Preview
			ReSlotPreview.push_back(3401);
			ReSlotPreview.push_back(3401);
			ReSlotPreview.push_back(3401);
			
			ReSlotPreview.push_back(298);
			ReSlotPreview.push_back(298);
			ReSlotPreview.push_back(298);
			
			ReSlotPreview.push_back(3401);
			ReSlotPreview.push_back(3401);
			ReSlotPreview.push_back(3401);
		}
		break;
		case 280: //Gold
		{
			//Requisitos
			ReSlotId.push_back(65);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(65);
		}	
		break;
		case 278: //Iron
		{
			//Requisitos
			ReSlotId.push_back(66);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(66);
		}	
		break;
		case 279: //Diamond
		{
			//Requisitos
			ReSlotId.push_back(64);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(64);
		}	
		break;
		case 318: //Lapis
		{
			//Requisitos
			ReSlotId.push_back(101);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(101);
		}	
		break;
		case 353: //RedStone
		{
			//Requisitos
			ReSlotId.push_back(215);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(215);
		}	
		break;
		case 277: //Coal
		{
			//Requisitos
			ReSlotId.push_back(214);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(214);
		}	
		break;
		case 287: //Wheat
		{
			//Requisitos
			ReSlotId.push_back(213);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(213);
		}	
		break;
		case 322: //BoneMeal
		{
			//Requisitos
			ReSlotId.push_back(321);
			ReSlotAm.push_back(1);

			//Preview
			ReSlotPreview.push_back(321);
		}	
		break;
	}
}
//Update Pag - Actualiza la pagina de crafteos.

void Recipes::UpdatePag(int Pag)
{
	SlotId.clear();
	SlotAm.clear();
	SlotSt.clear();
	
	ReSlotId.clear();
	ReSlotAm.clear();
	ReSlotPreview.clear();
	
	IndexId.clear();
	
	switch(Pag)
	{
		case 0: //Structures
		{
			//Index
			IndexId.push_back(34); //Oak
			IndexId.push_back(276); //Stick
			IndexId.push_back(216); //Quears
			IndexId.push_back(26); //SandStone
			IndexId.push_back(105); //Crafting
			
			if(!craft2x2)
			{
				IndexId.push_back(96); //Chest
				IndexId.push_back(361); //Bed
				IndexId.push_back(159); //Fence
				IndexId.push_back(306); //Door
				IndexId.push_back(67); //Stair
				IndexId.push_back(83); //Slab
			}
			
			UpdateIndex(34);
		}
		break;
		case 1: //Tools
		{
			//Index
			
			IndexId.push_back(275); //Scissors
			IndexId.push_back(308); //Torch
			
			if(!craft2x2)
			{
				IndexId.push_back(250); //Pickaxe
				IndexId.push_back(260); //Shovel
				IndexId.push_back(265); //Axe
				IndexId.push_back(270); //Hoe
				IndexId.push_back(408); //Bow
				IndexId.push_back(255); //Sword
				IndexId.push_back(415); //Shield
				IndexId.push_back(290); //Bucket
				IndexId.push_back(354); //Clock
			}
			
			UpdateIndex2(275);
		}
		break;
		case 2: //Food
		{
			//Index
			IndexId.push_back(303); //Mushroom Stew
			IndexId.push_back(314); //Cookie
			IndexId.push_back(312); //Melon Seed
			IndexId.push_back(313); //Sugar
			
			if(!craft2x2)
			{
				IndexId.push_back(285); //Golden Apple

				IndexId.push_back(81); //Melon

				IndexId.push_back(288); //Bread	
			}

			UpdateIndex3(303);
		}
		break;
		case 3: //RedStone
		{
			//Index
			IndexId.push_back(71); //Golden Apple
			
			UpdateIndex4(71);
		
		}
		break;
		case 4: //Armor
		{
			//Index
			IndexId.push_back(328); //Helmet
			IndexId.push_back(329); //Chestplace
			IndexId.push_back(330); //Leggings
			IndexId.push_back(331); //Boots
			
			UpdateIndex5(328);
		
		}
		break;
		case 5: //Decoracion
		{
			IndexId.push_back(10); //Wool
			IndexId.push_back(371); //Yellow Dye
			IndexId.push_back(198); //WhiteWoolCarpet
			IndexId.push_back(297); //Paper
			IndexId.push_back(280); //Gold
			
			//Index
			if(!craft2x2)
			{
				IndexId.push_back(349); //GlassPanel
				IndexId.push_back(64); //Diamond Block
				IndexId.push_back(228); //Terracota Black
				IndexId.push_back(72); //JukeBox
				IndexId.push_back(358); //Frame
			}
			
			UpdateIndex6(10);
		}
		break;
	}
}

void Recipes::CleanUp()
{
	SlotId.clear();
	SlotAm.clear();
	SlotSt.clear();
	
	ReSlotId.clear();
	ReSlotAm.clear();
	ReSlotPreview.clear();
	
	IndexId.clear();
}
