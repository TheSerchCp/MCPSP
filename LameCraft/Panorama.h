#ifndef PANORAMA_H
#define PANORAMA_H

#include <string>
#include <math.h>
#include <psptypes.h>
#include <algorithm>
#include <Aurora/Math/Frustum.h>
#include <Aurora/Math/Vector4.h>
#include <Aurora/Graphics/Effects/WeatherSystem.h>

#include <Aurora/Graphics/TextureManager.h>
#include <Aurora/Graphics/Vertex.h>
#include <Aurora/Graphics/RenderManager.h>
#include <pspmath.h>

#include "GlobalFunctions.h"

/*#include <sys/time.h>
#include <Aurora/Utils/Logger.h>
#include <Aurora/Utils/Timer.h>
#include <fstream>
#include <ostream>*/

using namespace std;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;

class Panorama
{
public:

    Panorama();
    ~Panorama();

    void render();
    void update(float dt);

private:

    float size;
    int vertCount;

    TexturesPSPVertex* box0;
    TexturesPSPVertex* box1;
    TexturesPSPVertex* box2;
    TexturesPSPVertex* box3;
    TexturesPSPVertex* box4;
    TexturesPSPVertex* box5;
	
	int panorama0;
    int panorama1;
    int panorama2;
    int panorama3;
    int panorama4;
    int panorama5;
};

#endif  // PANORAMA_H
