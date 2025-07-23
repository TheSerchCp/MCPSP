#ifndef SKELETON_H_
#define SKELETON_H_

#include <Aurora/Graphics/Vertex.h>
#include <Aurora/Graphics/RenderManager.h>
#include <pspmath.h>
#include <psptypes.h>
#include <Aurora/Math/Frustum.h>
#include <LameCraft/CraftWorld2.h>

#include <Aurora/Math/BoundingBox.h>
#include <Aurora/Math/Frustum.h>
#include <LameCraft/LameMob.h>


class CraftWorld;

class Skeleton : public LameMob
{
public:

    Skeleton(Vector3 position1, int number1);
    ~Skeleton();

    void BoxCollision();
    void Update(CraftWorld *myWorld, Vector3 playerPos, float dt);
    void Render(Frustum &camFrustum, float dt);
    void TakeDamage(float damage, float power, float dt);
    void TakeDamageFromPointExplosion(float damage, float power, float dt, Vector3 point);

	bool lanzar;
	
	bool InCamara;
	
	float AnglePlayer;
	
	float headAngleZ;
    float headAngleY;
	
	int barItems;
	
private:
    
	
    float rHandAngle;
    float lHandAngle;
    float rLegAngle;
    float lLegAngle;

    //float headAngleZ;
    //float headAngleY;

    float animHandAngle;
    float animHandAngleT;

    float animLegAngle;
    float animLegAngleT;

    float sunTimer;
	
    float tatack;
	
};



#endif

