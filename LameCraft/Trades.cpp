#include "Trades.h"

#define ENGLISH 1
#define RUSSIAN 2

Trades Trades::m_Trades;

Trades* Trades::Instance()
{
	return &m_Trades;
}

Trades::Trades()
{

}

Trades::~Trades()
{

}

void Trades::Init(int Proffesion, int Level, int random)
{
	switch(Proffesion)
	{
		case 0: //Farmer
		{
			tradeName = "Farmer";
			//Esmerald 0
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			TradeReId.push_back(287);
			TradeReAm.push_back(18 + random);
			 
			//Potato 1
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			//Carrot 2
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			//Bean 3
			TradeId.push_back(288); 
			TradeAm.push_back(4);
			TradeSt.push_back(1);
			
			if(Level >= 10)
			{
				//Pumpkin 4
				TradeId.push_back(422); 
				TradeAm.push_back(1);
				TradeSt.push_back(1);
			}
			
			if(Level >= 20)
			{
				//Melon Seeds 5
				TradeId.push_back(312); 
				TradeAm.push_back(4);
				TradeSt.push_back(1);
				
				//Apple 6
				TradeId.push_back(284); 
				TradeAm.push_back(6);
				TradeSt.push_back(1);
			}
			
			if(Level >= 30)
			{
				//Cookie 7
				TradeId.push_back(315); 
				TradeAm.push_back(7);
				TradeSt.push_back(1);
			}
		}
		break;
		case 1: //Fisher
		{
			tradeName = "Fisher";
			//String 0
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			TradeReId.push_back(407);
			TradeReAm.push_back(15 + random);
			 
			//Coal 1
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
		}
		break;
		case 2: //Shepherd
		{
			tradeName = "Shepherd";
			//Wool 0
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			TradeReId.push_back(24);
			TradeReAm.push_back(16 + random);
			 
			//Scissors 1
			TradeId.push_back(275); 
			TradeAm.push_back(239);
			TradeSt.push_back(0);
			
			
			if(Level >= 10)
			{
				//Wool 4
				TradeId.push_back(10 + (rand() % 15)); 
				TradeAm.push_back(1);
				TradeSt.push_back(1);
			}
			
		}
		break;
		case 3: //Fletcher
		{
			tradeName = "Fletcher";
			//String 0
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			TradeReId.push_back(407);
			TradeReAm.push_back(15 + random);
			 
			//Arrow 1
			TradeId.push_back(409); 
			TradeAm.push_back(8);
			TradeSt.push_back(1);
			
			
			if(Level >= 10)
			{
				//Flip
				TradeId.push_back(351); 
				TradeAm.push_back(7);
				TradeSt.push_back(1);
				//Bow
				TradeId.push_back(408); 
				TradeAm.push_back(50);
				TradeSt.push_back(0);
			}
			
		}
		break;
		case 4: //Librarian
		{
			tradeName = "Librarian";
			//Paper 0
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			TradeReId.push_back(297);
			TradeReAm.push_back(24 + random);
			 
			//Book 1
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			//Compass
			TradeId.push_back(355); 
			TradeAm.push_back(1);
			TradeSt.push_back(0);
			
			//BookShelf
			TradeId.push_back(35); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			
			if(Level >= 10)
			{
				//Clock
				TradeId.push_back(354); 
				TradeAm.push_back(1);
				TradeSt.push_back(0);
				//Glass
				TradeId.push_back(40); 
				TradeAm.push_back(5);
				TradeSt.push_back(1);
			}
			
		}
		break;
		case 5: //Cartographer
		{
			tradeName = "Cartographer";
			//Paper 0
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			TradeReId.push_back(297);
			TradeReAm.push_back(24 + random);
			 
			//Compass
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
		}
		break;
		case 6: //Cleric
		{
			tradeName = "Cleric";
			//RottenFlesh 0
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			TradeReId.push_back(348);
			TradeReAm.push_back(36 + random);
			 
			//Gold
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			if(Level >= 10)
			{
				TradeId.push_back(353); 
				TradeAm.push_back(4);
				TradeSt.push_back(1);
				
				TradeId.push_back(318); 
				TradeAm.push_back(2);
				TradeSt.push_back(1);
			}
			
			if(Level >= 20)
			{
				TradeId.push_back(225); 
				TradeAm.push_back(3);
				TradeSt.push_back(1);
				
			}
		}
		break;
		case 7: //Armorer
		{
			tradeName = "Armorer";
			//Coal 0
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			TradeReId.push_back(277);
			TradeReAm.push_back(16 + random);
			 
			//Iron Helmet
			TradeId.push_back(336); 
			TradeAm.push_back(165);
			TradeSt.push_back(0);
			
			if(Level >= 10)
			{
				TradeId.push_back(422); 
				TradeAm.push_back(1);
				TradeSt.push_back(1);
				
				TradeId.push_back(337); 
				TradeAm.push_back(240);
				TradeSt.push_back(0);
			}
			
			if(Level >= 20)
			{
				TradeId.push_back(422); 
				TradeAm.push_back(1);
				TradeSt.push_back(1);
				
				TradeId.push_back(341); 
				TradeAm.push_back(528);
				TradeSt.push_back(0);
			}
			
			if(Level >= 30)
			{
				//Slot Helmet Iron
				TradeId.push_back(332);
				TradeAm.push_back(165);
				TradeSt.push_back(0);
				
				//Slot Chestplace Iron
				TradeId.push_back(333);
				TradeAm.push_back(240);
				TradeSt.push_back(0);
				
				//Slot Leggings Iron
				TradeId.push_back(334);
				TradeAm.push_back(225);
				TradeSt.push_back(0);
				
				//Slot Boots Iron
				TradeId.push_back(335);
				TradeAm.push_back(195);
				TradeSt.push_back(0);
			}
		}
		break;
		case 8: //Weapon
		{
			tradeName = "Weapon Smith";
			//Coal 0
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			TradeReId.push_back(277);
			TradeReAm.push_back(16 + random);
			 
			//Iron Axe
			TradeId.push_back(267); 
			TradeAm.push_back(251);
			TradeSt.push_back(0);
			
			if(Level >= 10)
			{
				TradeId.push_back(422); 
				TradeAm.push_back(1);
				TradeSt.push_back(1);
				//Iron Sword
				TradeId.push_back(257); 
				TradeAm.push_back(251);
				TradeSt.push_back(0);
			}
			
			if(Level >= 20)
			{
				TradeId.push_back(422); 
				TradeAm.push_back(1);
				TradeSt.push_back(1);
				
				TradeId.push_back(258); 
				TradeAm.push_back(1562);
				TradeSt.push_back(0);
				
				TradeId.push_back(268); 
				TradeAm.push_back(1562);
				TradeSt.push_back(0);
			}
		}
		break;
		case 9: //Tools
		{
			tradeName = "Tool Smith";
			//Coal 0
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			TradeReId.push_back(277);
			TradeReAm.push_back(16 + random);
			 
			//Iron Shovel
			TradeId.push_back(262); 
			TradeAm.push_back(251);
			TradeSt.push_back(0);
			
			if(Level >= 10)
			{
				TradeId.push_back(422); 
				TradeAm.push_back(1);
				TradeSt.push_back(1);
				//Iron Pickaxe
				TradeId.push_back(252); 
				TradeAm.push_back(251);
				TradeSt.push_back(0);
			}
			
			if(Level >= 20)
			{
				TradeId.push_back(422); 
				TradeAm.push_back(1);
				TradeSt.push_back(1);
				
				TradeId.push_back(253); 
				TradeAm.push_back(1562);
				TradeSt.push_back(0);
			}
		}
		break;
		case 10: //Butcher
		{
			tradeName = "Butcher";
			//Raw Porkchop 0
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			TradeReId.push_back(392);
			TradeReAm.push_back(14 + random);
			 
			//Raw Chicken
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			if(Level >= 10)
			{
				TradeId.push_back(422); 
				TradeAm.push_back(1);
				TradeSt.push_back(1);
				//Cooked Porkchop
				TradeId.push_back(393); 
				TradeAm.push_back(6);
				TradeSt.push_back(1);
				//Cooked Chicken
				TradeId.push_back(397); 
				TradeAm.push_back(6);
				TradeSt.push_back(1);
			}
		}
		break;
		case 11: //Leatherworker
		{
			tradeName = "Leatherworker";
			//Leather 0
			TradeId.push_back(422); 
			TradeAm.push_back(1);
			TradeSt.push_back(1);
			
			TradeReId.push_back(323);
			TradeReAm.push_back(9 + random);
			
			if(Level >= 10)
			{
				TradeId.push_back(330); 
				TradeAm.push_back(75);
				TradeSt.push_back(0);
			}
			
			if(Level >= 20)
			{
				TradeId.push_back(329); 
				TradeAm.push_back(80);
				TradeSt.push_back(0);
			}
		}
		break;
	}
}

void Trades::Update(int SlotIndex, int Proffesion, int random)
{
	TradeReId.clear();
	TradeReAm.clear();
	
	int IDItem = TradeId[SlotIndex];
	
	switch(Proffesion)
	{
		case 0: //Farmer
		{
			switch(IDItem)
			{
				case 422:
				{
					switch(SlotIndex)
					{
						case 0:
						{
							//Wheal
							TradeReId.push_back(287);
							TradeReAm.push_back(18 + random);
						}
						break;
						case 1:
						{
							//Patato
							TradeReId.push_back(379);
							TradeReAm.push_back(16 + random);
						}
						break;
						case 2:
						{
							//Carrot
							TradeReId.push_back(382);
							TradeReAm.push_back(16 + random);
						}
						break;
						case 4:
						{
							//Pumpkin
							TradeReId.push_back(75);
							TradeReAm.push_back(8 + random);
						}
						break;
					}
				}
				break;
				case 312: //Melon
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(4 + random);
				}
				break;
				case 288: //Bean
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(2 + random);
				}
				break;
				case 284: //Apple
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(1);
				}
				break;
				case 315: //Cookie
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(1);
				}
				break;
			}
		}
		break;
		case 1: //Fisher
		{
			switch(IDItem)
			{
				case 422:
				{
					switch(SlotIndex)
					{
						case 0:
						{
							//String
							TradeReId.push_back(407);
							TradeReAm.push_back(15 + random);
						}
						break;
						case 1:
						{
							//Coal
							TradeReId.push_back(277);
							TradeReAm.push_back(16 + random);
						}
						break;
					}
				}
				break;
			}
		}
		break;
		case 2: //Shepherd
		{
			switch(IDItem)
			{
				case 422:
					TradeReId.push_back(24);
					TradeReAm.push_back(16 + random);
				break;
				case 275:
					TradeReId.push_back(422);
					TradeReAm.push_back(2 + random);
				break;
			}
			
			if(IDItem >= 10 && IDItem <= 24)
			{
				TradeReId.push_back(422);
				TradeReAm.push_back(2 + random);
			}
		}
		break;
		case 3: //Fletcher
		{
			switch(IDItem)
			{
				case 422: //Esmerald
				{
					TradeReId.push_back(407);
					TradeReAm.push_back(15 + random);
				}
				break;
				case 409: //Arrow
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(2 + random);
				}
				break;
				case 351: //Flip
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(1);
					
					TradeReId.push_back(113);
					TradeReAm.push_back(10 + random);
				}
				break;
				case 408: //Bow
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(2 + random);
				}
				break;
			}
		}
		break;
		case 4: //Librarian
		{
			switch(IDItem)
			{
				case 422: //Esmerald
				{
					switch(SlotIndex)
					{
						case 0:
							TradeReId.push_back(297);
							TradeReAm.push_back(24+ random);
						break;
						case 1:
							TradeReId.push_back(298);
							TradeReAm.push_back(8 + random);
						break;
					}
				}
				break;
				case 355: //Compass
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(12 + random);
				}
				break;
				case 35: //BookShelf
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(4 + random);
				}
				break;
				case 354: //Clock
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(12 + random);
				}
				break;
				case 40: //Glass
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(1 + random);
				}
				break;
			}
		}
		break;
		case 5: //Cartographer
		{
			switch(IDItem)
			{
				case 422: //Esmerald
				{
					switch(SlotIndex)
					{
						case 0:
							TradeReId.push_back(297);
							TradeReAm.push_back(24 + random);
						break;
						case 1:
							TradeReId.push_back(355);
							TradeReAm.push_back(1 + random);
						break;
					}
				}
				break;
			}
		}
		break;
		case 6: //Cleric
		{
			switch(IDItem)
			{
				case 422: //Esmerald
				{
					switch(SlotIndex)
					{
						case 0:
							TradeReId.push_back(348);
							TradeReAm.push_back(36 + random);
						break;
						case 1:
							TradeReId.push_back(280);
							TradeReAm.push_back(8 + random);
						break;
					}
				}
				break;
				default:
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(1);
				}
				break;
			}
		}
		break;
		case 7: //Armorer
		{
			switch(IDItem)
			{
				case 422: //Esmerald
				{
					switch(SlotIndex)
					{
						case 0:
							TradeReId.push_back(277);
							TradeReAm.push_back(16 + random);
						break;
						case 2:
							TradeReId.push_back(278);
							TradeReAm.push_back(8 + random);
						break;
						case 4:
							TradeReId.push_back(279);
							TradeReAm.push_back(3 + random);
						break;
					}
				}
				break;
				case 336: //Iron Helmet
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(4 + random);
				}
				break;
				case 337://Iron Chestplace
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(11 + random);
				}
				break;
				case 341: //Diamond Chestplace
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(16 + random);
				}
				break;
				case 332: //Helmet
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(5 + random);
				}
				break;
				case 333: //Chestplace
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(9 + random);
				}
				break;
				case 334: //Leggings
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(5 + random);
				}
				break;
				case 335: //Boots
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(11 + random);
				}
				break;
				default:
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(1);
				}
				break;
			}
		}
		break;
		case 8: //Weapon
		{
			switch(IDItem)
			{
				case 422: //Esmerald
				{
					switch(SlotIndex)
					{
						case 0:
							TradeReId.push_back(277);
							TradeReAm.push_back(16 + random);
						break;
						case 2:
							TradeReId.push_back(278);
							TradeReAm.push_back(8 + random);
						break;
						case 4:
							TradeReId.push_back(279);
							TradeReAm.push_back(3 + random);
						break;
					}
				}
				break;
				case 267: //Iron Axe
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(6 + random);
				}
				break;
				case 257://Iron Sword
				{
					TradeReId.push_back(257);
					TradeReAm.push_back(10 + random);
				}
				break;
				case 258: //Diamond Sword
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(12 + random);
				}
				break;
				case 268: //Diamond Axe
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(9 + random);
				}
				break;
				default:
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(1);
				}
				break;
			}
		}
		break;
		case 9: //Tools
		{
			switch(IDItem)
			{
				case 422: //Esmerald
				{
					switch(SlotIndex)
					{
						case 0:
							TradeReId.push_back(277);
							TradeReAm.push_back(16 + random);
						break;
						case 2:
							TradeReId.push_back(278);
							TradeReAm.push_back(8 + random);
						break;
						case 4:
							TradeReId.push_back(279);
							TradeReAm.push_back(3 + random);
						break;
					}
				}
				break;
				case 262: //Iron Shovel
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(6 + random);
				}
				break;
				case 252://Iron Pickaxe
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(10 + random);
				}
				break;
				case 253: //Diamond Pickaxe
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(12 + random);
				}
				break;
				default:
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(1);
				}
				break;
			}
		}
		break;
		case 10: //Butcher
		{
			switch(IDItem)
			{
				case 422: //Esmerald
				{
					switch(SlotIndex)
					{
						case 0:
							TradeReId.push_back(392);
							TradeReAm.push_back(14 + random);
						break;
						case 1:
							TradeReId.push_back(396);
							TradeReAm.push_back(14 + random);
						break;
						case 2:
							TradeReId.push_back(277);
							TradeReAm.push_back(16 + random);
						break;
					}
				}
				break;
				default:
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(1);
				}
				break;
			}
		}
		break;
		case 11: //Leatherworker
		{
			switch(IDItem)
			{
				case 422: //Esmerald
				{
					TradeReId.push_back(323);
					TradeReAm.push_back(9 + random);
				}
				break;
				case 330:
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(2 + random);
				}
				break;
				case 329:
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(4 + random);
				}
				break;
				default:
				{
					TradeReId.push_back(422);
					TradeReAm.push_back(1);
				}
				break;
			}
		}
		break;
	}
}

void Trades::CleanUp()
{
	TradeId.clear();
	TradeAm.clear();
	TradeSt.clear();
	
	TradeReId.clear();
	TradeReAm.clear();
	tradeName.clear();
}
