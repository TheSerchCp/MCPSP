#include <Aurora/Graphics/Effects/ArrowEn2.h>
#include <Aurora/Graphics/TextureManager.h>

#define PI 3.1415926535897f
#define DEG_TO_RAD (PI / 180.0f)

namespace Aurora
{
	namespace Graphics
	{
		ArrowEn2::ArrowEn2(float pos2x, float pos2y, float pos2z)
		{		
            snowHScale = 0.2f;
			snowVScale = 0.2f;

			position = Vector3(pos2x,pos2y,pos2z);

			ballVertices = (CraftPSPVertex*)memalign(16,4 * sizeof(CraftPSPVertex));

			startSpeed = 0.70;
			
			InCamara = false;
			
			bBox = BoundingBox(Vector3(0,0,0),Vector3(0,0,0));
		}

		ArrowEn2::~ArrowEn2()
		{
		    if(ballVertices != NULL)
            {
                free(ballVertices);
            }
		}

		void ArrowEn2::SetTexture(int texture)
		{
			textureNumber = texture;
		}

		void ArrowEn2::SetVeloc(float xAngle, float yAngle, float zAngle, float yHeadAngle)
		{
			float addVerAngle = (rand() % 12) * 0.01;
			
			relPlayerPosX = xAngle;
			relPlayerPosY = yAngle;
			relPlayerPosZ = zAngle;
		    
            velocity.y = sinf(yHeadAngle + addVerAngle) * startSpeed;
		}

		void  ArrowEn2::Update(CraftWorld* crtf, float dt)
		{
			
		    float myLight = crtf->BlockFinalLight(position.x,position.y,position.z);

			ScePspFMatrix4 t;
			sceGumMatrixMode(GU_VIEW);
			sceGumStoreMatrix(&t);
			sceGumMatrixMode(GU_MODEL);

            ScePspFVector3 up, right;

			right.x = t.x.x * snowHScale * 1;
			right.y = t.y.x * snowHScale * 1;
			right.z = t.z.x * snowHScale * 1;
			up.x = t.x.y * snowVScale * 1;
			up.y = t.y.y * snowVScale * 1;
			up.z = t.z.y * snowVScale * 1;

		
			float playerAngle = ATAN2_fast(position.x-relPlayerPosX,position.z-relPlayerPosZ)+PI;
			float distOld = crtf->FastDistance2d(abs(position.x-relPlayerPosX)*10,abs(position.z-relPlayerPosZ)*10)/10.0f + abs(position.y-(relPlayerPosY-0.7))/2.0f;
            
			if(distOld > 0.8f)
			{
				position += Vector3(sinf(playerAngle)*1.1f,velocity.y,cosf(playerAngle)*1.1f);
				velocity.y -= 0.3*dt;
			}
		
		
			
			
			//dist = crtf->FastDistance2d(abs(position.x-crtf->playerPos.x)*10,abs(position.z-crtf->playerPos.z)*10)/10.0f + abs(position.y-(crtf->playerPos.y-0.7))/2.0f;

			if (bBox.contains(crtf->playerPos) && Kick == false)
			{
				if(crtf->HP > 0)
                {
                    crtf->kickedStart = true;
                    crtf->kickedAngle = ATAN2_fast(position.x-crtf->playerPos.x,position.z-crtf->playerPos.z);
                    crtf->kickedBy = 3;
                    crtf->kickedDamage = 3;
					crtf->kickedinCamara = InCamara;
					Kick = true;
				}
			}
			else if (distOld <= 0.8f || position.x == relPlayerPosX || position.y == relPlayerPosY || position.z == relPlayerPosZ)
			{
				Kick = true;
			}
			else 
			{
				Kick = false;
			}
	
			UpdateBBox();
	
			int i = 0;

			ballVertices[i].x = position.x - right.x + up.x;// * stepScale;
			ballVertices[i].y = position.y - right.y + up.y;// * stepScale;
			ballVertices[i].z = position.z - right.z + up.z;// * stepScale;
            ballVertices[i].u = 0.f;// * textureScale;
			ballVertices[i].v = 0.f;// * textureScale;
			ballVertices[i].color = GU_COLOR(myLight,myLight,myLight,1);
			i++;

			// (x, y - 1, z)
			ballVertices[i].x = position.x - right.x - up.x;// * stepScale;
			ballVertices[i].y = position.y - right.y - up.y;// * stepScale;
			ballVertices[i].z = position.z - right.z - up.z;// * stepScale;
			ballVertices[i].u = 0.f;// * textureScale;
			ballVertices[i].v = 1.f;// * textureScale;
			ballVertices[i].color = GU_COLOR(myLight,myLight,myLight,1);
			i++;

			// (x + 1, y, z)
			ballVertices[i].x = position.x + right.x + up.x;// * stepScale;
			ballVertices[i].y = position.y + right.y + up.y;// * stepScale;
			ballVertices[i].z = position.z + right.z + up.z;// * stepScale;
			ballVertices[i].u = 1.f;// * textureScale;
			ballVertices[i].v = 0.f;// * textureScale;
			ballVertices[i].color = GU_COLOR(myLight,myLight,myLight,1);
			i++;

			// (x + 1, y - 1, z)
			ballVertices[i].x = position.x + right.x - up.x;// * stepScale;
			ballVertices[i].y = position.y + right.y - up.y;//* stepScale;
			ballVertices[i].z = position.z + right.z - up.z;// * stepScale;
			ballVertices[i].u = 1.f;// * textureScale;
			ballVertices[i].v = 1.f;// * textureScale;
			ballVertices[i].color = GU_COLOR(myLight,myLight,myLight,1);

			sceKernelDcacheWritebackInvalidateRange(ballVertices,4 * sizeof(CraftPSPVertex));
		}

		bool ArrowEn2::CheckCollision(CraftWorld* crtf)
		{
            if (crtf->BlockSolid(position.x+0.1875f,position.y,position.z) == true || crtf->BlockSolid(position.x-0.1875f,position.y,position.z) == true || crtf->BlockSolid(position.x,position.y-0.0625f,position.z) == true || crtf->BlockSolid(position.x,position.y+0.0625f,position.z) == true || crtf->BlockSolid(position.x,position.y,position.z+0.1875f) == true || crtf->BlockSolid(position.x,position.y,position.z-0.1875f) == true)
            {
                return 1;
            }
            else
            {
                return 0;
            }
		}
		
		void ArrowEn2::UpdateBBox()
		{
			bBox = BoundingBox(Vector3(position.x-0.5*1.45,position.y-0.5*1.3,position.z-0.5*1.45),Vector3(position.x+0.5*1.45,position.y+0.5*1.3,position.z+0.5*1.45));
		}
	
		void ArrowEn2::Render()
		{
			sceGuEnable(GU_TEXTURE_2D);
			sceGuEnable(GU_BLEND);

			sceGumDrawArray(GU_TRIANGLE_STRIP, GU_TEXTURE_32BITF |GU_COLOR_8888| GU_VERTEX_32BITF | GU_TRANSFORM_3D, 4, 0, ballVertices);

            sceGuDisable(GU_BLEND);
			sceGuDisable(GU_TEXTURE_2D);
		}
	}
}

