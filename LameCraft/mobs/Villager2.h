#ifndef VILLAGER_H_
#define VILLAGER_H_

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

class Villager : public LameMob
{
public:

    Villager(Vector3 position1, int number1);
    ~Villager();

    void BoxCollision();
    void Update(CraftWorld *myWorld, Vector3 playerPos, float dt);
    void Render(Frustum &camFrustum, float dt);
    void TakeDamage(float damage, float power, float dt);
    void TakeDamageFromPointExplosion(float damage, float power, float dt, Vector3 point);

	int Profession;//Profesion 
	int GetProfession(); //Obtener la profesion para guardar
	void SetProfession(int newProfession); //Devuelve la profession a cada aldeano.
	int LevelProfession; //Nivel de los tradeos
	int randomVillager; //Random Tradeos
	
    bool rotate1;
	bool tradder;
    int handItemId;

private:

    int lastCommand;

    float rLegAngle;
    float lLegAngle;

    float headAngleY;

    float animLegAngle;
    float animLegAngleT;

    Vector3 hauntingPos;
	
	int thevillagerTexture; //Nombre de la textura de Juan Alberto

    bool senselessJumps;
    float senselessJumpsTimer;
    float senselessJumpsTimerMax;
	
	int butcher;
	int farmer;
	int librarian;
	int priest;
	int smith;
};

#endif

