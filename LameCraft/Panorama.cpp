#include "Panorama.h"
#include <Aurora/Graphics/TextureManager.h>

Panorama::Panorama()
{
	vertCount = 0;

	//BUILD VERTICES
	box0 = (TexturesPSPVertex*)memalign(16,4 * sizeof(TexturesPSPVertex));
	box1 = (TexturesPSPVertex*)memalign(16,4 * sizeof(TexturesPSPVertex));
	box2 = (TexturesPSPVertex*)memalign(16,4 * sizeof(TexturesPSPVertex));
	box3 = (TexturesPSPVertex*)memalign(16,4 * sizeof(TexturesPSPVertex));
	box4 = (TexturesPSPVertex*)memalign(16,4 * sizeof(TexturesPSPVertex));
	box5 = (TexturesPSPVertex*)memalign(16,4 * sizeof(TexturesPSPVertex));
	
	panorama0 = TextureHelper::Instance()->GetTexture(TextureHelper::Panorama0);
    panorama1 = TextureHelper::Instance()->GetTexture(TextureHelper::Panorama1);
    panorama2 = TextureHelper::Instance()->GetTexture(TextureHelper::Panorama2);
    panorama3 = TextureHelper::Instance()->GetTexture(TextureHelper::Panorama3);
    panorama4 = TextureHelper::Instance()->GetTexture(TextureHelper::Panorama4);
    panorama5 = TextureHelper::Instance()->GetTexture(TextureHelper::Panorama5);

	size = 1.0f;

	int i = 0;

		box0[i].x = -size;
		box0[i].y = -size;
		box0[i].z = -size;
		box0[i].u = 0;
		box0[i].v = 1;
		i++;

		box0[i].x = size;
		box0[i].y = -size;
		box0[i].z = -size;
		box0[i].u = 1;
		box0[i].v = 1;
		i++;

		box0[i].x = size;
		box0[i].y = size;
		box0[i].z = -size;
		box0[i].u = 1;
		box0[i].v = 0;
		i++;

		box0[i].x = -size;
		box0[i].y = size;
		box0[i].z = -size;
		box0[i].u = 0;
		box0[i].v = 0;
		i++;

		sceKernelDcacheWritebackInvalidateRange(box0,4 * sizeof(TexturesPSPVertex));

		i = 0;

		box1[i].x = size;
		box1[i].y = -size;
		box1[i].z = size;
		box1[i].u = 1;
		box1[i].v = 1;
		i++;

		box1[i].x = size;
		box1[i].y = size;
		box1[i].z = size;
		box1[i].u = 1;
		box1[i].v = 0;
		i++;

		box1[i].x = size;
		box1[i].y = size;
		box1[i].z = -size;
		box1[i].u = 0;
		box1[i].v = 0;
		i++;

		box1[i].x = size;
		box1[i].y = -size;
		box1[i].z = -size;
		box1[i].u = 0;
		box1[i].v = 1;
		i++;

		sceKernelDcacheWritebackInvalidateRange(box1,4 * sizeof(TexturesPSPVertex));

		i = 0;

		box2[i].x = -size;
		box2[i].y = size;
		box2[i].z = size;
		box2[i].u = 1;
		box2[i].v = 0;
		i++;

		box2[i].x = size;
		box2[i].y = size;
		box2[i].z = size;
		box2[i].u = 0;
		box2[i].v = 0;
		i++;

		box2[i].x = size;
		box2[i].y = -size;
		box2[i].z = size;
		box2[i].u = 0;
		box2[i].v = 1;
		i++;

		box2[i].x = -size;
		box2[i].y = -size;
		box2[i].z = size;
		box2[i].u = 1;
		box2[i].v = 1;
		i++;

		sceKernelDcacheWritebackInvalidateRange(box2,4 * sizeof(TexturesPSPVertex));

		i = 0;

		box3[i].x = -size;
		box3[i].y = -size;
		box3[i].z = -size;
		box3[i].u = 1;
		box3[i].v = 1;
		i++;

		box3[i].x = -size;
		box3[i].y = size;
		box3[i].z = -size;
		box3[i].u = 1;
		box3[i].v = 0;
		i++;

		box3[i].x = -size;
		box3[i].y = size;
		box3[i].z = size;
		box3[i].u = 0;
		box3[i].v = 0;
		i++;

		box3[i].x = -size;
		box3[i].y = -size;
		box3[i].z = size;
		box3[i].u = 0;
		box3[i].v = 1;
		i++;

		sceKernelDcacheWritebackInvalidateRange(box3,4 * sizeof(TexturesPSPVertex));

		i = 0;

		box4[i].x = -size;
		box4[i].y = size;
		box4[i].z = -size;
		box4[i].u = 0;
		box4[i].v = 1;
		i++;

		box4[i].x = size;
		box4[i].y = size;
		box4[i].z = -size;
		box4[i].u = 1;
		box4[i].v = 1;
		i++;

		box4[i].x = size;
		box4[i].y = size;
		box4[i].z = size;
		box4[i].u = 1;
		box4[i].v = 0;
		i++;

		box4[i].x = -size;
		box4[i].y = size;
		box4[i].z = size;
		box4[i].u = 0;
		box4[i].v = 0;
		i++;

		sceKernelDcacheWritebackInvalidateRange(box4,4 * sizeof(TexturesPSPVertex));

		i = 0;

		box5[i].x = -size;
		box5[i].y = -size;
		box5[i].z = size;
		box5[i].u = 0;
		box5[i].v = 1;
		i++;

		box5[i].x = size;
		box5[i].y = -size;
		box5[i].z = size;
		box5[i].u = 1;
		box5[i].v = 1;
		i++;

		box5[i].x = size;
		box5[i].y = -size;
		box5[i].z = -size;
		box5[i].u = 1;
		box5[i].v = 0;
		i++;

		box5[i].x = -size;
		box5[i].y = -size;
		box5[i].z = -size;
		box5[i].u = 0;
		box5[i].v = 0;
		i++;

		sceKernelDcacheWritebackInvalidateRange(box5,4 * sizeof(TexturesPSPVertex));
}

Panorama::~Panorama(){
	
	free(box0);
	free(box1);
	free(box2);
	free(box3);
	free(box4);
	free(box5);
	
	// Liberar las texturas
    //TextureManager::Instance()->RemoveTexture(panorama0);
    //TextureManager::Instance()->RemoveTexture(panorama1);
    //TextureManager::Instance()->RemoveTexture(panorama2);
    //TextureManager::Instance()->RemoveTexture(panorama3);
    //TextureManager::Instance()->RemoveTexture(panorama4);
    //TextureManager::Instance()->RemoveTexture(panorama5);
}

void Panorama::update(float dt){
	GlobalFunctions::Instance()->angleX += dt * (360.0f / 180.0f);
	GlobalFunctions::Instance()->angleY = vfpu_sinf( (GlobalFunctions::Instance()->angleX + 90) / 180 * 3.14159)*30.0f+5.0f;
}

void Panorama::render(){
	sceGumMatrixMode(GU_VIEW);
	sceGumPushMatrix();
	sceGumLoadIdentity();

	sceGumRotateX((GlobalFunctions::Instance()->angleY)/180 * 3.14159);
	sceGumRotateY((GlobalFunctions::Instance()->angleX)/180 * 3.14159);
	sceGumRotateZ(0.0f);

	sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_BLEND);
	sceGuDisable(GU_DEPTH_TEST);
	sceGuDisable(GU_CULL_FACE);
	sceGuDepthMask(GU_TRUE);
	
	
	//panorama0->bindTexture(GU_LINEAR_MIPMAP_LINEAR, GU_LINEAR_MIPMAP_LINEAR);
	//TextureManager::Instance()->SetTexture(panorama0);
	TextureManager::Instance()->SetTextureConstModeulate(panorama0);
	sceGumDrawArray(GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, box0);
	
	//panorama1->bindTexture(GU_LINEAR_MIPMAP_LINEAR, GU_LINEAR_MIPMAP_LINEAR);
	TextureManager::Instance()->SetTextureConstModeulate(panorama1);
	sceGumDrawArray(GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, box1);
	
	//panorama2->bindTexture(GU_LINEAR_MIPMAP_LINEAR, GU_LINEAR_MIPMAP_LINEAR);
	TextureManager::Instance()->SetTextureConstModeulate(panorama2);
	sceGumDrawArray(GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, box2);
	
	//panorama3->bindTexture(GU_LINEAR_MIPMAP_LINEAR, GU_LINEAR_MIPMAP_LINEAR);
	TextureManager::Instance()->SetTextureConstModeulate(panorama3);
	sceGumDrawArray(GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, box3);
	
	//panorama4->bindTexture(GU_LINEAR_MIPMAP_LINEAR, GU_LINEAR_MIPMAP_LINEAR);
	TextureManager::Instance()->SetTextureConstModeulate(panorama4);
	sceGumDrawArray(GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, box4);
	
	//panorama5->bindTexture(GU_LINEAR_MIPMAP_LINEAR, GU_LINEAR_MIPMAP_LINEAR);
	TextureManager::Instance()->SetTextureConstModeulate(panorama5);
	sceGumDrawArray(GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 4, 0, box5);

	sceGuEnable(GU_DEPTH_TEST);

	sceGuEnable(GU_CULL_FACE);
	sceGuDepthMask(GU_FALSE);

	sceGumPopMatrix();
}