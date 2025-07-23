#ifndef GLOBALFUNCTIONS_H_
#define GLOBALFUNCTIONS_H_

#include <string>
#include <pspiofilemgr.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
class GlobalFunctions
{
public:

	GlobalFunctions();
	~GlobalFunctions();
	
	static GlobalFunctions m_GlobalFunctions;
	static GlobalFunctions* Instance();
	
	bool teleported;
	bool thisWorld;
	bool CreateHell;
	char GameMode;
	char Load;
	
	bool compressed;
	
	std::string filename;
	std::string nextSaveFileName;
	std::string newWorldName;
	
	unsigned int seed_1;
	bool makeBonus;
	bool makeDungeons;
	bool Return;
	bool Start;
	int worldType;
	
	float angleX;
	float angleY;
	
	void Init();
};

#endif
