#include <Aurora/Graphics/Effects/Arrow2.h>
#include <Aurora/Graphics/TextureManager.h>

#define PI 3.1415926535897f
#define DEG_TO_RAD (PI / 180.0f)

namespace Aurora
{
	namespace Graphics
	{
		Arrow2::Arrow2(float pos2x, float pos2y, float pos2z)
		{		
            snowHScale = 0.2f;
			snowVScale = 0.2f;

			position = Vector3(pos2x,pos2y,pos2z);

			ballVertices = (CraftPSPVertex*)memalign(16,4 * sizeof(CraftPSPVertex));

			startSpeed = 0.70;
			
			bBox = BoundingBox(Vector3(0,0,0),Vector3(0,0,0));
		}

		Arrow2::~Arrow2()
		{
		    if(ballVertices != NULL)
            {
                free(ballVertices);
            }
		}

		void Arrow2::SetTexture(int texture)
		{
			textureNumber = texture;
		}

		void Arrow2::SetVeloc(float verAngle, float horAngle, float iYBow)
		{
			float addVerAngle = 0.01;
		    float addHorAngle = 0.0;
            velocity.x = -sinf(horAngle-PI/2 + addHorAngle) * cosf(verAngle + addVerAngle) * startSpeed;
            velocity.y = sinf(verAngle + addVerAngle) * startSpeed;
			velocity.z = cosf(horAngle-PI/2 + addHorAngle) * cosf(verAngle + addVerAngle) * startSpeed;
			iY = iYBow;
			
			if (iYBow == 2.0f)
			{
				Damage = 3.0f;
			}
			else if (iYBow == 1.0f)
			{
				Damage = 5.0f;
			}
			else if (iYBow == 0.3f)
			{
				if(rand() % 2 == 0)
                {
					Damage = 10.0f;
				}
				else
                {
					Damage = 9.0f;
				}
			}
		}

		void  Arrow2::Update(CraftWorld* crtf, float dt)
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

            velocity.y -= iY*dt;

            position.x += velocity.x;
            position.y += velocity.y;
			position.z += velocity.z;

			if (Kick == false)
			{
				if(crtf->mSpiders.empty() == false && Kick == false)
				{
					for(unsigned int j = 0; j < crtf->mSpiders.size(); j++)
					{
						if(j < crtf->mSpiders.size())
						{
							Spider* TestMob = crtf->mSpiders[j];
							if(TestMob != NULL)
							{
								if(TestMob->bBox.intersect(bBox) && Kick == false)
								{
									TestMob->TakeDamage(Damage,0.75,dt);
									Kick = true;
								}
							}
						}
					}
				}
				if(crtf->mSpidercaves.empty() == false && Kick == false)
				{
					for(unsigned int j = 0; j < crtf->mSpidercaves.size(); j++)
					{
						if(j < crtf->mSpidercaves.size())
						{
							Spidercave* TestSpidercave = crtf->mSpidercaves[j];
							if(TestSpidercave != NULL)
							{
								if(TestSpidercave->bBox.intersect(bBox) && Kick == false)
								{
									TestSpidercave->TakeDamage(Damage,0.75,dt);
									Kick = true;
								}
							}
						}
					}
				}
				if(crtf->mZombies.empty() == false && Kick == false)
				{
					for(unsigned int j = 0; j < crtf->mZombies.size(); j++)
					{
						if(j < crtf->mZombies.size())
						{
							Zombie* TestZombie = crtf->mZombies[j];
							if(TestZombie != NULL)
							{
								if(TestZombie->bBox.intersect(bBox) && Kick == false)
								{
									TestZombie->TakeDamage(Damage,0.75,dt);
									Kick = true;
								}
							}
						}
					}
				}
				
				if(crtf->mCreepers.empty() == false && Kick == false)
				{
					for(unsigned int j = 0; j < crtf->mCreepers.size(); j++)
					{
						if(j < crtf->mCreepers.size())
						{
							Creeper* TestCreeper = crtf->mCreepers[j];
							if(TestCreeper != NULL)
							{
								if(TestCreeper->bBox.intersect(bBox) && Kick == false)
								{
									TestCreeper->TakeDamage(Damage,0.75,dt);
									Kick = true;
								}
							}
						}
					}
				}
				
				if(crtf->mCows.empty() == false && Kick == false)
				{
					for(unsigned int j = 0; j < crtf->mCows.size(); j++)
					{
						if(j < crtf->mCows.size())
						{
							Cow* TestCow = crtf->mCows[j];
							if(TestCow != NULL)
							{
								if(TestCow->bBox.intersect(bBox) && Kick == false)
								{
									TestCow->TakeDamage(Damage,0.75,dt);
									Kick = true;
								}
							}
						}
					}
				}
				
				if(crtf->mSheeps.empty() == false && Kick == false)
				{
					for(unsigned int j = 0; j < crtf->mSheeps.size(); j++)
					{
						if(j < crtf->mSheeps.size())
						{
							Sheep* TestSheep = crtf->mSheeps[j];
							if(TestSheep != NULL)
							{
								if(TestSheep->bBox.intersect(bBox) && Kick == false)
								{
									TestSheep->TakeDamage(Damage,0.75,dt);
									Kick = true;
								}
							}
						}
					}
				}
				
				if(crtf->mPigs.empty() == false && Kick == false)
				{
					for(unsigned int j = 0; j < crtf->mPigs.size(); j++)
					{
						if(j < crtf->mPigs.size())
						{
							Pig* TestPig = crtf->mPigs[j];
							if(TestPig != NULL)
							{
								if(TestPig->bBox.intersect(bBox) && Kick == false)
								{
									TestPig->TakeDamage(Damage,0.75,dt);
									Kick = true;
								}
							}
						}
					}
				}
				
				if(crtf->mChickens.empty() == false && Kick == false)
				{
					for(unsigned int j = 0; j < crtf->mChickens.size(); j++)
					{
						if(j < crtf->mChickens.size())
						{
							Chicken* TestChicken = crtf->mChickens[j];
							if(TestChicken != NULL)
							{
								if(TestChicken->bBox.intersect(bBox) && Kick == false)
								{
									TestChicken->TakeDamage(Damage,0.75,dt);
									Kick = true;
								}
							}
						}
					}
				}
				
				if(crtf->mSkeletons.empty() == false && Kick == false)
				{
					for(unsigned int j = 0; j < crtf->mSkeletons.size(); j++)
					{
						if(j < crtf->mSkeletons.size())
						{
							Skeleton* TestSkeleton = crtf->mSkeletons[j];
							if(TestSkeleton != NULL)
							{
								if(TestSkeleton->bBox.intersect(bBox) && Kick == false)
								{
									TestSkeleton->TakeDamage(Damage,0.75,dt);
									Kick = true;
								}
							}
						}
					}
				}
				if(crtf->mPigmans.empty() == false && Kick == false)
				{
					for(unsigned int j = 0; j < crtf->mPigmans.size(); j++)
					{
						if(j < crtf->mPigmans.size())
						{
							Pigman* TestPigman = crtf->mPigmans[j];
							if(TestPigman != NULL)
							{
								if(TestPigman->bBox.intersect(bBox) && Kick == false)
								{
									TestPigman->TakeDamage(Damage,0.75,dt);
									Kick = true;
								}
							}
						}
					}
				}
				if(crtf->mWitherSkeletons.empty() == false && Kick == false)
				{
					for(unsigned int j = 0; j < crtf->mWitherSkeletons.size(); j++)
					{
						if(j < crtf->mWitherSkeletons.size())
						{
							WitherSkeleton* TestWitherSkeleton = crtf->mWitherSkeletons[j];
							if(TestWitherSkeleton != NULL)
							{
								if(TestWitherSkeleton->bBox.intersect(bBox) && Kick == false)
								{
									TestWitherSkeleton->TakeDamage(Damage,0.75,dt);
									Kick = true;
								}
							}
						}
					}
				}
			}
			else if (Kick == true && CheckCollisionMob() == true){
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

		bool Arrow2::CheckCollision(CraftWorld* crtf)
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
		
		bool Arrow2::CheckCollisionMob()
		{
			if (Kick == true)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		
		void Arrow2::UpdateBBox()
		{
			bBox = BoundingBox(Vector3(position.x-0.5*1.45,position.y-0.5*1.3,position.z-0.5*1.45),Vector3(position.x+0.5*1.45,position.y+0.5*1.3,position.z+0.5*1.45));
		}

		void Arrow2::Render()
		{
			sceGuEnable(GU_TEXTURE_2D);
			sceGuEnable(GU_BLEND);

			sceGumDrawArray(GU_TRIANGLE_STRIP, GU_TEXTURE_32BITF |GU_COLOR_8888| GU_VERTEX_32BITF | GU_TRANSFORM_3D, 4, 0, ballVertices);

            sceGuDisable(GU_BLEND);
			sceGuDisable(GU_TEXTURE_2D);
		}
	}
}

