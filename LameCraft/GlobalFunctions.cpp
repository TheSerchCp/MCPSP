#include "GlobalFunctions.h"

GlobalFunctions GlobalFunctions::m_GlobalFunctions;

GlobalFunctions* GlobalFunctions::Instance()
{
	return &m_GlobalFunctions;
}

GlobalFunctions::GlobalFunctions()
{
	filename = "";
	nextSaveFileName = "";
	newWorldName = "";
}

GlobalFunctions::~GlobalFunctions()
{
	
}

void GlobalFunctions::Init()
{
	teleported = false;
	thisWorld = false;
	CreateHell = false;
	GameMode = 0;
	Load = 1;
	
	seed_1 = 0;
	makeBonus = false;
	makeDungeons = true;
	worldType = 0;
	
	compressed = true;
	
	Return = false;
	Start = false;
	
	angleX = 0.0f;
	angleY = 0.0f;
}