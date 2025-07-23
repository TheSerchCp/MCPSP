#ifndef TRADES_H_
#define TRADES_H_

#include "TextureHelper.h"

#include <math.h>
#include <psptypes.h>

#include <string>
#include <pspiofilemgr.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <string>

class Trades
{
public:

	Trades();
    ~Trades();
	
	static Trades* Instance();
	static Trades m_Trades;
	
	void Init(int Proffesion, int Level, int random);
	void Update(int SlotIndex, int Proffesion, int random);
	
	void CleanUp();
	
	//ID de Tradeos.
	std::vector<short> TradeId;
	std::vector<short> TradeAm;
	std::vector<bool> TradeSt;
	std::string tradeName;
	
	//Requisitos para el Tradeo.
	std::vector<short> TradeReId;
	std::vector<short> TradeReAm;

private:


	
};

#endif
