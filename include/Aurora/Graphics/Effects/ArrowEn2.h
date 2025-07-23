#ifndef ARROWEN2_H_
#define ARROWEN2_H_

//mobs
#include <LameCraft/mobs/Chicken2.h>
#include <LameCraft/mobs/Cow2.h>
#include <LameCraft/mobs/Creeper2.h>
#include <LameCraft/mobs/Pig2.h>
#include <LameCraft/mobs/Pigman2.h>
#include <LameCraft/mobs/Sheep2.h>
#include <LameCraft/mobs/Skeleton2.h>
#include <LameCraft/mobs/Spider2.h>
#include <LameCraft/mobs/Spidercave2.h>
#include <LameCraft/mobs/WitherSkeleton2.h>
#include <LameCraft/mobs/Zombie2.h>
#include <Lamecraft/LameMob.h>
#include <Aurora/Math/BoundingBox.h>

#include <Aurora/Math/Vector3.h>
#include <Aurora/Graphics/Vertex.h>
#include <pspmath.h>
#include <LameCraft/CraftWorld2.h>
#include <math.h>
#include <psptypes.h>

namespace Aurora
{
	namespace Graphics
	{
		class ArrowEn2
		{
		public:
			ArrowEn2(float pos2x, float pos2y, float pos2z);
			~ArrowEn2();

			void SetTexture(int texture);
			void SetVeloc(float xAngle, float yAngle, float zAngle, float yHeadAngle);
			void Update(CraftWorld* crtf, float dt);
			bool CheckCollision(CraftWorld* crtf);
			void UpdateBBox();
			//bool CheckCollisionPlayer(CraftWorld* crtf);
			
			float dist;
			bool Kick;
			bool InCamara;

			void Render();
			
			Vector3 position;
			Vector3 velocity;
			BoundingBox bBox;
		private:

			CraftPSPVertex *ballVertices;
			int textureNumber;
			float snowHScale;
			float snowVScale;
			float startSpeed;
			float mainAngle;
			float relPlayerPosX;
			float relPlayerPosY;
			float relPlayerPosZ;
		};
	}
}

#endif

