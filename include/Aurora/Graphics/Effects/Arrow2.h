#ifndef ARROW2_H_
#define ARROW2_H_

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
		class Arrow2
		{
		public:
			Arrow2(float pos2x, float pos2y, float pos2z);
			~Arrow2();

			void SetTexture(int texture);
			void SetVeloc(float verAngle, float horAngle, float iYBow);
			void Update(CraftWorld* crtf, float dt);
			bool CheckCollision(CraftWorld* crtf);
			bool CheckCollisionMob();
			void UpdateBBox();

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
			float iY;
			bool Kick;
			float Damage;
			float tickRe;
		};
	}
}

#endif

