#ifndef PIG_H_
#define PIG_H_

#include <Aurora/Graphics/Vertex.h>
#include <Aurora/Graphics/RenderManager.h>
#include <pspmath.h>
#include <psptypes.h>
#include <Aurora/Math/Frustum.h>

#include <Aurora/Math/BoundingBox.h>
#include <Aurora/Math/Frustum.h>
#include <LameCraft/LameMob.h>
#include <LameCraft/Blocks.h>
#include <LameCraft/CraftWorld2.h>

class CraftWorld;

class Pig : public LameMob
{
public:

    Pig(Vector3 position1, int number1);
    ~Pig();

    void BoxCollision();
    void Update(CraftWorld *myWorld, Vector3 playerPos, float dt);
    void Render(Frustum &camFrustum, float dt);
    void TakeDamage(float damage, float power, float dt);
    void TakeDamageFromPointExplosion(float damage, float power, float dt, Vector3 point);

	int colorpig;//Juan Alberto
	int GetColorpig(); //save colorpig
	void SetColorpig(int newProfession); //return colorpig
	
    bool rotate1;
    int handItemId;

private:

    int lastCommand;

    float rLegAngle;
    float lLegAngle;

    float headAngleY;

    float animLegAngle;
    float animLegAngleT;

    Vector3 hauntingPos;
	
	int thepigTexture; //Nombre de la textura de Juan Alberto

    bool senselessJumps;
    float senselessJumpsTimer;
    float senselessJumpsTimerMax;
};

#endif

