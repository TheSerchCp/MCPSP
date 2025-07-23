#include <Aurora/Graphics/Effects/InventoryPlayer.h>
#include <Aurora/Graphics/TextureManager.h>

#define PI 3.1415926535897f
#define DEG_TO_RAD (PI / 180.0f)
#define PIXEL 1.0f / 16.0f
#define GRAVITY -6.8f
#define JUMPVELOCITY 4.6f

namespace Aurora
{
	namespace Graphics
	{
		InventoryPlayer::InventoryPlayer()
		{
            rHandAngle = PI;
            lHandAngle = PI;
            rLegAngle = PI;
            lLegAngle = PI;

            mainAngle = 0.0f;
            scale = 1.0f;

            position = Vector3(0,0,0);
            animT = 0.0f;
			animR = 0.0f;
		}

		InventoryPlayer::~InventoryPlayer()
		{

		}

		void  InventoryPlayer::Update()
		{

		}

		void InventoryPlayer::Render(CraftWorld *world, float dt, float angle, int texNum, int handItemId, int hand2ItemId, bool sprint, bool shield, bool moving, float shift_x, float animDest)
		{
            animT += PI*dt*0.5f;
            if(animT >= 2*PI)
            {
                animT = 0.0f;
            }
			
			if(sprint)
			{
				animR += PI*dt*4.5f;
				if(animR >= 2*PI)
				{
					animR = 0.0f;
				}
			}
			else if(shield && moving)
			{
				animR += PI*dt*0.5f;
				if(animR >= 2*PI)
				{
					animR = 0.0f;
				}
			}
			else
			{
				animR = 0.0f;
			}
			
			float armSwing = sinf(animR) * 0.75f;  // Aumentamos el movimiento de brazos
			float legSwing = -sinf(animR) * 1.5f;
			
            sceGumPushMatrix();

            ScePspFVector3 loc22 = {position.x,position.y,position.z};
            sceGumTranslate(&loc22);

            sceGumRotateZ(0.0f);
            sceGumRotateY(mainAngle-PI/2);

            sceGuEnable(GU_TEXTURE_2D);
            sceGuEnable(GU_ALPHA_TEST);
            sceGuEnable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);


            // right hand
            TextureManager::Instance()->SetTextureModeulate(texNum);
            sceGumPushMatrix();
            ScePspFVector3 loc3 = {0,PIXEL*4,PIXEL*6};
            sceGumTranslate(&loc3);

            sceGumRotateX(-0.045+sinf(animT)*0.045);
            sceGumRotateY(0.0f);
			

			if(sprint == true)
			{
				sceGumRotateZ(rHandAngle + armSwing * 0.5f);
			}
			else 
			{
				sceGumRotateZ(rHandAngle);
			}

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->handVertices);
            sceGumPopMatrix();


            // left hand
            sceGumPushMatrix();
            ScePspFVector3 loc4 = {0,PIXEL*4,-PIXEL*6};
            sceGumTranslate(&loc4);

            sceGumRotateX(0.045+sinf(animT+PI)*0.045);
            sceGumRotateY(0.0f);

			if(shield == true)
			{
				sceGumRotateZ(rHandAngle + (sinf(animDest) * 0.5f));
			}
			else if(sprint == true)
			{
				if(handItemId != -1)
				{
					sceGumRotateZ(lHandAngle+PI/9.0f + (-armSwing) * 0.5f + (sinf(animDest) * 0.5f));
				}
				else
				{
					sceGumRotateZ(lHandAngle + (-armSwing) * 0.5f);
				}
			}
			else 
			{
				if(handItemId != -1)
				{
					sceGumRotateZ(lHandAngle+PI/9.0f);
				}
				else
				{
					sceGumRotateZ(lHandAngle);
				}
			}

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->handVertices);
			
            // ITEM IN OUR HAND
            sceGumPushMatrix();
			if(handItemId != -1)
            {
                if(handItemId >= 250)
                {
                    world->ItemHaveTerrainTexture(handItemId) == true ? TextureManager::Instance()->SetTextureModeulate(world->textureTerrainId) : TextureManager::Instance()->SetTextureModeulate(world->textureItemsId);
					if(handItemId <= 274)
                    {
                        ScePspFVector3 loc40 = {-PIXEL*4.7f,PIXEL*6.9,-PIXEL*0};
                        sceGumTranslate(&loc40);

                        sceGumRotateX(0.0f);
                        sceGumRotateY(0.0f);
						
						if(shield == true)
						{
							sceGumRotateZ(-PI*0.68f - (sinf(animDest) * 0.5f));
						}
						else if(sprint == true)
						{
							sceGumRotateZ(-PI*0.68f +(-armSwing) * 0.5f + (sinf(animDest) * 0.5f));
						}
						else
						{
							sceGumRotateZ(-PI*0.68f);
						}

                        ScePspFVector3 scale = {0.80,0.80,0.80};
                        sceGumScale(&scale);
                    }
					else
					{
						ScePspFVector3 loc40 = {-PIXEL*5.0f,PIXEL*7.3,0};
						sceGumTranslate(&loc40);

						if(shield == true)
						{
							sceGumRotateZ(-PI/3.5f - (sinf(animDest) * 0.5f));
						}
						else if(sprint == true)
						{
							sceGumRotateZ(-PI/3.5f +(-armSwing) * 0.5f + (sinf(animDest) * 0.5f));
						}
						else
						{
							sceGumRotateZ(-PI/3.5f);
						}
						
						sceGumRotateY(PI/2.0f);
						sceGumRotateX(0.18f);

						ScePspFVector3 scale = {0.53,0.53,0.53};
						sceGumScale(&scale);
					}

                    world->drawFull3DItemInv(handItemId,1.0f);
                }
                else
                {
                    TextureManager::Instance()->SetTextureModeulate(world->textureTerrainId);

                    ScePspFVector3 loc40 = {-PIXEL*2.4,PIXEL*8.4,0.0};
                    sceGumTranslate(&loc40);

                    sceGumRotateX(0.0f);
                    sceGumRotateY(PI/4.0f);

					if(shield == true)
					{
						sceGumRotateZ(-0.15 - (sinf(animDest) * 0.5f));
					}
					else if(sprint == true)
					{
						sceGumRotateZ(-0.15 +(-armSwing) * 0.5f + (sinf(animDest) * 0.5f));
					}
					else
					{
						sceGumRotateZ(-0.15);
					}

                    ScePspFVector3 scale = {0.3,0.3,0.3};
                    sceGumScale(&scale);

                    world->drawCubes(handItemId,1.0f);
                }
            }
			
			sceGumPopMatrix();
            sceGumPopMatrix();
			sceGuEnable(GU_TEXTURE_2D);
			
			// Shield render
			if(hand2ItemId != -1)
            {
                if(hand2ItemId >= 250)
                {
					sceGumPushMatrix();
                    world->ItemHaveTerrainTexture(hand2ItemId) == true ? TextureManager::Instance()->SetTextureModeulate(world->textureTerrainId) : TextureManager::Instance()->SetTextureModeulate(world->textureItemsId);
					
					if(shield)
					{
						ScePspFVector3 loc41 = {PIXEL*10,0,PIXEL*8};
                        sceGumTranslate(&loc41);
						
						sceGumRotateY(PI/2.0f);
						sceGumRotateX(0.0f);
						sceGumRotateZ(2.8f);
					}
					else
					{
						ScePspFVector3 loc41 = {0,0,PIXEL*8};
						sceGumTranslate(&loc41);
						
						sceGumRotateX(0.0f);
						sceGumRotateY(0.0f);
						
						
						if(sprint == true)
						{
							sceGumRotateZ(2.8f + armSwing * 0.5f);//sceGumRotateZ(PI);
						}
						else
						{
							sceGumRotateZ(2.8f);//sceGumRotateZ(PI);
						}
					}

					ScePspFVector3 scale = {0.53 * 2,0.53 * 2,0.53 * 2};
					sceGumScale(&scale);

                    world->drawFull3DItemInv(hand2ItemId,1.0f);	
					sceGumPopMatrix();
					sceGuEnable(GU_TEXTURE_2D);
                }
            }
			
            // right leg
            TextureManager::Instance()->SetTextureModeulate(texNum);
            sceGumPushMatrix();
            ScePspFVector3 loc5 = {0,-PIXEL*8,PIXEL*2};
            sceGumTranslate(&loc5);

            sceGumRotateX(0.0f);
            sceGumRotateY(0.0f);
			
			if(sprint == true || (shield == true && moving == true))
			{
				sceGumRotateZ(rLegAngle + legSwing * 0.3f);
			}
			else
			{
				sceGumRotateZ(rLegAngle);
			}

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->legVertices);
            sceGumPopMatrix();


            // left leg
            TextureManager::Instance()->SetTextureModeulate(texNum);
            sceGumPushMatrix();
            ScePspFVector3 loc6 = {0,-PIXEL*8,-PIXEL*2};
            sceGumTranslate(&loc6);

            sceGumRotateX(0.0f);
            sceGumRotateY(0.0f);
			
			if(sprint == true || (shield == true && moving == true)) 
			{
				sceGumRotateZ(lLegAngle + (-legSwing) * 0.3f);
			}
			else
			{
				sceGumRotateZ(lLegAngle);
			}

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->legVertices);
            sceGumPopMatrix();


            // body
            TextureManager::Instance()->SetTextureModeulate(texNum);
            sceGumPushMatrix();
            ScePspFVector3 loc = {0,0,0};
            sceGumTranslate(&loc);

            sceGumRotateX(0.0f);
            sceGumRotateY(0.0f);
            sceGumRotateZ(0.0f);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->bodyVertices);
            sceGumPopMatrix();



            // head
            TextureManager::Instance()->SetTextureModeulate(texNum);
            sceGumPushMatrix();
            ScePspFVector3 loc2 = {0,PIXEL*10,0};
            sceGumTranslate(&loc2);

            sceGumRotateX(0.0f);
            sceGumRotateY(0.0f + -(shift_x * 2.0f));
            sceGumRotateZ(0.0f);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->headVertices);
            sceGumPopMatrix();
			
			// head capa
            TextureManager::Instance()->SetTextureModeulate(texNum);
            sceGumPushMatrix();
            ScePspFVector3 loc15 = {0,PIXEL*10,0};
            sceGumTranslate(&loc15);
			
			ScePspFVector3 sca = {1.1f,1.1f,1.1f};
			sceGumScale(&sca);

            sceGumRotateX(0.0f);
            sceGumRotateY(0.0f + -(shift_x * 2.0f));
            sceGumRotateZ(0.0f);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->headCapaVertices);
            sceGumPopMatrix();


            // hat
            /*TextureManager::Instance()->SetTextureModeulate(texNum);
            sceGumPushMatrix();
            sceGumTranslate(&loc2);

            sceGumRotateX(0.0f);
            sceGumRotateY(0.0f);
            sceGumRotateZ(0.0f);

            sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 36, 0, world->hatVertices);
            sceGumPopMatrix();*/

            // boot
            if(world->armorId[3] != 327)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc11 = {0,-PIXEL*8,PIXEL*2};
                sceGumTranslate(&loc11);

                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);
				
				if(sprint == true || (shield == true && moving == true))
				{
					sceGumRotateZ(rLegAngle + (legSwing) * 0.3f);
				}
				else
				{
					sceGumRotateZ(rLegAngle);
				}

                world->drawArmor(world->armorId[3],1.0f);
                sceGumPopMatrix();
            }


            // boot
            if(world->armorId[3] != 327)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc12 = {0,-PIXEL*8,-PIXEL*2};
                sceGumTranslate(&loc12);

                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);
				
                if(sprint == true || (shield == true && moving == true))
				{
					sceGumRotateZ(lLegAngle + (-legSwing) * 0.3f);
				}
				else
				{
					sceGumRotateZ(lLegAngle);
				}

                world->drawArmor(world->armorId[3],1.0f);
                sceGumPopMatrix();
            }


            // legging
            if(world->armorId[2] != 326)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc9 = {0,-PIXEL*8,PIXEL*2};
                sceGumTranslate(&loc9);

                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);
				
                if(sprint == true || (shield == true && moving == true))
				{
					sceGumRotateZ(rLegAngle + (legSwing) * 0.3f);
				}
				else
				{
					sceGumRotateZ(rLegAngle);
				}

                world->drawArmor(world->armorId[2],1.0f);
                sceGumPopMatrix();
            }


            // legging
            if(world->armorId[2] != 326)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc10 = {0,-PIXEL*8,-PIXEL*2};
                sceGumTranslate(&loc10);

                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);
				
                if(sprint == true || (shield == true && moving == true))
				{
					sceGumRotateZ(lLegAngle + (-legSwing) * 0.3f);
				}
				else
				{
					sceGumRotateZ(lLegAngle);
				}

                world->drawArmor(world->armorId[2],1.0f);
                sceGumPopMatrix();
            }

            // belly
            if(world->armorId[2] != 326)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc14 = {0,0,0};
                sceGumTranslate(&loc14);

                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);
                sceGumRotateZ(0.0f);

                world->drawBelly(world->armorId[2],1.0f);
                sceGumPopMatrix();
            }


            // helmet
            if(world->armorId[0] != 324)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc7 = {0,PIXEL*10,0};
                sceGumTranslate(&loc7);

                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f + -(shift_x  * 2.0f));
                sceGumRotateZ(0.0f);

                if(world->armorId[0] == Pumpkin3::getID())
                {
                    ScePspFVector3 sca = {0.6f,0.6f,0.6f};
                    sceGumScale(&sca);
                    TextureManager::Instance()->SetTextureModeulate(TextureHelper::Instance()->GetTexture(TextureHelper::Terrain1));
                    world->drawCubes(Pumpkin2::getID(),1.0f);
                }
                else
                {
                    world->drawArmor(world->armorId[0],1.0f);
                }

                sceGumPopMatrix();
            }

            // chestplate
            if(world->armorId[1] != 325)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc8 = {0,0,0};
                sceGumTranslate(&loc8);

                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);
                sceGumRotateZ(0.0f);

                world->drawArmor(world->armorId[1],1.0f);
                sceGumPopMatrix();

                // right shoulder
                sceGumPushMatrix();
                ScePspFVector3 loc3 = {0,PIXEL*4,PIXEL*6};
                sceGumTranslate(&loc3);

                sceGumRotateX(-0.045+sinf(animT)*0.045);
                sceGumRotateY(0.0f);
				
                if(sprint == true)
				{
					sceGumRotateZ(rHandAngle + armSwing * 0.5f);
				}
				else 
				{
					sceGumRotateZ(rHandAngle);
				}
			
                world->drawShoulder(world->armorId[1],1.0f);
                sceGumPopMatrix();

                // left shoulder
                sceGumPushMatrix();
                ScePspFVector3 loc4 = {0,PIXEL*4,-PIXEL*6};
                sceGumTranslate(&loc4);

                sceGumRotateX(0.045+sinf(animT+PI)*0.045);
                sceGumRotateY(0.0f);
				
				if(sprint == true)
				{
					if(handItemId != -1)
					{
						sceGumRotateZ(lHandAngle+PI/9.0f + (-armSwing) * 0.5f);
					}
					else
					{
						sceGumRotateZ(lHandAngle + (-armSwing) * 0.5f);
					}
				}
				else 
				{
					if(handItemId != -1)
					{
						sceGumRotateZ(lHandAngle+PI/9.0f);
					}
					else
					{
						sceGumRotateZ(lHandAngle);
					}
				}

                world->drawShoulder(world->armorId[1],1.0f);
                sceGumPopMatrix();
            }
			
            sceGuDisable(GU_DEPTH_TEST);
            sceGuDisable(GU_BLEND);
            sceGuDisable(GU_ALPHA_TEST);
            sceGuDisable(GU_TEXTURE_2D);
            sceGuColor(0xFFFFFFFF);

            sceGumPopMatrix();
		}
	}
}

