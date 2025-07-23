#ifndef WITHERSKELETON_H
#define WITHERSKELETON_H

#include <Aurora/Graphics/Vertex.h>
#include <Aurora/Graphics/RenderManager.h>
#include <pspmath.h>
#include <psptypes.h>
#include <Aurora/Math/Frustum.h>

#include <Aurora/Math/BoundingBox.h>
#include <Aurora/Math/Frustum.h>
#include <LameCraft/LameMob.h>

class CraftWorld;

class WitherSkeleton : public LameMob
{
public:

    WitherSkeleton(Vector3 position1, int number1);
    ~WitherSkeleton();

    void BoxCollision();
    void Update(CraftWorld *myWorld, Vector3 playerPos, float dt);
    void Render(Frustum &camFrustum, float dt);
    void TakeDamage(float damage, float power, float dt);
    void TakeDamageFromPointExplosion(float damage, float power, float dt, Vector3 point);

private:

    float rHandAngle;
    float lHandAngle;
    float rLegAngle;
    float lLegAngle;

    float headAngleZ;
    float headAngleY;
	
	bool InCamara;

    float animHandAngle;
    float animHandAngleT;

    float animLegAngle;
    float animLegAngleT;

    float sunTimer;
};

#endif

