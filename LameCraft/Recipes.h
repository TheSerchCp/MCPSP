#ifndef RECIPES_H_
#define RECIPES_H_

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

class Recipes
{
public:

	Recipes();
    ~Recipes();
	
	static Recipes* Instance();
	static Recipes m_Recipes;
	
	void Init();
	
	void UpdateIndex(int Index);
	void UpdateSlot(int Slot);
	
	void UpdateIndex2(int Index);
	void UpdateSlot2(int Slot);
	
	void UpdateIndex3(int Index);
	void UpdateSlot3(int Slot);
	
	void UpdateIndex4(int Index);
	void UpdateSlot4(int Slot);
	
	void UpdateIndex5(int Index);
	void UpdateSlot5(int Slot);
	
	void UpdateIndex6(int Index);
	void UpdateSlot6(int Slot);
	
	void UpdatePag(int Pag);
	
	void CleanUp();
	
	//ID del crafteo.
	std::vector<short> SlotId;
	std::vector<short> SlotAm;
	std::vector<bool> SlotSt;
	
	//Materiales para ser crafteados
	std::vector<short> ReSlotId;
	std::vector<short> ReSlotAm;
	
	std::vector<short> ReSlotPreview;
	//En que Index esta, es decir si es en tablones, mesas de trabajos etc.
	std::vector<short> IndexId;
	
	bool craft2x2;

private:


	
};

#endif
