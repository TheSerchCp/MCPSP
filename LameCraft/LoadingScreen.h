#ifndef LOADINGSCREEN_H_
#define LOADINGSCREEN_H_

#include <pspkerneltypes.h>
#include "Panorama.h"

class LoadingScreen
{

protected:
    static int RunLoadingScreen(SceSize args, void *argp); //static int
    void RenderAll();
	SceUID thid_;

public:
	LoadingScreen();
	static bool Nether;
	static bool LoadNether;
	void KillLoadingScreen();
	static int readiness;
	static int stateName;
};

#endif
